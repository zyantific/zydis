/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd

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

#include <string.h>
#include <Zydis/CommonTypes.h>
#include <Zydis/Formatter.h>
#include <Zydis/Utils.h>
#include <FormatHelper.h>

/* ============================================================================================== */
/* Instruction formatter                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internal macros                                                                                */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_LETTER_CASE \
    (formatter->flags & ZYDIS_FMTFLAG_UPPERCASE) ? \
        ZYDIS_LETTER_CASE_UPPER : ZYDIS_LETTER_CASE_DEFAULT

/* ---------------------------------------------------------------------------------------------- */
/* Intel style                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintPrefixesIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        return ZydisPrintStr(buffer, bufferLen, "lock ", ZYDIS_LETTER_CASE);
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        return ZydisPrintStr(buffer, bufferLen, "rep ", ZYDIS_LETTER_CASE);
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        return ZydisPrintStr(buffer, bufferLen, "repe ", ZYDIS_LETTER_CASE);
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        return ZydisPrintStr(buffer, bufferLen, "repne ", ZYDIS_LETTER_CASE);
    } 
   
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_BOUND)
    {
        return ZydisPrintStr(buffer, bufferLen, "bnd ", ZYDIS_LETTER_CASE);
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
    {
        return ZydisPrintStr(buffer, bufferLen, "xacquire ", ZYDIS_LETTER_CASE);
    } 
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        return ZydisPrintStr(buffer, bufferLen, "xrelease ", ZYDIS_LETTER_CASE);
    } 

    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisFormatterPrintMnemonicIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;

    const char* mnemonic = ZydisMnemonicGetString(instruction->mnemonic);
    if (!mnemonic)
    {
        mnemonic = "invalid";
    }
    ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, mnemonic, ZYDIS_LETTER_CASE));
    
    if (instruction->attributes & ZYDIS_ATTRIB_IS_FAR_BRANCH)
    {
        return ZydisPrintStr(buffer, bufEnd - *buffer, " far", ZYDIS_LETTER_CASE);
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterFormatOperandRegIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if ((operand->id == 1) && (operand->encoding == ZYDIS_OPERAND_ENCODING_MASK))
    {
        return ZYDIS_STATUS_SUCCESS;
    }

    const char* reg = ZydisRegisterGetString(operand->reg.value);
    if (!reg)
    {
        reg = "invalid";
    }
    return ZydisPrintStr(buffer, bufferLen, reg, ZYDIS_LETTER_CASE);
}

static ZydisStatus ZydisFormatterFormatOperandMemIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;

    ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, "[", ZYDIS_LETTER_CASE_DEFAULT));
 
    if (operand->mem.disp.hasDisplacement && (
        (operand->mem.base == ZYDIS_REGISTER_NONE) ||
        (operand->mem.base == ZYDIS_REGISTER_EIP) || 
        (operand->mem.base == ZYDIS_REGISTER_RIP)) &&
        (operand->mem.index == ZYDIS_REGISTER_NONE) && (operand->mem.scale == 0))
    {
        // EIP/RIP-relative or absolute-displacement address operand
        if ((formatter->addressFormat == ZYDIS_FORMATTER_ADDR_DEFAULT) ||
            (formatter->addressFormat == ZYDIS_FORMATTER_ADDR_ABSOLUTE) ||
            (operand->mem.base == ZYDIS_REGISTER_NONE))
        {
            uint64_t address;
            ZYDIS_CHECK(ZydisCalcAbsoluteAddress(instruction, operand, &address));
            ZYDIS_CHECK(formatter->funcPrintAddress(formatter, buffer, bufEnd - *buffer, 
                instruction, operand, address, userData));  
        } else
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, 
                ZydisRegisterGetString(operand->mem.base), ZYDIS_LETTER_CASE));
            ZYDIS_CHECK(formatter->funcPrintDisplacement(formatter, buffer, bufEnd - *buffer,
                instruction, operand, userData)); 
        }
    } else
    {
        // Regular memory operand
        if (operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            const char* reg = ZydisRegisterGetString(operand->mem.base);
            if (!reg)
            {
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, reg, ZYDIS_LETTER_CASE)); 
        }
        if (operand->mem.index != ZYDIS_REGISTER_NONE)
        {
            const char* reg = ZydisRegisterGetString(operand->mem.index);
            if (!reg)
            {
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
            if (operand->mem.base != ZYDIS_REGISTER_NONE)
            {
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, "+", ZYDIS_LETTER_CASE_DEFAULT));
            }
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, reg, ZYDIS_LETTER_CASE));
            if (operand->mem.scale)
            {
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, "*", ZYDIS_LETTER_CASE_DEFAULT));
                ZYDIS_CHECK(ZydisPrintDecU(buffer, bufEnd - *buffer, operand->mem.scale, 0));   
            }
        }
        ZYDIS_CHECK(formatter->funcPrintDisplacement(formatter, buffer, bufEnd - *buffer,
            instruction, operand, userData)); 
    }

    return ZydisPrintStr(buffer, bufEnd - *buffer, "]", ZYDIS_LETTER_CASE_DEFAULT);
}

static ZydisStatus ZydisFormatterFormatOperandPtrIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;
    ZYDIS_CHECK(ZydisPrintHexU(
        buffer, bufEnd - *buffer, operand->ptr.segment, 4, ZYDIS_TRUE, ZYDIS_TRUE));
    ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, ":", ZYDIS_LETTER_CASE_DEFAULT));
    return ZydisPrintHexU(
        buffer, bufEnd - *buffer, operand->ptr.offset, 8, ZYDIS_TRUE, ZYDIS_TRUE);
}

static ZydisStatus ZydisFormatterFormatOperandImmIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    // The immediate operand contains an address
    if (operand->imm.isRelative)
    {
        ZydisBool printSignedHEX = ZYDIS_FALSE;
        switch (formatter->addressFormat)
        {
        case ZYDIS_FORMATTER_ADDR_DEFAULT:
        case ZYDIS_FORMATTER_ADDR_ABSOLUTE:
        {
            uint64_t address;
            ZYDIS_CHECK(ZydisCalcAbsoluteAddress(instruction, operand, &address));
            return formatter->funcPrintAddress(formatter, buffer, bufferLen, instruction, operand, 
                address, userData);
        }
        case ZYDIS_FORMATTER_ADDR_RELATIVE_SIGNED:
            printSignedHEX = ZYDIS_TRUE;
            break;
        case ZYDIS_FORMATTER_ADDR_RELATIVE_UNSIGNED:
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        
        if (printSignedHEX)
        {
            return ZydisPrintHexS(
                buffer, bufferLen, (int32_t)operand->imm.value.s, 2, ZYDIS_TRUE, ZYDIS_TRUE);
        }
        return ZydisPrintHexU(buffer, bufferLen, operand->imm.value.u, 2, ZYDIS_TRUE, ZYDIS_TRUE);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->funcPrintImmediate(
        formatter, buffer, bufferLen, instruction, operand, userData);
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintAddressIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, uint64_t address, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (instruction->stackWidth)
    {
    case 16:
        return ZydisPrintHexU(buffer, bufferLen, (uint16_t)address, 4, ZYDIS_TRUE, ZYDIS_TRUE);
    case 32:
        return ZydisPrintHexU(buffer, bufferLen, (uint32_t)address, 8, ZYDIS_TRUE, ZYDIS_TRUE);
    case 64:
        return ZydisPrintHexU(buffer, bufferLen, address, 16, ZYDIS_TRUE, ZYDIS_TRUE);  
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

static ZydisStatus ZydisFormatterPrintDisplacementIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (operand->mem.disp.hasDisplacement && ((operand->mem.disp.value) || 
        ((operand->mem.base == ZYDIS_REGISTER_NONE) && 
        (operand->mem.index == ZYDIS_REGISTER_NONE))))
    {
        ZydisBool printSignedHEX = 
            (formatter->displacementFormat != ZYDIS_FORMATTER_DISP_HEX_UNSIGNED);
        if (printSignedHEX && (operand->mem.disp.value < 0) && (
            (operand->mem.base != ZYDIS_REGISTER_NONE) || 
            (operand->mem.index != ZYDIS_REGISTER_NONE)))
        {
            return ZydisPrintHexS(
                buffer, bufferLen, operand->mem.disp.value, 2, ZYDIS_TRUE, ZYDIS_TRUE);     
        }
        char* bufEnd = *buffer + bufferLen;
        if ((operand->mem.base != ZYDIS_REGISTER_NONE) || 
            (operand->mem.index != ZYDIS_REGISTER_NONE))
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "+", ZYDIS_LETTER_CASE_DEFAULT));
        }
        return ZydisPrintHexU(
            buffer, bufEnd - *buffer, (uint64_t)operand->mem.disp.value, 2, ZYDIS_TRUE, ZYDIS_TRUE); 
    }
    return ZYDIS_STATUS_SUCCESS; 
}

static ZydisStatus ZydisFormatterPrintImmediateIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisBool printSignedHEX = (formatter->immediateFormat == ZYDIS_FORMATTER_IMM_HEX_SIGNED);
    if (formatter->immediateFormat == ZYDIS_FORMATTER_IMM_HEX_AUTO)
    {
        printSignedHEX = operand->imm.isSigned;    
    }

    if (printSignedHEX && (operand->imm.value.s < 0))
    {
        switch (operand->size)
        {
        case 8:
            return ZydisPrintHexS(
                buffer, bufferLen, (int8_t)operand->imm.value.s, 2, ZYDIS_TRUE, ZYDIS_TRUE);
        case 16:
            return ZydisPrintHexS(
                buffer, bufferLen, (int16_t)operand->imm.value.s, 2, ZYDIS_TRUE, ZYDIS_TRUE);
        case 32:
            return ZydisPrintHexS(
                buffer, bufferLen, (int32_t)operand->imm.value.s, 2, ZYDIS_TRUE, ZYDIS_TRUE);
        case 64:
            return ZydisPrintHexS(
                buffer, bufferLen, operand->imm.value.s, 2, ZYDIS_TRUE, ZYDIS_TRUE);
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }    
    }
    switch (instruction->operandWidth)
    {
    case 8:
        return ZydisPrintHexU(
            buffer, bufferLen, (uint8_t)operand->imm.value.u, 2, ZYDIS_TRUE, ZYDIS_TRUE);
    case 16:
        return ZydisPrintHexU(
            buffer, bufferLen, (uint16_t)operand->imm.value.u, 2, ZYDIS_TRUE, ZYDIS_TRUE);
    case 32:
        return ZydisPrintHexU(
            buffer, bufferLen, (uint32_t)operand->imm.value.u, 2, ZYDIS_TRUE, ZYDIS_TRUE);
    case 64:
        return ZydisPrintHexU(
            buffer, bufferLen, operand->imm.value.u, 2, ZYDIS_TRUE, ZYDIS_TRUE);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintOperandSizeIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    // TODO: refactor

    uint32_t typecast = 0;
    if (formatter->flags & ZYDIS_FMTFLAG_FORCE_OPERANDSIZE)
    {
        if ((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) && (!operand->mem.isAddressGenOnly))
        {
            typecast = instruction->operands[operand->id].size;
        }
    } else if ((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) && (!operand->mem.isAddressGenOnly)) 
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
        char* str = "";
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
        return ZydisPrintStr(buffer, bufferLen, str, ZYDIS_LETTER_CASE);
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterPrintSegmentIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;
    switch (operand->mem.segment)
    {
    case ZYDIS_REGISTER_ES:
    case ZYDIS_REGISTER_CS:
    case ZYDIS_REGISTER_FS:
    case ZYDIS_REGISTER_GS:
        ZYDIS_CHECK(
            ZydisPrintStr(buffer, bufEnd - *buffer, 
                ZydisRegisterGetString(operand->mem.segment), ZYDIS_LETTER_CASE));
        return ZydisPrintStr(buffer, bufEnd - *buffer, ":", ZYDIS_LETTER_CASE_DEFAULT);
    case ZYDIS_REGISTER_SS:
        if ((formatter->flags & ZYDIS_FMTFLAG_FORCE_SEGMENTS) || 
            (instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, 
                    ZydisRegisterGetString(operand->mem.segment), ZYDIS_LETTER_CASE));
            return ZydisPrintStr(buffer, bufEnd - *buffer, ":", ZYDIS_LETTER_CASE_DEFAULT);
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->flags & ZYDIS_FMTFLAG_FORCE_SEGMENTS) || 
            (instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, 
                    ZydisRegisterGetString(operand->mem.segment), ZYDIS_LETTER_CASE));
            return ZydisPrintStr(buffer, bufEnd - *buffer, ":", ZYDIS_LETTER_CASE_DEFAULT);
        }
        break;
    default:
        break;
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterPrintDecoratorIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, ZydisDecoratorType type, void* userData)
{
    (void)userData;

    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const char* bufEnd = *buffer + bufferLen;
    switch (type)
    {
    case ZYDIS_DECORATOR_TYPE_MASK:
    {
        if (instruction->avx.mask.reg != ZYDIS_REGISTER_K0)
        {
            const char* reg = ZydisRegisterGetString(instruction->avx.mask.reg);
            if (!reg)
            {
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, " {", ZYDIS_LETTER_CASE_DEFAULT)); 
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, reg, ZYDIS_LETTER_CASE));
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, "}", ZYDIS_LETTER_CASE_DEFAULT));
            if (instruction->avx.mask.mode == ZYDIS_MASK_MODE_ZERO)
            {
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {z}", ZYDIS_LETTER_CASE_DEFAULT));    
            } 
        }
        break;
    }
    case ZYDIS_DECORATOR_TYPE_BROADCAST:
        if (!instruction->avx.broadcast.isStatic)
        {
            switch (instruction->avx.broadcast.mode)
            {
            case ZYDIS_BROADCAST_MODE_INVALID:
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_2:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {1to2}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_4:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {1to4}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_8:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {1to8}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_16:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {1to16}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_8:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {4to8}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_16:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {4to16}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        }
        break;
    case ZYDIS_DECORATOR_TYPE_ROUNDING_CONTROL:
        if (instruction->avx.hasSAE)
        {
            switch (instruction->avx.rounding.mode)
            {
            case ZYDIS_ROUNDING_MODE_INVALID:   
                break;
            case ZYDIS_ROUNDING_MODE_RN:
                ZYDIS_CHECK(ZydisPrintStr(
                    buffer, bufEnd - *buffer, " {rn-sae}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_CHECK(ZydisPrintStr(
                    buffer, bufEnd - *buffer, " {rd-sae}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_CHECK(ZydisPrintStr(
                        buffer, bufEnd - *buffer, " {ru-sae}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_CHECK(ZydisPrintStr(
                        buffer, bufEnd - *buffer, " {rz-sae}", ZYDIS_LETTER_CASE_DEFAULT));
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
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {rn}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {rd}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {ru}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_CHECK(
                    ZydisPrintStr(buffer, bufEnd - *buffer, " {rz}", ZYDIS_LETTER_CASE_DEFAULT));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }    
        }
        break;
    case ZYDIS_DECORATOR_TYPE_SAE:
        if (instruction->avx.hasSAE && !instruction->avx.rounding.mode)
        {
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {sae}", ZYDIS_LETTER_CASE_DEFAULT)); 
        }
        break;
    case ZYDIS_DECORATOR_TYPE_SWIZZLE:
        switch (instruction->avx.swizzle.mode)
        {
        case ZYDIS_SWIZZLE_MODE_INVALID:
        case ZYDIS_SWIZZLE_MODE_DCBA:
            // Nothing to do here
            break;   
        case ZYDIS_SWIZZLE_MODE_CDAB:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {cdab}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_SWIZZLE_MODE_BADC:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {badc}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_SWIZZLE_MODE_DACB:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {dacb}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_SWIZZLE_MODE_AAAA:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {aaaa}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_SWIZZLE_MODE_BBBB:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {bbbb}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_SWIZZLE_MODE_CCCC:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {cccc}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_SWIZZLE_MODE_DDDD:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {dddd}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        break;
    case ZYDIS_DECORATOR_TYPE_CONVERSION:
        switch (instruction->avx.conversion.mode)
        {
        case ZYDIS_CONVERSION_MODE_INVALID:
            break;
        case ZYDIS_CONVERSION_MODE_FLOAT16:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {float16}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_CONVERSION_MODE_SINT8:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {sint8}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_CONVERSION_MODE_UINT8:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {uint8}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_CONVERSION_MODE_SINT16:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {sint16}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        case ZYDIS_CONVERSION_MODE_UINT16:
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {uint16}", ZYDIS_LETTER_CASE_DEFAULT));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        break;
    case ZYDIS_DECORATOR_TYPE_EVICTION_HINT:
        if (instruction->avx.hasEvictionHint)
        {
            ZYDIS_CHECK(
                ZydisPrintStr(buffer, bufEnd - *buffer, " {eh}", ZYDIS_LETTER_CASE_DEFAULT));     
        }
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterFormatInstrIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, const ZydisDecodedInstruction* instruction, void* userData)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;
    ZYDIS_CHECK(
        formatter->funcPrintPrefixes(formatter, buffer, bufEnd - *buffer, instruction, userData));
    ZYDIS_CHECK(
        formatter->funcPrintMnemonic(formatter, buffer, bufEnd - *buffer, instruction, userData));

    char* bufRestore = *buffer;
    for (uint8_t i = 0; i < instruction->operandCount; ++i)
    {
        if (instruction->operands[i].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        if (i == 0)
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, " ", ZYDIS_LETTER_CASE_DEFAULT));
        } else
        {
            bufRestore = *buffer;
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, ", ", ZYDIS_LETTER_CASE_DEFAULT));
        }

        const char* bufPreOperand = *buffer;
        switch (instruction->operands[i].type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            ZYDIS_CHECK(formatter->funcFormatOperandReg(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i], userData));
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
        {
            ZYDIS_CHECK(formatter->funcPrintOperandSize(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i], userData));
            ZYDIS_CHECK(formatter->funcPrintSegment(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i], userData));
            const char* bufTemp = *buffer;
            ZYDIS_CHECK(formatter->funcFormatOperandMem(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i], userData));
            if (bufTemp == *buffer)
            {
                *buffer = (char*)bufPreOperand;
            }
            break;
        }
        case ZYDIS_OPERAND_TYPE_POINTER:
            ZYDIS_CHECK(formatter->funcFormatOperandPtr(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i], userData));
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            ZYDIS_CHECK(formatter->funcFormatOperandImm(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i], userData));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        
        if (bufPreOperand == *buffer)
        {
            // Omit whole operand, if the buffer did not change during the formatting-callback
            *buffer = bufRestore;
            *buffer[0] = 0;
        } else
        {
            if ((instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ||
                (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX))
            {
                if  ((i == 0) && 
                     (instruction->operands[i + 1].encoding == ZYDIS_OPERAND_ENCODING_MASK))
                {
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                        bufEnd - *buffer, instruction, &instruction->operands[i], 
                        ZYDIS_DECORATOR_TYPE_MASK, userData));    
                }
                if (instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
                {
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                        bufEnd - *buffer, instruction, &instruction->operands[i], 
                        ZYDIS_DECORATOR_TYPE_BROADCAST, userData));
                    if (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_CONVERSION, userData)); 
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_EVICTION_HINT, userData));
                    }
                } else
                {
                    if ((i == (instruction->operandCount - 1)) || 
                        (instruction->operands[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE))
                    { 
                        if (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                        {
                            ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                                bufEnd - *buffer, instruction, &instruction->operands[i], 
                                ZYDIS_DECORATOR_TYPE_SWIZZLE, userData)); 
                        }
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_ROUNDING_CONTROL, userData));
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_SAE, userData));
                    }
                }
            }
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisFormatterInit(ZydisFormatter* formatter, 
    ZydisFormatterStyle style)
{
    return ZydisFormatterInitEx(formatter, style, 0, ZYDIS_FORMATTER_ADDR_DEFAULT, 
        ZYDIS_FORMATTER_DISP_DEFAULT, ZYDIS_FORMATTER_IMM_DEFAULT);    
}

ZydisStatus ZydisFormatterInitEx(ZydisFormatter* formatter, 
    ZydisFormatterStyle style, ZydisFormatterFlags flags, ZydisFormatterAddressFormat addressFormat, 
    ZydisFormatterDisplacementFormat displacementFormat,
    ZydisFormatterImmediateFormat immmediateFormat)
{
    if (!formatter || 
        ((addressFormat != ZYDIS_FORMATTER_ADDR_DEFAULT) && 
         (addressFormat != ZYDIS_FORMATTER_ADDR_ABSOLUTE) &&
         (addressFormat != ZYDIS_FORMATTER_ADDR_RELATIVE_SIGNED) &&
         (addressFormat != ZYDIS_FORMATTER_ADDR_RELATIVE_UNSIGNED)) ||
        ((displacementFormat != ZYDIS_FORMATTER_DISP_DEFAULT) && 
         (displacementFormat != ZYDIS_FORMATTER_DISP_HEX_SIGNED) &&
         (displacementFormat != ZYDIS_FORMATTER_DISP_HEX_UNSIGNED)) ||
        ((immmediateFormat != ZYDIS_FORMATTER_IMM_DEFAULT) && 
         (immmediateFormat != ZYDIS_FORMATTER_IMM_HEX_AUTO) && 
         (immmediateFormat != ZYDIS_FORMATTER_IMM_HEX_SIGNED) &&
         (immmediateFormat != ZYDIS_FORMATTER_IMM_HEX_UNSIGNED)))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    memset(formatter, 0, sizeof(ZydisFormatter));
    formatter->flags = flags;
    formatter->addressFormat = addressFormat;
    formatter->displacementFormat = displacementFormat;
    formatter->immediateFormat = immmediateFormat;

    switch (style)
    {
    case ZYDIS_FORMATTER_STYLE_INTEL:
        formatter->funcFormatInstruction    = &ZydisFormatterFormatInstrIntel;
        formatter->funcPrintPrefixes        = &ZydisFormatterPrintPrefixesIntel; 
        formatter->funcPrintMnemonic        = &ZydisFormatterPrintMnemonicIntel;
        formatter->funcFormatOperandReg     = &ZydisFormatterFormatOperandRegIntel;
        formatter->funcFormatOperandMem     = &ZydisFormatterFormatOperandMemIntel;
        formatter->funcFormatOperandPtr     = &ZydisFormatterFormatOperandPtrIntel;
        formatter->funcFormatOperandImm     = &ZydisFormatterFormatOperandImmIntel;
        formatter->funcPrintOperandSize     = &ZydisFormatterPrintOperandSizeIntel;
        formatter->funcPrintSegment         = &ZydisFormatterPrintSegmentIntel;
        formatter->funcPrintDecorator       = &ZydisFormatterPrintDecoratorIntel;
        formatter->funcPrintAddress         = &ZydisFormatterPrintAddressIntel;
        formatter->funcPrintDisplacement    = &ZydisFormatterPrintDisplacementIntel;
        formatter->funcPrintImmediate       = &ZydisFormatterPrintImmediateIntel;
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
    case ZYDIS_FORMATTER_HOOK_PRE:
        *callback = *(const void**)&formatter->funcPre;
        break;
    case ZYDIS_FORMATTER_HOOK_POST:
        *callback = *(const void**)&formatter->funcPost;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        *callback = *(const void**)&formatter->funcFormatInstruction;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        *callback = *(const void**)&formatter->funcPrintPrefixes;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC:
        *callback = *(const void**)&formatter->funcPrintMnemonic;
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
    case ZYDIS_FORMATTER_HOOK_PRINT_OPERANDSIZE:
        *callback = *(const void**)&formatter->funcPrintOperandSize;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_SEGMENT:
        *callback = *(const void**)&formatter->funcPrintSegment;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        *callback = *(const void**)&formatter->funcPrintDecorator;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS:
        *callback = *(const void**)&formatter->funcPrintAddress;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DISPLACEMENT:
        *callback = *(const void**)&formatter->funcPrintDisplacement;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMMEDIATE:
        *callback = *(const void**)&formatter->funcPrintImmediate;
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
    case ZYDIS_FORMATTER_HOOK_PRE:
        formatter->funcPre = *(ZydisFormatterNotifyFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_POST:
        formatter->funcPost = *(ZydisFormatterNotifyFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION:
        formatter->funcFormatInstruction = *(ZydisFormatterFormatFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES:
        formatter->funcPrintPrefixes = *(ZydisFormatterFormatFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC:
        formatter->funcPrintMnemonic = *(ZydisFormatterFormatFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG:
        formatter->funcFormatOperandReg = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM:
        formatter->funcFormatOperandMem = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR:
        formatter->funcFormatOperandPtr = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM:
        formatter->funcFormatOperandImm = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_OPERANDSIZE:
        formatter->funcPrintOperandSize = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_SEGMENT:
        formatter->funcPrintSegment = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR:
        formatter->funcPrintDecorator = *(ZydisFormatterFormatDecoratorFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS:
        formatter->funcPrintAddress = *(ZydisFormatterFormatAddressFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_DISPLACEMENT:
        formatter->funcPrintDisplacement = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    case ZYDIS_FORMATTER_HOOK_PRINT_IMMEDIATE:
        formatter->funcPrintImmediate = *(ZydisFormatterFormatOperandFunc*)&temp;
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter, 
    ZydisDecodedInstruction* instruction, char* buffer, size_t bufferLen)
{
    return ZydisFormatterFormatInstructionEx(formatter, instruction, buffer, bufferLen, NULL);
}

ZydisStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter, 
    ZydisDecodedInstruction* instruction, char* buffer, size_t bufferLen, void* userData)
{
    if (!formatter || !instruction || !buffer || (bufferLen == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (formatter->funcPre)
    {
        ZYDIS_CHECK(formatter->funcPre(formatter, instruction, userData));
    }
    ZYDIS_CHECK(
        formatter->funcFormatInstruction(formatter, &buffer, bufferLen, instruction, userData));
    if (formatter->funcPost)
    {
        return formatter->funcPost(formatter, instruction, userData);
    }
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
