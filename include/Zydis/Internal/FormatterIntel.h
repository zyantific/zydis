/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd, Joel Hoener

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
 * @brief   Implements the `INTEL` style instruction-formatter.
 */

#ifndef ZYDIS_FORMATTER_INTEL_H
#define ZYDIS_FORMATTER_INTEL_H

#include <Zydis/Formatter.h>
#include <Zydis/Internal/FormatterShared.h>
#include <Zydis/Internal/String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Intel                                                                                          */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatInstruction(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelFormatOperandMEM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintMnemonic(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintRegister(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context, ZydisRegister reg);

ZyanStatus ZydisFormatterIntelPrintDISP(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintSize(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */
/* MASM                                                                                           */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatInstructionMASM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintAddressMASM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Fomatter presets                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* INTEL                                                                                          */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   The default formatter configuration for `INTEL` style disassembly.
 */
static const ZydisFormatter FORMATTER_INTEL =
{
    /* style                   */ ZYDIS_FORMATTER_STYLE_INTEL,
    /* letter_case             */ ZYDIS_LETTER_CASE_DEFAULT,
    /* force_memory_size       */ ZYAN_FALSE,
    /* force_memory_seg        */ ZYAN_FALSE,
    /* detailed_prefixes       */ ZYAN_FALSE,
    /* addr_base               */ ZYDIS_NUMERIC_BASE_HEX,
    /* addr_signedness         */ ZYDIS_SIGNEDNESS_SIGNED,
    /* addr_padding_absolute   */ ZYDIS_PADDING_AUTO,
    /* addr_padding_relative   */ 2,
    /* disp_base               */ ZYDIS_NUMERIC_BASE_HEX,
    /* disp_signedness         */ ZYDIS_SIGNEDNESS_SIGNED,
    /* disp_padding            */ 2,
    /* imm_base                */ ZYDIS_NUMERIC_BASE_HEX,
    /* imm_signedness          */ ZYDIS_SIGNEDNESS_UNSIGNED,
    /* imm_padding             */ 2,
    /* hex_uppercase           */ ZYAN_TRUE,
    /* number_format           */
    {
        // ZYDIS_NUMERIC_BASE_DEC
        {
            // Prefix
            {
                /* string      */ ZYAN_NULL,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW(""),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            },
            // Suffix
            {
                /* string      */ ZYAN_NULL,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW(""),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            }
        },
        // ZYDIS_NUMERIC_BASE_HEX
        {
            // Prefix
            {
                /* string      */ &FORMATTER_INTEL.number_format[
                                      ZYDIS_NUMERIC_BASE_HEX][0].string_data,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW("0x"),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            },
            // Suffix
            {
                /* string      */ ZYAN_NULL,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW(""),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            }
        }
    },
    /* func_pre_instruction    */ ZYAN_NULL,
    /* func_post_instruction   */ ZYAN_NULL,
    /* func_format_instruction */ &ZydisFormatterIntelFormatInstruction,
    /* func_pre_operand        */ ZYAN_NULL,
    /* func_post_operand       */ ZYAN_NULL,
    /* func_format_operand_reg */ &ZydisFormatterSharedFormatOperandREG,
    /* func_format_operand_mem */ &ZydisFormatterIntelFormatOperandMEM,
    /* func_format_operand_ptr */ &ZydisFormatterSharedFormatOperandPTR,
    /* func_format_operand_imm */ &ZydisFormatterSharedFormatOperandIMM,
    /* func_print_mnemonic     */ &ZydisFormatterIntelPrintMnemonic,
    /* func_print_register     */ &ZydisFormatterIntelPrintRegister,
    /* func_print_address_abs  */ &ZydisFormatterSharedPrintAddressABS,
    /* func_print_address_rel  */ &ZydisFormatterSharedPrintAddressREL,
    /* func_print_disp         */ &ZydisFormatterIntelPrintDISP,
    /* func_print_imm          */ &ZydisFormatterSharedPrintIMM,
    /* func_print_size         */ &ZydisFormatterIntelPrintSize,
    /* func_print_segment      */ &ZydisFormatterSharedPrintSegment,
    /* func_print_prefixes     */ &ZydisFormatterSharedPrintPrefixes,
    /* func_print_decorator    */ &ZydisFormatterSharedPrintDecorator
};

/* ---------------------------------------------------------------------------------------------- */
/* MASM                                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   The default formatter configuration for `MASM` style disassembly.
 */
static const ZydisFormatter FORMATTER_INTEL_MASM =
{
    /* style                   */ ZYDIS_FORMATTER_STYLE_INTEL_MASM,
    /* letter_case             */ ZYDIS_LETTER_CASE_DEFAULT,
    /* force_memory_size       */ ZYAN_TRUE,
    /* force_memory_seg        */ ZYAN_FALSE,
    /* detailed_prefixes       */ ZYAN_FALSE,
    /* addr_base               */ ZYDIS_NUMERIC_BASE_HEX,
    /* addr_signedness         */ ZYDIS_SIGNEDNESS_SIGNED,
    /* addr_padding_absolute   */ ZYDIS_PADDING_DISABLED,
    /* addr_padding_relative   */ ZYDIS_PADDING_DISABLED,
    /* disp_base               */ ZYDIS_NUMERIC_BASE_HEX,
    /* disp_signedness         */ ZYDIS_SIGNEDNESS_SIGNED,
    /* disp_padding            */ ZYDIS_PADDING_DISABLED,
    /* imm_base                */ ZYDIS_NUMERIC_BASE_HEX,
    /* imm_signedness          */ ZYDIS_SIGNEDNESS_AUTO,
    /* imm_padding             */ ZYDIS_PADDING_DISABLED,
    /* hex_uppercase           */ ZYAN_TRUE,
    /* number_format           */
    {
        // ZYDIS_NUMERIC_BASE_DEC
        {
            // Prefix
            {
                /* string      */ ZYAN_NULL,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW(""),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            },
            // Suffix
            {
                /* string      */ ZYAN_NULL,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW(""),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            }
        },
        // ZYDIS_NUMERIC_BASE_HEX
        {
            // Prefix
            {
                /* string      */ ZYAN_NULL,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW(""),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            },
            // Suffix
            {
                /* string      */ &FORMATTER_INTEL_MASM.number_format[
                                      ZYDIS_NUMERIC_BASE_HEX][1].string_data,
                /* string_data */ ZYAN_DECLARE_STRING_VIEW("h"),
                /* buffer      */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            }
        }
    },
    /* func_pre_instruction    */ ZYAN_NULL,
    /* func_post_instruction   */ ZYAN_NULL,
    /* func_format_instruction */ &ZydisFormatterIntelFormatInstructionMASM,
    /* func_pre_operand        */ ZYAN_NULL,
    /* func_post_operand       */ ZYAN_NULL,
    /* func_format_operand_reg */ &ZydisFormatterSharedFormatOperandREG,
    /* func_format_operand_mem */ &ZydisFormatterIntelFormatOperandMEM,
    /* func_format_operand_ptr */ &ZydisFormatterSharedFormatOperandPTR,
    /* func_format_operand_imm */ &ZydisFormatterSharedFormatOperandIMM,
    /* func_print_mnemonic     */ &ZydisFormatterIntelPrintMnemonic,
    /* func_print_register     */ &ZydisFormatterIntelPrintRegister,
    /* func_print_address_abs  */ &ZydisFormatterIntelPrintAddressMASM,
    /* func_print_address_rel  */ &ZydisFormatterIntelPrintAddressMASM,
    /* func_print_disp         */ &ZydisFormatterIntelPrintDISP,
    /* func_print_imm          */ &ZydisFormatterSharedPrintIMM,
    /* func_print_size         */ &ZydisFormatterIntelPrintSize,
    /* func_print_segment      */ &ZydisFormatterSharedPrintSegment,
    /* func_print_prefixes     */ &ZydisFormatterSharedPrintPrefixes,
    /* func_print_decorator    */ &ZydisFormatterSharedPrintDecorator
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif // ZYDIS_FORMATTER_INTEL_H
