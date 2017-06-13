/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

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

#include <string.h>
#include <Zydis/Status.h>
#include <Zydis/Decoder.h>
#include <Zydis/Internal/InstructionTable.h>

/* ============================================================================================== */
/* Internal functions and types                                                                   */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internals structs                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisDecoderContext struct.
 */
typedef struct ZydisDecoderContext_
{
    /**
     * @brief   A pointer to the @c ZydisInstructionDecoder instance.
     */
    ZydisInstructionDecoder* decoder;
    /**
     * @brief   The input buffer.
     */
    const uint8_t* buffer;
    /**
     * @brief   The input buffer length.
     */
    size_t bufferLen;
    /**
     * @brief   Contains the last (significant) segment prefix.
     */
    uint8_t lastSegmentPrefix;
    /**
     * @brief   Contains the prefix that should be traited as the mandatory-prefix, if the current
     *          instruction needs one.
     *          0x66 has precedence over 0xF3/0xF2 and the last 0xF3/0xF2 has precedence over 
     *          previous ones.
     */
    uint8_t mandatoryCandidate;
    /**
     * @brief   Contains the effective operand-size index.
     * 
     * 0 = 16 bit, 1 = 32 bit, 2 = 64 bit
     */
    uint8_t eoszIndex;
    /**
     * @brief   Contains some cached REX/XOP/VEX/EVEX/MVEX values to provide uniform access.
     */
    struct
    {
        uint8_t W;
        uint8_t R;
        uint8_t X;
        uint8_t B;
        uint8_t L;
        uint8_t LL;
        uint8_t R2;
        uint8_t V2;
        uint8_t v_vvvv;
    } cache;
} ZydisDecoderContext;

/* ---------------------------------------------------------------------------------------------- */
/* Input helper functions                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Reads one byte from the current read-position of the input data-source.
 *
 * @param   context A pointer to the @c ZydisDecoderContext instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   value   A pointer to the memory that receives the byte from the input data-source.
 *
 * @return  A zydis status code.
 *          
 * If not empty, the internal buffer of the @c ZydisDecoderContext instance is used as temporary
 * data-source, instead of reading the byte from the actual input data-source.
 * 
 * This function may fail, if the @c ZYDIS_MAX_INSTRUCTION_LENGTH limit got exceeded, or no more   
 * data is available.
 */
static ZydisStatus ZydisInputPeek(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    uint8_t* value)
{ 
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info); 
    ZYDIS_ASSERT(value);

    if (info->length >= ZYDIS_MAX_INSTRUCTION_LENGTH) 
    { 
        return ZYDIS_STATUS_INSTRUCTION_TOO_LONG; 
    } 

    if (context->bufferLen > 0)
    {
        *value = context->buffer[0];
        return ZYDIS_STATUS_SUCCESS;
    }

    return ZYDIS_STATUS_NO_MORE_DATA;    
}

/**
 * @brief   Increases the read-position of the input data-source by one byte.
 *
 * @param   context A pointer to the @c ZydisDecoderContext instance
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 *                  
 * This function is supposed to get called ONLY after a successfull call of @c ZydisInputPeek.
 * 
 * If not empty, the read-position of the @c ZydisDecoderContext instances internal buffer is
 * increased, instead of the actual input data-sources read-position.
 * 
 * This function increases the @c length field of the @c ZydisInstructionInfo struct by one and
 * adds the current byte to the @c data array.
 */
static void ZydisInputSkip(ZydisDecoderContext* context, ZydisInstructionInfo* info)
{ 
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->length < ZYDIS_MAX_INSTRUCTION_LENGTH);

    info->data[info->length++] = context->buffer++[0];
    --context->bufferLen;
}

/**
 * @brief   Reads one byte from the current read-position of the input data-source and increases the
 *          read-position by one byte afterwards.
 *
 * @param   context A pointer to the @c ZydisDecoderContext instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   value   A pointer to the memory that receives the byte from the input data-source.
 *
 * @return  A zydis status code.
 *          
 * This function acts like a subsequent call of @c ZydisInputPeek and @c ZydisInputSkip.
 */
static ZydisStatus ZydisInputNext(ZydisDecoderContext* context, ZydisInstructionInfo* info, 
    uint8_t* value)
{ 
    ZYDIS_ASSERT(context); 
    ZYDIS_ASSERT(info); 
    ZYDIS_ASSERT(value);

    if (info->length >= ZYDIS_MAX_INSTRUCTION_LENGTH) 
    { 
        return ZYDIS_STATUS_INSTRUCTION_TOO_LONG; 
    } 

    if (context->bufferLen > 0)
    {
        *value = context->buffer++[0];
        info->data[info->length++] = *value;
        --context->bufferLen;
        return ZYDIS_STATUS_SUCCESS;
    }

    return ZYDIS_STATUS_NO_MORE_DATA;
}

/* ---------------------------------------------------------------------------------------------- */
/* Decoder functions                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Decodes the REX-prefix.
 *
 * @param   context A pointer to the @c ZydisDecoderContext struct.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   data    The REX byte.
 */
static void ZydisDecodeREX(ZydisDecoderContext* context, ZydisInstructionInfo* info, 
    uint8_t data)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT((data & 0xF0) == 0x40);

    info->attributes |= ZYDIS_ATTRIB_HAS_REX;
    info->details.rex.isDecoded = ZYDIS_TRUE;
    info->details.rex.data[0]   = data;
    info->details.rex.W         = (data >> 3) & 0x01;
    info->details.rex.R         = (data >> 2) & 0x01;
    info->details.rex.X         = (data >> 1) & 0x01;
    info->details.rex.B         = (data >> 0) & 0x01;

    // Update internal fields
    context->cache.W       = info->details.rex.W;
    context->cache.R       = info->details.rex.R;
    context->cache.X       = info->details.rex.X;
    context->cache.B       = info->details.rex.B;
}

/**
 * @brief   Decodes the XOP-prefix.
 *
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   data        The XOP bytes.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeXOP(ZydisDecoderContext* context, ZydisInstructionInfo* info, 
    uint8_t data[3])
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(data[0] == 0x8F);
    ZYDIS_ASSERT(((data[1] >> 0) & 0x1F) >= 8);

    info->attributes |= ZYDIS_ATTRIB_HAS_XOP;
    info->details.xop.isDecoded     = ZYDIS_TRUE;
    info->details.xop.data[0]       = 0x8F;
    info->details.xop.data[1]       = data[1];
    info->details.xop.data[2]       = data[2];
    info->details.xop.R             = (data[1] >> 7) & 0x01;
    info->details.xop.X             = (data[1] >> 6) & 0x01;
    info->details.xop.B             = (data[1] >> 5) & 0x01;
    info->details.xop.m_mmmm        = (data[1] >> 0) & 0x1F;

    if ((info->details.xop.m_mmmm < 0x08) || (info->details.xop.m_mmmm > 0x0A))
    {
        // Invalid according to the AMD documentation
        return ZYDIS_STATUS_INVALID_MAP;
    }

    info->details.xop.W             = (data[2] >> 7) & 0x01;
    info->details.xop.vvvv          = (data[2] >> 3) & 0x0F;
    info->details.xop.L             = (data[2] >> 2) & 0x01;
    info->details.xop.pp            = (data[2] >> 0) & 0x03; 

    // Update internal fields
    context->cache.W           = info->details.xop.W;
    context->cache.R           = 0x01 & ~info->details.xop.R;
    context->cache.X           = 0x01 & ~info->details.xop.X;
    context->cache.B           = 0x01 & ~info->details.xop.B;
    context->cache.L           = info->details.xop.L;
    context->cache.v_vvvv       = (0x0F & ~info->details.xop.vvvv);

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the VEX-prefix.
 *
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   data        The VEX bytes.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeVEX(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    uint8_t data[3])
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT((data[0] == 0xC4) || (data[0] == 0xC5));

    info->attributes |= ZYDIS_ATTRIB_HAS_VEX;
    info->details.vex.isDecoded     = ZYDIS_TRUE;
    info->details.vex.data[0]       = data[0];
    switch (data[0])
    {
    case 0xC4:
        info->details.vex.data[1]   = data[1];
        info->details.vex.data[2]   = data[2];
        info->details.vex.R         = (data[1] >> 7) & 0x01;
        info->details.vex.X         = (data[1] >> 6) & 0x01;
        info->details.vex.B         = (data[1] >> 5) & 0x01;
        info->details.vex.m_mmmm    = (data[1] >> 0) & 0x1F;
        info->details.vex.W         = (data[2] >> 7) & 0x01;
        info->details.vex.vvvv      = (data[2] >> 3) & 0x0F;
        info->details.vex.L         = (data[2] >> 2) & 0x01;
        info->details.vex.pp        = (data[2] >> 0) & 0x03;
        break;
    case 0xC5:
        info->details.vex.data[1]   = data[1];
        info->details.vex.data[2]   = 0;
        info->details.vex.R         = (data[1] >> 7) & 0x01;
        info->details.vex.X         = 1;
        info->details.vex.B         = 1;
        info->details.vex.m_mmmm    = 1;
        info->details.vex.W         = 0;
        info->details.vex.vvvv      = (data[1] >> 3) & 0x0F;
        info->details.vex.L         = (data[1] >> 2) & 0x01;
        info->details.vex.pp        = (data[1] >> 0) & 0x03;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }  

    // TODO: map = 0 is allowed for some newer VEX instructions
    if (/*(info->details.vex.m_mmmm == 0x00) || */(info->details.vex.m_mmmm > 0x03))
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_INVALID_MAP;
    }

    // Update internal fields
    context->cache.W = info->details.vex.W;
    context->cache.R = 0x01 & ~info->details.vex.R;
    context->cache.X = 0x01 & ~info->details.vex.X;
    context->cache.B = 0x01 & ~info->details.vex.B;
    context->cache.L = info->details.vex.L;
    context->cache.v_vvvv = (0x0F & ~info->details.vex.vvvv);

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the EVEX-prefix.
 *
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   data        The EVEX bytes.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeEVEX(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    uint8_t data[4])
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(data[0] == 0x62);

    info->attributes |= ZYDIS_ATTRIB_HAS_EVEX;
    info->details.evex.isDecoded    = ZYDIS_TRUE;
    info->details.evex.data[0]      = 0x62;
    info->details.evex.data[1]      = data[1];
    info->details.evex.data[2]      = data[2];
    info->details.evex.data[3]      = data[3];
    info->details.evex.R            = (data[1] >> 7) & 0x01;
    info->details.evex.X            = (data[1] >> 6) & 0x01;
    info->details.evex.B            = (data[1] >> 5) & 0x01;
    info->details.evex.R2           = (data[1] >> 4) & 0x01;

    if (((data[1] >> 2) & 0x03) != 0x00)
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_MALFORMED_EVEX;
    }

    info->details.evex.mm           = (data[1] >> 0) & 0x03;

    // TODO: Check if map = 0 is allowed for new EVEX instructions

    //if (info->details.evex.mm == 0x00)
    //{
    //    // Invalid according to the intel documentation
    //    return ZYDIS_STATUS_INVALID_MAP;
    //}

    info->details.evex.W            = (data[2] >> 7) & 0x01;
    info->details.evex.vvvv         = (data[2] >> 3) & 0x0F;

    ZYDIS_ASSERT(((data[2] >> 2) & 0x01) == 0x01);

    info->details.evex.pp           = (data[2] >> 0) & 0x03;
    info->details.evex.z            = (data[3] >> 7) & 0x01;
    info->details.evex.L2           = (data[3] >> 6) & 0x01;
    info->details.evex.L            = (data[3] >> 5) & 0x01;
    info->details.evex.b            = (data[3] >> 4) & 0x01;
    info->details.evex.V2           = (data[3] >> 3) & 0x01;
    info->details.evex.aaa          = (data[3] >> 0) & 0x07; 
    
    // Update internal fields
    context->cache.W           = info->details.evex.W;
    context->cache.R           = 0x01 & ~info->details.evex.R;
    context->cache.X           = 0x01 & ~info->details.evex.X;
    context->cache.B           = 0x01 & ~info->details.evex.B;
    context->cache.LL          = (data[3] >> 5) & 0x03;
    context->cache.R2          = 0x01 & ~info->details.evex.R2;
    context->cache.V2          = 0x01 & ~info->details.evex.V2;
    context->cache.v_vvvv       = 
        ((0x01 & ~info->details.evex.V2) << 4) | (0x0F & ~info->details.evex.vvvv); 

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the MVEX-prefix.
 *
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   data        The MVEX bytes.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeMVEX(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    uint8_t data[4])
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(data[0] == 0x62);

    info->attributes |= ZYDIS_ATTRIB_HAS_EVEX;
    info->details.mvex.isDecoded    = ZYDIS_TRUE;
    info->details.mvex.data[0]      = 0x62;
    info->details.mvex.data[1]      = data[1];
    info->details.mvex.data[2]      = data[2];
    info->details.mvex.data[3]      = data[3];
    info->details.mvex.R            = (data[1] >> 7) & 0x01;
    info->details.mvex.X            = (data[1] >> 6) & 0x01;
    info->details.mvex.B            = (data[1] >> 5) & 0x01;
    info->details.mvex.R2           = (data[1] >> 4) & 0x01;
    info->details.mvex.mmmm         = (data[1] >> 0) & 0x0F;

    // TODO: Check if map = 0 is allowed for new MVEX instructions
    if (/*(info->details.mvex.mmmm == 0x00) || */(info->details.mvex.mmmm > 0x03))
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_INVALID_MAP;
    }

    info->details.mvex.W            = (data[2] >> 7) & 0x01;
    info->details.mvex.vvvv         = (data[2] >> 3) & 0x0F;

    ZYDIS_ASSERT(((data[2] >> 2) & 0x01) == 0x00);

    info->details.mvex.pp           = (data[2] >> 0) & 0x03;
    info->details.mvex.E            = (data[3] >> 7) & 0x01;
    info->details.mvex.SSS          = (data[3] >> 4) & 0x07;
    info->details.mvex.V2           = (data[3] >> 3) & 0x01;
    info->details.mvex.kkk          = (data[3] >> 0) & 0x07; 
    
    // Update internal fields
    context->cache.W           = info->details.mvex.W;
    context->cache.R           = 0x01 & ~info->details.mvex.R;
    context->cache.X           = 0x01 & ~info->details.mvex.X;
    context->cache.B           = 0x01 & ~info->details.mvex.B;
    context->cache.R2          = 0x01 & ~info->details.mvex.R2;
    context->cache.V2          = 0x01 & ~info->details.mvex.V2;
    context->cache.v_vvvv       = 
        ((0x01 & ~info->details.mvex.V2) << 4) | (0x0F & ~info->details.mvex.vvvv);

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the ModRM-byte.
 *
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   data    The modrm byte.
 */
static void ZydisDecodeModRM(ZydisInstructionInfo* info, uint8_t data)
{
    ZYDIS_ASSERT(info);

    info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
    info->details.modrm.isDecoded   = ZYDIS_TRUE;
    info->details.modrm.data[0]     = data;
    info->details.modrm.mod         = (data >> 6) & 0x03;
    info->details.modrm.reg         = (data >> 3) & 0x07;
    info->details.modrm.rm          = (data >> 0) & 0x07;
}

/**
 * @brief   Decodes the SIB-byte.
 *
 * @param   info    A pointer to the @c ZydisInstructionInfo struct
 * @param   data    The sib byte.
 */
static void ZydisDecodeSIB(ZydisInstructionInfo* info, uint8_t data)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->details.modrm.isDecoded);
    ZYDIS_ASSERT((info->details.modrm.rm & 0x7) == 4);

    info->attributes |= ZYDIS_ATTRIB_HAS_SIB;
    info->details.sib.isDecoded = ZYDIS_TRUE;
    info->details.sib.data[0]   = data;
    info->details.sib.scale     = (data >> 6) & 0x03;
    info->details.sib.index     = (data >> 3) & 0x07;
    info->details.sib.base      = (data >> 0) & 0x07;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Reads a displacement value.
 * 
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   size        The physical size of the displacement value.
 * 
 * @return  A zydis status code.
 */
static ZydisStatus ZydisReadDisplacement(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    uint8_t size)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->details.disp.dataSize == 0);

    info->details.disp.dataSize = size;
    info->details.disp.dataOffset = info->length;
    switch (size)
    {
    case 8:
    {
        uint8_t value;
        ZYDIS_CHECK(ZydisInputNext(context, info, &value));
        info->details.disp.value.sbyte = (int8_t)value;
        break;
    }
    case 16:
    {
        uint16_t data[2] = { 0, 0 };
        ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[1]));
        ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[0]));
        info->details.disp.value.sword = (data[0] << 8) | data[1];
        break;   
    }
    case 32:
    {
        uint32_t data[4] = { 0, 0, 0, 0 };
        for (int i = ZYDIS_ARRAY_SIZE(data); i > 0; --i)
        {
            ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[i - 1]));    
        }
        info->details.disp.value.sdword = 
            (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        break;
    }
    case 64:
    {
        uint64_t data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int i = sizeof(data) / sizeof(data[0]); i > 0; --i)
        {
            ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[i - 1]));    
        }
        info->details.disp.value.sqword = 
            (data[0] << 56) | (data[1] << 48) | (data[2] << 40) | (data[3] << 32) | 
            (data[4] << 24) | (data[5] << 16) | (data[6] <<  8) | data[7];
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }

    // TODO: Fix endianess on big-endian systems

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Reads an immediate value.
 * 
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   id          The immediate id (either 0 or 1).
 * @param   size        The physical size of the immediate value.
 * @param   isSigned    Signals, if the immediate value is signed.
 * @param   isRelative  Signals, if the immediate value is a relative offset.
 * 
 * @return  A zydis status code.
 */
static ZydisStatus ZydisReadImmediate(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    uint8_t id, uint8_t size, ZydisBool isSigned, ZydisBool isRelative)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT((id == 0) || (id == 1));
    ZYDIS_ASSERT(isSigned || ~isRelative);
    ZYDIS_ASSERT(info->details.imm[id].dataSize == 0);

    info->details.imm[id].dataSize = size;
    info->details.imm[id].dataOffset = info->length;
    info->details.imm[id].isSigned = isSigned;
    info->details.imm[id].isRelative = isRelative;
    switch (size)
    {
    case 8:
    {
        uint8_t value;
        ZYDIS_CHECK(ZydisInputNext(context, info, &value));
        if (isSigned)
        {
            info->details.imm[id].value.sbyte = (int8_t)value;
        } else
        {
            info->details.imm[id].value.ubyte = value;    
        }
        break;
    }
    case 16:
    {
        uint16_t data[2] = { 0, 0 };
        ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[1]));
        ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[0]));
        uint16_t value = (data[0] << 8) | data[1];
        if (isSigned)
        {
            info->details.imm[id].value.sword = (int16_t)value;
        } else
        {
            info->details.imm[id].value.uword = value;    
        }
        break;   
    }
    case 32:
    {
        uint32_t data[4] = { 0, 0, 0, 0 };
        for (int i = ZYDIS_ARRAY_SIZE(data); i > 0; --i)
        {
            ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[i - 1]));    
        }
        uint32_t value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        if (isSigned)
        {
            info->details.imm[id].value.sdword = (int32_t)value;
        } else
        {
            info->details.imm[id].value.udword = value;    
        }
        break;
    }
    case 64:
    {
        uint64_t data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        for (int i = sizeof(data) / sizeof(data[0]); i > 0; --i)
        {
            ZYDIS_CHECK(ZydisInputNext(context, info, (uint8_t*)&data[i - 1]));    
        }
        uint64_t value = 
            (data[0] << 56) | (data[1] << 48) | (data[2] << 40) | (data[3] << 32) | 
            (data[4] << 24) | (data[5] << 16) | (data[6] <<  8) | data[7];
        if (isSigned)
        {
            info->details.imm[id].value.sqword = (int64_t)value;
        } else
        {
            info->details.imm[id].value.uqword = value;    
        }
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }

    // TODO: Fix endianess on big-endian systems

    return ZYDIS_STATUS_SUCCESS;    
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Collects optional instruction prefixes.
 *
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  A zydis status code.
 *         
 * This function sets the corresponding flag for each prefix and automatically decodes the last
 * REX-prefix (if exists).
 */
static ZydisStatus ZydisCollectOptionalPrefixes(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->details.prefixes.count == 0);

    ZydisBool done = ZYDIS_FALSE;
    do
    {
        uint8_t prefixByte;
        ZYDIS_CHECK(ZydisInputPeek(context, info, &prefixByte));
        switch (prefixByte)
        {
        case 0xF0:
            ++info->details.prefixes.hasF0;
            break;
        case 0xF2:
            if (context->mandatoryCandidate != 0x66)
            {
                context->mandatoryCandidate = 0xF2;
            }
            ++info->details.prefixes.hasF2;
            break;
        case 0xF3:
            if (context->mandatoryCandidate != 0x66)
            {
                context->mandatoryCandidate = 0xF3;
            }
            ++info->details.prefixes.hasF3;
            break;
        case 0x2E: 
            ++info->details.prefixes.has2E;
            context->lastSegmentPrefix = 0x2E;
            break;
        case 0x36:
            ++info->details.prefixes.has36;
            context->lastSegmentPrefix = 0x36;
            break;
        case 0x3E: 
            ++info->details.prefixes.has3E;
            context->lastSegmentPrefix = 0x3E;
            break;
        case 0x26: 
            ++info->details.prefixes.has26;
            context->lastSegmentPrefix = 0x26;
            break;
        case 0x64:
            ++info->details.prefixes.has64;
            context->lastSegmentPrefix = 0x64;
            break;
        case 0x65: 
            ++info->details.prefixes.has65;
            context->lastSegmentPrefix = 0x65;
            break;
        case 0x66:
            context->mandatoryCandidate = 0x66;
            ++info->details.prefixes.has66;
            info->attributes |= ZYDIS_ATTRIB_HAS_OPERANDSIZE;
            break;
        case 0x67:
            ++info->details.prefixes.has67;
            info->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
            break;
        default:
            if ((context->decoder->machineMode == ZYDIS_MACHINE_MODE_LONG_64) && 
                (prefixByte & 0xF0) == 0x40)
            {
                info->details.rex.data[0] = prefixByte; 
            } else
            {
                done = ZYDIS_TRUE;
            }
            break;
        }
        if (!done)
        {
            info->details.prefixes.data[info->details.prefixes.count++] = prefixByte;
            ZydisInputSkip(context, info);
        }
    } while (!done);

    if (info->details.rex.data[0])
    {
        ZydisDecodeREX(context, info, info->details.rex.data[0]);
    }

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes optional instruction parts like the ModRM byte, the SIB byte and additional
 *          displacements and/or immediate values.
 *          
 * @param   context         A pointer to the @c ZydisDecoderContext struct.
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   optionalParts   A pointer to the @c ZydisInstructionParts struct.
 * 
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOptionalInstructionParts(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, const ZydisInstructionParts* optionalParts)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(optionalParts);

    if (optionalParts->flags & ZYDIS_INSTRPART_FLAG_HAS_MODRM)
    {
        if (!info->details.modrm.isDecoded)
        {
            uint8_t modrmByte;
            ZYDIS_CHECK(ZydisInputNext(context, info, &modrmByte));
            ZydisDecodeModRM(info, modrmByte);               
        }
        uint8_t hasSIB = 0;
        uint8_t displacementSize = 0;
        switch (info->addressWidth)
        {
        case 16:
            switch (info->details.modrm.mod)
            {
            case 0:
                if (info->details.modrm.rm == 6) 
                {
                    displacementSize = 16;
                }
                break;
            case 1:
                displacementSize = 8;
                break;
            case 2:
                displacementSize = 16;
                break;
            case 3:
                break;
            default:
                ZYDIS_UNREACHABLE;
            }
        case 32:
        case 64:
            hasSIB = (info->details.modrm.mod != 3) && (info->details.modrm.rm == 4);
            switch (info->details.modrm.mod)
            {
            case 0:
                if (info->details.modrm.rm == 5)
                {
                    if (context->decoder->machineMode == 64)
                    {
                        info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
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
            case 3:
                break;
            default:
                ZYDIS_UNREACHABLE;
            }
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        if (hasSIB)
        {
            uint8_t sibByte;
            ZYDIS_CHECK(ZydisInputNext(context, info, &sibByte)); 
            ZydisDecodeSIB(info, sibByte);
            if (info->details.sib.base == 5)
            {
                displacementSize = (info->details.modrm.mod == 1) ? 8 : 32;
            }
        }
        if (displacementSize)
        {
            ZYDIS_CHECK(ZydisReadDisplacement(context, info, displacementSize));
        }    
    }

    if (optionalParts->flags & ZYDIS_INSTRPART_FLAG_HAS_DISP)
    {
        ZYDIS_CHECK(ZydisReadDisplacement(
            context, info, optionalParts->disp.size[context->eoszIndex]));    
    }

    if (optionalParts->flags & ZYDIS_INSTRPART_FLAG_HAS_IMM0)
    {
        if (optionalParts->imm[0].isSigned)
        {
            info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
        }
        ZYDIS_CHECK(ZydisReadImmediate(context, info, 0, 
            optionalParts->imm[0].size[context->eoszIndex], 
            optionalParts->imm[0].isSigned, optionalParts->imm[0].isRelative));    
    }

    if (optionalParts->flags & ZYDIS_INSTRPART_FLAG_HAS_IMM1)
    {
        ZYDIS_ASSERT(!(optionalParts->flags & ZYDIS_INSTRPART_FLAG_HAS_DISP));
        ZYDIS_CHECK(ZydisReadImmediate(context, info, 1, 
            optionalParts->imm[1].size[context->eoszIndex], 
            optionalParts->imm[1].isSigned, optionalParts->imm[1].isRelative));     
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Decodes an register-operand.
 *
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand         A pointer to the @c ZydisOperandInfo struct.
 * @param   registerClass   The register class.
 * @param   registerId      The register id.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperandRegister(ZydisInstructionInfo* info, 
    ZydisOperandInfo* operand, ZydisRegisterClass registerClass, uint8_t registerId)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);

    operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
    if (registerClass == ZYDIS_REGCLASS_GPR8)
    {
        if ((info->attributes & ZYDIS_ATTRIB_HAS_REX) && (registerId >= 4)) 
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
        // TODO: Return critical error, if an invalid register was found
    } else
    {
        operand->reg = ZydisRegisterEncode(registerClass, registerId);
        if (!operand->reg)
        {
            return ZYDIS_STATUS_BAD_REGISTER;
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes a memory operand.
 *
 * @param   context         A pointer to the @c ZydisDecoderContext instance.
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand         A pointer to the @c ZydisOperandInfo struct.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperandMemory(ZydisDecoderContext* context,
    ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);
    ZYDIS_ASSERT(info->details.modrm.isDecoded);
    ZYDIS_ASSERT(info->details.modrm.mod != 3);

    operand->type = ZYDIS_OPERAND_TYPE_MEMORY;

    uint8_t modrm_rm = (context->cache.B << 3) | info->details.modrm.rm;
    uint8_t displacementSize = 0;
    switch (info->addressWidth)
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
        switch (info->details.modrm.mod)
        {
        case 0:
            if (modrm_rm == 6) 
            {
                displacementSize = 16;
                operand->mem.base = ZYDIS_REGISTER_NONE;
            }
            break;
        case 1:
            displacementSize = 8;
            break;
        case 2:
            displacementSize = 16;
            break;
        default:
            ZYDIS_UNREACHABLE;
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
                if (context->decoder->machineMode == 64)
                {
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
            ZYDIS_ASSERT(info->details.sib.isDecoded);
            uint8_t sib_index = (context->cache.X << 3) | info->details.sib.index;
            uint8_t sib_base = (context->cache.B << 3) | info->details.sib.base;
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
            ZYDIS_ASSERT(info->details.sib.isDecoded);
            uint8_t sib_index = (context->cache.X << 3) | info->details.sib.index;
            uint8_t sib_base = (context->cache.B << 3) | info->details.sib.base;
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
        ZYDIS_ASSERT(info->details.disp.dataSize == displacementSize);
        operand->mem.disp.hasDisplacement = ZYDIS_TRUE;
        operand->mem.disp.value.sqword = info->details.disp.value.sqword;
    }
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the instruction operands.
 *          
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   definition  A pointer to the @c ZydisInstructionDefinition struct.
 * 
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperands(ZydisDecoderContext* context, ZydisInstructionInfo* info,
    const ZydisInstructionDefinition* definition)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(definition);

    (void)context;

    uint8_t immId = 0;
    const ZydisOperandDefinition* operand;
    info->operandCount = ZydisGetOperandDefinitions(definition, &operand);
    for (uint8_t i = 0; i < info->operandCount; ++i)
    {
        info->operands[i].id = i;
        info->operands[i].visibility = operand->visibility;
        info->operands[i].action = operand->action;

        // Register operands
        ZydisRegisterClass registerClass = ZYDIS_REGCLASS_INVALID;
        switch (operand->type)
        {
        case ZYDIS_SEMANTIC_OPTYPE_GPR8:
            registerClass = ZYDIS_REGCLASS_GPR8;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_GPR16:
            registerClass = ZYDIS_REGCLASS_GPR16;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_GPR32:
            registerClass = ZYDIS_REGCLASS_GPR32;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_GPR64:
            registerClass = ZYDIS_REGCLASS_GPR64;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_GPR16_32_64:
            registerClass = 
                (info->operandSize == 16) ? ZYDIS_REGCLASS_GPR16 : (
                (info->operandSize == 32) ? ZYDIS_REGCLASS_GPR32 : ZYDIS_REGCLASS_GPR64);
            break; 
        case ZYDIS_SEMANTIC_OPTYPE_GPR32_32_64:
            registerClass = 
                (info->operandSize == 16) ? ZYDIS_REGCLASS_GPR32 : (
                (info->operandSize == 32) ? ZYDIS_REGCLASS_GPR32: ZYDIS_REGCLASS_GPR64);
            break; 
        case ZYDIS_SEMANTIC_OPTYPE_GPR16_32_32:
            registerClass = 
                (info->operandSize == 16) ? ZYDIS_REGCLASS_GPR16 : (
                (info->operandSize == 32) ? ZYDIS_REGCLASS_GPR32 : ZYDIS_REGCLASS_GPR32);
            break;  
        case ZYDIS_SEMANTIC_OPTYPE_FPR:
            registerClass = ZYDIS_REGCLASS_X87;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_MMX:
            registerClass = ZYDIS_REGCLASS_MMX;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_XMM:
            registerClass = ZYDIS_REGCLASS_XMM;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_YMM:
            registerClass = ZYDIS_REGCLASS_YMM;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_ZMM:
            registerClass = ZYDIS_REGCLASS_ZMM;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_BND:
            registerClass = ZYDIS_REGCLASS_BOUND;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_SREG:
            registerClass = ZYDIS_REGCLASS_SEGMENT;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_CR:
            registerClass = ZYDIS_REGCLASS_CONTROL;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_DR:
            registerClass = ZYDIS_REGCLASS_DEBUG;
            break;
        case ZYDIS_SEMANTIC_OPTYPE_MASK:
            registerClass = ZYDIS_REGCLASS_MASK;
            break;
        default:
            break;
        }
        if (registerClass)
        {
            info->operands[i].encoding = operand->op.encoding;
            switch (operand->op.encoding)
            {
            case ZYDIS_OPERAND_ENCODING_MODRM_REG:
                ZYDIS_ASSERT(info->details.modrm.isDecoded);
                ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass, 
                    (context->cache.R2 << 4) | 
                    (context->cache.R  << 3) | info->details.modrm.reg));
                break;
            case ZYDIS_OPERAND_ENCODING_MODRM_RM:
                ZYDIS_ASSERT(info->details.modrm.isDecoded);
                ZYDIS_CHECK(
                    ZydisDecodeOperandRegister(info, &info->operands[i], registerClass,
                        (context->cache.X << 4) | 
                        (context->cache.B << 3) | info->details.modrm.rm));
                break;
            case ZYDIS_OPERAND_ENCODING_OPCODE:
            {
                uint8_t registerId = (info->opcode & 0x0F);
                if (registerId > 7)
                {
                    registerId = registerId - 8;
                }
                ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass, 
                    (context->cache.B << 3) | registerId));
                break;
            }
            case ZYDIS_OPERAND_ENCODING_NDS:
                switch (info->encoding)
                {
                case ZYDIS_INSTRUCTION_ENCODING_XOP:
                    ZYDIS_ASSERT(info->details.xop.isDecoded);
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass, 
                        context->cache.v_vvvv));
                    break;
                case ZYDIS_INSTRUCTION_ENCODING_VEX:
                    ZYDIS_ASSERT(info->details.vex.isDecoded);
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass, 
                        context->cache.v_vvvv));
                    break;
                case ZYDIS_INSTRUCTION_ENCODING_EVEX:
                    ZYDIS_ASSERT(info->details.evex.isDecoded);
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass, 
                        context->cache.v_vvvv));
                    break;
                case ZYDIS_INSTRUCTION_ENCODING_MVEX:
                    ZYDIS_ASSERT(info->details.mvex.isDecoded);
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass, 
                        context->cache.v_vvvv));
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }        
                break;
            case ZYDIS_OPERAND_ENCODING_MASK:
                ZYDIS_ASSERT(registerClass == ZYDIS_REGCLASS_MASK);
                switch (info->encoding)
                {
                case ZYDIS_INSTRUCTION_ENCODING_EVEX:
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass,
                        info->details.evex.aaa));
                    break;
                case ZYDIS_INSTRUCTION_ENCODING_MVEX:
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass,
                        info->details.mvex.kkk));
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_OPERAND_ENCODING_UIMM8_HI:
                switch (context->decoder->machineMode)
                {
                case 32:
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass,
                        (info->details.imm[0].value.ubyte >> 4) & 0x07));
                    break;
                case 64:
                    ZYDIS_CHECK(ZydisDecodeOperandRegister(info, &info->operands[i], registerClass,
                        (info->details.imm[0].value.ubyte >> 4) & 0x0F));
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            default:
                ZYDIS_UNREACHABLE;
            }
            
            if (!operand->size[context->eoszIndex])
            {
                info->operands[i].size = (context->decoder->machineMode == 64) ? 
                    ZydisRegisterGetWidth64(info->operands[i].reg) :
                    ZydisRegisterGetWidth(info->operands[i].reg);
            } else
            {
                // TODO: Always override size for register operands?
                info->operands[i].size = operand->size[context->eoszIndex] * 8;
            }
        }

        // Memory operands
        ZydisRegister vsibBaseRegister = ZYDIS_REGISTER_NONE;
        switch (operand->type)
        {
        case ZYDIS_SEMANTIC_OPTYPE_MEM:
            ZYDIS_CHECK(ZydisDecodeOperandMemory(context, info, &info->operands[i]));
            break;
        case ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBX:
            vsibBaseRegister = ZYDIS_REGISTER_XMM0;
            ZYDIS_CHECK(ZydisDecodeOperandMemory(context, info, &info->operands[i]));
            break;
        case ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBY:
            vsibBaseRegister = ZYDIS_REGISTER_YMM0;
            ZYDIS_CHECK(ZydisDecodeOperandMemory(context, info, &info->operands[i]));
            break;
        case ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBZ: 
            vsibBaseRegister = ZYDIS_REGISTER_ZMM0;
            ZYDIS_CHECK(ZydisDecodeOperandMemory(context, info, &info->operands[i]));
            break;
        case ZYDIS_SEMANTIC_OPTYPE_PTR:
            break; // TODO: implement
        case ZYDIS_SEMANTIC_OPTYPE_AGEN:
            break; // TODO: implement
        case ZYDIS_SEMANTIC_OPTYPE_MOFFS:
            ZYDIS_ASSERT(info->details.disp.dataSize);
            info->operands[i].type = ZYDIS_OPERAND_TYPE_MEMORY;
            info->operands[i].mem.disp.hasDisplacement = ZYDIS_TRUE;
            info->operands[i].mem.disp.value.sqword = info->details.disp.value.sqword;
            break;
        default:
            break;
        }
        if (info->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            if (vsibBaseRegister)
            {
                if (info->details.modrm.rm != 0x04)
                {
                    return ZYDIS_STATUS_INVALID_VSIB;
                }
                switch (info->addressWidth)
                {
                case 16:
                    return ZYDIS_STATUS_INVALID_VSIB;
                case 32:
                    info->operands[i].mem.index = 
                        info->operands[i].mem.index - ZYDIS_REGISTER_EAX + vsibBaseRegister + 
                        ((context->cache.V2 == 1) ? 16 : 0);
                    break;
                case 64:
                    info->operands[i].mem.index = 
                        info->operands[i].mem.index - ZYDIS_REGISTER_RAX + vsibBaseRegister + 
                        ((context->cache.V2 == 1) ? 16 : 0);
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
            }

            if (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_CS)
            {
                info->operands[i].mem.segment = ZYDIS_REGISTER_CS;    
            } else
            if (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS)
            {
                info->operands[i].mem.segment = ZYDIS_REGISTER_SS;    
            } else
            if (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS)
            {
                info->operands[i].mem.segment = ZYDIS_REGISTER_DS;    
            } else
            if (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_ES)
            {
                info->operands[i].mem.segment = ZYDIS_REGISTER_ES;    
            } else
            if (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_FS)
            {
                info->operands[i].mem.segment = ZYDIS_REGISTER_FS;    
            } else
            if (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_GS)
            {
                info->operands[i].mem.segment = ZYDIS_REGISTER_GS;    
            } else
            {
                if ((info->operands[i].mem.base == ZYDIS_REGISTER_RSP) ||
                    (info->operands[i].mem.base == ZYDIS_REGISTER_RBP) || 
                    (info->operands[i].mem.base == ZYDIS_REGISTER_ESP) ||
                    (info->operands[i].mem.base == ZYDIS_REGISTER_EBP) ||
                    (info->operands[i].mem.base == ZYDIS_REGISTER_SP)  ||
                    (info->operands[i].mem.base == ZYDIS_REGISTER_BP))
                {
                    info->operands[i].mem.segment = ZYDIS_REGISTER_SS;
                } else
                {
                    info->operands[i].mem.segment = ZYDIS_REGISTER_DS;
                };
            }

            //ZYDIS_ASSERT(operand->size[context->eoszIndex]);
            info->operands[i].size = operand->size[context->eoszIndex] * 8;

            // Handle compressed 8-bit displacement
            if (((info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
                 (info->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)) &&
                (info->details.disp.dataSize == 8))
            {
                info->operands[i].mem.disp.value.sqword *= info->avx.compressedDisp8Scale;
            }
        }

        // Immediate operands
        switch (operand->type)
        {
        case ZYDIS_SEMANTIC_OPTYPE_REL:
            ZYDIS_ASSERT(info->details.imm[immId].isRelative);
        case ZYDIS_SEMANTIC_OPTYPE_IMM:
            ZYDIS_ASSERT(!info->details.imm[immId].isRelative);
            ZYDIS_ASSERT((immId == 0) || (immId == 1));
            info->operands[i].type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
            info->operands[i].size = info->details.imm[immId].dataSize;
            info->operands[i].imm.value.uqword = info->details.imm[immId].value.uqword;
            info->operands[i].imm.isSigned = info->details.imm[immId].isSigned;
            info->operands[i].imm.isRelative = info->details.imm[immId].isRelative;
            ++immId;
            break;
        default:
            break;
        }

        ++operand;
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Sets the effective operand size for the given instruction.
 * 
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   definition  A pointer to the @c ZydisInstructionDefinition struct.
 */
static void ZydisSetEffectiveOperandSize(ZydisDecoderContext* context, ZydisInstructionInfo* info, 
    const ZydisInstructionDefinition* definition)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(definition);

    static const uint8_t operandSizeMap[6][8] =
    {
        // Default for most instructions
        {
            16, // 16 __ W0
            32, // 16 66 W0
            32, // 32 __ W0
            16, // 32 66 W0
            32, // 64 __ W0
            16, // 64 66 W0
            64, // 64 __ W1
            64  // 64 66 W1
        },
        // Operand size override 0x66 is ignored
        {
            16, // 16 __ W0
            16, // 16 66 W0
            32, // 32 __ W0
            32, // 32 66 W0
            32, // 64 __ W0
            32, // 64 66 W0
            64, // 64 __ W1
            64  // 64 66 W1
        },
        // REX.W promotes to 32-bit instead of 64-bit
        {
            16, // 16 __ W0
            32, // 16 66 W0
            32, // 32 __ W0
            16, // 32 66 W0
            32, // 64 __ W0
            16, // 64 66 W0
            32, // 64 __ W1
            32  // 64 66 W1
        },
        // Operand size defaults to 64-bit in 64-bit mode
        {
            16, // 16 __ W0
            32, // 16 66 W0
            32, // 32 __ W0
            16, // 32 66 W0
            64, // 64 __ W0
            16, // 64 66 W0
            64, // 64 __ W1
            64  // 64 66 W1
        },
        // Operand size is forced to 64-bit in 64-bit mode
        {
            16, // 16 __ W0
            32, // 16 66 W0
            32, // 32 __ W0
            16, // 32 66 W0
            64, // 64 __ W0
            64, // 64 66 W0
            64, // 64 __ W1
            64  // 64 66 W1
        },
        // Operand size is forced to 32-bit, if no REX.W is present.
        {
            32, // 16 __ W0
            32, // 16 66 W0
            32, // 32 __ W0
            32, // 32 66 W0
            32, // 64 __ W0
            32, // 64 66 W0
            64, // 64 __ W1
            64  // 64 66 W1
        }
    };
    
    uint8_t index = (info->attributes & ZYDIS_ATTRIB_HAS_OPERANDSIZE) ? 1 : 0;
    switch (context->decoder->machineMode)
    {
    case 16:
        index += 0;
        break;
    case 32:
        index += 2;
        break;
    case 64:
        index += 4;
        index += (context->cache.W & 0x01) << 1;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

    ZYDIS_ASSERT(definition->operandSizeMap < ZYDIS_ARRAY_SIZE(operandSizeMap));
    ZYDIS_ASSERT(index < ZYDIS_ARRAY_SIZE(operandSizeMap[definition->operandSizeMap]));

    info->operandSize = operandSizeMap[definition->operandSizeMap][index];
    
    switch (info->operandSize)
    {
    case 16:
        context->eoszIndex = 0;
        break;
    case 32:
        context->eoszIndex = 1;
        break;
    case 64:
        context->eoszIndex = 2;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
}

/**
 * @brief   Sets the effective address width for the given instruction.
 * 
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 */
static void ZydisSetEffectiveAddressWidth(ZydisDecoderContext* context, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);

    switch (context->decoder->addressWidth)
    {
    case 16:
        info->addressWidth = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 32 : 16;
        break;
    case 32:
        info->addressWidth = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 16 : 32;
        break;
    case 64:
        info->addressWidth = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 32 : 64;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
}

/**
 * @brief   Sets prefix-related attributes for the given instruction.
 * 
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   definition  A pointer to the @c ZydisInstructionDefinition struct.
 */
static void ZydisSetPrefixRelatedAttributes(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, const ZydisInstructionDefinition* definition)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(definition);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
    {
        const ZydisInstructionDefinitionDEFAULT* def = 
            (const ZydisInstructionDefinitionDEFAULT*)definition;

        if (def->acceptsLock)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_LOCK;
            if (info->details.prefixes.hasF0)
            {
                info->attributes |= ZYDIS_ATTRIB_HAS_LOCK;
            }
        }
        if (def->acceptsREP)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_REP;
        }
        if (def->acceptsREPEREPZ)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_REPE;
        }
        if (def->acceptsREPNEREPNZ)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_REPNE;
        }
        if (def->acceptsBOUND)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_BOUND;    
        }
        if (def->acceptsXACQUIRE)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_XACQUIRE;    
        }
        if (def->acceptsXRELEASE)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_XRELEASE;    
        }
        if (def->acceptsHLEWithoutLock)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_HLE_WITHOUT_LOCK;
        }

        switch (context->mandatoryCandidate)
        {
        case 0xF2:
            if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_REPNE)
            {
                info->attributes |= ZYDIS_ATTRIB_HAS_REPNE;
                break;
            }
            if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_XACQUIRE)
            {
                if ((info->attributes & ZYDIS_ATTRIB_HAS_LOCK) || (def->acceptsHLEWithoutLock))
                {
                    info->attributes |= ZYDIS_ATTRIB_HAS_XACQUIRE;
                    break;
                }
            }
            if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_BOUND)
            {
                info->attributes |= ZYDIS_ATTRIB_HAS_BOUND;
                break;
            }   
            break;
        case 0xF3:
            if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_REP)
            {
                info->attributes |= ZYDIS_ATTRIB_HAS_REP;
                break;
            }
            if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_REPE)
            {
                info->attributes |= ZYDIS_ATTRIB_HAS_REPE;
                break;
            }
            if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_XRELEASE)
            {
                if ((info->attributes & ZYDIS_ATTRIB_HAS_LOCK) || (def->acceptsHLEWithoutLock))
                {
                    info->attributes |= ZYDIS_ATTRIB_HAS_XRELEASE;
                    break;
                }
            }
            break;
        default:
            break;
        }

        if (def->acceptsBranchHints)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_BRANCH_HINTS;
            switch (context->lastSegmentPrefix)
            {
            case 0x2E:
                info->attributes |= ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN;
                break;
            case 0x3E:
                info->attributes |= ZYDIS_ATTRIB_HAS_BRANCH_TAKEN;
                break;
            default:
                break;
            }
        } else
        {
            if (context->lastSegmentPrefix && def->acceptsSegment)
            {
                switch (context->lastSegmentPrefix)
                {
                case 0x2E: 
                    info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_CS;
                    break;
                case 0x36:
                    info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_SS;
                    break;
                case 0x3E: 
                    info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_DS;
                    break;
                case 0x26: 
                    info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_ES;
                    break;
                case 0x64:
                    info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_FS;
                    break;
                case 0x65: 
                    info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_GS;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
            }
        }

        break;
    }
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
}

/**
 * @brief   Sets AVX-specific information for the given instruction.
 * 
 * @param   context     A pointer to the @c ZydisDecoderContext struct.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 * @param   definition  A pointer to the @c ZydisInstructionDefinition struct.
 */
static void ZydisSetAVXInformation(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, const ZydisInstructionDefinition* definition)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(definition);
    
    // Vector length
    switch (context->cache.LL)
    {
    case 0:
        info->avx.vectorLength = ZYDIS_VECTOR_LENGTH_128;
        break;
    case 1:
        info->avx.vectorLength = ZYDIS_VECTOR_LENGTH_256;
        break;
    case 2:
        info->avx.vectorLength = ZYDIS_VECTOR_LENGTH_512;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

    if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX)
    {
        const ZydisInstructionDefinitionEVEX* def = 
            (const ZydisInstructionDefinitionEVEX*)definition;
    
        info->avx.tupleType = def->tupleType;
        if (info->avx.tupleType)
        {
            ZYDIS_ASSERT(info->details.modrm.mod != 3);
            ZYDIS_ASSERT((def->elementSize ==  8) || (def->elementSize == 16) ||
                         (def->elementSize == 32) || (def->elementSize == 64));
            info->avx.elementSize = def->elementSize;

            // Compressed disp8 scale and broadcast-factor
            switch (info->avx.tupleType)
            {
            case ZYDIS_TUPLETYPE_FV:
                switch (info->details.evex.b)
                {
                case 0:
                    switch (info->avx.vectorLength)
                    {
                    case 128:
                        info->avx.compressedDisp8Scale = 16;
                        break;
                    case 256:
                        info->avx.compressedDisp8Scale = 32;
                        break;
                    case 512:
                        info->avx.compressedDisp8Scale = 64;
                        break;
                    default:
                        ZYDIS_UNREACHABLE;
                    }
                    break;
                case 1:
                    ZYDIS_ASSERT(def->functionality == ZYDIS_EVEX_FUNC_BC);
                    switch (context->cache.W)
                    {
                    case 0:
                        ZYDIS_ASSERT(info->avx.elementSize == 32);
                        info->avx.compressedDisp8Scale = 4;
                        switch (info->avx.vectorLength)
                        {
                        case 128:
                            info->avx.broadcastMode = ZYDIS_BROADCAST_MODE_1_TO_4;
                            break;
                        case 256:
                            info->avx.broadcastMode = ZYDIS_BROADCAST_MODE_1_TO_8;
                            break;
                        case 512:
                            info->avx.broadcastMode = ZYDIS_BROADCAST_MODE_1_TO_16;
                            break;
                        default:
                            ZYDIS_UNREACHABLE;
                        }
                        break;
                    case 1:
                        ZYDIS_ASSERT(info->avx.elementSize == 64);
                        info->avx.compressedDisp8Scale = 8;
                        switch (info->avx.vectorLength)
                        {
                        case 128:
                            info->avx.broadcastMode = ZYDIS_BROADCAST_MODE_1_TO_2;
                            break;
                        case 256:
                            info->avx.broadcastMode = ZYDIS_BROADCAST_MODE_1_TO_4;
                            break;
                        case 512:
                            info->avx.broadcastMode = ZYDIS_BROADCAST_MODE_1_TO_8;
                            break;
                        default:
                            ZYDIS_UNREACHABLE;
                        }
                        break;
                    default:
                        ZYDIS_UNREACHABLE;
                    }
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_HV:
                ZYDIS_ASSERT(info->avx.elementSize == 32);
                switch (info->details.evex.b)
                {
                case 0:
                    switch (info->avx.vectorLength)
                    {
                    case 128:
                        info->avx.compressedDisp8Scale = 8;
                        break;
                    case 256:
                        info->avx.compressedDisp8Scale = 16;
                        break;
                    case 512:
                        info->avx.compressedDisp8Scale = 32;
                        break;
                    default:
                        ZYDIS_UNREACHABLE;
                    }
                    break;
                case 1:
                    info->avx.compressedDisp8Scale = 4;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_FVM:
                switch (info->avx.vectorLength)
                {
                case 128:
                    info->avx.compressedDisp8Scale = 16;
                    break;
                case 256:
                    info->avx.compressedDisp8Scale = 32;
                    break;
                case 512:
                    info->avx.compressedDisp8Scale = 64;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_T1S:
                info->avx.compressedDisp8Scale = info->avx.elementSize / 8;
                break;
            case ZYDIS_TUPLETYPE_T1F:
                switch (info->avx.elementSize)
                {
                case 32:
                    info->avx.compressedDisp8Scale = 4;
                    break;
                case 64:
                    info->avx.compressedDisp8Scale = 8;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_GSCAT:
                switch (context->cache.W)
                {
                case 0:
                    ZYDIS_ASSERT(info->avx.elementSize == 32);
                    info->avx.compressedDisp8Scale = 4;
                    break;
                case 1:
                    ZYDIS_ASSERT(info->avx.elementSize == 64);
                    info->avx.compressedDisp8Scale = 8;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_T2:
                switch (context->cache.W)
                {
                case 0:
                    ZYDIS_ASSERT(info->avx.elementSize == 32);
                    info->avx.compressedDisp8Scale = 8;
                    break;
                case 1:
                    ZYDIS_ASSERT(info->avx.elementSize == 64);
                    ZYDIS_ASSERT((info->avx.vectorLength == 256) || (info->avx.vectorLength == 512));
                    info->avx.compressedDisp8Scale = 16;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_T4:
                switch (context->cache.W)
                {
                case 0:
                    ZYDIS_ASSERT(info->avx.elementSize == 32);
                    ZYDIS_ASSERT((info->avx.vectorLength == 256) || (info->avx.vectorLength == 512));
                    info->avx.compressedDisp8Scale = 16;
                    break;
                case 1:
                    ZYDIS_ASSERT(info->avx.elementSize == 64);
                    ZYDIS_ASSERT(info->avx.vectorLength == 512);
                    info->avx.compressedDisp8Scale = 32;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_T8:
                ZYDIS_ASSERT(!context->cache.W);
                ZYDIS_ASSERT(info->avx.vectorLength == 512);
                ZYDIS_ASSERT(info->avx.elementSize == 32);
                info->avx.compressedDisp8Scale = 32;
                break;
            case ZYDIS_TUPLETYPE_HVM:
                switch (info->avx.vectorLength)
                {
                case 128:
                    info->avx.compressedDisp8Scale = 8;
                    break;
                case 256:
                    info->avx.compressedDisp8Scale = 16;
                    break;
                case 512:
                    info->avx.compressedDisp8Scale = 32;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_QVM:
                switch (info->avx.vectorLength)
                {
                case 128:
                    info->avx.compressedDisp8Scale = 4;
                    break;
                case 256:
                    info->avx.compressedDisp8Scale = 8;
                    break;
                case 512:
                    info->avx.compressedDisp8Scale = 16;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_OVM:
                switch (info->avx.vectorLength)
                {
                case 128:
                    info->avx.compressedDisp8Scale = 2;
                    break;
                case 256:
                    info->avx.compressedDisp8Scale = 4;
                    break;
                case 512:
                    info->avx.compressedDisp8Scale = 8;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            case ZYDIS_TUPLETYPE_M128:
                info->avx.compressedDisp8Scale = 16;
                break;
            case ZYDIS_TUPLETYPE_DUP:
                switch (info->avx.vectorLength)
                {
                case 128:
                    info->avx.compressedDisp8Scale = 8;
                    break;
                case 256:
                    info->avx.compressedDisp8Scale = 32;
                    break;
                case 512:
                    info->avx.compressedDisp8Scale = 64;
                    break;
                default:
                    ZYDIS_UNREACHABLE;
                }
                break;
            default:
                ZYDIS_UNREACHABLE;
            }
        } else
        {
            // TODO: Add tuple type
            ZYDIS_ASSERT(info->details.modrm.mod == 3);
        }

        // Rounding mode
        if (def->functionality == ZYDIS_EVEX_FUNC_RC)
        {
            info->avx.roundingMode = ZYDIS_RNDMODE_RN_SAE + context->cache.LL;
        }

        // Mask mode
        info->avx.maskMode = ZYDIS_MASKMODE_MERGE + info->details.evex.z;
    }
}

/* ---------------------------------------------------------------------------------------------- */

// TODO: Update attributes after a valid instruction was found

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisNodeHandlerXOP(ZydisInstructionInfo* info, uint16_t* index)
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
    return ZYDIS_STATUS_SUCCESS;      
}

static ZydisStatus ZydisNodeHandlerVEX(ZydisInstructionInfo* info, uint16_t* index)
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
        *index = info->details.vex.m_mmmm + (info->details.vex.pp << 2) + 1;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerEMVEX(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        *index = 0;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        *index = info->details.evex.mm + (info->details.evex.pp << 2) + 1;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        ZYDIS_ASSERT(info->details.mvex.isDecoded);
        *index = info->details.mvex.mmmm + (info->details.mvex.pp << 2) + 17;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerOpcode(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    // Handle possible encoding-prefix and opcode-map changes
    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        ZYDIS_CHECK(ZydisInputNext(context, info, &info->opcode));
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
                ZYDIS_CHECK(ZydisInputPeek(context, info, &nextInput)); 
                if (((nextInput & 0xF0) >= 0xC0) || 
                    (context->decoder->machineMode == ZYDIS_MACHINE_MODE_LONG_64))
                {
                    if (info->attributes & ZYDIS_ATTRIB_HAS_REX)
                    {
                        return ZYDIS_STATUS_ILLEGAL_REX;
                    }
                    if (context->mandatoryCandidate)
                    {
                        return ZYDIS_STATUS_ILLEGAL_LEGACY_PFX;
                    }
                    uint8_t prefixBytes[4] = { 0, 0, 0, 0 };
                    prefixBytes[0] = info->opcode;
                    switch (info->opcode)
                    {
                    case 0xC4:
                        // Read additional 3-byte VEX-prefix data
                        ZYDIS_ASSERT(!info->details.vex.isDecoded);
                        ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[1]));
                        ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[2]));
                        break;
                    case 0xC5:
                        // Read additional 2-byte VEX-prefix data
                        ZYDIS_ASSERT(!info->details.vex.isDecoded);
                        ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[1]));
                        break;
                    case 0x62:
                        // Read additional EVEX/MVEX-prefix data
                        ZYDIS_ASSERT(!info->details.evex.isDecoded);
                        ZYDIS_ASSERT(!info->details.mvex.isDecoded);
                        ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[1]));
                        ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[2]));
                        ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[3]));
                        break;
                    default:
                        ZYDIS_UNREACHABLE;
                    }
                    switch (info->opcode)
                    {
                    case 0xC4:
                    case 0xC5:
                        // Decode VEX-prefix
                        info->encoding = ZYDIS_INSTRUCTION_ENCODING_VEX;
                        ZYDIS_CHECK(ZydisDecodeVEX(context, info, prefixBytes));
                        info->opcodeMap = ZYDIS_OPCODE_MAP_EX0 + info->details.vex.m_mmmm;
                        break;
                    case 0x62:
                        switch ((prefixBytes[2] >> 2) & 0x01)
                        {
                        case 0:
                            // Decode MVEX-prefix
                            info->encoding = ZYDIS_INSTRUCTION_ENCODING_MVEX;
                            ZYDIS_CHECK(ZydisDecodeMVEX(context, info, prefixBytes));
                            info->opcodeMap = ZYDIS_OPCODE_MAP_EX0 + info->details.mvex.mmmm;
                            break;
                        case 1:
                            // Decode EVEX-prefix
                            info->encoding = ZYDIS_INSTRUCTION_ENCODING_EVEX;
                            ZYDIS_CHECK(ZydisDecodeEVEX(context, info, prefixBytes));
                            info->opcodeMap = ZYDIS_OPCODE_MAP_EX0 + info->details.evex.mm;
                            break;
                        default:
                            ZYDIS_UNREACHABLE;
                        }
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
                ZYDIS_CHECK(ZydisInputPeek(context, info, &nextInput));
                if ((nextInput & 0x1F) >= 8)
                {
                    if (info->attributes & ZYDIS_ATTRIB_HAS_REX)
                    {
                        return ZYDIS_STATUS_ILLEGAL_REX;
                    }
                    if (context->mandatoryCandidate)
                    {
                        return ZYDIS_STATUS_ILLEGAL_LEGACY_PFX;
                    }
                    uint8_t prefixBytes[3] = { 0x8F, 0x00, 0x00 };
                    // Read additional xop-prefix data
                    ZYDIS_ASSERT(!info->details.xop.isDecoded);
                    ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[1]));
                    ZYDIS_CHECK(ZydisInputNext(context, info, &prefixBytes[2]));
                    // Decode xop-prefix
                    info->encoding = ZYDIS_INSTRUCTION_ENCODING_XOP;
                    ZYDIS_CHECK(ZydisDecodeXOP(context, info, prefixBytes));
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
        // TODO: We need to change this
        // All 3DNOW (0x0F 0x0F) instructions are using the same operand encoding. We just 
        // decode a random (pi2fw) instruction and extract the actual opcode later.
        *index = 0x0C;
        return ZYDIS_STATUS_SUCCESS;
    default:
        ZYDIS_CHECK(ZydisInputNext(context, info, &info->opcode));
        break;
    }

    *index = info->opcode; 
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerMode(ZydisDecoderContext* context, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(index);

    switch (context->decoder->machineMode)
    {
    case 16:
        *index = 0;
        break;
    case 32:
        *index = 1;
        break;
    case 64:
        *index = 2;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerModeCompact(ZydisDecoderContext* context, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(index);

    *index = (context->decoder->machineMode == ZYDIS_MACHINE_MODE_LONG_64) ? 0 : 1;
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerModrmMod(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(context, info, &modrmByte));
        ZydisDecodeModRM(info, modrmByte);               
    }
    *index = info->details.modrm.mod;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerModrmModCompact(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_CHECK(ZydisNodeHandlerModrmMod(context, info, index));
    *index = (*index == 0x3) ? 0 : 1;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerModrmReg(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(context, info, &modrmByte));
        ZydisDecodeModRM(info, modrmByte);               
    }
    *index = info->details.modrm.reg;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerModrmRm(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(context, info, &modrmByte));
        ZydisDecodeModRM(info, modrmByte);                
    }
    *index = info->details.modrm.rm;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerMandatoryPrefix(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (context->mandatoryCandidate)
    {
    case 0x66:
        info->attributes &= ~ZYDIS_ATTRIB_HAS_OPERANDSIZE;
        *index = 2;
        break;
    case 0xF3:
        *index = 3;
        break;
    case 0xF2:
        *index = 4;
        break;
    default:
        *index = 1;
        break;
    }
    // TODO: Consume prefix and make sure it's available again, if we need to fallback

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerOperandSize(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if ((context->decoder->machineMode == 64) && (context->cache.W))
    {
        *index = 2;
    } else
    {
        switch (context->decoder->machineMode)
        {
        case 16:
            *index = (info->attributes & ZYDIS_ATTRIB_HAS_OPERANDSIZE) ? 1 : 0;
            break;
        case 32:
        case 64:
            *index = (info->attributes & ZYDIS_ATTRIB_HAS_OPERANDSIZE) ? 0 : 1;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
    }   

    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerAddressSize(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (context->decoder->addressWidth)
    {
    case 16:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 1 : 0;
        break;
    case 32:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 0 : 1;
        break;
    case 64:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 1 : 2;
        break;
    default: 
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerVectorLength(ZydisDecoderContext* context, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYDIS_ASSERT(info->details.xop.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYDIS_ASSERT(info->details.vex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        ZYDIS_ASSERT(info->details.mvex.isDecoded);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    *index = context->cache.LL;
    if (*index == 3)
    {
        return ZYDIS_STATUS_DECODING_ERROR;
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerRexW(ZydisDecoderContext* context, ZydisInstructionInfo* info, 
    uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        // nothing to do here       
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYDIS_ASSERT(info->details.xop.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYDIS_ASSERT(info->details.vex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        ZYDIS_ASSERT(info->details.mvex.isDecoded);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    *index = context->cache.W;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerRexB(ZydisDecoderContext* context, ZydisInstructionInfo* info, 
    uint16_t* index)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    switch (info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        // nothing to do here       
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYDIS_ASSERT(info->details.xop.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYDIS_ASSERT(info->details.vex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYDIS_ASSERT(info->details.evex.isDecoded);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        ZYDIS_ASSERT(info->details.mvex.isDecoded);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    *index = context->cache.B;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerEvexB(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = info->details.evex.b;
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerEvexZ(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = info->details.evex.z;
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerMvexE(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX);
    ZYDIS_ASSERT(info->details.mvex.isDecoded);
    *index = info->details.mvex.E;
    return ZYDIS_STATUS_SUCCESS;   
}

/**
 * @brief   Uses the instruction-tree to decode the current instruction.
 *
 * @param   context A pointer to the @c ZydisDecoderContext instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  A zydis decoder status code.
 */
static ZydisStatus ZydisDecodeInstruction(ZydisDecoderContext* context, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(context);
    ZYDIS_ASSERT(info);

    // Iterate through the instruction table
    const ZydisInstructionTreeNode* node = ZydisInstructionTreeGetRootNode();
    ZydisInstructionTreeNodeType nodeType;
    do
    {
        nodeType = node->type;
        uint16_t index = 0;
        ZydisStatus status = 0;
        switch (nodeType)
        {
        case ZYDIS_NODETYPE_INVALID:
            return ZYDIS_STATUS_DECODING_ERROR;
        case ZYDIS_NODETYPE_FILTER_XOP:
            status = ZydisNodeHandlerXOP(info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_VEX:
            status = ZydisNodeHandlerVEX(info, &index);
            break;  
        case ZYDIS_NODETYPE_FILTER_EMVEX:
            status = ZydisNodeHandlerEMVEX(info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_OPCODE:
            status = ZydisNodeHandlerOpcode(context, info, &index);
            break;            
        case ZYDIS_NODETYPE_FILTER_MODE:
            status = ZydisNodeHandlerMode(context, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_MODE_COMPACT:
            status = ZydisNodeHandlerModeCompact(context, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_MODRM_MOD:
            status = ZydisNodeHandlerModrmMod(context, info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_MODRM_MOD_COMPACT:
            status = ZydisNodeHandlerModrmModCompact(context, info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_MODRM_REG:
            status = ZydisNodeHandlerModrmReg(context, info, &index);
            break;       
        case ZYDIS_NODETYPE_FILTER_MODRM_RM:
            status = ZydisNodeHandlerModrmRm(context, info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_MANDATORY_PREFIX:
            status = ZydisNodeHandlerMandatoryPrefix(context, info, &index);
            // TODO: Return to this point, if index == 0 contains a value and the previous path
            // TODO: was not successfull
            // TODO: Restore consumed prefix
            break; 
        case ZYDIS_NODETYPE_FILTER_OPERAND_SIZE:
            status = ZydisNodeHandlerOperandSize(context, info, &index);
            break;    
        case ZYDIS_NODETYPE_FILTER_ADDRESS_SIZE:
            status = ZydisNodeHandlerAddressSize(context, info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_VECTOR_LENGTH:
            status = ZydisNodeHandlerVectorLength(context, info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_REX_W:
            status = ZydisNodeHandlerRexW(context, info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_REX_B:
            status = ZydisNodeHandlerRexB(context, info, &index);
            break;
        case ZYDIS_NODETYPE_FILTER_EVEX_B:
            status = ZydisNodeHandlerEvexB(info, &index);
            break;  
        case ZYDIS_NODETYPE_FILTER_EVEX_Z:
            status = ZydisNodeHandlerEvexZ(info, &index);
            break; 
        case ZYDIS_NODETYPE_FILTER_MVEX_E:
            status = ZydisNodeHandlerMvexE(info, &index);
            break;                           
        default:
            if (nodeType & ZYDIS_NODETYPE_DEFINITION_MASK)
            { 
                const ZydisInstructionDefinition* definition;
                ZydisGetInstructionDefinition(node, &definition);
                ZydisSetEffectiveOperandSize(context, info, definition);
                ZydisSetEffectiveAddressWidth(context, info);

                const ZydisInstructionParts* optionalParts;
                ZydisGetOptionalInstructionParts(node, &optionalParts);
                ZYDIS_CHECK(ZydisDecodeOptionalInstructionParts(context, info, optionalParts));

                if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW)
                {
                    ZYDIS_CHECK(ZydisInputNext(context, info, &info->opcode));
                    node = ZydisInstructionTreeGetRootNode();
                    node = ZydisInstructionTreeGetChildNode(node, 0x0F);
                    node = ZydisInstructionTreeGetChildNode(node, 0x0F);
                    node = ZydisInstructionTreeGetChildNode(node, info->opcode);
                    if (node->type == ZYDIS_NODETYPE_INVALID)
                    {
                        return ZYDIS_STATUS_DECODING_ERROR;        
                    }
                    ZYDIS_ASSERT(node->type == ZYDIS_NODETYPE_FILTER_MODRM_MOD_COMPACT);
                    node = ZydisInstructionTreeGetChildNode(
                        node, (info->details.modrm.mod == 0x3) ? 0 : 1);
                    ZydisGetInstructionDefinition(node, &definition);
                }              

                info->mnemonic = definition->mnemonic;

                if (context->decoder->decodeGranularity == ZYDIS_DECODE_GRANULARITY_FULL)
                {
                    ZydisSetPrefixRelatedAttributes(context, info, definition);
                    switch (info->encoding)
                    {
                    case ZYDIS_INSTRUCTION_ENCODING_XOP:
                    case ZYDIS_INSTRUCTION_ENCODING_VEX:
                    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
                    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
                        ZydisSetAVXInformation(context, info, definition);
                        break;
                    default:
                        break;
                    }
                    ZYDIS_CHECK(ZydisDecodeOperands(context, info, definition));
                }

                return ZYDIS_STATUS_SUCCESS;
            }
            ZYDIS_UNREACHABLE;
        }
        ZYDIS_CHECK(status);
        node = ZydisInstructionTreeGetChildNode(node, index);
    } while((nodeType != ZYDIS_NODETYPE_INVALID) && !(nodeType & ZYDIS_NODETYPE_DEFINITION_MASK));
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZydisStatus ZydisDecoderInitInstructionDecoder(ZydisInstructionDecoder* decoder, 
    ZydisMachineMode machineMode, ZydisAddressWidth addressWidth)
{
    return ZydisDecoderInitInstructionDecoderEx(
        decoder, machineMode, addressWidth, ZYDIS_DECODE_GRANULARITY_DEFAULT);
}

ZydisStatus ZydisDecoderInitInstructionDecoderEx(ZydisInstructionDecoder* decoder, 
    ZydisMachineMode machineMode, ZydisAddressWidth addressWidth, 
    ZydisDecodeGranularity decodeGranularity)
{
    if (!decoder || ((machineMode != 16) && (machineMode != 32) && (machineMode != 64)) ||
        ((decodeGranularity != ZYDIS_DECODE_GRANULARITY_DEFAULT) && 
         (decodeGranularity != ZYDIS_DECODE_GRANULARITY_FULL) && 
         (decodeGranularity != ZYDIS_DECODE_GRANULARITY_MINIMAL)))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    if (machineMode == 64)
    {
        addressWidth = ZYDIS_ADDRESS_WIDTH_64;
    } else
    {
        if ((addressWidth != 16) && (addressWidth != 32) && (addressWidth != 64))
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
    }
    if (decodeGranularity == ZYDIS_DECODE_GRANULARITY_DEFAULT)
    {
        decodeGranularity = ZYDIS_DECODE_GRANULARITY_FULL;
    }

    decoder->machineMode = machineMode;
    decoder->addressWidth = addressWidth;
    decoder->decodeGranularity = decodeGranularity;

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisDecoderDecodeBuffer(ZydisInstructionDecoder* decoder, const void* buffer, 
    size_t bufferLen, uint64_t instructionPointer, ZydisInstructionInfo* info)
{
    if (!decoder)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (!buffer || !bufferLen)
    {
        return ZYDIS_STATUS_NO_MORE_DATA;
    }

    ZydisDecoderContext context;
    memset(&context.cache, 0, sizeof(context.cache));
    context.decoder = decoder;
    context.buffer = (uint8_t*)buffer;
    context.bufferLen = bufferLen;
    context.lastSegmentPrefix = 0;
    context.mandatoryCandidate = 0;

    void* userData = info->userData;
    memset(info, 0, sizeof(*info));   
    info->machineMode = decoder->machineMode;
    info->instrAddress = instructionPointer;
    info->userData = userData;

    ZYDIS_CHECK(ZydisCollectOptionalPrefixes(&context, info));
    ZYDIS_CHECK(ZydisDecodeInstruction(&context, info));

    // TODO: The index, dest and mask regs for AVX2 gathers must be different.

    // TODO: More EVEX UD conditions (page 81)

    // TODO: Set AVX-512 info

    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
