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

typedef uint8_t ZydisPrefixBit;

enum ZydisPrefixBits
{
    // TODO: Use defines instead?
    ZYDIS_PREFBIT_VEX_L     = 0x01,
    ZYDIS_PREFBIT_REX_W     = 0x02,
    ZYDIS_PREFBIT_EVEX_L2   = 0x04,
    ZYDIS_PREFBIT_EVEX_B    = 0x08,
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
    ZydisPrefixBit prefixBits;
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
    uint8_t opcodeMapPrefixLen;
    uint8_t opcodeMapPrefix[3];
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

    // Can we use short 2-byte VEX encoding?
    if (ctx->info->details.vex.X == 1 &&
        ctx->info->details.vex.B == 1 &&
        ctx->info->details.vex.W  == 0 &&
        ctx->info->details.vex.m_mmmm == 1)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xC5));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            (~ctx->info->details.vex.R    & 0x01) << 7 |
            (~ctx->info->details.vex.vvvv & 0x0F) << 3 |
            ( ctx->info->details.vex.L    & 0x01) << 2 |
            ( ctx->info->details.vex.pp   & 0x03) << 0
        ));
    }
    // Nope, use 3-byte VEX.
    else
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xC4));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            (~ctx->info->details.vex.R      & 0x01) << 7 |
            (~ctx->info->details.vex.X      & 0x01) << 6 |
            (~ctx->info->details.vex.B      & 0x01) << 5 |
            ( ctx->info->details.vex.m_mmmm & 0x1F) << 0
        ));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            ( ctx->info->details.vex.W    & 0x01) << 7 |
            (~ctx->info->details.vex.vvvv & 0x0F) << 3 |
            ( ctx->info->details.vex.L    & 0x01) << 2 |
            ( ctx->info->details.vex.pp   & 0x03) << 0
        ));
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

static ZydisStatus ZydisPrepareOpcode(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(ctx->matchingEntry);

    // Put opcode map prefix(es), if required.
    switch (ctx->info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        switch (ctx->matchingEntry->map)
        {
        case ZYDIS_OPCODE_MAP_0F:
            ctx->opcodeMapPrefix[ctx->opcodeMapPrefixLen++] = 0x0F;
            break;
        case ZYDIS_OPCODE_MAP_0F38:
            ctx->opcodeMapPrefix[ctx->opcodeMapPrefixLen++] = 0x0F;
            ctx->opcodeMapPrefix[ctx->opcodeMapPrefixLen++] = 0x38;
            break;
        case ZYDIS_OPCODE_MAP_0F3A:
            ctx->opcodeMapPrefix[ctx->opcodeMapPrefixLen++] = 0x0F;
            ctx->opcodeMapPrefix[ctx->opcodeMapPrefixLen++] = 0x3A;
            break;
        case ZYDIS_OPCODE_MAP_DEFAULT:
            break; // Nothing to do.
        default:
            ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ctx->info->details.vex.m_mmmm = ctx->matchingEntry->map;
        ZYDIS_ASSERT(ctx->info->details.vex.m_mmmm <= 0x03);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ctx->info->details.evex.mm = ctx->matchingEntry->map;
        ZYDIS_ASSERT(ctx->info->details.evex.mm <= 0x03);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ctx->info->details.xop.m_mmmm =
            ctx->matchingEntry->map - ZYDIS_OPCODE_MAP_XOP8 + 0x08;
        ZYDIS_ASSERT(ctx->info->details.xop.m_mmmm >= 0x08);
        ZYDIS_ASSERT(ctx->info->details.xop.m_mmmm <= 0x0B);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

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
    ZydisRegister reg, char topBitLoc)
{
    int16_t regID = ZydisRegisterGetId(reg);
    if (regID == -1) return ZYDIS_STATUS_INVALID_PARAMETER;

    uint8_t lowerBits = (regID & 0x07) >> 0;
    uint8_t topBit    = (regID & 0x08) >> 3;

    switch (topBitLoc)
    {
        case 'B': ctx->info->details.modrm.rm  = lowerBits; break;
        case 'R': ctx->info->details.modrm.reg = lowerBits; break;
        case 'X': ctx->info->details.sib.index = lowerBits; break;
        default: ZYDIS_UNREACHABLE;
    }
    
    uint8_t* topBitDst = NULL;

    switch (ctx->info->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        switch (topBitLoc)
        {
            case 'B': topBitDst = &ctx->info->details.rex.B; break;
            case 'R': topBitDst = &ctx->info->details.rex.R; break;
            case 'X': topBitDst = &ctx->info->details.rex.X; break;
            default: ZYDIS_UNREACHABLE;
        }
        if (topBit) ctx->info->attributes |= ZYDIS_ATTRIB_HAS_REX;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        switch (topBitLoc)
        {
            case 'B': topBitDst = &ctx->info->details.vex.B; break;
            case 'R': topBitDst = &ctx->info->details.vex.R; break;
            case 'X': topBitDst = &ctx->info->details.vex.X; break;
            default: ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        switch (topBitLoc)
        {
            case 'B': topBitDst = &ctx->info->details.xop.B; break;
            case 'R': topBitDst = &ctx->info->details.xop.R; break;
            case 'X': topBitDst = &ctx->info->details.xop.X; break;
            default: ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        switch (topBitLoc)
        {
            case 'B': topBitDst = &ctx->info->details.evex.B; break;
            case 'R': topBitDst = &ctx->info->details.evex.R; break;
            case 'X': topBitDst = &ctx->info->details.evex.X; break;
            default: ZYDIS_UNREACHABLE;
        }
        break;
    default:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    }

    *topBitDst = topBit;

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
        ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, 'R'));
    } break;
    case ZYDIS_OPERAND_ENCODING_RM:
    case ZYDIS_OPERAND_ENCODING_RM_CD2:
    case ZYDIS_OPERAND_ENCODING_RM_CD4:
    case ZYDIS_OPERAND_ENCODING_RM_CD8:
    case ZYDIS_OPERAND_ENCODING_RM_CD16:
    case ZYDIS_OPERAND_ENCODING_RM_CD32:
    case ZYDIS_OPERAND_ENCODING_RM_CD64:
    {
        // TODO: MMX registers
        // TODO: rBP
        // TODO: RIP relative addressing

        // Memory operand?
        if (operand->type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            // Absolute memory access?
            if (operand->mem.base == ZYDIS_REGISTER_NONE)
            {
                ctx->disp = operand->mem.disp.value.sdword;
                ctx->dispBitSize = 32;

                // In 32 bit mode, ModRM allows for a shortcut here.
                if (ctx->info->mode == ZYDIS_DISASSEMBLER_MODE_32BIT)
                {
                    ctx->info->details.modrm.mod = 0x00;
                    ctx->info->details.modrm.rm  = 0x05 /* memory */;
                }
                // In AMD64 mode, we have to build a SIB.
                else
                {
                    ctx->info->details.modrm.mod = 0x00;
                    ctx->info->details.modrm.rm  = 0x04 /* SIB  */;
                    ctx->info->details.sib.index = 0x04 /* none */;
                    ctx->info->details.sib.scale = 0x00 /* * 1  */;
                    ctx->info->details.sib.base  = 0x05;
                    ctx->info->attributes |= ZYDIS_ATTRIB_HAS_SIB;
                }

                ctx->info->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
                break;
            }

            // Base register?
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->mem.base, 'B'));

            // SIB byte required?
            if (operand->mem.index || operand->mem.scale)
            {
                switch (operand->mem.scale)
                {
                case 1: ctx->info->details.sib.index = 0x00; break;
                case 2: ctx->info->details.sib.index = 0x01; break;
                case 4: ctx->info->details.sib.index = 0x02; break;
                case 8: ctx->info->details.sib.index = 0x03; break;
                default: return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
                }

                // Base & index register.
                ctx->info->details.sib.base = ctx->info->details.modrm.rm;
                ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->mem.index, 'X'));

                ctx->info->details.modrm.rm = 0x04 /* SIB */;
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
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, 'B'));
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
    {
        int16_t reg = ZydisRegisterGetId(operand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        // TODO: Conditional assignment instead?
        ctx->info->details.vex.vvvv  = (reg & 0x0F);
        ctx->info->details.evex.vvvv = (reg & 0x0F);
        break;
    }        
    case ZYDIS_OPERAND_ENCODING_AAA:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
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
    // TODO: Do binary search / hash based lookup instead.
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
            // TODO: Match operand size.
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

    // TODO: Check compatibility of requested prefixes to found instruction.

    // Determine required prefixes.
    switch (ctx.matchingEntry->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        info->attributes |= ZYDIS_ATTRIB_HAS_EVEX;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        info->attributes |= ZYDIS_ATTRIB_HAS_VEX;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        info->attributes |= ZYDIS_ATTRIB_HAS_XOP;
        break;
    }

    // Prepare prefix bits.
    ZydisPrefixBit pb = ctx.matchingEntry->prefixBits;
    info->details.evex.B  = (pb & ZYDIS_PREFBIT_EVEX_B ) ? 1 : 0;
    info->details.evex.L2 = (pb & ZYDIS_PREFBIT_EVEX_L2) ? 1 : 0;
    info->details.vex.L   = (pb & ZYDIS_PREFBIT_VEX_L  ) ? 1 : 0;
    info->details.rex.W   = (pb & ZYDIS_PREFBIT_REX_W  ) ? 1 : 0;

    // Prepare opcode.
    ZYDIS_CHECK(ZydisPrepareOpcode(&ctx));

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
    
    for (uint8_t i = 0; i < ctx.opcodeMapPrefixLen; ++i)
    {
        ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.opcodeMapPrefix[i]));
    }

    ZYDIS_CHECK(ZydisEmitByte(&ctx, info->opcode));

    if (info->attributes & ZYDIS_ATTRIB_HAS_MODRM) ZYDIS_CHECK(ZydisEmitModRM(&ctx));
    if (info->attributes & ZYDIS_ATTRIB_HAS_SIB  ) ZYDIS_CHECK(ZydisEmitSIB  (&ctx));

    if (ctx.dispBitSize   ) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.disp,    ctx.dispBitSize   ));
    if (ctx.immBitSizes[0]) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.imms[0], ctx.immBitSizes[0]));
    if (ctx.immBitSizes[1]) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.imms[1], ctx.immBitSizes[1]));

    *bufferLen = ctx.writeOffs;
    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
