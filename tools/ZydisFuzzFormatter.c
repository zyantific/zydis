/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Cline (OSS-Fuzz coverage-pipeline agent)

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

/**
 * @file
 *
 * Fuzz target for the instruction formatter. Every successfully decoded instruction is
 * formatted and tokenized under a deterministic sweep of formatter styles, formatter
 * properties, output-buffer sizes and custom formatter hooks.
 *
 * Rationale: the formatter is the code path that turns attacker-controlled instruction
 * bytes into human-readable text (disassembler UIs, JIT loggers, EDR telemetry), so its
 * input is untrusted by construction. The union coverage of 2026-11-13 shows the whole
 * formatter family (`src/Formatter*.c`, `src/FormatterBuffer.c`,
 * `include/Zydis/Internal/String.h`, ~416 dark lines) reachable only via `ZydisFuzzDecoder`,
 * which probes the style/property grid only stochastically, and shows the
 * `ZydisFormatterSetHook` plus formatter-buffer API surface completely unreached.
 * This target sweeps the style x property x buffer-size grid deterministically for each
 * decoded instruction and installs custom hooks following the official examples
 * (`examples/Formatter01.c`, `examples/Formatter02.c`), so hook dispatch, the buffer API and
 * the deep format/token paths run under fuzz control with attacker-influenced instructions.
 */


#include "ZydisFuzzShared.h"

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/**
 * Main fuzzer control block data structure. Instruction bytes follow this block in the input.
 */
typedef struct ZydisFuzzControlBlock_
{
    ZydisMachineMode machine_mode;
    ZydisStackWidth stack_width;
    ZyanBool decoder_mode[ZYDIS_DECODER_MODE_MAX_VALUE + 1];
    ZyanU8 style_lo;           /**< First formatter style of the sweep. */
    ZyanU8 style_count;        /**< Number of styles to sweep (modulo 3 + 1, forced >= 1). */
    ZyanU8 prop_lo;            /**< First formatter property of the sweep. */
    ZyanU8 prop_count;         /**< Number of properties to sweep. */
    ZyanU8 hook_mask;          /**< Bit 0: install a custom formatter hook. */
    ZyanU8 hook_func;          /**< Formatter function to replace (mod FUNC_MAX_VALUE + 1). */
    ZyanU16 formatter_max_len; /**< Artificially restricted output-buffer size. */
    ZyanU64 prop_value;        /**< Base value applied to the swept properties. */
    ZyanU64 runtime_address;   /**< Runtime address used for formatting. */
} ZydisFuzzControlBlock;

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/**
 * A static string appended by the fuzz hooks and usable as prefix/suffix for the
 * string-valued formatter properties.
 */
static const char fuzz_property_string[] = "fz:";

/**
 * The formatter function that was replaced by the fuzz hook, or `ZYAN_NULL`.
 */
static ZydisFormatterFunc fuzz_hook_default;

/**
 * Generic hook replacement: exercises the formatter-buffer API on hook entry and chains to
 * the replaced default implementation, if one is installed. Note: `ZyanStringAppend` and
 * friends are deliberately not used here because the OSS-Fuzz link line only provides
 * `libZydis.a`, which does not bundle the zycore string API.
 */
static ZyanStatus FuzzHook(const ZydisFormatter* formatter, ZydisFormatterBuffer* buffer,
    ZydisFormatterContext* context)
{
    ZyanString* string;
    if (ZYAN_SUCCESS(ZydisFormatterBufferGetString(buffer, &string)))
    {
        ZydisFormatterBufferAppend(buffer, ZYDIS_TOKEN_SYMBOL);
    }
    if (fuzz_hook_default)
    {
        return fuzz_hook_default(formatter, buffer, context);
    }
    return ZYAN_STATUS_SUCCESS;
}

/**
 * Full replacement for `ZYDIS_FORMATTER_FUNC_FORMAT_INSTRUCTION`: exercises the
 * remember/restore dance and emits a mnemonic token without chaining (replacing this
 * function disables all other hooks by design).
 */
static ZyanStatus FuzzHookFormatInstruction(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(context);
    ZyanUPointer state;
    ZYAN_CHECK(ZydisFormatterBufferRemember(buffer, &state));
    ZYAN_CHECK(ZydisFormatterBufferAppend(buffer, ZYDIS_TOKEN_MNEMONIC));
    ZyanString* string;
    ZYAN_CHECK(ZydisFormatterBufferGetString(buffer, &string));
    const ZydisFormatterToken* token;
    ZYAN_CHECK(ZydisFormatterBufferGetToken(buffer, &token));
    ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, state));
    return ZYAN_STATUS_SUCCESS;
}

/**
 * Retrieves the current function for `func` and installs the matching fuzz hook.
 */
static void InstallFuzzHook(ZydisFormatter* formatter, ZyanU8 hook_func)
{
    const ZyanUSize func = hook_func % (ZYDIS_FORMATTER_FUNC_MAX_VALUE + 1);
    const void* fn = ZYAN_NULL;
    if (!ZYAN_SUCCESS(ZydisFormatterSetHook(formatter, (ZydisFormatterFunction)func, &fn)))
    {
        return;  // Function not replaceable for the current formatter style.
    }
    fuzz_hook_default = (ZyanStatus (*)(const ZydisFormatter*,
        ZydisFormatterBuffer*, ZydisFormatterContext*))fn;
    const void* hook = (func == ZYDIS_FORMATTER_FUNC_FORMAT_INSTRUCTION)
        ? (const void*)&FuzzHookFormatInstruction
        : (const void*)&FuzzHook;
    ZydisFormatterSetHook(formatter, (ZydisFormatterFunction)func, &hook);
}

/* ============================================================================================== */
/* Fuzz target                                                                                    */
/* ============================================================================================== */

// We disable enum sanitization here because we actually want Zydis to be tested with
// possibly invalid enum values in mind, thus need to be able to create them here.
ZYAN_NO_SANITIZE("enum")
int ZydisFuzzTarget(ZydisStreamRead read_fn, void* stream_ctx)
{
    ZydisFuzzControlBlock control_block;
    if (read_fn(
        stream_ctx, (ZyanU8*)&control_block, sizeof(control_block)) != sizeof(control_block))
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
    for (int mode = 0; mode <= ZYDIS_DECODER_MODE_MAX_VALUE; ++mode)
    {
        if (!ZYAN_SUCCESS(ZydisDecoderEnableMode(&decoder, (ZydisDecoderMode)mode,
            control_block.decoder_mode[mode] ? 1 : 0)))
        {
            ZYDIS_MAYBE_FPUTS("Failed to adjust decoder-mode\n", ZYAN_STDERR);
            return EXIT_FAILURE;
        }
    }

    ZyanU8 buffer[32];
    ZyanUSize input_len = read_fn(stream_ctx, buffer, sizeof(buffer));
    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, buffer, input_len, &instruction, operands)))
    {
        return EXIT_FAILURE;
    }

    ZyanU8 style_count = control_block.style_count % (ZYDIS_FORMATTER_STYLE_MAX_VALUE + 2);
    if (style_count == 0)
    {
        style_count = 1;
    }

    for (ZyanU8 s = 0; s < style_count; ++s)
    {
        ZydisFormatter formatter;
        const ZydisFormatterStyle style = (ZydisFormatterStyle)((control_block.style_lo + s) %
            (ZYDIS_FORMATTER_STYLE_MAX_VALUE + 1));
        if (!ZYAN_SUCCESS(ZydisFormatterInit(&formatter, style)))
        {
            ZYDIS_MAYBE_FPUTS("Failed to initialize formatter\n", ZYAN_STDERR);
            return EXIT_FAILURE;
        }

        // Deterministic property sweep: raw values are deliberately applied and failures are
        // ignored, the formatter validates the combinations.
        for (ZyanU8 p = 0; p < control_block.prop_count; ++p)
        {
            const ZyanUSize prop = (control_block.prop_lo + p) %
                (ZYDIS_FORMATTER_PROP_MAX_VALUE + 1);
            ZyanUPointer value = (ZyanUPointer)(control_block.prop_value + p);
            switch (prop)
            {
            case ZYDIS_FORMATTER_PROP_DEC_PREFIX:
            case ZYDIS_FORMATTER_PROP_DEC_SUFFIX:
            case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
            case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
                value = (control_block.prop_value & 1)
                    ? (ZyanUPointer)&fuzz_property_string
                    : (ZyanUPointer)ZYAN_NULL;
                break;
            default:
                break;
            }
            ZydisFormatterSetProperty(&formatter, (ZydisFormatterProperty)prop, value);
        }

        if (control_block.hook_mask & 1)
        {
            InstallFuzzHook(&formatter, control_block.hook_func);
        }

        // Output-buffer truncation sweep: the requested size, a tiny and the full buffer.
        char format_buffer[256];
        ZyanUSize output_len = ZYAN_MIN(sizeof(format_buffer),
            ZYAN_MAX((ZyanUSize)1, (ZyanUSize)control_block.formatter_max_len));
        if (s == 1)
        {
            output_len = 16;
        }
        else if (s == 2)
        {
            output_len = 1;
        }

        ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
            instruction.operand_count_visible, format_buffer, output_len,
            control_block.runtime_address, ZYAN_NULL);

        // Fuzz the tokenizer.
        const ZydisFormatterToken* token;
        ZyanStatus status = ZydisFormatterTokenizeInstruction(&formatter, &instruction, operands,
            instruction.operand_count_visible, format_buffer, output_len,
            control_block.runtime_address, &token, ZYAN_NULL);
        while (ZYAN_SUCCESS(status))
        {
            ZydisTokenType type;
            ZyanConstCharPointer value;
            if (!ZYAN_SUCCESS(status = ZydisFormatterTokenGetValue(token, &type, &value)))
            {
                break;
            }
            status = ZydisFormatterTokenNext(&token);
        }

        // Fuzz single-operand formatting and tokenization.
        if (instruction.operand_count_visible > 0)
        {
            const ZyanU8 op_idx =
                (ZyanU8)(control_block.runtime_address % instruction.operand_count_visible);
            const ZydisDecodedOperand* op = &operands[op_idx];
            ZydisFormatterFormatOperand(&formatter, &instruction, op, format_buffer, output_len,
                control_block.runtime_address, ZYAN_NULL);
            status = ZydisFormatterTokenizeOperand(&formatter, &instruction, op, format_buffer,
                output_len, control_block.runtime_address, &token, ZYAN_NULL);
            while (ZYAN_SUCCESS(status))
            {
                ZydisTokenType type;
                ZyanConstCharPointer value;
                if (!ZYAN_SUCCESS(status = ZydisFormatterTokenGetValue(token, &type, &value)))
                {
                    break;
                }
                status = ZydisFormatterTokenNext(&token);
            }
        }
    }

    return EXIT_SUCCESS;
}

/* ============================================================================================== */

