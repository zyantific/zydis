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

#include <Zydis/Internal/FormatterIntel.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* String constants                                                                               */
/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString STR_WHITESPACE     = ZYDIS_MAKE_SHORTSTRING(" ");
static const ZydisShortString STR_DELIMITER      = ZYDIS_MAKE_SHORTSTRING(",");
static const ZydisShortString STR_MEMORY_BEGIN   = ZYDIS_MAKE_SHORTSTRING("[");
static const ZydisShortString STR_MEMORY_END     = ZYDIS_MAKE_SHORTSTRING("]");
static const ZydisShortString STR_ADDR_RELATIVE  = ZYDIS_MAKE_SHORTSTRING("$");
static const ZydisShortString STR_ADD            = ZYDIS_MAKE_SHORTSTRING("+");
static const ZydisShortString STR_MUL            = ZYDIS_MAKE_SHORTSTRING("*");
static const ZydisShortString STR_INVALID        = ZYDIS_MAKE_SHORTSTRING("invalid");
static const ZydisShortString STR_FAR            = ZYDIS_MAKE_SHORTSTRING(" far");
static const ZydisShortString STR_SIZE_8         = ZYDIS_MAKE_SHORTSTRING("byte ptr ");
static const ZydisShortString STR_SIZE_16        = ZYDIS_MAKE_SHORTSTRING("word ptr ");
static const ZydisShortString STR_SIZE_32        = ZYDIS_MAKE_SHORTSTRING("dword ptr ");
static const ZydisShortString STR_SIZE_48        = ZYDIS_MAKE_SHORTSTRING("fword ptr ");
static const ZydisShortString STR_SIZE_64        = ZYDIS_MAKE_SHORTSTRING("qword ptr ");
static const ZydisShortString STR_SIZE_80        = ZYDIS_MAKE_SHORTSTRING("tbyte ptr ");
static const ZydisShortString STR_SIZE_128       = ZYDIS_MAKE_SHORTSTRING("xmmword ptr ");
static const ZydisShortString STR_SIZE_256       = ZYDIS_MAKE_SHORTSTRING("ymmword ptr ");
static const ZydisShortString STR_SIZE_512       = ZYDIS_MAKE_SHORTSTRING("zmmword ptr ");

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Intel                                                                                          */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatInstruction(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYAN_CHECK(formatter->func_print_prefixes(formatter, buffer, context));
    ZYAN_CHECK(formatter->func_print_mnemonic(formatter, buffer, context));

    ZyanUPointer state_mnemonic;
    ZYDIS_BUFFER_REMEMBER(buffer, state_mnemonic);
    for (ZyanU8 i = 0; i < context->instruction->operand_count; ++i)
    {
        const ZydisDecodedOperand* const operand = &context->instruction->operands[i];

        if (operand->visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) &&
            (context->operand->type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (context->operand->encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            continue;
        }

        ZyanUPointer buffer_state;
        ZYDIS_BUFFER_REMEMBER(buffer, buffer_state);

        if (buffer_state != state_mnemonic)
        {
            ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
            ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIMITER));
        }
        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_WHITESPACE);
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_WHITESPACE));

        // Set current operand
        context->operand = operand;

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

        switch (operand->type)
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
            if (operand->type == ZYDIS_OPERAND_TYPE_MEMORY)
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

ZyanStatus ZydisFormatterIntelFormatOperandMEM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    if (context->operand->mem.type == ZYDIS_MEMOP_TYPE_MEM)
    {
        ZYAN_CHECK(formatter->func_print_size(formatter, buffer, context));
    }
    ZYAN_CHECK(formatter->func_print_segment(formatter, buffer, context));

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PARENTHESIS_OPEN);
    ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_MEMORY_BEGIN));

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
        if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.base));
        }
        if ((context->operand->mem.index != ZYDIS_REGISTER_NONE) &&
            (context->operand->mem.type  != ZYDIS_MEMOP_TYPE_MIB))
        {
            if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_ADD));
            }
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.index));
            if (context->operand->mem.scale)
            {
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_MUL));
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
                ZYAN_CHECK(ZydisStringAppendDecU(&buffer->string, context->operand->mem.scale, 0,
                    ZYAN_NULL, ZYAN_NULL));
            }
        }
        if (context->operand->mem.disp.has_displacement && context->operand->mem.disp.value)
        {
            ZYAN_CHECK(formatter->func_print_disp(formatter, buffer, context));
        }
    }

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PARENTHESIS_CLOSE);
    return ZydisStringAppendShort(&buffer->string, &STR_MEMORY_END);
}

ZyanStatus ZydisFormatterIntelPrintMnemonic(const ZydisFormatter* formatter,
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
    ZYAN_CHECK(ZydisStringAppendShortCase(&buffer->string, mnemonic, formatter->letter_case));

    if (context->instruction->attributes & ZYDIS_ATTRIB_IS_FAR_BRANCH)
    {
        return ZydisStringAppendShortCase(&buffer->string, &STR_FAR, formatter->letter_case);
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintRegister(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context, ZydisRegister reg)
{
    ZYAN_UNUSED(context);

    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_REGISTER);

    const ZydisShortString* str = ZydisRegisterGetStringWrapped(reg);
    if (!str)
    {
        return ZydisStringAppendShortCase(&buffer->string, &STR_INVALID, formatter->letter_case);
    }
    return ZydisStringAppendShortCase(&buffer->string, str, formatter->letter_case);
}

ZyanStatus ZydisFormatterIntelPrintDISP(const ZydisFormatter* formatter,
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
            context->operand->mem.disp.value, formatter->disp_padding, ZYAN_TRUE);
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

ZyanStatus ZydisFormatterIntelPrintSize(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    const ZydisShortString* size_string = ZYAN_NULL;
    switch (ZydisFormatterHelperGetExplicitSize(formatter, context, context->operand->id))
    {
    case   8: size_string = &STR_SIZE_8  ; break;
    case  16: size_string = &STR_SIZE_16 ; break;
    case  32: size_string = &STR_SIZE_32 ; break;
    case  48: size_string = &STR_SIZE_48 ; break;
    case  64: size_string = &STR_SIZE_64 ; break;
    case  80: size_string = &STR_SIZE_80 ; break;
    case 128: size_string = &STR_SIZE_128; break;
    case 256: size_string = &STR_SIZE_256; break;
    case 512: size_string = &STR_SIZE_512; break;
    default:
        break;
    }
    if (size_string)
    {
        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_TYPECAST);
        return ZydisStringAppendShortCase(&buffer->string, size_string, formatter->letter_case);
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* MASM                                                                                           */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatInstructionMASM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    // Force the formatter to always call our MASM `ZYDIS_FORMATTER_PRINT_ADDRESS_ABS` function.
    // This implicitly omits printing of the `RIP`/`EIP` registers for `RIP`/`EIP`-relative
    // memory operands
    context->runtime_address = 0;

    return ZydisFormatterIntelFormatInstruction(formatter, buffer, context);
}

ZyanStatus ZydisFormatterIntelPrintAddressMASM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZyanU64 address;
    ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand, 0, &address));

    ZyanU8 padding = (formatter->addr_padding_relative ==
        ZYDIS_PADDING_AUTO) ? 0 : (ZyanU8)formatter->addr_padding_relative;
    if ((formatter->addr_padding_relative == ZYDIS_PADDING_AUTO) &&
        (formatter->addr_base == ZYDIS_NUMERIC_BASE_HEX))
    {
        switch (context->instruction->stack_width)
        {
        case 16:
            padding =  4;
            address = (ZyanU16)address;
            break;
        case 32:
            padding =  8;
            address = (ZyanU32)address;
            break;
        case 64:
            padding = 16;
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
    }

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_ADDRESS_REL);
    ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_ADDR_RELATIVE));
    ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->addr_base, &buffer->string, address, padding,
        ZYAN_TRUE);

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
