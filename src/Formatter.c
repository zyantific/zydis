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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <Zydis/Formatter.h>
#include <Zydis/Utils.h>
#include <Zydis/CommonTypes.h>

#if defined(ZYDIS_WINKERNEL)
#   include <ntddk.h>
#   include <Ntstrsafe.h>
#endif

/* ============================================================================================== */
/* String formatting                                                                              */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 *  @brief  Defines the @c ZydisStringBufferAppendMode datatype.
 */
typedef uint8_t ZydisStringBufferAppendMode;

/**
 * @brief   Values that represent zydis string-buffer append-modes.
 */
enum ZydisStringBufferAppendModes
{
    /**
     *  @brief  Appends the string as it is.
     */
    ZYDIS_STRBUF_APPEND_MODE_DEFAULT,
    /**
     *  @brief  Converts the string to lowercase characters.
     */
    ZYDIS_STRBUF_APPEND_MODE_LOWERCASE,
    /**
     *  @brief  Converts the string to uppercase characters.
     */
    ZYDIS_STRBUF_APPEND_MODE_UPPERCASE
};

/* ---------------------------------------------------------------------------------------------- */
/* Internal functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

#if defined(ZYDIS_WINKERNEL)
static int ZydisVSNPrintF(char* s, size_t n, const char* format, va_list arg)
{
    size_t bytesRemaining;
    NTSTATUS ret = RtlStringCchVPrintfExA(
        s, n, NULL, &bytesRemaining, 0, format, arg
    );

    if (!NT_SUCCESS(ret)) return -1;
    return (int)(n - bytesRemaining);
}
#else
static int ZydisVSNPrintF(char* s, size_t n, const char* format, va_list arg)
{
    return vsnprintf(s, n, format, arg);
}
#endif

/**
 * @brief   Appends the @c text to the given @c buffer and increases the string-buffer pointer by
 *          the number of chars written.
 *
 * @param   buffer      A pointer to the string-buffer.
 * @param   bufferLen   The length of the string-buffer.
 * @param   mode        The append-mode.
 * @param   text        The text to append.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c text.
 */
static ZydisStatus ZydisStringBufferAppend(char** buffer, size_t bufferLen, 
    ZydisStringBufferAppendMode mode, const char* text)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(text);

    size_t strLen = strlen(text);
    if (strLen >= bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    strncpy(*buffer, text, strLen + 1);
    switch (mode)
    {
    case ZYDIS_STRBUF_APPEND_MODE_LOWERCASE:
        for (size_t i = 0; i < strLen; ++i)
        {
            (*buffer[i]) = (char)tolower((*buffer)[i]);    
        }
        break;
    case ZYDIS_STRBUF_APPEND_MODE_UPPERCASE:
        for (size_t i = 0; i < strLen; ++i)
        {
            (*buffer)[i] = (char)toupper((*buffer)[i]);    
        }
        break;
    default:
        break;
    }
    *buffer += strLen;
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Appends formatted text to the given @c buffer and increases the string-buffer pointer 
 *          by the number of chars written.
 *
 * @param   buffer      A pointer to the string-buffer.
 * @param   bufferLen   The length of the string-buffer.
 * @param   mode        The append-mode.
 * @param   format      The format string.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given text.
 */
static ZydisStatus ZydisStringBufferAppendFormat(char** buffer, size_t bufferLen, 
    ZydisStringBufferAppendMode mode, const char* format, ...)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(format);

    va_list arglist;
    va_start(arglist, format);
    int w = ZydisVSNPrintF(*buffer, bufferLen, format, arglist);
    if ((w < 0) || ((size_t)w >= bufferLen))
    {
        va_end(arglist);
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    switch (mode)
    {
    case ZYDIS_STRBUF_APPEND_MODE_LOWERCASE:
        for (size_t i = 0; i < (size_t)w; ++i)
        {
            (*buffer)[i] = (char)tolower((*buffer)[i]);    
        }
        break;
    case ZYDIS_STRBUF_APPEND_MODE_UPPERCASE:
        for (size_t i = 0; i < (size_t)w; ++i)
        {
            (*buffer)[i] = (char)toupper((*buffer)[i]);    
        }
        break;
    default:
        break;
    }
    *buffer += (size_t)w;
    va_end(arglist);
    return ZYDIS_STATUS_SUCCESS;
}

/* ============================================================================================== */
/* Instruction formatter                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internal macros                                                                                */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_APPENDMODE \
    (formatter->flags & ZYDIS_FMTFLAG_UPPERCASE) ? \
        ZYDIS_STRBUF_APPEND_MODE_UPPERCASE : ZYDIS_STRBUF_APPEND_MODE_DEFAULT

/* ---------------------------------------------------------------------------------------------- */
/* Intel style                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintPrefixesIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "lock ");
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "rep ");
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "repe ");
    }
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "repne ");
    } 
   
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_BOUND)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "bnd ");
    }

    if (instruction->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "xacquire ");
    } 
    if (instruction->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "xrelease ");
    } 

    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisFormatterPrintMnemonicIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const char* mnemonic = ZydisMnemonicGetString(instruction->mnemonic);
    if (!mnemonic)
    {
        mnemonic = "invalid";
    }
    return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, mnemonic);    
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterFormatOperandRegIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if ((operand->id == 1) && (operand->encoding == ZYDIS_OPERAND_ENCODING_MASK))
    {
        return ZYDIS_STATUS_SUCCESS;
    }

    const char* reg = ZydisRegisterGetString(operand->reg);
    if (!reg)
    {
        reg = "invalid";
    }
    return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, reg);
}

static ZydisStatus ZydisFormatterFormatOperandMemIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;

    ZYDIS_CHECK(
        ZydisStringBufferAppend(buffer, bufEnd - *buffer, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "["));
 
    if (operand->mem.disp.hasDisplacement && (
        (operand->mem.base == ZYDIS_REGISTER_NONE) ||
        (operand->mem.base == ZYDIS_REGISTER_EIP) || 
        (operand->mem.base == ZYDIS_REGISTER_RIP)) &&
        (operand->mem.index == ZYDIS_REGISTER_NONE) && (operand->mem.scale == 0))
    {
        // Address operand
        uint64_t address;
        if (operand->mem.base == ZYDIS_REGISTER_NONE)
        {
            // MOFFS8/16/32/64
            address = (uint64_t)operand->mem.disp.value;
        } else
        {
            // EIP/RIP-relative
            ZYDIS_CHECK(ZydisUtilsCalcAbsoluteTargetAddress(instruction, operand, &address));
        }
        ZYDIS_CHECK(formatter->funcPrintAddress(formatter, buffer, bufEnd - *buffer, 
            instruction, operand, address));   
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
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, ZYDIS_APPENDMODE, reg)); 
        }
        if (operand->mem.index != ZYDIS_REGISTER_NONE)
        {
            const char* reg = ZydisRegisterGetString(operand->mem.index);
            if (!reg)
            {
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
            const char* c = (operand->mem.base != ZYDIS_REGISTER_NONE) ? "+" : "";
            ZYDIS_CHECK(ZydisStringBufferAppendFormat(buffer, bufEnd - *buffer, ZYDIS_APPENDMODE, 
                "%s%s", c, reg));
            if (operand->mem.scale)
            {
                ZYDIS_CHECK(ZydisStringBufferAppendFormat(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "*%d", operand->mem.scale));    
            }
        }
        ZYDIS_CHECK(formatter->funcPrintDisplacement(formatter, buffer, bufEnd - *buffer,
            instruction, operand)); 
    }

    return ZydisStringBufferAppend(buffer, bufEnd - *buffer, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "]");
}

static ZydisStatus ZydisFormatterFormatOperandPtrIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
        "0x%04"PRIX16":0x%08"PRIX32, operand->ptr.segment, operand->ptr.offset);
}

static ZydisStatus ZydisFormatterFormatOperandImmIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
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
            ZYDIS_CHECK(ZydisUtilsCalcAbsoluteTargetAddress(instruction, operand, &address));
            return formatter->funcPrintAddress(formatter, buffer, bufferLen, instruction, operand, 
                address);
        }
        case ZYDIS_FORMATTER_ADDR_RELATIVE_SIGNED:
            printSignedHEX = ZYDIS_TRUE;
            break;
        case ZYDIS_FORMATTER_ADDR_RELATIVE_UNSIGNED:
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        if (printSignedHEX && (operand->imm.value.s < 0))
        {
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX32, -(int32_t)operand->imm.value.s);
        }
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "0x%02"PRIX32, (int32_t)operand->imm.value.s);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->funcPrintImmediate(formatter, buffer, bufferLen, instruction, operand);
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintAddressIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction,
    ZydisDecodedOperand* operand, 
    uint64_t address)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (instruction->machineMode)
    {
    case 16:
    case 32:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "0x%08"PRIX64, address);
    case 64:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "0x%016"PRIX64, address);   
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

static ZydisStatus ZydisFormatterPrintDisplacementIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
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
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX32, -operand->mem.disp.value);     
        }
        const char* sign = 
            ((operand->mem.base == ZYDIS_REGISTER_NONE) && 
            (operand->mem.index == ZYDIS_REGISTER_NONE)) ? "" : "+";
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "%s0x%02"PRIX32, sign, operand->mem.disp.value);
    }
    return ZYDIS_STATUS_SUCCESS; 
}

static ZydisStatus ZydisFormatterPrintImmediateIntel(const ZydisFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
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
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX8, -(int8_t)operand->imm.value.s);
        case 16:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX16, -(int16_t)operand->imm.value.s);
        case 32:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX32, -(int32_t)operand->imm.value.s);
        case 64:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX64, -operand->imm.value.s);
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }    
    }
    switch (instruction->operandSize)
    {
    case 16:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX16, (uint16_t)operand->imm.value.u);
    case 32:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX32, (uint32_t)operand->imm.value.u);
    case 64:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX64, operand->imm.value.u);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintOperandSizeIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
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
                (instruction->operands[1].reg == ZYDIS_REGISTER_CL))
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
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, str);
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterPrintSegmentIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (operand->mem.segment)
    {
    case ZYDIS_REGISTER_ES:
    case ZYDIS_REGISTER_CS:
    case ZYDIS_REGISTER_FS:
    case ZYDIS_REGISTER_GS:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_APPENDMODE, "%s:", 
            ZydisRegisterGetString(operand->mem.segment));
    case ZYDIS_REGISTER_SS:
        if ((formatter->flags & ZYDIS_FMTFLAG_FORCE_SEGMENTS) || 
            (instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_APPENDMODE, "%s:", 
                ZydisRegisterGetString(operand->mem.segment));
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->flags & ZYDIS_FMTFLAG_FORCE_SEGMENTS) || 
            (instruction->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
        {
            return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_APPENDMODE, "%s:", 
                ZydisRegisterGetString(operand->mem.segment));
        }
        break;
    default:
        break;
    }
    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterPrintDecoratorIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction, 
    ZydisDecodedOperand* operand, ZydisDecoratorType type)
{
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
            ZYDIS_CHECK(ZydisStringBufferAppendFormat(
                buffer, bufEnd - *buffer, ZYDIS_APPENDMODE, " {%s}", reg)); 
            if (instruction->avx.mask.mode == ZYDIS_MASK_MODE_ZERO)
            {
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {z}"));    
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
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to2}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_4:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to4}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_8:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to8}"));
                break;
            case ZYDIS_BROADCAST_MODE_1_TO_16:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to16}"));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_8:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {4to8}"));
                break;
            case ZYDIS_BROADCAST_MODE_4_TO_16:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {4to16}"));
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
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rn-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rd-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {ru-sae}"));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rz-sae}"));
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
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rn}"));
                break;
            case ZYDIS_ROUNDING_MODE_RD:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rd}"));
                break;
            case ZYDIS_ROUNDING_MODE_RU:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {ru}"));
                break;
            case ZYDIS_ROUNDING_MODE_RZ:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rz}"));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }    
        }
        break;
    case ZYDIS_DECORATOR_TYPE_SAE:
        if (instruction->avx.hasSAE && !instruction->avx.rounding.mode)
        {
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {sae}")); 
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
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {cdab}"));
            break;
        case ZYDIS_SWIZZLE_MODE_BADC:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {badc}"));
            break;
        case ZYDIS_SWIZZLE_MODE_DACB:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {dacb}"));
            break;
        case ZYDIS_SWIZZLE_MODE_AAAA:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {aaaa}"));
            break;
        case ZYDIS_SWIZZLE_MODE_BBBB:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {bbbb}"));
            break;
        case ZYDIS_SWIZZLE_MODE_CCCC:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {cccc}"));
            break;
        case ZYDIS_SWIZZLE_MODE_DDDD:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {dddd}"));
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
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {float16}"));
            break;
        case ZYDIS_CONVERSION_MODE_SINT8:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {sint8}"));
            break;
        case ZYDIS_CONVERSION_MODE_UINT8:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {uint8}"));
            break;
        case ZYDIS_CONVERSION_MODE_SINT16:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {sint16}"));
            break;
        case ZYDIS_CONVERSION_MODE_UINT16:
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {uint16}"));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        break;
    case ZYDIS_DECORATOR_TYPE_EVICTION_HINT:
        if (instruction->avx.hasEvictionHint)
        {
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {eh}"));     
        }
        break;
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterFormatInstrIntel(const ZydisFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisDecodedInstruction* instruction)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;
    ZYDIS_CHECK(formatter->funcPrintPrefixes(formatter, buffer, bufEnd - *buffer, instruction));
    ZYDIS_CHECK(formatter->funcPrintMnemonic(formatter, buffer, bufEnd - *buffer, instruction));

    char* bufRestore = *buffer;
    for (uint8_t i = 0; i < instruction->operandCount; ++i)
    {
        if (instruction->operands[i].visibility == ZYDIS_OPERAND_VISIBILITY_HIDDEN)
        {
            break;
        }

        if (i == 0)
        {
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 0, " "));
        } else
        {
            bufRestore = *buffer;
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 0, ", "));
        }

        const char* bufPreOperand = *buffer;
        switch (instruction->operands[i].type)
        {
        case ZYDIS_OPERAND_TYPE_REGISTER:
            ZYDIS_CHECK(formatter->funcFormatOperandReg(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i]));
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
        {
            ZYDIS_CHECK(formatter->funcPrintOperandSize(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i]));
            ZYDIS_CHECK(formatter->funcPrintSegment(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i]));
            const char* bufTemp = *buffer;
            ZYDIS_CHECK(formatter->funcFormatOperandMem(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i]));
            if (bufTemp == *buffer)
            {
                *buffer = (char*)bufPreOperand;
            }
            break;
        }
        case ZYDIS_OPERAND_TYPE_POINTER:
            ZYDIS_CHECK(formatter->funcFormatOperandPtr(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i]));
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            ZYDIS_CHECK(formatter->funcFormatOperandImm(formatter, buffer, bufEnd - *buffer, 
                instruction, &instruction->operands[i]));
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
                        ZYDIS_DECORATOR_TYPE_MASK));    
                }
                if (instruction->operands[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
                {
                    ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                        bufEnd - *buffer, instruction, &instruction->operands[i], 
                        ZYDIS_DECORATOR_TYPE_BROADCAST));
                    if (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)
                    {
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_CONVERSION)); 
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_EVICTION_HINT));
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
                                ZYDIS_DECORATOR_TYPE_SWIZZLE)); 
                        }
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_ROUNDING_CONTROL));
                        ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, 
                            bufEnd - *buffer, instruction, &instruction->operands[i], 
                            ZYDIS_DECORATOR_TYPE_SAE));
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
    if (!formatter || !instruction || !buffer || (bufferLen == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (formatter->funcPre)
    {
        ZYDIS_CHECK(formatter->funcPre(formatter, instruction));
    }
    ZYDIS_CHECK(formatter->funcFormatInstruction(formatter, &buffer, bufferLen, instruction));
    if (formatter->funcPost)
    {
        return formatter->funcPost(formatter, instruction);
    }
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
