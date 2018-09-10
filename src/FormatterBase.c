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

#include <Zydis/Internal/FormatterBase.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* String constants                                                                               */
/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString STR_WHITESPACE     = ZYDIS_MAKE_SHORTSTRING(" ");
static const ZydisShortString STR_DELIM_SEGMENT  = ZYDIS_MAKE_SHORTSTRING(":");
static const ZydisShortString STR_PREF_XACQUIRE  = ZYDIS_MAKE_SHORTSTRING("xacquire");
static const ZydisShortString STR_PREF_XRELEASE  = ZYDIS_MAKE_SHORTSTRING("xrelease");
static const ZydisShortString STR_PREF_LOCK      = ZYDIS_MAKE_SHORTSTRING("lock");
static const ZydisShortString STR_PREF_REP       = ZYDIS_MAKE_SHORTSTRING("rep");
static const ZydisShortString STR_PREF_REPE      = ZYDIS_MAKE_SHORTSTRING("repe");
static const ZydisShortString STR_PREF_REPNE     = ZYDIS_MAKE_SHORTSTRING("repne");
static const ZydisShortString STR_PREF_BND       = ZYDIS_MAKE_SHORTSTRING("bnd");
static const ZydisShortString STR_PREF_SEG_CS    = ZYDIS_MAKE_SHORTSTRING("cs");
static const ZydisShortString STR_PREF_SEG_SS    = ZYDIS_MAKE_SHORTSTRING("ss");
static const ZydisShortString STR_PREF_SEG_DS    = ZYDIS_MAKE_SHORTSTRING("ds");
static const ZydisShortString STR_PREF_SEG_ES    = ZYDIS_MAKE_SHORTSTRING("es");
static const ZydisShortString STR_PREF_SEG_FS    = ZYDIS_MAKE_SHORTSTRING("fs");
static const ZydisShortString STR_PREF_SEG_GS    = ZYDIS_MAKE_SHORTSTRING("gs");
static const ZydisShortString STR_DECO_BEGIN     = ZYDIS_MAKE_SHORTSTRING("{");
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
static const ZydisShortString STR_ADD            = ZYDIS_MAKE_SHORTSTRING("+");

/* ---------------------------------------------------------------------------------------------- */

static const ZydisShortString STR_PREF_REX[0x10] =
{
    /* 40 */ ZYDIS_MAKE_SHORTSTRING("re "),
    /* 41 */ ZYDIS_MAKE_SHORTSTRING("rex.b"),
    /* 42 */ ZYDIS_MAKE_SHORTSTRING("rex.x"),
    /* 43 */ ZYDIS_MAKE_SHORTSTRING("rex.xb"),
    /* 44 */ ZYDIS_MAKE_SHORTSTRING("rex.r"),
    /* 45 */ ZYDIS_MAKE_SHORTSTRING("rex.rb"),
    /* 46 */ ZYDIS_MAKE_SHORTSTRING("rex.rx"),
    /* 47 */ ZYDIS_MAKE_SHORTSTRING("rex.rxb"),
    /* 48 */ ZYDIS_MAKE_SHORTSTRING("rex.w"),
    /* 49 */ ZYDIS_MAKE_SHORTSTRING("rex.wb"),
    /* 4A */ ZYDIS_MAKE_SHORTSTRING("rex.wx"),
    /* 4B */ ZYDIS_MAKE_SHORTSTRING("rex.wxb"),
    /* 4C */ ZYDIS_MAKE_SHORTSTRING("rex.wr"),
    /* 4D */ ZYDIS_MAKE_SHORTSTRING("rex.wrb"),
    /* 4E */ ZYDIS_MAKE_SHORTSTRING("rex.wrx"),
    /* 4F */ ZYDIS_MAKE_SHORTSTRING("rex.wrxb")
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/**
 * @brief   Appends a prefix string.
 *
 * @brief   buffer      A pointer to the `ZydisFormatterBuffer` struct.
 * @brief   string      A pointer to the `ZydisShortString` that contains the prefix string.
 * @brief   letter_case The desired letter-case.
 */
#define ZYDIS_APPEND_PREFIX(buffer, string, letter_case) \
    ZYDIS_BUFFER_APPEND_STRING_CASE(buffer, ZYDIS_TOKEN_PREFIX, string, letter_case); \
    ZYDIS_BUFFER_APPEND_STRING(buffer, ZYDIS_TOKEN_WHITESPACE, &STR_WHITESPACE);

/**
 * @brief   Appends a decorator string.
 *
 * @brief   buffer  A pointer to the `ZydisFormatterBuffer` struct.
 * @brief   value   A pointer to the `ZydisShortString` that contains the decorator string.
 */
#define ZYDIS_APPEND_DECORATOR(buffer, value) \
    if ((buffer)->tokenized) \
    { \
        ZYAN_CHECK(ZydisFormatterBufferAppend(buffer, ZYDIS_TOKEN_WHITESPACE)); \
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_WHITESPACE)); \
        ZYAN_CHECK(ZydisFormatterBufferAppend(buffer, ZYDIS_TOKEN_DELIMITER)); \
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DECO_BEGIN)); \
        ZYAN_CHECK(ZydisFormatterBufferAppend(buffer, ZYDIS_TOKEN_DECORATOR)); \
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, value)); \
        ZYAN_CHECK(ZydisFormatterBufferAppend(buffer, ZYDIS_TOKEN_DELIMITER)); \
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DECO_END)); \
    } else \
    { \
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, value)); \
    }

//#undef ZYDIS_APPEND_DECORATOR
//#define ZYDIS_APPEND_DECORATOR(buffer, value) ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, value));

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

ZyanU32 ZydisFormatterHelperGetExplicitSize(const ZydisFormatter* formatter,
    ZydisFormatterContext* context, ZyanU8 memop_id)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(context);
    ZYAN_ASSERT(memop_id < context->instruction->operand_count);

    const ZydisDecodedOperand* const operand = &context->instruction->operands[memop_id];
    ZYAN_ASSERT(operand->type == ZYDIS_OPERAND_TYPE_MEMORY);
    ZYAN_ASSERT(operand->mem.type == ZYDIS_MEMOP_TYPE_MEM);

    if (formatter->force_memory_size)
    {
        return operand->size;
    }

    switch (operand->id)
    {
    case 0:
        if ((context->instruction->operands[1].type == ZYDIS_OPERAND_TYPE_UNUSED) ||
            (context->instruction->operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
        {
            return context->instruction->operands[0].size;
        }
        if (context->instruction->operands[0].size != context->instruction->operands[1].size)
        {
            return context->instruction->operands[0].size;
        }
        if ((context->instruction->operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (context->instruction->operands[1].visibility == ZYDIS_OPERAND_VISIBILITY_IMPLICIT) &&
            (context->instruction->operands[1].reg.value == ZYDIS_REGISTER_CL))
        {
            return context->instruction->operands[0].size;
        }
        break;
    case 1:
    case 2:
        if (context->instruction->operands[operand->id - 1].size !=
            context->instruction->operands[operand->id].size)
        {
            return context->instruction->operands[operand->id].size;
        }
        break;
    default:
        break;
    }

    return 0;
}

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterBaseFormatOperandREG(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    return formatter->func_print_register(formatter, buffer, context, context->operand->reg.value);
}

ZyanStatus ZydisFormatterBaseFormatOperandPTR(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, &buffer->string,
        context->operand->ptr.segment, 4);
    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
    ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIM_SEGMENT));
    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, &buffer->string,
        context->operand->ptr.offset , 8);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBaseFormatOperandIMM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    // The immediate operand contains an address
    if (context->operand->imm.is_relative)
    {
        const ZyanBool absolute = (context->runtime_address != ZYDIS_RUNTIME_ADDRESS_NONE);
        if (absolute)
        {
            return formatter->func_print_address_abs(formatter, buffer, context);
        }
        return formatter->func_print_address_rel(formatter, buffer, context);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->func_print_imm(formatter, buffer, context);
}

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterBasePrintAddressABS(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

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

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_ADDRESS_ABS);
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, &buffer->string, address, padding);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBasePrintAddressREL(const ZydisFormatter* formatter,
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
    switch (formatter->addr_signedness)
    {
    case ZYDIS_SIGNEDNESS_AUTO:
    case ZYDIS_SIGNEDNESS_SIGNED:
        ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->addr_base, &buffer->string, address,
            padding, ZYAN_TRUE);
        break;
    case ZYDIS_SIGNEDNESS_UNSIGNED:
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_ADD));
        ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->addr_base, &buffer->string, address,
            padding);
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBasePrintIMM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_IMMEDIATE);

    const ZyanBool is_signed =
        (formatter->imm_signedness == ZYDIS_SIGNEDNESS_SIGNED) ||
        (formatter->imm_signedness == ZYDIS_SIGNEDNESS_AUTO && (context->operand->imm.is_signed));
    if (is_signed && (context->operand->imm.value.s < 0))
    {
        ZYDIS_STRING_APPEND_NUM_S(formatter, formatter->imm_base, &buffer->string,
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
    ZYDIS_STRING_APPEND_NUM_U(formatter, formatter->imm_base, &buffer->string, value, padding);

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Optional tokens                                                                                */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterBasePrintSegment(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

    ZyanBool printed_segment = ZYAN_FALSE;
    switch (context->operand->mem.segment)
    {
    case ZYDIS_REGISTER_ES:
    case ZYDIS_REGISTER_CS:
    case ZYDIS_REGISTER_FS:
    case ZYDIS_REGISTER_GS:
        ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
            context->operand->mem.segment));
        printed_segment = ZYAN_TRUE;
        break;
    case ZYDIS_REGISTER_SS:
        if ((formatter->force_memory_segment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.segment));
            printed_segment = ZYAN_TRUE;
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->force_memory_segment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                context->operand->mem.segment));
            printed_segment = ZYAN_TRUE;
        }
        break;
    default:
        break;
    }
    if (printed_segment)
    {
        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_DELIMITER);
        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DELIM_SEGMENT));
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBasePrintPrefixes(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

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
                    ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REX[value & 0x0F],
                        formatter->letter_case);
                } else
                {
                    switch (value)
                    {
                    case 0xF0:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_LOCK, formatter->letter_case);
                        break;
                    case 0x2E:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_SEG_CS, formatter->letter_case);
                        break;
                    case 0x36:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_SEG_SS, formatter->letter_case)
                        break;
                    case 0x3E:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_SEG_DS, formatter->letter_case)
                        break;
                    case 0x26:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_SEG_ES, formatter->letter_case)
                        break;
                    case 0x64:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_SEG_FS, formatter->letter_case)
                        break;
                    case 0x65:
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_SEG_GS, formatter->letter_case)
                        break;
                    default:
                        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PREFIX);
                        ZYAN_CHECK(ZydisStringAppendHexU(&buffer->string, value, 0,
                            formatter->hex_uppercase, ZYAN_NULL, ZYAN_NULL));
                        ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_WHITESPACE);
                        ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_WHITESPACE));
                        break;
                    }
                }
                break;
            }
            case ZYDIS_PREFIX_TYPE_EFFECTIVE:
                switch (value)
                {
                case 0xF0:
                    ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_LOCK, formatter->letter_case);
                    break;
                case 0xF2:
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
                    {
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_XACQUIRE, formatter->letter_case);
                    }
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
                    {
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REPNE, formatter->letter_case);
                    }

                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_BND)
                    {
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_BND, formatter->letter_case);
                    }
                    break;
                case 0xF3:
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
                    {
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_XRELEASE, formatter->letter_case);
                    }
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
                    {
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REP, formatter->letter_case);
                    }
                    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
                    {
                        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REPE, formatter->letter_case);
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
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_XACQUIRE, formatter->letter_case);
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_XRELEASE, formatter->letter_case);
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_LOCK, formatter->letter_case);
        return ZYAN_STATUS_SUCCESS;
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REP, formatter->letter_case);
        return ZYAN_STATUS_SUCCESS;
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REPE, formatter->letter_case);
        return ZYAN_STATUS_SUCCESS;
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_REPNE, formatter->letter_case);
        return ZYAN_STATUS_SUCCESS;
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_BND)
    {
        ZYDIS_APPEND_PREFIX(buffer, &STR_PREF_BND, formatter->letter_case);
        return ZYAN_STATUS_SUCCESS;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBasePrintDecorator(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context, ZydisDecorator decorator)
{
    ZYAN_ASSERT(formatter);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(context);

#if !defined(ZYDIS_DISABLE_AVX512) && !defined(ZYDIS_DISABLE_KNC)
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(buffer);
    ZYAN_UNUSED(context);
#endif

    switch (decorator)
    {
    case ZYDIS_DECORATOR_MASK:
    {
#if !defined(ZYDIS_DISABLE_AVX512) || !defined(ZYDIS_DISABLE_KNC)
        if (context->instruction->avx.mask.reg != ZYDIS_REGISTER_K0)
        {
            if (buffer->tokenized)
            {
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_WHITESPACE);
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_WHITESPACE));
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PARENTHESIS_OPEN);
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DECO_BEGIN));
                ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                    context->instruction->avx.mask.reg));
                ZYDIS_BUFFER_APPEND_TOKEN(buffer, ZYDIS_TOKEN_PARENTHESIS_CLOSE);
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DECO_END));
            } else
            {
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DECO_BEGIN));
                ZYAN_CHECK(formatter->func_print_register(formatter, buffer, context,
                    context->instruction->avx.mask.reg));
                ZYAN_CHECK(ZydisStringAppendShort(&buffer->string, &STR_DECO_END));
            }

            // Only print the zeroing decorator, if the instruction is not a "zeroing masking only"
            // instruction (e.g. `vcmpsd`)
            if ((context->instruction->avx.mask.mode == ZYDIS_MASK_MODE_ZEROING) &&
                (context->instruction->raw.evex.z))
            {
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_ZERO);
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
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_1TO2);
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_4:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_1TO4);
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_8:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_1TO8);
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_16:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_1TO16);
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_8:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_4TO8);
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_16:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_4TO16);
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
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RN_SAE);
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RD_SAE);
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RU_SAE);
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RZ_SAE);
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
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RN);
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RD);
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RU);
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_RZ);
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
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_SAE);
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
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_CDAB);
            break;
        case ZYDIS_SWIZZLE_MODE_BADC:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_BADC);
            break;
        case ZYDIS_SWIZZLE_MODE_DACB:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_DACB);
            break;
        case ZYDIS_SWIZZLE_MODE_AAAA:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_AAAA);
            break;
        case ZYDIS_SWIZZLE_MODE_BBBB:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_BBBB);
            break;
        case ZYDIS_SWIZZLE_MODE_CCCC:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_CCCC);
            break;
        case ZYDIS_SWIZZLE_MODE_DDDD:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_DDDD);
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
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_FLOAT16);
            break;
        case ZYDIS_CONVERSION_MODE_SINT8:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_SINT8);
            break;
        case ZYDIS_CONVERSION_MODE_UINT8:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_UINT8);
            break;
        case ZYDIS_CONVERSION_MODE_SINT16:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_SINT16);
            break;
        case ZYDIS_CONVERSION_MODE_UINT16:
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_UINT16);
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
            ZYDIS_APPEND_DECORATOR(buffer, &STR_DECO_EH);
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
