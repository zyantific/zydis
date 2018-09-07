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

#include <Zydis/CommonTypes.h>
#include <Zydis/Formatter.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Internal functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* General                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatInstruction(const ZydisFormatter* formatter, const
    ZydisDecodedInstruction* instruction, ZydisString* string, void* userData)
{
    if (formatter->funcPreInstruction)
    {
        ZYDIS_CHECK(formatter->funcPreInstruction(formatter, string, instruction, userData));
    }

    ZYDIS_CHECK(formatter->funcFormatInstruction(formatter, string, instruction, userData));

    if (formatter->funcPostInstruction)
    {
        return formatter->funcPostInstruction(formatter, string, instruction, userData);
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Intel style                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatInstrIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, void* userData)
{
    if (!formatter || !string || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZYDIS_CHECK(formatter->funcPrintPrefixes(formatter, string, instruction, userData));
    ZYDIS_CHECK(formatter->funcPrintMnemonic(formatter, string, instruction, userData));

    const ZydisUSize strLenMnemonic = string->length;
    for (ZydisU8 i = 0; i < instruction->operandCount; ++i)
    {
        if (instruction->operands[i].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        const ZydisUSize strLenRestore = string->length;
        if (string->length == strLenMnemonic)
        {
            ZYDIS_CHECK(ZydisStringAppendC(string, " "));
        } else
        {
            ZYDIS_CHECK(ZydisStringAppendC(string, ", "));
        }

        const ZydisUSize strLenPreOperand = string->length;

        // Print embedded-mask registers as decorator instead of a regular operand
        if ((i == 1) && (instruction->operands[i].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
            (instruction->operands[i].encoding == ZYDIS_OPERAND_ENCODING_MASK))
        {
            goto SkipOperand;
        }

        ZydisStatus status;
        if (formatter->funcPreOperand)
        {
            status = formatter->funcPreOperand(formatter, string, instruction,
                &instruction->operands[i], userData);
            if (status == ZYDIS_STATUS_SKIP_OPERAND)
            {
                goto SkipOperand;
            }
            if (status != ZYDIS_STATUS_SUCCESS)
            {
                return status;
            }
        }

        switch (instruction->operands[i].type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            status = formatter->funcFormatOperandReg(formatter, string, instruction,
                &instruction->operands[i], userData);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
        {
            status = formatter->funcFormatOperandMem(formatter, string, instruction,
                &instruction->operands[i], userData);
            break;
        }
        case ZYDIS_OPERAND_TYPE_POINTER:
            status = formatter->funcFormatOperandPtr(formatter, string, instruction,
                &instruction->operands[i], userData);
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            status = formatter->funcFormatOperandImm(formatter, string, instruction,
                &instruction->operands[i], userData);
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        if (status == ZYDIS_STATUS_SKIP_OPERAND)
        {
            goto SkipOperand;
        }
        if (status != ZYDIS_STATUS_SUCCESS)
        {
            return status;
        }

        if (formatter->funcPostOperand)
        {
            status = formatter->funcPostOperand(formatter, string, instruction,
                &instruction->operands[i], userData);
            if (status == ZYDIS_STATUS_SKIP_OPERAND)
            {
                goto SkipOperand;
            }
            if (status != ZYDIS_STATUS_SUCCESS)
            {
                return status;
            }
        }

        if (strLenPreOperand == string->length)
        {
SkipOperand:
            // Omit whole operand, if the string did not change during the formatting-callback
            string->length = strLenRestore;

            if (formatter->funcPostOperand)
            {
                formatter->funcPostOperand(formatter, string, instruction,
                    &instruction->operands[i], userData);
            }

            continue;
        }

        if ((instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
            (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX))
        {
            if  ((i == 0) &&
                    (instruction->operands[i + 1].encoding == ZYDIS_OPERAND_ENCODING_MASK))
            {
                ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                    &instruction->operands[i], ZYDIS_DECORATOR_TYPE_MASK, userData));
            }
            if (instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                    &instruction->operands[i], ZYDIS_DECORATOR_TYPE_BC, userData));
                if (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                {
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                        &instruction->operands[i], ZYDIS_DECORATOR_TYPE_CONVERSION, userData));
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                        &instruction->operands[i], ZYDIS_DECORATOR_TYPE_EH, userData));
                }
            } else
            {
                if ((i == (instruction->operandCount - 1)) ||
                    (instruction->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
                {
                    if (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                            &instruction->operands[i], ZYDIS_DECORATOR_TYPE_SWIZZLE, userData));
                    }
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                        &instruction->operands[i], ZYDIS_DECORATOR_TYPE_RC, userData));
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, string, instruction,
                        &instruction->operands[i], ZYDIS_DECORATOR_TYPE_SAE, userData));
                }
            }
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatOperandRegIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    if (!operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return formatter->funcPrintRegister(formatter, string, instruction, operand,
        operand->reg.value, userData);
}

static ZydisStatus ZydisFormatOperandMemIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    if (!formatter || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZYDIS_CHECK(formatter->funcPrintMemSize(formatter, string, instruction, operand, userData));

    const ZydisUSize lenPreSegment = string->length;
    switch (operand->mem.segment)
    {
    case ZYDIS_REGISTER_ES:
    case ZYDIS_REGISTER_CS:
    case ZYDIS_REGISTER_FS:
    case ZYDIS_REGISTER_GS:
        ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
            operand->mem.segment, userData));
        break;
    case ZYDIS_REGISTER_SS:
        if ((formatter->forceMemorySegment) ||
            (instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
                operand->mem.segment, userData));
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->forceMemorySegment) ||
            (instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
                operand->mem.segment, userData));
        }
        break;
    default:
        break;
    }
    // TODO: Rename ZYDIS_STATUS_SKIP_OPERAND to ZYDIS_STATUS_SKIP_TOKEN and use it in this case
    if (string->length > lenPreSegment)
    {
        ZYDIS_CHECK(ZydisStringAppendC(string, ":"));
    }

    ZYDIS_CHECK(ZydisStringAppendC(string, "["));

    if (operand->mem.disp.hasDisplacement && (
        (operand->mem.base == ZYDIS_REGISTER_NONE) ||
        (operand->mem.base == ZYDIS_REGISTER_EIP) ||
        (operand->mem.base == ZYDIS_REGISTER_RIP)) &&
        (operand->mem.index == ZYDIS_REGISTER_NONE) && (operand->mem.scale == 0))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        if ((formatter->formatAddress == ZYDIS_ADDR_FORMAT_ABSOLUTE) ||
            (operand->mem.base == ZYDIS_REGISTER_NONE))
        {
            ZydisU64 address;
            ZYDIS_CHECK(ZydisCalcAbsoluteAddress(instruction, operand, &address));
            ZYDIS_CHECK(formatter->funcPrintAddress(formatter, string, instruction, operand,
                address, userData));
        } else
        {
            ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
                operand->mem.base, userData));
            ZYDIS_CHECK(formatter->funcPrintDisp(formatter, string, instruction, operand,
                userData));
        }
    } else
    {
        // Regular memory operand
        if (operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
                operand->mem.base, userData));
        }
        if ((operand->mem.index != ZYDIS_REGISTER_NONE) &&
            (operand->mem.type != ZYDIS_MEMOP_TYPE_MIB))
        {
            if (operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYDIS_CHECK(ZydisStringAppendC(string, "+"));
            }
            ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
                operand->mem.index, userData));
            if (operand->mem.scale)
            {
                ZYDIS_CHECK(ZydisStringAppendC(string, "*"));
                ZYDIS_CHECK(ZydisStringAppendDecU(string, operand->mem.scale, 0));
            }
        }
        ZYDIS_CHECK(formatter->funcPrintDisp(formatter, string, instruction, operand, userData));
    }

    return ZydisStringAppendC(string, "]");
}

static ZydisStatus ZydisFormatOperandPtrIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(instruction);
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZYDIS_CHECK(ZydisStringAppendHexU(string, operand->ptr.segment, 4,
        formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix));
    ZYDIS_CHECK(ZydisStringAppendC(string, ":"));
    return ZydisStringAppendHexU(string, operand->ptr.offset, 8,
        formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
}

static ZydisStatus ZydisFormatOperandImmIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    if (!formatter || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    // The immediate operand contains an address
    if (operand->imm.isRelative)
    {
        ZydisBool printSignedHEX = ZYDIS_FALSE;
        switch (formatter->formatAddress)
        {
        case ZYDIS_ADDR_FORMAT_ABSOLUTE:
        {
            ZydisU64 address;
            ZYDIS_CHECK(ZydisCalcAbsoluteAddress(instruction, operand, &address));
            return formatter->funcPrintAddress(formatter, string, instruction, operand, address,
                userData);
        }
        case ZYDIS_ADDR_FORMAT_RELATIVE_SIGNED:
            printSignedHEX = ZYDIS_TRUE;
            break;
        case ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED:
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }

        if (printSignedHEX)
        {
            return ZydisStringAppendHexS(string, (ZydisI32)operand->imm.value.s,
                formatter->hexPaddingAddress, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        }
        return ZydisStringAppendHexU(string, operand->imm.value.u,
            formatter->hexPaddingAddress, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->funcPrintImm(formatter, string, instruction, operand, userData);
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisPrintMnemonicIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const ZydisStaticString* mnemonic = ZydisMnemonicGetStaticString(instruction->mnemonic);
    if (!mnemonic)
    {
        return ZydisStringAppendExC(string, "invalid", formatter->letterCase);
    }
    ZYDIS_CHECK(ZydisStringAppendExStatic(string, mnemonic, formatter->letterCase));

    if (instruction->attributes & ZYDIS_ATTRIB_IS_FAR_BRANCH)
    {
        return ZydisStringAppendExC(string, " far", formatter->letterCase);
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrintRegisterIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand,
    ZydisRegister reg, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(instruction);
    ZYDIS_UNUSED_PARAMETER(operand);
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const ZydisStaticString* str = ZydisRegisterGetStaticString(reg);
    if (!str)
    {
        return ZydisStringAppendExC(string, "invalid", formatter->letterCase);
    }
    return ZydisStringAppendExStatic(string, str, formatter->letterCase);
}

static ZydisStatus ZydisPrintAddrIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand,
    ZydisU64 address, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(operand);
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (instruction->stackWidth)
    {
    case 16:
        return ZydisStringAppendHexU(string, (ZydisU16)address, 4,
            formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
    case 32:
        return ZydisStringAppendHexU(string, (ZydisU32)address, 8,
            formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
    case 64:
        return ZydisStringAppendHexU(string, address, 16,
            formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

static ZydisStatus ZydisPrintDispIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(instruction);
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (operand->mem.disp.hasDisplacement && ((operand->mem.disp.value) ||
        ((operand->mem.base == ZYDIS_REGISTER_NONE) &&
        (operand->mem.index == ZYDIS_REGISTER_NONE))))
    {
        const ZydisBool printSignedHEX = (formatter->formatDisp != ZYDIS_DISP_FORMAT_HEX_UNSIGNED);
        if (printSignedHEX && (operand->mem.disp.value < 0) && (
            (operand->mem.base != ZYDIS_REGISTER_NONE) ||
            (operand->mem.index != ZYDIS_REGISTER_NONE)))
        {
            return ZydisStringAppendHexS(string, operand->mem.disp.value, formatter->hexPaddingDisp,
                formatter->hexUppercase, formatter->hexPrefix, formatter->hexSuffix);
        }
        if ((operand->mem.base != ZYDIS_REGISTER_NONE) ||
            (operand->mem.index != ZYDIS_REGISTER_NONE))
        {
            ZYDIS_CHECK(ZydisStringAppendC(string, "+"));
        }
        return ZydisStringAppendHexU(string, (ZydisU64)operand->mem.disp.value,
            formatter->hexPaddingDisp, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrintImmIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisBool printSignedHEX = (formatter->formatImm == ZYDIS_IMM_FORMAT_HEX_SIGNED);
    if (formatter->formatImm == ZYDIS_IMM_FORMAT_HEX_AUTO)
    {
        printSignedHEX = operand->imm.isSigned;
    }

    if (printSignedHEX && (operand->imm.value.s < 0))
    {
        switch (operand->size)
        {
        case 8:
            return ZydisStringAppendHexS(string, (ZydisI8)operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        case 16:
            return ZydisStringAppendHexS(string, (ZydisI16)operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        case 32:
            return ZydisStringAppendHexS(string, (ZydisI32)operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        case 64:
            return ZydisStringAppendHexS(string, operand->imm.value.s,
                formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
                formatter->hexSuffix);
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
    }
    switch (instruction->operandWidth)
    {
    case 8:
        return ZydisStringAppendHexU(string, (ZydisU8)operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    case 16:
        return ZydisStringAppendHexU(string, (ZydisU16)operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    case 32:
        return ZydisStringAppendHexU(string, (ZydisU32)operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    case 64:
        return ZydisStringAppendHexU(string, operand->imm.value.u,
            formatter->hexPaddingImm, formatter->hexUppercase, formatter->hexPrefix,
            formatter->hexSuffix);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

static ZydisStatus ZydisPrintMemSizeIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    // TODO: refactor

    ZydisU32 typecast = 0;
    if (formatter->forceMemorySize)
    {
        if ((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) &&
            (operand->mem.type == ZYDIS_MEMOP_TYPE_MEM))
        {
            typecast = instruction->operands[operand->id].size;
        }
    } else
    if ((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) &&
        (operand->mem.type == ZYDIS_MEMOP_TYPE_MEM))
    {
        switch (operand->id)
        {
        case 0:
            typecast =
                ((instruction->operands[1].type == ZYDIS_OPERAND_TYPE_UNUSED) ||
                 (instruction->operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) ||
                 (instruction->operands[0].size != instruction->operands[1].size)) ?
                    instruction->operands[0].size : 0;
            if (!typecast &&
                (instruction->operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) &&
                (instruction->operands[1].reg.value == ZYDIS_REGISTER_CL))
            {
                switch (instruction->mnemonic)
                {
                case ZYDIS_MNEMONIC_RCL:
                case ZYDIS_MNEMONIC_ROL:
                case ZYDIS_MNEMONIC_ROR:
                case ZYDIS_MNEMONIC_RCR:
                case ZYDIS_MNEMONIC_SHL:
                case ZYDIS_MNEMONIC_SHR:
                case ZYDIS_MNEMONIC_SAR:
                    typecast = instruction->operands[0].size;
                default:
                    break;
                }
            }
            break;
        case 1:
        case 2:
            typecast =
                (instruction->operands[operand->id - 1].size !=
                    instruction->operands[operand->id].size) ?
                    instruction->operands[operand->id].size : 0;
            break;
        default:
            break;
        }
    }
    if (typecast)
    {
        const char* str = ZYDIS_NULL;
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

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisPrintPrefixesIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, void* userData)
{
    ZYDIS_UNUSED_PARAMETER(userData);

    if (!formatter || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
    {
        ZYDIS_CHECK(ZydisStringAppendExC(string, "xacquire ", formatter->letterCase));
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        ZYDIS_CHECK(ZydisStringAppendExC(string, "xrelease ", formatter->letterCase));
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        return ZydisStringAppendExC(string, "lock ", formatter->letterCase);
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        return ZydisStringAppendExC(string, "rep ", formatter->letterCase);
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        return ZydisStringAppendExC(string, "repe ", formatter->letterCase);
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        return ZydisStringAppendExC(string, "repne ", formatter->letterCase);
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_BOUND)
    {
        return ZydisStringAppendExC(string, "bnd ", formatter->letterCase);
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisPrintDecoratorIntel(const ZydisFormatter* formatter, ZydisString* string,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operand,
    ZydisDecoratorType type, void* userData)
{
    if (!formatter || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (type)
    {
    case ZYDIS_DECORATOR_TYPE_MASK:
    {
#if !defined(ZYDIS_DISABLE_EVEX) || !defined(ZYDIS_DISABLE_MVEX)
        if (instruction->avx.mask.reg != ZYDIS_REGISTER_K0)
        {
            ZYDIS_CHECK(ZydisStringAppendC(string, " {"));
            ZYDIS_CHECK(formatter->funcPrintRegister(formatter, string, instruction, operand,
                instruction->avx.mask.reg, userData));
            ZYDIS_CHECK(ZydisStringAppendC(string, "}"));
            if (instruction->avx.mask.mode == ZYDIS_MASK_MODE_ZERO)
            {
                ZYDIS_CHECK(ZydisStringAppendC(string, " {z}"));
            }
        }
#endif
        break;
    }
    case ZYDIS_DECORATOR_TYPE_BC:
#if !defined(ZYDIS_DISABLE_EVEX)
        if (!instruction->avx.broadcast.isStatic)
        {
            switch (instruction->avx.broadcast.mode)
            {
            case ZYDIS_BROADCAST_MODE_INVALID:
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_2:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {1to2}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_4:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {1to4}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_8:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {1to8}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_16:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {1to16}"));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_8:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {4to8}"));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_16:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {4to16}"));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_RC:
#if !defined(ZYDIS_DISABLE_EVEX)
        if (instruction->avx.hasSAE)
        {
            switch (instruction->avx.rounding.mode)
            {
            case ZYDIS_ROUNDING_MODE_INVALID:
                break;
            case ZYDIS_ROUNDING_MODE_RN:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {rn-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {rd-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {ru-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {rz-sae}"));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        } else
        {
            switch (instruction->avx.rounding.mode)
            {
            case ZYDIS_ROUNDING_MODE_INVALID:
                break;
            case ZYDIS_ROUNDING_MODE_RN:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {rn}"));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {rd}"));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {ru}"));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_CHECK(ZydisStringAppendC(string, " {rz}"));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_SAE:
#if !defined(ZYDIS_DISABLE_EVEX)
        if (instruction->avx.hasSAE && !instruction->avx.rounding.mode)
        {
            ZYDIS_CHECK(ZydisStringAppendC(string, " {sae}"));
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_SWIZZLE:
#if !defined(ZYDIS_DISABLE_MVEX)
        switch (instruction->avx.swizzle.mode)
        {
        case ZYDIS_SWIZZLE_MODE_INVALID:
        case ZYDIS_SWIZZLE_MODE_DCBA:
            // Nothing to do here
            break;
        case ZYDIS_SWIZZLE_MODE_CDAB:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {cdab}"));
            break;
        case ZYDIS_SWIZZLE_MODE_BADC:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {badc}"));
            break;
        case ZYDIS_SWIZZLE_MODE_DACB:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {dacb}"));
            break;
        case ZYDIS_SWIZZLE_MODE_AAAA:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {aaaa}"));
            break;
        case ZYDIS_SWIZZLE_MODE_BBBB:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {bbbb}"));
            break;
        case ZYDIS_SWIZZLE_MODE_CCCC:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {cccc}"));
            break;
        case ZYDIS_SWIZZLE_MODE_DDDD:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {dddd}"));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_CONVERSION:
#if !defined(ZYDIS_DISABLE_MVEX)
        switch (instruction->avx.conversion.mode)
        {
        case ZYDIS_CONVERSION_MODE_INVALID:
            break;
        case ZYDIS_CONVERSION_MODE_FLOAT16:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {float16}"));
            break;
        case ZYDIS_CONVERSION_MODE_SINT8:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {sint8}"));
            break;
        case ZYDIS_CONVERSION_MODE_UINT8:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {uint8}"));
            break;
        case ZYDIS_CONVERSION_MODE_SINT16:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {sint16}"));
            break;
        case ZYDIS_CONVERSION_MODE_UINT16:
            ZYDIS_CHECK(ZydisStringAppendC(string, " {uint16}"));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
#endif
        break;
    case ZYDIS_DECORATOR_TYPE_EH:
#if !defined(ZYDIS_DISABLE_MVEX)
        if (instruction->avx.hasEvictionHint)
        {
            ZYDIS_CHECK(ZydisStringAppendC(string, " {eh}"));
        }
#endif
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZydisStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style)
{
    if (!formatter)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    static ZydisString hexPrefixDefault = ZYDIS_MAKE_STRING("0x");

    ZydisMemorySet(formatter, 0, sizeof(ZydisFormatter));
    formatter->letterCase               = ZYDIS_LETTER_CASE_DEFAULT;
    formatter->forceMemorySegment       = ZYDIS_FALSE;
    formatter->forceMemorySize          = ZYDIS_FALSE;
    formatter->formatAddress            = ZYDIS_ADDR_FORMAT_ABSOLUTE;
    formatter->formatDisp               = ZYDIS_DISP_FORMAT_HEX_SIGNED;
    formatter->formatImm                = ZYDIS_IMM_FORMAT_HEX_UNSIGNED;
    formatter->hexUppercase             = ZYDIS_TRUE;
    formatter->hexPrefix                = &hexPrefixDefault;
    formatter->hexSuffix                = ZYDIS_NULL;
    formatter->hexPaddingAddress        = 2;
    formatter->hexPaddingDisp           = 2;
    formatter->hexPaddingImm            = 2;

    switch (style)
    {
    case ZYDIS_FORMATTER_STYLE_INTEL:
        formatter->funcPreInstruction       = ZYDIS_NULL;
        formatter->funcPostInstruction      = ZYDIS_NULL;
        formatter->funcPreOperand           = ZYDIS_NULL;
        formatter->funcPostOperand          = ZYDIS_NULL;
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
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisFormatterSetProperty(ZydisFormatter* formatter,
    ZydisFormatterProperty property, ZydisUPointer value)
{
    if (!formatter)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (property)
    {
    case ZYDIS_FORMATTER_PROP_UPPERCASE:
        formatter->letterCase = (value) ? ZYDIS_LETTER_CASE_UPPER : ZYDIS_LETTER_CASE_DEFAULT;
        break;
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSEG:
        formatter->forceMemorySegment = (value) ? ZYDIS_TRUE : ZYDIS_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE:
        formatter->forceMemorySize = (value) ? ZYDIS_TRUE : ZYDIS_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_ADDR_FORMAT:
        if (value > ZYDIS_ADDR_FORMAT_MAX_VALUE)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        formatter->formatAddress = (ZydisU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_DISP_FORMAT:
        if (value > ZYDIS_DISP_FORMAT_MAX_VALUE)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        formatter->formatDisp = (ZydisU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_IMM_FORMAT:
        if (value > ZYDIS_IMM_FORMAT_MAX_VALUE)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        formatter->formatImm = (ZydisU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_UPPERCASE:
        formatter->hexUppercase = (value) ? ZYDIS_TRUE : ZYDIS_FALSE;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
        formatter->hexPrefix = (value) ? &formatter->hexPrefixData : ZYDIS_NULL;
        if (value)
        {
            return ZydisStringInit(&formatter->hexPrefixData, (char*)value);
        }
        break;
    case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
        formatter->hexSuffix = (value) ? &formatter->hexSuffixData : ZYDIS_NULL;
        if (value)
        {
            return ZydisStringInit(&formatter->hexSuffixData, (char*)value);
        }
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_ADDR:
        if (value > 20)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        formatter->hexPaddingAddress = (ZydisU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_DISP:
        if (value > 20)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        formatter->hexPaddingDisp = (ZydisU8)value;
        break;
    case ZYDIS_FORMATTER_PROP_HEX_PADDING_IMM:
        if (value > 20)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        formatter->hexPaddingImm = (ZydisU8)value;
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisFormatterSetHook(ZydisFormatter* formatter, ZydisFormatterHookType hook,
    const void** callback)
{
    if (!formatter || !callback)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
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
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    // The function was used to get the current function-pointer without replacing it
    if (!temp)
    {
        return ZYDIS_STATUS_SUCCESS;
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
        formatter->funcPreOperand = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_POST_OPERAND:
        formatter->funcPostOperand = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        formatter->funcFormatInstruction = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG:
        formatter->funcFormatOperandReg = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM:
        formatter->funcFormatOperandMem = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR:
        formatter->funcFormatOperandPtr = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM:
        formatter->funcFormatOperandImm = *(ZydisFormatterOperandFunc*)&temp;
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
        formatter->funcPrintDisp = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMM:
        formatter->funcPrintImm = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE:
        formatter->funcPrintMemSize = *(ZydisFormatterOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        formatter->funcPrintPrefixes = *(ZydisFormatterFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        formatter->funcPrintDecorator = *(ZydisFormatterDecoratorFunc*)&temp;
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZydisUSize bufferLen)
{
    return ZydisFormatterFormatInstructionEx(formatter, instruction, buffer, bufferLen, ZYDIS_NULL);
}

ZydisStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZydisUSize bufferLen, void* userData)
{
    if (!formatter || !instruction || !buffer || (bufferLen == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisString string;
    string.buffer   = buffer;
    string.length   = 0;
    string.capacity = bufferLen - 1;

    const ZydisStatus status = ZydisFormatInstruction(formatter, instruction, &string, userData);

    buffer[string.length] = 0;

    if (status == ZYDIS_STATUS_SKIP_OPERAND)
    {
        return ZYDIS_STATUS_SUCCESS;
    }
    return status;
}

ZydisStatus ZydisFormatterFormatOperand(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZydisU8 index, char* buffer, ZydisUSize bufferLen)
{
    return ZydisFormatterFormatOperandEx(
        formatter, instruction, index, buffer, bufferLen, ZYDIS_NULL);
}

ZydisStatus ZydisFormatterFormatOperandEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZydisU8 index, char* buffer, ZydisUSize bufferLen,
    void* userData)
{
    if (!formatter || !instruction || index >= instruction->operandCount || !buffer ||
        (bufferLen == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisString string;
    string.buffer   = buffer;
    string.length   = 0;
    string.capacity = bufferLen - 1;

    ZydisStatus status;
    const ZydisDecodedOperand* operand = &instruction->operands[index];

    if (formatter->funcPreOperand)
    {
        status = formatter->funcPreOperand(formatter, &string, instruction, operand, userData);
        // We ignore `ZYDIS_STATUS_SKIP_OPERAND` as it does not make any sense to skip the only
        // operand printed by this function
        if ((status != ZYDIS_STATUS_SUCCESS) && (status != ZYDIS_STATUS_SKIP_OPERAND))
        {
            goto FinalizeString;
        }
    }

    switch (operand->type)
    {
    case ZYDIS_OPERAND_TYPE_REGISTER:
        status = formatter->funcFormatOperandReg(formatter, &string, instruction, operand,
            userData);
        break;
    case ZYDIS_OPERAND_TYPE_MEMORY:
        status = formatter->funcFormatOperandMem(formatter, &string, instruction, operand,
            userData);
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        status = formatter->funcFormatOperandImm(formatter, &string, instruction, operand,
            userData);
        break;
    case ZYDIS_OPERAND_TYPE_POINTER:
        status = formatter->funcFormatOperandPtr(formatter, &string, instruction, operand,
            userData);
        break;
    default:
        status = ZYDIS_STATUS_INVALID_PARAMETER;
        break;
    }
    // Ignore `ZYDIS_STATUS_SKIP_OPERAND`
    if (status == ZYDIS_STATUS_SKIP_OPERAND)
    {
        status = ZYDIS_STATUS_SUCCESS;
    }
    if (!ZYDIS_SUCCESS(status))
    {
        goto FinalizeString;
    }

    // TODO: Print AVX512/KNC decorator

    if (formatter->funcPostOperand)
    {
        status = formatter->funcPostOperand(formatter, &string, instruction, operand, userData);
        // Ignore `ZYDIS_STATUS_SKIP_OPERAND`
        if (status == ZYDIS_STATUS_SKIP_OPERAND)
        {
            status = ZYDIS_STATUS_SUCCESS;
        }
    }

FinalizeString:
    buffer[string.length] = 0;
    return status;
}

/* ============================================================================================== */
