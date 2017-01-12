/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Joel Höner

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

***************************************************************************************************/

#include <Zydis/Encoder.h>

/* ============================================================================================== */
/* Internal context                                                                               */
/* ============================================================================================== */

/**
 * @brief   The encoder context struct.
 */
typedef struct ZydisInstructionEncoder_
{
    uint8_t* buffer;
    size_t bufferLen;
    size_t writeOffs;
    ZydisInstructionInfo* info;
} ZydisInstructionEncoder;

/* ============================================================================================== */
/* Internal helpers                                                                               */
/* ============================================================================================== */

static ZydisStatus ZydisEmitByte(ZydisInstructionEncoder* encoder, uint8_t byte)
{
    if (encoder->writeOffs + 1 >= encoder->bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    encoder->buffer[encoder->writeOffs++] = byte;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeLegacyPrefixes(ZydisInstructionEncoder* encoder)
{
    ZYDIS_ASSERT(encoder);
    uint64_t attribs = encoder->info->attributes;

    if (attribs & ZYDIS_ATTRIB_HAS_LOCK) 
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0xF0));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_REP | ZYDIS_ATTRIB_HAS_REPE | ZYDIS_ATTRIB_HAS_XRELEASE)) 
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0xF3));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_REPNE | ZYDIS_ATTRIB_HAS_BOUND | ZYDIS_ATTRIB_HAS_XACQUIRE))
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0xF2));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN | ZYDIS_ATTRIB_HAS_SEGMENT_CS))
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x2E));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_BRANCH_TAKEN | ZYDIS_ATTRIB_HAS_SEGMENT_DS))
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x3E));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_SS)
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x36));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_ES)
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x26));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_FS)
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x64));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_GS)
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x65));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_OPERANDSIZE)
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x66));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_ADDRESSSIZE)
    {
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x67));
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeREX(ZydisInstructionEncoder *encoder)
{
    ZYDIS_ASSERT(encoder);
    ZYDIS_CHECK(ZydisEmitByte(
        encoder, 
        0x40 |
        (encoder->info->details.rex.W & 0x01) << 3 |
        (encoder->info->details.rex.R & 0x01) << 2 |
        (encoder->info->details.rex.X & 0x01) << 1 |
        (encoder->info->details.rex.B & 0x01) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeVEX(ZydisInstructionEncoder *encoder)
{
    ZYDIS_ASSERT(encoder);

    // Write opcode.
    uint8_t opcode = encoder->info->details.vex.data[0];
    ZYDIS_CHECK(ZydisEmitByte(encoder, opcode));

    // Write prefix' "operands".
    switch (opcode)
    {
    case 0xC4:
        ZYDIS_CHECK(ZydisEmitByte(
            encoder, 
            (encoder->info->details.vex.R      & 0x01) << 7 | 
            (encoder->info->details.vex.X      & 0x01) << 6 |
            (encoder->info->details.vex.B      & 0x01) << 5 |
            (encoder->info->details.vex.m_mmmm & 0x1F) << 0
        ));
        ZYDIS_CHECK(ZydisEmitByte(
            encoder, 
            (encoder->info->details.vex.W      & 0x01) << 7 | 
            (encoder->info->details.vex.vvvv   & 0x0F) << 3 |
            (encoder->info->details.vex.L      & 0x01) << 2 |
            (encoder->info->details.vex.pp     & 0x03) << 0 
        ));
        break;
    case 0xC5:
        ZYDIS_CHECK(ZydisEmitByte(
            encoder, 
            (encoder->info->details.vex.R      & 0x01) << 7 | 
            (encoder->info->details.vex.vvvv   & 0x0F) << 3 |
            (encoder->info->details.vex.L      & 0x01) << 2 |
            (encoder->info->details.vex.pp     & 0x03) << 0 
        ));
        break;
    default:
        ZYDIS_UNREACHABLE; // TODO: return error instead
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeEVEX(ZydisInstructionEncoder *encoder)
{
    ZYDIS_ASSERT(encoder);

    ZYDIS_CHECK(ZydisEmitByte(encoder, 0x62));
    ZYDIS_CHECK(ZydisEmitByte(
        encoder, 
        (encoder->info->details.evex.R  & 0x01) << 7 |
        (encoder->info->details.evex.X  & 0x01) << 6 |
        (encoder->info->details.evex.B  & 0x01) << 5 |
        (encoder->info->details.evex.R2 & 0x01) << 4 |
        (encoder->info->details.evex.mm & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        encoder, 
        (encoder->info->details.evex.W    & 0x01) << 7 |
        (encoder->info->details.evex.vvvv & 0x0F) << 3 |
        (encoder->info->details.evex.pp   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        encoder,
        (encoder->info->details.evex.z    & 0x01) << 7 |
        (encoder->info->details.evex.L2   & 0x01) << 6 |
        (encoder->info->details.evex.L    & 0x01) << 5 |
        (encoder->info->details.evex.b    & 0x01) << 4 |
        (encoder->info->details.evex.V2   & 0x01) << 3 |
        (encoder->info->details.evex.aaa  & 0x07) << 0
    ));

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeXOP(ZydisInstructionEncoder *encoder)
{
    ZYDIS_ASSERT(encoder);
    
    ZYDIS_CHECK(ZydisEmitByte(encoder, 0x8F));
    ZYDIS_CHECK(ZydisEmitByte(
        encoder,
        (encoder->info->details.xop.R      & 0x01) << 7 |
        (encoder->info->details.xop.X      & 0x01) << 6 |
        (encoder->info->details.xop.B      & 0x01) << 5 |
        (encoder->info->details.xop.m_mmmm & 0x1F) << 0 
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        encoder,
        (encoder->info->details.xop.W      & 0x01) << 7 |
        (encoder->info->details.xop.vvvv   & 0x0F) << 3 |
        (encoder->info->details.xop.L      & 0x01) << 2 |
        (encoder->info->details.xop.pp     & 0x03) << 0 
    ));

    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
/* Implementation of public functions                                                             */
/* ============================================================================================== */

ZydisStatus ZydisEncoderEncodeInstruction(void* buffer, size_t bufferLen,
    ZydisInstructionInfo* info)
{
    if (!info) return ZYDIS_STATUS_INVALID_PARAMETER;
    if (!buffer || !bufferLen) return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;

    ZydisInstructionEncoder encoder;
    encoder.buffer = (uint8_t*)buffer;
    encoder.bufferLen = bufferLen;
    encoder.writeOffs = 0;
    encoder.info = info;

    ZYDIS_CHECK(ZydisEncodeLegacyPrefixes(&encoder));

    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
