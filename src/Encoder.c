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

#include <string.h>
#include <stdint.h>

/* ============================================================================================== */
/* Internal context                                                                               */
/* ============================================================================================== */

typedef struct ZydisEncoderTableOperand_
{
    ZydisOperandEncoding encoding;
} ZydisEncoderTableOperand;

typedef uint8_t ZydisModRMMod;

enum ZydisModRMMods
{
    ZYDIS_MODRM_MOD_NONE,
    ZYDIS_MODRM_MOD_REGISTER,
    ZYDIS_MODRM_MOD_MEMORY,
};

typedef uint8_t ZydisModeConstraint;

enum ZydisModeConstraints
{
    ZYDIS_MODE_CONSTR_NONE,
    ZYDIS_MODE_CONSTR_EXCLUDE64,
    ZYDIS_MODE_CONSTR_REQUIRE64,
};

typedef struct ZydisEncoderTableEntry_
{
    uint16_t mnemonic;
    uint8_t opcode;
    ZydisInstructionEncoding encoding;
    uint8_t operandCount;
    ZydisEncoderTableOperand operands[5];
    ZydisOpcodeMap map;
    ZydisInstructionAttributes mandatoryAttribs;
    ZydisModRMMod modRmMod;
    ZydisModeConstraint modeConstraint;
} ZydisEncoderTableEntry;

#include <Zydis/Internal/EncoderTable.inc>

/**
 * @brief   The encoder context struct.
 */
typedef struct ZydisInstructionEncoder_
{
    uint8_t* buffer;
    size_t bufferLen;
    size_t writeOffs;
    ZydisInstructionInfo* info;
    const ZydisEncoderTableEntry* matchingEntry;
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

static ZydisStatus ZydisEmitImm(ZydisInstructionEncoder* encoder, uint64_t imm, int bits)
{
    ZYDIS_ASSERT(bits == 8 || bits == 16 || bits == 32 || bits == 64);
    if (encoder->writeOffs + bits / 8 >= encoder->bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    // TODO: bswap on big-endian
    switch (bits)
    {
    case 8:  *(uint8_t* )&encoder->buffer[encoder->writeOffs++] = (uint8_t )imm; break;
    case 16: *(uint16_t*)&encoder->buffer[encoder->writeOffs++] = (uint16_t)imm; break;
    case 32: *(uint32_t*)&encoder->buffer[encoder->writeOffs++] = (uint32_t)imm; break;
    case 64: *(uint64_t*)&encoder->buffer[encoder->writeOffs++] = (uint64_t)imm; break;
    default: ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeLegacyPrefixes(ZydisInstructionEncoder* encoder)
{
    ZYDIS_ASSERT(encoder);
    ZydisInstructionAttributes attribs = encoder->info->attributes;

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
        (encoder->info->details.evex.R    & 0x01) << 7 |
        (encoder->info->details.evex.X    & 0x01) << 6 |
        (encoder->info->details.evex.B    & 0x01) << 5 |
        (encoder->info->details.evex.R2   & 0x01) << 4 |
        (encoder->info->details.evex.mm   & 0x03) << 0
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

static ZydisStatus ZydisEncodeXOP(ZydisInstructionEncoder* encoder)
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

static ZydisStatus ZydisEncodeModRM(ZydisInstructionEncoder* encoder)
{
    ZYDIS_ASSERT(encoder);
    ZYDIS_CHECK(ZydisEmitByte(
        encoder,
        (encoder->info->details.modrm.mod & 0x03) << 6 |
        (encoder->info->details.modrm.reg & 0x07) << 3 |
        (encoder->info->details.modrm.rm  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeSIB(ZydisInstructionEncoder* encoder)
{
    ZYDIS_ASSERT(encoder);
    ZYDIS_CHECK(ZydisEmitByte(
        encoder,
        (encoder->info->details.sib.scale & 0x03) << 6 |
        (encoder->info->details.sib.index & 0x07) << 3 |
        (encoder->info->details.sib.base  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEncodeOpcode(ZydisInstructionEncoder* encoder)
{
    ZYDIS_ASSERT(encoder);
    ZYDIS_ASSERT(encoder->matchingEntry);

    // Put opcode extension prefix(es), if required.
    switch (encoder->matchingEntry->map)
    {
    case ZYDIS_OPCODE_MAP_0F:
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x0F));
        break;
    case ZYDIS_OPCODE_MAP_0F38:
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x0F));
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x38));
        break;
    case ZYDIS_OPCODE_MAP_0F3A:
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x0F));
        ZYDIS_CHECK(ZydisEmitByte(encoder, 0x3A));
        break;
    case ZYDIS_OPCODE_MAP_XOP8:
    case ZYDIS_OPCODE_MAP_XOP9:
    case ZYDIS_OPCODE_MAP_XOPA:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        break;
    case ZYDIS_OPCODE_MAP_DEFAULT:
        break; // Nothing to do.
    default:
        ZYDIS_UNREACHABLE;
    }

    // Emit actual opcode.
    ZYDIS_CHECK(ZydisEmitByte(encoder, encoder->matchingEntry->opcode));

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareOperand(ZydisInstructionEncoder* encoder,
    ZydisOperandInfo* operand)
{
    switch (operand->encoding)
    {
    case ZYDIS_OPERAND_ENCODING_NONE:
        break; // Nothing to do.
    case ZYDIS_OPERAND_ENCODING_REG:
    {
        int16_t reg = ZydisRegisterGetId(operand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        encoder->info->details.modrm.reg = reg & 0x07;
        encoder->info->details.rex.R = (reg & 0x08) >> 3;
        encoder->info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
        if (encoder->info->details.rex.R)
        {
            encoder->info->attributes |= ZYDIS_ATTRIB_HAS_REX;
        }
    } break;
    case ZYDIS_OPERAND_ENCODING_RM:
    case ZYDIS_OPERAND_ENCODING_RM_CD2:
    case ZYDIS_OPERAND_ENCODING_RM_CD4:
    case ZYDIS_OPERAND_ENCODING_RM_CD8:
    case ZYDIS_OPERAND_ENCODING_RM_CD16:
    case ZYDIS_OPERAND_ENCODING_RM_CD32:
    case ZYDIS_OPERAND_ENCODING_RM_CD64:
    {
        // Memory operand?
        if (operand->reg == ZYDIS_REGISTER_NONE)
        {
            int32_t divisor = 1;
            switch (operand->encoding)
            {
                case ZYDIS_OPERAND_ENCODING_RM:      divisor = 1;  break;
                case ZYDIS_OPERAND_ENCODING_RM_CD2:  divisor = 2;  break;
                case ZYDIS_OPERAND_ENCODING_RM_CD4:  divisor = 4;  break;
                case ZYDIS_OPERAND_ENCODING_RM_CD8:  divisor = 8;  break;
                case ZYDIS_OPERAND_ENCODING_RM_CD16: divisor = 16; break;
                case ZYDIS_OPERAND_ENCODING_RM_CD32: divisor = 32; break;
                case ZYDIS_OPERAND_ENCODING_RM_CD64: divisor = 64; break;
                default: ZYDIS_UNREACHABLE;
            }

            // Has compressed disp encoding and is compression possible?
            int32_t* sdword = &operand->mem.disp.value.sdword;
            encoder->info->details.modrm.mod = 0x02 /* 32 bit disp */;
            if (divisor != 1 &&
                *sdword % divisor == 0 &&
                *sdword / divisor <= INT8_MAX &&
                *sdword / divisor >= INT8_MIN)
            {
                encoder->info->details.modrm.mod = 0x01 /* 8 bit disp */;
                *sdword /= divisor;
            }
            // Nope, regular encoding. Does it fit a byte anyway?
            else if (*sdword <= INT8_MAX && *sdword >= INT8_MIN)
            {
                encoder->info->details.modrm.mod = 0x01 /* 8 bit disp */;
            }
        }
        // Nope, register.
        else
        {
            int16_t reg = ZydisRegisterGetId(operand->reg);
            if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
            encoder->info->details.modrm.reg = reg & 0x07;
            encoder->info->details.rex.B = (reg & 0x08) >> 3;
            encoder->info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
            if (encoder->info->details.rex.B)
            {
                encoder->info->attributes |= ZYDIS_ATTRIB_HAS_REX;
            }
            encoder->info->details.modrm.mod = 0x03;
        }
    }
    case ZYDIS_OPERAND_ENCODING_OPCODE:
        break; // TODO
    case ZYDIS_OPERAND_ENCODING_VVVV:
        break; // TODO
    case ZYDIS_OPERAND_ENCODING_AAA:
        break; // TODO
    case ZYDIS_OPERAND_ENCODING_IMM8_LO:
    case ZYDIS_OPERAND_ENCODING_IMM8_HI:
    case ZYDIS_OPERAND_ENCODING_IMM8:
    case ZYDIS_OPERAND_ENCODING_IMM16:
    case ZYDIS_OPERAND_ENCODING_IMM32:
    case ZYDIS_OPERAND_ENCODING_IMM64:
        // Nothing to do here, we put those in a later stage.
        // TODO: moffs
        break; 
    default:
        ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFindMatchingDef(const ZydisInstructionInfo* info,
    const ZydisEncoderTableEntry** matchingEntry)
{
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(matchingEntry);

    // Locate entries with matching mnemonic.
    // TODO: do binary search / hash based lookup instead
    for (size_t i = 0; i < sizeof(kEncoderTable) / sizeof(kEncoderTable[0]); ++i)
    {
        const ZydisEncoderTableEntry* curEntry = &kEncoderTable[i];
        if (curEntry->mnemonic != info->mnemonic ||
            curEntry->operandCount != info->operandCount ||
            curEntry->encoding != info->encoding ||
            (info->mode == ZYDIS_DISASSEMBLER_MODE_64BIT && 
                curEntry->modeConstraint == ZYDIS_MODE_CONSTR_EXCLUDE64) ||
            (info->mode != ZYDIS_DISASSEMBLER_MODE_64BIT && 
                curEntry->modeConstraint == ZYDIS_MODE_CONSTR_REQUIRE64))
        {
            continue;
        }

        // Check operands.
        for (size_t k = 0; k < curEntry->operandCount; ++k)
        {
            const ZydisEncoderTableOperand* curEncoderOp = &curEntry->operands[k];
            const ZydisOperandInfo* curReqOp = &info->operands[k];
            if (curEncoderOp->encoding != curReqOp->encoding) goto continueTopLevel;
        }

        // Still here? We found our entry!
        *matchingEntry = curEntry;
        return ZYDIS_STATUS_SUCCESS;

    continueTopLevel:
        ;
    }

    return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
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
    memset(&encoder, 0, sizeof(encoder));
    memset(&info->details, 0, sizeof(info->details));
    encoder.buffer = (uint8_t*)buffer;
    encoder.bufferLen = bufferLen;
    encoder.writeOffs = 0;
    encoder.info = info;

    // Mask out attributes that can't be set explicitly by user.
    info->attributes &= ZYDIS_USER_ENCODABLE_ATTRIB_MASK;

    // Search matching instruction, collect information about what needs to be
    // encoded, what prefixes are required etc..
    ZYDIS_CHECK(ZydisFindMatchingDef(info, &encoder.matchingEntry));
    info->opcode = encoder.matchingEntry->opcode;
    info->attributes |= encoder.matchingEntry->mandatoryAttribs;

    // Analyze and prepare operands.
    for (size_t i = 0; i < encoder.matchingEntry->operandCount; ++i)
    {
        ZYDIS_CHECK(ZydisPrepareOperand(&encoder, &info->operands[i]));
    }
    
    // Do actual encoding work.
    ZYDIS_CHECK(ZydisEncodeLegacyPrefixes(&encoder));
    if (info->attributes & ZYDIS_ATTRIB_HAS_REX  ) ZYDIS_CHECK(ZydisEncodeREX  (&encoder));
    if (info->attributes & ZYDIS_ATTRIB_HAS_VEX  ) ZYDIS_CHECK(ZydisEncodeVEX  (&encoder));
    if (info->attributes & ZYDIS_ATTRIB_HAS_EVEX ) ZYDIS_CHECK(ZydisEncodeEVEX (&encoder));
    if (info->attributes & ZYDIS_ATTRIB_HAS_XOP  ) ZYDIS_CHECK(ZydisEncodeXOP  (&encoder));
    ZYDIS_CHECK(ZydisEncodeOpcode(&encoder));
    if (info->attributes & ZYDIS_ATTRIB_HAS_MODRM) ZYDIS_CHECK(ZydisEncodeModRM(&encoder));
    if (info->attributes & ZYDIS_ATTRIB_HAS_SIB  ) ZYDIS_CHECK(ZydisEncodeSIB  (&encoder));

    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
