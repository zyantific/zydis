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
 * @return  A zydis status code.
 *          
 * If not empty, the internal buffer of the @c ZydisInstructionDecoder instance is used as temporary
 * data-source, instead of reading the byte from the actual input data-source.
 * 
 * This function may fail, if the @c ZYDIS_MAX_INSTRUCTION_LENGTH limit got exceeded, or no more   
 * data is available.
 */
static ZydisStatus ZydisInputPeek(ZydisInstructionDecoder* decoder, ZydisInstructionInfo* info, 
    uint8_t* value)
{ 
    ZYDIS_ASSERT(decoder); 
    ZYDIS_ASSERT(info); 
    ZYDIS_ASSERT(value);

    if (info->length >= ZYDIS_MAX_INSTRUCTION_LENGTH) 
    { 
        return ZYDIS_STATUS_INSTRUCTION_TOO_LONG; 
    } 

    if (decoder->input.bufferLen > 0)
    {
        *value = decoder->input.buffer[0];
        return ZYDIS_STATUS_SUCCESS;
    }

    return ZYDIS_STATUS_NO_MORE_DATA;    
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
static void ZydisInputSkip(ZydisInstructionDecoder* decoder, ZydisInstructionInfo* info)
{ 
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->length < ZYDIS_MAX_INSTRUCTION_LENGTH);

    info->data[info->length++] = decoder->input.buffer++[0];
    --decoder->input.bufferLen;
}

/**
 * @brief   Reads one byte from the current read-position of the input data-source and increases the
 *          read-position by one byte afterwards.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 * @param   value   A pointer to the memory that receives the byte from the input data-source.
 *
 * @return  A zydis status code.
 *          
 * This function acts like a subsequent call of @c ZydisInputPeek and @c ZydisInputSkip.
 */
static ZydisStatus ZydisInputNext(ZydisInstructionDecoder* decoder, ZydisInstructionInfo* info, 
    uint8_t* value)
{ 
    ZYDIS_ASSERT(decoder); 
    ZYDIS_ASSERT(info); 
    ZYDIS_ASSERT(value);

    if (info->length >= ZYDIS_MAX_INSTRUCTION_LENGTH) 
    { 
        return ZYDIS_STATUS_INSTRUCTION_TOO_LONG; 
    } 

    if (decoder->input.bufferLen > 0)
    {
        *value = decoder->input.buffer++[0];
        info->data[info->length++] = *value;
        --decoder->input.bufferLen;
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
 * @param   rexByte The REX byte.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 */
static void ZydisDecodeREX(ZydisInstructionInfo* info, uint8_t rexByte)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT((rexByte & 0xF0) == 0x40);

    info->attributes |= ZYDIS_ATTRIB_HAS_REX;
    info->details.rex.isDecoded = ZYDIS_TRUE;
    info->details.rex.data[0]   = rexByte;
    info->details.rex.W         = (rexByte >> 3) & 0x01;
    info->details.rex.R         = (rexByte >> 2) & 0x01;
    info->details.rex.X         = (rexByte >> 1) & 0x01;
    info->details.rex.B         = (rexByte >> 0) & 0x01;
    // Update internal fields
    info->details.internal.W    = info->details.rex.W;
    info->details.internal.R    = info->details.rex.R;
    info->details.internal.X    = info->details.rex.X;
    info->details.internal.B    = info->details.rex.B;
}

/**
 * @brief   Decodes the XOP-prefix.
 *
 * @param   xopByte1    The first XOP byte.
 * @param   xopByte2    The second XOP byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeXOP(uint8_t xopByte1, uint8_t xopByte2, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(((xopByte1 >> 0) & 0x1F) >= 8);

    info->attributes |= ZYDIS_ATTRIB_HAS_XOP;
    info->details.xop.isDecoded     = ZYDIS_TRUE;
    info->details.xop.data[0]       = 0x8F;
    info->details.xop.data[1]       = xopByte1;
    info->details.xop.data[2]       = xopByte2;
    info->details.xop.R             = (xopByte1 >> 7) & 0x01;
    info->details.xop.X             = (xopByte1 >> 6) & 0x01;
    info->details.xop.B             = (xopByte1 >> 5) & 0x01;
    info->details.xop.m_mmmm        = (xopByte1 >> 0) & 0x1F;
    if ((info->details.xop.m_mmmm < 0x08) || (info->details.xop.m_mmmm > 0x0A))
    {
        // Invalid according to the AMD documentation
        return ZYDIS_STATUS_INVALID_MAP;
    }
    info->details.xop.W             = (xopByte2 >> 7) & 0x01;
    info->details.xop.vvvv          = (xopByte2 >> 3) & 0x0F;
    info->details.xop.L             = (xopByte2 >> 2) & 0x01;
    info->details.xop.pp            = (xopByte2 >> 0) & 0x03; 
    // Update internal fields
    info->details.internal.W = info->details.xop.W;
    info->details.internal.R = 0x01 & ~info->details.xop.R;
    info->details.internal.X = 0x01 & ~info->details.xop.X;
    info->details.internal.B = 0x01 & ~info->details.xop.B;
    info->details.internal.L = info->details.xop.L;     
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the VEX-prefix.
 *
 * @param   vexOpcode   The VEX opcode.
 * @param   vexByte1    The first VEX byte.
 * @param   vexByte2    The second VEX byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeVEX(uint8_t vexOpcode, uint8_t vexByte1, uint8_t vexByte2, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    info->attributes |= ZYDIS_ATTRIB_HAS_VEX;
    info->details.vex.isDecoded     = ZYDIS_TRUE;
    info->details.vex.data[0]       = vexOpcode;
    switch (vexOpcode)
    {
    case 0xC4:
        info->details.vex.data[1]   = vexByte1;
        info->details.vex.data[2]   = vexByte2;
        info->details.vex.R         = (vexByte1 >> 7) & 0x01;
        info->details.vex.X         = (vexByte1 >> 6) & 0x01;
        info->details.vex.B         = (vexByte1 >> 5) & 0x01;
        info->details.vex.m_mmmm    = (vexByte1 >> 0) & 0x1F;
        info->details.vex.W         = (vexByte2 >> 7) & 0x01;
        info->details.vex.vvvv      = (vexByte2 >> 3) & 0x0F;
        info->details.vex.L         = (vexByte2 >> 2) & 0x01;
        info->details.vex.pp        = (vexByte2 >> 0) & 0x03;
        break;
    case 0xC5:
        info->details.vex.data[1]   = vexByte1;
        info->details.vex.data[2]   = 0;
        info->details.vex.R         = (vexByte1 >> 7) & 0x01;
        info->details.vex.X         = 1;
        info->details.vex.B         = 1;
        info->details.vex.m_mmmm    = 1;
        info->details.vex.W         = 0;
        info->details.vex.vvvv      = (vexByte1 >> 3) & 0x0F;
        info->details.vex.L         = (vexByte1 >> 2) & 0x01;
        info->details.vex.pp        = (vexByte1 >> 0) & 0x03;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }  
    if ((info->details.vex.m_mmmm == 0x00) || (info->details.vex.m_mmmm > 0x03))
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_INVALID_MAP;
    }
    // Update internal fields
    info->details.internal.W = info->details.vex.W;
    info->details.internal.R = 0x01 & ~info->details.vex.R;
    info->details.internal.X = 0x01 & ~info->details.vex.X;
    info->details.internal.B = 0x01 & ~info->details.vex.B;
    info->details.internal.L = info->details.vex.L;
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the EVEX-prefix.
 *
 * @param   evexByte1   The first EVEX byte.
 * @param   evexByte2   The second EVEX byte.
 * @param   evexByte3   The third EVEX byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeEVEX(uint8_t evexByte1, uint8_t evexByte2, uint8_t evexByte3, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    info->attributes |= ZYDIS_ATTRIB_HAS_EVEX;
    info->details.evex.isDecoded    = ZYDIS_TRUE;
    info->details.evex.data[0]      = 0x62;
    info->details.evex.data[1]      = evexByte1;
    info->details.evex.data[2]      = evexByte2;
    info->details.evex.data[3]      = evexByte3;
    info->details.evex.R            = (evexByte1 >> 7) & 0x01;
    info->details.evex.X            = (evexByte1 >> 6) & 0x01;
    info->details.evex.B            = (evexByte1 >> 5) & 0x01;
    info->details.evex.R2           = (evexByte1 >> 4) & 0x01;
    if (((evexByte1 >> 2) & 0x03) != 0x00)
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_MALFORMED_EVEX;
    }
    info->details.evex.mm           = (evexByte1 >> 0) & 0x03;
    if (info->details.evex.mm == 0x00)
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_INVALID_MAP;
    }
    info->details.evex.W            = (evexByte2 >> 7) & 0x01;
    info->details.evex.vvvv         = (evexByte2 >> 3) & 0x0F;
    if (((evexByte2 >> 2) & 0x01) != 0x01)
    {
        // Invalid according to the intel documentation
        return ZYDIS_STATUS_MALFORMED_EVEX;
    }
    info->details.evex.pp           = (evexByte2 >> 0) & 0x03;
    info->details.evex.z            = (evexByte3 >> 7) & 0x01;
    info->details.evex.L2           = (evexByte3 >> 6) & 0x01;
    info->details.evex.L            = (evexByte3 >> 5) & 0x01;
    info->details.evex.b            = (evexByte3 >> 4) & 0x01;
    info->details.evex.V2           = (evexByte3 >> 3) & 0x01;
    info->details.evex.aaa          = (evexByte3 >> 0) & 0x07;    
    // Update internal fields
    info->details.internal.W  = info->details.evex.W;
    info->details.internal.R  = 0x01 & ~info->details.evex.R;
    info->details.internal.X  = 0x01 & ~info->details.evex.X;
    info->details.internal.B  = 0x01 & ~info->details.evex.B;
    info->details.internal.L  = info->details.evex.L;
    info->details.internal.R2 = 0x01 & ~info->details.evex.R2;
    info->details.internal.V2 = 0x01 & ~info->details.evex.V2;
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes the ModRM-byte.
 *
 * @param   modrmByte   The ModRM byte.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct.
 */
static void ZydisDecodeModRM(uint8_t modrmByte, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);

    info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
    info->details.modrm.isDecoded   = ZYDIS_TRUE;
    info->details.modrm.data[0]     = modrmByte;
    info->details.modrm.mod         = (modrmByte >> 6) & 0x03;
    info->details.modrm.reg         = (modrmByte >> 3) & 0x07;
    info->details.modrm.rm          = (modrmByte >> 0) & 0x07;
}

/**
 * @brief   Decodes the SIB-byte.
 *
 * @param   sibByte The SIB byte.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct
 */
static void ZydisDecodeSIB(uint8_t sibByte, ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->details.modrm.isDecoded);
    ZYDIS_ASSERT((info->details.modrm.rm & 0x7) == 4);

    info->attributes |= ZYDIS_ATTRIB_HAS_SIB;
    info->details.sib.isDecoded = ZYDIS_TRUE;
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
 * @return  A zydis status code.
 *         
 * This function sets the corresponding flag for each prefix and automatically decodes the last
 * REX-prefix (if exists).
 */
static ZydisStatus ZydisCollectOptionalPrefixes(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);

    ZydisBool done = ZYDIS_FALSE;
    do
    {
        uint8_t prefixByte;
        ZYDIS_CHECK(ZydisInputPeek(decoder, info, &prefixByte));
        switch (prefixByte)
        {
        case 0xF0:
            ++info->details.prefixes.hasF0;
            break;
        case 0xF2:
            decoder->hasUnusedPrefixF2F3 = 0xF2;
            ++info->details.prefixes.hasF2;
            break;
        case 0xF3:
            decoder->hasUnusedPrefixF2F3 = 0xF3;
            ++info->details.prefixes.hasF3;
            break;
        case 0x2E: 
            ++info->details.prefixes.has2E;
            decoder->lastSegmentPrefix = 0x2E;
            break;
        case 0x36:
            ++info->details.prefixes.has36;
            decoder->lastSegmentPrefix = 0x36;
            break;
        case 0x3E: 
            ++info->details.prefixes.has3E;
            decoder->lastSegmentPrefix = 0x3E;
            break;
        case 0x26: 
            ++info->details.prefixes.has26;
            decoder->lastSegmentPrefix = 0x26;
            break;
        case 0x64:
            ++info->details.prefixes.has64;
            decoder->lastSegmentPrefix = 0x64;
            break;
        case 0x65: 
            ++info->details.prefixes.has65;
            decoder->lastSegmentPrefix = 0x65;
            break;
        case 0x66:
            decoder->hasUnusedPrefix66 = 0x66;
            ++info->details.prefixes.has66;
            break;
        case 0x67:
            ++info->details.prefixes.has67;
            break;
        default:
            if ((decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) && 
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
            ZydisInputSkip(decoder, info);
        }
    } while (!done);

    if (info->details.rex.data[0])
    {
        ZydisDecodeREX(info, info->details.rex.data[0]);
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
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperandImmediate(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, ZydisOperandInfo* operand, uint8_t physicalSize, 
    ZydisBool isSigned)
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
            decoder->imm8initialized = ZYDIS_TRUE;
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
    return ZYDIS_STATUS_SUCCESS;
}

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
 * @brief   Decodes a memory or register operand encoded in the ModRM.rm field.
 *
 * @param   decoder         A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operand         A pointer to the @c ZydisOperandInfo struct.
 * @param   registerClass   The register class.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperandModrmRm(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, ZydisOperandInfo* operand, ZydisRegisterClass registerClass)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);
    ZYDIS_ASSERT(info->details.modrm.isDecoded);

    uint8_t modrm_rm = (info->details.internal.B << 3) | info->details.modrm.rm;
    if (info->details.modrm.mod == 3)
    {
        return ZydisDecodeOperandRegister(info, operand, registerClass, 
            (info->details.internal.X << 4) | modrm_rm);
    }
    operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
    uint8_t displacementSize = 0;
    // TODO: Some instructions (like the MPX ones) do not accept the address-size prefix
    info->attributes |= ZYDIS_ATTRIB_ACCEPTS_ADDRESSSIZE;
    if (info->details.prefixes.has67)
    {
        info->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
    }
    switch (decoder->disassemblerMode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:                     // TODO: Set ZYDIS_ATTRIB_ACCEPTS_ADDRESSSIZE and ZYDIS_ATTRIB_HAS_ADDRESSSIZE after getting the instruction definition
        operand->mem.addressSize = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 32 : 16;
        break;
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
        operand->mem.addressSize = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 16 : 32;
        break;
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        operand->mem.addressSize = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 32 : 64;
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
                    info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
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
                ZydisDecodeSIB(sibByte, info);
            }
            uint8_t sib_index = (info->details.internal.X << 3) | info->details.sib.index;
            uint8_t sib_base = (info->details.internal.B << 3) | info->details.sib.base;
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
                info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
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
                ZydisDecodeSIB(sibByte, info);
            }
            uint8_t sib_index = (info->details.internal.X << 3) | info->details.sib.index;
            uint8_t sib_base = (info->details.internal.B << 3) | info->details.sib.base;
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
        ZYDIS_CHECK(
            ZydisDecodeOperandImmediate(decoder, info, operand, displacementSize, ZYDIS_TRUE));
        decoder->imm8initialized = ZYDIS_FALSE;
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->mem.disp.dataSize = displacementSize;
        operand->mem.disp.value.sqword = operand->imm.value.sqword;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->imm.isSigned = ZYDIS_FALSE;
        operand->imm.dataSize = 0;
        operand->imm.value.sqword = 0;
        operand->imm.dataOffset = 0;
    }
    return ZYDIS_STATUS_SUCCESS;
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
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperand(ZydisInstructionDecoder* decoder, ZydisInstructionInfo* info, 
    ZydisOperandInfo* operand, ZydisSemanticOperandType type, ZydisOperandEncoding encoding)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);

    // Fixed registers
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_AL:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 8;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_AL;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_CL:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 8;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_CL;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_AX:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_AX;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_DX:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_DX;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_ECX:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 32;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_ECX;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_EAX:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 32;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_EAX;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_RAX:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 64;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_RAX;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_ES:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_ES;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_CS:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_CS;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_SS:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_SS;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_DS:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_DS;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_GS:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_GS;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_FS:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 16;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_FS;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_ST0:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->size = 80;
        operand->type = ZYDIS_OPERAND_TYPE_REGISTER;
        operand->reg = ZYDIS_REGISTER_ST0;
        return ZYDIS_STATUS_SUCCESS;
    default:
        break;
    }
    
    // Register operands
    ZydisRegisterClass registerClass = ZYDIS_REGCLASS_INVALID;
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_GPR8:
        operand->size = 8;
        registerClass = ZYDIS_REGCLASS_GPR8;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_GPR16:
        operand->size = 16;
        registerClass = ZYDIS_REGCLASS_GPR16;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_GPR32:
        operand->size = 32;
        registerClass = ZYDIS_REGCLASS_GPR32;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_GPR64:
        operand->size = 64;
        registerClass = ZYDIS_REGCLASS_GPR64;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_TR:
        operand->size = 32;
        registerClass = ZYDIS_REGCLASS_TEST;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_CR:
        operand->size = (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ? 64 : 32;
        registerClass = ZYDIS_REGCLASS_CONTROL;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_DR:
        operand->size = (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ? 64 : 32;
        registerClass = ZYDIS_REGCLASS_DEBUG;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_FPR:
        operand->size = 80; 
        registerClass = ZYDIS_REGCLASS_X87;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_SREG:
        operand->size = 16;
        registerClass = ZYDIS_REGCLASS_SEGMENT;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR64:
        operand->size = 64;
        registerClass = ZYDIS_REGCLASS_MMX;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR128:
        operand->size = 128;
        registerClass = ZYDIS_REGCLASS_XMM;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR256:
        operand->size = 256;
        registerClass = ZYDIS_REGCLASS_YMM;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_VR512:
        operand->size = 512;
        registerClass = ZYDIS_REGCLASS_ZMM;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MSKR:
        operand->size = 64;
        registerClass = ZYDIS_REGCLASS_MASK;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_BNDR:
        operand->size = 128;
        registerClass = ZYDIS_REGCLASS_BOUND;
        break;
    default:
        break;
    }
    if (registerClass != ZYDIS_REGCLASS_INVALID)
    {
        switch (encoding)
        {
        case ZYDIS_OPERAND_ENCODING_REG:
            ZYDIS_ASSERT(info->details.modrm.isDecoded);
            return ZydisDecodeOperandRegister(info, operand, registerClass, 
                (info->details.internal.R2 << 4) | 
                (info->details.internal.R  << 3) | info->details.modrm.reg);
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
                (info->details.internal.B << 3) | registerId);
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
                    (info->details.internal.V2 << 4) | (0x0F & ~info->details.evex.vvvv));
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
            ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 8, ZYDIS_FALSE));
            ZYDIS_CHECK(ZydisDecodeOperandRegister(info, operand, registerClass, 
                (operand->imm.value.ubyte & 0xF0) >> 4));
            operand->imm.dataSize = 0;
            operand->imm.dataOffset = 0;
            operand->imm.value.uqword = 0;
            return ZYDIS_STATUS_SUCCESS;
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
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM8:
        operand->size = 8;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM16:
        operand->size = 16;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST2:
        info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_2;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST4:
        if (info->avx.broadcast == ZYDIS_AVX512_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_4;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST8:
        if (info->avx.broadcast == ZYDIS_AVX512_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_8;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST16:
        if (info->avx.broadcast == ZYDIS_AVX512_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_16;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM32:
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST2:
        info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_2;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST4:
        if (info->avx.broadcast == ZYDIS_AVX512_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_4;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST8:
        if (info->avx.broadcast == ZYDIS_AVX512_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_8;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST16:
        if (info->avx.broadcast == ZYDIS_AVX512_BCSTMODE_INVALID) 
        {
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_16;
        }
    case ZYDIS_SEM_OPERAND_TYPE_MEM64:
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM80:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 80;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID);
    case ZYDIS_SEM_OPERAND_TYPE_MEM112:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 112;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID);
    case ZYDIS_SEM_OPERAND_TYPE_MEM128:
        operand->size = 128;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM224:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 224;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID);
    case ZYDIS_SEM_OPERAND_TYPE_MEM256:
        operand->size = 256;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM512:
        operand->size = 512;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_M1616:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 32;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID);
    case ZYDIS_SEM_OPERAND_TYPE_M1632:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 48;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID);
    case ZYDIS_SEM_OPERAND_TYPE_M1664:
        ZYDIS_ASSERT(evexCD8Scale == 0);
        operand->size = 80;
        return ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID);
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBX:
        vsibBaseRegister = ZYDIS_REGISTER_XMM0;
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBY:
        vsibBaseRegister = ZYDIS_REGISTER_YMM0;
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBZ:
        vsibBaseRegister = ZYDIS_REGISTER_ZMM0;
        operand->size = 32;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBX:
        vsibBaseRegister = ZYDIS_REGISTER_XMM0;
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBY:
        vsibBaseRegister = ZYDIS_REGISTER_YMM0;
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBZ:
        vsibBaseRegister = ZYDIS_REGISTER_ZMM0;
        operand->size = 64;
        ZYDIS_CHECK(ZydisDecodeOperandModrmRm(decoder, info, operand, ZYDIS_REGCLASS_INVALID));
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
            return ZYDIS_STATUS_INVALID_VSIB;
        }
        switch (operand->mem.addressSize)
        {
        case 16:
            return ZYDIS_STATUS_INVALID_VSIB;
        case 32:
            operand->mem.index = operand->mem.index - ZYDIS_REGISTER_EAX + vsibBaseRegister + 
                ((info->details.evex.V2 == 1) ? 0 : 16);
            break;
        case 64:
            operand->mem.index = operand->mem.index - ZYDIS_REGISTER_RAX + vsibBaseRegister + 
                ((info->details.evex.V2 == 1) ? 0 : 16);
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        return ZYDIS_STATUS_SUCCESS;
    }

    // Immediate operands
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_FIXED1:
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        operand->type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
        operand->size = 8;
        operand->imm.isSigned = ZYDIS_TRUE;
        operand->imm.value.ubyte = 1;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_REL8:
        info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
        operand->imm.isRelative = ZYDIS_TRUE;
    case ZYDIS_SEM_OPERAND_TYPE_IMM8:
        operand->size = 8;
        operand->imm.isSigned = ZYDIS_TRUE;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_IMM8U:
        operand->size = 8;
        operand->imm.isSigned = ZYDIS_FALSE;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_REL16:
        info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
        operand->imm.isRelative = ZYDIS_TRUE;
    case ZYDIS_SEM_OPERAND_TYPE_IMM16:
        operand->size = 16;
        operand->imm.isSigned = ZYDIS_TRUE;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_REL32:
        info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
        operand->imm.isRelative = ZYDIS_TRUE;
    case ZYDIS_SEM_OPERAND_TYPE_IMM32:
        operand->size = 32;
        operand->imm.isSigned = ZYDIS_TRUE;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_REL64:
        info->attributes |= ZYDIS_ATTRIB_IS_RELATIVE;
        operand->imm.isRelative = ZYDIS_TRUE;
    case ZYDIS_SEM_OPERAND_TYPE_IMM64:
        operand->size = 64;
        operand->imm.isSigned = ZYDIS_TRUE;
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
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, ZYDIS_FALSE));
        operand->ptr.offset = operand->imm.value.uword;
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, ZYDIS_FALSE));
        operand->ptr.segment = operand->imm.value.uword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        operand->type = ZYDIS_OPERAND_TYPE_POINTER;
        operand->size = 32;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_PTR1632:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 32, ZYDIS_FALSE));
        operand->ptr.offset = operand->imm.value.udword;
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, ZYDIS_FALSE));
        operand->ptr.segment = operand->imm.value.uword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        operand->type = ZYDIS_OPERAND_TYPE_POINTER;
        operand->size = 48;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_PTR1664:
        // TODO: ?
        assert(0);
        return ZYDIS_STATUS_SUCCESS;
    default:
        break;
    }

    // Moffs
    switch (type)
    {
    case ZYDIS_SEM_OPERAND_TYPE_MOFFS16:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 16, ZYDIS_FALSE));
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->size = 16;
        operand->mem.disp.dataSize = 16;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->mem.disp.value.sword = operand->imm.value.sword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_MOFFS32:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 32, ZYDIS_FALSE));
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->size = 32;
        operand->mem.disp.dataSize = 32;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->mem.disp.value.sdword = operand->imm.value.sdword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_SEM_OPERAND_TYPE_MOFFS64:
        ZYDIS_CHECK(ZydisDecodeOperandImmediate(decoder, info, operand, 64, ZYDIS_FALSE));
        operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
        operand->size = 64;
        operand->mem.disp.dataSize = 64;
        operand->mem.disp.dataOffset = operand->imm.dataOffset;
        operand->mem.disp.value.sqword = operand->imm.value.sqword;
        operand->imm.dataSize = 0;
        operand->imm.dataOffset = 0;
        operand->imm.value.uqword = 0;
        return ZYDIS_STATUS_SUCCESS;
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
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_ADDRESSSIZE;
        if (info->details.prefixes.has67)
        {
            info->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
        }
        switch (decoder->disassemblerMode)
        {
        case ZYDIS_DISASSEMBLER_MODE_16BIT:
            operand->mem.addressSize = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 32 : 16;
            break;
        case ZYDIS_DISASSEMBLER_MODE_32BIT:
            operand->mem.addressSize = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 16 : 32;
            break;
        case ZYDIS_DISASSEMBLER_MODE_64BIT:
            operand->mem.addressSize = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 32 : 64;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        registerClass = ZYDIS_REGCLASS_INVALID;
        switch (operand->mem.addressSize)
        {
        case 16:
            registerClass = ZYDIS_REGCLASS_GPR16;
            break;
        case 32:
            registerClass = ZYDIS_REGCLASS_GPR32;
            break;
        case 64:
            registerClass = ZYDIS_REGCLASS_GPR64;
            break;
        default:
            ZYDIS_UNREACHABLE;
        } 
        operand->visibility = ZYDIS_OPERAND_VISIBILITY_IMPLICIT;
        if (srcidx)
        {   
            ZYDIS_CHECK(ZydisDecodeOperandRegister(info, operand, registerClass, 6));
            operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
            operand->size = srcidx;
            operand->mem.segment = ZYDIS_REGISTER_DS;
            operand->mem.base = operand->reg;
            operand->reg = ZYDIS_REGISTER_NONE; 
            return ZYDIS_STATUS_SUCCESS;
        }
        if (dstidx)
        {   
            ZYDIS_CHECK(ZydisDecodeOperandRegister(info, operand, registerClass, 7));
            operand->type = ZYDIS_OPERAND_TYPE_MEMORY;
            operand->size = dstidx;
            operand->mem.base = operand->reg;
            operand->mem.segment = ZYDIS_REGISTER_ES;
            operand->reg = ZYDIS_REGISTER_NONE;
            return ZYDIS_STATUS_SUCCESS;
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Decodes all instruction-operands.
 *
 * @param   decoder         A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info            A pointer to the @c ZydisInstructionInfo struct.
 * @param   operands        A pointer to the first operand-definition of the instruction.
 * @param   operandCount    The number of operands.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisDecodeOperands(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info, const ZydisOperandDefinition* operands, uint8_t operandCount)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operands);
    ZYDIS_ASSERT((operandCount > 0) && (operandCount < 6));

    info->operandCount = operandCount;
    for (uint8_t i = 0; i < operandCount; ++i)
    {
        if (operands[i].type == ZYDIS_SEM_OPERAND_TYPE_UNUSED)
        {
            break;
        }
        info->operands[i].id = i;
        ZYDIS_CHECK(ZydisDecodeOperand(decoder, info, &info->operands[i], operands[i].type, 
            operands[i].encoding));

        // temp
        info->operands[i].temp = operands[i].type;

        info->operands[i].encoding = operands[i].encoding;
        info->operands[i].action = operands[i].action;
        // Adjust segment register for memory operands
        if (info->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            info->attributes |= ZYDIS_ATTRIB_ACCEPTS_SEGMENT;
            switch (decoder->lastSegmentPrefix)
            {
            case 0x2E:
                info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_CS;
                info->operands[i].mem.segment = ZYDIS_REGISTER_CS;
                decoder->lastSegmentPrefix = 0;
                break;
            case 0x36:
                info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_SS;
                info->operands[i].mem.segment = ZYDIS_REGISTER_SS;
                decoder->lastSegmentPrefix = 0;
                break;
            case 0x3E:
                info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_DS;
                info->operands[i].mem.segment = ZYDIS_REGISTER_DS;
                decoder->lastSegmentPrefix = 0;
                break;
            case 0x26:
                info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_ES;
                info->operands[i].mem.segment = ZYDIS_REGISTER_ES;
                decoder->lastSegmentPrefix = 0;
                break;
            case 0x64:
                info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_FS;
                info->operands[i].mem.segment = ZYDIS_REGISTER_FS;
                decoder->lastSegmentPrefix = 0;
                break;
            case 0x65:
                info->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_GS;
                info->operands[i].mem.segment = ZYDIS_REGISTER_GS;
                decoder->lastSegmentPrefix = 0;
                break;
            default:
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
        }
    }
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Applies additional information from the instruction-definition to the 
 *          @c ZydisInstructionInfo struct.
 * 
 * @param   decoder A pointer to the @c ZydisInstructionDecoder decoder instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct.
 */
static void ZydisApplyInstructionDefinition(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(info->details.internal.definition);

    const ZydisInstructionDefinition* definition = 
        (ZydisInstructionDefinition*)info->details.internal.definition;

    // Set prefix-flags
    if (definition->acceptsLock)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_LOCK;
        if (info->details.prefixes.hasF0)
        {
            info->attributes |= ZYDIS_ATTRIB_HAS_LOCK;
        }
    }
    if (definition->acceptsREP)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_REP;
    }
    if (definition->acceptsREPEREPNE)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_REPE | ZYDIS_ATTRIB_ACCEPTS_REPNE;
    }
    if (definition->acceptsBOUND)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_BOUND;    
    }
    if (definition->acceptsXACQUIRE)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_XACQUIRE;    
    }
    if (definition->acceptsXRELEASE)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_XRELEASE;    
    }
    if (definition->acceptsHLEWithoutLock)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_HLE_WITHOUT_LOCK;
    } 
    switch (decoder->hasUnusedPrefixF2F3)
    {
    case 0xF2:
        if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_REPNE)
        {
            info->attributes |= ZYDIS_ATTRIB_HAS_REPNE;
            break;
        }
        if (info->attributes & ZYDIS_ATTRIB_ACCEPTS_XACQUIRE)
        {
            if ((info->attributes & ZYDIS_ATTRIB_HAS_LOCK) || (definition->acceptsHLEWithoutLock))
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
            if ((info->attributes & ZYDIS_ATTRIB_HAS_LOCK) || (definition->acceptsHLEWithoutLock))
            {
                info->attributes |= ZYDIS_ATTRIB_HAS_XRELEASE;
                break;
            }
        }
        break;
    default:
        break;
    }
 
    if (definition->acceptsBranchHints)
    {
        info->attributes |= ZYDIS_ATTRIB_ACCEPTS_BRANCH_HINTS;
        switch (decoder->lastSegmentPrefix)
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
    }
    
    
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisNodeHandlerOpcode(ZydisInstructionDecoder* decoder, 
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
                if ((nextInput & 0xF0) >= 0xC0)
                {
                    if (info->attributes & ZYDIS_ATTRIB_HAS_REX)
                    {
                        return ZYDIS_STATUS_ILLEGAL_REX;
                    }
                    if ((decoder->hasUnusedPrefixF2F3) || (decoder->hasUnusedPrefix66))
                    {
                        return ZYDIS_STATUS_ILLEGAL_LEGACY_PFX;
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
                        ZYDIS_CHECK(
                            ZydisDecodeVEX(info->opcode, prefixBytes[0], prefixBytes[1], info));
                        info->opcodeMap = info->details.vex.m_mmmm;
                        break;
                    case 0x62:
                        // Decode evex-prefix
                        info->encoding = ZYDIS_INSTRUCTION_ENCODING_EVEX;
                        ZYDIS_CHECK(
                            ZydisDecodeEVEX(prefixBytes[0], prefixBytes[1], prefixBytes[2], info));
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
                    if (info->attributes & ZYDIS_ATTRIB_HAS_REX)
                    {
                        return ZYDIS_STATUS_ILLEGAL_REX;
                    }
                    if ((decoder->hasUnusedPrefixF2F3) || (decoder->hasUnusedPrefix66))
                    {
                        return ZYDIS_STATUS_ILLEGAL_LEGACY_PFX;
                    }
                    uint8_t prefixBytes[2];
                    // Read additional xop-prefix data
                    ZYDIS_ASSERT(!info->details.xop.isDecoded);
                    ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[0]));
                    ZYDIS_CHECK(ZydisInputNext(decoder, info, &prefixBytes[1]));
                    // Decode xop-prefix
                    info->encoding = ZYDIS_INSTRUCTION_ENCODING_XOP;
                    ZYDIS_CHECK(ZydisDecodeXOP(prefixBytes[0], prefixBytes[1], info));
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
        return ZYDIS_STATUS_SUCCESS;
    default:
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &info->opcode));
        break;
    }

    *index = info->opcode; 
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerXop(ZydisInstructionInfo* info, uint16_t* index)
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

static ZydisStatus ZydisNodeHandlerMode(ZydisInstructionDecoder* decoder, 
    uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(index);

    *index = (decoder->disassemblerMode == ZYDIS_DISASSEMBLER_MODE_64BIT) ? 0 : 1;
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerVex(ZydisInstructionInfo* info, uint16_t* index)
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
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerMandatoryPrefix(ZydisInstructionDecoder* decoder, 
    uint16_t* index)
{
    ZYDIS_ASSERT(index);

    // 0x66 has precedence over 0xF2 and 0xF3
    if (decoder->hasUnusedPrefix66)
    {
        decoder->hasUnusedPrefix66 = 0;
        *index = 1;      
    } else
    {
        switch (decoder->hasUnusedPrefixF2F3)
        {
        case 0xF3:
            decoder->hasUnusedPrefixF2F3 = 0;
            *index = 2;
            
            break;
        case 0xF2:
            decoder->hasUnusedPrefixF2F3 = 0;
            *index = 3;         
            break;
        default:
            break;
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerModrmMod(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &modrmByte));
        ZydisDecodeModRM(modrmByte, info);               
    }
    *index = (info->details.modrm.mod == 0x3) ? 1 : 0;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerModrmReg(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &modrmByte));
        ZydisDecodeModRM(modrmByte, info);               
    }
    *index = info->details.modrm.reg;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerModrmRm(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    if (!info->details.modrm.isDecoded)
    {
        uint8_t modrmByte;
        ZYDIS_CHECK(ZydisInputNext(decoder, info, &modrmByte));
        ZydisDecodeModRM(modrmByte, info);                
    }
    *index = info->details.modrm.rm;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerOperandSize(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    info->attributes |= ZYDIS_ATTRIB_ACCEPTS_OPERANDSIZE;
    if (decoder->hasUnusedPrefix66)
    {
        info->attributes |= ZYDIS_ATTRIB_HAS_OPERANDSIZE;
        decoder->hasUnusedPrefix66 = 0;
    }

    switch (decoder->disassemblerMode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_OPERANDSIZE) ? 1 : 0;
        break;
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_OPERANDSIZE) ? 0 : 1;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerAddressSize(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    info->attributes |= ZYDIS_ATTRIB_ACCEPTS_ADDRESSSIZE;
    if (info->details.prefixes.has67)
    {
        info->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
    }

    switch (decoder->disassemblerMode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 1 : 0;
        break;
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 0 : 1;
        break;
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        *index = (info->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) ? 1 : 2;
        break;
    default: 
        ZYDIS_UNREACHABLE;
    }
    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisNodeHandlerRexW(ZydisInstructionInfo* info, uint16_t* index)
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
    *index = info->details.internal.W;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerVexL(ZydisInstructionInfo* info, uint16_t* index)
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
    *index = info->details.internal.L;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisNodeHandlerEvexL2(ZydisInstructionInfo* info, uint16_t* index)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(index);

    ZYDIS_ASSERT(info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
    ZYDIS_ASSERT(info->details.evex.isDecoded);
    *index = info->details.evex.L2;
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

/**
 * @brief   Uses the instruction-table to decode the bytestream until an instruction-definition
 *          is found.
 *
 * @param   decoder A pointer to the instruction decoder instance.
 * @param   info    A pointer to the instruction-info struct.
 *
 * @return  A zydis decoder status code.
 */
static ZydisStatus ZydisDecodeOpcode(ZydisInstructionDecoder* decoder, 
    ZydisInstructionInfo* info)
{
    ZYDIS_ASSERT(decoder);
    ZYDIS_ASSERT(info);

    // Iterate through the instruction table
    const ZydisInstructionTableNode* node = ZydisInstructionTableGetRootNode();
    ZydisInstructionTableNodeType nodeType;
    do
    {
        nodeType = node->type;
        uint16_t index = 0;
        ZydisStatus status = 0;
        switch (nodeType)
        {
        case ZYDIS_NODETYPE_INVALID:
        {
            return ZYDIS_STATUS_DECODING_ERROR;
        }
        case ZYDIS_NODETYPE_DEFINITION_0OP:
        case ZYDIS_NODETYPE_DEFINITION_1OP:
        case ZYDIS_NODETYPE_DEFINITION_2OP:
        case ZYDIS_NODETYPE_DEFINITION_3OP:
        case ZYDIS_NODETYPE_DEFINITION_4OP:
        case ZYDIS_NODETYPE_DEFINITION_5OP:
        {   
            const ZydisInstructionDefinition* definition = NULL;
            const ZydisOperandDefinition* operands = NULL;
            uint8_t operandCount;
            ZydisInstructionTableGetDefinition(node, &definition, &operands, &operandCount);

            ZYDIS_ASSERT(definition);
            ZYDIS_ASSERT(operands || (operandCount == 0));

            info->mnemonic = (ZydisInstructionMnemonic)definition->mnemonic;
            info->details.internal.definition = (void*)definition;
            ZydisApplyInstructionDefinition(decoder, info);

            if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW)
            {
                // Save input-buffer state and decode dummy operands
                const uint8_t* buffer = decoder->input.buffer;
                size_t bufferLen = decoder->input.bufferLen;
                uint8_t length = info->length;
                ZYDIS_ASSERT(operandCount == 2);
                ZYDIS_CHECK(ZydisDecodeOperands(decoder, info, operands, operandCount));
                // Read actual 3dnow opcode
                ZYDIS_CHECK(ZydisInputNext(decoder, info, &info->opcode));
                // Restore input-buffer state
                decoder->input.buffer = buffer;
                decoder->input.bufferLen = bufferLen;
                info->length = length;
                node = ZydisInstructionTableGetRootNode();
                node = ZydisInstructionTableGetChildNode(node, 0x0F);
                node = ZydisInstructionTableGetChildNode(node, 0x0F);
                node = ZydisInstructionTableGetChildNode(node, info->opcode);
                if (node->type == ZYDIS_NODETYPE_INVALID)
                {
                    return ZYDIS_STATUS_DECODING_ERROR;        
                }
                node = ZydisInstructionTableGetChildNode(node, 
                    (info->details.modrm.mod == 0x3) ? 1 : 0);

                // Decode actual operands and fix the instruction-info 
                ZydisInstructionTableGetDefinition(node, &definition, &operands, &operandCount);
                ZYDIS_ASSERT(definition);
                ZYDIS_ASSERT(operands && (operandCount == 2));

                info->mnemonic = (ZydisInstructionMnemonic)definition->mnemonic;
                info->details.internal.definition = (void*)definition;
                ZydisApplyInstructionDefinition(decoder, info);

                ZYDIS_CHECK(ZydisDecodeOperands(decoder, info, operands, operandCount));
                 
                return ZydisInputNext(decoder, info, &info->opcode);
            }

            if (operandCount != 0)
            {
                ZYDIS_CHECK(ZydisDecodeOperands(decoder, info, operands, operandCount));
            }

            return ZYDIS_STATUS_SUCCESS;
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
            status = ZydisNodeHandlerMandatoryPrefix(decoder, &index);
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
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZydisStatus ZydisDecoderInitInstructionDecoder(ZydisInstructionDecoder* decoder,
    ZydisDisassemblerMode disassemblerMode)
{
    if (!decoder || (
        (disassemblerMode != ZYDIS_DISASSEMBLER_MODE_16BIT) && 
        (disassemblerMode != ZYDIS_DISASSEMBLER_MODE_32BIT) && 
        (disassemblerMode != ZYDIS_DISASSEMBLER_MODE_64BIT)))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    decoder->disassemblerMode = disassemblerMode;
    decoder->input.buffer = NULL;
    decoder->input.bufferLen = 0;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisDecoderDecodeInstruction(ZydisInstructionDecoder* decoder,
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, ZydisInstructionInfo* info)
{
    return ZydisDecoderDecodeInstructionEx(decoder, buffer, bufferLen, instructionPointer, 0, info);
}

ZydisStatus ZydisDecoderDecodeInstructionEx(ZydisInstructionDecoder* decoder,
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, ZydisDecoderFlags flags, 
    ZydisInstructionInfo* info)
{
    (void)flags;

    if (!decoder)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    if (!buffer || (bufferLen == 0))
    {
        return ZYDIS_STATUS_NO_MORE_DATA;
    }
    
    decoder->input.buffer = (uint8_t*)buffer;
    decoder->input.bufferLen = bufferLen;
    decoder->hasUnusedPrefix66 = 0;
    decoder->hasUnusedPrefixF2F3 = 0;
    decoder->lastSegmentPrefix = 0;
    decoder->imm8initialized = ZYDIS_FALSE;

    void* userData = info->userData;
    memset(info, 0, sizeof(*info));   
    info->mode = decoder->disassemblerMode;
    info->instrAddress = instructionPointer;
    info->userData = userData;

    ZYDIS_CHECK(ZydisCollectOptionalPrefixes(decoder, info));
    ZYDIS_CHECK(ZydisDecodeOpcode(decoder, info));

    // TODO: The index, dest and mask regs for AVX2 gathers must be different.
    // TODO: More EVEX UD conditions (page 81)
    // Set AVX-512 info
     if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX)
    {
        const ZydisInstructionDefinition* definition = 
            (ZydisInstructionDefinition*)info->details.internal.definition;

        switch (definition->evexContext)
        {
        case ZYDIS_EVEX_CONTEXT_INVALID:
            if (info->details.evex.b)
            {
                return ZYDIS_STATUS_DECODING_ERROR; // TODO:
            }
            break;
        case ZYDIS_EVEX_CONTEXT_BC:
            break;
        case ZYDIS_EVEX_CONTEXT_RC:
            info->avx.roundingMode = 
                (((info->details.evex.L2 & 0x01) << 1) | info->details.evex.L) + 1;
            break;
        case ZYDIS_EVEX_CONTEXT_SAE:
            info->avx.hasSAE = ZYDIS_TRUE;
            break;
        default:
            info->avx.broadcast = ZYDIS_AVX512_BCSTMODE_INVALID;
        }

        switch (definition->evexMaskPolicy)
        {
        case ZYDIS_AVX512_MASKPOLICY_MASK_ACCEPTED:
            info->avx.maskRegister = ZYDIS_REGISTER_K0 + info->details.evex.aaa;
            break;
        case ZYDIS_AVX512_MASKPOLICY_MASK_REQUIRED:
            if (info->details.evex.aaa == 0)
            {
                return ZYDIS_STATUS_INVALID_MASK;
            }
            info->avx.maskRegister = ZYDIS_REGISTER_K0 + info->details.evex.aaa;
            break;
        case ZYDIS_AVX512_MASKPOLICY_MASK_FORBIDDEN:
            if (info->details.evex.aaa != 0)
            {
                return ZYDIS_STATUS_INVALID_MASK;
            }
            info->avx.maskRegister = ZYDIS_REGISTER_K0;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        if (info->details.evex.z)
        {
            if (!definition->evexZeroMaskAccepted)
            {
                return ZYDIS_STATUS_INVALID_MASK;    
            }
            info->avx.maskMode = ZYDIS_AVX512_MASKMODE_MERGE;
        } else
        {
            info->avx.maskMode = ZYDIS_AVX512_MASKMODE_MERGE;
        }
    }

    // Replace XCHG rAX, rAX with NOP alias
    if (info->mnemonic == ZYDIS_MNEMONIC_XCHG)
    {
        if (((info->operands[0].reg == ZYDIS_REGISTER_RAX) && 
            (info->operands[1].reg == ZYDIS_REGISTER_RAX)) || 
            ((info->operands[0].reg == ZYDIS_REGISTER_EAX) && 
            (info->operands[1].reg == ZYDIS_REGISTER_EAX)) ||
            ((info->operands[0].reg == ZYDIS_REGISTER_AX) && 
            (info->operands[1].reg == ZYDIS_REGISTER_AX)))
        {
            info->mnemonic = ZYDIS_MNEMONIC_NOP;
            info->operandCount = 0;
            memset(&info->operands[0], 0, sizeof(ZydisOperandInfo) * 2);
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
