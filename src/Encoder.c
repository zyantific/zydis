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
#include <Zydis/Internal/InstructionTable.h>

#include <string.h>
#include <stdint.h>

/* ============================================================================================== */
/* Internal context                                                                               */
/* ============================================================================================== */

typedef struct ZydisEncoderTableOperand_
{
    ZydisOperandEncoding encoding;
    ZydisSemanticOperandType type;
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
typedef struct ZydisEncoderContext_
{
    uint8_t* buffer;
    size_t bufferLen;
    size_t writeOffs;
    ZydisInstructionInfo* info;
    const ZydisEncoderTableEntry* matchingEntry;
    uint8_t dispBitSize;
    uint64_t disp;
    uint8_t immBitSizes[2];
    uint64_t imms[2];
} ZydisEncoderContext;

/* ============================================================================================== */
/* Internal helpers                                                                               */
/* ============================================================================================== */

static ZydisStatus ZydisEmitByte(ZydisEncoderContext* ctx, uint8_t byte)
{
    if (ctx->writeOffs + 1 >= ctx->bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ctx->buffer[ctx->writeOffs++] = byte;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitImm(ZydisEncoderContext* ctx, uint64_t imm, int bits)
{
    ZYDIS_ASSERT(bits == 8 || bits == 16 || bits == 32 || bits == 64);
    size_t newWriteOffs = ctx->writeOffs + bits / 8;
    if (newWriteOffs >= ctx->bufferLen ||
        newWriteOffs > ZYDIS_MAX_INSTRUCTION_LENGTH)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    // TODO: bswap on big-endian
    switch (bits)
    {
    case 8:  *(uint8_t* )&ctx->buffer[ctx->writeOffs] = (uint8_t )imm; break;
    case 16: *(uint16_t*)&ctx->buffer[ctx->writeOffs] = (uint16_t)imm; break;
    case 32: *(uint32_t*)&ctx->buffer[ctx->writeOffs] = (uint32_t)imm; break;
    case 64: *(uint64_t*)&ctx->buffer[ctx->writeOffs] = (uint64_t)imm; break;
    default: ZYDIS_UNREACHABLE;
    }

    ctx->writeOffs = newWriteOffs;
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitLegacyPrefixes(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZydisInstructionAttributes attribs = ctx->info->attributes;

    if (attribs & ZYDIS_ATTRIB_HAS_LOCK) 
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xF0));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_REP | ZYDIS_ATTRIB_HAS_REPE | ZYDIS_ATTRIB_HAS_XRELEASE)) 
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xF3));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_REPNE | ZYDIS_ATTRIB_HAS_BOUND | ZYDIS_ATTRIB_HAS_XACQUIRE))
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xF2));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN | ZYDIS_ATTRIB_HAS_SEGMENT_CS))
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x2E));
    }
    if (attribs & (ZYDIS_ATTRIB_HAS_BRANCH_TAKEN | ZYDIS_ATTRIB_HAS_SEGMENT_DS))
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x3E));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_SS)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x36));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_ES)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x26));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_FS)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x64));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_SEGMENT_GS)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x65));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_OPERANDSIZE)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x66));
    }
    if (attribs & ZYDIS_ATTRIB_HAS_ADDRESSSIZE)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x67));
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitREX(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(
        ctx, 
        0x40 |
        (ctx->info->details.rex.W & 0x01) << 3 |
        (ctx->info->details.rex.R & 0x01) << 2 |
        (ctx->info->details.rex.X & 0x01) << 1 |
        (ctx->info->details.rex.B & 0x01) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitVEX(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);

    // Write opcode.
    uint8_t opcode = ctx->info->details.vex.data[0];
    ZYDIS_CHECK(ZydisEmitByte(ctx, opcode));

    // Write prefix' "operands".
    switch (opcode)
    {
    case 0xC4:
        ZYDIS_CHECK(ZydisEmitByte(
            ctx, 
            (ctx->info->details.vex.R      & 0x01) << 7 | 
            (ctx->info->details.vex.X      & 0x01) << 6 |
            (ctx->info->details.vex.B      & 0x01) << 5 |
            (ctx->info->details.vex.m_mmmm & 0x1F) << 0
        ));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx, 
            (ctx->info->details.vex.W      & 0x01) << 7 | 
            (ctx->info->details.vex.vvvv   & 0x0F) << 3 |
            (ctx->info->details.vex.L      & 0x01) << 2 |
            (ctx->info->details.vex.pp     & 0x03) << 0 
        ));
        break;
    case 0xC5:
        ZYDIS_CHECK(ZydisEmitByte(
            ctx, 
            (ctx->info->details.vex.R      & 0x01) << 7 | 
            (ctx->info->details.vex.vvvv   & 0x0F) << 3 |
            (ctx->info->details.vex.L      & 0x01) << 2 |
            (ctx->info->details.vex.pp     & 0x03) << 0 
        ));
        break;
    default:
        ZYDIS_UNREACHABLE; // TODO: return error instead
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitEVEX(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(ctx, 0x62));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx, 
        (ctx->info->details.evex.R    & 0x01) << 7 |
        (ctx->info->details.evex.X    & 0x01) << 6 |
        (ctx->info->details.evex.B    & 0x01) << 5 |
        (ctx->info->details.evex.R2   & 0x01) << 4 |
        (ctx->info->details.evex.mm   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx, 
        (ctx->info->details.evex.W    & 0x01) << 7 |
        (ctx->info->details.evex.vvvv & 0x0F) << 3 |
        (ctx->info->details.evex.pp   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->info->details.evex.z    & 0x01) << 7 |
        (ctx->info->details.evex.L2   & 0x01) << 6 |
        (ctx->info->details.evex.L    & 0x01) << 5 |
        (ctx->info->details.evex.b    & 0x01) << 4 |
        (ctx->info->details.evex.V2   & 0x01) << 3 |
        (ctx->info->details.evex.aaa  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitXOP(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(ctx, 0x8F));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->info->details.xop.R      & 0x01) << 7 |
        (ctx->info->details.xop.X      & 0x01) << 6 |
        (ctx->info->details.xop.B      & 0x01) << 5 |
        (ctx->info->details.xop.m_mmmm & 0x1F) << 0 
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->info->details.xop.W      & 0x01) << 7 |
        (ctx->info->details.xop.vvvv   & 0x0F) << 3 |
        (ctx->info->details.xop.L      & 0x01) << 2 |
        (ctx->info->details.xop.pp     & 0x03) << 0 
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitModRM(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->info->details.modrm.mod & 0x03) << 6 |
        (ctx->info->details.modrm.reg & 0x07) << 3 |
        (ctx->info->details.modrm.rm  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitSIB(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->info->details.sib.scale & 0x03) << 6 |
        (ctx->info->details.sib.index & 0x07) << 3 |
        (ctx->info->details.sib.base  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitOpcode(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(ctx->matchingEntry);

    // Put opcode extension prefix(es), if required.
    switch (ctx->matchingEntry->map)
    {
    case ZYDIS_OPCODE_MAP_0F:
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x0F));
        break;
    case ZYDIS_OPCODE_MAP_0F38:
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x0F));
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x38));
        break;
    case ZYDIS_OPCODE_MAP_0F3A:
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x0F));
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x3A));
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
    ZYDIS_CHECK(ZydisEmitByte(ctx, ctx->info->opcode));

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisSimplifyOperandType(ZydisSemanticOperandType semType,
    ZydisOperandType* simpleType)
{
    // TODO: Better mapping, this is just for testing.
    switch (semType)
    {
    case ZYDIS_SEM_OPERAND_TYPE_GPR8:
    case ZYDIS_SEM_OPERAND_TYPE_GPR16:
    case ZYDIS_SEM_OPERAND_TYPE_GPR32:
    case ZYDIS_SEM_OPERAND_TYPE_GPR64:
        *simpleType = ZYDIS_OPERAND_TYPE_REGISTER;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_IMM8:
    case ZYDIS_SEM_OPERAND_TYPE_IMM16:
    case ZYDIS_SEM_OPERAND_TYPE_IMM32:
    case ZYDIS_SEM_OPERAND_TYPE_IMM64:
    case ZYDIS_SEM_OPERAND_TYPE_REL8:
    case ZYDIS_SEM_OPERAND_TYPE_REL16:
    case ZYDIS_SEM_OPERAND_TYPE_REL32:
    case ZYDIS_SEM_OPERAND_TYPE_REL64:
        *simpleType = ZYDIS_OPERAND_TYPE_IMMEDIATE;
        break;
    case ZYDIS_SEM_OPERAND_TYPE_MEM8:
    case ZYDIS_SEM_OPERAND_TYPE_MEM16:
    case ZYDIS_SEM_OPERAND_TYPE_MEM32:
    case ZYDIS_SEM_OPERAND_TYPE_MEM64:
        *simpleType = ZYDIS_OPERAND_TYPE_MEMORY;
        break;
    default:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareRegOperand(ZydisEncoderContext* ctx,
    ZydisRegister reg, uint8_t useRM)
{
    uint8_t* regRM = useRM ? &ctx->info->details.modrm.rm 
                           : &ctx->info->details.modrm.reg;
    uint8_t* rexRB = useRM ? &ctx->info->details.rex.B 
                           : &ctx->info->details.rex.R;

    int16_t regID = ZydisRegisterGetId(reg);
    if (regID == -1) return ZYDIS_STATUS_INVALID_PARAMETER;

    *regRM = regID & 0x07;
    *rexRB = (regID & 0x08) >> 3;
    ctx->info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
    if (*rexRB) ctx->info->attributes |= ZYDIS_ATTRIB_HAS_REX;

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareOperand(ZydisEncoderContext* ctx,
    ZydisOperandInfo* operand, const ZydisEncoderTableOperand* tableEntry)
{
    switch (tableEntry->encoding)
    {
    case ZYDIS_OPERAND_ENCODING_NONE:
        break; // Nothing to do.
    case ZYDIS_OPERAND_ENCODING_REG:
    {
        ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, ZYDIS_FALSE));
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
        if (operand->type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            // Has base register?
            if (operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, ZYDIS_TRUE));
            }
            else
            {
                // TODO: Does rm=0x05 work with sbyte disps?
                ctx->info->details.modrm.rm = 0x05 /* memory */;
            }

            // SIB byte required?
            if (operand->mem.index || operand->mem.scale)
            {
                switch (operand->mem.scale)
                {
                case 1: ctx->info->details.sib.index = 0x01; break;
                case 2: ctx->info->details.sib.index = 0x02; break;
                case 4: ctx->info->details.sib.index = 0x03; break;
                case 8: ctx->info->details.sib.index = 0x04; break;
                default: return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
                }

                // TODO: base, index

                ctx->info->attributes |= ZYDIS_ATTRIB_HAS_SIB;
            }

            // Has displacement?
            if (operand->mem.disp.value.sdword)
            {
                int32_t divisor = 1;
                switch (tableEntry->encoding)
                {
                    case ZYDIS_OPERAND_ENCODING_RM:                    break;
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
                if (divisor != 1 &&
                    *sdword % divisor == 0 &&
                    *sdword / divisor <= INT8_MAX &&
                    *sdword / divisor >= INT8_MIN)
                {
                    ctx->dispBitSize = 8;
                    ctx->info->details.modrm.mod = 0x01 /* 8 bit disp */;
                    *sdword /= divisor;
                }
                // Nope, regular encoding. Does it fit a byte anyway?
                else if (*sdword <= INT8_MAX && *sdword >= INT8_MIN)
                {
                    ctx->dispBitSize = 8;
                    ctx->info->details.modrm.mod = 0x01 /* 8 bit disp */;
                }
                // No compression possible, emit as 32 bit.
                else
                {
                    ctx->dispBitSize = 32;
                    ctx->info->details.modrm.mod = 0x02 /* 32 bit disp */;
                }

                ctx->disp = *sdword;
            }
            // No displacement.
            else
            {
                ctx->info->details.modrm.mod = 0x00 /* no disp */;
            }
        }
        // Nope, register.
        else if (operand->type == ZYDIS_OPERAND_TYPE_REGISTER)
        {
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, ZYDIS_TRUE));
            ctx->info->details.modrm.mod = 0x03 /* reg */;
        }

        ctx->info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_OPCODE:
    {
        int16_t reg = ZydisRegisterGetId(operand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        ctx->info->opcode += reg & 0x0F;
        ctx->info->details.rex.R = (reg & 0x08) >> 3;
        if (ctx->info->details.rex.B) ctx->info->attributes |= ZYDIS_ATTRIB_HAS_REX;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_VVVV:
        break; // TODO
    case ZYDIS_OPERAND_ENCODING_AAA:
        break; // TODO
    case ZYDIS_OPERAND_ENCODING_IMM8_LO:
    {
        ctx->immBitSizes[0] = 8;
        ctx->imms[0] |= operand->imm.value.ubyte & 0x0F;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_IMM8_HI:
    {
        ctx->immBitSizes[0] = 8;
        ctx->imms[0] |= (operand->imm.value.ubyte & 0x0F) << 4;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_IMM8:
    case ZYDIS_OPERAND_ENCODING_IMM16:
    case ZYDIS_OPERAND_ENCODING_IMM32:
    case ZYDIS_OPERAND_ENCODING_IMM64:
    {
        uint8_t immIdx = ctx->immBitSizes[0] ? 1 : 0;
        ctx->immBitSizes[immIdx] = operand->imm.dataSize;
        ctx->imms[immIdx] = operand->imm.value.uqword;
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisDeriveEncodingForOp(ZydisOperandDefinition* operand)
{
    switch (operand->type)
    {
    default:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
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
    for (size_t i = 0; i < ZYDIS_ARRAY_SIZE(kEncoderTable); ++i)
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
            if (curReqOp->encoding != curEncoderOp->encoding) goto continueTopLevel;
            ZydisOperandType simpleType;
            ZYDIS_CHECK(ZydisSimplifyOperandType(curEncoderOp->type, &simpleType));
            if (curReqOp->type != simpleType) goto continueTopLevel;
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

ZydisStatus ZydisEncoderEncodeInstruction(void* buffer, size_t* bufferLen,
    ZydisInstructionInfo* info)
{
    if (!info || !bufferLen) return ZYDIS_STATUS_INVALID_PARAMETER;
    if (!buffer || !*bufferLen) return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;

    ZydisEncoderContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    memset(&info->details, 0, sizeof(info->details));
    ctx.buffer = (uint8_t*)buffer;
    ctx.bufferLen = *bufferLen;
    ctx.writeOffs = 0;
    ctx.info = info;
    *bufferLen = 0;

    // Mask out attributes that can't be set explicitly by user.
    info->attributes &= ZYDIS_USER_ENCODABLE_ATTRIB_MASK;

    // Search matching instruction, collect information about what needs to be
    // encoded, what prefixes are required, etc.
    ZYDIS_CHECK(ZydisFindMatchingDef(info, &ctx.matchingEntry));
    info->opcode = ctx.matchingEntry->opcode;
    info->attributes |= ctx.matchingEntry->mandatoryAttribs;

    // Analyze and prepare operands.
    if (info->operandCount > ZYDIS_ARRAY_SIZE(info->operands))
    {
        // TODO: Better status?
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    for (size_t i = 0; i < ctx.matchingEntry->operandCount; ++i)
    {
        ZYDIS_CHECK(ZydisPrepareOperand(
            &ctx, &info->operands[i], 
            &ctx.matchingEntry->operands[i]
        ));
    }
    
    // Do actual encoding work.
    ZYDIS_CHECK(ZydisEmitLegacyPrefixes(&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_REX  ) ZYDIS_CHECK(ZydisEmitREX  (&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_VEX  ) ZYDIS_CHECK(ZydisEmitVEX  (&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_EVEX ) ZYDIS_CHECK(ZydisEmitEVEX (&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_XOP  ) ZYDIS_CHECK(ZydisEmitXOP  (&ctx));
    ZYDIS_CHECK(ZydisEmitOpcode(&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_MODRM) ZYDIS_CHECK(ZydisEmitModRM(&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_SIB  ) ZYDIS_CHECK(ZydisEmitSIB  (&ctx));

    if (ctx.dispBitSize)    ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.disp, ctx.dispBitSize));
    if (ctx.immBitSizes[0]) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.imms[0], ctx.immBitSizes[0]));
    if (ctx.immBitSizes[1]) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.imms[1], ctx.immBitSizes[1]));

    *bufferLen = ctx.writeOffs;
    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
