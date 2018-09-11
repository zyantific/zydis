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

static const ZydisFormatter* const FORMATTER_PRESETS[ZYDIS_FORMATTER_STYLE_MAX_VALUE + 1] =
{
    &FORMATTER_ATT,
    &FORMATTER_INTEL,
    &FORMATTER_INTEL_MASM
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Initialization                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style)
{
    if (!formatter || (style > ZYDIS_FORMATTER_STYLE_MAX_VALUE))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_MEMCPY(formatter, FORMATTER_PRESETS[style], sizeof(*formatter));

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Setter                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

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
    case ZYDIS_FORMATTER_PROP_FORCE_SIZE:
    {
        formatter->force_memory_size = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    }
    case ZYDIS_FORMATTER_PROP_FORCE_SEGMENT:
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
            formatter->disp_padding = FORMATTER_PRESETS[formatter->style]->disp_padding;
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
            formatter->imm_padding = FORMATTER_PRESETS[formatter->style]->imm_padding;
        }
        formatter->imm_padding = (ZydisPadding)value;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DEC_PREFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_DEC;
        index = 0;
        break;
    }
    case ZYDIS_FORMATTER_PROP_DEC_SUFFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_DEC;
        index = 1;
        break;
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
        break;
    }
    case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
    {
        base  = ZYDIS_NUMERIC_BASE_HEX;
        index = 1;
        break;
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

    // The following code relies on the order of the enum values and the function fields inside
    // the `ZydisFormatter` struct

#ifdef ZYAN_DEBUG
    const ZyanUPointer* test = (ZyanUPointer*)(&formatter->func_pre_instruction + type);
    switch (type)
    {
    case ZYDIS_FORMATTER_FUNC_PRE_INSTRUCTION:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_pre_instruction   ); break;
    case ZYDIS_FORMATTER_FUNC_POST_INSTRUCTION:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_post_instruction  ); break;
    case ZYDIS_FORMATTER_FUNC_FORMAT_INSTRUCTION:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_format_instruction); break;
    case ZYDIS_FORMATTER_FUNC_PRE_OPERAND:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_pre_operand       ); break;
    case ZYDIS_FORMATTER_FUNC_POST_OPERAND:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_post_operand      ); break;
    case ZYDIS_FORMATTER_FUNC_FORMAT_OPERAND_REG:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_format_operand_reg); break;
    case ZYDIS_FORMATTER_FUNC_FORMAT_OPERAND_MEM:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_format_operand_mem); break;
    case ZYDIS_FORMATTER_FUNC_FORMAT_OPERAND_PTR:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_format_operand_ptr); break;
    case ZYDIS_FORMATTER_FUNC_FORMAT_OPERAND_IMM:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_format_operand_imm); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_MNEMONIC:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_mnemonic    ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_REGISTER:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_register    ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_ADDRESS_ABS:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_address_abs ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_ADDRESS_REL:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_address_rel ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_DISP:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_disp        ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_IMM:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_imm         ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_SIZE:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_size        ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_SEGMENT:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_segment     ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_PREFIXES:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_prefixes    ); break;
    case ZYDIS_FORMATTER_FUNC_PRINT_DECORATOR:
        ZYAN_ASSERT(test == (ZyanUPointer*)&formatter->func_print_decorator   ); break;
    default:
        ZYAN_UNREACHABLE;
    }
#endif

    *callback = *(const void**)(&formatter->func_pre_instruction + type);
    if (!temp)
    {
        return ZYAN_STATUS_SUCCESS;
    }
    *(ZyanUPointer*)(&formatter->func_pre_instruction + type) = *(ZyanUPointer*)&temp;

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Formatting                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

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

    ZydisFormatterBuffer buf;
    buf.is_token_list              = ZYAN_FALSE;
    buf.string.flags               = ZYAN_STRING_HAS_FIXED_CAPACITY;
    buf.string.vector.allocator    = ZYAN_NULL;
    buf.string.vector.element_size = sizeof(char);
    buf.string.vector.size         = 1;
    buf.string.vector.capacity     = length;
    buf.string.vector.data         = buffer;
    *buffer = '\0';

    ZydisFormatterContext context;
    context.instruction            = instruction;
    context.runtime_address        = runtime_address;
    context.operand                = ZYAN_NULL;
    context.user_data              = user_data;

    if (formatter->func_pre_instruction)
    {
        ZYAN_CHECK(formatter->func_pre_instruction(formatter, &buf, &context));
    }

    ZYAN_CHECK(formatter->func_format_instruction(formatter, &buf, &context));

    if (formatter->func_post_instruction)
    {
        ZYAN_CHECK(formatter->func_post_instruction(formatter, &buf, &context));
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

    ZydisFormatterBuffer buf;
    buf.is_token_list              = ZYAN_FALSE;
    buf.string.flags               = ZYAN_STRING_HAS_FIXED_CAPACITY;
    buf.string.vector.allocator    = ZYAN_NULL;
    buf.string.vector.element_size = sizeof(char);
    buf.string.vector.size         = 1;
    buf.string.vector.capacity     = length;
    buf.string.vector.data         = buffer;
    *buffer = '\0';

    ZydisFormatterContext context;
    context.instruction            = instruction;
    context.runtime_address        = runtime_address;
    context.operand                = &instruction->operands[index];
    context.user_data              = user_data;

    // We ignore `ZYDIS_STATUS_SKIP_TOKEN` for all operand-functions as it does not make any sense
    // to skip the only operand printed by this function

    if (formatter->func_pre_operand)
    {
        ZYAN_CHECK(formatter->func_pre_operand(formatter, &buf, &context));
    }

    switch (context.operand->type)
    {
    case ZYDIS_OPERAND_TYPE_REGISTER:
        ZYAN_CHECK(formatter->func_format_operand_reg(formatter, &buf, &context));
        break;
    case ZYDIS_OPERAND_TYPE_MEMORY:
        ZYAN_CHECK(formatter->func_format_operand_mem(formatter, &buf, &context));
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        ZYAN_CHECK(formatter->func_format_operand_imm(formatter, &buf, &context));
        break;
    case ZYDIS_OPERAND_TYPE_POINTER:
        ZYAN_CHECK(formatter->func_format_operand_ptr(formatter, &buf, &context));
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (formatter->func_post_operand)
    {
        ZYAN_CHECK(formatter->func_post_operand(formatter, &buf, &context));
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Tokenizing                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterTokenizeInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, void* buffer, ZyanUSize length,
    ZyanU64 runtime_address, ZydisFormatterTokenConst** token)
{
    return ZydisFormatterTokenizeInstructionEx(formatter, instruction, buffer, length,
        runtime_address, token, ZYAN_NULL);
}

ZyanStatus ZydisFormatterTokenizeInstructionEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, void* buffer, ZyanUSize length,
    ZyanU64 runtime_address, ZydisFormatterTokenConst** token, void* user_data)
{
    if (!formatter || !instruction || !buffer || (length <= sizeof(ZydisFormatterToken)) || !token)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZydisFormatterToken* first = buffer;
    first->type = ZYDIS_TOKEN_INVALID;
    first->next = 0;

    buffer  = (ZyanU8*)buffer + sizeof(ZydisFormatterToken);
    length -= sizeof(ZydisFormatterToken);

    ZydisFormatterBuffer buf;
    buf.is_token_list              = ZYAN_TRUE;
    buf.capacity                   = length;
    buf.string.flags               = ZYAN_STRING_HAS_FIXED_CAPACITY;
    buf.string.vector.allocator    = ZYAN_NULL;
    buf.string.vector.element_size = sizeof(char);
    buf.string.vector.size         = 1;
    buf.string.vector.capacity     = length;
    buf.string.vector.data         = buffer;
    *(char*)buffer = '\0';

    ZydisFormatterContext context;
    context.instruction            = instruction;
    context.runtime_address        = runtime_address;
    context.operand                = ZYAN_NULL;
    context.user_data              = user_data;

    if (formatter->func_pre_instruction)
    {
        ZYAN_CHECK(formatter->func_pre_instruction(formatter, &buf, &context));
    }

    ZYAN_CHECK(formatter->func_format_instruction(formatter, &buf, &context));

    if (formatter->func_post_instruction)
    {
        ZYAN_CHECK(formatter->func_post_instruction(formatter, &buf, &context));
    }

    if (first->next)
    {
        *token = (ZydisFormatterTokenConst*)((ZyanU8*)buffer + 1);
        return ZYAN_STATUS_SUCCESS;
    }

    *token = first;
    return ZYAN_STATUS_SUCCESS;
}

/* ============================================================================================== */

/* ============================================================================================== */
