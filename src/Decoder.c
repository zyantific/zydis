/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

  Original Author : Florian Bernd

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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <Zydis/Status.h>
#include <Zydis/Input.h>
#include <Zydis/Decoder.h>
#include <Zydis/Internal/InstructionTable.h>

/* ============================================================================================== */
/* Internal macros                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Constants                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_MAX_INSTRUCTION_LENGTH 15

/* ---------------------------------------------------------------------------------------------- */
/* Helper macros                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_CHECK(status) \
    if (status != ZYDIS_STATUS_DECODER_SUCCESS) \
    { \
        return status; \
    }

/* ============================================================================================== */
/* Internal enums and structs                                                                     */
/* ============================================================================================== */

/**
 * @brief   Defines the @c ZydisDecoderStatus datatype.
 */
typedef uint32_t ZydisDecoderStatus;

/**
 * @brief   Values that represents zydis decoder status-codes.
 */
typedef enum ZydisDecoderStatusCode_
{
    ZYDIS_STATUS_DECODER_SUCCESS,
    ZYDIS_STATUS_DECODER_NO_MORE_DATA,
    ZYDIS_STATUS_DECODER_INVALID_INSTRUCTION,
    ZYDIS_STATUS_DECODER_INVALID_INSTRUCTION_LENGTH,
    ZYDIS_STATUS_DECODER_MALFORMED_VEX_PREFIX,
    ZYDIS_STATUS_DECODER_MALFORMED_EVEX_PREFIX,
    ZYDIS_STATUS_DECODER_MALFORMED_XOP_PREFIX,
    ZYDIS_STATUS_DECODER_ILLEGAL_REX,
    ZYDIS_STATUS_DECODER_INVALID_VSIB
} ZydisDecoderStatusCode;

/* ============================================================================================== */
/* Internal functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Input helper functions                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Reads one byte from the current read-position of the input data-source.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   value   A pointer to the memory that receives the byte from the input data-source.
 *
 * @return  A zydis decoder status code.
 *          
 * If not empty, the internal buffer of the @c ZydisInstructionDecoder instance is used as temporary
 * data-source, instead of reading the byte from the actual input data-source.
 * 
 * This function may fail, if the @c ZYDIS_MAX_INSTRUCTION_LENGTH limit got exceeded, or no more   
 * data is available.
 */
static ZydisDecoderStatus ZydisInputPeek(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint8_t* value)
{ 
    ZYDIS_ASSERT(decoder); 
    ZYDIS_ASSERT(info); 
    ZYDIS_ASSERT(value);

    if (info->length >= ZYDIS_MAX_INSTRUCTION_LENGTH) 
    { 
        info->flags |= ZYDIS_INSTRUCTION_ERROR_INSTRUCTION_LENGTH; 
        return ZYDIS_STATUS_DECODER_INVALID_INSTRUCTION_LENGTH; 
    } 

    if (decoder->buffer.count > 0)
    {
        ZYDIS_ASSERT(decoder->buffer.posRead < sizeof(decoder->buffer.data));
        *value = decoder->buffer.data[decoder->buffer.posRead];
        return ZYDIS_STATUS_DECODER_SUCCESS;
    }

    if (!decoder->input->inputNext((void*)decoder->input, value))
    {
        return ZYDIS_STATUS_DECODER_NO_MORE_DATA;    
    }
    
    ZYDIS_ASSERT(decoder->buffer.count < sizeof(decoder->buffer.data));
    decoder->buffer.data[decoder->buffer.posWrite++] = *value;
    if (decoder->buffer.posWrite == sizeof(decoder->buffer.data))
    {
        decoder->buffer.posWrite = 0;
    }
    ++decoder->buffer.count;

    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/**
 * @brief   Increases the read-position of the input data-source by one byte.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 *                  
 * This function is supposed to get called ONLY after a successfull call of @c ZydisInputPeek.
 * 
 * If not empty, the read-position of the @c ZydisInstructionDecoder instances internal buffer is
 * increased, instead of the actual input data-sources read-position.
 * 
 * This function increases the @c length field of the @c ZydisInstructionInfo struct by one and
 * adds the current byte to the @c data array.
 */
static void ZydisInputSkip(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info)
{ 
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->length < ZYDIS_MAX_INSTRUCTION_LENGTH);

    info->data[info->length++] = decoder->buffer.data[decoder->buffer.posRead++];
    if (decoder->buffer.posRead == sizeof(decoder->buffer.data))
    {
        decoder->buffer.posRead = 0;
    }  
    --decoder->buffer.count;
}

/**
 * @brief   Reads one byte from the current read-position of the input data-source and increases the
 *          read-position by one byte afterwards.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   value   A pointer to the memory that receives the byte from the input data-source.
 *
 * @return  A zydis decoder status code.
 *          
 * This function acts like a subsequent call of @c ZydisInputPeek and @c ZydisInputSkip.
 */
static ZydisDecoderStatus ZydisInputNext(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint8_t* value)
{ 
    ZydisDecoderStatus status = ZydisInputPeek(decoder, info, value);
    if (status != ZYDIS_STATUS_DECODER_SUCCESS)
    {
        return status;
    }
    ZydisInputSkip(decoder, info);
    return ZYDIS_STATUS_DECODER_SUCCESS; 
}

/* ---------------------------------------------------------------------------------------------- */
/* Decoder functions                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Decodes the rex-prefix.
 *
 * @param   rexByte The rex byte.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 */
static void ZydisDecodeRexPrefix(ZydisInstructionInfo* info, uint8_t rexByte)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT((rexByte & 0xF0) == 0x40);

    info->details.rex.isDecoded = true;
    info->details.rex.data[0]   = rexByte;
    info->details.rex.w         = (rexByte >> 3) & 0x01;
    info->details.rex.r         = (rexByte >> 2) & 0x01;
    info->details.rex.x         = (rexByte >> 1) & 0x01;
    info->details.rex.b         = (rexByte >> 0) & 0x01;
    // Update internal fields
    info->details.internal.w    = info->details.rex.w;
    info->details.internal.r    = info->details.rex.r;
    info->details.internal.x    = info->details.rex.x;
    info->details.internal.b    = info->details.rex.b;
}

/**
 * @brief   Decodes the vex-prefix.
 *
 * @param   vexOpcode   The vex opcode.
 * @param   vexByte1    The first vex byte.
 * @param   vexByte2    The second vex byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  True if the decoding succeeds, false if an invalid vex encoding was detected.
 */
static bool ZydisDecodeVexPrefix(uint8_t vexOpcode, uint8_t vexByte1, uint8_t vexByte2, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    info->details.vex.isDecoded     = true;
    info->details.vex.data[0]       = vexOpcode;
    switch (vexOpcode)
    {
    case 0xC4:
    {
        info->details.vex.data[1]   = vexByte1;
        info->details.vex.data[2]   = vexByte2;
        info->details.vex.r         = (vexByte1 >> 7) & 0x01;
        info->details.vex.x         = (vexByte1 >> 6) & 0x01;
        info->details.vex.b         = (vexByte1 >> 5) & 0x01;
        info->details.vex.m_mmmm    = (vexByte1 >> 0) & 0x1F;
        info->details.vex.w         = (vexByte2 >> 7) & 0x01;
        info->details.vex.vvvv      = (vexByte2 >> 3) & 0x0F;
        info->details.vex.l         = (vexByte2 >> 2) & 0x01;
        info->details.vex.pp        = (vexByte2 >> 0) & 0x03;
        break;
    }
    case 0xC5:
        info->details.vex.data[1]   = vexByte1;
        info->details.vex.data[2]   = 0;
        info->details.vex.r         = (vexByte1 >> 7) & 0x01;
        info->details.vex.x         = 1;
        info->details.vex.b         = 1;
        info->details.vex.m_mmmm    = 1;
        info->details.vex.w         = 0;
        info->details.vex.vvvv      = (vexByte1 >> 3) & 0x0F;
        info->details.vex.l         = (vexByte1 >> 2) & 0x01;
        info->details.vex.pp        = (vexByte1 >> 0) & 0x03;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }  
    if ((info->details.vex.m_mmmm == 0x00) || (info->details.vex.m_mmmm > 0x03))
    {
        // Invalid according to the intel documentation
        return false;
    }
    // Update internal fields
    info->details.internal.w = info->details.vex.w;
    info->details.internal.r = 0x01 & ~info->details.vex.r;
    info->details.internal.x = 0x01 & ~info->details.vex.x;
    info->details.internal.b = 0x01 & ~info->details.vex.b;
    info->details.internal.l = info->details.vex.l;
    return true;
}

/**
 * @brief   Decodes the evex-prefix.
 *
 * @param   evexByte1   The first evex byte.
 * @param   evexByte2   The second evex byte.
 * @param   evexByte3   The third evex byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  True if the decoding succeeds, false if an invalid evex encoding was detected.
 */
static bool ZydisDecodeEvexPrefix(uint8_t evexByte1, uint8_t evexByte2, uint8_t evexByte3, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    info->details.evex.isDecoded    = true;
    info->details.evex.data[0]      = 0x62;
    info->details.evex.data[1]      = evexByte1;
    info->details.evex.data[2]      = evexByte2;
    info->details.evex.data[3]      = evexByte3;
    info->details.evex.r            = (evexByte1 >> 7) & 0x01;
    info->details.evex.x            = (evexByte1 >> 6) & 0x01;
    info->details.evex.b            = (evexByte1 >> 5) & 0x01;
    info->details.evex.r2           = (evexByte1 >> 4) & 0x01;
    if (((evexByte1 >> 2) & 0x03) != 0x00)
    {
        // Invalid according to the intel documentation
        return false;
    }
    info->details.evex.mm           = (evexByte1 >> 0) & 0x03;
    if (info->details.evex.mm == 0x00)
    {
        // Invalid according to the intel documentation
        return false;
    }
    info->details.evex.w            = (evexByte2 >> 7) & 0x01;
    info->details.evex.vvvv         = (evexByte2 >> 3) & 0x0F;
    if (((evexByte2 >> 2) & 0x01) != 0x01)
    {
        // Invalid according to the intel documentation
        return false;
    }
    info->details.evex.pp           = (evexByte2 >> 0) & 0x03;
    info->details.evex.z            = (evexByte3 >> 7) & 0x01;
    info->details.evex.l2           = (evexByte3 >> 6) & 0x01;
    info->details.evex.l            = (evexByte3 >> 5) & 0x01;
    info->details.evex.b0           = (evexByte3 >> 4) & 0x01;
    info->details.evex.v2           = (evexByte3 >> 3) & 0x01;
    info->details.evex.aaa          = (evexByte3 >> 0) & 0x07;    
    // Update internal fields
    info->details.internal.w = info->details.evex.w;
    info->details.internal.r = 0x01 & ~info->details.evex.r;
    info->details.internal.x = 0x01 & ~info->details.evex.x;
    info->details.internal.b = 0x01 & ~info->details.evex.b;
    info->details.internal.l = info->details.evex.l;
    return true;
}

/**
 * @brief   Decodes the xop-prefix.
 *
 * @param   xopByte1    The first xop byte.
 * @param   xopByte2    The second xop byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  True if the decoding succeeds, false if an invalid xop encoding was detected.
 */
static bool ZydisDecodeXopPrefix(uint8_t xopByte1, uint8_t xopByte2, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(((xopByte1 >> 0) & 0x1F) >= 8);

    info->details.xop.isDecoded     = true;
    info->details.xop.data[0]       = 0x8F;
    info->details.xop.data[1]       = xopByte1;
    info->details.xop.data[2]       = xopByte2;
    info->details.xop.r             = (xopByte1 >> 7) & 0x01;
    info->details.xop.x             = (xopByte1 >> 6) & 0x01;
    info->details.xop.b             = (xopByte1 >> 5) & 0x01;
    info->details.xop.m_mmmm        = (xopByte1 >> 0) & 0x1F;
    if ((info->details.xop.m_mmmm < 0x08) || (info->details.xop.m_mmmm > 0x0A))
    {
        // Invalid according to the documentation
        return false;
    }
    info->details.xop.w             = (xopByte2 >> 7) & 0x01;
    info->details.xop.vvvv          = (xopByte2 >> 3) & 0x0F;
    info->details.xop.l             = (xopByte2 >> 2) & 0x01;
    info->details.xop.pp            = (xopByte2 >> 0) & 0x03; 
    // Update internal fields
    info->details.internal.w = info->details.xop.w;
    info->details.internal.r = 0x01 & ~info->details.xop.r;
    info->details.internal.x = 0x01 & ~info->details.xop.x;
    info->details.internal.b = 0x01 & ~info->details.xop.b;
    info->details.internal.l = info->details.xop.l;     
    return true;
}

/**
 * @brief   Decodes the modrm-byte.
 *
 * @param   modrmByte   The modrm byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 */
static void ZydisDecodeModrm(uint8_t modrmByte, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    info->flags |= ZYDIS_INSTRUCTION_HAS_MODRM;
    info->details.modrm.isDecoded   = true;
    info->details.modrm.data[0]     = modrmByte;
    info->details.modrm.mod         = (modrmByte >> 6) & 0x03;
    info->details.modrm.reg         = (modrmByte >> 3) & 0x07;
    info->details.modrm.rm          = (modrmByte >> 0) & 0x07;
}

/**
 * @brief   Decodes the sib-byte.
 *
 * @param   sibByte The sib byte.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct
 */
static void ZydisDecodeSib(uint8_t sibByte, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->details.modrm.isDecoded);
    ZYDIS_ASSERT((info->details.modrm.rm & 0x7) == 4);

    info->flags |= ZYDIS_INSTRUCTION_HAS_SIB;
    info->details.sib.isDecoded = true;
    info->details.sib.data[0]   = sibByte;
    info->details.sib.scale     = (sibByte >> 6) & 0x03;
    info->details.sib.index     = (sibByte >> 3) & 0x07;
    info->details.sib.base      = (sibByte >> 0) & 0x07;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Collects optional instruction prefixes.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  A zydis decoder status code.
 *         
 * This function sets the corresponding flag for each prefix and automatically decodes the last
 * rex-prefix (if exists).
 */
static ZydisDecoderStatus ZydisCollectOptionalPrefixes(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);

    uint8_t groups[4] = { 0, 0, 0, 0 };
    bool done = false;
    do
    {
        uint8_t prefixByte;
        ZYDIS_CHECK(ZydisInputPeek(decoder, info, &prefixByte));
        switch (prefixByte)
        {
        case 0xF0:
            info->prefixes |= ZYDIS_PREFIX_LOCK;
            ++groups[0];
            break;
        case 0xF2:
            // 0xF2 and 0xF3 are mutally exclusive. The one that comes later has precedence.
            info->prefixes |= ZYDIS_PREFIX_REPNE;
            info->prefixes &= ~ZYDIS_PREFIX_REP;
            ++groups[0];
            break;
        case 0xF3:
            // 0xF2 and 0xF3 are mutally exclusive. The one that comes later has precedence.
            info->prefixes |= ZYDIS_PREFIX_REP;
            info->prefixes &= ~ZYDIS_PREFIX_REPNE;
            ++groups[0];
            break;
        case 0x2E: 
            info->prefixes |= ZYDIS_PREFIX_SEGMENT_CS;
            ++groups[1];
            break;
        case 0x36:
            info->prefixes |= ZYDIS_PREFIX_SEGMENT_SS;
            ++groups[1];
            break;
        case 0x3E: 
            info->prefixes |= ZYDIS_PREFIX_SEGMENT_DS;
            ++groups[1];
            break;
        case 0x26: 
            info->prefixes |= ZYDIS_PREFIX_SEGMENT_ES;
            ++groups[1];
            break;
        case 0x64:
            info->prefixes |= ZYDIS_PREFIX_SEGMENT_FS;
            ++groups[1];
            break;
        case 0x65: 
            info->prefixes |= ZYDIS_PREFIX_SEGMENT_GS;
            ++groups[1];
            break;
        case 0x66:
            info->prefixes |= ZYDIS_PREFIX_OPERANDSIZE;
            ++groups[2];
            break;
        case 0x67:
            info->prefixes |= ZYDIS_PREFIX_ADDRESSSIZE;
            ++groups[3];
            break;
        default:
            if ((decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) && 
                (prefixByte & 0xF0) == 0x40)
            {
                info->prefixes |= ZYDIS_PREFIX_REX;
                info->details.rex.data[0] = prefixByte; 
            } else
            {
                done = true;
            }
            break;
        }
        if (!done)
        {
            ZydisInputSkip(decoder, info);
        }
    } while (!done);

    if (info->prefixes & ZYDIS_PREFIX_REX)
    {
        ZydisDecodeRexPrefix(info, info->details.rex.data[0]);
    }

    if (groups[0] > 1)
    {
        info->prefixes |= ZYDIS_PREFIX_MULTIPLE_GRP1;
    }
    if (groups[1] > 1)
    {
        info->prefixes |= ZYDIS_PREFIX_MULTIPLE_GRP2;
    }
    if (groups[2] > 1)
    {
        info->prefixes |= ZYDIS_PREFIX_MULTIPLE_GRP3;
    }
    if (groups[3] > 1)
    {
        info->prefixes |= ZYDIS_PREFIX_MULTIPLE_GRP4;
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Decodes an immediate operand.
 *
 * @param   decoder         A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand         A pointer to the @c ZydisOperandInfo struct.
 * @param   physicalSize    The physical size of the immediate operand.
 * @param   isSigned        Set @c true, if the immediate value is signed or @c false, if not.
 *
 * @return  A zydis decoder status code.
 */
static ZydisDecoderStatus ZydisDecodeOperandImmediate(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, ZydisOperandInfo* operand, uint8_t physicalSize, bool isSigned)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);
    
    operand->type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
    operand->imm.isSigned = isSigned;
    operand->imm.dataSize = physicalSize;
    operand->imm.dataOffset = info->length;
    switch (physicalSize)
    {
    case 8:
    {
        // We have to store a copy of the imm8 value for instructions that encode different operands
        // in the lo and hi part of the immediate.
        if (decoder->imm8initialized)
        {
            operand->imm.value.ubyte = decoder->imm8;        
        } else
        {
            uint8_t immediate;
            ZYDIS_CHECK(ZydisInputNext(decoder, info, &immediate));
            if (isSigned)
            {
                operand->imm.value.sqword = (int8_t)immediate;
            } else
            {
                operand->imm.value.uqword = immediate;       
            }
            decoder->imm8initialized = true;
            decoder->imm8 = operand->imm.value.ubyte;   
        }
        break;
    }
    case 16:
    {
        uint16_t data[2] = { 0, 0 };
        ZYDIS_CHECK(ZydisInputNext(decoder, info, (uint8_t*)&data[1]));
        ZYDIS_CHECK(ZydisInputNext(decoder, info, (uint8_t*)&data[0]));
        uint16_t immediate;
        immediate = (data[0] << 8) | data[1];
        if (isSigned)
        {
            operand->imm.value.sqword = (int16_t)immediate;
        } else
        {
            operand->imm.value.uqword = immediate;       
        }
        break;   
    }
    case 32:
    {
        uint32_t data[4] = { 0, 0, 0, 0 };
        for (int i = sizeof(data) / sizeof(data[0]); i > 0; --i)
        {
            ZYDIS_CHECK(ZydisInputNext(decoder, info, (uint8_t*)&data[i - 1]));    
        }
        uint32_t immediate;
        immediate = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        if (isSigned)
        {
            operand->imm.value.sqword = (int32_t)immediate;
        } else
        {
            operand->imm.value.uqword = immediate;       
        }
        break;
    }
    case 64:
    {
        uint64_t data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int i = sizeof(data) / sizeof(data[0]); i > 0; --i)
        {
            ZYDIS_CHECK(ZydisInputNext(decoder, info, (uint8_t*)&data[i - 1]));    
        }
        uint64_t immediate;
        immediate = (data[0] << 56) | (data[1] << 48) | (data[2] << 40) | (data[3] << 32) | 
            (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
        if (isSigned)
        {
            operand->imm.value.sqword = (int64_t)immediate;
        } else
        {
            operand->imm.value.uqword = immediate;       
        }
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/**
 * @brief   Decodes an register-operand.
 *
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand         A pointer to the @c ZydisOperandInfo struct.
 * @param   registerClass   The register class.
 * @param   registerId      The register id.
 *
 * @return  A zydis decoder status code.
 */
static ZydisDecoderStatus ZydisDecodeOperandRegister(ZydisInstructionInfo* info, 
    ZydisOperandInfo* operand, ZydisRegisterClass registerClass, uint8_t registerId)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);

    operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
    if (registerClass == ZYDIS_REGISTERCLASS_GENERAL_PURPOSE8)
    {
        if ((info->prefixes & ZYDIS_PREFIX_REX) && (registerId >= 4)) 
        {
            operand->reg = ZYDIS_REGISTER_SPL + (registerId - 4);
        } else 
        {
            operand->reg = ZYDIS_REGISTER_AL + registerId;
        }
        if (operand->reg > ZYDIS_REGISTER_R15B)
        {
            operand->reg = ZYDIS_REGISTER_NONE;
        }
    } else
    {
        operand->reg = ZydisRegisterGetById(registerClass, registerId);
    }

    // TODO: Return critical error, if an invalid register was found

    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/**
 * @brief   Decodes a memory or register operand encoded in the modrm.rm field.
 *
 * @param   decoder         A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand         A pointer to the @c ZydisOperandInfo struct.
 * @param   registerClass   The register class.
 *
 * @return  A zydis decoder status code.
 */
static ZydisDecoderStatus ZydisDecodeOperandModrmRm(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, ZydisOperandInfo* operand, ZydisRegisterClass registerClass)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);
    ZYDIS_ASSERT(info->details.modrm.isDecoded);

    uint8_t modrm_rm = (info->details.internal.b << 3) | info->details.modrm.rm;
    if (info->details.modrm.mod == 3)
    {
        return ZydisDecodeOperandRegister(info, operand, registerClass, modrm_rm);
    }
    operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
    uint8_t displacementSize = 0;
    info->prefixes |= ZYDIS_PREFIX_ACCEPTS_ADDRESSSIZE;
    switch (decoder->disassemblerMode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
        operand->mem.addressSize = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 32 : 16;
        break;
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
        operand->mem.addressSize = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 16 : 32;
        break;
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        operand->mem.addressSize = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 32 : 64;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    switch (operand->mem.addressSize)
    {
    case 16:
    {
        static const ZydisRegister bases[] = 
        { 
            ZYDIS_REGISTER_BX,   ZYDIS_REGISTER_BX,   ZYDIS_REGISTER_BP,   ZYDIS_REGISTER_BP, 
            ZYDIS_REGISTER_SI,   ZYDIS_REGISTER_DI,   ZYDIS_REGISTER_BP,   ZYDIS_REGISTER_BX 
        };
        static const ZydisRegister indices[] = 
        { 
            ZYDIS_REGISTER_SI,   ZYDIS_REGISTER_DI,   ZYDIS_REGISTER_SI,   ZYDIS_REGISTER_DI,
            ZYDIS_REGISTER_NONE, ZYDIS_REGISTER_NONE, ZYDIS_REGISTER_NONE, ZYDIS_REGISTER_NONE 
        };
        operand->mem.base = bases[modrm_rm & 0x07];
        operand->mem.index = indices[modrm_rm & 0x07];
        operand->mem.scale = 0;
        if ((info->details.modrm.mod == 0) && (modrm_rm == 6)) 
        {
            displacementSize = 16;
            operand->mem.base = ZYDIS_REGISTER_NONE;
        } else if (info->details.modrm.mod == 1) 
        {
            displacementSize = 8;
        } else if (info->details.modrm.mod == 2) 
        {
            displacementSize = 16;
        }
        break;
    }
    case 32:
    {
        operand->mem.base = ZYDIS_REGISTER_EAX + modrm_rm;
        switch (info->details.modrm.mod)
        {
        case 0:
            if (modrm_rm == 5)
            {
                if (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT)
                {
                    info->flags |= ZYDIS_INSTRUCTION_RELATIVE;
                    operand->mem.base = ZYDIS_REGISTER_EIP;
                } else
                {
                    operand->mem.base = ZYDIS_REGISTER_NONE;
                }
                displacementSize = 32;
            }
            break;
        case 1:
            displacementSize = 8;
            break;
        case 2:
            displacementSize = 32;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        if ((modrm_rm & 0x07) == 4)
        {
            if (!info->details.sib.isDecoded)
            {                                                                          
                uint8_t sibByte;
                ZYDIS_CHECK(ZydisInputNext(decoder, info, &sibByte)); 
                ZydisDecodeSib(sibByte, info);
            }
            uint8_t sib_index = (info->details.internal.x << 3) | info->details.sib.index;
            uint8_t sib_base = (info->details.internal.b << 3) | info->details.sib.base;
            operand->mem.base = ZYDIS_REGISTER_EAX + sib_base;
            operand->mem.index = ZYDIS_REGISTER_EAX + sib_index;
            operand->mem.scale = (1 << info->details.sib.scale) & ~1;
            if (operand->mem.index == ZYDIS_REGISTER_ESP)  
            {
                operand->mem.index = ZYDIS_REGISTER_NONE;
                operand->mem.scale = 0;
            } 
            if (operand->mem.base == ZYDIS_REGISTER_EBP)
            {
                if (info->details.modrm.mod == 0)
                {
                    operand->mem.base = ZYDIS_REGISTER_NONE;
                } 
                displacementSize = (info->details.modrm.mod == 1) ? 8 : 32;
            }
        } else
        {
            operand->mem.index = ZYDIS_REGISTER_NONE;
            operand->mem.scale = 0;    
        }
        break;
    }
    case 64:
    {
        operand->mem.base = ZYDIS_REGISTER_RAX + modrm_rm;
        switch (info->details.modrm.mod)
        {
        case 0:
            if (modrm_rm == 5)
            {
                info->flags |= ZYDIS_INSTRUCTION_RELATIVE;
                operand->mem.base = ZYDIS_REGISTER_RIP;
                displacementSize = 32;
            }
            break;
        case 1:
            displacementSize = 8;
            break;
        case 2:
            displacementSize = 32;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        if ((modrm_rm & 0x07) == 4)
        {
            if (!info->details.sib.isDecoded)
            {                                                                          
                uint8_t sibByte;
                ZYDIS_CHECK(ZydisInputNext(decoder, info, &sibByte)); 
                ZydisDecodeSib(sibByte, info);
            }
            uint8_t sib_index = (info->details.internal.x << 3) | info->details.sib.index;
            uint8_t sib_base = (info->details.internal.b << 3) | info->details.sib.base;
            operand->mem.base = ZYDIS_REGISTER_RAX + sib_base;
            operand->mem.index = ZYDIS_REGISTER_RAX + sib_index;
            operand->mem.scale = (1 << info->details.sib.scale) & ~1;
            if (operand->mem.index == ZYDIS_REGISTER_RSP)  
            {
                operand->mem.index = ZYDIS_REGISTER_NONE;
                operand->mem.scale = 0;
            } 
            if ((operand->mem.base == ZYDIS_REGISTER_RBP) || 
                (operand->mem.base == ZYDIS_REGISTER_R13))
            {
                if (info->details.modrm.mod == 0)
                {
                    operand->mem.base = ZYDIS_REGISTER_NONE;
                } 
                displacementSize = (info->details.modrm.mod == 1) ? 8 : 32;
            }
        } else
        {
            operand->mem.index = ZYDIS_REGISTER_NONE;
            operand->mem.scale = 0;    
        }
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }
    if (displacementSize)
    {
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, displacementSize, true));
        decoder->imm8initialized = false;
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->mem.disp.dataSize = displacementSize;
        operand->mem.disp.value.sqword = operand->imm.value.sqword;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->imm.isSigned = false;
        operand->imm.dataSize = 0;
        operand->imm.value.sqword = 0;
        operand->imm.dataOffset = 0;
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/**
 * @brief   Decodes an instruction-operand.
 *
 * @param   decoder     A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand     A pointer to the @c ZydisOperandInfo struct.
 * @param   type        The sementic operand-type.
 * @param   encoding    The operand encoding.
 *
 * @return  A zydis decoder status code.
 */
static ZydisDecoderStatus ZydisDecodeOperand(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, ZydisOperandInfo* operand, 
    ZydisSemanticOperandType type, ZydisOperandEncoding encoding)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);

    // Fixed registers
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_AL:
        operand->size = 8;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_AL;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_CL:
        operand->size = 8;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_CL;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_AX:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_AX;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_DX:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_DX;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_EAX:
        operand->size = 32;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_EAX;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_RAX:
        operand->size = 64;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_RAX;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_ES:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_ES;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_CS:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_CS;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_SS:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_SS;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_DS:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_DS;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_GS:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_GS;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_FS:
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_FS;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_ST0:
        operand->size = 80;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_ST0;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    default:
        break;
    }
    
    // Register operands
    ZydisRegisterClass registerClass = ZYDIS_REGISTERCLASS_NONE;
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_GPR8:
        operand->size = 8;
        registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE8;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_GPR16:
        operand->size = 16;
        registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE16;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_GPR32:
        operand->size = 32;
        registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE32;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_GPR64:
        operand->size = 64;
        registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE64;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_TR:
        operand->size = 32; // TODO: ?
        registerClass = ZYDIS_REGISTERCLASS_TEST;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_CR:
        operand->size = (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ? 64 : 32;
        registerClass = ZYDIS_REGISTERCLASS_CONTROL;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_DR:
        operand->size = (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ? 64 : 32;
        registerClass = ZYDIS_REGISTERCLASS_DEBUG;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_FPR:
        operand->size = 80; 
        registerClass = ZYDIS_REGISTERCLASS_FLOATING_POINT;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_SREG:
        operand->size = 16;
        registerClass = ZYDIS_REGISTERCLASS_SEGMENT;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR64:
        operand->size = 64;
        registerClass = ZYDIS_REGISTERCLASS_MULTIMEDIA;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR128:
        operand->size = 128;
        registerClass = ZYDIS_REGISTERCLASS_VECTOR128;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR256:
        operand->size = 256;
        registerClass = ZYDIS_REGISTERCLASS_VECTOR256;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR512:
        operand->size = 512;
        registerClass = ZYDIS_REGISTERCLASS_VECTOR512;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MSKR:
        operand->size = 64;
        registerClass = ZYDIS_REGISTERCLASS_MASK;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_BNDR:
        operand->size = 128;
        registerClass = ZYDIS_REGISTERCLASS_BOUNDS;
        break;
    default:
        break;
    }
    if (registerClass != ZYDIS_REGISTERCLASS_NONE)
    {
        switch (encoding)
        {
        case ZYDIS_OPERAND_ENCODING_REG:
            ZYDIS_ASSERT(info->details.modrm.isDecoded);
            return ZydisDecodeOperandRegister(info, operand, registerClass, 
                (info->details.internal.r << 3) | info->details.modrm.reg);
        case ZYDIS_OPERAND_ENCODING_RM:
        case ZYDIS_OPERAND_ENCODING_RM_CD2:
        case ZYDIS_OPERAND_ENCODING_RM_CD4:
        case ZYDIS_OPERAND_ENCODING_RM_CD8:
        case ZYDIS_OPERAND_ENCODING_RM_CD16:
        case ZYDIS_OPERAND_ENCODING_RM_CD32:
        case ZYDIS_OPERAND_ENCODING_RM_CD64:
            ZYDIS_ASSERT(info->details.modrm.isDecoded);
            return ZydisDecodeOperandModrmRm(decoder, info, operand, registerClass);
        case ZYDIS_OPERAND_ENCODING_OPCODE:
        {
            uint8_t registerId = (info->opcode & 0x0F);
            if (registerId > 7)
            {
                registerId = registerId - 8;
            }
            return ZydisDecodeOperandRegister(info, operand, registerClass, 
                (info->details.internal.b << 3) | registerId);
        }
        case ZYDIS_OPERAND_ENCODING_VVVV:
            switch (info->encoding)
            {
            case ZYDIS_INSTRUCTION_ENCODING_VEX:
                ZYDIS_ASSERT(info->details.vex.isDecoded);
                return ZydisDecodeOperandRegister(info, operand, registerClass, 
                    (0x0F & ~info->details.vex.vvvv));
            case ZYDIS_INSTRUCTION_ENCODING_EVEX:
                ZYDIS_ASSERT(info->details.evex.isDecoded);
                return ZydisDecodeOperandRegister(info, operand, registerClass, 
                    (0x0F & ~info->details.evex.vvvv));
            case ZYDIS_INSTRUCTION_ENCODING_XOP:
                ZYDIS_ASSERT(info->details.xop.isDecoded);
                return ZydisDecodeOperandRegister(info, operand, registerClass, 
                    (0x0F & ~info->details.xop.vvvv));
            default:
                ZYDIS_UNREACHABLE;
            }        
            break;
        case ZYDIS_OPERAND_ENCODING_IMM8_HI:
            ZYDIS_ASSERT((info->encoding == ZYDIS_INSTRUCTION_ENCODING_VEX) ||
                (info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
                (info->encoding == ZYDIS_INSTRUCTION_ENCODING_XOP));
            ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 8, false));
            ZYDIS_CHECK(ZydisDecodeOperandRegister(info, operand, registerClass, 
                (operand->imm.value.ubyte & 0xF0) >> 4));
            operand->imm.dataSize = 0;
            operand->imm.dataOffset = 0;
            operand->imm.value.uqword = 0;
            return ZYDIS_STATUS_DECODER_SUCCESS;
        default:
            ZYDIS_UNREACHABLE;
        }
    }

    // Memory operands
    uint8_t evexCD8Scale = 0;
    switch (encoding)
    {
    case ZYDIS_OPERAND_ENCODING_RM_CD2:
        evexCD8Scale = 2;
        break;
    case ZYDIS_OPERAND_ENCODING_RM_CD4:
        evexCD8Scale = 4;
        break;
    case ZYDIS_OPERAND_ENCODING_RM_CD8:
        evexCD8Scale = 8;
        break;
    case ZYDIS_OPERAND_ENCODING_RM_CD16:
        evexCD8Scale = 16;
        break;
    case ZYDIS_OPERAND_ENCODING_RM_CD32:
        evexCD8Scale = 32;
        break;
    case ZYDIS_OPERAND_ENCODING_RM_CD64:
        evexCD8Scale = 64;
        break;
    default:
        break;
    };
    ZydisRegister vsibBaseRegister = ZYDIS_REGISTER_NONE;
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_MEM:
        operand->size = 0;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM8:
        operand->size = 8;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM16:
        operand->size = 16;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST2:
        info->avx.broadcast = ZYDIS_AVX_BCSTMODE_2;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST4:
        if (info->avx.broadcast == ZYDIS_AVX_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX_BCSTMODE_4;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST8:
        if (info->avx.broadcast == ZYDIS_AVX_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX_BCSTMODE_8;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST16:
        if (info->avx.broadcast == ZYDIS_AVX_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX_BCSTMODE_16;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM32:
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST2:
        info->avx.broadcast = ZYDIS_AVX_BCSTMODE_2;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST4:
        if (info->avx.broadcast == ZYDIS_AVX_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX_BCSTMODE_4;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST8:
        if (info->avx.broadcast == ZYDIS_AVX_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX_BCSTMODE_8;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST16:
        if (info->avx.broadcast == ZYDIS_AVX_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX_BCSTMODE_16;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM64:
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM80:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 80;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE);
    case ZYDIS_SEM_OPERAND_TYPE_MEM112:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 112;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE);
    case ZYDIS_SEM_OPERAND_TYPE_MEM128:
        operand->size = 128;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM224:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 224;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE);
    case ZYDIS_SEM_OPERAND_TYPE_MEM256:
        operand->size = 256;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM512:
        operand->size = 512;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_M1616:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 32;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE);
    case ZYDIS_SEM_OPERAND_TYPE_M1632:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 48;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE);
    case ZYDIS_SEM_OPERAND_TYPE_M1664:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 80;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE);
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBX:
        vsibBaseRegister = ZYDIS_REGISTER_XMM0;
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBY:
        vsibBaseRegister = ZYDIS_REGISTER_YMM0;
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBZ:
        vsibBaseRegister = ZYDIS_REGISTER_ZMM0;
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBX:
        vsibBaseRegister = ZYDIS_REGISTER_XMM0;
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBY:
        vsibBaseRegister = ZYDIS_REGISTER_YMM0;
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBZ:
        vsibBaseRegister = ZYDIS_REGISTER_ZMM0;
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGISTERCLASS_NONE));
        break;
    default:
        break;
    }
    if (evexCD8Scale)
    {
        ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
        if (operand->mem.disp.dataSize == 8)
        {
            operand->mem.disp.value.sdword *= evexCD8Scale;
        }
    }
    if (vsibBaseRegister)
    {
        if (info->details.modrm.rm != 0x04)
        {
            info->flags |= ZYDIS_INSTRUCTION_ERROR_INVALID_VSIB;
            return ZYDIS_STATUS_DECODER_INVALID_VSIB;
        }
        switch (operand->mem.addressSize)
        {
        case 16:
            info->flags |= ZYDIS_INSTRUCTION_ERROR_INVALID_VSIB;
            return ZYDIS_STATUS_DECODER_INVALID_VSIB;
        case 32:
            operand->mem.index = operand->mem.index - ZYDIS_REGISTER_EAX + vsibBaseRegister;
            break;
        case 64:
            operand->mem.index = operand->mem.index - ZYDIS_REGISTER_RAX + vsibBaseRegister;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        return ZYDIS_STATUS_DECODER_SUCCESS;
    }

    // Immediate operands
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_FIXED1:
        operand->type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
        operand->size = 8;
        operand->imm.isSigned = true;
        operand->imm.value.ubyte = 1;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_REL8:
        info->flags |= ZYDIS_INSTRUCTION_RELATIVE;
        operand->imm.isRelative = true;
    case ZYDIS_SEM_OPERAND_TYPE_IMM8:
        operand->size = 8;
        operand->imm.isSigned = true;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_IMM8U:
        operand->size = 8;
        operand->imm.isSigned = false;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_REL16:
        info->flags |= ZYDIS_INSTRUCTION_RELATIVE;
        operand->imm.isRelative = true;
    case ZYDIS_SEM_OPERAND_TYPE_IMM16:
        operand->size = 16;
        operand->imm.isSigned = true;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_REL32:
        info->flags |= ZYDIS_INSTRUCTION_RELATIVE;
        operand->imm.isRelative = true;
    case ZYDIS_SEM_OPERAND_TYPE_IMM32:
        operand->size = 32;
        operand->imm.isSigned = true;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_REL64:
        info->flags |= ZYDIS_INSTRUCTION_RELATIVE;
        operand->imm.isRelative = true;
    case ZYDIS_SEM_OPERAND_TYPE_IMM64:
        operand->size = 64;
        operand->imm.isSigned = true;
        break;
    default:
        break;
    }
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_REL8:
    case ZYDIS_SEM_OPERAND_TYPE_IMM8:
    case ZYDIS_SEM_OPERAND_TYPE_IMM8U:
    case ZYDIS_SEM_OPERAND_TYPE_REL16:
    case ZYDIS_SEM_OPERAND_TYPE_IMM16:
    case ZYDIS_SEM_OPERAND_TYPE_REL32:
    case ZYDIS_SEM_OPERAND_TYPE_IMM32:
    case ZYDIS_SEM_OPERAND_TYPE_REL64:
    case ZYDIS_SEM_OPERAND_TYPE_IMM64:
        switch (encoding)
        {
        case ZYDIS_OPERAND_ENCODING_IMM8_LO:
            ZYDIS_CHECK(
                ZydisDecodeOperandImmediate(decoder, info, operand, 8, operand->imm.isSigned));
            operand->imm.value.ubyte &= 0x0F;
            break;
        case ZYDIS_OPERAND_ENCODING_IMM8:
            return ZydisDecodeOperandImmediate(decoder, info, operand, 8, operand->imm.isSigned);
        case ZYDIS_OPERAND_ENCODING_IMM16:
            return ZydisDecodeOperandImmediate(decoder, info, operand, 16, operand->imm.isSigned);
        case ZYDIS_OPERAND_ENCODING_IMM32:
            return ZydisDecodeOperandImmediate(decoder, info, operand, 32, operand->imm.isSigned);
        case ZYDIS_OPERAND_ENCODING_IMM64:
            return ZydisDecodeOperandImmediate(decoder, info, operand, 64, operand->imm.isSigned);
        default:
            ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_SEM_OPERAND_TYPE_PTR1616:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, false));
        operand->ptr.offset = operand->imm.value.uword;
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, false));
        operand->ptr.segment = operand->imm.value.uword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        operand->type = ZYDIS_OPERAND_TYPE_POINTER;
        operand->size = 32;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_PTR1632:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 32, false));
        operand->ptr.offset = operand->imm.value.udword;
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, false));
        operand->ptr.segment = operand->imm.value.uword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        operand->type = ZYDIS_OPERAND_TYPE_POINTER;
        operand->size = 48;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_PTR1664:
        // TODO: ?
        assert(0);
        return ZYDIS_STATUS_DECODER_SUCCESS;
    default:
        break;
    }

    // Moffs
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_MOFFS16:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, false));
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->size = 16;
        operand->mem.disp.dataSize = 16;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->mem.disp.value.sword = operand->imm.value.sword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_MOFFS32:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 32, false));
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->size = 32;
        operand->mem.disp.dataSize = 32;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->mem.disp.value.sdword = operand->imm.value.sdword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_MOFFS64:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 64, false));
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->size = 64;
        operand->mem.disp.dataSize = 64;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->mem.disp.value.sqword = operand->imm.value.sqword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    default:
        break;
    }

    // SrcIdx and DstIdx operands
    uint8_t srcidx = 0;
    uint8_t dstidx = 0;
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_SRCIDX8:
        srcidx = 8;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_SRCIDX16:
        srcidx = 16;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_SRCIDX32:
        srcidx = 32;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_SRCIDX64:
        srcidx = 64;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_DSTIDX8:
        dstidx = 8;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_DSTIDX16:
        dstidx = 16;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_DSTIDX32:
        dstidx = 32;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_DSTIDX64:
        dstidx = 64;
        break;
    default:
        break;
    }   
    if (srcidx || dstidx)
    {
        info->prefixes |= ZYDIS_PREFIX_ACCEPTS_ADDRESSSIZE;
        switch (decoder->disassemblerMode)
        {
        case ZYDIS_DISASSEMBLER_MODE_16BIT:
            operand->mem.addressSize = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 32 : 16;
            break;
        case ZYDIS_DISASSEMBLER_MODE_32BIT:
            operand->mem.addressSize = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 16 : 32;
            break;
        case ZYDIS_DISASSEMBLER_MODE_64BIT:
            operand->mem.addressSize = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 32 : 64;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        registerClass = ZYDIS_REGISTERCLASS_NONE;
        switch (operand->mem.addressSize)
        {
        case 16:
            registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE16;
            break;
        case 32:
            registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE32;
            break;
        case 64:
            registerClass = ZYDIS_REGISTERCLASS_GENERAL_PURPOSE64;
            break;
        default:
            ZYDIS_UNREACHABLE;
        } 
        if (srcidx)
        {   
            ZYDIS_CHECK(ZydisDecodeOperandRegister(info, operand, registerClass, 6));
            operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
            operand->size = srcidx;
            operand->mem.segment = ZYDIS_REGISTER_DS;
            operand->mem.base = operand->reg;
            operand->reg = ZYDIS_REGISTER_NONE; 
            return ZYDIS_STATUS_DECODER_SUCCESS;
        }
        if (dstidx)
        {   
            ZYDIS_CHECK(ZydisDecodeOperandRegister(info, operand, registerClass, 7));
            operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
            operand->size = dstidx;
            operand->mem.base = operand->reg;
            operand->mem.segment = ZYDIS_REGISTER_ES;
            operand->reg = ZYDIS_REGISTER_NONE;
            return ZYDIS_STATUS_DECODER_SUCCESS;
        }
    }

    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/**
 * @brief   Decodes all instruction-operands.
 *
 * @param   decoder     A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   definition  A pointer to the @c ZydisInstructionDefinition struct.
 *
 * @return  A zydis decoder status code.
 */
static ZydisDecoderStatus ZydisDecodeOperands(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, const ZydisInstructionDefinition* definition)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(definition);
    ZYDIS_ASSERT(definition->operandCount <= 6);

    info->operandCount = definition->operandCount;
    for (int i = 0; i < definition->operandCount; ++i)
    {
        ZydisSemanticOperandType type = definition->operands[i].type;
        if (type == ZYDIS_SEM_OPERAND_TYPE_UNUSED)
        {
            break;
        }
        ZydisInstructionEncoding encoding = definition->operands[i].encoding;
        ZydisDecoderStatus status = 
            ZydisDecodeOperand(decoder, info, &info->operand[i], type, encoding);
        info->operand[i].encoding = encoding;
        info->operand[i].access = definition->operands[i].access;
        if (status != ZYDIS_STATUS_DECODER_SUCCESS)
        {
            info->flags |= ZYDIS_INSTRUCTION_ERROR_OPERANDS;
            return status;
        }
        // Adjust segment register for memory operands
        if (info->operand[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            if (info->prefixes & ZYDIS_PREFIX_SEGMENT_CS)
            {
                info->operand[i].mem.segment = ZYDIS_REGISTER_CS;    
            } else
            if (info->prefixes & ZYDIS_PREFIX_SEGMENT_SS)
            {
                info->operand[i].mem.segment = ZYDIS_REGISTER_SS;    
            } else
            if (info->prefixes & ZYDIS_PREFIX_SEGMENT_DS)
            {
                info->operand[i].mem.segment = ZYDIS_REGISTER_DS;    
            } else
            if (info->prefixes & ZYDIS_PREFIX_SEGMENT_ES)
            {
                info->operand[i].mem.segment = ZYDIS_REGISTER_ES;    
            } else
            if (info->prefixes & ZYDIS_PREFIX_SEGMENT_FS)
            {
                info->operand[i].mem.segment = ZYDIS_REGISTER_FS;    
            } else
            if (info->prefixes & ZYDIS_PREFIX_SEGMENT_GS)
            {
                info->operand[i].mem.segment = ZYDIS_REGISTER_GS;    
            } else
            {
                if ((info->operand[i].mem.base == ZYDIS_REGISTER_RSP) ||
                    (info->operand[i].mem.base == ZYDIS_REGISTER_RBP) || 
                    (info->operand[i].mem.base == ZYDIS_REGISTER_ESP) ||
                    (info->operand[i].mem.base == ZYDIS_REGISTER_EBP) ||
                    (info->operand[i].mem.base == ZYDIS_REGISTER_SP)  ||
                    (info->operand[i].mem.base == ZYDIS_REGISTER_BP))
                {
                    info->operand[i].mem.segment = ZYDIS_REGISTER_SS;
                } else
                {
                    info->operand[i].mem.segment = ZYDIS_REGISTER_DS;
                }
            }
        }
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

static void ZydisFinalizeInstructionInfo(ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    // TODO: Encode all these things in the instruction definition

    // Adjust prefix flags
    switch (info->mnemonic)
    {
    case ZYDIS_MNEMONIC_ADD:
    case ZYDIS_MNEMONIC_ADC:
    case ZYDIS_MNEMONIC_AND:
    case ZYDIS_MNEMONIC_BTC:
    case ZYDIS_MNEMONIC_BTR:
    case ZYDIS_MNEMONIC_BTS:
    case ZYDIS_MNEMONIC_CMPXCHG:
    case ZYDIS_MNEMONIC_CMPXCHG8B:
    case ZYDIS_MNEMONIC_CMPXCHG16B:
    case ZYDIS_MNEMONIC_DEC:
    case ZYDIS_MNEMONIC_INC:
    case ZYDIS_MNEMONIC_NEG:
    case ZYDIS_MNEMONIC_NOT:
    case ZYDIS_MNEMONIC_OR:
    case ZYDIS_MNEMONIC_SBB:
    case ZYDIS_MNEMONIC_SUB:
    case ZYDIS_MNEMONIC_XOR:
    case ZYDIS_MNEMONIC_XADD:
    case ZYDIS_MNEMONIC_XCHG:
        if (info->operand[0].type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            info->prefixes |= ZYDIS_PREFIX_ACCEPTS_LOCK;
        }
        break;
    case ZYDIS_MNEMONIC_MOVSB:
    case ZYDIS_MNEMONIC_MOVSW:
    case ZYDIS_MNEMONIC_MOVSD:
    case ZYDIS_MNEMONIC_MOVSQ:
    case ZYDIS_MNEMONIC_CMPSB:
    case ZYDIS_MNEMONIC_CMPSW:
    case ZYDIS_MNEMONIC_CMPSD:
    case ZYDIS_MNEMONIC_CMPSQ:
    case ZYDIS_MNEMONIC_SCASB:
    case ZYDIS_MNEMONIC_SCASW:
    case ZYDIS_MNEMONIC_SCASD:
    case ZYDIS_MNEMONIC_SCASQ:
    case ZYDIS_MNEMONIC_LODSB:
    case ZYDIS_MNEMONIC_LODSW:
    case ZYDIS_MNEMONIC_LODSD:
    case ZYDIS_MNEMONIC_LODSQ:
    case ZYDIS_MNEMONIC_STOSB:
    case ZYDIS_MNEMONIC_STOSW:
    case ZYDIS_MNEMONIC_STOSD:
    case ZYDIS_MNEMONIC_STOSQ:
    case ZYDIS_MNEMONIC_INSB:
    case ZYDIS_MNEMONIC_INSW:
    case ZYDIS_MNEMONIC_INSD:
    case ZYDIS_MNEMONIC_OUTSB:
    case ZYDIS_MNEMONIC_OUTSW:
    case ZYDIS_MNEMONIC_OUTSD:
        info->prefixes |= ZYDIS_PREFIX_ACCEPTS_REP | ZYDIS_PREFIX_ACCEPTS_REPNE;
        break;  
    case ZYDIS_MNEMONIC_JO:
    case ZYDIS_MNEMONIC_JNO:
    case ZYDIS_MNEMONIC_JS:
    case ZYDIS_MNEMONIC_JNS:
    case ZYDIS_MNEMONIC_JE:
    case ZYDIS_MNEMONIC_JNE:
    case ZYDIS_MNEMONIC_JB:
    case ZYDIS_MNEMONIC_JAE:
    case ZYDIS_MNEMONIC_JBE:
    case ZYDIS_MNEMONIC_JA:
    case ZYDIS_MNEMONIC_JL:
    case ZYDIS_MNEMONIC_JGE:
    case ZYDIS_MNEMONIC_JLE:
    case ZYDIS_MNEMONIC_JG:
    case ZYDIS_MNEMONIC_JP:
    case ZYDIS_MNEMONIC_JNP:
    case ZYDIS_MNEMONIC_JCXZ:
    case ZYDIS_MNEMONIC_JECXZ:
    case ZYDIS_MNEMONIC_JRCXZ:
        if (info->prefixes & ZYDIS_PREFIX_SEGMENT_CS)
        {
            info->prefixes &= ~ZYDIS_PREFIX_SEGMENT_CS;
            info->prefixes |= ZYDIS_PREFIX_BRANCH_NOT_TAKEN;
        } else
        if (info->prefixes & ZYDIS_PREFIX_SEGMENT_DS)
        {
            info->prefixes &= ~ZYDIS_PREFIX_SEGMENT_DS;
            info->prefixes |= ZYDIS_PREFIX_BRANCH_TAKEN;    
        }
        break;
    default:
        break;
    }
    if ((info->prefixes & ZYDIS_PREFIX_ACCEPTS_LOCK) && 
        ((info->prefixes & ZYDIS_PREFIX_REP) || (info->prefixes & ZYDIS_PREFIX_REPNE)))
    {
        if (info->mnemonic != ZYDIS_MNEMONIC_CMPXCHG16B)
        {
            if ((info->prefixes & ZYDIS_PREFIX_LOCK) || (info->mnemonic == ZYDIS_MNEMONIC_XCHG))
            {
                if (info->prefixes & ZYDIS_PREFIX_REPNE)
                {
                    info->prefixes &= ~ZYDIS_PREFIX_REPNE;
                    info->prefixes |= ZYDIS_PREFIX_XACQUIRE;    
                } 
                {
                    info->prefixes &= ~ZYDIS_PREFIX_REP;
                    info->prefixes |= ZYDIS_PREFIX_XRELEASE;    
                }    
            } else
            if ((info->mnemonic == ZYDIS_MNEMONIC_MOV) && ((info->opcode == 0x88) || 
                (info->opcode == 0x89) || (info->opcode == 0xC6) || (info->opcode == 0xC7)))
            {
                if (info->prefixes & ZYDIS_PREFIX_REP)
                {
                    info->prefixes &= ~ZYDIS_PREFIX_REP;
                    info->prefixes |= ZYDIS_PREFIX_XRELEASE;    
                }   
            }
        }
    }

    // Adjust instruction mnemonics
    if (info->mnemonic == ZYDIS_MNEMONIC_XCHG)
    {
        if (((info->operand[0].reg == ZYDIS_REGISTER_RAX) && 
            (info->operand[1].reg == ZYDIS_REGISTER_RAX)) || 
            ((info->operand[0].reg == ZYDIS_REGISTER_EAX) && 
            (info->operand[1].reg == ZYDIS_REGISTER_EAX)) ||
            ((info->operand[0].reg == ZYDIS_REGISTER_AX) && 
            (info->operand[1].reg == ZYDIS_REGISTER_AX)))
        {
            info->mnemonic = ZYDIS_MNEMONIC_NOP; 
            info->operand[0].type = ZYDIS_OPERAND_TYPE_UNUSED;
            info->operand[1].type = ZYDIS_OPERAND_TYPE_UNUSED;
        }
    }
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisDecoderStatus ZydisNodeHandlerOpcode(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    // Handle possible encoding-prefix and opcode-map changes
    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &info->opcode));
        switch (info->opcodeMap)
        {
        case ZYDIS_OPCODE_MAP_DEFAULT:
            switch (info->opcode)
            {
            case 0x0F:
                info->opcodeMap = ZYDIS_OPCODE_MAP_0F;
                break;
            case 0xC4:
            case 0xC5:
            case 0x62:
            {
                uint8_t nextInput;
                ZYDIS_CHECK(ZydisInputPeek(decoder, info, &nextInput)); 
                if ((decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ||
                    ((nextInput & 0xF0) >= 0xC0))
                {
                    if (info->prefixes & ZYDIS_PREFIX_REX)
                    {
                        info->flags |= ZYDIS_INSTRUCTION_ERROR_ILLEGAL_REX;
                        return ZYDIS_STATUS_DECODER_ILLEGAL_REX;
                    }
                    uint8_t prefixBytes[3];
                    switch (info->opcode)
                    {
                    case 0xC4:
                        // Read additional 3-byte vex-prefix data
                        ZYDIS_ASSERT(!info->details.vex.isDecoded);
                        ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[0]));
                        ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[1]));
                        break;
                    case 0xC5:
                        // Read additional 2-byte vex-prefix data
                        ZYDIS_ASSERT(!info->details.vex.isDecoded);
                        ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[0]));
                        break;
                    case 0x62:
                        // Read additional evex-prefix data
                        ZYDIS_ASSERT(!info->details.evex.isDecoded);
                        ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[0]));
                        ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[1]));
                        ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[2]));
                        break;
                    default:
                        ZYDIS_UNREACHABLE;
                    }
                    switch (info->opcode)
                    {
                    case 0xC4:
                    case 0xC5:
                        // Decode vex-prefix
                        info->encoding = ZYDIS_INSTRUCTION_ENCODING_VEX;
                        info->prefixes |= ZYDIS_PREFIX_VEX;
                        if (!ZydisDecodeVexPrefix(info->opcode, prefixBytes[0], prefixBytes[1], 
                            info))
                        {
                            info->flags |= ZYDIS_INSTRUCTION_ERROR_MALFORMED_VEX;
                            return ZYDIS_STATUS_DECODER_MALFORMED_VEX_PREFIX;
                        }
                        info->opcodeMap = info->details.vex.m_mmmm;
                        break;
                    case 0x62:
                        // Decode evex-prefix
                        info->encoding = ZYDIS_INSTRUCTION_ENCODING_EVEX;
                        info->prefixes |= ZYDIS_PREFIX_EVEX;
                        if (!ZydisDecodeEvexPrefix(prefixBytes[0], prefixBytes[1], prefixBytes[2], 
                            info))
                        {
                            info->flags |= ZYDIS_INSTRUCTION_ERROR_MALFORMED_EVEX;
                            return ZYDIS_STATUS_DECODER_MALFORMED_EVEX_PREFIX;
                        }
                        info->opcodeMap = info->details.evex.mm;
                        break;
                    default:
                        ZYDIS_UNREACHABLE;
                    }
                }
                break;
            } 
            case 0x8F:
            {
                uint8_t nextInput;
                ZYDIS_CHECK(ZydisInputPeek(decoder, info, &nextInput)); 
                if (((nextInput >> 0) & 0x1F) >= 8)
                {
                    if (info->prefixes & ZYDIS_PREFIX_REX)
                    {
                        info->flags |= ZYDIS_INSTRUCTION_ERROR_ILLEGAL_REX;
                        return ZYDIS_STATUS_DECODER_ILLEGAL_REX;
                    }
                    uint8_t prefixBytes[2];
                    // Read additional xop-prefix data
                    ZYDIS_ASSERT(!info->details.xop.isDecoded);
                    ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[0]));
                    ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[1]));
                    // Decode xop-prefix
                    info->encoding = ZYDIS_INSTRUCTION_ENCODING_XOP;
                    info->prefixes |= ZYDIS_PREFIX_XOP;
                    if (!ZydisDecodeXopPrefix(prefixBytes[0], prefixBytes[1], info))
                    {
                        info->flags |= ZYDIS_INSTRUCTION_ERROR_MALFORMED_XOP;
                        return ZYDIS_STATUS_DECODER_MALFORMED_XOP_PREFIX;
                    }
                    info->opcodeMap = ZYDIS_OPCODE_MAP_XOP8 + info->details.xop.m_mmmm - 0x08;
                }
                break;
            }
            default:
                break;
            }
            break;
        case ZYDIS_OPCODE_MAP_0F:
            switch (info->opcode)
            {
            case 0x0F:
                info->encoding = ZYDIS_INSTRUCTION_ENCODING_3DNOW;
                info->opcodeMap = ZYDIS_OPCODE_MAP_DEFAULT;
                break;
            case 0x38:
                info->opcodeMap = ZYDIS_OPCODE_MAP_0F38;
                break;
            case 0x3A:
                info->opcodeMap = ZYDIS_OPCODE_MAP_0F3A;
                break;
            default:
                break;
            }
            break;
        case ZYDIS_OPCODE_MAP_0F38:
        case ZYDIS_OPCODE_MAP_0F3A:
        case ZYDIS_OPCODE_MAP_XOP8:
        case ZYDIS_OPCODE_MAP_XOP9:
        case ZYDIS_OPCODE_MAP_XOPA:
            // Nothing to do here
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        // All 3dnow (0x0F 0x0F) instructions are using the same operand encoding. We just 
        // decode a random (pi2fw) instruction and extract the actual opcode later.
        *index = 0x0C;
        return ZYDIS_STATUS_DECODER_SUCCESS;
    default:
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &info->opcode));
        break;
    }

    *index = info->opcode; 
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerXop(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        *index = 0;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYDIS_ASSERT(info->details.xop.isDecoded);
        *index = (info->details.xop.m_mmmm - 0x08) + 1;
        break;
    default:
        ZYDIS_UNREACHABLE;
    } 
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerMode(ZydisInstructionDecoder* decoder, 
    uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(index);

    *index = (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ? 0 : 1;
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerVex(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        *index = 0;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYDIS_ASSERT(info->details.vex.isDecoded);
        *index = info->details.vex.m_mmmm + (info->details.vex.pp << 2);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        *index = info->details.evex.mm + (info->details.evex.pp << 2);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerMandatoryPrefix(ZydisInstructionInfo* info, 
    uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (info->prefixes & ZYDIS_PREFIX_REP)
    {
        *index = 2;    
        info->prefixes &= ~ ZYDIS_PREFIX_REP; // TODO: don't remove but mark as mandatory
    } else if (info->prefixes & ZYDIS_PREFIX_REPNE)
    {
        *index = 3;
        info->prefixes &= ~ ZYDIS_PREFIX_REPNE; // TODO: don't remove but mark as mandatory
    } else if (info->prefixes & ZYDIS_PREFIX_OPERANDSIZE)
    {
        *index = 1;
        info->prefixes &= ~ ZYDIS_PREFIX_OPERANDSIZE; // TODO: don't remove but mark as mandatory
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerModrmMod(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &modrmByte));
        ZydisDecodeModrm(modrmByte, info);               
    }
    *index = (info->details.modrm.mod == 0x3) ? 1 : 0;
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerModrmReg(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &modrmByte));
        ZydisDecodeModrm(modrmByte, info);               
    }
    *index = info->details.modrm.reg;
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerModrmRm(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &modrmByte));
        ZydisDecodeModrm(modrmByte, info);                
    }
    *index = info->details.modrm.rm;
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerOperandSize(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    info->prefixes |= ZYDIS_PREFIX_ACCEPTS_OPERANDSIZE;

    switch (decoder->disassemblerMode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
        *index = (info->prefixes & ZYDIS_PREFIX_OPERANDSIZE) ? 1 : 0;
        break;
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        *index = (info->prefixes & ZYDIS_PREFIX_OPERANDSIZE) ? 0 : 1;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerAddressSize(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    info->prefixes |= ZYDIS_PREFIX_ACCEPTS_ADDRESSSIZE;

    switch (decoder->disassemblerMode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
        *index = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 1 : 0;
        break;
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
        *index = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 0 : 1;
        break;
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        *index = (info->prefixes & ZYDIS_PREFIX_ADDRESSSIZE) ? 1 : 2;
        break;
    default: 
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerRexW(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        // nothing to do here       
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYDIS_ASSERT(info->details.vex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYDIS_ASSERT(info->details.xop.isDecoded);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    *index = info->details.internal.w;
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerVexL(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYDIS_ASSERT(info->details.vex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYDIS_ASSERT(info->details.xop.isDecoded);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    *index = info->details.internal.l;
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

static ZydisDecoderStatus ZydisNodeHandlerEvexL2(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = info->details.evex.l2;
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerEvexB(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = info->details.evex.b0;
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerEvexK(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = (info->details.evex.aaa == 0) ? 0 : 1;
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

static ZydisDecoderStatus ZydisNodeHandlerEvexZ(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = info->details.evex.z;
    return ZYDIS_STATUS_DECODER_SUCCESS;   
}

/**
 * @brief   Uses the instruction-table to decode the bytestream until an instruction-definition
 *          is found.
 *
 * @param   decoder A pointer to the instruction decoder instance.
 * @param   info    A pointer to the instruction-info struct.
 *
 * @return  A zydis decoder status code.
 */
static ZydisDecoderStatus ZydisDecodeOpcode(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);

    // Iterate through the instruction table
    ZydisInstructionTableNode node = ZydisInstructionTableGetRootNode();
    ZydisInstructionTableNodeType nodeType;
    do
    {
        nodeType = ZydisInstructionTableGetNodeType(node);
        uint16_t index = 0;
        ZydisDecoderStatus status = 0;
        switch (nodeType)
        {
        case ZYDIS_NODETYPE_INVALID:
        {
            info->flags |= ZYDIS_INSTRUCTION_ERROR_INVALID;
            return ZYDIS_STATUS_DECODER_INVALID_INSTRUCTION;
        }
        case ZYDIS_NODETYPE_DEFINITION_0OP:
        case ZYDIS_NODETYPE_DEFINITION_1OP:
        case ZYDIS_NODETYPE_DEFINITION_2OP:
        case ZYDIS_NODETYPE_DEFINITION_3OP:
        case ZYDIS_NODETYPE_DEFINITION_4OP:
        case ZYDIS_NODETYPE_DEFINITION_5OP:
        {   
            const ZydisInstructionDefinition definition = ZydisInstructionDefinitionByNode(node);
            //ZYDIS_ASSERT(definition); // TODO: Pointer?
            info->mnemonic = definition.mnemonic;

            if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW)
            {
                // Save input-buffer state and decode dummy operands
                uint8_t bufferPosRead = decoder->buffer.posRead;
                uint8_t length = info->length;
                ZYDIS_CHECK(ZydisDecodeOperands(decoder, info, &definition)); // TODO: Reference?
                // Read actual 3dnow opcode
                ZYDIS_CHECK(ZydisInputNext(decoder, info, &info->opcode));
                // Restore input-buffer state
                if (decoder->buffer.posWrite >= bufferPosRead)
                {
                    decoder->buffer.count = decoder->buffer.posWrite - bufferPosRead;
                } else
                {
                    decoder->buffer.count = 
                        decoder->buffer.posWrite + (sizeof(decoder->buffer.data) - bufferPosRead);   
                }
                decoder->buffer.posRead = bufferPosRead;
                info->length = length;
                node = ZydisInstructionTableGetRootNode();
                node = ZydisInstructionTableGetChildNode(node, 0x0F);
                node = ZydisInstructionTableGetChildNode(node, 0x0F);
                node = ZydisInstructionTableGetChildNode(node, info->opcode);
                if (ZydisInstructionTableGetNodeType(node) == ZYDIS_NODETYPE_INVALID)
                {
                    info->flags |= ZYDIS_INSTRUCTION_ERROR_INVALID;
                    return ZYDIS_STATUS_DECODER_INVALID_INSTRUCTION;        
                }
                node = ZydisInstructionTableGetChildNode(node, 
                    (info->details.modrm.mod == 0x3) ? 1 : 0);
                // Decode actual operands and fix the instruction-info               
                ZydisInstructionDefinition definition2 = ZydisInstructionDefinitionByNode(node);
                //ZYDIS_ASSERT(definition);  // TODO: Pointer
                ZYDIS_CHECK(ZydisDecodeOperands(decoder, info, &definition2)); // TODO: Reference
                info->mnemonic = definition2.mnemonic;
                ZydisFinalizeInstructionInfo(info);  
                return ZydisInputNext(decoder, info, &info->opcode);
            }

            ZYDIS_CHECK(ZydisDecodeOperands(decoder, info, &definition)); // TODO: Reference
            ZydisFinalizeInstructionInfo(info);

            if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX)
            {
                if (definition.hasEvexAAA && info->details.evex.aaa)
                {
                    info->avx.maskRegister = ZYDIS_REGISTER_K0 + info->details.evex.aaa; 
                }
                if (definition.hasEvexZ && info->details.evex.z)
                {
                    info->avx.maskMode = ZYDIS_AVX_MASKMODE_ZERO;
                } else
                {
                    info->avx.maskMode = ZYDIS_AVX_MASKMODE_MERGE;
                }
                switch (definition.evexBFunctionality)
                {
                case ZYDIS_EVEXB_FUNCTIONALITY_BC:
                    break;
                case ZYDIS_EVEXB_FUNCTIONALITY_RC:
                    info->avx.roundingMode = 
                        (((info->details.evex.l2 & 0x01) << 1) | info->details.evex.l) + 1; 
                case ZYDIS_EVEXB_FUNCTIONALITY_SAE:
                    info->avx.sae = true;
                default:
                    info->avx.broadcast = ZYDIS_AVX_BCSTMODE_INVALID;
                }
            }
            return ZYDIS_STATUS_DECODER_SUCCESS;
        }
        case ZYDIS_NODETYPE_FILTER_OPCODE:
            status = ZydisNodeHandlerOpcode(decoder, info, &index);
            break;         
        case ZYDIS_NODETYPE_FILTER_VEX:
            status = ZydisNodeHandlerVex(info, &index);
            break;            
        case ZYDIS_NODETYPE_FILTER_XOP:
            status = ZydisNodeHandlerXop(info, &index);
            break;            
        case ZYDIS_NODETYPE_FILTER_MODE:
            status = ZydisNodeHandlerMode(decoder, &index);
            break;           
        case ZYDIS_NODETYPE_FILTER_MANDATORYPREFIX:
            status = ZydisNodeHandlerMandatoryPrefix(info, &index);
            break;
        case ZYDIS_NODETYPE_FILTER_MODRMMOD:
            status = ZydisNodeHandlerModrmMod(decoder, info, &index);
            break;                                                                                 
        case ZYDIS_NODETYPE_FILTER_MODRMREG:
            status = ZydisNodeHandlerModrmReg(decoder, info, &index);
            break;       
        case ZYDIS_NODETYPE_FILTER_MODRMRM:
            status = ZydisNodeHandlerModrmRm(decoder, info, &index);
            break;          
        case ZYDIS_NODETYPE_FILTER_OPERANDSIZE:
            status = ZydisNodeHandlerOperandSize(decoder, info, &index);
            break;    
        case ZYDIS_NODETYPE_FILTER_ADDRESSSIZE:
            status = ZydisNodeHandlerAddressSize(decoder, info, &index);
            break;    
        case ZYDIS_NODETYPE_FILTER_REXW:
            status = ZydisNodeHandlerRexW(info, &index);
            break;           
        case ZYDIS_NODETYPE_FILTER_VEXL:
            status = ZydisNodeHandlerVexL(info, &index);
            break;           
        case ZYDIS_NODETYPE_FILTER_EVEXL2:
            status = ZydisNodeHandlerEvexL2(info, &index);
            break;         
        case ZYDIS_NODETYPE_FILTER_EVEXB:
            status = ZydisNodeHandlerEvexB(info, &index);
            break;                   
        default:
            ZYDIS_UNREACHABLE;
        }
        ZYDIS_CHECK(status);
        node = ZydisInstructionTableGetChildNode(node, index);
    } while((nodeType != ZYDIS_NODETYPE_INVALID) && 
        (nodeType != ZYDIS_NODETYPE_DEFINITION_0OP) &&
        (nodeType != ZYDIS_NODETYPE_DEFINITION_1OP) && 
        (nodeType != ZYDIS_NODETYPE_DEFINITION_2OP) && 
        (nodeType != ZYDIS_NODETYPE_DEFINITION_3OP) && 
        (nodeType != ZYDIS_NODETYPE_DEFINITION_4OP) && 
        (nodeType != ZYDIS_NODETYPE_DEFINITION_5OP));
    return ZYDIS_STATUS_DECODER_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZydisStatus ZydisDecoderInitInstructionDecoder(ZydisInstructionDecoder* decoder,
    ZydisDisassemblerMode disassemblerMode, ZydisCustomInput* input)
{
    return ZydisDecoderInitInstructionDecoderEx(decoder, disassemblerMode, input, 0);
}

ZydisStatus ZydisDecoderInitInstructionDecoderEx(ZydisInstructionDecoder* decoder,
    ZydisDisassemblerMode disassemblerMode, ZydisCustomInput* input, ZydisDecoderFlags flags)
{
    if (!decoder || (
        (disassemblerMode != ZYDIS_DISASSEMBLER_MODE_16BIT) && 
        (disassemblerMode != ZYDIS_DISASSEMBLER_MODE_32BIT) && 
        (disassemblerMode != ZYDIS_DISASSEMBLER_MODE_64BIT)))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    decoder->disassemblerMode = disassemblerMode;
    decoder->input = input;
    decoder->flags = flags;
    decoder->buffer.count = 0;
    decoder->buffer.posRead = 0; 
    decoder->buffer.posWrite = 0;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisDecoderGetDisassemblerMode(const ZydisInstructionDecoder* decoder, 
    ZydisDisassemblerMode* disassemblerMode)
{
    if (!decoder || !disassemblerMode)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *disassemblerMode = decoder->disassemblerMode;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisDecoderSetDisassemblerMode(ZydisInstructionDecoder* decoder, 
    ZydisDisassemblerMode disassemblerMode)
{
    if (!decoder ||
        ((disassemblerMode != 16) && (disassemblerMode != 32) && (disassemblerMode != 64)))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    decoder->disassemblerMode = disassemblerMode;
    return ZYDIS_STATUS_SUCCESS;    
}

ZydisStatus ZydisDecoderGetDecoderInput(const ZydisInstructionDecoder* decoder,
    ZydisCustomInput** input)
{
    if (!decoder || !input)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *input = decoder->input;
    return ZYDIS_STATUS_SUCCESS;    
}

ZydisStatus ZydisDecoderSetDecoderInput(ZydisInstructionDecoder* decoder,
    ZydisCustomInput* input)
{
    if (!decoder)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    decoder->input = input;
    decoder->buffer.count = 0;
    decoder->buffer.posRead = 0; 
    decoder->buffer.posWrite = 0;
    return ZYDIS_STATUS_SUCCESS;      
}

ZydisStatus ZydisDecoderGetDecoderFlags(const ZydisInstructionDecoder* decoder,
    ZydisDecoderFlags* flags)
{
    if (!decoder || !flags)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *flags = decoder->flags;
    return ZYDIS_STATUS_SUCCESS;    
}

ZydisStatus ZydisDecoderSetDecoderFlags(ZydisInstructionDecoder* decoder, 
    ZydisDecoderFlags flags)
{
    if (!decoder)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    decoder->flags = flags;
    return ZYDIS_STATUS_SUCCESS;     
}

ZydisStatus ZydisDecoderGetInstructionPointer(const ZydisInstructionDecoder* decoder,
    uint64_t* instructionPointer)
{
    if (!decoder || !instructionPointer)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *instructionPointer = decoder->instructionPointer;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisDecoderSetInstructionPointer(ZydisInstructionDecoder* decoder, 
    uint64_t instructionPointer)
{
    if (!decoder)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    decoder->instructionPointer = instructionPointer;
    return ZYDIS_STATUS_SUCCESS; 
}

ZydisStatus ZydisDecoderDecodeNextInstruction(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info)
{
    if (!decoder)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    if (!decoder->input)
    {
        return ZYDIS_STATUS_NO_MORE_DATA;
    }
    
    decoder->imm8initialized = false;

    void* userData[6];
    for (int i = 0; i < 5; ++i)
    {
        userData[i] = info->operand[i].userData;
    }
    userData[5] = info->userData;
    memset(info, 0, sizeof(*info));   
    info->mode = decoder->disassemblerMode;
    info->instrAddress = decoder->instructionPointer;
    for (int i = 0; i < 5; ++i)
    {
        info->operand[i].userData = userData[i];
    }
    info->userData = userData[5];

    uint8_t bufferPosRead = decoder->buffer.posRead;

    ZydisDecoderStatus status = ZydisCollectOptionalPrefixes(decoder, info);
    if (status != ZYDIS_STATUS_DECODER_SUCCESS)
    {
        goto DecodeError;
    }
    status = ZydisDecodeOpcode(decoder, info);
    if (status != ZYDIS_STATUS_DECODER_SUCCESS)
    {
        goto DecodeError;
    }

    decoder->instructionPointer += info->length;
    info->instrPointer = decoder->instructionPointer;

    return ZYDIS_STATUS_SUCCESS;

DecodeError:
{
    uint32_t flags = info->flags;
    uint8_t firstByte = info->data[0];
    uint64_t instrAddress = info->instrAddress;
    memset(info, 0, sizeof(*info));

    if (decoder->buffer.posWrite >= bufferPosRead)
    {
        decoder->buffer.count = decoder->buffer.posWrite - bufferPosRead;
    } else
    {
        decoder->buffer.count = 
            decoder->buffer.posWrite + (sizeof(decoder->buffer.data) - bufferPosRead);   
    }
    decoder->buffer.posRead = bufferPosRead;
    if (status == ZYDIS_STATUS_DECODER_NO_MORE_DATA)
    {       
        return status;
    }
    --decoder->buffer.count;
    ++decoder->buffer.posRead;
    if (decoder->buffer.posRead == sizeof(decoder->buffer.data))
    {
        decoder->buffer.posRead = 0;
    }
  
    ++decoder->instructionPointer;
    info->mode = decoder->disassemblerMode;
    info->flags = flags & ZYDIS_INSTRUCTION_ERROR_MASK;
    info->length = 1;
    info->data[0] = firstByte;
    info->instrAddress = instrAddress;
    info->instrPointer = decoder->instructionPointer;

    if (!decoder->flags & ZYDIS_DECODER_FLAG_SKIP_DATA)
    {
        return ZYDIS_STATUS_INVALID_INSTRUCTION;
    }
}
    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
