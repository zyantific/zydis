/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Mappa

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
 * This file implements fuzz target for encoder.
 */

#include "ZydisFuzzShared.h"

/* ============================================================================================== */
/* Fuzz target                                                                                    */
/* ============================================================================================== */

ZYAN_NO_SANITIZE("enum")
int ZydisFuzzTarget(ZydisStreamRead read_fn, void *stream_ctx)
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
