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
    ZydisAddressWidth address_width;
    ZyanBool decoder_mode[ZYDIS_DECODER_MODE_MAX_VALUE + 1];
    ZydisFormatterStyle formatter_style;
    ZyanU64 u64; // u64 used for all kind of non-overlapping purposes
    ZyanUPointer formatter_properties[ZYDIS_FORMATTER_PROP_MAX_VALUE + 1];
    char string[16];
    ZyanU16 formatter_max_len;
} ZydisFuzzControlBlock;

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

// We disable enum sanitization here because we actually want Zydis to be tested with
// possibly invalid enum values in mind, thus need to be able to create them here.
ZYAN_NO_SANITIZE("enum")
static int ZydisFuzzIteration(ZydisStreamRead read_fn, void* stream_ctx)
{
    ZydisFuzzControlBlock control_block;

#ifdef ZYAN_WINDOWS
    // The `stdin` pipe uses text-mode on Windows platforms by default. We need it to be opened in
    // binary mode
    (void)_setmode(_fileno(ZYAN_STDIN), _O_BINARY);
#endif

    if (read_fn(
        stream_ctx, (ZyanU8*)&control_block, sizeof(control_block)) != sizeof(control_block))
    {
        ZYDIS_MAYBE_FPUTS("Not enough bytes to fuzz\n", ZYAN_STDERR);
        return EXIT_SUCCESS;
    }
    control_block.string[ZYAN_ARRAY_LENGTH(control_block.string) - 1] = 0;

    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS(ZydisDecoderInit(&decoder, control_block.machine_mode,
        control_block.address_width)))
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

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

#ifdef ZYDIS_LIBFUZZER

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerInitialize(int *argc, char ***argv)
{
    ZYAN_UNUSED(argc);
    ZYAN_UNUSED(argv);

    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        fputs("Invalid zydis version\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int LLVMFuzzerTestOneInput(ZyanU8 *buf, ZyanUSize len)
{
    ZydisLibFuzzerContext ctx;
    ctx.buf = buf;
    ctx.buf_len = len;
    ctx.read_offs = 0;

    ZydisFuzzIteration(&ZydisLibFuzzerRead, &ctx);
    return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif

#else // !ZYDIS_LIBFUZZER

int main(void)
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        fputs("Invalid zydis version\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }

#ifdef ZYDIS_FUZZ_AFL_FAST
    while (__AFL_LOOP(1000))
    {
        ZydisFuzzIteration(&ZydisStdinRead, ZYAN_NULL);
    }
    return EXIT_SUCCESS;
#else
    return ZydisFuzzIteration(&ZydisStdinRead, ZYAN_NULL);
#endif
}

#endif // ZYDIS_LIBFUZZER

/* ============================================================================================== */
