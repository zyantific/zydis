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
#include <SharedData.h>
#include <EncoderData.h>

#include <string.h>
#include <stdint.h>

/* ============================================================================================== */
/* Internal context and table types                                                               */
/* ============================================================================================== */

struct ZydisPrefixAcceptMapping
{
    uint64_t has;
    uint64_t accepts;
} static const prefixAcceptMap[] =
{
    { ZYDIS_ATTRIB_HAS_LOCK,             ZYDIS_ATTRIB_ACCEPTS_LOCK         },
    { ZYDIS_ATTRIB_HAS_REP,              ZYDIS_ATTRIB_ACCEPTS_REP          },
    { ZYDIS_ATTRIB_HAS_REPE,             ZYDIS_ATTRIB_ACCEPTS_REPE         },
    { ZYDIS_ATTRIB_HAS_REPZ,             ZYDIS_ATTRIB_ACCEPTS_REPZ         },
    { ZYDIS_ATTRIB_HAS_REPNE,            ZYDIS_ATTRIB_ACCEPTS_REPNE        },
    { ZYDIS_ATTRIB_HAS_REPNZ,            ZYDIS_ATTRIB_ACCEPTS_REPNZ        },
    { ZYDIS_ATTRIB_HAS_BOUND,            ZYDIS_ATTRIB_ACCEPTS_BOUND        },
    { ZYDIS_ATTRIB_HAS_XACQUIRE,         ZYDIS_ATTRIB_ACCEPTS_XACQUIRE     },
    { ZYDIS_ATTRIB_HAS_XRELEASE,         ZYDIS_ATTRIB_ACCEPTS_XRELEASE     },
    { ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN, ZYDIS_ATTRIB_ACCEPTS_BRANCH_HINTS },
    { ZYDIS_ATTRIB_HAS_BRANCH_TAKEN,     ZYDIS_ATTRIB_ACCEPTS_BRANCH_HINTS },
    { ZYDIS_ATTRIB_HAS_SEGMENT,          ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    { ZYDIS_ATTRIB_HAS_SEGMENT_CS,       ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    { ZYDIS_ATTRIB_HAS_SEGMENT_SS,       ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    { ZYDIS_ATTRIB_HAS_SEGMENT_DS,       ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    { ZYDIS_ATTRIB_HAS_SEGMENT_ES,       ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    { ZYDIS_ATTRIB_HAS_SEGMENT_FS,       ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    { ZYDIS_ATTRIB_HAS_SEGMENT_GS,       ZYDIS_ATTRIB_ACCEPTS_SEGMENT      },
    //{ ZYDIS_ATTRIB_HAS_OPERANDSIZE,      ZYDIS_ATTRIB_ACCEPTS_OPERANDSIZE  },
    //{ ZYDIS_ATTRIB_HAS_ADDRESSSIZE,      ZYDIS_ATTRIB_ACCEPTS_ADDRESSSIZE  },
};

/**
 * @brief   The encoder context struct.
 */
typedef struct ZydisEncoderContext_
{
    uint8_t* buffer;
    size_t bufferLen;
    size_t writeOffs;
    ZydisEncoderRequest* req;
    const ZydisEncodableInstruction* matchingInsn;
    const ZydisInstructionDefinition* matchingDef;
    uint8_t matchingOperandCount;
    const ZydisOperandDefinition* matchingOperands;
    ZydisBool emitMandatoryPrefix;
    uint8_t mandatoryPrefix;
    uint8_t dispBitSize;
    uint64_t disp;
    uint8_t immBitSizes[2];
    uint64_t imms[2];
    uint8_t opcodeMapPrefixLen;
    uint8_t opcodeMapPrefix[3];

    struct
    {
        uint8_t opcode;
        struct
        {
            uint8_t W;
            uint8_t R;
            uint8_t X;
            uint8_t B;
        } rex;
        struct
        {
            uint8_t R;
            uint8_t X;
            uint8_t B;
            uint8_t m_mmmm;
            uint8_t W;
            uint8_t vvvv;
            uint8_t L;
            uint8_t pp;
        } xop;
        struct
        {
            uint8_t R;
            uint8_t X;
            uint8_t B;
            uint8_t m_mmmm;
            uint8_t W;
            uint8_t vvvv;
            uint8_t L;
            uint8_t pp;
        } vex;
        struct
        {
            uint8_t R;
            uint8_t X;
            uint8_t B;
            uint8_t R2;
            uint8_t mm;
            uint8_t W;
            uint8_t vvvv;
            uint8_t pp;
            uint8_t z;
            uint8_t L2;
            uint8_t L;
            uint8_t b;
            uint8_t V2;
            uint8_t aaa;
        } evex;
        struct
        {
            uint8_t R;
            uint8_t X;
            uint8_t B;
            uint8_t R2;
            uint8_t mmmm;
            uint8_t W;
            uint8_t vvvv;
            uint8_t pp;
            uint8_t E;
            uint8_t SSS;
            uint8_t V2;
            uint8_t kkk;
        } mvex;
        struct
        {
            uint8_t mod;
            uint8_t reg;
            uint8_t rm;
        } modrm;
        struct
        {
            uint8_t scale;
            uint8_t index;
            uint8_t base;
        } sib;
        struct
        {
            int64_t value;
            uint8_t size;
            uint8_t offset;
        } disp;
        struct
        {
            ZydisBool isSigned;
            ZydisBool isRelative;
            union
            {
                uint64_t u;
                int64_t s;
            } value;
            uint8_t size;
            uint8_t offset;
        } imm[2];
    } raw;
} ZydisEncoderContext;

/* ============================================================================================== */
/* Internal helpers                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Byte stream output functions. Those are the only funcs that access the output stream directly. */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisEmitImm(ZydisEncoderContext* ctx, uint64_t imm, int bits)
{
    ZYDIS_ASSERT(bits == 8 || bits == 16 || bits == 32 || bits == 64);
    size_t newWriteOffs = ctx->writeOffs + bits / 8;
    if (newWriteOffs >= ctx->bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    if (newWriteOffs > ZYDIS_MAX_INSTRUCTION_LENGTH)
    {
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
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

static ZydisStatus ZydisEmitByte(ZydisEncoderContext* ctx, uint8_t byte)
{
    return ZydisEmitImm(ctx, byte, 8);
}

/* ---------------------------------------------------------------------------------------------- */
/* Byte code encoding functions. Translate prepared data to final format.                         */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisEmitLegacyPrefixes(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZydisInstructionAttributes attribs = ctx->req->attributes;

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
        (ctx->raw.rex.W & 0x01) << 3 |
        (ctx->raw.rex.R & 0x01) << 2 |
        (ctx->raw.rex.X & 0x01) << 1 |
        (ctx->raw.rex.B & 0x01) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitVEX(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);

    // Can we use short 2-byte VEX encoding?
    if (ctx->raw.vex.X      == 0 &&
        ctx->raw.vex.B      == 0 &&
        ctx->raw.vex.W      == 0 &&
        ctx->raw.vex.m_mmmm == 1)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xC5));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            (~ctx->raw.vex.R    & 0x01) << 7 |
            (~ctx->raw.vex.vvvv & 0x0F) << 3 |
            ( ctx->raw.vex.L    & 0x01) << 2 |
            ( ctx->raw.vex.pp   & 0x03) << 0
        ));
    }
    // Nope, use 3-byte VEX.
    else
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xC4));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            (~ctx->raw.vex.R      & 0x01) << 7 |
            (~ctx->raw.vex.X      & 0x01) << 6 |
            (~ctx->raw.vex.B      & 0x01) << 5 |
            ( ctx->raw.vex.m_mmmm & 0x1F) << 0
        ));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            ( ctx->raw.vex.W    & 0x01) << 7 |
            (~ctx->raw.vex.vvvv & 0x0F) << 3 |
            ( ctx->raw.vex.L    & 0x01) << 2 |
            ( ctx->raw.vex.pp   & 0x03) << 0
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
        (ctx->raw.evex.R    & 0x01) << 7 |
        (ctx->raw.evex.X    & 0x01) << 6 |
        (ctx->raw.evex.B    & 0x01) << 5 |
        (ctx->raw.evex.R2   & 0x01) << 4 |
        (ctx->raw.evex.mm   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx, 
        (ctx->raw.evex.W    & 0x01) << 7 |
        (ctx->raw.evex.vvvv & 0x0F) << 3 |
        (ctx->raw.evex.pp   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.evex.z    & 0x01) << 7 |
        (ctx->raw.evex.L2   & 0x01) << 6 |
        (ctx->raw.evex.L    & 0x01) << 5 |
        (ctx->raw.evex.b    & 0x01) << 4 |
        (ctx->raw.evex.V2   & 0x01) << 3 |
        (ctx->raw.evex.aaa  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitXOP(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(ctx, 0x8F));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.xop.R      & 0x01) << 7 |
        (ctx->raw.xop.X      & 0x01) << 6 |
        (ctx->raw.xop.B      & 0x01) << 5 |
        (ctx->raw.xop.m_mmmm & 0x1F) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.xop.W      & 0x01) << 7 |
        (ctx->raw.xop.vvvv   & 0x0F) << 3 |
        (ctx->raw.xop.L      & 0x01) << 2 |
        (ctx->raw.xop.pp     & 0x03) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitModRM(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.modrm.mod & 0x03) << 6 |
        (ctx->raw.modrm.reg & 0x07) << 3 |
        (ctx->raw.modrm.rm  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitSIB(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.sib.scale & 0x03) << 6 |
        (ctx->raw.sib.index & 0x07) << 3 |
        (ctx->raw.sib.base  & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Preparation functions. Parse encoder request, determine required bytes and prefixes.           */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisPrepareOpcode(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(ctx->matchingDef);
    ZYDIS_ASSERT(ctx->req);

    // Put opcode map prefix(es), if required.
    switch (ctx->req->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        switch (ctx->matchingInsn->opcodeMap)
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
        ctx->raw.vex.m_mmmm = ctx->matchingInsn->opcodeMap;
        ZYDIS_ASSERT(ctx->raw.vex.m_mmmm <= 0x03);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ctx->raw.evex.mm = ctx->matchingInsn->opcodeMap;
        ZYDIS_ASSERT(ctx->raw.evex.mm <= 0x03);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ctx->raw.xop.m_mmmm =
            ctx->matchingInsn->opcodeMap - ZYDIS_OPCODE_MAP_XOP8 + 0x08;
        ZYDIS_ASSERT(ctx->raw.xop.m_mmmm >= 0x08);
        ZYDIS_ASSERT(ctx->raw.xop.m_mmmm <= 0x0B);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareRegOperand(ZydisEncoderContext* ctx,
    ZydisRegister reg, char topBitLoc)
{
    ZYDIS_ASSERT(ctx);

    int16_t regID = ZydisRegisterGetId(reg);
    if (regID == -1) return ZYDIS_STATUS_INVALID_PARAMETER;

    uint8_t lowerBits = (regID & 0x07) >> 0;
    uint8_t topBit    = (regID & 0x08) >> 3;

    switch (topBitLoc)
    {
        case 'B': ctx->raw.modrm.rm  = lowerBits; break;
        case 'R': ctx->raw.modrm.reg = lowerBits; break;
        case 'X': ctx->raw.sib.index = lowerBits; break;
        default: ZYDIS_UNREACHABLE;
    }

    // No top bit? Quick exit.
    if (!topBit) return ZYDIS_STATUS_SUCCESS;
    
    switch (ctx->req->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        switch (topBitLoc)
        {
            case 'B': ctx->raw.rex.B = topBit; break;
            case 'R': ctx->raw.rex.R = topBit; break;
            case 'X': ctx->raw.rex.X = topBit; break;
            default: ZYDIS_UNREACHABLE;
        }
        if (topBit) ctx->req->attributes |= ZYDIS_ATTRIB_HAS_REX;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        switch (topBitLoc)
        {
            case 'B': ctx->raw.vex.B = topBit; break;
            case 'R': ctx->raw.vex.R = topBit; break;
            case 'X': ctx->raw.vex.X = topBit; break;
            default: ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        switch (topBitLoc)
        {
            case 'B': ctx->raw.xop.B = topBit; break;
            case 'R': ctx->raw.xop.R = topBit; break;
            case 'X': ctx->raw.xop.X = topBit; break;
            default: ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        switch (topBitLoc)
        {
            case 'B': ctx->raw.evex.B = topBit; break;
            case 'R': ctx->raw.evex.R = topBit; break;
            case 'X': ctx->raw.evex.X = topBit; break;
            default: ZYDIS_UNREACHABLE;
        }
        break;
    default:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisBool ZydisIsBPReg(ZydisRegister reg)
{
    return reg == ZYDIS_REGISTER_BPL ||
           reg == ZYDIS_REGISTER_BP  ||
           reg == ZYDIS_REGISTER_EBP ||
           reg == ZYDIS_REGISTER_RBP;
}

static ZydisBool ZydisIsSPReg(ZydisRegister reg)
{
    return reg == ZYDIS_REGISTER_SPL ||
           reg == ZYDIS_REGISTER_SP  ||
           reg == ZYDIS_REGISTER_ESP ||
           reg == ZYDIS_REGISTER_RSP;
}

static ZydisBool ZydisIsIPReg(ZydisRegister reg)
{
    return reg == ZYDIS_REGISTER_IP  ||
           reg == ZYDIS_REGISTER_EIP ||
           reg == ZYDIS_REGISTER_RIP;
}

static ZydisBool ZydisIsStackReg(ZydisRegister reg)
{
    return ZydisIsSPReg(reg) || ZydisIsBPReg(reg);
}

static ZydisStatus ZydisPrepareSegmentPrefix(ZydisEncoderContext* ctx,
    ZydisRegister segment, ZydisRegister base)
{
    // Segment prefix required?
    switch (segment)
    {
    case ZYDIS_REGISTER_ES:
        ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_ES;
        break;
    case ZYDIS_REGISTER_SS:
        if (!ZydisIsStackReg(base))
        {
            ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_SS;
        }
        break;
    case ZYDIS_REGISTER_CS:
        ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_CS;
        break;
    case ZYDIS_REGISTER_DS:
        if (ZydisIsStackReg(base))
        {
            ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_DS;
        }
        break;
    case ZYDIS_REGISTER_FS:
        ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_FS;
        break;
    case ZYDIS_REGISTER_GS:
        ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SEGMENT_GS;
        break;
    default:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO: Better status.
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareMemoryOperand(ZydisEncoderContext* ctx,
    ZydisEncoderOperand* operand, const ZydisOperandDefinition* operandDef)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(ctx->req);
    ZYDIS_ASSERT(operand);
    ZYDIS_ASSERT(operandDef);

    ZYDIS_CHECK(ZydisPrepareSegmentPrefix(ctx, operand->mem.segment, operand->mem.base));

    // Absolute memory access? Special case.
    if (operand->mem.base == ZYDIS_REGISTER_NONE)
    {
        ctx->disp = operand->mem.disp;
        ctx->dispBitSize = 32;

        // In 32 bit mode, ModRM allows for a shortcut here.
        if (ctx->req->machineMode == 32)
        {
            ctx->raw.modrm.mod = 0x00;
            ctx->raw.modrm.rm  = 0x05 /* memory */;
        }
        // In AMD64 mode, we have to build a special SIB.
        else
        {
            ctx->raw.modrm.mod = 0x00;
            ctx->raw.modrm.rm  = 0x04 /* SIB  */;
            ctx->raw.sib.index = 0x04 /* none */;
            ctx->raw.sib.scale = 0x00 /* * 1  */;
            ctx->raw.sib.base  = 0x05;
            ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SIB;
        }

        return ZYDIS_STATUS_SUCCESS;
    }

    // rIP relative addressing? Special case.
    if (ZydisIsIPReg(operand->mem.base))
    {
        // rIP addressing is only available since AMD64.
        if (ctx->req->machineMode != 64)
        {
            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        }

        // Only available with either EIP or RIP, not with IP.
        if (operand->mem.base == ZYDIS_REGISTER_IP)
        {
            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        }

        ctx->disp = operand->mem.disp;
        ctx->dispBitSize = 32;
        ctx->raw.modrm.mod = 0x00;
        ctx->raw.modrm.rm  = 0x05 /* RIP relative mem */;

        if (operand->mem.base == ZYDIS_REGISTER_EIP)
        {
            ctx->req->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
        }

        return ZYDIS_STATUS_SUCCESS;
    }

    // Process base register.
    ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->mem.base, 'B'));

    // Address size prefix required?
    ZydisRegisterClass baseRegClass = ZydisRegisterGetClass(operand->mem.base);
    switch (baseRegClass)
    {
    case ZYDIS_REGCLASS_GPR16:
        switch (ctx->req->machineMode)
        {
        case 16:
            break; // Nothing to do.
        case 32:
            ctx->req->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
            break;
        case 64:
            // AMD64 doesn't allow for 16 bit addressing.
            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER; // TODO
        }
        break;
    case ZYDIS_REGCLASS_GPR32:
        switch (ctx->req->machineMode)
        {
        case 16:
            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        case 32:
            break; // Nothing to do.
        case 64:
            ctx->req->attributes |= ZYDIS_ATTRIB_HAS_ADDRESSSIZE;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER; // TODO
        }
        break;
    case ZYDIS_REGCLASS_GPR64:
        if (ctx->req->machineMode != 64)
        {
            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        }
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER; // TODO
    }

    // SIB byte required? rSP can only be encoded with SIB.
    if (operand->mem.index || operand->mem.scale || ZydisIsSPReg(operand->mem.base))
    {
        // Translate scale to SIB format.
        switch (operand->mem.scale)
        {
        case 0: // We take 0 (uninitialized, 0 from memset) as * 1.
        case 1: ctx->raw.sib.scale = 0x00; break;
        case 2: ctx->raw.sib.scale = 0x01; break;
        case 4: ctx->raw.sib.scale = 0x02; break;
        case 8: ctx->raw.sib.scale = 0x03; break;
        default: return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        }

        // Move base register info to SIB.
        ctx->raw.sib.base = ctx->raw.modrm.rm;
        ctx->raw.modrm.rm = 0x04 /* SIB */;

        // Process index register.
        if (operand->mem.index != ZYDIS_REGISTER_NONE)
        {
            // Base and index register must be of same register class, verify.
            if (ZydisRegisterGetClass(operand->mem.index) != baseRegClass)
            {
                return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
            }
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->mem.index, 'X'));
        }
        else
        {
            ctx->raw.sib.index = 0x04 /* no index */;
        }
        
        ctx->req->attributes |= ZYDIS_ATTRIB_HAS_SIB;
    }

    // Has displacement or is rBP and we have no SIB?
    // rBP can't be ModRM-encoded without a disp.
    if (operand->mem.disp || (!(ctx->req->attributes & ZYDIS_ATTRIB_HAS_SIB)
        && ZydisIsBPReg(operand->mem.base)))
    {
        ctx->dispBitSize = 32;
        ctx->raw.modrm.mod = 0x02 /* 32 bit disp */;
        ctx->disp = operand->mem.disp;
    }
    // No displacement.
    else
    {
        ctx->raw.modrm.mod = 0x00 /* no disp */;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareOperand(ZydisEncoderContext* ctx,
    ZydisEncoderOperand* operand, const ZydisOperandDefinition* operandDef)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(operand);
    ZYDIS_ASSERT(operandDef);
    ZYDIS_ASSERT(operandDef->type != ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG);
    ZYDIS_ASSERT(operandDef->type != ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_MEM);
    ZYDIS_ASSERT(operandDef->type != ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_IMM1);

    switch (operandDef->op.encoding)
    {
    case ZYDIS_OPERAND_ENCODING_NONE:
    {
        // For some encodings, we have to switch on the sem op type.
        if (operandDef->type == ZYDIS_SEMANTIC_OPTYPE_MOFFS)
        {
            ZYDIS_CHECK(ZydisPrepareSegmentPrefix(
                ctx, operand->mem.segment, ZYDIS_REGISTER_NONE
            ));
            ctx->imms[0] = operand->mem.disp;
            ctx->immBitSizes[0] = operand->mem.dispSize;
        }
    } break;
    case ZYDIS_OPERAND_ENCODING_MODRM_REG:
    {
        ZYDIS_ASSERT(!ctx->raw.modrm.reg);
        ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, 'R'));
    } break;
    case ZYDIS_OPERAND_ENCODING_MODRM_RM:
    {
        ZYDIS_ASSERT(!ctx->raw.modrm.mod);
        ZYDIS_ASSERT(!ctx->raw.modrm.rm);
        ZYDIS_ASSERT(!ctx->raw.sib.base);
        ZYDIS_ASSERT(!ctx->raw.sib.index);
        ZYDIS_ASSERT(!ctx->raw.sib.scale);

        // Memory operand?
        if (operand->type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            ZYDIS_CHECK(ZydisPrepareMemoryOperand(ctx, operand, operandDef));
        }
        // Nope, register.
        else if (operand->type == ZYDIS_OPERAND_TYPE_REGISTER)
        {
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->reg, 'B'));
            ctx->raw.modrm.mod = 0x03 /* reg */;
        }

        ctx->req->attributes |= ZYDIS_ATTRIB_HAS_MODRM;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_OPCODE:
    {
        int16_t reg = ZydisRegisterGetId(operand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        ctx->raw.opcode += reg & 0x07;
        ctx->raw.rex.B = (reg & 0x08) >> 3;
        if (ctx->raw.rex.B) ctx->req->attributes |= ZYDIS_ATTRIB_HAS_REX;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_NDSNDD:
    {
        int16_t reg = ZydisRegisterGetId(operand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        // TODO: Conditional assignment instead?
        ctx->raw.vex.vvvv  = (reg & 0x0F);
        ctx->raw.xop.vvvv  = (reg & 0x0F);
        ctx->raw.evex.vvvv = (reg & 0x0F);
        break;
    }        
    case ZYDIS_OPERAND_ENCODING_MASK:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
        break; // TODO
    case ZYDIS_OPERAND_ENCODING_IS4:
    {
        ctx->immBitSizes[0] = 8;
        ctx->imms[0] |= operand->imm.u & 0x0F;
        break;
    }
    // TODO
    //case ZYDIS_OPERAND_ENCODING_IS4:
    //{
    //    ctx->immBitSizes[0] = 8;
    //    ctx->imms[0] |= (operand->imm.u & 0x0F) << 4;
    //    break;
    //}
    case ZYDIS_OPERAND_ENCODING_SIMM8:
    case ZYDIS_OPERAND_ENCODING_UIMM8:
    case ZYDIS_OPERAND_ENCODING_SIMM16:
    case ZYDIS_OPERAND_ENCODING_UIMM16:
    case ZYDIS_OPERAND_ENCODING_SIMM32:
    case ZYDIS_OPERAND_ENCODING_UIMM32:
    case ZYDIS_OPERAND_ENCODING_UIMM64:
    case ZYDIS_OPERAND_ENCODING_SIMM64:
    {
        uint8_t immIdx = ctx->immBitSizes[0] ? 1 : 0;
        ctx->immBitSizes[immIdx] = operand->immSize;
        ctx->imms[immIdx] = operand->imm.u;
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareMandatoryPrefixes(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);

    // Is a prefix mandatory? 0x00 is a sentinel value for `None` in the table.
    uint8_t prefix = ctx->matchingInsn->mandatoryPrefix;
    if (prefix != 0x00)
    {
        switch (ctx->req->encoding)
        {
        case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
            ctx->emitMandatoryPrefix = ZYDIS_TRUE;
            ctx->mandatoryPrefix = prefix;
            break;
        case ZYDIS_INSTRUCTION_ENCODING_VEX:
            ctx->raw.vex.pp = prefix;
            break;
        case ZYDIS_INSTRUCTION_ENCODING_EVEX:
            ctx->raw.evex.pp = prefix;
            break;
        case ZYDIS_INSTRUCTION_ENCODING_XOP:
            ctx->raw.xop.pp = prefix;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisDetermineInstructionEncoding(ZydisEncoderRequest* ctx)
{
    ZYDIS_ASSERT(ctx);

    for (const ZydisEncoderOperand *op = ctx->operands, 
            *end = ctx->operands + ctx->operandCount
        ; op < end
        ; ++op)
    {

    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFindMatchingDef(
    ZydisEncoderContext* ctx, const ZydisEncoderRequest* req)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(req);

    // Translate requested mode to flags.
    uint8_t modeFlag;
    switch (req->encoding)
    {
    case 16: modeFlag = 0x01; break;
    case 32: modeFlag = 0x02; break;
    case 64: modeFlag = 0x04; break;
    default: return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    }

    // Walk list of candidates.
    const ZydisEncodableInstruction* insns = NULL;
    uint8_t insnCount = ZydisGetEncodableInstructions(req->mnemonic, &insns);
    if (!insnCount) return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    ZYDIS_ASSERT(insns);

    for (uint8_t i = 0; i < insnCount; ++i)
    {
        const ZydisEncodableInstruction* candidateInsn = insns + i;
        if (!(candidateInsn->mode & modeFlag)) goto _nextInsn;

        const ZydisInstructionDefinition* candidateDef = NULL;
        ZydisGetInstructionDefinition(
            candidateInsn->encoding, insns->definitionReference, &candidateDef);
        ZydisOperandDefinition* candidateOperands = NULL;
        uint8_t defOperandCount = ZydisGetOperandDefinitions(candidateDef, &candidateOperands);

        if (req->operandCount > defOperandCount) goto _nextInsn;

        const ZydisOperandDefinition* curDefOperand = candidateOperands;
        for (uint8_t k = 0; k < req->operandCount; ++k)
        {
            curDefOperand = candidateOperands + k;
            const ZydisEncoderOperand* curReqOperand = req->operands + k;

            // Visible operands are always in the front. When we encounter the first hidden
            // operand in the definition and haven't exhausted the request operands yet,
            // it's safe to assume this isn't the instruction we're looking for.
            if (curDefOperand->visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN) goto _nextInsn;

            if (curDefOperand->type != curReqOperand->type) continue;

            // blah blah more checks
        }

        // Make sure we compared either all operands or the remaining operands are hidden.
        if (req->operandCount != defOperandCount && 
            (curDefOperand + 1)->visibility != ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            goto _nextInsn;
        }

        // Still here? Looks like we found our instruction, then!
        ctx->matchingInsn = candidateInsn;
        ctx->matchingDef = candidateDef;
        ctx->matchingOperandCount = req->operandCount;
        return ZYDIS_STATUS_SUCCESS;

    _nextInsn:
        ;
    }

    return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Implementation of public functions                                                             */
/* ============================================================================================== */

#ifdef ZYDIS_ENABLE_FEATURE_DECODER

ZydisStatus ZydisEncoderDecodedInstructionToRequest(
    const ZydisDecodedInstruction* in, ZydisEncoderRequest* out)
{
    ZYDIS_ASSERT(in);
    ZYDIS_ASSERT(out);

    (void) in; (void) out;
    // TODO

    return ZYDIS_STATUS_SUCCESS;
}

#endif

ZydisStatus ZydisEncoderEncodeInstruction(void* buffer, size_t* bufferLen,
    ZydisEncoderRequest* request)
{
    if (!request || !bufferLen || request->operandCount > ZYDIS_ARRAY_SIZE(request->operands))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    if (!buffer || !*bufferLen) return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;

    ZydisEncoderContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.buffer = (uint8_t*)buffer;
    ctx.bufferLen = *bufferLen;
    ctx.writeOffs = 0;
    ctx.req = request;
    *bufferLen = 0;

    // Mask out attributes that can't be set explicitly by user.
    request->attributes &= ZYDIS_USER_ENCODABLE_ATTRIB_MASK;

    // Search matching instruction, collect information about what needs to be
    // encoded, what prefixes are required, etc.
    ZYDIS_CHECK(ZydisFindMatchingDef(&ctx, request));
    ctx.raw.opcode = ctx.matchingInsn->opcode;

    // Check compatibility of requested prefixes to found instruction.
    // TODO
    //if (ctx.req->attributes)
    //{
    //    for (size_t i = 0; i < ZYDIS_ARRAY_SIZE(prefixAcceptMap); ++i)
    //    {
    //        if (ctx.req->attributes & prefixAcceptMap[i].has &&
    //            !(ctx.matchingDef->attribs & prefixAcceptMap[i].accepts))
    //        {
    //            // TODO: Better status.
    //            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
    //        }
    //    }
    //}

    // Determine required prefixes.
    switch (ctx.matchingInsn->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        request->attributes |= ZYDIS_ATTRIB_HAS_EVEX;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        request->attributes |= ZYDIS_ATTRIB_HAS_VEX;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        request->attributes |= ZYDIS_ATTRIB_HAS_XOP;
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

    // Prepare prefix bits.
    ctx.raw.evex.B  = ctx.matchingInsn->evexB;
    ctx.raw.evex.L  = ctx.matchingInsn->vectorLength & 0x01;
    ctx.raw.evex.L2 = ctx.matchingInsn->vectorLength & 0x02;
    ctx.raw.vex.L   = ctx.matchingInsn->vectorLength & 0x01;
    if (ctx.matchingInsn->rexW)
    {
        ctx.raw.rex.W = 1;
        request->attributes |= ZYDIS_ATTRIB_HAS_REX;
    }
    ZYDIS_CHECK(ZydisPrepareMandatoryPrefixes(&ctx));

    // Prepare opcode.
    ZYDIS_CHECK(ZydisPrepareOpcode(&ctx));

    // Some instructions have additional opcode bits encoded in ModRM.reg.
    if (ctx.matchingInsn->modrmReg != 0xFF)
    {
        ctx.raw.modrm.reg = ctx.matchingInsn->modrmReg;
    }

    // Analyze and prepare operands.
    if (request->operandCount > ZYDIS_ARRAY_SIZE(request->operands))
    {
        // TODO: Better status?
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    //for (size_t i = 0; i < ctx.matchingDef->operandCount; ++i)
    //{
    //    ZYDIS_CHECK(ZydisPrepareOperand(
    //        &ctx, &request->operands[i], 
    //        &ctx.matchingDef->operands[i]
    //    ));
    //}
    //
    // Do actual encoding work.
    ZYDIS_CHECK(ZydisEmitLegacyPrefixes(&ctx));
    if (request->attributes & ZYDIS_ATTRIB_HAS_REX  ) ZYDIS_CHECK(ZydisEmitREX  (&ctx));
    if (request->attributes & ZYDIS_ATTRIB_HAS_VEX  ) ZYDIS_CHECK(ZydisEmitVEX  (&ctx));
    if (request->attributes & ZYDIS_ATTRIB_HAS_EVEX ) ZYDIS_CHECK(ZydisEmitEVEX (&ctx));
    if (request->attributes & ZYDIS_ATTRIB_HAS_XOP  ) ZYDIS_CHECK(ZydisEmitXOP  (&ctx));

    if (ctx.emitMandatoryPrefix) ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.mandatoryPrefix));
    
    for (uint8_t i = 0; i < ctx.opcodeMapPrefixLen; ++i)
    {
        ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.opcodeMapPrefix[i]));
    }

    ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.raw.opcode));

    if (request->attributes & ZYDIS_ATTRIB_HAS_MODRM) ZYDIS_CHECK(ZydisEmitModRM(&ctx));
    if (request->attributes & ZYDIS_ATTRIB_HAS_SIB  ) ZYDIS_CHECK(ZydisEmitSIB  (&ctx));

    if (ctx.dispBitSize   ) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.disp,    ctx.dispBitSize   ));
    if (ctx.immBitSizes[0]) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.imms[0], ctx.immBitSizes[0]));
    if (ctx.immBitSizes[1]) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.imms[1], ctx.immBitSizes[1]));

    *bufferLen = ctx.writeOffs;
    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
