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

#include <Zydis/Internal/FormatterATT.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* String constants                                                                               */
/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString STR_DELIM_MNEMONIC = ZYDIS_MAKE_SHORTSTRING(" ");
static const ZydisShortString STR_DELIM_OPERAND  = ZYDIS_MAKE_SHORTSTRING(", ");
static const ZydisShortString STR_DELIM_MEMORY   = ZYDIS_MAKE_SHORTSTRING(",");
static const ZydisShortString STR_MEMORY_BEGIN   = ZYDIS_MAKE_SHORTSTRING("(");
static const ZydisShortString STR_MEMORY_END     = ZYDIS_MAKE_SHORTSTRING(")");
static const ZydisShortString STR_INVALID        = ZYDIS_MAKE_SHORTSTRING("invalid");
static const ZydisShortString STR_FAR            = ZYDIS_MAKE_SHORTSTRING("l");
static const ZydisShortString STR_SIZE_8         = ZYDIS_MAKE_SHORTSTRING("b");
static const ZydisShortString STR_SIZE_16        = ZYDIS_MAKE_SHORTSTRING("w");
static const ZydisShortString STR_SIZE_32        = ZYDIS_MAKE_SHORTSTRING("l");
static const ZydisShortString STR_SIZE_64        = ZYDIS_MAKE_SHORTSTRING("q");
static const ZydisShortString STR_SIZE_128       = ZYDIS_MAKE_SHORTSTRING("x");
static const ZydisShortString STR_SIZE_256       = ZYDIS_MAKE_SHORTSTRING("y");
static const ZydisShortString STR_SIZE_512       = ZYDIS_MAKE_SHORTSTRING("z");
static const ZydisShortString STR_REGISTER       = ZYDIS_MAKE_SHORTSTRING("%");
static const ZydisShortString STR_IMMEDIATE      = ZYDIS_MAKE_SHORTSTRING("$");

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTFormatInstruction(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYAN_CHECK(formatter->func_print_prefixes(formatter, buffer, context));
    ZYAN_CHECK(formatter->func_print_mnemonic(formatter, buffer, context));
    ZYAN_CHECK(formatter->func_print_size(formatter, buffer, context));

    ZyanUPointer state_mnemonic;
    ZYDIS_BUFFER_REMEMBER(buffer, state_mnemonic);
    ZyanI8 c = (ZyanI8)context->instruction->operand_count - 1;
    for (; c >= 0; --c)
    {
        if (context->instruction->operands[c].visibility != ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }
    }

    for (ZyanI8 i = c; i >= 0; --i)
    {
        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) &&
            (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (context->instruction->operands[i].encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            continue;
        }

        ZyanUPointer buffer_state;
        ZYDIS_BUFFER_REMEMBER(buffer, buffer_state);
        if (buffer_state == state_mnemonic)
        {
            ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_WHITESPACE);
            ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIM_MNEMONIC));
        } else
        {
            ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
            ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIM_OPERAND));
        }

        // Set current operand
        context->operand = &context->instruction->operands[i];

        ZyanStatus status;
        if (formatter->func_pre_operand)
        {
            status = formatter->func_pre_operand(formatter, buffer, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, buffer_state));
                continue;
            }
            if (!ZYAN_SUCCESS(status))
            {
                return status;
            }
        }

        switch (context->instruction->operands[i].type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            status = formatter->func_format_operand_reg(formatter, buffer, context);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            status = formatter->func_format_operand_mem(formatter, buffer, context);
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            status = formatter->func_format_operand_ptr(formatter, buffer, context);
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            status = formatter->func_format_operand_imm(formatter, buffer, context);
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        if (status == ZYDIS_STATUS_SKIP_TOKEN)
        {
            ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, buffer_state));
            continue;
        }
        if (!ZYAN_SUCCESS(status))
        {
            return status;
        }

        if (formatter->func_post_operand)
        {
            status = formatter->func_post_operand(formatter, buffer, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                ZYAN_CHECK(ZydisFormatterBufferRestore(buffer, buffer_state));
                continue;
            }
            if (ZYAN_SUCCESS(status))
            {
                return status;
            }
        }

#if !defined(ZYDIS_DISABLE_AVX512) || !defined(ZYDIS_DISABLE_KNC)
        if ((context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
            (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX))
        {
            if  ((i == 0) &&
                 (context->instruction->operands[i + 1].encoding == ZYDIS_OPERAND_ENCODING_MASK))
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                    ZYDIS_DECORATOR_MASK));
            }
            if (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                    ZYDIS_DECORATOR_BC));
                if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                {
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_CONVERSION));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_EH));
                }
            } else
            {
                if ((i == (context->instruction->operand_count - 1)) ||
                    (context->instruction->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
                {
                    if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                            ZYDIS_DECORATOR_SWIZZLE));
                    }
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_RC));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, buffer, context,
                        ZYDIS_DECORATOR_SAE));
                }
            }
        }
#endif
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTFormatOperandMEM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYAN_CHECK(formatter->func_print_segment(formatter, buffer, context));

    const ZyanBool absolute = (context->runtime_address != ZYDIS_RUNTIME_ADDRESS_NONE);
    if (absolute && context->operand->mem.disp.has_displacement &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE) &&
       ((context->operand->mem.base  == ZYDIS_REGISTER_NONE) ||
        (context->operand->mem.base  == ZYDIS_REGISTER_EIP ) ||
        (context->operand->mem.base  == ZYDIS_REGISTER_RIP )))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        ZYAN_CHECK(formatter->func_print_address_abs(formatter, buffer, context));
    } else
    {
        // Regular memory operand
        if (context->operand->mem.disp.has_displacement && context->operand->mem.disp.value)
        {
            ZYAN_CHECK(formatter->func_print_disp(formatter, buffer, context));
        }

        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PARENTHESIS_OPEN);
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_MEMORY_BEGIN));

        if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.base));
        }
        if ((context->operand->mem.index != ZYDIS_REGISTER_NONE) &&
            (context->operand->mem.type  != ZYDIS_MEMOP_TYPE_MIB))
        {
            ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
            ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIM_MEMORY));
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.index));
            if (context->operand->mem.scale)
            {
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIM_MEMORY));
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
                ZYAN_CHECK(ZydisStringAppendDecU(&buffer->string, context->operand->mem.scale, 0,
                    ZYAN_NULL, ZYAN_NULL));
            }
        }

        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PARENTHESIS_CLOSE);
        return ZydisStringAppendShort(&buffer->string, &STR_MEMORY_END);
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTPrintMnemonic(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_MNEMONIC);

    const ZydisShortString* mnemonic = ZydisMnemonicGetStringWrapped(
        context->instruction->mnemonic);
    if (!mnemonic)
    {
        return ZydisStringAppendShortCase(&buffer->string, &STR_INVALID, formatter->letter_case);
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_IS_FAR_BRANCH)
    {
        ZYAN_CHECK(ZydisStringAppendShortCase(&buffer->string, &STR_FAR, formatter->letter_case));
    }
    return ZydisStringAppendShortCase(&buffer->string, mnemonic, formatter->letter_case);
}

ZyanStatus ZydisFormatterATTPrintRegister(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context, ZydisRegister reg)
{
    ZYAN_UNUSED(context);

    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_REGISTER);
    ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_REGISTER));
    const ZydisShortString* str = ZydisRegisterGetStringWrapped(reg);
    if (!str)
    {
        return ZydisStringAppendShortCase(&buffer->string, &STR_INVALID, formatter->letter_case);
    }
    return ZydisStringAppendShortCase(&buffer->string, str, formatter->letter_case);
}

ZyanStatus ZydisFormatterATTPrintDISP(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DISPLACEMENT);
    switch (formatter->disp_signedness)
    {
    case ZYDIS_SIGNEDNESS_AUTO:
    case ZYDIS_SIGNEDNESS_SIGNED:
        ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->disp_base, &buffer->string,
            context->operand->mem.disp.value, formatter->disp_padding, ZYAN_FALSE);
        break;
    case ZYDIS_SIGNEDNESS_UNSIGNED:
        ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->disp_base, &buffer->string,
            context->operand->mem.disp.value, formatter->disp_padding);
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintIMM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
    ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_IMMEDIATE));
    return ZydisFormatterSharedPrintIMM(formatter, buffer, context);
}

/* ---------------------------------------------------------------------------------------------- */
/* Optional tokens                                                                                */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTPrintSize(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZyanU32 size = 0;
    for (ZyanU8 i = 0; i < context->instruction->operand_count; ++i)
    {
        const ZydisDecodedOperand* const operand = &context->instruction->operands[i];
        if (operand->visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }
        if ((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) &&
            (operand->mem.type == ZYDIS_MEMOP_TYPE_MEM))
        {
            size = ZydisFormatterHelperGetExplicitSize(formatter, context, i);
            break;
        }
    }

    const ZydisShortString* size_string = ZYAN_NULL;
    switch (size)
    {
    case   8: size_string = &STR_SIZE_8  ; break;
    case  16: size_string = &STR_SIZE_16 ; break;
    case  32: size_string = &STR_SIZE_32 ; break;
    case  64: size_string = &STR_SIZE_64 ; break;
    case 128: size_string = &STR_SIZE_128; break;
    case 256: size_string = &STR_SIZE_256; break;
    case 512: size_string = &STR_SIZE_512; break;
    default:
        break;
    }
    if (size_string)
    {
        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_MNEMONIC);
        return ZydisStringAppendShortCase(&buffer->string, size_string, formatter->letter_case);
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
