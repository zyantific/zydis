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

#include <Zycore/Types.h>
#include <Zydis/Formatter.h>
#include <Zydis/Utils.h>
#include <Zydis/Internal/String.h>

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
static const ZydisShortString STR_SUB            = ZYDIS_MAKE_SHORTSTRING("-");
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

static const ZyanString STR_PREFIX_HEX           = ZYAN_STRING_WRAP("0x");
static const ZyanString STR_SUFFIX_HEX           = ZYAN_STRING_WRAP("h");

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Internal functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* General                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisFormatInstruction(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (formatter->func_pre_instruction)
    {
        ZYAN_CHECK(formatter->func_pre_instruction(formatter, string, context));
    }

    ZYAN_CHECK(formatter->func_format_instruction(formatter, string, context));

    if (formatter->func_post_instruction)
    {
        return formatter->func_post_instruction(formatter, string, context);
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Intel style                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisFormatInstrIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !string || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_CHECK(formatter->func_print_prefixes(formatter, string, context));
    ZYAN_CHECK(formatter->func_print_mnemonic(formatter, string, context));

    const ZyanUSize str_len_mnemonic = string->data.size;
    for (ZyanU8 i = 0; i < context->instruction->operand_count; ++i)
    {
        if (context->instruction->operands[i].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        const ZyanUSize str_len_restore = string->data.size;
        if (string->data.size == str_len_mnemonic)
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_MNEMONIC));
        } else
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_OPERAND));
        }

        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) && (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (context->instruction->operands[i].encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            string->data.size = str_len_restore;
            *((char*)string->data.data + string->data.size - 1) = '\0';
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
                string->data.size = str_len_restore;
                *((char*)string->data.data + string->data.size - 1) = '\0';
                continue;
            }
            if (status != ZYAN_STATUS_SUCCESS)
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
            string->data.size = str_len_restore;
            *((char*)string->data.data + string->data.size - 1) = '\0';
            continue;
        }
        if (status != ZYAN_STATUS_SUCCESS)
        {
            return status;
        }

        if (formatter->func_post_operand)
        {
            status = formatter->func_post_operand(formatter, string, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                string->data.size = str_len_restore;
                *((char*)string->data.data + string->data.size - 1) = '\0';
                continue;
            }
            if (status != ZYAN_STATUS_SUCCESS)
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
                    ZYDIS_DECORATOR_TYPE_MASK));
            }
            if (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                    ZYDIS_DECORATOR_TYPE_BC));
                if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                {
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_CONVERSION));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_EH));
                }
            } else
            {
                if ((i == (context->instruction->operand_count - 1)) ||
                    (context->instruction->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
                {
                    if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                            ZYDIS_DECORATOR_TYPE_SWIZZLE));
                    }
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_RC));
                    ZYAN_CHECK(formatter->func_print_decorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_SAE));
                }
            }
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

static ZyanStatus ZydisFormatOperandRegIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return formatter->func_print_register(formatter, string, context, context->operand->reg.value);
}

static ZyanStatus ZydisFormatOperandMemIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZyanStatus status = formatter->func_print_mem_size(formatter, string, context);
    if ((status != ZYAN_STATUS_SUCCESS) && (status != ZYDIS_STATUS_SKIP_TOKEN))
    {
        return status;
    }

    switch (context->operand->mem.segment)
    {
    case ZYDIS_REGISTER_ES:
    case ZYDIS_REGISTER_CS:
    case ZYDIS_REGISTER_FS:
    case ZYDIS_REGISTER_GS:
        ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
            context->operand->mem.segment));
        break;
    case ZYDIS_REGISTER_SS:
        if ((formatter->force_memory_segment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->operand->mem.segment));
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->force_memory_segment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                context->operand->mem.segment));
        }
        break;
    default:
        break;
    }
    if (ZYAN_SUCCESS(status))
    {
        ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_SGMENT));
    }

    ZYAN_CHECK(ZydisStringAppendShort(string, &STR_MEMORY_BEGIN));

    if (context->operand->mem.disp.has_displacement && (
        (context->operand->mem.base == ZYDIS_REGISTER_NONE) ||
        (context->operand->mem.base == ZYDIS_REGISTER_EIP) ||
        (context->operand->mem.base == ZYDIS_REGISTER_RIP)) &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE) && (context->operand->mem.scale == 0))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        if ((formatter->format_address == ZYDIS_ADDR_FORMAT_ABSOLUTE) ||
            (context->operand->mem.base == ZYDIS_REGISTER_NONE))
        {
            ZyanU64 address;
            ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand,
                context->address, &address));
            ZYAN_CHECK(formatter->func_print_address(formatter, string, context, address));
        } else
        {
            if (formatter->format_address == ZYDIS_ADDR_FORMAT_RELATIVE_ASSEMBLER)
            {
                ZYAN_CHECK(ZydisStringAppendShort(string, &STR_ADDR_RELATIVE));
                ZYAN_CHECK(ZydisStringAppendHexS(string,
                    context->operand->mem.disp.value + context->instruction->length,
                    formatter->hex_padding_address, formatter->hex_uppercase, ZYAN_TRUE,
                    formatter->hex_prefix, formatter->hex_suffix));
            } else
            {
                ZYAN_CHECK(formatter->func_print_register(formatter, string, context,
                    context->operand->mem.base));
                ZYAN_CHECK(formatter->func_print_disp(formatter, string, context));
            }
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
            (context->operand->mem.type != ZYDIS_MEMOP_TYPE_MIB))
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
                ZYAN_CHECK(ZydisStringAppendDecU(string, context->operand->mem.scale, 0, ZYAN_NULL,
                    ZYAN_NULL));
            }
        }
        ZYAN_CHECK(formatter->func_print_disp(formatter, string, context));
    }

    return ZydisStringAppendShort(string, &STR_MEMORY_END);
}

static ZyanStatus ZydisFormatOperandPtrIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_CHECK(ZydisStringAppendHexU(string, context->operand->ptr.segment, 4,
        formatter->hex_uppercase, formatter->hex_prefix, formatter->hex_suffix));
    ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DELIM_SGMENT));
    return ZydisStringAppendHexU(string, context->operand->ptr.offset, 8,
        formatter->hex_uppercase, formatter->hex_prefix, formatter->hex_suffix);
}

static ZyanStatus ZydisFormatOperandImmIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // The immediate operand contains an address
    if (context->operand->imm.is_relative)
    {
        switch (formatter->format_address)
        {
        case ZYDIS_ADDR_FORMAT_ABSOLUTE:
        {
            ZyanU64 address;
            ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand,
                context->address, &address));
            return formatter->func_print_address(formatter, string, context, address);
        }
        case ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED:
            return ZydisStringAppendHexU(string, context->operand->imm.value.u,
                formatter->hex_padding_address, formatter->hex_uppercase, formatter->hex_prefix,
                formatter->hex_suffix);
        case ZYDIS_ADDR_FORMAT_RELATIVE_SIGNED:
            return ZydisStringAppendHexS(string, (ZyanI32)context->operand->imm.value.s,
                formatter->hex_padding_address, formatter->hex_uppercase, ZYAN_FALSE,
                formatter->hex_prefix, formatter->hex_suffix);
        case ZYDIS_ADDR_FORMAT_RELATIVE_ASSEMBLER:
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_ADDR_RELATIVE));
            return ZydisStringAppendHexS(string,
                (ZyanI32)(context->operand->imm.value.s + context->instruction->length),
                formatter->hex_padding_address, formatter->hex_uppercase, ZYAN_TRUE,
                formatter->hex_prefix, formatter->hex_suffix);
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
    }

    // The immediate operand contains an actual ordinal value
    return formatter->func_print_imm(formatter, string, context);
}

/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisPrintMnemonicIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZydisShortString* mnemonic =
        ZydisMnemonicGetStringWrapped(context->instruction->mnemonic);
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

static ZyanStatus ZydisPrintRegisterIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context, ZydisRegister reg)
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

static ZyanStatus ZydisPrintAddrIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context, ZyanU64 address)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (context->instruction->stack_width)
    {
    case 16:
        return ZydisStringAppendHexU(string, (ZyanU16)address, 4,
            formatter->hex_uppercase, formatter->hex_prefix, formatter->hex_suffix);
    case 32:
        return ZydisStringAppendHexU(string, (ZyanU32)address, 8,
            formatter->hex_uppercase, formatter->hex_prefix, formatter->hex_suffix);
    case 64:
        return ZydisStringAppendHexU(string, address, 16,
            formatter->hex_uppercase, formatter->hex_prefix, formatter->hex_suffix);
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
}

static ZyanStatus ZydisPrintDispIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (context->operand->mem.disp.has_displacement && ((context->operand->mem.disp.value) ||
        ((context->operand->mem.base == ZYDIS_REGISTER_NONE) &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE))))
    {
        const ZyanBool printSignedHEX = (formatter->format_disp != ZYDIS_DISP_FORMAT_HEX_UNSIGNED);
        if (printSignedHEX && (context->operand->mem.disp.value < 0) && (
            (context->operand->mem.base != ZYDIS_REGISTER_NONE) ||
            (context->operand->mem.index != ZYDIS_REGISTER_NONE)))
        {
            return ZydisStringAppendHexS(string, context->operand->mem.disp.value,
                formatter->hex_padding_disp, formatter->hex_uppercase, ZYAN_FALSE,
                formatter->hex_prefix, formatter->hex_suffix);
        }
        if ((context->operand->mem.base != ZYDIS_REGISTER_NONE) ||
            (context->operand->mem.index != ZYDIS_REGISTER_NONE))
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_ADD));
        }
        return ZydisStringAppendHexU(string, (ZyanU64)context->operand->mem.disp.value,
            formatter->hex_padding_disp, formatter->hex_uppercase, formatter->hex_prefix,
            formatter->hex_suffix);
    }
    return ZYAN_STATUS_SUCCESS;
}

static ZyanStatus ZydisPrintImmIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanBool printSignedHEX = (formatter->format_imm == ZYDIS_IMM_FORMAT_HEX_SIGNED);
    if (formatter->format_imm == ZYDIS_IMM_FORMAT_HEX_AUTO)
    {
        printSignedHEX = context->operand->imm.is_signed;
    }

    if (printSignedHEX && (context->operand->imm.value.s < 0))
    {
        switch (context->operand->size)
        {
        case 8:
            return ZydisStringAppendHexS(string, (ZyanI8)context->operand->imm.value.s,
                formatter->hex_padding_imm, formatter->hex_uppercase, ZYAN_FALSE,
                formatter->hex_prefix, formatter->hex_suffix);
        case 16:
            return ZydisStringAppendHexS(string, (ZyanI16)context->operand->imm.value.s,
                formatter->hex_padding_imm, formatter->hex_uppercase, ZYAN_FALSE,
                formatter->hex_prefix, formatter->hex_suffix);
        case 32:
            return ZydisStringAppendHexS(string, (ZyanI32)context->operand->imm.value.s,
                formatter->hex_padding_imm, formatter->hex_uppercase, ZYAN_FALSE,
                formatter->hex_prefix, formatter->hex_suffix);
        case 64:
            return ZydisStringAppendHexS(string, context->operand->imm.value.s,
                formatter->hex_padding_imm, formatter->hex_uppercase, ZYAN_FALSE,
                formatter->hex_prefix, formatter->hex_suffix);
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
    }
    switch (context->instruction->operand_width)
    {
    case 8:
        return ZydisStringAppendHexU(string, (ZyanU8)context->operand->imm.value.u,
            formatter->hex_padding_imm, formatter->hex_uppercase, formatter->hex_prefix,
            formatter->hex_suffix);
    case 16:
        return ZydisStringAppendHexU(string, (ZyanU16)context->operand->imm.value.u,
            formatter->hex_padding_imm, formatter->hex_uppercase, formatter->hex_prefix,
            formatter->hex_suffix);
    case 32:
        return ZydisStringAppendHexU(string, (ZyanU32)context->operand->imm.value.u,
            formatter->hex_padding_imm, formatter->hex_uppercase, formatter->hex_prefix,
            formatter->hex_suffix);
    case 64:
        return ZydisStringAppendHexU(string, context->operand->imm.value.u,
            formatter->hex_padding_imm, formatter->hex_uppercase, formatter->hex_prefix,
            formatter->hex_suffix);
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
}

static ZyanStatus ZydisPrintMemSizeIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
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

/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisPrintPrefixesIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
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

static ZyanStatus ZydisPrintDecoratorIntel(const ZydisFormatter* formatter, ZyanString* string,
    ZydisFormatterContext* context, ZydisDecoratorType type)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (type)
    {
    case ZYDIS_DECORATOR_TYPE_MASK:
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
    case ZYDIS_DECORATOR_TYPE_BC:
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
    case ZYDIS_DECORATOR_TYPE_RC:
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
    case ZYDIS_DECORATOR_TYPE_SAE:
#if !defined(ZYDIS_DISABLE_AVX512)
        if (context->instruction->avx.has_SAE && !context->instruction->avx.rounding.mode)
        {
            ZYAN_CHECK(ZydisStringAppendShort(string, &STR_DECO_SAE));
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_SWIZZLE:
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
    case ZYDIS_DECORATOR_TYPE_CONVERSION:
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
    case ZYDIS_DECORATOR_TYPE_EH:
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
/* Exported functions                                                                             */
/* ============================================================================================== */

ZyanStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style)
{
    if (!formatter)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_MEMSET(formatter, 0, sizeof(ZydisFormatter));
    switch (style)
    {
    case ZYDIS_FORMATTER_STYLE_INTEL:
        formatter->letter_case              = ZYDIS_LETTER_CASE_DEFAULT;
        formatter->force_memory_segment     = ZYAN_FALSE;
        formatter->force_memory_size        = ZYAN_FALSE;
        formatter->format_address           = ZYDIS_ADDR_FORMAT_ABSOLUTE;
        formatter->format_disp              = ZYDIS_DISP_FORMAT_HEX_SIGNED;
        formatter->format_imm               = ZYDIS_IMM_FORMAT_HEX_UNSIGNED;
        formatter->hex_uppercase            = ZYAN_TRUE;
        formatter->hex_prefix               = &STR_PREFIX_HEX;
        formatter->hex_suffix               = ZYAN_NULL;
        formatter->hex_padding_address      = 2;
        formatter->hex_padding_disp         = 2;
        formatter->hex_padding_imm          = 2;
        break;
    case ZYDIS_FORMATTER_STYLE_INTEL_MASM:
        formatter->letter_case              = ZYDIS_LETTER_CASE_DEFAULT;
        formatter->force_memory_segment     = ZYAN_FALSE;
        formatter->force_memory_size        = ZYAN_TRUE;
        formatter->format_address           = ZYDIS_ADDR_FORMAT_RELATIVE_ASSEMBLER;
        formatter->format_disp              = ZYDIS_DISP_FORMAT_HEX_SIGNED;
        formatter->format_imm               = ZYDIS_IMM_FORMAT_HEX_UNSIGNED;
        formatter->hex_uppercase            = ZYAN_TRUE;
        formatter->hex_prefix               = ZYAN_NULL;
        formatter->hex_suffix               = &STR_SUFFIX_HEX;
        formatter->hex_padding_address      = 2;
        formatter->hex_padding_disp         = 2;
        formatter->hex_padding_imm          = 2;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (style)
    {
    case ZYDIS_FORMATTER_STYLE_INTEL:
    case ZYDIS_FORMATTER_STYLE_INTEL_MASM:
        formatter->func_pre_instruction     = ZYAN_NULL;
        formatter->func_post_instruction    = ZYAN_NULL;
        formatter->func_pre_operand         = ZYAN_NULL;
        formatter->func_post_operand        = ZYAN_NULL;
        formatter->func_format_instruction  = &ZydisFormatInstrIntel;
        formatter->func_format_operand_reg  = &ZydisFormatOperandRegIntel;
        formatter->func_format_operand_mem  = &ZydisFormatOperandMemIntel;
        formatter->func_format_operand_ptr  = &ZydisFormatOperandPtrIntel;
        formatter->func_format_operand_imm  = &ZydisFormatOperandImmIntel;
        formatter->func_print_mnemonic      = &ZydisPrintMnemonicIntel;
        formatter->func_print_register      = &ZydisPrintRegisterIntel;
        formatter->func_print_address       = &ZydisPrintAddrIntel;
        formatter->func_print_disp          = &ZydisPrintDispIntel;
        formatter->func_print_imm           = &ZydisPrintImmIntel;
        formatter->func_print_mem_size      = &ZydisPrintMemSizeIntel;
        formatter->func_print_prefixes      = &ZydisPrintPrefixesIntel;
        formatter->func_print_decorator     = &ZydisPrintDecoratorIntel;
        break;
    default:
        ZYAN_UNREACHABLE;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterSetProperty(ZydisFormatter* formatter,
    ZydisFormatterProperty property, ZyanUPointer value)
{
    if (!formatter)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (property)
    {
    case ZYDIS_FORMATTER_PROP_UPPERCASE:
        formatter->letter_case = (value) ? ZYDIS_LETTER_CASE_UPPER : ZYDIS_LETTER_CASE_DEFAULT;
        break;
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSEG:
        formatter->force_memory_segment = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE:
        formatter->force_memory_size = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_ADDR_FORMAT:
        if (value > ZYDIS_ADDR_FORMAT_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->format_address = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_DISP_FORMAT:
        if (value > ZYDIS_DISP_FORMAT_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->format_disp = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_IMM_FORMAT:
        if (value > ZYDIS_IMM_FORMAT_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->format_imm = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_UPPERCASE:
        formatter->hex_uppercase = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
        formatter->hex_prefix = (value) ? &formatter->hex_prefix_data : ZYAN_NULL;
        if (value)
        {
            formatter->hex_prefix_data.flags = ZYAN_STRING_IS_IMMUTABLE;
            formatter->hex_prefix_data.data.allocator = ZYAN_NULL;
            formatter->hex_prefix_data.data.element_size = sizeof(char);
            formatter->hex_prefix_data.data.capacity = sizeof((char*)value) + 1;
            formatter->hex_prefix_data.data.size = formatter->hex_prefix_data.data.capacity;
            return ZYAN_STATUS_SUCCESS;
        }
        break;
    case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
        formatter->hex_suffix = (value) ? &formatter->hex_suffix_data : ZYAN_NULL;
        if (value)
        {
            formatter->hex_suffix_data.flags = ZYAN_STRING_IS_IMMUTABLE;
            formatter->hex_suffix_data.data.allocator = ZYAN_NULL;
            formatter->hex_suffix_data.data.element_size = sizeof(char);
            formatter->hex_suffix_data.data.capacity = sizeof((char*)value) + 1;
            formatter->hex_suffix_data.data.size = formatter->hex_suffix_data.data.capacity;
            return ZYAN_STATUS_SUCCESS;
        }
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_ADDR:
        if (value > 20)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->hex_padding_address = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_DISP:
        if (value > 20)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->hex_padding_disp = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_IMM:
        if (value > 20)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->hex_padding_imm = (ZyanU8)value;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterSetHook(ZydisFormatter* formatter, ZydisFormatterHookType hook,
    const void** callback)
{
    if (!formatter || !callback)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const void* temp = *callback;

    // Backup the function-pointer
    switch (hook)
    {
    case ZYDIS_FORMATTER_HOOK_PRE_INSTRUCTION:
        *callback = *(const void**)&formatter->func_pre_instruction;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION:
        *callback = *(const void**)&formatter->func_post_instruction;
        break;
    case ZYDIS_FORMATTER_HOOK_PRE_OPERAND:
        *callback = *(const void**)&formatter->func_pre_operand;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_OPERAND:
        *callback = *(const void**)&formatter->func_post_operand;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        *callback = *(const void**)&formatter->func_format_instruction;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG:
        *callback = *(const void**)&formatter->func_format_operand_reg;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM:
        *callback = *(const void**)&formatter->func_format_operand_mem;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR:
        *callback = *(const void**)&formatter->func_format_operand_ptr;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM:
        *callback = *(const void**)&formatter->func_format_operand_imm;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC:
        *callback = *(const void**)&formatter->func_print_mnemonic;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_REGISTER:
        *callback = *(const void**)&formatter->func_print_register;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS:
        *callback = *(const void**)&formatter->func_print_address;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DISP:
        *callback = *(const void**)&formatter->func_print_disp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMM:
        *callback = *(const void**)&formatter->func_print_imm;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE:
        *callback = *(const void**)&formatter->func_print_mem_size;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        *callback = *(const void**)&formatter->func_print_prefixes;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        *callback = *(const void**)&formatter->func_print_decorator;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // The function was used to get the current function-pointer without replacing it
    if (!temp)
    {
        return ZYAN_STATUS_SUCCESS;
    }

    // Replace the function-pointer
    switch (hook)
    {
    case ZYDIS_FORMATTER_HOOK_PRE_INSTRUCTION:
        formatter->func_pre_instruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION:
        formatter->func_post_instruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRE_OPERAND:
        formatter->func_pre_operand = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_OPERAND:
        formatter->func_post_operand = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        formatter->func_format_instruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG:
        formatter->func_format_operand_reg = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM:
        formatter->func_format_operand_mem = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR:
        formatter->func_format_operand_ptr = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM:
        formatter->func_format_operand_imm = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC:
        formatter->func_print_mnemonic = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_REGISTER:
        formatter->func_print_register = *(ZydisFormatterRegisterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS:
        formatter->func_print_address = *(ZydisFormatterAddressFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DISP:
        formatter->func_print_disp = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMM:
        formatter->func_print_imm = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE:
        formatter->func_print_mem_size = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        formatter->func_print_prefixes = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        formatter->func_print_decorator = *(ZydisFormatterDecoratorFunc*)&temp;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZyanUSize length, ZyanU64 address)
{
    return ZydisFormatterFormatInstructionEx(formatter, instruction, buffer, length, address,
        ZYAN_NULL);
}

ZyanStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZyanUSize length, ZyanU64 address,
    void* user_data)
{
    if (!formatter || !instruction || !buffer || (length == 0))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanString string;
    string.flags             = ZYAN_STRING_HAS_FIXED_CAPACITY;
    string.data.allocator    = ZYAN_NULL;
    string.data.element_size = sizeof(char);
    string.data.size         = 1;
    string.data.capacity     = length;
    string.data.data         = buffer;
    *buffer = '\0';

    ZydisFormatterContext context;
    context.instruction = instruction;
    context.address     = address;
    context.operand     = ZYAN_NULL;
    context.user_data   = user_data;

    const ZyanStatus status = ZydisFormatInstruction(formatter, &string, &context);
    if (status == ZYDIS_STATUS_SKIP_TOKEN)
    {
        return ZYAN_STATUS_SUCCESS;
    }
    return status;
}

ZyanStatus ZydisFormatterFormatOperand(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZyanU8 index, char* buffer, ZyanUSize length,
    ZyanU64 address)
{
    return ZydisFormatterFormatOperandEx(formatter, instruction, index, buffer, length,
        address, ZYAN_NULL);
}

ZyanStatus ZydisFormatterFormatOperandEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZyanU8 index, char* buffer, ZyanUSize length,
    ZyanU64 address, void* user_data)
{
    if (!formatter || !instruction || index >= instruction->operand_count || !buffer ||
        (length == 0))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanString string;
    string.flags             = ZYAN_STRING_HAS_FIXED_CAPACITY;
    string.data.allocator    = ZYAN_NULL;
    string.data.element_size = sizeof(char);
    string.data.size         = 1;
    string.data.capacity     = length;
    string.data.data         = buffer;
    *buffer = '\0';

    ZydisFormatterContext context;
    context.instruction = instruction;
    context.address     = address;
    context.operand     = &instruction->operands[index];
    context.user_data   = user_data;

    ZyanStatus status;
    if (formatter->func_pre_operand)
    {
        status = formatter->func_pre_operand(formatter, &string, &context);
        // We ignore `ZYDIS_STATUS_SKIP_TOKEN` as it does not make any sense to skip the only
        // operand printed by this function
        if ((status != ZYAN_STATUS_SUCCESS) && (status != ZYDIS_STATUS_SKIP_TOKEN))
        {
            goto FinalizeString;
        }
    }

    switch (context.operand->type)
    {
    case ZYDIS_OPERAND_TYPE_REGISTER:
        status = formatter->func_format_operand_reg(formatter, &string, &context);
        break;
    case ZYDIS_OPERAND_TYPE_MEMORY:
        status = formatter->func_format_operand_mem(formatter, &string, &context);
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        status = formatter->func_format_operand_imm(formatter, &string, &context);
        break;
    case ZYDIS_OPERAND_TYPE_POINTER:
        status = formatter->func_format_operand_ptr(formatter, &string, &context);
        break;
    default:
        status = ZYAN_STATUS_INVALID_ARGUMENT;
        break;
    }
    // Ignore `ZYDIS_STATUS_SKIP_TOKEN`
    if (status == ZYDIS_STATUS_SKIP_TOKEN)
    {
        status = ZYAN_STATUS_SUCCESS;
    }
    if (!ZYAN_SUCCESS(status))
    {
        goto FinalizeString;
    }

    // TODO: Print AVX512/KNC decorator

    if (formatter->func_post_operand)
    {
        status = formatter->func_post_operand(formatter, &string, &context);
        // Ignore `ZYDIS_STATUS_SKIP_TOKEN`
        if (status == ZYDIS_STATUS_SKIP_TOKEN)
        {
            status = ZYAN_STATUS_SUCCESS;
        }
    }

FinalizeString:
    return status;
}

/* ============================================================================================== */
