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

/* ============================================================================================== */
/* Internal functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* General                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisFormatInstruction(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (formatter->funcPreInstruction)
    {
        ZYAN_CHECK(formatter->funcPreInstruction(formatter, string, context));
    }

    ZYAN_CHECK(formatter->funcFormatInstruction(formatter, string, context));

    if (formatter->funcPostInstruction)
    {
        return formatter->funcPostInstruction(formatter, string, context);
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Intel style                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisFormatInstrIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !string || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_CHECK(formatter->funcPrintPrefixes(formatter, string, context));
    ZYAN_CHECK(formatter->funcPrintMnemonic(formatter, string, context));

    const ZyanUSize strLenMnemonic = string->length;
    for (ZyanU8 i = 0; i < context->instruction->operandCount; ++i)
    {
        if (context->instruction->operands[i].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        const ZyanUSize strLenRestore = string->length;
        if (string->length == strLenMnemonic)
        {
            ZYAN_CHECK(ZydisStringAppendC(string, " "));
        } else
        {
            ZYAN_CHECK(ZydisStringAppendC(string, ", "));
        }

        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) && (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (context->instruction->operands[i].encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            string->length = strLenRestore;
            continue;
        }

        // Set current operand
        context->operand = &context->instruction->operands[i];

        ZyanStatus status;
        if (formatter->funcPreOperand)
        {
            status = formatter->funcPreOperand(formatter, string, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                string->length = strLenRestore;
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
            status = formatter->funcFormatOperandReg(formatter, string, context);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
        {
            status = formatter->funcFormatOperandMem(formatter, string, context);
            break;
        }
        case ZYDIS_OPERAND_TYPE_POINTER:
            status = formatter->funcFormatOperandPtr(formatter, string, context);
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            status = formatter->funcFormatOperandImm(formatter, string, context);
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        if (status == ZYDIS_STATUS_SKIP_TOKEN)
        {
            string->length = strLenRestore;
            continue;
        }
        if (status != ZYAN_STATUS_SUCCESS)
        {
            return status;
        }

        if (formatter->funcPostOperand)
        {
            status = formatter->funcPostOperand(formatter, string, context);
            if (status == ZYDIS_STATUS_SKIP_TOKEN)
            {
                string->length = strLenRestore;
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
                ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                    ZYDIS_DECORATOR_TYPE_MASK));
            }
            if (context->instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                    ZYDIS_DECORATOR_TYPE_BC));
                if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                {
                    ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_CONVERSION));
                    ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_EH));
                }
            } else
            {
                if ((i == (context->instruction->operandCount - 1)) ||
                    (context->instruction->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
                {
                    if (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                            ZYDIS_DECORATOR_TYPE_SWIZZLE));
                    }
                    ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_RC));
                    ZYAN_CHECK(formatter->funcPrintDecorator(formatter, string, context,
                        ZYDIS_DECORATOR_TYPE_SAE));
                }
            }
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

static ZyanStatus ZydisFormatOperandRegIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return formatter->funcPrintRegister(formatter, string, context, context->operand->reg.value);
}

static ZyanStatus ZydisFormatOperandMemIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZyanStatus status = formatter->funcPrintMemSize(formatter, string, context);
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
        ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
            context->operand->mem.segment));
        break;
    case ZYDIS_REGISTER_SS:
        if ((formatter->forceMemorySegment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
                context->operand->mem.segment));
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->forceMemorySegment) ||
            (context->instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
                context->operand->mem.segment));
        }
        break;
    default:
        break;
    }
    if (ZYAN_SUCCESS(status))
    {
        ZYAN_CHECK(ZydisStringAppendC(string, ":"));
    }

    ZYAN_CHECK(ZydisStringAppendC(string, "["));

    if (context->operand->mem.disp.hasDisplacement && (
        (context->operand->mem.base == ZYDIS_REGISTER_NONE) ||
        (context->operand->mem.base == ZYDIS_REGISTER_EIP) ||
        (context->operand->mem.base == ZYDIS_REGISTER_RIP)) &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE) && (context->operand->mem.scale == 0))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        if ((formatter->formatAddress == ZYDIS_ADDR_FORMAT_ABSOLUTE) ||
            (context->operand->mem.base == ZYDIS_REGISTER_NONE))
        {
            ZyanU64 address;
            ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand,
                context->address, &address));
            ZYAN_CHECK(formatter->funcPrintAddress(formatter, string, context, address));
        } else
        {
            ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
                context->operand->mem.base));
            ZYAN_CHECK(formatter->funcPrintDisp(formatter, string, context));
        }
    } else
    {
        // Regular memory operand
        if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
                context->operand->mem.base));
        }
        if ((context->operand->mem.index != ZYDIS_REGISTER_NONE) &&
            (context->operand->mem.type != ZYDIS_MEMOP_TYPE_MIB))
        {
            if (context->operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYAN_CHECK(ZydisStringAppendC(string, "+"));
            }
            ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
                context->operand->mem.index));
            if (context->operand->mem.scale)
            {
                ZYAN_CHECK(ZydisStringAppendC(string, "*"));
                ZYAN_CHECK(ZydisStringAppendDecU(string, context->operand->mem.scale, 0));
            }
        }
        ZYAN_CHECK(formatter->funcPrintDisp(formatter, string, context));
    }

    return ZydisStringAppendC(string, "]");
}

static ZyanStatus ZydisFormatOperandPtrIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZYAN_CHECK(ZydisStringAppendHexU(string, context->operand->ptr.segment, 4,
        formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix));
    ZYAN_CHECK(ZydisStringAppendC(string, ":"));
    return ZydisStringAppendHexU(string, context->operand->ptr.offset, 8,
        formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
}

static ZyanStatus ZydisFormatOperandImmIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // The immediate operand contains an address
    if (context->operand->imm.isRelative)
    {
        ZyanBool printSignedHEX = ZYAN_FALSE;
        switch (formatter->formatAddress)
        {
        case ZYDIS_ADDR_FORMAT_ABSOLUTE:
        {
            ZyanU64 address;
            ZYAN_CHECK(ZydisCalcAbsoluteAddress(context->instruction, context->operand,
                context->address, &address));
            return formatter->funcPrintAddress(formatter, string, context, address);
        }
        case ZYDIS_ADDR_FORMAT_RELATIVE_SIGNED:
            printSignedHEX = ZYAN_TRUE;
            break;
        case ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED:
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }

        if (printSignedHEX)
        {
            return ZydisStringAppendHexS(string, (ZyanI32)context->operand->imm.value.s,
                formatter->hexPaddingAddress, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        }
        return ZydisStringAppendHexU(string, context->operand->imm.value.u,
            formatter->hexPaddingAddress, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->funcPrintImm(formatter, string, context);
}

/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisPrintMnemonicIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZydisStaticString* mnemonic =
        ZydisMnemonicGetStaticString(context->instruction->mnemonic);
    if (!mnemonic)
    {
        return ZydisStringAppendExC(string, "invalid", formatter->letterCase);
    }
    ZYAN_CHECK(ZydisStringAppendExStatic(string, mnemonic, formatter->letterCase));

    if (context->instruction->attributes & ZYDIS_ATTRIB_IS_FAR_BRANCH)
    {
        return ZydisStringAppendExC(string, " far", formatter->letterCase);
    }

    return ZYAN_STATUS_SUCCESS;
}

static ZyanStatus ZydisPrintRegisterIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context, ZydisRegister reg)
{
    ZYAN_UNUSED(context);

    if (!formatter)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZydisStaticString* str = ZydisRegisterGetStaticString(reg);
    if (!str)
    {
        return ZydisStringAppendExC(string, "invalid", formatter->letterCase);
    }
    return ZydisStringAppendExStatic(string, str, formatter->letterCase);
}

static ZyanStatus ZydisPrintAddrIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context, ZyanU64 address)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    switch (context->instruction->stackWidth)
    {
    case 16:
        return ZydisStringAppendHexU(string, (ZyanU16)address, 4,
            formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
    case 32:
        return ZydisStringAppendHexU(string, (ZyanU32)address, 8,
            formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
    case 64:
        return ZydisStringAppendHexU(string, address, 16,
            formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
}

static ZyanStatus ZydisPrintDispIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (context->operand->mem.disp.hasDisplacement && ((context->operand->mem.disp.value) ||
        ((context->operand->mem.base == ZYDIS_REGISTER_NONE) &&
        (context->operand->mem.index == ZYDIS_REGISTER_NONE))))
    {
        const ZyanBool printSignedHEX = (formatter->formatDisp != ZYDIS_DISP_FORMAT_HEX_UNSIGNED);
        if (printSignedHEX && (context->operand->mem.disp.value < 0) && (
            (context->operand->mem.base != ZYDIS_REGISTER_NONE) ||
            (context->operand->mem.index != ZYDIS_REGISTER_NONE)))
        {
            return ZydisStringAppendHexS(string, context->operand->mem.disp.value,
                formatter->hexPaddingDisp, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        }
        if ((context->operand->mem.base != ZYDIS_REGISTER_NONE) ||
            (context->operand->mem.index != ZYDIS_REGISTER_NONE))
        {
            ZYAN_CHECK(ZydisStringAppendC(string, "+"));
        }
        return ZydisStringAppendHexU(string, (ZyanU64)context->operand->mem.disp.value,
            formatter->hexPaddingDisp, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    }
    return ZYAN_STATUS_SUCCESS;
}

static ZyanStatus ZydisPrintImmIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZyanBool printSignedHEX = (formatter->formatImm == ZYDIS_IMM_FORMAT_HEX_SIGNED);
    if (formatter->formatImm == ZYDIS_IMM_FORMAT_HEX_AUTO)
    {
        printSignedHEX = context->operand->imm.isSigned;
    }

    if (printSignedHEX && (context->operand->imm.value.s < 0))
    {
        switch (context->operand->size)
        {
        case 8:
            return ZydisStringAppendHexS(string, (ZyanI8)context->operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        case 16:
            return ZydisStringAppendHexS(string, (ZyanI16)context->operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        case 32:
            return ZydisStringAppendHexS(string, (ZyanI32)context->operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        case 64:
            return ZydisStringAppendHexS(string, context->operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
    }
    switch (context->instruction->operandWidth)
    {
    case 8:
        return ZydisStringAppendHexU(string, (ZyanU8)context->operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    case 16:
        return ZydisStringAppendHexU(string, (ZyanU16)context->operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    case 32:
        return ZydisStringAppendHexU(string, (ZyanU32)context->operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    case 64:
        return ZydisStringAppendHexU(string, context->operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
}

static ZyanStatus ZydisPrintMemSizeIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    // TODO: refactor

    ZyanU32 typecast = 0;
    if (formatter->forceMemorySize)
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
        const char* str = ZYAN_NULL;
        switch (typecast)
        {
        case 8:
            str = "byte ptr ";
            break;
        case 16:
            str = "word ptr ";
            break;
        case 32:
            str = "dword ptr ";
            break;
        case 48:
            str = "fword ptr ";
            break;
        case 64:
            str = "qword ptr ";
            break;
        case 80:
            str = "tbyte ptr ";
            break;
        case 128:
            str = "xmmword ptr ";
            break;
        case 256:
            str = "ymmword ptr ";
            break;
        case 512:
            str = "zmmword ptr ";
            break;
        default:
            break;
        }

        if (str)
        {
            return ZydisStringAppendExC(string, str, formatter->letterCase);
        }
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

static ZyanStatus ZydisPrintPrefixesIntel(const ZydisFormatter* formatter, ZydisString* string,
    ZydisFormatterContext* context)
{
    if (!formatter || !context)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
    {
        ZYAN_CHECK(ZydisStringAppendExC(string, "xacquire ", formatter->letterCase));
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        ZYAN_CHECK(ZydisStringAppendExC(string, "xrelease ", formatter->letterCase));
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        return ZydisStringAppendExC(string, "lock ", formatter->letterCase);
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        return ZydisStringAppendExC(string, "rep ", formatter->letterCase);
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        return ZydisStringAppendExC(string, "repe ", formatter->letterCase);
    }
    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        return ZydisStringAppendExC(string, "repne ", formatter->letterCase);
    }

    if (context->instruction->attributes & ZYDIS_ATTRIB_HAS_BOUND)
    {
        return ZydisStringAppendExC(string, "bnd ", formatter->letterCase);
    }

    return ZYAN_STATUS_SUCCESS;
}

static ZyanStatus ZydisPrintDecoratorIntel(const ZydisFormatter* formatter, ZydisString* string,
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
#if !defined(ZYDIS_DISABLE_EVEX) || !defined(ZYDIS_DISABLE_MVEX)
        if (context->instruction->avx.mask.reg != ZYDIS_REGISTER_K0)
        {
            ZYAN_CHECK(ZydisStringAppendC(string, " {"));
            ZYAN_CHECK(formatter->funcPrintRegister(formatter, string, context,
                context->instruction->avx.mask.reg));
            ZYAN_CHECK(ZydisStringAppendC(string, "}"));
            if (context->instruction->avx.mask.mode == ZYDIS_MASK_MODE_ZERO)
            {
                ZYAN_CHECK(ZydisStringAppendC(string, " {z}"));
            }
        }
#endif
        break;
    }
    case ZYDIS_DECORATOR_TYPE_BC:
#if !defined(ZYDIS_DISABLE_EVEX)
        if (!context->instruction->avx.broadcast.isStatic)
        {
            switch (context->instruction->avx.broadcast.mode)
            {
            case ZYDIS_BROADCAST_MODE_INVALID:
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_2:
                ZYAN_CHECK(ZydisStringAppendC(string, " {1to2}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_4:
                ZYAN_CHECK(ZydisStringAppendC(string, " {1to4}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_8:
                ZYAN_CHECK(ZydisStringAppendC(string, " {1to8}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_16:
                ZYAN_CHECK(ZydisStringAppendC(string, " {1to16}"));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_8:
                ZYAN_CHECK(ZydisStringAppendC(string, " {4to8}"));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_16:
                ZYAN_CHECK(ZydisStringAppendC(string, " {4to16}"));
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_RC:
#if !defined(ZYDIS_DISABLE_EVEX)
        if (context->instruction->avx.hasSAE)
        {
            switch (context->instruction->avx.rounding.mode)
            {
            case ZYDIS_ROUNDING_MODE_INVALID:
                break;
            case ZYDIS_ROUNDING_MODE_RN:
                ZYAN_CHECK(ZydisStringAppendC(string, " {rn-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYAN_CHECK(ZydisStringAppendC(string, " {rd-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYAN_CHECK(ZydisStringAppendC(string, " {ru-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYAN_CHECK(ZydisStringAppendC(string, " {rz-sae}"));
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
                ZYAN_CHECK(ZydisStringAppendC(string, " {rn}"));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYAN_CHECK(ZydisStringAppendC(string, " {rd}"));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYAN_CHECK(ZydisStringAppendC(string, " {ru}"));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYAN_CHECK(ZydisStringAppendC(string, " {rz}"));
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_SAE:
#if !defined(ZYDIS_DISABLE_EVEX)
        if (context->instruction->avx.hasSAE && !context->instruction->avx.rounding.mode)
        {
            ZYAN_CHECK(ZydisStringAppendC(string, " {sae}"));
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_SWIZZLE:
#if !defined(ZYDIS_DISABLE_MVEX)
        switch (context->instruction->avx.swizzle.mode)
        {
        case ZYDIS_SWIZZLE_MODE_INVALID:
        case ZYDIS_SWIZZLE_MODE_DCBA:
            // Nothing to do here
            break;
        case ZYDIS_SWIZZLE_MODE_CDAB:
            ZYAN_CHECK(ZydisStringAppendC(string, " {cdab}"));
            break;
        case ZYDIS_SWIZZLE_MODE_BADC:
            ZYAN_CHECK(ZydisStringAppendC(string, " {badc}"));
            break;
        case ZYDIS_SWIZZLE_MODE_DACB:
            ZYAN_CHECK(ZydisStringAppendC(string, " {dacb}"));
            break;
        case ZYDIS_SWIZZLE_MODE_AAAA:
            ZYAN_CHECK(ZydisStringAppendC(string, " {aaaa}"));
            break;
        case ZYDIS_SWIZZLE_MODE_BBBB:
            ZYAN_CHECK(ZydisStringAppendC(string, " {bbbb}"));
            break;
        case ZYDIS_SWIZZLE_MODE_CCCC:
            ZYAN_CHECK(ZydisStringAppendC(string, " {cccc}"));
            break;
        case ZYDIS_SWIZZLE_MODE_DDDD:
            ZYAN_CHECK(ZydisStringAppendC(string, " {dddd}"));
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_CONVERSION:
#if !defined(ZYDIS_DISABLE_MVEX)
        switch (context->instruction->avx.conversion.mode)
        {
        case ZYDIS_CONVERSION_MODE_INVALID:
            break;
        case ZYDIS_CONVERSION_MODE_FLOAT16:
            ZYAN_CHECK(ZydisStringAppendC(string, " {float16}"));
            break;
        case ZYDIS_CONVERSION_MODE_SINT8:
            ZYAN_CHECK(ZydisStringAppendC(string, " {sint8}"));
            break;
        case ZYDIS_CONVERSION_MODE_UINT8:
            ZYAN_CHECK(ZydisStringAppendC(string, " {uint8}"));
            break;
        case ZYDIS_CONVERSION_MODE_SINT16:
            ZYAN_CHECK(ZydisStringAppendC(string, " {sint16}"));
            break;
        case ZYDIS_CONVERSION_MODE_UINT16:
            ZYAN_CHECK(ZydisStringAppendC(string, " {uint16}"));
            break;
        default:
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_EH:
#if !defined(ZYDIS_DISABLE_MVEX)
        if (context->instruction->avx.hasEvictionHint)
        {
            ZYAN_CHECK(ZydisStringAppendC(string, " {eh}"));
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

    static ZydisString hexPrefixDefault = ZYDIS_MAKE_STRING("0x");

    ZYAN_MEMSET(formatter, 0, sizeof(ZydisFormatter));
    formatter->letterCase               = ZYDIS_LETTER_CASE_DEFAULT;
    formatter->forceMemorySegment       = ZYAN_FALSE;
    formatter->forceMemorySize          = ZYAN_FALSE;
    formatter->formatAddress            = ZYDIS_ADDR_FORMAT_ABSOLUTE;
    formatter->formatDisp               = ZYDIS_DISP_FORMAT_HEX_SIGNED;
    formatter->formatImm                = ZYDIS_IMM_FORMAT_HEX_UNSIGNED;
    formatter->hexUppercase             = ZYAN_TRUE;
    formatter->hexPrefix                = &hexPrefixDefault;
    formatter->hexSuffix                = ZYAN_NULL;
    formatter->hexPaddingAddress        = 2;
    formatter->hexPaddingDisp           = 2;
    formatter->hexPaddingImm            = 2;

    switch (style)
    {
    case ZYDIS_FORMATTER_STYLE_INTEL:
        formatter->funcPreInstruction       = ZYAN_NULL;
        formatter->funcPostInstruction      = ZYAN_NULL;
        formatter->funcPreOperand           = ZYAN_NULL;
        formatter->funcPostOperand          = ZYAN_NULL;
        formatter->funcFormatInstruction    = &ZydisFormatInstrIntel;
        formatter->funcFormatOperandReg     = &ZydisFormatOperandRegIntel;
        formatter->funcFormatOperandMem     = &ZydisFormatOperandMemIntel;
        formatter->funcFormatOperandPtr     = &ZydisFormatOperandPtrIntel;
        formatter->funcFormatOperandImm     = &ZydisFormatOperandImmIntel;
        formatter->funcPrintMnemonic        = &ZydisPrintMnemonicIntel;
        formatter->funcPrintRegister        = &ZydisPrintRegisterIntel;
        formatter->funcPrintAddress         = &ZydisPrintAddrIntel;
        formatter->funcPrintDisp            = &ZydisPrintDispIntel;
        formatter->funcPrintImm             = &ZydisPrintImmIntel;
        formatter->funcPrintMemSize         = &ZydisPrintMemSizeIntel;
        formatter->funcPrintPrefixes        = &ZydisPrintPrefixesIntel;
        formatter->funcPrintDecorator       = &ZydisPrintDecoratorIntel;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
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
        formatter->letterCase = (value) ? ZYDIS_LETTER_CASE_UPPER : ZYDIS_LETTER_CASE_DEFAULT;
        break;
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSEG:
        formatter->forceMemorySegment = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE:
        formatter->forceMemorySize = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_ADDR_FORMAT:
        if (value > ZYDIS_ADDR_FORMAT_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->formatAddress = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_DISP_FORMAT:
        if (value > ZYDIS_DISP_FORMAT_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->formatDisp = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_IMM_FORMAT:
        if (value > ZYDIS_IMM_FORMAT_MAX_VALUE)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->formatImm = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_UPPERCASE:
        formatter->hexUppercase = (value) ? ZYAN_TRUE : ZYAN_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
        formatter->hexPrefix = (value) ? &formatter->hexPrefixData : ZYAN_NULL;
        if (value)
        {
            return ZydisStringInit(&formatter->hexPrefixData, (char*)value);
        }
        break;
    case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
        formatter->hexSuffix = (value) ? &formatter->hexSuffixData : ZYAN_NULL;
        if (value)
        {
            return ZydisStringInit(&formatter->hexSuffixData, (char*)value);
        }
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_ADDR:
        if (value > 20)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->hexPaddingAddress = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_DISP:
        if (value > 20)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->hexPaddingDisp = (ZyanU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_IMM:
        if (value > 20)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        formatter->hexPaddingImm = (ZyanU8)value;
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
        *callback = *(const void**)&formatter->funcPreInstruction;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION:
        *callback = *(const void**)&formatter->funcPostInstruction;
        break;
    case ZYDIS_FORMATTER_HOOK_PRE_OPERAND:
        *callback = *(const void**)&formatter->funcPreOperand;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_OPERAND:
        *callback = *(const void**)&formatter->funcPostOperand;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        *callback = *(const void**)&formatter->funcFormatInstruction;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG:
        *callback = *(const void**)&formatter->funcFormatOperandReg;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM:
        *callback = *(const void**)&formatter->funcFormatOperandMem;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR:
        *callback = *(const void**)&formatter->funcFormatOperandPtr;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM:
        *callback = *(const void**)&formatter->funcFormatOperandImm;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC:
        *callback = *(const void**)&formatter->funcPrintMnemonic;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_REGISTER:
        *callback = *(const void**)&formatter->funcPrintRegister;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS:
        *callback = *(const void**)&formatter->funcPrintAddress;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DISP:
        *callback = *(const void**)&formatter->funcPrintDisp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMM:
        *callback = *(const void**)&formatter->funcPrintImm;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE:
        *callback = *(const void**)&formatter->funcPrintMemSize;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        *callback = *(const void**)&formatter->funcPrintPrefixes;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        *callback = *(const void**)&formatter->funcPrintDecorator;
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
        formatter->funcPreInstruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION:
        formatter->funcPostInstruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRE_OPERAND:
        formatter->funcPreOperand = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_OPERAND:
        formatter->funcPostOperand = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        formatter->funcFormatInstruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG:
        formatter->funcFormatOperandReg = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM:
        formatter->funcFormatOperandMem = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR:
        formatter->funcFormatOperandPtr = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM:
        formatter->funcFormatOperandImm = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC:
        formatter->funcPrintMnemonic = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_REGISTER:
        formatter->funcPrintRegister = *(ZydisFormatterRegisterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS:
        formatter->funcPrintAddress = *(ZydisFormatterAddressFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DISP:
        formatter->funcPrintDisp = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMM:
        formatter->funcPrintImm = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE:
        formatter->funcPrintMemSize = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        formatter->funcPrintPrefixes = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        formatter->funcPrintDecorator = *(ZydisFormatterDecoratorFunc*)&temp;
        break;
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZyanUSize bufferLen,
    ZyanU64 address)
{
    return ZydisFormatterFormatInstructionEx(formatter, instruction, buffer, bufferLen, address,
        ZYAN_NULL);
}

ZyanStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZyanUSize bufferLen,
    ZyanU64 address, void* userData)
{
    if (!formatter || !instruction || !buffer || (bufferLen == 0))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZydisString string;
    string.buffer   = buffer;
    string.length   = 0;
    string.capacity = bufferLen - 1;

    ZydisFormatterContext context;
    context.instruction = instruction;
    context.address = address;
    context.operand = ZYAN_NULL;
    context.userData = userData;

    const ZyanStatus status = ZydisFormatInstruction(formatter, &string, &context);

    buffer[string.length] = 0;

    if (status == ZYDIS_STATUS_SKIP_TOKEN)
    {
        return ZYAN_STATUS_SUCCESS;
    }
    return status;
}

ZyanStatus ZydisFormatterFormatOperand(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZyanU8 index, char* buffer, ZyanUSize bufferLen,
    ZyanU64 address)
{
    return ZydisFormatterFormatOperandEx(formatter, instruction, index, buffer, bufferLen,
        address, ZYAN_NULL);
}

ZyanStatus ZydisFormatterFormatOperandEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZyanU8 index, char* buffer, ZyanUSize bufferLen,
    ZyanU64 address, void* userData)
{
    if (!formatter || !instruction || index >= instruction->operandCount || !buffer ||
        (bufferLen == 0))
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZydisString string;
    string.buffer   = buffer;
    string.length   = 0;
    string.capacity = bufferLen - 1;

    ZydisFormatterContext context;
    context.instruction = instruction;
    context.address = address;
    context.operand = &instruction->operands[index];
    context.userData = userData;

    ZyanStatus status;
    if (formatter->funcPreOperand)
    {
        status = formatter->funcPreOperand(formatter, &string, &context);
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
        status = formatter->funcFormatOperandReg(formatter, &string, &context);
        break;
    case ZYDIS_OPERAND_TYPE_MEMORY:
        status = formatter->funcFormatOperandMem(formatter, &string, &context);
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        status = formatter->funcFormatOperandImm(formatter, &string, &context);
        break;
    case ZYDIS_OPERAND_TYPE_POINTER:
        status = formatter->funcFormatOperandPtr(formatter, &string, &context);
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

    if (formatter->funcPostOperand)
    {
        status = formatter->funcPostOperand(formatter, &string, &context);
        // Ignore `ZYDIS_STATUS_SKIP_TOKEN`
        if (status == ZYDIS_STATUS_SKIP_TOKEN)
        {
            status = ZYAN_STATUS_SUCCESS;
        }
    }

FinalizeString:
    buffer[string.length] = 0;
    return status;
}

/* ============================================================================================== */
