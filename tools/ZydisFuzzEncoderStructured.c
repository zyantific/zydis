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
 * Fuzz target for the encoder driven by structurally valid encoder requests.
 *
 * Rationale: `ZydisFuzzEncoder` builds `ZydisEncoderRequest` instances from raw fuzz bytes,
 * which requires heavy field sanitization to reach the encoder at all (see the comment at
 * `ZydisFuzzEncoder.c:185`) because encode success depends on a semantically consistent
 * request: mnemonic, operand types/counts/widths and encoding features must cross-check
 * inside `ZydisFindMatchingDefinition`/`ZydisAreEvexFeaturesCompatible`/
 * `ZydisAreMvexFeaturesCompatible` (`src/Encoder.c`). That consistency gate is
 * mutation-resistant, so byte-level mutation mostly probes rejection paths: the union
 * coverage of 2026-11-13 leaves ~253 lines of `src/Encoder.c` dark, the
 * `ZYDIS_ENCODABLE_ENCODING_MVEX` feature-compat machinery barely reached and the public
 * `ZydisEncoderEncodeInstructionAbsolute` entry point completely unreached.
 *
 * This target starts from a request produced by
 * `ZydisEncoderDecodedInstructionToEncoderRequest` for an attacker-controlled (fuzzed) but
 * genuinely decodable instruction, then deterministically sweeps the request option fields
 * (allowed encodings incl. MVEX, prefixes, branch type/width, size hints, EVEX and MVEX
 * broadcast/rounding/conversion/swizzle) around that valid skeleton and exercises both
 * `ZydisEncoderEncodeInstruction` and `ZydisEncoderEncodeInstructionAbsolute`. The encoder
 * must safely reject every inconsistent combination instead of misbehaving on it.
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
    ZyanU8 encodings_sel;  ///< Selector for the `allowed_encodings` sweep value.
    ZyanU8 prefixes_sel;   ///< Selector for the prefix sweep value.
    ZyanU8 branch_sel;     ///< Selector for the branch type/width sweep values.
    ZyanU8 hint_sel;       ///< Selector for the address/operand size hint sweep values.
    ZyanU8 evex_sel;       ///< Selector for the EVEX sweep values.
    ZyanU8 mvex_sel;       ///< Selector for the MVEX sweep values.
    ZyanU8 abs_mode;       ///< Bit 0: additionally call `ZydisEncoderEncodeInstructionAbsolute`.
    ZyanU8 sweep_count;    ///< Number of field-sweep iterations (clamped to 32).
    ZyanU64 runtime_address; ///< Runtime address for absolute encoding.
} ZydisFuzzControlBlock;

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/**
 * Applies one deterministic option-field sweep iteration to `request`.
 */
static void SweepRequest(ZydisEncoderRequest* request, const ZydisFuzzControlBlock* cb,
    ZyanU8 iteration)
{
    static const ZyanU64 prefixes[] =
    {
        0,
        ZYDIS_ATTRIB_HAS_LOCK,
        ZYDIS_ATTRIB_HAS_REP,
        ZYDIS_ATTRIB_HAS_REPNE,
        ZYDIS_ATTRIB_HAS_XACQUIRE,
        ZYDIS_ATTRIB_HAS_XRELEASE,
        ZYDIS_ATTRIB_HAS_NOTRACK,
        ZYDIS_ATTRIB_HAS_SEGMENT_FS
    };

    switch (cb->encodings_sel % 4)
    {
    case 0:
        request->allowed_encodings = ZYDIS_ENCODABLE_ENCODING_DEFAULT;
        break;
    case 1:
        request->allowed_encodings = (ZydisEncodableEncoding)ZYDIS_ENCODABLE_ENCODING_MAX_VALUE;
        break;
    case 2:
        request->allowed_encodings = (ZydisEncodableEncoding)
            (1ULL << ((cb->encodings_sel + iteration) % 8));
        break;
    default:
        request->allowed_encodings = (ZydisEncodableEncoding)
            (ZYDIS_ENCODABLE_ENCODING_MAX_VALUE &
             ~(1ULL << ((cb->encodings_sel + iteration) % 4)));
        break;
    }

    request->prefixes = (ZydisInstructionAttributes)
        prefixes[(cb->prefixes_sel + iteration) % ZYAN_ARRAY_LENGTH(prefixes)];
    request->branch_type = (ZydisBranchType)
        ((cb->branch_sel + iteration) % (ZYDIS_BRANCH_TYPE_MAX_VALUE + 1));
    request->branch_width = (ZydisBranchWidth)
        ((cb->branch_sel + iteration) % (ZYDIS_BRANCH_WIDTH_MAX_VALUE + 1));
    request->address_size_hint = (ZydisAddressSizeHint)
        ((cb->hint_sel + iteration) % (ZYDIS_ADDRESS_SIZE_HINT_MAX_VALUE + 1));
    request->operand_size_hint = (ZydisOperandSizeHint)
        ((cb->hint_sel + iteration) % (ZYDIS_OPERAND_SIZE_HINT_MAX_VALUE + 1));
    request->evex.broadcast = (ZydisBroadcastMode)
        ((cb->evex_sel + iteration) % (ZYDIS_BROADCAST_MODE_MAX_VALUE + 1));
    request->evex.rounding = (ZydisRoundingMode)
        ((cb->evex_sel + iteration) % (ZYDIS_ROUNDING_MODE_MAX_VALUE + 1));
    request->mvex.broadcast = (ZydisBroadcastMode)
        ((cb->mvex_sel + iteration) % (ZYDIS_BROADCAST_MODE_MAX_VALUE + 1));
    request->mvex.conversion = (ZydisConversionMode)
        ((cb->mvex_sel + iteration) % (ZYDIS_CONVERSION_MODE_MAX_VALUE + 1));
    request->mvex.rounding = (ZydisRoundingMode)
        ((cb->mvex_sel + iteration) % (ZYDIS_ROUNDING_MODE_MAX_VALUE + 1));
    request->mvex.swizzle = (ZydisSwizzleMode)
        ((cb->mvex_sel + iteration) % (ZYDIS_SWIZZLE_MODE_MAX_VALUE + 1));
}

/* ============================================================================================== */
/* Fuzz target                                                                                    */
/* ============================================================================================== */

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

    ZydisEncoderRequest request;
    if (!ZYAN_SUCCESS(ZydisEncoderDecodedInstructionToEncoderRequest(&instruction, operands,
        instruction.operand_count_visible, &request)))
    {
        return EXIT_SUCCESS;
    }

    // Encode the untouched request skeleton first, then sweep the option fields. Both encode
    // entry points must safely reject every inconsistent swept combination.
    ZyanU8 encoded[ZYDIS_MAX_INSTRUCTION_LENGTH];
    ZyanUSize encoded_length = sizeof(encoded);
    (void)ZydisEncoderEncodeInstruction(&request, encoded, &encoded_length);
    if (control_block.abs_mode & 1)
    {
        encoded_length = sizeof(encoded);
        (void)ZydisEncoderEncodeInstructionAbsolute(&request, encoded, &encoded_length,
            control_block.runtime_address);
    }

    ZyanU8 sweep_count = control_block.sweep_count;
    if (sweep_count > 32)
    {
        sweep_count = 32;
    }
    for (ZyanU8 i = 0; i < sweep_count; ++i)
    {
        ZydisEncoderRequest swept = request;
        SweepRequest(&swept, &control_block, i);
        encoded_length = sizeof(encoded);
        (void)ZydisEncoderEncodeInstruction(&swept, encoded, &encoded_length);
        if (control_block.abs_mode & 1)
        {
            encoded_length = sizeof(encoded);
            (void)ZydisEncoderEncodeInstructionAbsolute(&swept, encoded, &encoded_length,
                control_block.runtime_address);
        }
    }

    return EXIT_SUCCESS;
}

/* ============================================================================================== */


