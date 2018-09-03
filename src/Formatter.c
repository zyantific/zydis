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

#include <Zycore/LibC.h>
#include <Zydis/Formatter.h>
#include <Zydis/Internal/FormatterATT.h>
#include <Zydis/Internal/FormatterIntel.h>
#include <Zydis/Internal/String.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Formatter presets                                                                              */
/* ---------------------------------------------------------------------------------------------- */

static const ZydisFormatter FORMATTER_PRESETS[ZYDIS_FORMATTER_STYLE_MAX_VALUE + 1] =
{
    // ZYDIS_FORMATTER_STYLE_ATT
    {
        /* style                   */ ZYDIS_FORMATTER_STYLE_ATT,
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
        /* imm_signedness          */ ZYDIS_SIGNEDNESS_AUTO,
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
                    /* string      */ &FORMATTER_PRESETS[
                                          ZYDIS_FORMATTER_STYLE_ATT].number_format[
                                          ZYDIS_NUMERIC_BASE_HEX     ][0].string_data,
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
        /* func_format_instruction */ &ZydisFormatterATTFormatInstruction,
        /* func_pre_operand        */ ZYAN_NULL,
        /* func_post_operand       */ ZYAN_NULL,
        /* func_format_operand_reg */ &ZydisFormatterATTFormatOperandREG,
        /* func_format_operand_mem */ &ZydisFormatterATTFormatOperandMEM,
        /* func_format_operand_ptr */ &ZydisFormatterATTFormatOperandPTR,
        /* func_format_operand_imm */ &ZydisFormatterATTFormatOperandIMM,
        /* func_print_mnemonic     */ &ZydisFormatterATTPrintMnemonic,
        /* func_print_register     */ &ZydisFormatterATTPrintRegister,
        /* func_print_address_abs  */ &ZydisFormatterATTPrintAddressAbsolute,
        /* func_print_address_rel  */ &ZydisFormatterATTPrintAddressRelative,
        /* func_print_disp         */ &ZydisFormatterATTPrintDISP,
        /* func_print_imm          */ &ZydisFormatterATTPrintIMM,
        /* func_print_mem_size     */ &ZydisFormatterATTPrintMemorySize,
        /* func_print_mem_seg      */ &ZydisFormatterATTPrintMemorySegment,
        /* func_print_prefixes     */ &ZydisFormatterATTPrintPrefixes,
        /* func_print_decorator    */ &ZydisFormatterATTPrintDecorator
    },

    // ZYDIS_FORMATTER_STYLE_INTEL
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
                    /* string      */ &FORMATTER_PRESETS[
                                          ZYDIS_FORMATTER_STYLE_INTEL].number_format[
                                          ZYDIS_NUMERIC_BASE_HEX     ][0].string_data,
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
        /* func_format_operand_reg */ &ZydisFormatterIntelFormatOperandREG,
        /* func_format_operand_mem */ &ZydisFormatterIntelFormatOperandMEM,
        /* func_format_operand_ptr */ &ZydisFormatterIntelFormatOperandPTR,
        /* func_format_operand_imm */ &ZydisFormatterIntelFormatOperandIMM,
        /* func_print_mnemonic     */ &ZydisFormatterIntelPrintMnemonic,
        /* func_print_register     */ &ZydisFormatterIntelPrintRegister,
        /* func_print_address_abs  */ &ZydisFormatterIntelPrintAddressAbsolute,
        /* func_print_address_rel  */ &ZydisFormatterIntelPrintAddressRelative,
        /* func_print_disp         */ &ZydisFormatterIntelPrintDISP,
        /* func_print_imm          */ &ZydisFormatterIntelPrintIMM,
        /* func_print_mem_size     */ &ZydisFormatterIntelPrintMemorySize,
        /* func_print_mem_seg      */ &ZydisFormatterIntelPrintMemorySegment,
        /* func_print_prefixes     */ &ZydisFormatterIntelPrintPrefixes,
        /* func_print_decorator    */ &ZydisFormatterIntelPrintDecorator
    },

    // ZYDIS_FORMATTER_STYLE_INTEL_MASM
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
                    /* string      */ &FORMATTER_PRESETS[
                                          ZYDIS_FORMATTER_STYLE_INTEL_MASM].number_format[
                                          ZYDIS_NUMERIC_BASE_HEX     ][1].string_data,
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
        /* func_format_operand_reg */ &ZydisFormatterIntelFormatOperandREG,
        /* func_format_operand_mem */ &ZydisFormatterIntelFormatOperandMEM,
        /* func_format_operand_ptr */ &ZydisFormatterIntelFormatOperandPTR,
        /* func_format_operand_imm */ &ZydisFormatterIntelFormatOperandIMM,
        /* func_print_mnemonic     */ &ZydisFormatterIntelPrintMnemonic,
        /* func_print_register     */ &ZydisFormatterIntelPrintRegister,
        /* func_print_address_abs  */ &ZydisFormatterIntelPrintAddressMASM,
        /* func_print_address_rel  */ ZYAN_NULL,
        /* func_print_disp         */ &ZydisFormatterIntelPrintDISP,
        /* func_print_imm          */ &ZydisFormatterIntelPrintIMM,
        /* func_print_mem_size     */ &ZydisFormatterIntelPrintMemorySize,
        /* func_print_mem_seg      */ &ZydisFormatterIntelPrintMemorySegment,
        /* func_print_prefixes     */ &ZydisFormatterIntelPrintPrefixes,
        /* func_print_decorator    */ &ZydisFormatterIntelPrintDecorator
    }
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZyanStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style)
{
    if (!formatter || (style > ZYDIS_FORMATTER_STYLE_MAX_VALUE))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_MEMCPY(formatter, &FORMATTER_PRESETS[style], sizeof(*formatter));

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterSetProperty(ZydisFormatter* formatter, ZydisFormatterProperty property,
    ZyanUPointer value)
{
    if (!formatter)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZydisNumericBase base = (ZydisNumericBase)(-1);
    ZyanU8 index = 0xFF;

    switch (property)
    {
    case ZYDIS_FORMATTER_PROP_UPPERCASE:
    {
        formatter->letter_case = (value) ? ZYDIS_LETTER_CASE_UPPER : ZYDIS_LETTER_CASE_DEFAULT;
        break;
    }
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE:
    {
        formatter->force_memory_size = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    }
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSEG:
    {
        formatter->force_memory_segment = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DETAILED_PREFIXES:
    {
        formatter->detailed_prefixes = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    }
    case ZYDIS_FORMATTER_PROP_ADDR_BASE:
    {
        if ((ZydisNumericBase)value > ZYDIS_NUMERIC_BASE_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->addr_base = (ZydisNumericBase)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_ADDR_SIGNEDNESS:
    {
        if ((ZydisSignedness)value > ZYDIS_SIGNEDNESS_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->addr_signedness = (ZydisSignedness)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_ADDR_PADDING_ABSOLUTE:
    {
        formatter->addr_padding_absolute = (ZydisPadding)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_ADDR_PADDING_RELATIVE:
    {
        formatter->addr_padding_relative = (ZydisPadding)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DISP_BASE:
    {
        if ((ZydisNumericBase)value > ZYDIS_NUMERIC_BASE_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->disp_base = (ZydisNumericBase)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DISP_SIGNEDNESS:
    {
        if ((ZydisSignedness)value > ZYDIS_SIGNEDNESS_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->disp_signedness = (ZydisSignedness)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DISP_PADDING:
    {
        if ((ZydisPadding)value == ZYDIS_PADDING_AUTO)
        {
            if (formatter->style > ZYDIS_FORMATTER_STYLE_MAX_VALUE)
            {
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
            formatter->disp_padding = FORMATTER_PRESETS[formatter->style].disp_padding;
        }
        formatter->disp_padding = (ZydisPadding)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_IMM_BASE:
    {
        if ((ZydisNumericBase)value > ZYDIS_NUMERIC_BASE_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->imm_base = (ZydisNumericBase)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_IMM_SIGNEDNESS:
    {
        if ((ZydisSignedness)value  > ZYDIS_SIGNEDNESS_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->imm_signedness  = (ZydisSignedness)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_IMM_PADDING:
    {
        if ((ZydisPadding)value == ZYDIS_PADDING_AUTO)
        {
            if (formatter->style > ZYDIS_FORMATTER_STYLE_MAX_VALUE)
            {
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
            formatter->imm_padding = FORMATTER_PRESETS[formatter->style].imm_padding;
        }
        formatter->imm_padding = (ZydisPadding)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DEC_PREFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_DEC;
        index = 0;
    }
    case ZYDIS_FORMATTER_PROP_DEC_SUFFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_DEC;
        index = 1;
    }
    case ZYDIS_FORMATTER_PROP_HEX_UPPERCASE:
    {
        formatter->hex_uppercase = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    }
    case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_HEX;
        index = 0;
    }
    case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_HEX;
        index = 1;
    }
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // Set prefix or suffix
    if (base != (ZydisNumericBase)(-1))
    {
        if (value)
        {
            const ZyanUSize len = ZYAN_STRLEN((char*)value);
            if (len > 10)
            {
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
            ZYAN_MEMCPY(formatter->number_format[base][index].buffer, (void*)value, len);
            formatter->number_format[base][index].string_data.string.vector.data =
                formatter->number_format[base][index].buffer;
            formatter->number_format[base][index].string_data.string.vector.size = len;
            formatter->number_format[base][index].string =
                &formatter->number_format[base][index].string_data;
        } else
        {
            formatter->number_format[base][index].string = ZYAN_NULL;
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterSetHook(ZydisFormatter* formatter, ZydisFormatterFunction type,
    const void** callback)
{
    if (!formatter || !callback || (type > ZYDIS_FORMATTER_FUNC_MAX_VALUE))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const void* const temp = *callback;

    // This code relies on the order of the enum values and the function fields inside the
    // `ZydisFormatter` struct
    *callback = *(const void**)(&formatter->func_pre_instruction + type);
    if (!temp)
    {
        return ZYAN_STATUS_SUCCESS;
    }
    *(ZyanUPointer*)(&formatter->func_pre_instruction + type) = *(ZyanUPointer*)&temp;

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZyanUSize length,
    ZyanU64 runtime_address)
{
     return ZydisFormatterFormatInstructionEx(formatter, instruction, buffer, length,
         runtime_address, ZYAN_NULL);
}

ZyanStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZyanUSize length,
    ZyanU64 runtime_address, void* user_data)
{
    if (!formatter || !instruction || !buffer || (length == 0))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanString string;
    string.flags               = ZYAN_STRING_HAS_FIXED_CAPACITY;
    string.vector.allocator    = ZYAN_NULL;
    string.vector.element_size = sizeof(char);
    string.vector.size         = 1;
    string.vector.capacity     = length;
    string.vector.data         = buffer;
    *buffer = '\0';

    ZydisFormatterContext context;
    context.instruction        = instruction;
    context.runtime_address    = runtime_address;
    context.operand            = ZYAN_NULL;
    context.user_data          = user_data;

    if (formatter->func_pre_instruction)
    {
        ZYAN_CHECK(formatter->func_pre_instruction(formatter, &string, &context));
    }

    ZYAN_CHECK(formatter->func_format_instruction(formatter, &string, &context));

    if (formatter->func_post_instruction)
    {
        ZYAN_CHECK(formatter->func_post_instruction(formatter, &string, &context));
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterFormatOperand(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZyanU8 index, char* buffer, ZyanUSize length,
    ZyanU64 runtime_address)
{
    return ZydisFormatterFormatOperandEx(formatter, instruction, index, buffer, length,
        runtime_address, ZYAN_NULL);
}

ZyanStatus ZydisFormatterFormatOperandEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZyanU8 index, char* buffer, ZyanUSize length,
    ZyanU64 runtime_address, void* user_data)
{
if (!formatter || !instruction || index >= instruction->operand_count || !buffer ||
        (length == 0))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanString string;
    string.flags               = ZYAN_STRING_HAS_FIXED_CAPACITY;
    string.vector.allocator    = ZYAN_NULL;
    string.vector.element_size = sizeof(char);
    string.vector.size         = 1;
    string.vector.capacity     = length;
    string.vector.data         = buffer;
    *buffer = '\0';

    ZydisFormatterContext context;
    context.instruction        = instruction;
    context.runtime_address    = runtime_address;
    context.operand            = &instruction->operands[index];
    context.user_data          = user_data;

    // We ignore `ZYDIS_STATUS_SKIP_TOKEN` for all operand-functions as it does not make any sense
    // to skip the only operand printed by this function

    if (formatter->func_pre_operand)
    {
        ZYAN_CHECK(formatter->func_pre_operand(formatter, &string, &context));
    }

    switch (context.operand->type)
    {
    case ZYDIS_OPERAND_TYPE_REGISTER:
        ZYAN_CHECK(formatter->func_format_operand_reg(formatter, &string, &context));
        break;
    case ZYDIS_OPERAND_TYPE_MEMORY:
        ZYAN_CHECK(formatter->func_format_operand_mem(formatter, &string, &context));
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        ZYAN_CHECK(formatter->func_format_operand_imm(formatter, &string, &context));
        break;
    case ZYDIS_OPERAND_TYPE_POINTER:
        ZYAN_CHECK(formatter->func_format_operand_ptr(formatter, &string, &context));
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (formatter->func_post_operand)
    {
        ZYAN_CHECK(formatter->func_post_operand(formatter, &string, &context));
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ============================================================================================== */

/* ============================================================================================== */
