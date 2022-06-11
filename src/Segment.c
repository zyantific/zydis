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

#include <Zycore/LibC.h>
#include <Zydis/Segment.h>

/* ============================================================================================== */
/* Tables                                                                                         */
/* ============================================================================================== */

#define ZYDIS_DEF_OFFS(name, width, offs, struc)                        \
    {                                                                   \
        .field_name = #name,                                            \
        .bit_width = (width),                                           \
        .value_source.bit_offset = (offs),                              \
        .struct_offset = offsetof(ZydisInstructionSegment##struc, name) \
    }
#define ZYDIS_DEF_CNST(name, c, struc)                                  \
    {                                                                   \
        .field_name = #name,                                            \
        .bit_width = 0,                                                 \
        .value_source.constant = (c),                                   \
        .struct_offset = offsetof(ZydisInstructionSegment##struc, name) \
    }

static const ZydisInstructionSegmentFieldInfo REX_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(W, 1, 3, REX),
    ZYDIS_DEF_OFFS(R, 1, 2, REX),
    ZYDIS_DEF_OFFS(X, 1, 1, REX),
    ZYDIS_DEF_OFFS(B, 1, 0, REX),
    {}, // terminating empty record
};

static const ZydisInstructionSegmentFieldInfo VEX2_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(R,      1, 15, VEX),
    ZYDIS_DEF_CNST(X,      1,     VEX),
    ZYDIS_DEF_CNST(B,      1,     VEX),
    ZYDIS_DEF_CNST(m_mmmm, 1,     VEX),
    ZYDIS_DEF_CNST(W,      0,     VEX),
    ZYDIS_DEF_OFFS(vvvv,   4, 11, VEX),
    ZYDIS_DEF_OFFS(L,      1, 10, VEX),
    ZYDIS_DEF_OFFS(pp,     2, 8,  VEX),
    {},
};

static const ZydisInstructionSegmentFieldInfo VEX3_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(R,      15, 1, VEX),
    ZYDIS_DEF_OFFS(X,      14, 1, VEX),
    ZYDIS_DEF_OFFS(B,      13, 1, VEX),
    ZYDIS_DEF_OFFS(m_mmmm,  8, 5, VEX),
    ZYDIS_DEF_OFFS(W,      23, 1, VEX),
    ZYDIS_DEF_OFFS(vvvv,   19, 4, VEX),
    ZYDIS_DEF_OFFS(L,      18, 1, VEX),
    ZYDIS_DEF_OFFS(pp,     16, 2, VEX),
    {},
};

static const ZydisInstructionSegmentFieldInfo XOP_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(R,      15, 1, XOP),
    ZYDIS_DEF_OFFS(X,      14, 1, XOP),
    ZYDIS_DEF_OFFS(B,      13, 1, XOP),
    ZYDIS_DEF_OFFS(m_mmmm,  8, 5, XOP),
    ZYDIS_DEF_OFFS(W,      23, 1, XOP),
    ZYDIS_DEF_OFFS(vvvv,   19, 4, XOP),
    ZYDIS_DEF_OFFS(L,      18, 1, XOP),
    ZYDIS_DEF_OFFS(pp,     16, 2, XOP),
    {},
};

static const ZydisInstructionSegmentFieldInfo EVEX_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(R,    15, 1, EVEX),
    ZYDIS_DEF_OFFS(X,    14, 1, EVEX),
    ZYDIS_DEF_OFFS(B,    13, 1, EVEX),
    ZYDIS_DEF_OFFS(R2,   12, 1, EVEX),
    ZYDIS_DEF_OFFS(mmm,   8, 3, EVEX),
    ZYDIS_DEF_OFFS(W,    23, 1, EVEX),
    ZYDIS_DEF_OFFS(vvvv, 19, 4, EVEX),
    ZYDIS_DEF_OFFS(pp,   16, 2, EVEX),
    ZYDIS_DEF_OFFS(z,    31, 1, EVEX),
    ZYDIS_DEF_OFFS(L2,   30, 1, EVEX),
    ZYDIS_DEF_OFFS(L,    29, 1, EVEX),
    ZYDIS_DEF_OFFS(b,    28, 1, EVEX),
    ZYDIS_DEF_OFFS(V2,   27, 1, EVEX),
    ZYDIS_DEF_OFFS(aaa,  24, 3, EVEX),
    {},
};

static const ZydisInstructionSegmentFieldInfo MVEX_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(R,    15, 1, MVEX),
    ZYDIS_DEF_OFFS(X,    14, 1, MVEX),
    ZYDIS_DEF_OFFS(B,    13, 1, MVEX),
    ZYDIS_DEF_OFFS(R2,   12, 1, MVEX),
    ZYDIS_DEF_OFFS(mmmm,  8, 4, MVEX),
    ZYDIS_DEF_OFFS(W,    23, 1, MVEX),
    ZYDIS_DEF_OFFS(vvvv, 19, 4, MVEX),
    ZYDIS_DEF_OFFS(pp,   16, 2, MVEX),
    ZYDIS_DEF_OFFS(E,    31, 1, MVEX),
    ZYDIS_DEF_OFFS(SSS,  28, 3, MVEX),
    ZYDIS_DEF_OFFS(V2,   27, 1, MVEX),
    ZYDIS_DEF_OFFS(kkk,  24, 3, MVEX),
    {},
};

static const ZydisInstructionSegmentFieldInfo MODRM_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(mod, 6, 2, ModRM),
    ZYDIS_DEF_OFFS(reg, 3, 3, ModRM),
    ZYDIS_DEF_OFFS(rm,  0, 3, ModRM),
    {},
};

static const ZydisInstructionSegmentFieldInfo SIB_FIELD_LIST[] =
{
    ZYDIS_DEF_OFFS(scale, 6, 2, SIB),
    ZYDIS_DEF_OFFS(index, 3, 3, SIB),
    ZYDIS_DEF_OFFS(base,  0, 3, SIB),
    {},
};

static const ZydisInstructionSegmentFieldInfo NOBITS_FIELD_LIST[] =
{
    {},
};

#undef ZYDIS_DEF_OFFS
#undef ZYDIS_DEF_CONST

/* ============================================================================================== */
/* Helpers                                                                                        */
/* ============================================================================================== */

/**
 * Keeps context between `ZydisSegmentAdd` calls.
 */
typedef struct ZydisSegmentContext_ {
    /**
     * Pointer to the first byte of the instruction.
     */
    const ZyanU8* const raw_instr;
    /**
     * Length of `raw_instr`.
     */
    const ZyanU8 instr_length;
    /**
     * Output buffer to write segments to.
     */
    ZydisInstructionSegments *const segments;
    /**
     * Current byte offset within the instruction.
     */
    ZyanU8 offset;
} ZydisSegmentContext;

static ZyanStatus ZydisSegmentAdd(ZydisSegmentContext* const ctx,
    const ZydisInstructionSegmentKind kind, const char* name,
    const ZydisInstructionSegmentFieldInfo* field_list, const ZyanU8 size)
{
    ZYAN_ASSERT(ctx);
    ZYAN_ASSERT(kind <= ZYDIS_INSTR_SEGMENT_MAX_VALUE);
    ZYAN_ASSERT(size > 0 && size < ZYDIS_MAX_INSTRUCTION_LENGTH - 1);
    ZYAN_ASSERT(ctx->segments->count < ZYAN_ARRAY_LENGTH(ctx->segments->segments));

    if ((ZyanU32)(ctx->offset) + (ZyanU32)size > ctx->instr_length)
    {
        return ZYDIS_STATUS_NO_MORE_DATA;
    }

    ZydisInstructionSegment* seg = &ctx->segments->segments[ctx->segments->count++];

    *seg = (ZydisInstructionSegment) {
        .type = kind,
        .size = size,
        .offset = ctx->offset,
        .field_meta = field_list,
        .name = name,
    };

    for (; field_list->field_name; ++field_list)
    {
        ZyanU8* field = ((ZyanU8*)&seg->bits) + field_list->struct_offset;

        if (field_list->bit_width == 0)
        {
            // Constant.
            *field = field_list->value_source.constant;
        } else
        {
            // Read from raw segment data.
            ZyanU8 byte = field_list->value_source.bit_offset / 8;
            ZyanU8 bit  = field_list->value_source.bit_offset % 8;
            ZyanU8 mask = (1 << field_list->bit_width) - 1;
            ZYAN_ASSERT(byte < size);
            *field = (ctx->raw_instr[ctx->offset + byte] >> bit) & mask;
        }
    }

    ctx->offset += size;

    return ZYAN_STATUS_SUCCESS;
}

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZyanStatus ZydisGetInstructionSegments(const ZydisDecodedInstruction* const instruction,
    const ZyanU8* buffer, ZyanUSize length, ZydisInstructionSegments* const segments)
{
    if (!instruction || !segments || !buffer || (length < instruction->length))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    segments->count = 0;

    ZydisSegmentContext ctx = {
        .offset = 0,
        .segments = segments,
        .raw_instr = buffer,
        .instr_length = length,
    };

    // Legacy prefixes and `REX`.
    if (instruction->raw.prefix_count)
    {
        const ZyanU8 rex_offset = (instruction->attributes & ZYDIS_ATTRIB_HAS_REX) ? 1 : 0;
        if (!rex_offset || (instruction->raw.prefix_count > 1))
        {
            ZYAN_ASSERT(ctx.offset == 0);
            ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_PREFIXES, "prefixes",
                NOBITS_FIELD_LIST, instruction->raw.prefix_count - rex_offset));
        }
        if (rex_offset)
        {
            ZYAN_ASSERT(ctx.offset == instruction->raw.rex.offset);
            ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_REX, "rex", REX_FIELD_LIST, 1));
        }
    }

    // Encoding prefixes
    switch (instruction->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        ZYAN_ASSERT(ctx.offset == instruction->raw.xop.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_XOP, "xop", XOP_FIELD_LIST, 3));
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        ZYAN_ASSERT(ctx.offset == instruction->raw.vex.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_VEX, "vex",
            instruction->raw.vex.size == 2 ? VEX2_FIELD_LIST : VEX3_FIELD_LIST,
            instruction->raw.vex.size));
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        ZYAN_ASSERT(ctx.offset == instruction->raw.evex.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_EVEX, "evex", EVEX_FIELD_LIST, 4));
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        ZYAN_ASSERT(ctx.offset == instruction->raw.mvex.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_MVEX, "mvex", MVEX_FIELD_LIST, 4));
        break;
    default:
        break;
    }

    // Opcode
    ZyanU8 opcode_size = 1;
    if ((instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_LEGACY) ||
        (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW))
    {
        switch (instruction->opcode_map)
        {
        case ZYDIS_OPCODE_MAP_DEFAULT:
            break;
        case ZYDIS_OPCODE_MAP_0F:
            ZYAN_FALLTHROUGH;
        case ZYDIS_OPCODE_MAP_0F0F:
            opcode_size = 2;
            break;
        case ZYDIS_OPCODE_MAP_0F38:
            ZYAN_FALLTHROUGH;
        case ZYDIS_OPCODE_MAP_0F3A:
            opcode_size = 3;
            break;
        default:
            ZYAN_UNREACHABLE;
        }
    }

    ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_OPCODE, "opcode",
        NOBITS_FIELD_LIST, opcode_size));

    // ModRM
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_MODRM)
    {
        ZYAN_ASSERT(ctx.offset == instruction->raw.modrm.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_MODRM, "modrm", MODRM_FIELD_LIST, 1));
    }

    // SIB
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_SIB)
    {
        ZYAN_ASSERT(ctx.offset == instruction->raw.sib.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_SIB, "sib", SIB_FIELD_LIST, 1));
    }

    // Displacement
    if (instruction->raw.disp.size)
    {
        ZYAN_ASSERT(ctx.offset == instruction->raw.disp.offset);
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_DISPLACEMENT, "displacement",
            NOBITS_FIELD_LIST, instruction->raw.disp.size / 8));
    }

    // Immediates
    for (ZyanU8 i = 0; i < 2; ++i)
    {
        if (instruction->raw.imm[i].size)
        {
            ZYAN_ASSERT(ctx.offset == instruction->raw.imm[i].offset);
            ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_IMMEDIATE, "immediate",
                NOBITS_FIELD_LIST, instruction->raw.imm[i].size / 8));
        }
    }

    // 3DNow! suffix opcode
    if (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW)
    {
        ZYAN_CHECK(ZydisSegmentAdd(&ctx, ZYDIS_INSTR_SEGMENT_OPCODE, "opcode",
            NOBITS_FIELD_LIST, 1));
    }

    // Zero out remaining entries
    ZYAN_MEMSET(&segments->segments[segments->count], 0,
        sizeof(*segments->segments) - segments->count);

    return ZYAN_STATUS_SUCCESS;
}

/* ============================================================================================== */
