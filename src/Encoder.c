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

/* ============================================================================================== */
/* Internal context and table types                                                               */
/* ============================================================================================== */

typedef uint32_t ZydisSemanticOperandTypeMask;

typedef struct ZydisInstructionQuery_
{
    ZydisSemanticOperandTypeMask semOperandTypeMasks[ZYDIS_ENCODER_MAX_OPERANDS];
    ZydisBool require66;
    ZydisBool require67;
    ZydisBool requireREXW;
    uint8_t eosz;
    uint8_t easz;
} ZydisInstructionQuery;

typedef struct ZydisInstructionMatch_
{
    const ZydisInstructionQuery* q;
    const ZydisEncodableInstruction* insn;
    const ZydisInstructionDefinition* def;
    uint8_t operandCount;
    const ZydisOperandDefinition* operands;
    uint8_t derivedImmSizes[ZYDIS_ENCODER_MAX_OPERANDS];
} ZydisInstructionMatch;

typedef struct ZydisRawInstruction_
{
    ZydisInstructionAttributes derivedAttrs;
    uint8_t mandatoryPrefix; // 0 = not present
    uint8_t opcodeMapPrefixLen;
    uint8_t opcodeMapPrefix[3];
    uint8_t opcode;
    ZydisBool didWriteFirstHalfIS4;

    struct
    {
        int64_t val;
        uint8_t size;
    } disp;
    struct
    {
        uint64_t val;
        uint8_t size;
    } imms[2];
    struct
    {
        // REX bits
        uint8_t W;
        uint8_t R;
        uint8_t X;
        uint8_t B;

        // XOP/VEX bits
        uint8_t mm;
        uint8_t vvvv;
        uint8_t L;
        uint8_t pp;

        // EVEX/MVEX bits
        uint8_t R2;
        uint8_t z;
        uint8_t L2;
        uint8_t b;
        uint8_t V2;
        uint8_t mask; // `.aaa` / `.kkk`
        uint8_t SSS;
        uint8_t E;
    } bits;
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
} ZydisRawInstruction;

typedef struct ZydisEncoderContext_
{
    // Input parameters.
    uint8_t* buffer;
    size_t bufferLen;
    size_t writeOffs;
    const ZydisEncoderRequest* req;

    ZydisRawInstruction raw;
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

static ZydisStatus ZydisEmitLegacyPrefixes(ZydisEncoderContext* ctx, 
    const ZydisInstructionQuery* q)
{
    ZYDIS_ASSERT(ctx);
    ZydisInstructionAttributes attribs = ctx->raw.derivedAttrs;

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
    if (q->require66)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0x66));
    }
    if (q->require67)
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
        (ctx->raw.bits.W & 0x01) << 3 |
        (ctx->raw.bits.R & 0x01) << 2 |
        (ctx->raw.bits.X & 0x01) << 1 |
        (ctx->raw.bits.B & 0x01) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitVEX(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);

    // Can we use short 2-byte VEX encoding?
    if (ctx->raw.bits.X == 0 && ctx->raw.bits.B == 0 &&
        ctx->raw.bits.W == 0 && ctx->raw.bits.mm == 1)
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xC5));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            (~ctx->raw.bits.R    & 0x01) << 7 |
            (~ctx->raw.bits.vvvv & 0x0F) << 3 |
            ( ctx->raw.bits.L    & 0x01) << 2 |
            ( ctx->raw.bits.pp   & 0x03) << 0
        ));
    }
    // Nope, use 3-byte VEX.
    else
    {
        ZYDIS_CHECK(ZydisEmitByte(ctx, 0xC4));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            (~ctx->raw.bits.R  & 0x01) << 7 |
            (~ctx->raw.bits.X  & 0x01) << 6 |
            (~ctx->raw.bits.B  & 0x01) << 5 |
            ( ctx->raw.bits.mm & 0x1F) << 0
        ));
        ZYDIS_CHECK(ZydisEmitByte(
            ctx,
            ( ctx->raw.bits.W    & 0x01) << 7 |
            (~ctx->raw.bits.vvvv & 0x0F) << 3 |
            ( ctx->raw.bits.L    & 0x01) << 2 |
            ( ctx->raw.bits.pp   & 0x03) << 0
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
        (ctx->raw.bits.R  & 0x01) << 7 |
        (ctx->raw.bits.X  & 0x01) << 6 |
        (ctx->raw.bits.B  & 0x01) << 5 |
        (ctx->raw.bits.R2 & 0x01) << 4 |
        (ctx->raw.bits.mm & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx, 
        (ctx->raw.bits.W    & 0x01) << 7 |
        (ctx->raw.bits.vvvv & 0x0F) << 3 |
        (ctx->raw.bits.pp   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.bits.z    & 0x01) << 7 |
        (ctx->raw.bits.L2   & 0x01) << 6 |
        (ctx->raw.bits.L    & 0x01) << 5 |
        (ctx->raw.bits.b    & 0x01) << 4 |
        (ctx->raw.bits.V2   & 0x01) << 3 |
        (ctx->raw.bits.mask & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitMVEX(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(ctx, 0x62));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.bits.R  & 0x01) << 7 |
        (ctx->raw.bits.X  & 0x01) << 6 |
        (ctx->raw.bits.B  & 0x01) << 5 |
        (ctx->raw.bits.R2 & 0x01) << 4 |
        (ctx->raw.bits.mm & 0x0F) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.bits.W    & 0x01) << 7 |
        (ctx->raw.bits.vvvv & 0x0F) << 3 |
        (ctx->raw.bits.pp   & 0x03) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.bits.E    & 0x01) << 7 |
        (ctx->raw.bits.SSS  & 0x07) << 4 |
        (ctx->raw.bits.V2   & 0x01) << 3 |
        (ctx->raw.bits.mask & 0x07) << 0
    ));
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisEmitXOP(ZydisEncoderContext* ctx)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_CHECK(ZydisEmitByte(ctx, 0x8F));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.bits.R  & 0x01) << 7 |
        (ctx->raw.bits.X  & 0x01) << 6 |
        (ctx->raw.bits.B  & 0x01) << 5 |
        (ctx->raw.bits.mm & 0x1F) << 0
    ));
    ZYDIS_CHECK(ZydisEmitByte(
        ctx,
        (ctx->raw.bits.W    & 0x01) << 7 |
        (ctx->raw.bits.vvvv & 0x0F) << 3 |
        (ctx->raw.bits.L    & 0x01) << 2 |
        (ctx->raw.bits.pp   & 0x03) << 0
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
/* Table lookup and value translation helpers                                                     */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   For a `ZydisEncoderOperand`, compose a mask of permitted semantic operand types.
 * @param   op      The operand to compute the mask for.
 * @param   mask    The output parameter receiving the derived mask.
 * @returns A zydis error code.
 */
static ZydisStatus ZydisSemanticOperandTypeDeriveMask(
    const ZydisEncoderOperand* op, ZydisSemanticOperandTypeMask* mask)
{
    ZYDIS_ASSERT(op);
    ZYDIS_ASSERT(mask);

    switch (op->type)
    {
    case ZYDIS_OPERAND_TYPE_REGISTER:
        switch (ZydisRegisterGetClass(op->reg))
        {
        case ZYDIS_REGCLASS_GPR8:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_GPR8;
            break;
        case ZYDIS_REGCLASS_GPR16:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_GPR16 |
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR16_32_32 |
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR16_32_32;
            break;
        case ZYDIS_REGCLASS_GPR32:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_GPR32 |
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR16_32_64 |
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR32_32_64 |
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR16_32_32;
            break;
        case ZYDIS_REGCLASS_GPR64:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_GPR64 | 
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR16_32_64 |
                    1 << ZYDIS_SEMANTIC_OPTYPE_GPR32_32_64;
            break;
        case ZYDIS_REGCLASS_X87:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_FPR;
            break;
        case ZYDIS_REGCLASS_MMX:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_MMX;
            break;
        case ZYDIS_REGCLASS_XMM:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_XMM;
            break;
        case ZYDIS_REGCLASS_YMM:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_YMM;
            break;
        case ZYDIS_REGCLASS_ZMM:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_ZMM;
            break;
        case ZYDIS_REGCLASS_FLAGS:
        case ZYDIS_REGCLASS_IP:
            return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
        case ZYDIS_REGCLASS_SEGMENT:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_SREG;
            break;
        case ZYDIS_REGCLASS_TEST:
            // TODO
            ZYDIS_UNREACHABLE;
        case ZYDIS_REGCLASS_CONTROL:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_CR;
            break;
        case ZYDIS_REGCLASS_DEBUG:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_DR;
            break;
        case ZYDIS_REGCLASS_MASK:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_MASK;
            break;
        case ZYDIS_REGCLASS_BOUND:
            *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_BND;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
        *mask |= 1 << ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG;
        break;
    case ZYDIS_OPERAND_TYPE_MEMORY:
        *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_MEM |
                1 << ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBX |
                1 << ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBY |
                1 << ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBZ |
                1 << ZYDIS_SEMANTIC_OPTYPE_AGEN |
                1 << ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_MEM;
        break;
    case ZYDIS_OPERAND_TYPE_POINTER:
        *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_PTR;
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        *mask = 1 << ZYDIS_SEMANTIC_OPTYPE_IMM |
                1 << ZYDIS_SEMANTIC_OPTYPE_REL |
                1 << ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_IMM1;
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static uint8_t ZydisUImmGetMinSize(uint64_t imm)
{
    if (imm <= UINT8_MAX ) return 8;
    if (imm <= UINT16_MAX) return 16;
    if (imm <= UINT32_MAX) return 32;
    return 64;
}

static uint8_t ZydisSImmGetMinSize(int64_t imm)
{
    if (imm <= INT8_MAX  && imm >= INT8_MIN ) return 8;
    if (imm <= INT16_MAX && imm >= INT16_MIN) return 16;
    if (imm <= INT32_MAX && imm >= INT32_MIN) return 32;
    return 64;
}

static ZydisBool ZydisOperandEncodingImmIsSigned(ZydisOperandEncoding enc)
{
    switch (enc)
    {
    case ZYDIS_OPERAND_ENCODING_DISP8:
    case ZYDIS_OPERAND_ENCODING_DISP16:
    case ZYDIS_OPERAND_ENCODING_DISP32:
    case ZYDIS_OPERAND_ENCODING_DISP64:
    case ZYDIS_OPERAND_ENCODING_DISP16_32_64:
    case ZYDIS_OPERAND_ENCODING_DISP32_32_64:
    case ZYDIS_OPERAND_ENCODING_DISP16_32_32:
    case ZYDIS_OPERAND_ENCODING_SIMM8:
    case ZYDIS_OPERAND_ENCODING_SIMM16:
    case ZYDIS_OPERAND_ENCODING_SIMM32:
    case ZYDIS_OPERAND_ENCODING_SIMM64:
    case ZYDIS_OPERAND_ENCODING_SIMM16_32_64:
    case ZYDIS_OPERAND_ENCODING_SIMM32_32_64:
    case ZYDIS_OPERAND_ENCODING_SIMM16_32_32:
    case ZYDIS_OPERAND_ENCODING_JIMM8:
    case ZYDIS_OPERAND_ENCODING_JIMM16:
    case ZYDIS_OPERAND_ENCODING_JIMM32:
    case ZYDIS_OPERAND_ENCODING_JIMM64:
    case ZYDIS_OPERAND_ENCODING_JIMM16_32_64:
    case ZYDIS_OPERAND_ENCODING_JIMM32_32_64:
    case ZYDIS_OPERAND_ENCODING_JIMM16_32_32:
        return ZYDIS_TRUE;
    case ZYDIS_OPERAND_ENCODING_UIMM8:
    case ZYDIS_OPERAND_ENCODING_UIMM16:
    case ZYDIS_OPERAND_ENCODING_UIMM32:
    case ZYDIS_OPERAND_ENCODING_UIMM64:
    case ZYDIS_OPERAND_ENCODING_UIMM16_32_64:
    case ZYDIS_OPERAND_ENCODING_UIMM32_32_64:
    case ZYDIS_OPERAND_ENCODING_UIMM16_32_32:
        return ZYDIS_FALSE;
    default: 
        ZYDIS_UNREACHABLE;
    }
}

static ZydisStatus ZydisOperandEncodingGetEffectiveImmSize(
    ZydisOperandEncoding enc, ZydisMachineMode machineMode, uint8_t* esz)
{
    switch (enc)
    {
    case ZYDIS_OPERAND_ENCODING_DISP8:
    case ZYDIS_OPERAND_ENCODING_SIMM8:
    case ZYDIS_OPERAND_ENCODING_UIMM8:
    case ZYDIS_OPERAND_ENCODING_JIMM8:
        *esz = 8;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_OPERAND_ENCODING_DISP16:
    case ZYDIS_OPERAND_ENCODING_SIMM16:
    case ZYDIS_OPERAND_ENCODING_UIMM16:
    case ZYDIS_OPERAND_ENCODING_JIMM16:
        *esz = 16;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_OPERAND_ENCODING_DISP32:
    case ZYDIS_OPERAND_ENCODING_SIMM32:
    case ZYDIS_OPERAND_ENCODING_UIMM32:
    case ZYDIS_OPERAND_ENCODING_JIMM32:
        *esz = 32;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_OPERAND_ENCODING_DISP64:
    case ZYDIS_OPERAND_ENCODING_SIMM64:
    case ZYDIS_OPERAND_ENCODING_UIMM64:
    case ZYDIS_OPERAND_ENCODING_JIMM64:
        *esz = 64;
        return ZYDIS_STATUS_SUCCESS;
    case ZYDIS_OPERAND_ENCODING_DISP16_32_64:
    case ZYDIS_OPERAND_ENCODING_SIMM16_32_64:
    case ZYDIS_OPERAND_ENCODING_JIMM16_32_64:
    case ZYDIS_OPERAND_ENCODING_UIMM16_32_64:
        switch (machineMode)
        {
        case 16: *esz = 16; return ZYDIS_STATUS_SUCCESS;
        case 32: *esz = 32; return ZYDIS_STATUS_SUCCESS;
        case 64: *esz = 64; return ZYDIS_STATUS_SUCCESS;
        default: return ZYDIS_STATUS_INVALID_PARAMETER;
        }
    case ZYDIS_OPERAND_ENCODING_DISP32_32_64:
    case ZYDIS_OPERAND_ENCODING_SIMM32_32_64:
    case ZYDIS_OPERAND_ENCODING_UIMM32_32_64:
    case ZYDIS_OPERAND_ENCODING_JIMM32_32_64:
        switch (machineMode)
        {
        case 16: *esz = 32; return ZYDIS_STATUS_SUCCESS;
        case 32: *esz = 32; return ZYDIS_STATUS_SUCCESS;
        case 64: *esz = 64; return ZYDIS_STATUS_SUCCESS;
        default: return ZYDIS_STATUS_INVALID_PARAMETER;
        }
    case ZYDIS_OPERAND_ENCODING_DISP16_32_32:
    case ZYDIS_OPERAND_ENCODING_SIMM16_32_32:
    case ZYDIS_OPERAND_ENCODING_UIMM16_32_32:
    case ZYDIS_OPERAND_ENCODING_JIMM16_32_32:
        switch (machineMode)
        {
        case 16: *esz = 16; return ZYDIS_STATUS_SUCCESS;
        case 32: *esz = 32; return ZYDIS_STATUS_SUCCESS;
        case 64: *esz = 32; return ZYDIS_STATUS_SUCCESS;
        default: return ZYDIS_STATUS_INVALID_PARAMETER;
        }
    default: 
        ZYDIS_UNREACHABLE;
    }
}

static uint8_t ZydisSizeToFlag(uint8_t size)
{
    switch (size)
    {
    case 16: return 1 << 0;
    case 32: return 1 << 1;
    case 64: return 1 << 2;
    default: return 0;
    }
}

static ZydisBool ZydisRegIsBP(ZydisRegister reg)
{
    return reg == ZYDIS_REGISTER_BPL ||
           reg == ZYDIS_REGISTER_BP  ||
           reg == ZYDIS_REGISTER_EBP ||
           reg == ZYDIS_REGISTER_RBP;
}

static ZydisBool ZydisRegIsSP(ZydisRegister reg)
{
    return reg == ZYDIS_REGISTER_SPL ||
           reg == ZYDIS_REGISTER_SP  ||
           reg == ZYDIS_REGISTER_ESP ||
           reg == ZYDIS_REGISTER_RSP;
}

static ZydisBool ZydisRegIsIP(ZydisRegister reg)
{
    return reg == ZYDIS_REGISTER_IP  ||
           reg == ZYDIS_REGISTER_EIP ||
           reg == ZYDIS_REGISTER_RIP;
}

static ZydisBool ZydisRegIsStack(ZydisRegister reg)
{
    return ZydisRegIsSP(reg) || ZydisRegIsBP(reg);
}

/* ---------------------------------------------------------------------------------------------- */
/* Preparation functions. Parse encoder request, determine required bytes and prefixes.           */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisPrepareOpcode(ZydisEncoderContext* ctx, const ZydisInstructionMatch* match)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(match);

    // Put opcode map prefix(es), if required.
    switch (ctx->req->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        switch (match->insn->opcodeMap)
        {
        case ZYDIS_OPCODE_MAP_0F:
            ctx->raw.opcodeMapPrefix[ctx->raw.opcodeMapPrefixLen++] = 0x0F;
            break;
        case ZYDIS_OPCODE_MAP_0F38:
            ctx->raw.opcodeMapPrefix[ctx->raw.opcodeMapPrefixLen++] = 0x0F;
            ctx->raw.opcodeMapPrefix[ctx->raw.opcodeMapPrefixLen++] = 0x38;
            break;
        case ZYDIS_OPCODE_MAP_0F3A:
            ctx->raw.opcodeMapPrefix[ctx->raw.opcodeMapPrefixLen++] = 0x0F;
            ctx->raw.opcodeMapPrefix[ctx->raw.opcodeMapPrefixLen++] = 0x3A;
            break;
        case ZYDIS_OPCODE_MAP_DEFAULT:
            break; // Nothing to do.
        default:
            ZYDIS_UNREACHABLE;
        }
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ctx->raw.bits.mm = match->insn->opcodeMap;
        ZYDIS_ASSERT(ctx->raw.bits.mm <= 0x03);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        ctx->raw.bits.mm = match->insn->opcodeMap;
        ZYDIS_ASSERT(ctx->raw.bits.mm <= 0x03);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ctx->raw.bits.mm =
            match->insn->opcodeMap - ZYDIS_OPCODE_MAP_XOP8 + 0x08;
        ZYDIS_ASSERT(ctx->raw.bits.mm >= 0x08);
        ZYDIS_ASSERT(ctx->raw.bits.mm <= 0x0B);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareRegOperand(ZydisEncoderContext* ctx,
    ZydisRegister reg, char topBitDst)
{
    ZYDIS_ASSERT(ctx);

    int16_t regID = ZydisRegisterGetId(reg);
    if (regID == -1) return ZYDIS_STATUS_INVALID_PARAMETER;

    uint8_t lowerBits = (regID & 0x07) >> 0;
    uint8_t topBit    = (regID & 0x08) >> 3;

    switch (topBitDst)
    {
        case 'B': ctx->raw.modrm.rm  = lowerBits; break;
        case 'R': ctx->raw.modrm.reg = lowerBits; break;
        case 'X': ctx->raw.sib.index = lowerBits; break;
        default: ZYDIS_UNREACHABLE;
    }

    // No top bit? Quick exit.
    if (!topBit) return ZYDIS_STATUS_SUCCESS;
    
    if ((ctx->req->encoding == ZYDIS_INSTRUCTION_ENCODING_DEFAULT ||
        ctx->req->encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW) && topBit)
    {
        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_REX;
    }

    switch (topBitDst)
    {
        case 'B': ctx->raw.bits.B = topBit; break;
        case 'R': ctx->raw.bits.R = topBit; break;
        case 'X': ctx->raw.bits.X = topBit; break;
        default: ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareSegmentPrefix(ZydisEncoderContext* ctx,
    ZydisRegister segment, ZydisRegister base)
{
    // Segment prefix required?
    switch (segment)
    {
    case ZYDIS_REGISTER_ES:
        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SEGMENT_ES;
        break;
    case ZYDIS_REGISTER_SS:
        if (!ZydisRegIsStack(base))
        {
            ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SEGMENT_SS;
        }
        break;
    case ZYDIS_REGISTER_CS:
        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SEGMENT_CS;
        break;
    case ZYDIS_REGISTER_DS:
        if (ZydisRegIsStack(base))
        {
            ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SEGMENT_DS;
        }
        break;
    case ZYDIS_REGISTER_FS:
        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SEGMENT_FS;
        break;
    case ZYDIS_REGISTER_GS:
        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SEGMENT_GS;
        break;
    default:
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO: Better status.
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareMemoryOperand(ZydisEncoderContext* ctx,
    const ZydisEncoderOperand* operand, const ZydisInstructionMatch* match)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(ctx->req);
    ZYDIS_ASSERT(operand);

    ZYDIS_CHECK(ZydisPrepareSegmentPrefix(ctx, operand->mem.segment, operand->mem.base));

    // Absolute memory access? Special case.
    if (operand->mem.base == ZYDIS_REGISTER_NONE)
    {
        ctx->raw.disp.val = operand->mem.disp;
        ctx->raw.disp.size = 32;

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
            ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SIB;
        }

        return ZYDIS_STATUS_SUCCESS;
    }

    // rIP relative addressing? Special case.
    if (ZydisRegIsIP(operand->mem.base))
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

        ctx->raw.disp.val  = operand->mem.disp;
        ctx->raw.disp.size = 32;
        ctx->raw.modrm.mod = 0x00;
        ctx->raw.modrm.rm  = 0x05 /* RIP relative mem */;

        return ZYDIS_STATUS_SUCCESS;
    }

    // Process base register.
    ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->mem.base, 'B'));

    // SIB byte required? rSP can only be encoded with SIB.
    if (operand->mem.index || operand->mem.scale || ZydisRegIsSP(operand->mem.base))
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
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, operand->mem.index, 'X'));
        }
        else
        {
            ctx->raw.sib.index = 0x04 /* no index */;
        }
        
        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_SIB;
    }

    // Has displacement or is rBP and we have no SIB?
    // rBP can't be ModRM-encoded without a disp.
    if (operand->mem.disp || (!(ctx->req->attributes & ZYDIS_ATTRIB_HAS_SIB)
        && ZydisRegIsBP(operand->mem.base)))
    {
        if (ZydisSImmGetMinSize(operand->mem.disp) == 8)
        {
            ctx->raw.disp.size = 8;
            ctx->raw.modrm.mod = 0x01 /* 8 bit disp */;
        }
        else
        {
            ctx->raw.disp.size = 32;
            ctx->raw.modrm.mod = 0x02 /* 32 bit disp */;
        }
        ctx->raw.disp.val = operand->mem.disp;
    }
    // No displacement.
    else
    {
        ctx->raw.modrm.mod = 0x00 /* no disp */;
    }

    // Verify if the `.reg` and `.rm` values we calculated are permitted for this
    // instruction. We don't backtrace for a different definition here in that case
    // since the instructions with such restrictions don't have alternate encodings 
    // that would allow the instruction to be encoded anyway.
    if ((!match->insn->forceModrmRm  && !(1 << ctx->raw.modrm.rm  & match->insn->modrmRm )) ||
        (!match->insn->forceModrmReg && !(1 << ctx->raw.modrm.reg & match->insn->modrmReg)))
    {
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrepareOperand(ZydisEncoderContext* ctx, 
    ZydisInstructionMatch* match, uint8_t n)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(n < ZYDIS_ARRAY_SIZE(ctx->req->operands));
    ZYDIS_ASSERT(n < match->operandCount);
    const ZydisEncoderOperand* reqOperand = ctx->req->operands + n;
    const ZydisOperandDefinition* operandDef = match->operands + n;

    switch (operandDef->op.encoding)
    {
    case ZYDIS_OPERAND_ENCODING_NONE:
    {
        // For some encodings, we have to switch on the sem op type.
        if (operandDef->type == ZYDIS_SEMANTIC_OPTYPE_MOFFS)
        {
            ZYDIS_CHECK(ZydisPrepareSegmentPrefix(
                ctx, reqOperand->mem.segment, ZYDIS_REGISTER_NONE
            ));
            ctx->raw.imms[0].val = reqOperand->mem.disp;
            ctx->raw.imms[0].size = reqOperand->mem.dispSize;
        }
    } break;
    case ZYDIS_OPERAND_ENCODING_MODRM_REG:
    {
        ZYDIS_ASSERT(!ctx->raw.modrm.reg);
        ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, reqOperand->reg, 'R'));
    } break;
    case ZYDIS_OPERAND_ENCODING_MODRM_RM:
    {
        ZYDIS_ASSERT(!ctx->raw.modrm.mod);
        ZYDIS_ASSERT(!ctx->raw.modrm.rm);
        ZYDIS_ASSERT(!ctx->raw.sib.base);
        ZYDIS_ASSERT(!ctx->raw.sib.index);
        ZYDIS_ASSERT(!ctx->raw.sib.scale);

        // Memory operand?
        if (reqOperand->type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            ZYDIS_CHECK(ZydisPrepareMemoryOperand(ctx, reqOperand, match));
        }
        // Nope, register.
        else if (reqOperand->type == ZYDIS_OPERAND_TYPE_REGISTER)
        {
            ZYDIS_CHECK(ZydisPrepareRegOperand(ctx, reqOperand->reg, 'B'));
            ctx->raw.modrm.mod = 0x03 /* reg */;
        }

        ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_MODRM;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_OPCODE:
    {
        int16_t reg = ZydisRegisterGetId(reqOperand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        ctx->raw.opcode += reg & 0x07;
        ctx->raw.bits.B = (reg & 0x08) >> 3;
        if (ctx->raw.bits.B) ctx->raw.derivedAttrs |= ZYDIS_ATTRIB_HAS_REX;
        break;
    }
    case ZYDIS_OPERAND_ENCODING_NDSNDD:
    {
        int16_t reg = ZydisRegisterGetId(reqOperand->reg);
        if (reg == -1) return ZYDIS_STATUS_INVALID_PARAMETER;
        ctx->raw.bits.vvvv = ctx->raw.bits.vvvv = ctx->raw.bits.vvvv = reg & 0x0F;
        break;
    }        
    case ZYDIS_OPERAND_ENCODING_MASK:
    {
        ctx->raw.bits.mask = reqOperand->reg - ZYDIS_REGISTER_K0;
    } break;
    case ZYDIS_OPERAND_ENCODING_IS4:
    {
        if (!ctx->raw.didWriteFirstHalfIS4)
        {
            ctx->raw.imms[0].size = 8;
            ctx->raw.imms[0].val |= reqOperand->imm.u & 0x0F;
            ctx->raw.didWriteFirstHalfIS4 = ZYDIS_TRUE;
        }
        else
        {
            ZYDIS_ASSERT(ctx->raw.imms[0].size == 8);
            ctx->raw.imms[0].val |= (reqOperand->imm.u & 0x0F) << 4;
        }
        break;
    }
    case ZYDIS_OPERAND_ENCODING_SIMM8:
    case ZYDIS_OPERAND_ENCODING_UIMM8:
    case ZYDIS_OPERAND_ENCODING_JIMM8:
    case ZYDIS_OPERAND_ENCODING_SIMM16:
    case ZYDIS_OPERAND_ENCODING_UIMM16:
    case ZYDIS_OPERAND_ENCODING_JIMM16:
    case ZYDIS_OPERAND_ENCODING_SIMM32:
    case ZYDIS_OPERAND_ENCODING_UIMM32:
    case ZYDIS_OPERAND_ENCODING_JIMM32:
    case ZYDIS_OPERAND_ENCODING_UIMM64:
    case ZYDIS_OPERAND_ENCODING_SIMM64:
    case ZYDIS_OPERAND_ENCODING_JIMM64:
    {
        uint8_t immIdx = ctx->raw.imms[0].size ? 1 : 0;
        ctx->raw.imms[immIdx].val = reqOperand->imm.u;
        ctx->raw.imms[immIdx].size = match->derivedImmSizes[n];
        break;
    }
    default:
        ZYDIS_UNREACHABLE;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static void ZydisPrepareMandatoryPrefixes(ZydisEncoderContext* ctx,
    ZydisInstructionMatch* match)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(match);

    // Is a prefix mandatory? 0x00 is a sentinel value for `None` in the table.
    uint8_t prefix = match->insn->mandatoryPrefix;
    if (prefix != 0x00)
    {
        switch (ctx->req->encoding)
        {
        case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
            ctx->raw.mandatoryPrefix = prefix;
            break;
        case ZYDIS_INSTRUCTION_ENCODING_XOP:
        case ZYDIS_INSTRUCTION_ENCODING_VEX:
        case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        case ZYDIS_INSTRUCTION_ENCODING_MVEX:
            ctx->raw.bits.pp = prefix;
            break;
        default:
            ZYDIS_UNREACHABLE;
        }
    }
}

static ZydisStatus ZydisRequestToInstructionQuery(
    ZydisEncoderContext* ctx, const ZydisEncoderRequest* req, ZydisInstructionQuery* q)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(req);
    ZYDIS_ASSERT(q);

    // Walk list of requested operands, derive possible encodings
    // and perform additional sanity checks.
    q->require66 = ZYDIS_FALSE;
    q->require67 = ZYDIS_FALSE;
    q->requireREXW = ZYDIS_FALSE;
    q->eosz = req->machineMode;
    q->easz = req->machineMode;
    for (uint8_t i = 0; i < req->operandCount; ++i)
    {
        const ZydisEncoderOperand* curReqOperand = req->operands + i;

        // Do we need any operand size overrides?
        if (curReqOperand->type == ZYDIS_OPERAND_TYPE_REGISTER)
        {
            switch (ZydisRegisterGetClass(curReqOperand->reg))
            {
            case ZYDIS_REGCLASS_GPR16:
                q->eosz = 16;
                switch (req->machineMode)
                {
                case 16: break; // Default mode.
                case 32:
                case 64: q->require66 = ZYDIS_TRUE; break;
                default: return ZYDIS_STATUS_INVALID_PARAMETER;
                }
                break;
            case ZYDIS_REGCLASS_GPR32:
                q->eosz = 32;
                switch (req->machineMode)
                {
                case 16: q->require66 = ZYDIS_TRUE; break;
                case 32:
                case 64: break; // Default mode.
                default: return ZYDIS_STATUS_INVALID_PARAMETER;
                }
                break;
            case ZYDIS_REGCLASS_GPR64:
                q->eosz = 64;
                switch (req->machineMode)
                {
                case 16: 
                case 32: return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
                case 64: q->requireREXW = ZYDIS_TRUE; break;
                default: return ZYDIS_STATUS_INVALID_PARAMETER;
                }
                break;
            default:
                ; // Other registers can't be operand-scaled. 
            }
        }

        // Address size overrides?
        if (curReqOperand->type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            // Verify base and index have the same register class, if present.
            ZydisRegisterClass baseRegClass = ZydisRegisterGetClass(curReqOperand->mem.base);
            if (curReqOperand->mem.base != ZYDIS_REGISTER_NONE &&
                curReqOperand->mem.index != ZYDIS_REGISTER_NONE &&
                baseRegClass != ZydisRegisterGetClass(curReqOperand->mem.index))
            {
                return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
            }

            // Address size prefix required?
            switch (baseRegClass)
            {
            case ZYDIS_REGCLASS_GPR16: q->easz = 16; break;
            case ZYDIS_REGCLASS_GPR32: q->easz = 32; break;
            case ZYDIS_REGCLASS_GPR64: q->easz = 64; break;
            default:
                switch (baseRegClass)
                {
                case ZYDIS_REGISTER_IP:  q->easz = 16; break;
                case ZYDIS_REGISTER_EIP: q->easz = 32; break;
                case ZYDIS_REGISTER_RIP: q->easz = 64; break;
                default:
                    ; // Other registers can't be address-scaled.
                }
            }

            switch (q->easz)
            {
            case 16:
                switch (ctx->req->machineMode)
                {
                case 16: break; // Default mode.
                case 32: q->require67 = ZYDIS_TRUE; break;
                case 64: return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
                default: return ZYDIS_STATUS_INVALID_PARAMETER;
                }
                break;
            case 32:
                switch (ctx->req->machineMode)
                {
                case 16: q->require67 = ZYDIS_TRUE; break;
                case 32: break; // Default mode.
                case 64: q->require67 = ZYDIS_TRUE; break;
                default: return ZYDIS_STATUS_INVALID_PARAMETER;
                }
                break;
            case 64:
                if (ctx->req->machineMode != 64)
                {
                    return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
                }
                break;
            default:
                ; // Don't care.
            }
        }

        ZYDIS_CHECK(ZydisSemanticOperandTypeDeriveMask(
            req->operands + i, q->semOperandTypeMasks + i
        ));
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFindMatchingDef(
    ZydisEncoderContext* ctx, const ZydisEncoderRequest* req, const ZydisInstructionQuery* q,
    ZydisInstructionMatch* match)
{
    ZYDIS_ASSERT(ctx);
    ZYDIS_ASSERT(req);
    ZYDIS_ASSERT(match);
    (void)ctx;

    // Translate sizes to flags.
    uint8_t modeFlag = ZydisSizeToFlag(req->machineMode);
    if (!modeFlag) return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    uint8_t easzFlag = ZydisSizeToFlag(q->easz);
    uint8_t eoszFlag = ZydisSizeToFlag(q->eosz);
    ZYDIS_ASSERT(easzFlag && eoszFlag);

    // Walk list of candidates.
    const ZydisEncodableInstruction* insns = NULL;
    uint8_t insnCount = ZydisGetEncodableInstructions(req->mnemonic, &insns);
    if (!insnCount) return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION; // TODO
    ZYDIS_ASSERT(insns);

    for (const ZydisEncodableInstruction *candidateInsn = insns, 
        *insnsEnd = insns + insnCount
        ; candidateInsn < insnsEnd
        ; ++candidateInsn)
    {
        if (!(candidateInsn->mode & modeFlag)) goto _nextInsn;
        //if (!candidateInsn->rexW && q->requireREXW) goto _nextInsn;
        if (!(candidateInsn->addressSize & easzFlag)) goto _nextInsn;
        if (!(candidateInsn->operandSize & eoszFlag)) goto _nextInsn;

        const ZydisInstructionDefinition* candidateDef = NULL;
        ZydisGetInstructionDefinition(
            candidateInsn->encoding, candidateInsn->definitionReference, &candidateDef);
        const ZydisOperandDefinition* candidateOperands = NULL;
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

            // Is the type one of those we permit for the given operand?
            if (!(1 << curDefOperand->type & q->semOperandTypeMasks[k])) goto _nextInsn;

            // For some operand types, additional checks are required.
            switch (curDefOperand->type)
            {
            case ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG:
            {
                switch (curDefOperand->op.reg.type)
                {
                case ZYDIS_IMPLREG_TYPE_STATIC:
                {
                    // reg reg reg banana phooone!
                    if (curDefOperand->op.reg.reg.reg != curReqOperand->reg) goto _nextInsn;
                } break;
                case ZYDIS_IMPLREG_TYPE_GPR_OSZ:
                case ZYDIS_IMPLREG_TYPE_GPR_ASZ:
                case ZYDIS_IMPLREG_TYPE_GPR_SSZ:
                case ZYDIS_IMPLREG_TYPE_IP_ASZ:
                case ZYDIS_IMPLREG_TYPE_IP_SSZ:
                case ZYDIS_IMPLREG_TYPE_FLAGS_SSZ:
                {
                    int16_t id = ZydisRegisterGetId(curReqOperand->reg);
                    if (curDefOperand->op.reg.reg.id != id)
                    {
                        if (id < 0) return ZYDIS_STATUS_INVALID_PARAMETER; // TODO
                        goto _nextInsn;
                    }
                } break;
                default: ZYDIS_UNREACHABLE;
                }
            } break;
            case ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_MEM:
            {
                // TODO: Can those be scaled using 67?
                ZydisRegisterClass regClass;
                switch (req->machineMode)
                {
                case 16: regClass = ZYDIS_REGCLASS_GPR16; break;
                case 32: regClass = ZYDIS_REGCLASS_GPR32; break;
                case 64: regClass = ZYDIS_REGCLASS_GPR64; break;
                default: return ZYDIS_STATUS_INVALID_PARAMETER;
                }

                static const uint8_t regIdxLookup[4] = {3, 5, 6, 7};
                ZYDIS_ASSERT(curDefOperand->op.mem.base < ZYDIS_ARRAY_SIZE(regIdxLookup));
                uint8_t regIdx = regIdxLookup[curDefOperand->op.mem.base];
                ZydisRegister derivedReg = ZydisRegisterEncode(regClass, regIdx);

                if (curReqOperand->mem.base != derivedReg) goto _nextInsn;
            } break;
            case ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_IMM1: 
            {
                if (curReqOperand->imm.u != 1) goto _nextInsn;
            } break;
            case ZYDIS_SEMANTIC_OPTYPE_IMM:
            case ZYDIS_SEMANTIC_OPTYPE_REL:
            {
                // Even though the user probably had an idea if their immediate was signed
                // or unsigned, we try to encode it with whatever the signedness of the 
                // current definiton dictates. In X86 assembly, signedness only affects sign 
                // extension, so if a user wishes to encode e.g. 0xFFFFFFFF unsigned, we can 
                // also encode it as an 8-bit signed -1 that is then expanded back to 0xFFFFFFFF 
                // at runtime (assuming machineMode == 32), resulting in more compact and 
                // efficient encoding.
                uint8_t minSize = ZydisOperandEncodingImmIsSigned(curDefOperand->op.encoding)
                    ? ZydisSImmGetMinSize(curReqOperand->imm.s)
                    : ZydisUImmGetMinSize(curReqOperand->imm.u);
                uint8_t eisz;
                ZYDIS_CHECK(ZydisOperandEncodingGetEffectiveImmSize(
                    curDefOperand->op.encoding, req->machineMode, &eisz
                ));
                if (eisz < minSize) goto _nextInsn;
                match->derivedImmSizes[k] = eisz;
            } break;
            default: 
                ; // No further checks required.
            }
        }

        // Make sure we compared either all operands or the remaining operands are hidden.
        if (req->operandCount != defOperandCount && 
            (curDefOperand + 1)->visibility != ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            goto _nextInsn;
        }

        // Still here? Looks like we found our instruction, then!
        match->q = q;
        match->insn = candidateInsn;
        match->def = candidateDef;
        match->operands = candidateOperands;
        match->operandCount = req->operandCount;
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
    if (!in || !out || in->operandCount > ZYDIS_ARRAY_SIZE(in->operands))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    out->machineMode = in->machineMode;
    out->mnemonic = in->mnemonic;
    out->attributes = in->attributes & ZYDIS_USER_ENCODABLE_ATTRIB_MASK;
    out->encoding = in->encoding;
    out->operandCount = 0;
    out->avx.mask.reg = in->avx.mask.reg;
    out->avx.mask.mode = in->avx.mask.mode;
    out->avx.vectorLength = in->avx.vectorLength;

    for (uint8_t i = 0
        ; i < in->operandCount && out->operandCount < ZYDIS_ARRAY_SIZE(out->operands)
        ; ++i)
    {
        const ZydisDecodedOperand* inOp = in->operands + i;
        ZydisEncoderOperand* outOp = out->operands + out->operandCount;
        if (inOp->visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN) continue;

        outOp->type = inOp->type;
        switch (inOp->type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            outOp->reg = inOp->reg.value;
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            outOp->mem.segment = inOp->mem.segment;
            outOp->mem.base = inOp->mem.base;
            outOp->mem.index = inOp->mem.index;
            outOp->mem.scale = inOp->mem.scale;
            outOp->mem.disp = inOp->mem.disp.value;
            outOp->mem.dispSize = in->raw.disp.size;
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            outOp->ptr.segment = inOp->ptr.segment;
            outOp->ptr.offset = inOp->ptr.offset;
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            outOp->imm.u = inOp->imm.value.u;
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }

        ++out->operandCount;
    }
     
    return ZYDIS_STATUS_SUCCESS;
}

#endif

ZydisStatus ZydisEncoderEncodeInstruction(void* buffer, size_t* bufferLen,
    const ZydisEncoderRequest* request)
{
    if (!request || !bufferLen ) return ZYDIS_STATUS_INVALID_PARAMETER;
    if (!buffer  || !*bufferLen) return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    if (request->operandCount > ZYDIS_ARRAY_SIZE(request->operands)) 
    {
        return ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION;
    }

    ZydisEncoderContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.buffer = (uint8_t*)buffer;
    ctx.bufferLen = *bufferLen;
    ctx.writeOffs = 0;
    ctx.req = request;
    *bufferLen = 0;

    // Mask out attributes that can't be set explicitly by user.
    // TODO: We should probably rather error on unsupported attrs.
    ctx.raw.derivedAttrs = request->attributes & ZYDIS_USER_ENCODABLE_ATTRIB_MASK;

    // Evaluate request.
    ZydisInstructionQuery q;
    memset(&q, 0, sizeof(q));
    ZYDIS_CHECK(ZydisRequestToInstructionQuery(&ctx, request, &q));

    // Search matching instruction, collect information about what needs to be
    // encoded, what prefixes are required, etc.
    ZydisInstructionMatch match;
    memset(&match, 0, sizeof(match));
    ZYDIS_CHECK(ZydisFindMatchingDef(&ctx, request, &q, &match));
    ctx.raw.opcode = match.insn->opcode;

    // TODO: Check compatibility of requested prefixes to found instruction.

    // Prepare prefix bits.
    ctx.raw.bits.B  = match.insn->evexB;
    ctx.raw.bits.L  = match.insn->vectorLength & 0x01;
    ctx.raw.bits.L2 = match.insn->vectorLength & 0x02;
    ZydisPrepareMandatoryPrefixes(&ctx, &match);

    // Prepare opcode.
    ZYDIS_CHECK(ZydisPrepareOpcode(&ctx, &match));

    // Some instructions have additional opcode bits encoded in ModRM.[rm/reg].
    if (match.insn->forceModrmReg) ctx.raw.modrm.reg = match.insn->modrmReg;
    if (match.insn->forceModrmRm ) ctx.raw.modrm.rm  = match.insn->modrmRm;

    // Analyze and prepare operands.
    for (uint8_t i = 0; i < match.def->operandCount; ++i)
    {
        ZYDIS_CHECK(ZydisPrepareOperand(&ctx, &match, i));
    } 

    // Emit prepared raw instruction to bytestream.
    ZYDIS_CHECK(ZydisEmitLegacyPrefixes(&ctx, &q));
    if (ctx.raw.derivedAttrs & ZYDIS_ATTRIB_HAS_REX) ZYDIS_CHECK(ZydisEmitREX(&ctx));

    switch (match.insn->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_MVEX: ZYDIS_CHECK(ZydisEmitMVEX(&ctx)); break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX: ZYDIS_CHECK(ZydisEmitEVEX(&ctx)); break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:  ZYDIS_CHECK(ZydisEmitVEX (&ctx)); break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:  ZYDIS_CHECK(ZydisEmitXOP (&ctx)); break;
    default:; // Shut up linter.
    }

    if (ctx.raw.mandatoryPrefix) ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.raw.mandatoryPrefix));
    
    for (uint8_t i = 0; i < ctx.raw.opcodeMapPrefixLen; ++i)
    {
        ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.raw.opcodeMapPrefix[i]));
    }

    ZYDIS_CHECK(ZydisEmitByte(&ctx, ctx.raw.opcode));

    if (ctx.raw.derivedAttrs & ZYDIS_ATTRIB_HAS_MODRM) ZYDIS_CHECK(ZydisEmitModRM(&ctx));
    if (ctx.raw.derivedAttrs & ZYDIS_ATTRIB_HAS_SIB) ZYDIS_CHECK(ZydisEmitSIB(&ctx));
    if (ctx.raw.disp.size) ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.raw.disp.val, ctx.raw.disp.size));

    for (uint8_t i = 0
        ; i < ZYDIS_ARRAY_SIZE(ctx.raw.imms) && ctx.raw.imms[i].size
        ; ++i)
    {
        ZYDIS_CHECK(ZydisEmitImm(&ctx, ctx.raw.imms[i].val, ctx.raw.imms[i].size));
    }

    *bufferLen = ctx.writeOffs;
    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
