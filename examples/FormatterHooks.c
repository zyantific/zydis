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

/**
 * @file
 * @brief   Demonstrates the hooking functionality of the @c ZydisFormatter class.
 *
 * This example demonstrates the hooking functionality of the @c ZydisFormatter class by
 * rewriting the mnemonics of (V)CMPPS and (V)CMPPD to their corresponding alias-forms (based on
 * the condition encoded in the immediate operand).
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
#include <Zydis/Zydis.h>

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/**
 * @brief   Appends formatted text to the given `string`.
 *
 * @param   string  A pointer to the string.
 * @param   format  The format string.
 * @param   ...     The format arguments.
 *
 * @return  @c ZYAN_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given text.
 */
static ZyanStatus ZydisStringAppendFormatC(ZydisString* string, const char* format, ...)
{
    if (!string || !string->buffer || !format)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    va_list arglist;
    va_start(arglist, format);

    const int w = vsnprintf(string->buffer + string->length, string->capacity - string->length,
        format, arglist);
    if ((w < 0) || ((size_t)w > string->capacity - string->length))
    {
        va_end(arglist);
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    string->length += w;

    va_end(arglist);

    return ZYAN_STATUS_SUCCESS;
}

/* ============================================================================================== */
/* Static data                                                                                    */
/* ============================================================================================== */

/**
 * @brief   Static array with the condition-code strings.
 */
static const char* conditionCodeStrings[0x20] =
{
    /*00*/ "eq",
    /*01*/ "lt",
    /*02*/ "le",
    /*03*/ "unord",
    /*04*/ "neq",
    /*05*/ "nlt",
    /*06*/ "nle",
    /*07*/ "ord",
    /*08*/ "eq_uq",
    /*09*/ "nge",
    /*0A*/ "ngt",
    /*0B*/ "false",
    /*0C*/ "oq",
    /*0D*/ "ge",
    /*0E*/ "gt",
    /*0F*/ "true",
    /*10*/ "eq_os",
    /*11*/ "lt_oq",
    /*12*/ "le_oq",
    /*13*/ "unord_s",
    /*14*/ "neq_us",
    /*15*/ "nlt_uq",
    /*16*/ "nle_uq",
    /*17*/ "ord_s",
    /*18*/ "eq_us",
    /*19*/ "nge_uq",
    /*1A*/ "ngt_uq",
    /*1B*/ "false_os",
    /*1C*/ "neq_os",
    /*1D*/ "ge_oq",
    /*1E*/ "gt_oq",
    /*1F*/ "true_us"
};

/* ============================================================================================== */
/* Enums and Types                                                                                */
/* ============================================================================================== */

/**
 * @brief   Custom user data struct.
 */
typedef struct ZydisCustomUserData_
{
    ZyanBool ommitImmediate;
} ZydisCustomUserData;

/* ============================================================================================== */
/* Hook callbacks                                                                                 */
/* ============================================================================================== */

ZydisFormatterFunc defaultPrintMnemonic;

static ZyanStatus ZydisFormatterPrintMnemonic(const ZydisFormatter* formatter,
    ZydisString* string, ZydisFormatterContext* context)
{
    // We use the user-data to pass data to the @c ZydisFormatterFormatOperandImm function
    ZydisCustomUserData* userData = (ZydisCustomUserData*)context->userData;
    userData->ommitImmediate = ZYAN_TRUE;

    // Rewrite the instruction-mnemonic for the given instructions
    if (context->instruction->operands[context->instruction->operandCount - 1].type ==
        ZYDIS_OPERAND_TYPE_IMMEDIATE)
    {
        const ZyanU8 conditionCode = (ZyanU8)context->instruction->operands[
            context->instruction->operandCount - 1].imm.value.u;
        switch (context->instruction->mnemonic)
        {
        case ZYDIS_MNEMONIC_CMPPS:
            if (conditionCode < 0x08)
            {
                return ZydisStringAppendFormatC(
                    string, "cmp%sps", conditionCodeStrings[conditionCode]);
            }
            break;
        case ZYDIS_MNEMONIC_CMPPD:
            if (conditionCode < 0x08)
            {
                return ZydisStringAppendFormatC(
                    string, "cmp%spd", conditionCodeStrings[conditionCode]);
            }
            break;
        case ZYDIS_MNEMONIC_VCMPPS:
            if (conditionCode < 0x20)
            {
                return ZydisStringAppendFormatC(
                    string, "vcmp%sps", conditionCodeStrings[conditionCode]);
            }
            break;
        case ZYDIS_MNEMONIC_VCMPPD:
            if (conditionCode < 0x20)
            {
                return ZydisStringAppendFormatC(
                    string, "vcmp%spd", conditionCodeStrings[conditionCode]);
            }
            break;
        default:
            break;
        }
    }

    // We did not rewrite the instruction-mnemonic. Signal the @c ZydisFormatterFormatOperandImm
    // function not to omit the operand
    userData->ommitImmediate = ZYAN_FALSE;

    // Default mnemonic printing
    return defaultPrintMnemonic(formatter, string, context);
}

/* ---------------------------------------------------------------------------------------------- */

ZydisFormatterFunc defaultFormatOperandImm;

static ZyanStatus ZydisFormatterFormatOperandImm(const ZydisFormatter* formatter,
    ZydisString* string, ZydisFormatterContext* context)
{
    // The @c ZydisFormatterFormatMnemonic sinals us to omit the immediate (condition-code)
    // operand, because it got replaced by the alias-mnemonic
    const ZydisCustomUserData* userData = (ZydisCustomUserData*)context->userData;
    if (userData->ommitImmediate)
    {
        return ZYDIS_STATUS_SKIP_TOKEN;
    }

    // Default immediate formatting
    return defaultFormatOperandImm(formatter, string, context);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

static void disassembleBuffer(ZydisDecoder* decoder, ZyanU8* data, ZyanUSize length,
    ZyanBool installHooks)
{
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);
    ZydisFormatterSetProperty(&formatter, ZYDIS_FORMATTER_PROP_FORCE_MEMSEG, ZYAN_TRUE);
    ZydisFormatterSetProperty(&formatter, ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE, ZYAN_TRUE);

    if (installHooks)
    {
        defaultPrintMnemonic = (ZydisFormatterFunc)&ZydisFormatterPrintMnemonic;
        ZydisFormatterSetHook(&formatter, ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC,
            (const void**)&defaultPrintMnemonic);
        defaultFormatOperandImm = (ZydisFormatterFunc)&ZydisFormatterFormatOperandImm;
        ZydisFormatterSetHook(&formatter, ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM,
            (const void**)&defaultFormatOperandImm);
    }

    ZyanU64 instructionAddress = 0x007FFFFFFF400000;

    ZydisDecodedInstruction instruction;
    ZydisCustomUserData userData;
    char buffer[256];
    while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(decoder, data, length, &instruction)))
    {
        printf("%016" PRIX64 "  ", instructionAddress);
        ZydisFormatterFormatInstructionEx(&formatter, &instruction, &buffer[0], sizeof(buffer),
            instructionAddress, &userData);
        printf(" %s\n", &buffer[0]);
        data += instruction.length;
        length -= instruction.length;
        instructionAddress += instruction.length;
    }
}

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main()
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        fputs("Invalid zydis version\n", stderr);
        return EXIT_FAILURE;
    }

    ZyanU8 data[] =
    {
        // cmpps xmm1, xmm4, 0x03
        0x0F, 0xC2, 0xCC, 0x03,

        // vcmppd xmm1, xmm2, xmm3, 0x17
        0xC5, 0xE9, 0xC2, 0xCB, 0x17,

        // vcmpps k2 {k7}, zmm2, dword ptr ds:[rax + rbx*4 + 0x100] {1to16}, 0x0F
        0x62, 0xF1, 0x6C, 0x5F, 0xC2, 0x54, 0x98, 0x40, 0x0F
    };

    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);

    disassembleBuffer(&decoder, &data[0], sizeof(data), ZYAN_FALSE);
    puts("");
    disassembleBuffer(&decoder, &data[0], sizeof(data), ZYAN_TRUE);

    return 0;
}

/* ============================================================================================== */
