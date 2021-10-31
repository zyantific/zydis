/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Joel Hoener

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

// NOTE: This file must be valid C AND C++ as well for OSS-Fuzz!

/**
 * @file
 *
 * This file implements a tool that is supposed to be fed as input for fuzzers like AFL, reading a
 * control block from `stdin`, allowing the fuzzer to reach every possible code-path, testing any
 * possible combination of disassembler configurations.
 */

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <Zycore/LibC.h>
#include <Zydis/Zydis.h>

#ifdef ZYAN_WINDOWS
#   include <fcntl.h>
#   include <io.h>
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/**
 * Main fuzzer control block data structure.
 */
typedef struct ZydisFuzzControlBlock_
{
    ZydisMachineMode machine_mode;
    ZydisStackWidth stack_width;
    ZyanBool decoder_mode[ZYDIS_DECODER_MODE_MAX_VALUE + 1];
    ZydisFormatterStyle formatter_style;
    ZyanU64 u64; // u64 used for all kind of non-overlapping purposes
    ZyanUPointer formatter_properties[ZYDIS_FORMATTER_PROP_MAX_VALUE + 1];
    char string[16];
    ZyanU16 formatter_max_len;
} ZydisFuzzControlBlock;

/**
 * Structure for fuzzing decoder inputs.
 */
typedef struct ZydisFuzzControlBlockDecoderOnly_
{
    ZydisMachineMode machine_mode;
    ZydisStackWidth stack_width;
} ZydisFuzzControlBlockDecoderOnly;

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

// Limit maximum amount of bytes
#define ZYDIS_FUZZ_MAX_BYTES (1024 * 10 /* 10 KiB */)

#if defined(ZYDIS_FUZZ_AFL_FAST) || defined(ZYDIS_LIBFUZZER)
#   define ZYDIS_MAYBE_FPUTS(x, y)
#else
#   define ZYDIS_MAYBE_FPUTS(x, y) fputs(x, y)
#endif

#ifndef ZYDIS_FUZZ_TARGET
#   define ZYDIS_FUZZ_TARGET ZydisFuzzDecoder
#endif

#define ZYDIS_SANITIZE_MASK(var, type, mask)      var = (type)((ZyanUSize)(var) & (mask))
#define ZYDIS_SANITIZE_ENUM(var, type, max_value) var = (type)((ZyanUSize)(var) % (max_value + 1))

/* ============================================================================================== */
/* Stream reading abstraction                                                                     */
/* ============================================================================================== */

typedef ZyanUSize (*ZydisStreamRead)(void* ctx, ZyanU8* buf, ZyanUSize max_len);

ZyanUSize ZydisStdinRead(void *ctx, ZyanU8* buf, ZyanUSize max_len)
{
    ZYAN_UNUSED(ctx);
    return fread(buf, 1, max_len, ZYAN_STDIN);
}

#ifdef ZYDIS_LIBFUZZER
typedef struct
{
    ZyanU8 *buf;
    ZyanISize buf_len;
    ZyanISize read_offs;
} ZydisLibFuzzerContext;

ZyanUSize ZydisLibFuzzerRead(void* ctx, ZyanU8* buf, ZyanUSize max_len)
{
    ZydisLibFuzzerContext* c = (ZydisLibFuzzerContext*)ctx;
    ZyanUSize len = ZYAN_MIN(c->buf_len - c->read_offs, max_len);
    // printf("buf_len: %ld, read_offs: %ld, len: %ld, max_len: %ld, ptr: %p\n",
    //     c->buf_len, c->read_offs, len, max_len, c->buf + c->read_offs);
    if (!len)
    {
        return 0;
    }
    ZYAN_MEMCPY(buf, c->buf + c->read_offs, len);
    c->read_offs += len;
    return len;
}
#endif // ZYDIS_LIBFUZZER

/* ============================================================================================== */
/* Main iteration                                                                                 */
/* ============================================================================================== */

#if defined(ZYDIS_FUZZ_AFL_FAST) || defined(ZYDIS_LIBFUZZER)

#define ZydisPrintInstruction(...)

#else

void ZydisPrintInstruction(const ZydisDecodedInstruction *instruction, 
    const ZyanU8 *instruction_bytes)
{
    printf("(ssz: %u) ", instruction->stack_width);
    switch (instruction->machine_mode)
    {
    case ZYDIS_MACHINE_MODE_LONG_64:
        printf("-64 ");
        break;
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
    case ZYDIS_MACHINE_MODE_LEGACY_32:
        printf("-32 ");
        break;
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
    case ZYDIS_MACHINE_MODE_LEGACY_16:
    case ZYDIS_MACHINE_MODE_REAL_16:
        printf("-16 ");
        break;
    default:
        ZYAN_UNREACHABLE;
    }

    for (ZyanU8 i = 0; i < instruction->length; ++i)
    {
        printf("%02X", instruction_bytes[i]);
    }

    ZydisFormatter formatter;
    if (!ZYAN_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL)) ||
        !ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter, ZYDIS_FORMATTER_PROP_FORCE_SEGMENT,
            ZYAN_TRUE)) ||
        !ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter, ZYDIS_FORMATTER_PROP_FORCE_SIZE,
            ZYAN_TRUE)))
    {
        fputs("Failed to initialize instruction formatter\n", ZYAN_STDERR);
        abort();
    }

    char buffer[256];
    ZydisFormatterFormatInstruction(&formatter, instruction, buffer, sizeof(buffer), 0);
    printf(" %s\n", buffer);
}

#endif

// NOTE: This function doesn't validate flag values, yet.
static void ZydisValidateEnumRanges(const ZydisDecodedInstruction *insn)
{
#   define ZYDIS_CHECK_ENUM(value, max)                                                            \
    if ((ZyanU64)(value) > (ZyanU64)(max))                                                         \
    {                                                                                              \
        fprintf(stderr, "Value " #value " = 0x%016" PRIX64 " is above expected max " #max          \
            " = 0x%016" PRIX64 "\n", (ZyanU64)(value), (ZyanU64)(max));                            \
        abort();                                                                                   \
    }

    ZYDIS_CHECK_ENUM(insn->length, ZYDIS_MAX_INSTRUCTION_LENGTH);

    ZYDIS_CHECK_ENUM(insn->machine_mode, ZYDIS_MACHINE_MODE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->mnemonic, ZYDIS_MNEMONIC_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->encoding, ZYDIS_INSTRUCTION_ENCODING_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->opcode_map, ZYDIS_OPCODE_MAP_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->opcode_map, ZYDIS_OPCODE_MAP_MAX_VALUE);
    for (ZyanU32 i = 0; i < ZYAN_ARRAY_LENGTH(insn->accessed_flags); ++i)
    {
        ZYDIS_CHECK_ENUM(insn->accessed_flags[i].action, ZYDIS_CPUFLAG_MAX_VALUE);
    }

    // Operands.
    for (ZyanU32 i = 0; i < ZYAN_ARRAY_LENGTH(insn->operands); ++i)
    {
        const ZydisDecodedOperand* op = &insn->operands[i];
        ZYDIS_CHECK_ENUM(op->type, ZYDIS_OPERAND_TYPE_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->visibility, ZYDIS_OPERAND_VISIBILITY_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->encoding, ZYDIS_OPERAND_ENCODING_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->element_type, ZYDIS_ELEMENT_TYPE_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->reg.value, ZYDIS_REGISTER_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->mem.type, ZYDIS_MEMOP_TYPE_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->mem.segment, ZYDIS_REGISTER_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->mem.base, ZYDIS_REGISTER_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->mem.index, ZYDIS_REGISTER_MAX_VALUE);
        ZYDIS_CHECK_ENUM(op->mem.disp.has_displacement, ZYAN_TRUE);
        ZYDIS_CHECK_ENUM(op->imm.is_signed, ZYAN_TRUE);
        ZYDIS_CHECK_ENUM(op->imm.is_relative, ZYAN_TRUE);
    }

    // AVX.
    ZYDIS_CHECK_ENUM(insn->avx.mask.mode, ZYDIS_MASK_MODE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->avx.mask.reg, ZYDIS_REGISTER_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->avx.broadcast.is_static, ZYAN_TRUE);
    ZYDIS_CHECK_ENUM(insn->avx.broadcast.mode, ZYDIS_BROADCAST_MODE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->avx.rounding.mode, ZYDIS_ROUNDING_MODE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->avx.swizzle.mode, ZYDIS_SWIZZLE_MODE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->avx.conversion.mode, ZYDIS_CONVERSION_MODE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->avx.has_sae, ZYAN_TRUE);
    ZYDIS_CHECK_ENUM(insn->avx.has_eviction_hint, ZYAN_TRUE);

    // Meta.
    ZYDIS_CHECK_ENUM(insn->meta.category, ZYDIS_CATEGORY_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->meta.isa_set, ZYDIS_ISA_SET_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->meta.isa_ext, ZYDIS_ISA_SET_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->meta.branch_type, ZYDIS_BRANCH_TYPE_MAX_VALUE);
    ZYDIS_CHECK_ENUM(insn->meta.exception_class, ZYDIS_EXCEPTION_CLASS_MAX_VALUE);

    // Raw.
    for (ZyanU32 i = 0; i < ZYAN_ARRAY_LENGTH(insn->raw.prefixes); ++i)
    {
        ZYDIS_CHECK_ENUM(insn->raw.prefixes[i].type, ZYDIS_PREFIX_TYPE_MAX_VALUE);
    }
    for (ZyanU32 i = 0; i < ZYAN_ARRAY_LENGTH(insn->raw.imm); ++i)
    {
        ZYDIS_CHECK_ENUM(insn->raw.imm[i].is_signed, ZYAN_TRUE);
        ZYDIS_CHECK_ENUM(insn->raw.imm[i].is_relative, ZYAN_TRUE);
    }

#   undef ZYDIS_CHECK_ENUM
}

static void ZydisValidateInstructionIdentity(const ZydisDecodedInstruction *insn1, 
    const ZydisDecodedInstruction *insn2)
{
    // Special case, `xchg rAX, rAX` is an alias for `NOP`
    if ((insn1->mnemonic == ZYDIS_MNEMONIC_XCHG) &&
        (insn1->operand_count == 2) &&
        (insn1->operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
        (insn1->operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
        (insn1->operands[0].reg.value == insn1->operands[1].reg.value) &&
        (insn2->mnemonic == ZYDIS_MNEMONIC_NOP))
    {
        switch (insn1->operands[0].reg.value)
        {
        case ZYDIS_REGISTER_AX:
        case ZYDIS_REGISTER_EAX:
        case ZYDIS_REGISTER_RAX:
            return;
        default:
            break;
        }
    }

    ZydisSwizzleMode swizzle1 = insn1->avx.swizzle.mode == ZYDIS_SWIZZLE_MODE_DCBA ? 
        ZYDIS_SWIZZLE_MODE_INVALID : insn1->avx.swizzle.mode;
    ZydisSwizzleMode swizzle2 = insn2->avx.swizzle.mode == ZYDIS_SWIZZLE_MODE_DCBA ? 
        ZYDIS_SWIZZLE_MODE_INVALID : insn2->avx.swizzle.mode;
    if ((insn1->machine_mode != insn2->machine_mode) ||
        (insn1->mnemonic != insn2->mnemonic) ||
        (insn1->stack_width != insn2->stack_width) ||
        (insn1->operand_count != insn2->operand_count) ||
        (insn1->avx.mask.mode != insn2->avx.mask.mode) ||
        (insn1->avx.broadcast.is_static != insn2->avx.broadcast.is_static) ||
        (insn1->avx.broadcast.mode != insn2->avx.broadcast.mode) ||
        (insn1->avx.conversion.mode != insn2->avx.conversion.mode) ||
        (insn1->avx.rounding.mode != insn2->avx.rounding.mode) ||
        (insn1->avx.has_sae != insn2->avx.has_sae) ||
        (insn1->avx.has_eviction_hint != insn2->avx.has_eviction_hint) ||
        (swizzle1 != swizzle2))
    {
        fputs("Basic instruction attributes mismatch\n", ZYAN_STDERR);
        abort();
    }

    for (ZyanU8 i = 0; i < insn1->operand_count; ++i)
    {
        const ZydisDecodedOperand *op1 = &insn1->operands[i];
        const ZydisDecodedOperand *op2 = &insn2->operands[i];
        if ((op1->type != op2->type) ||
            (op1->size != op2->size && op1->type != ZYDIS_OPERAND_TYPE_IMMEDIATE))
        {
            fprintf(ZYAN_STDERR, "Mismatch for operand %u\n", i);
            abort();
        }
        switch (op1->type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            if (op1->reg.value != op2->reg.value)
            {
                fprintf(ZYAN_STDERR, "Mismatch for register operand %u\n", i);
                abort();
            }
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            if ((op1->mem.type != op2->mem.type) ||
                (op1->mem.segment != op2->mem.segment) ||
                (op1->mem.base != op2->mem.base) ||
                (op1->mem.index != op2->mem.index) ||
                (op1->mem.scale != op2->mem.scale && op1->mem.type != ZYDIS_MEMOP_TYPE_MIB) ||
                (op1->mem.disp.value != op2->mem.disp.value))
            {
                ZyanBool acceptable_mismatch = ZYAN_FALSE;
                if ((op1->mem.disp.has_displacement) && 
                    (op2->mem.disp.has_displacement) &&
                    (op1->mem.index == ZYDIS_REGISTER_NONE) &&
                    ((op1->mem.base == ZYDIS_REGISTER_NONE) ||
                     (op1->mem.base == ZYDIS_REGISTER_EIP) ||
                     (op1->mem.base == ZYDIS_REGISTER_RIP)))
                {
                    ZyanU64 addr1, addr2;
                    ZydisCalcAbsoluteAddress(insn1, op1, 0, &addr1);
                    ZydisCalcAbsoluteAddress(insn2, op2, 0, &addr2);
                    acceptable_mismatch = (addr1 == addr2);
                }
                if (!acceptable_mismatch)
                {
                    fprintf(ZYAN_STDERR, "Mismatch for memory operand %u\n", i);
                    abort();
                }
            }
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            if ((op1->ptr.segment != op2->ptr.segment) ||
                (op1->ptr.offset != op2->ptr.offset))
            {
                fprintf(ZYAN_STDERR, "Mismatch for pointer operand %u\n", i);
                abort();
            }
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            if ((op1->imm.is_relative != op2->imm.is_relative) ||
                (op1->imm.is_signed != op2->imm.is_signed) ||
                (op1->imm.value.u != op2->imm.value.u))
            {
                ZyanBool acceptable_mismatch = ZYAN_FALSE;
                if ((insn1->meta.category == ZYDIS_CATEGORY_DATAXFER) ||
                    (insn1->meta.category == ZYDIS_CATEGORY_LOGICAL))
                {
                    ZyanU8 size = ZYAN_MAX(op1->size, op2->size);
                    if (size < 64)
                    {
                        ZyanU64 mask = (1ULL << size) - 1;
                        acceptable_mismatch = 
                            (op1->imm.value.u & mask) == (op2->imm.value.u & mask);
                    }
                    else
                    {
                        acceptable_mismatch = op1->imm.value.u == op2->imm.value.u;
                    }
                }
                if (!acceptable_mismatch)
                {
                    fprintf(ZYAN_STDERR, "Mismatch for immediate operand %u\n", i);
                    abort();
                }
            }
            break;
        default:
            fprintf(ZYAN_STDERR, "Invalid operand type for operand %u\n", i);
            abort();
        }
    }
}

// We disable enum sanitization here because we actually want Zydis to be tested with
// possibly invalid enum values in mind, thus need to be able to create them here.
ZYAN_NO_SANITIZE("enum")
int ZydisFuzzDecoder(ZydisStreamRead read_fn, void* stream_ctx)
{
    ZydisFuzzControlBlock control_block;
    if (read_fn(
        stream_ctx, (ZyanU8*)&control_block, sizeof(control_block)) != sizeof(control_block))
    {
        ZYDIS_MAYBE_FPUTS("Not enough bytes to fuzz\n", ZYAN_STDERR);
        return EXIT_SUCCESS;
    }
    control_block.string[ZYAN_ARRAY_LENGTH(control_block.string) - 1] = 0;

    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS(ZydisDecoderInit(&decoder, control_block.machine_mode,
        control_block.stack_width)))
    {
        ZYDIS_MAYBE_FPUTS("Failed to initialize decoder\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }
    for (int mode = 0; mode <= ZYDIS_DECODER_MODE_MAX_VALUE; ++mode)
    {
        if (!ZYAN_SUCCESS(ZydisDecoderEnableMode(&decoder, (ZydisDecoderMode)mode,
            control_block.decoder_mode[mode] ? 1 : 0)))
        {
            ZYDIS_MAYBE_FPUTS("Failed to adjust decoder-mode\n", ZYAN_STDERR);
            return EXIT_FAILURE;
        }
    }

    ZydisFormatter formatter;
    if (!ZYAN_SUCCESS(ZydisFormatterInit(&formatter, control_block.formatter_style)))
    {
        ZYDIS_MAYBE_FPUTS("Failed to initialize formatter\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }
    for (int prop = 0; prop <= ZYDIS_FORMATTER_PROP_MAX_VALUE; ++prop)
    {
        switch (prop)
        {
        case ZYDIS_FORMATTER_PROP_DEC_PREFIX:
        case ZYDIS_FORMATTER_PROP_DEC_SUFFIX:
        case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
        case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
            control_block.formatter_properties[prop] =
                control_block.formatter_properties[prop] ? (ZyanUPointer)&control_block.string : 0;
            break;
        default:
            break;
        }
        if (!ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter, (ZydisFormatterProperty)prop,
            control_block.formatter_properties[prop])))
        {
            ZYDIS_MAYBE_FPUTS("Failed to set formatter-attribute\n", ZYAN_STDERR);
            return EXIT_FAILURE;
        }
    }

    ZyanU8 buffer[32];
    ZyanUSize input_len = read_fn(stream_ctx, buffer, sizeof(buffer));
    ZydisDecodedInstruction instruction;

    // Fuzz decoder.
    ZyanStatus status = ZydisDecoderDecodeBuffer(&decoder, buffer, input_len, &instruction);
    if (!ZYAN_SUCCESS(status))
    {
        return EXIT_FAILURE;
    }

    ZydisValidateEnumRanges(&instruction);

    // Fuzz formatter.
    char format_buffer[256];
    // Allow the control block to artificially restrict the buffer size.
    ZyanUSize output_len = ZYAN_MIN(sizeof(format_buffer), control_block.formatter_max_len);
    ZydisFormatterFormatInstruction(&formatter, &instruction, format_buffer, output_len,
        control_block.u64);

    // Fuzz tokenizer.
    const ZydisFormatterToken* token;
    status = ZydisFormatterTokenizeInstruction(&formatter, &instruction, format_buffer, output_len,
        control_block.u64, &token);

    // Walk tokens.
    while (ZYAN_SUCCESS(status))
    {
        ZydisTokenType type;
        ZyanConstCharPointer value;
        if (!ZYAN_SUCCESS(status = ZydisFormatterTokenGetValue(token, &type, &value)))
        {
            ZYDIS_MAYBE_FPUTS("Failed to get token value\n", ZYAN_STDERR);
            break;
        }

        status = ZydisFormatterTokenNext(&token);
    }

    if (instruction.operand_count > 0)
    {
        // Fuzz single operand formatting. We reuse rt-address for operand selection.
        // It's casted to u8 because modulo is way cheaper on that.
        ZyanU8 op_idx = (ZyanU8)control_block.u64 % instruction.operand_count;
        ZydisFormatterFormatOperand(&formatter, &instruction, op_idx, format_buffer, output_len,
            control_block.u64);

        // Fuzz single operand tokenization.
        ZydisFormatterTokenizeOperand(&formatter, &instruction, op_idx, format_buffer, output_len,
            control_block.u64, &token);

        // Address translation helper.
        ZyanU64 abs_addr;
        ZydisCalcAbsoluteAddress(&instruction, &instruction.operands[op_idx],
            control_block.u64, &abs_addr);
    }

    // Mnemonic helpers.
    ZydisMnemonicGetString((ZydisMnemonic)control_block.u64);
    ZydisMnemonicGetStringWrapped((ZydisMnemonic)control_block.u64);

    // Flag helpers.
    ZydisCPUFlagAction flag_action = (ZydisCPUFlagAction)control_block.u64;
    ZydisCPUFlags flags;
    ZydisGetAccessedFlagsByAction(&instruction, flag_action, &flags);

    // Instruction segment helper.
    ZydisInstructionSegments segments;
    ZydisGetInstructionSegments(&instruction, &segments);

    // Feature enable check helper.
    ZydisIsFeatureEnabled((ZydisFeature)control_block.u64);

    // Register helpers.
    ZydisRegisterEncode((ZydisRegisterClass)(control_block.u64 >> 8), (ZyanU8)control_block.u64);
    ZydisRegisterGetId((ZydisRegister)control_block.u64);
    ZydisRegisterGetClass((ZydisRegister)control_block.u64);
    ZydisRegisterGetWidth(control_block.machine_mode, (ZydisRegister)control_block.u64);
    ZydisRegisterGetLargestEnclosing(control_block.machine_mode, (ZydisRegister)control_block.u64);
    ZydisRegisterGetString((ZydisRegister)control_block.u64);
    ZydisRegisterGetStringWrapped((ZydisRegister)control_block.u64);
    ZydisRegisterClassGetWidth(control_block.machine_mode, (ZydisRegisterClass)control_block.u64);

    return EXIT_SUCCESS;
}

void ZydisReEncodeInstruction(const ZydisDecoder *decoder, const ZydisDecodedInstruction *insn1, 
    const ZyanU8 *insn1_bytes)
{
    ZydisPrintInstruction(insn1, insn1_bytes);
    ZydisValidateEnumRanges(insn1);

    ZydisEncoderRequest request;
    ZyanStatus status = ZydisEncoderDecodedInstructionToEncoderRequest(insn1, &request);
    if (!ZYAN_SUCCESS(status))
    {
        fputs("ZydisEncoderDecodedInstructionToEncoderRequest failed\n", ZYAN_STDERR);
        abort();
    }

    ZyanU8 encoded_instruction[ZYDIS_MAX_INSTRUCTION_LENGTH];
    ZyanUSize encoded_length = sizeof(encoded_instruction);
    status = ZydisEncoderEncodeInstruction(&request, encoded_instruction, &encoded_length);
    if (!ZYAN_SUCCESS(status))
    {
        fputs("Failed to re-encode instruction\n", ZYAN_STDERR);
        abort();
    }

    ZydisDecodedInstruction insn2;
    status = ZydisDecoderDecodeBuffer(decoder, encoded_instruction, encoded_length, &insn2);
    if (!ZYAN_SUCCESS(status))
    {
        fputs("Failed to decode re-encoded instruction\n", ZYAN_STDERR);
        abort();
    }

    ZydisPrintInstruction(&insn2, encoded_instruction);
    ZydisValidateEnumRanges(&insn2);
    ZydisValidateInstructionIdentity(insn1, &insn2);
}

ZYAN_NO_SANITIZE("enum")
int ZydisFuzzDecoderEncoderDecoder(ZydisStreamRead read_fn, void *stream_ctx)
{
    ZydisFuzzControlBlockDecoderOnly control_block;
    if (read_fn(
        stream_ctx, (ZyanU8 *)&control_block, sizeof(control_block)) != sizeof(control_block))
    {
        ZYDIS_MAYBE_FPUTS("Not enough bytes to fuzz\n", ZYAN_STDERR);
        return EXIT_SUCCESS;
    }

    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS(ZydisDecoderInit(&decoder, control_block.machine_mode,
        control_block.stack_width)))
    {
        ZYDIS_MAYBE_FPUTS("Failed to initialize decoder\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }

    ZyanU8 buffer[32];
    ZyanUSize input_len = read_fn(stream_ctx, buffer, sizeof(buffer));
    ZydisDecodedInstruction insn1;
    ZyanStatus status = ZydisDecoderDecodeBuffer(&decoder, buffer, input_len, &insn1);
    if (!ZYAN_SUCCESS(status))
    {
        return EXIT_FAILURE;
    }

    ZydisReEncodeInstruction(&decoder, &insn1, buffer);

    return EXIT_SUCCESS;
}

ZYAN_NO_SANITIZE("enum")
int ZydisFuzzEncoderDecoderEncoderDecoder(ZydisStreamRead read_fn, void *stream_ctx)
{
    ZydisEncoderRequest request;
    if (read_fn(stream_ctx, (ZyanU8 *)&request, sizeof(request)) != sizeof(request))
    {
        ZYDIS_MAYBE_FPUTS("Not enough bytes to fuzz\n", ZYAN_STDERR);
        return EXIT_SUCCESS;
    }

    // Sanitization greatly improves coverage, without it most inputs will fail at basic checks
    // inside `ZydisEncoderCheckRequestSanity`
    request.operand_count %= ZYDIS_ENCODER_MAX_OPERANDS + 1;
    ZYDIS_SANITIZE_MASK(request.allowed_encodings, ZydisEncodableEncoding,
        ZYDIS_ENCODABLE_ENCODING_MAX_VALUE);
    ZYDIS_SANITIZE_MASK(request.prefixes, ZydisEncodablePrefix, ZYDIS_ENCODABLE_PREFIX_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.machine_mode, ZydisMachineMode, ZYDIS_MACHINE_MODE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.mnemonic, ZydisMnemonic, ZYDIS_MNEMONIC_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.branch_type, ZydisEncodableBranchType,
        ZYDIS_ENCODABLE_BRANCH_TYPE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.address_size_hint, ZydisAddressSizeHint,
        ZYDIS_ADDRESS_SIZE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.operand_size_hint, ZydisOperandSizeHint,
        ZYDIS_OPERAND_SIZE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.evex.broadcast, ZydisBroadcastMode, ZYDIS_BROADCAST_MODE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.evex.rounding, ZydisRoundingMode, ZYDIS_ROUNDING_MODE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.mvex.broadcast, ZydisBroadcastMode, ZYDIS_BROADCAST_MODE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.mvex.conversion, ZydisConversionMode,
        ZYDIS_CONVERSION_MODE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.mvex.rounding, ZydisRoundingMode, ZYDIS_ROUNDING_MODE_MAX_VALUE);
    ZYDIS_SANITIZE_ENUM(request.mvex.swizzle, ZydisSwizzleMode, ZYDIS_SWIZZLE_MODE_MAX_VALUE);
    for (ZyanU8 i = 0; i < request.operand_count; ++i)
    {
        ZydisEncoderOperand *op = &request.operands[i];
        op->type = (ZydisOperandType)(ZYDIS_OPERAND_TYPE_REGISTER +
            ((ZyanUSize)op->type % ZYDIS_OPERAND_TYPE_MAX_VALUE));
        switch (op->type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            ZYDIS_SANITIZE_ENUM(op->reg.value, ZydisRegister, ZYDIS_REGISTER_MAX_VALUE);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            ZYDIS_SANITIZE_ENUM(op->mem.base, ZydisRegister, ZYDIS_REGISTER_MAX_VALUE);
            ZYDIS_SANITIZE_ENUM(op->mem.index, ZydisRegister, ZYDIS_REGISTER_MAX_VALUE);
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            break;
        default:
            ZYAN_UNREACHABLE;
        }
    }

    ZyanU8 encoded_instruction[ZYDIS_MAX_INSTRUCTION_LENGTH];
    ZyanUSize encoded_length = sizeof(encoded_instruction);
    ZyanStatus status = ZydisEncoderEncodeInstruction(&request, encoded_instruction,
        &encoded_length);
    if (!ZYAN_SUCCESS(status))
    {
        return EXIT_SUCCESS;
    }

    ZydisStackWidth stack_width;
    switch (request.machine_mode)
    {
    case ZYDIS_MACHINE_MODE_LONG_64:
        stack_width = ZYDIS_STACK_WIDTH_64;
        break;
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
    case ZYDIS_MACHINE_MODE_LEGACY_32:
        stack_width = ZYDIS_STACK_WIDTH_32;
        break;
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
    case ZYDIS_MACHINE_MODE_LEGACY_16:
    case ZYDIS_MACHINE_MODE_REAL_16:
        stack_width = ZYDIS_STACK_WIDTH_16;
        break;
    default:
        ZYAN_UNREACHABLE;
    }

    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS(ZydisDecoderInit(&decoder, request.machine_mode, stack_width)))
    {
        fputs("Failed to initialize decoder\n", ZYAN_STDERR);
        abort();
    }

    ZydisDecodedInstruction insn1;
    status = ZydisDecoderDecodeBuffer(&decoder, encoded_instruction, encoded_length, &insn1);
    if (!ZYAN_SUCCESS(status))
    {
        fputs("Failed to decode instruction\n", ZYAN_STDERR);
        abort();
    }

    ZydisReEncodeInstruction(&decoder, &insn1, encoded_instruction);

    return EXIT_SUCCESS;
}

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int ZydisFuzzerInit()
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        fputs("Invalid Zydis version\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }

#ifdef ZYAN_WINDOWS
    // The `stdin` pipe uses text-mode on Windows platforms by default. We need it to be opened in
    // binary mode
    (void)_setmode(_fileno(ZYAN_STDIN), _O_BINARY);
#endif

    return EXIT_SUCCESS;
}

#ifdef ZYDIS_LIBFUZZER

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerInitialize(int *argc, char ***argv)
{
    ZYAN_UNUSED(argc);
    ZYAN_UNUSED(argv);

    return ZydisFuzzerInit();
}

int LLVMFuzzerTestOneInput(ZyanU8 *buf, ZyanUSize len)
{
    ZydisLibFuzzerContext ctx;
    ctx.buf = buf;
    ctx.buf_len = len;
    ctx.read_offs = 0;

    ZYDIS_FUZZ_TARGET(&ZydisLibFuzzerRead, &ctx);
    return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif

#else // !ZYDIS_LIBFUZZER

int main(void)
{
    if (ZydisFuzzerInit() != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

#ifdef ZYDIS_FUZZ_AFL_FAST
    while (__AFL_LOOP(1000))
    {
        ZYDIS_FUZZ_TARGET(&ZydisStdinRead, ZYAN_NULL);
    }
    return EXIT_SUCCESS;
#else
    return ZYDIS_FUZZ_TARGET(&ZydisStdinRead, ZYAN_NULL);
#endif
}

#endif // ZYDIS_LIBFUZZER

/* ============================================================================================== */
