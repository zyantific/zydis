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
#include <Zydis/Internal/String.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* String constants                                                                               */
/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString STR_DELIM_MNEMONIC = ZYDIS_MAKE_SHORTSTRING(" ");
static const ZydisShortString STR_DELIM_OPERAND  = ZYDIS_MAKE_SHORTSTRING(", ");
static const ZydisShortString STR_DELIM_SGMENT   = ZYDIS_MAKE_SHORTSTRING(":");
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
static const ZydisShortString STR_PREF_XACQUIRE  = ZYDIS_MAKE_SHORTSTRING("xacquire ");
static const ZydisShortString STR_PREF_XRELEASE  = ZYDIS_MAKE_SHORTSTRING("xrelease ");
static const ZydisShortString STR_PREF_LOCK      = ZYDIS_MAKE_SHORTSTRING("lock ");
static const ZydisShortString STR_PREF_REP       = ZYDIS_MAKE_SHORTSTRING("rep ");
static const ZydisShortString STR_PREF_REPE      = ZYDIS_MAKE_SHORTSTRING("repe ");
static const ZydisShortString STR_PREF_REPNE     = ZYDIS_MAKE_SHORTSTRING("repne ");
static const ZydisShortString STR_PREF_BND       = ZYDIS_MAKE_SHORTSTRING("bnd ");
static const ZydisShortString STR_PREF_SEG_CS    = ZYDIS_MAKE_SHORTSTRING("cs ");
static const ZydisShortString STR_PREF_SEG_SS    = ZYDIS_MAKE_SHORTSTRING("ss ");
static const ZydisShortString STR_PREF_SEG_DS    = ZYDIS_MAKE_SHORTSTRING("ds ");
static const ZydisShortString STR_PREF_SEG_ES    = ZYDIS_MAKE_SHORTSTRING("es ");
static const ZydisShortString STR_PREF_SEG_FS    = ZYDIS_MAKE_SHORTSTRING("fs ");
static const ZydisShortString STR_PREF_SEG_GS    = ZYDIS_MAKE_SHORTSTRING("gs ");
static const ZydisShortString STR_DECO_BEGIN     = ZYDIS_MAKE_SHORTSTRING(" {");
static const ZydisShortString STR_DECO_END       = ZYDIS_MAKE_SHORTSTRING("}");
static const ZydisShortString STR_DECO_ZERO      = ZYDIS_MAKE_SHORTSTRING(" {z}");
static const ZydisShortString STR_DECO_1TO2      = ZYDIS_MAKE_SHORTSTRING(" {1to2}");
static const ZydisShortString STR_DECO_1TO4      = ZYDIS_MAKE_SHORTSTRING(" {1to4}");
static const ZydisShortString STR_DECO_1TO8      = ZYDIS_MAKE_SHORTSTRING(" {1to8}");
static const ZydisShortString STR_DECO_1TO16     = ZYDIS_MAKE_SHORTSTRING(" {1to16}");
static const ZydisShortString STR_DECO_4TO8      = ZYDIS_MAKE_SHORTSTRING(" {4to8}");
static const ZydisShortString STR_DECO_4TO16     = ZYDIS_MAKE_SHORTSTRING(" {4to16}");
static const ZydisShortString STR_DECO_RN_SAE    = ZYDIS_MAKE_SHORTSTRING(" {rn-sae}");
static const ZydisShortString STR_DECO_RD_SAE    = ZYDIS_MAKE_SHORTSTRING(" {rd-sae}");
static const ZydisShortString STR_DECO_RU_SAE    = ZYDIS_MAKE_SHORTSTRING(" {ru-sae}");
static const ZydisShortString STR_DECO_RZ_SAE    = ZYDIS_MAKE_SHORTSTRING(" {rz-sae}");
static const ZydisShortString STR_DECO_RN        = ZYDIS_MAKE_SHORTSTRING(" {rn}");
static const ZydisShortString STR_DECO_RD        = ZYDIS_MAKE_SHORTSTRING(" {rd}");
static const ZydisShortString STR_DECO_RU        = ZYDIS_MAKE_SHORTSTRING(" {ru}");
static const ZydisShortString STR_DECO_RZ        = ZYDIS_MAKE_SHORTSTRING(" {rz}");
static const ZydisShortString STR_DECO_SAE       = ZYDIS_MAKE_SHORTSTRING(" {sae}");
static const ZydisShortString STR_DECO_CDAB      = ZYDIS_MAKE_SHORTSTRING(" {cdab}");
static const ZydisShortString STR_DECO_BADC      = ZYDIS_MAKE_SHORTSTRING(" {badc}");
static const ZydisShortString STR_DECO_DACB      = ZYDIS_MAKE_SHORTSTRING(" {dacb}");
static const ZydisShortString STR_DECO_AAAA      = ZYDIS_MAKE_SHORTSTRING(" {aaaa}");
static const ZydisShortString STR_DECO_BBBB      = ZYDIS_MAKE_SHORTSTRING(" {bbbb}");
static const ZydisShortString STR_DECO_CCCC      = ZYDIS_MAKE_SHORTSTRING(" {cccc}");
static const ZydisShortString STR_DECO_DDDD      = ZYDIS_MAKE_SHORTSTRING(" {dddd}");
static const ZydisShortString STR_DECO_FLOAT16   = ZYDIS_MAKE_SHORTSTRING(" {float16}");
static const ZydisShortString STR_DECO_SINT8     = ZYDIS_MAKE_SHORTSTRING(" {sint8}");
static const ZydisShortString STR_DECO_UINT8     = ZYDIS_MAKE_SHORTSTRING(" {uint8}");
static const ZydisShortString STR_DECO_SINT16    = ZYDIS_MAKE_SHORTSTRING(" {sint16}");
static const ZydisShortString STR_DECO_UINT16    = ZYDIS_MAKE_SHORTSTRING(" {uint16}");
static const ZydisShortString STR_DECO_EH        = ZYDIS_MAKE_SHORTSTRING(" {eh}");

/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString STR_PREF_REX[0x10] =
{
    /* 40 */ ZYDIS_MAKE_SHORTSTRING("rex "),
    /* 41 */ ZYDIS_MAKE_SHORTSTRING("rex.b "),
    /* 42 */ ZYDIS_MAKE_SHORTSTRING("rex.x "),
    /* 43 */ ZYDIS_MAKE_SHORTSTRING("rex.xb "),
    /* 44 */ ZYDIS_MAKE_SHORTSTRING("rex.r "),
    /* 45 */ ZYDIS_MAKE_SHORTSTRING("rex.rb "),
    /* 46 */ ZYDIS_MAKE_SHORTSTRING("rex.rx "),
    /* 47 */ ZYDIS_MAKE_SHORTSTRING("rex.rxb "),
    /* 48 */ ZYDIS_MAKE_SHORTSTRING("rex.w "),
    /* 49 */ ZYDIS_MAKE_SHORTSTRING("rex.wb "),
    /* 4A */ ZYDIS_MAKE_SHORTSTRING("rex.wx "),
    /* 4B */ ZYDIS_MAKE_SHORTSTRING("rex.wxb "),
    /* 4C */ ZYDIS_MAKE_SHORTSTRING("rex.wr "),
    /* 4D */ ZYDIS_MAKE_SHORTSTRING("rex.wrb "),
    /* 4E */ ZYDIS_MAKE_SHORTSTRING("rex.wrx "),
    /* 4F */ ZYDIS_MAKE_SHORTSTRING("rex.wrxb ")
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Internal macros                                                                                */
/* ============================================================================================== */

/**
 * @brief   Appends an unsigned numeric value to the given string.
 *
 * @param   formatter       A pointer to the `ZydisFormatter` instance.
 * @param   str             The destination string.
 * @param   base            The numeric base.
 * @param   value           The value.
 * @param   padding_length  The padding length.
 */
#define ZYDIS_STRING_APPEND_NUM_U(formatter, base, str, value, padding_length) \
    switch (base) \
    { \
    case ZYDIS_NUMERIC_BASE_DEC: \
        ZYAN_CHECK(ZydisStringAppendDecU(str, value, padding_length, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    case ZYDIS_NUMERIC_BASE_HEX: \
        ZYAN_CHECK(ZydisStringAppendHexU(str, value, padding_length, \
            (formatter)->hex_uppercase, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    default: \
        return ZYAN_STATUS_INVALID_ARGUMENT; \
    }

/**
 * @brief   Appends a signed numeric value to the given string.
 *
 * @param   formatter       A pointer to the `ZydisFormatter` instance.
 * @param   str             The destination string.
 * @param   base            The numeric base.
 * @param   value           The value.
 * @param   padding_length  The padding length.
 * @param   force_sign      Forces printing of the '+' sign for positive numbers.
 */
#define ZYDIS_STRING_APPEND_NUM_S(formatter, base, str, value, padding_length, force_sign) \
    switch (base) \
    { \
    case ZYDIS_NUMERIC_BASE_DEC: \
        ZYAN_CHECK(ZydisStringAppendDecS(str, value, padding_length, force_sign, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    case ZYDIS_NUMERIC_BASE_HEX: \
        ZYAN_CHECK(ZydisStringAppendHexS(str, value, padding_length, force_sign, \
            (formatter)->hex_uppercase, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    default: \
        return ZYAN_STATUS_INVALID_ARGUMENT; \
    }

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatInstruction(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !string || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_CHECK(formatter->func_print_prefixes(formatter, string, context));
    ZYAN_CHECK(formatter->func_print_mnemonic(formatter, string, context));

    const ZyanUSize str_len_mnemonic = string->vector.size;
    for (ZyanU8 i = 0; i < context->instruction->operand_count; ++i)
    {
        if (context->instruction->operands[i].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        const ZyanUSize str_len_restore = string->vector.size;
        if (string->vector.size == str_len_mnemonic)
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_MNEMONIC));
        } else
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_OPERAND));
        }

        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) &&
            (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (context->instruction->operands[i].encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            string->vector.size = str_len_restore;
            ZYDIS_STRING_NULLTERMINATE(string);
            continue;
        }

        // Set current operand
        context->operand = &context->instruction->operands[i];

        ZyanStatus status;
        if (formatter->func_pre_operand)
        {
            status = formatter->func_pre_operand(formatter, string, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                string->vector.size = str_len_restore;
                ZYDIS_STRING_NULLTERMINATE(string);
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
            status = formatter->func_format_operand_reg(formatter, string, context);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            status = formatter->func_format_operand_mem(formatter, string, context);
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            status = formatter->func_format_operand_ptr(formatter, string, context);
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            status = formatter->func_format_operand_imm(formatter, string, context);
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        if (status == ZYDIS_STATUS_SKIP_TOKEN)
        {
            string->vector.size = str_len_restore;
            ZYDIS_STRING_NULLTERMINATE(string);
            continue;
        }
        if (!ZYAN_SUCCESS(status))
        {
            return status;
        }

        if (formatter->func_post_operand)
        {
            status = formatter->func_post_operand(formatter, string, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                string->vector.size = str_len_restore;
                ZYDIS_STRING_NULLTERMINATE(string);
                continue;
            }
            if (ZYAN_SUCCESS(status))
            {
                return status;
            }
        }

        if ((context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
            (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX))
        {
            if  ((i == 0) &&
                 (context->instruction->operands[i + 1].encoding == ZYDIS_OPERAND_ENCODING_MASK))
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                    ZYDIS_DECORATOR_MASK));
            }
            if (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                    ZYDIS_DECORATOR_BC));
                if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                {
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_CONVERSION));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_EH));
                }
            } else
            {
                if ((i == (context->instruction->operand_count - 1)) ||
                    (context->instruction->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
                {
                    if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                            ZYDIS_DECORATOR_SWIZZLE));
                    }
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_RC));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_SAE));
                }
            }
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelFormatInstructionMASM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // Force the formatter to always call our MASM `ZYDIS_FORMATTER_PRINT_ADDRESS_ABS` function.
    // This implicitly omits printing of the `RIP`/`EIP` registers for `RIP`/`EIP`-relative
    // memory operands
    context->runtime_address = 0;

    return ZydisFormatterIntelFormatInstruction(formatter, string, context);
}

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatOperandREG(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return formatter->func_print_register(formatter, string, context, context->operand->reg.value);
}

ZyanStatus ZydisFormatterIntelFormatOperandMEM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_CHECK(formatter->func_print_mem_size(formatter, string, context));
    ZYAN_CHECK(formatter->func_print_mem_seg (formatter, string, context));

    ZYAN_CHECK(ZydisStringAppendShort(string, &STR_MEMORY_BEGIN));

    if (context->operand->mem.disp.has_displacement &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE) &&
       ((context->operand->mem.base  == ZYDIS_REGISTER_NONE) ||
        (context->operand->mem.base  == ZYDIS_REGISTER_EIP ) ||
        (context->operand->mem.base  == ZYDIS_REGISTER_RIP )))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        const ZyanBool absolute = (context->runtime_address != ZYDIS_RUNTIME_ADDRESS_NONE);
        if (absolute)
        {
            ZYAN_CHECK(formatter->func_print_address_abs(formatter, string, context));
        } else
        {
            if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                    context->operand->mem.base));
            }
            ZYAN_CHECK(formatter->func_print_address_rel(formatter, string, context));
        }
    } else
    {
        // Regular memory operand
        if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->operand->mem.base));
        }
        if ((context->operand->mem.index != ZYDIS_REGISTER_NONE) &&
            (context->operand->mem.type  != ZYDIS_MEMOP_TYPE_MIB))
        {
            if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_ADD));
            }
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->operand->mem.index));
            if (context->operand->mem.scale)
            {
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_MUL));
                ZYAN_CHECK(ZydisStringAppendDecU(string, context->operand->mem.scale, 0,
                    ZYAN_NULL, ZYAN_NULL));
            }
        }
        if (context->operand->mem.disp.has_displacement && context->operand->mem.disp.value)
        {
            ZYAN_CHECK(formatter->func_print_disp(formatter, string, context));
        }
    }

    return ZydisStringAppendShort(string, &STR_MEMORY_END);
}

ZyanStatus ZydisFormatterIntelFormatOperandPTR(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, string,
        context->operand->ptr.segment, 4);
    ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_SGMENT));
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, string,
        context->operand->ptr.offset , 8);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelFormatOperandIMM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // The immediate operand contains an address
    if (context->operand->imm.is_relative)
    {
        const ZyanBool absolute = (context->runtime_address != ZYDIS_RUNTIME_ADDRESS_NONE);
        if (absolute)
        {
            return formatter->func_print_address_abs(formatter, string, context);
        }
        return formatter->func_print_address_rel(formatter, string, context);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->func_print_imm(formatter, string, context);
}

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelPrintMnemonic(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZydisShortString* mnemonic = ZydisMnemonicGetStringWrapped(
        context->instruction->mnemonic);
    if (!mnemonic)
    {
        return ZydisStringAppendShortCase(string, &STR_INVALID, formatter->letter_case);
    }
    ZYAN_CHECK(ZydisStringAppendShortCase(string, mnemonic, formatter->letter_case));

    if (context->instruction->attributes & ZYDIS_ATTRIB_IS_FAR_BRANCH)
    {
        return ZydisStringAppendShortCase(string, &STR_FAR, formatter->letter_case);
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintRegister(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context, ZydisRegister reg)
{
    ZYAN_UNUSED(context);

    if (!formatter)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZydisShortString* str = ZydisRegisterGetStringWrapped(reg);
    if (!str)
    {
        return ZydisStringAppendShortCase(string, &STR_INVALID, formatter->letter_case);
    }
    return ZydisStringAppendShortCase(string, str, formatter->letter_case);
}

ZyanStatus ZydisFormatterIntelPrintAddressAbsolute(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanU64 address;
    ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand,
        context->runtime_address, &address));
    ZyanU8 padding = (formatter->addr_padding_absolute ==
        ZYDIS_PADDING_AUTO) ? 0 : (ZyanU8)formatter->addr_padding_absolute;
    if ((formatter->addr_padding_absolute == ZYDIS_PADDING_AUTO) &&
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
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, string, address, padding);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintAddressRelative(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanU8 padding = (formatter->addr_padding_relative == ZYDIS_PADDING_AUTO) ?
        0 : (ZyanU8)formatter->addr_padding_relative;
    if ((formatter->addr_padding_relative == ZYDIS_PADDING_AUTO) &&
        (formatter->addr_base == ZYDIS_NUMERIC_BASE_HEX))
    {
        switch (context->instruction->stack_width)
        {
        case 16: padding =  4; break;
        case 32: padding =  8; break;
        case 64: padding = 16; break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
    }
    switch (context->operand->type)
    {
    case ZYDIS_OPERAND_TYPE_MEMORY:
        switch (formatter->addr_signedness)
        {
        case ZYDIS_SIGNEDNESS_AUTO:
        case ZYDIS_SIGNEDNESS_SIGNED:
            ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->addr_base, string,
                context->operand->mem.disp.value, padding, ZYAN_TRUE);
            break;
        case ZYDIS_SIGNEDNESS_UNSIGNED:
            ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, string,
                context->operand->mem.disp.value, padding);
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        return ZYAN_STATUS_SUCCESS;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
    {
        switch (formatter->addr_signedness)
        {
        case ZYDIS_SIGNEDNESS_AUTO:
        case ZYDIS_SIGNEDNESS_SIGNED:
            ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->addr_base, string,
                context->operand->imm.value.s, padding, ZYAN_TRUE);
            break;
        case ZYDIS_SIGNEDNESS_UNSIGNED:
            ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, string,
                context->operand->imm.value.u, padding);
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        return ZYAN_STATUS_SUCCESS;
    }
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
}

ZyanStatus ZydisFormatterIntelPrintAddressMASM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanU64 address;
    ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand, 0, &address));
    ZyanU8 padding = (formatter->addr_padding_absolute ==
        ZYDIS_PADDING_AUTO) ? 0 : (ZyanU8)formatter->addr_padding_absolute;
    if ((formatter->addr_padding_absolute == ZYDIS_PADDING_AUTO) &&
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
    ZYAN_CHECK(ZydisStringAppendShort(string, &STR_ADDR_RELATIVE));
    ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->addr_base, string, address, padding, ZYAN_TRUE);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintDISP(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (formatter->disp_signedness)
    {
    case ZYDIS_SIGNEDNESS_AUTO:
    case ZYDIS_SIGNEDNESS_SIGNED:
        ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->disp_base, string,
            context->operand->mem.disp.value, formatter->disp_padding, ZYAN_TRUE);
        break;
    case ZYDIS_SIGNEDNESS_UNSIGNED:
        ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->disp_base, string,
            context->operand->mem.disp.value, formatter->disp_padding);
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintIMM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZyanBool is_signed =
        (formatter->imm_signedness == ZYDIS_SIGNEDNESS_SIGNED) ||
        (formatter->imm_signedness == ZYDIS_SIGNEDNESS_AUTO && (context->operand->imm.is_signed));
    if (is_signed && (context->operand->imm.value.s < 0))
    {
        ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->imm_base, string,
            context->operand->imm.value.s, formatter->imm_padding, ZYAN_FALSE);
        return ZYAN_STATUS_SUCCESS;
    }
    ZyanU64 value;
    ZyanU8 padding = (formatter->imm_padding ==
        ZYDIS_PADDING_AUTO) ? 0 : (ZyanU8)formatter->imm_padding;
    switch (context->instruction->operand_width)
    {
    case 8:
        if (formatter->imm_padding == ZYDIS_PADDING_AUTO)
        {
            padding =  2;
        }
        value = (ZyanU8 )context->operand->imm.value.u;
        break;
    case 16:
        if (formatter->imm_padding == ZYDIS_PADDING_AUTO)
        {
            padding =  4;
        }
        value = (ZyanU16)context->operand->imm.value.u;
        break;
    case 32:
        if (formatter->imm_padding == ZYDIS_PADDING_AUTO)
        {
            padding =  8;
        }
        value = (ZyanU32)context->operand->imm.value.u;
        break;
    case 64:
        if (formatter->imm_padding == ZYDIS_PADDING_AUTO)
        {
            padding = 16;
        }
        value = (ZyanU64)context->operand->imm.value.u;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->imm_base, string, value, padding);

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Optional tokens                                                                                */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelPrintMemorySize(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // TODO: refactor

    ZyanU32 typecast = 0;
    if (formatter->force_memory_size)
    {
        if ((context->operand->type == ZYDIS_OPERAND_TYPE_MEMORY) &&
            (context->operand->mem.type == ZYDIS_MEMOP_TYPE_MEM))
        {
            typecast = context->instruction->operands[context->operand->id].size;
        }
    } else
    if ((context->operand->type == ZYDIS_OPERAND_TYPE_MEMORY) &&
        (context->operand->mem.type == ZYDIS_MEMOP_TYPE_MEM))
    {
        switch (context->operand->id)
        {
        case 0:
            typecast =
                ((context->instruction->operands[1].type == ZYDIS_OPERAND_TYPE_UNUSED) ||
                 (context->instruction->operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) ||
                 (context->instruction->operands[0].size !=
                    context->instruction->operands[1].size)) ?
                    context->instruction->operands[0].size : 0;
            if (!typecast &&
                (context->instruction->operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
                (context->instruction->operands[1].reg.value == ZYDIS_REGISTER_CL))
            {
                switch (context->instruction->mnemonic)
                {
                case ZYDIS_MNEMONIC_RCL:
                case ZYDIS_MNEMONIC_ROL:
                case ZYDIS_MNEMONIC_ROR:
                case ZYDIS_MNEMONIC_RCR:
                case ZYDIS_MNEMONIC_SHL:
                case ZYDIS_MNEMONIC_SHR:
                case ZYDIS_MNEMONIC_SAR:
                    typecast = context->instruction->operands[0].size;
                default:
                    break;
                }
            }
            break;
        case 1:
        case 2:
            typecast =
                (context->instruction->operands[context->operand->id - 1].size !=
                    context->instruction->operands[context->operand->id].size) ?
                    context->instruction->operands[context->operand->id].size : 0;
            break;
        default:
            break;
        }
    }
    if (typecast)
    {
        const ZydisShortString* str = ZYAN_NULL;
        switch (typecast)
        {
        case 8:
            str = &STR_SIZE_8;
            break;
        case 16:
            str = &STR_SIZE_16;
            break;
        case 32:
            str = &STR_SIZE_32;
            break;
        case 48:
            str = &STR_SIZE_48;
            break;
        case 64:
            str = &STR_SIZE_64;
            break;
        case 80:
            str = &STR_SIZE_80;
            break;
        case 128:
            str = &STR_SIZE_128;
            break;
        case 256:
            str = &STR_SIZE_256;
            break;
        case 512:
            str = &STR_SIZE_512;
            break;
        default:
            break;
        }

        if (str)
        {
            return ZydisStringAppendShortCase(string, str, formatter->letter_case);
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintMemorySegment(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanBool printed_segment = ZYAN_FALSE;
    switch (context->operand->mem.segment)
    {
    case ZYDIS_REGISTER_ES:
    case ZYDIS_REGISTER_CS:
    case ZYDIS_REGISTER_FS:
    case ZYDIS_REGISTER_GS:
        ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
            context->operand->mem.segment));
        printed_segment = ZYAN_TRUE;
        break;
    case ZYDIS_REGISTER_SS:
        if ((formatter->force_memory_segment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->operand->mem.segment));
            printed_segment = ZYAN_TRUE;
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->force_memory_segment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->operand->mem.segment));
            printed_segment = ZYAN_TRUE;
        }
        break;
    default:
        break;
    }
    if (printed_segment)
    {
        ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_SGMENT));
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintPrefixes(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (formatter->detailed_prefixes)
    {
        for (ZyanU8 i = 0; i < context->instruction->raw.prefix_count; ++i)
        {
            const ZyanU8 value = context->instruction->raw.prefixes[i].value;
            switch (context->instruction->raw.prefixes[i].type)
            {
            case ZYDIS_PREFIX_TYPE_IGNORED:
            case ZYDIS_PREFIX_TYPE_MANDATORY:
            {
                if ((value & 0xF0) == 0x40)
                {
                    ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_REX[value & 0x0F],
                        formatter->letter_case));
                } else
                {
                    switch (value)
                    {
                    case 0xF0:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_LOCK,
                            formatter->letter_case));
                        break;
                    case 0x2E:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_SEG_CS,
                            formatter->letter_case));
                        break;
                    case 0x36:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_SEG_SS,
                            formatter->letter_case));
                        break;
                    case 0x3E:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_SEG_DS,
                            formatter->letter_case));
                        break;
                    case 0x26:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_SEG_ES,
                            formatter->letter_case));
                        break;
                    case 0x64:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_SEG_FS,
                            formatter->letter_case));
                        break;
                    case 0x65:
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_SEG_GS,
                            formatter->letter_case));
                        break;
                    default:
                        ZYAN_CHECK(ZydisStringAppendHexU(string, value, 0,
                            formatter->hex_uppercase, ZYAN_NULL, ZYAN_NULL));
                        ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_MNEMONIC));
                        break;
                    }
                }
                break;
            }
            case ZYDIS_PREFIX_TYPE_EFFECTIVE:
                switch (value)
                {
                case 0xF0:
                    ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_LOCK,
                        formatter->letter_case));
                    break;
                case 0xF2:
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
                    {
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_XACQUIRE,
                            formatter->letter_case));
                    }
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
                    {
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_REPNE,
                            formatter->letter_case));
                    }

                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_BND)
                    {
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_BND,
                            formatter->letter_case));
                    }
                    break;
                case 0xF3:
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
                    {
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_XRELEASE,
                            formatter->letter_case));
                    }
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
                    {
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_REP,
                            formatter->letter_case));
                    }
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
                    {
                        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_REPE,
                            formatter->letter_case));
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        }
        return ZYAN_STATUS_SUCCESS;
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
    {
        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_XACQUIRE, formatter->letter_case));
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        ZYAN_CHECK(ZydisStringAppendShortCase(string, &STR_PREF_XRELEASE, formatter->letter_case));
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        return ZydisStringAppendShortCase(string, &STR_PREF_LOCK, formatter->letter_case);
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        return ZydisStringAppendShortCase(string, &STR_PREF_REP, formatter->letter_case);
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        return ZydisStringAppendShortCase(string, &STR_PREF_REPE, formatter->letter_case);
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        return ZydisStringAppendShortCase(string, &STR_PREF_REPNE, formatter->letter_case);
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_BND)
    {
        return ZydisStringAppendShortCase(string, &STR_PREF_BND, formatter->letter_case);
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterIntelPrintDecorator(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context, ZydisDecorator decorator)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (decorator)
    {
    case ZYDIS_DECORATOR_MASK:
    {
#if !defined(ZYDIS_DISABLE_AVX512) || !defined(ZYDIS_DISABLE_KNC)
        if (context->instruction->avx.mask.reg != ZYDIS_REGISTER_K0)
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_BEGIN));
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->instruction->avx.mask.reg));
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_END));

            // Only print the zeroing decorator, if the instruction is not a "zeroing masking only"
            // instruction (e.g. `vcmpsd`)
            if ((context->instruction->avx.mask.mode == ZYDIS_MASK_MODE_ZEROING) &&
                (context->instruction->raw.evex.z))
            {
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_ZERO));
            }
        }
#endif
        break;
    }
    case ZYDIS_DECORATOR_BC:
#if !defined(ZYDIS_DISABLE_AVX512)
        if (!context->instruction->avx.broadcast.is_static)
        {
            switch (context->instruction->avx.broadcast.mode)
            {
            case ZYDIS_BROADCAST_MODE_INVALID:
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_2:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_1TO2));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_4:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_1TO4));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_8:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_1TO8));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_16:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_1TO16));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_8:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_4TO8));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_16:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_4TO16));
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        }
#endif
        break;
    case ZYDIS_DECORATOR_RC:
#if !defined(ZYDIS_DISABLE_AVX512)
        if (context->instruction->avx.has_SAE)
        {
            switch (context->instruction->avx.rounding.mode)
            {
            case ZYDIS_ROUNDING_MODE_INVALID:
                break;
            case ZYDIS_ROUNDING_MODE_RN:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RN_SAE));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RD_SAE));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RU_SAE));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RZ_SAE));
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        } else
        {
            switch (context->instruction->avx.rounding.mode)
            {
            case ZYDIS_ROUNDING_MODE_INVALID:
                break;
            case ZYDIS_ROUNDING_MODE_RN:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RN));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RD));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RU));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_RZ));
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        }
#endif
        break;
    case ZYDIS_DECORATOR_SAE:
#if !defined(ZYDIS_DISABLE_AVX512)
        if (context->instruction->avx.has_SAE && !context->instruction->avx.rounding.mode)
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_SAE));
        }
#endif
        break;
    case ZYDIS_DECORATOR_SWIZZLE:
#if !defined(ZYDIS_DISABLE_KNC)
        switch (context->instruction->avx.swizzle.mode)
        {
        case ZYDIS_SWIZZLE_MODE_INVALID:
        case ZYDIS_SWIZZLE_MODE_DCBA:
            // Nothing to do here
            break;
        case ZYDIS_SWIZZLE_MODE_CDAB:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_CDAB));
            break;
        case ZYDIS_SWIZZLE_MODE_BADC:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_BADC));
            break;
        case ZYDIS_SWIZZLE_MODE_DACB:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_DACB));
            break;
        case ZYDIS_SWIZZLE_MODE_AAAA:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_AAAA));
            break;
        case ZYDIS_SWIZZLE_MODE_BBBB:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_BBBB));
            break;
        case ZYDIS_SWIZZLE_MODE_CCCC:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_CCCC));
            break;
        case ZYDIS_SWIZZLE_MODE_DDDD:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_DDDD));
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
#endif
        break;
    case ZYDIS_DECORATOR_CONVERSION:
#if !defined(ZYDIS_DISABLE_KNC)
        switch (context->instruction->avx.conversion.mode)
        {
        case ZYDIS_CONVERSION_MODE_INVALID:
            break;
        case ZYDIS_CONVERSION_MODE_FLOAT16:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_FLOAT16));
            break;
        case ZYDIS_CONVERSION_MODE_SINT8:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_SINT8));
            break;
        case ZYDIS_CONVERSION_MODE_UINT8:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_UINT8));
            break;
        case ZYDIS_CONVERSION_MODE_SINT16:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_SINT16));
            break;
        case ZYDIS_CONVERSION_MODE_UINT16:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_UINT16));
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
#endif
        break;
    case ZYDIS_DECORATOR_EH:
#if !defined(ZYDIS_DISABLE_KNC)
        if (context->instruction->avx.has_eviction_hint)
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_EH));
        }
#endif
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
