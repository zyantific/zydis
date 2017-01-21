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
#include <inttypes.h>
#include <Zydis/Formatter.h>
#include <Zydis/Utils.h>

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
    int w = vsnprintf(*buffer, bufferLen, format, arglist);
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

static ZydisStatus ZydisFormatterPrintPrefixesIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (info->attributes & ZYDIS_ATTRIB_HAS_LOCK)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "lock ");
    }

    if (info->attributes & ZYDIS_ATTRIB_HAS_REP)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "rep ");
    }
    if (info->attributes & ZYDIS_ATTRIB_HAS_REPE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "repe ");
    }
    if (info->attributes & ZYDIS_ATTRIB_HAS_REPNE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "repne ");
    } 
   
    if (info->attributes & ZYDIS_ATTRIB_HAS_BOUND)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "bnd ");
    }

    if (info->attributes & ZYDIS_ATTRIB_HAS_XACQUIRE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "xacquire ");
    } 
    if (info->attributes & ZYDIS_ATTRIB_HAS_XRELEASE)
    {
        return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, "xrelease ");
    } 

    return ZYDIS_STATUS_SUCCESS;   
}

static ZydisStatus ZydisFormatterPrintMnemonicIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const char* mnemonic = ZydisMnemonicGetString(info->mnemonic);
    if (!mnemonic)
    {
        mnemonic = "invalid";
    }
    return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, mnemonic);    
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterFormatOperandRegIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const char* reg = ZydisRegisterGetString(operand->reg);
    if (!reg)
    {
        reg = "invalid";
    }
    return ZydisStringBufferAppend(buffer, bufferLen, ZYDIS_APPENDMODE, reg);
}

static ZydisStatus ZydisFormatterFormatOperandMemIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd = *buffer + bufferLen;

    ZYDIS_CHECK(
        ZydisStringBufferAppend(buffer, bufEnd - *buffer, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "["));
 
    if ((operand->mem.disp.dataSize != 0) && (
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
            address = (uint64_t)operand->mem.disp.value.sqword;
        } else
        {
            // EIP/RIP-relative
            ZYDIS_CHECK(ZydisUtilsCalcAbsoluteTargetAddress(info, operand, &address));
        }
        ZYDIS_CHECK(formatter->funcPrintAddress(formatter, buffer, bufEnd - *buffer, 
            info, operand, address));   
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
            info, operand)); 
    }

    return ZydisStringBufferAppend(buffer, bufEnd - *buffer, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "]");
}

static ZydisStatus ZydisFormatterFormatOperandPtrIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
        "0x%04"PRIX16":0x%08"PRIX32, operand->ptr.segment, operand->ptr.offset);
}

static ZydisStatus ZydisFormatterFormatOperandImmIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
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
            ZYDIS_CHECK(ZydisUtilsCalcAbsoluteTargetAddress(info, operand, &address));
            return formatter->funcPrintAddress(formatter, buffer, bufferLen, info, operand, 
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
        if (printSignedHEX && (operand->imm.value.sqword < 0))
        {
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX32, -operand->imm.value.sdword);
        }
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "0x%02"PRIX32, operand->imm.value.sdword);
    }

    // The immediate operand contains an actual ordinal value
    return formatter->funcPrintImmediate(formatter, buffer, bufferLen, info, operand);
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintAddressIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand, 
    uint64_t address)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    switch (info->mode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "0x%08"PRIX64, address);
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "0x%016"PRIX64, address);   
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

static ZydisStatus ZydisFormatterPrintDisplacementIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if ((operand->mem.disp.dataSize) && ((operand->mem.disp.value.sqword) || 
        ((operand->mem.base == ZYDIS_REGISTER_NONE) && 
        (operand->mem.index == ZYDIS_REGISTER_NONE))))
    {
        ZydisBool printSignedHEX = 
            (formatter->displacementFormat != ZYDIS_FORMATTER_DISP_HEX_UNSIGNED);
        if (printSignedHEX && (operand->mem.disp.value.sqword < 0) && (
            (operand->mem.base != ZYDIS_REGISTER_NONE) || 
            (operand->mem.index != ZYDIS_REGISTER_NONE)))
        {
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX32, -operand->mem.disp.value.sdword);     
        }
        const char* sign = 
            ((operand->mem.base == ZYDIS_REGISTER_NONE) && 
            (operand->mem.index == ZYDIS_REGISTER_NONE)) ? "" : "+";
        return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_STRBUF_APPEND_MODE_DEFAULT, 
            "%s0x%02"PRIX32, sign, operand->mem.disp.value.sdword);
    }
    return ZYDIS_STATUS_SUCCESS; 
}

static ZydisStatus ZydisFormatterPrintImmediateIntel(ZydisInstructionFormatter* formatter, 
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisBool printSignedHEX = (formatter->immediateFormat == ZYDIS_FORMATTER_IMM_HEX_SIGNED);
    if (formatter->immediateFormat == ZYDIS_FORMATTER_IMM_HEX_AUTO)
    {
        printSignedHEX = operand->imm.isSigned;    
    }
    if (printSignedHEX && (operand->imm.value.sqword < 0))
    {
        switch (operand->size)
        {
        case 8:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX8, -operand->imm.value.sbyte);
        case 16:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX16, -operand->imm.value.sword);
        case 32:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX32, -operand->imm.value.sdword);
        case 64:
            return ZydisStringBufferAppendFormat(buffer, bufferLen, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "-0x%02"PRIX64,  -operand->imm.value.sqword);
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }    
    }
    switch (operand->size)
    {
    case 8:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX8, operand->imm.value.ubyte);
    case 16:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX16, operand->imm.value.uword);
    case 32:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX32, operand->imm.value.udword);
    case 64:
        return ZydisStringBufferAppendFormat(buffer, bufferLen, 
            ZYDIS_STRBUF_APPEND_MODE_DEFAULT, "0x%02"PRIX64,  operand->imm.value.uqword);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisFormatterPrintOperandSizeIntel(ZydisInstructionFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    uint32_t typecast = 0;
    if (formatter->flags & ZYDIS_FMTFLAG_FORCE_OPERANDSIZE)
    {
        if (info->operands[operand->id].type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            typecast = info->operands[operand->id].size;
        }
    } else if (info->operands[operand->id].type == ZYDIS_OPERAND_TYPE_MEMORY) 
    {
        switch (operand->id)
        {
        case 0:
            typecast = ((info->operands[1].type == ZYDIS_OPERAND_TYPE_UNUSED) ||
                (info->operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) ||
                (info->operands[0].size != info->operands[1].size)) ? info->operands[0].size : 0;
            if (!typecast && 
                (info->operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) && 
                (info->operands[1].reg == ZYDIS_REGISTER_CL))
            {
                switch (info->mnemonic)
                {
                case ZYDIS_MNEMONIC_RCL:
                case ZYDIS_MNEMONIC_ROL:
                case ZYDIS_MNEMONIC_ROR:
                case ZYDIS_MNEMONIC_RCR:
                case ZYDIS_MNEMONIC_SHL:
                case ZYDIS_MNEMONIC_SHR:
                case ZYDIS_MNEMONIC_SAR:
                    typecast = info->operands[0].size;
                default:
                    break;
                }
            }
            break;
        case 1:
        case 2:
            typecast = 
                (info->operands[operand->id - 1].size != info->operands[operand->id].size) ? 
                 info->operands[operand->id].size : 0;
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

static ZydisStatus ZydisFormatterPrintSegmentIntel(ZydisInstructionFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
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
            (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_SS))
        {
            return ZydisStringBufferAppendFormat(buffer, bufferLen, ZYDIS_APPENDMODE, "%s:", 
                ZydisRegisterGetString(operand->mem.segment));
        }
        break;
    case ZYDIS_REGISTER_DS:
        if ((formatter->flags & ZYDIS_FMTFLAG_FORCE_SEGMENTS) || 
            (info->attributes & ZYDIS_ATTRIB_HAS_SEGMENT_DS))
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

static ZydisStatus ZydisFormatterPrintDecoratorIntel(ZydisInstructionFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info, ZydisOperandInfo* operand)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info || !operand)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const char* bufEnd = *buffer + bufferLen;

    if (operand->id == 0)
    {
        if (info->avx.maskRegister)
        {
            const char* reg = ZydisRegisterGetString(info->avx.maskRegister);
            if (!reg)
            {
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
            ZYDIS_CHECK(ZydisStringBufferAppendFormat(buffer, bufEnd - *buffer, ZYDIS_APPENDMODE, 
                " {%s}", reg)); 
        }
        if (info->avx.maskMode == ZYDIS_AVX512_MASKMODE_ZERO)
        {
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {z}"));    
        }
    } else
    {
        if (info->operands[operand->id].type == ZYDIS_OPERAND_TYPE_MEMORY)
        {
            switch (info->avx.broadcast)
            {
            case ZYDIS_AVX512_BCSTMODE_INVALID:
                break;
            case ZYDIS_AVX512_BCSTMODE_2:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to2}"));
                break;
            case ZYDIS_AVX512_BCSTMODE_4:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to4}"));
                break;
            case ZYDIS_AVX512_BCSTMODE_8:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to8}"));
                break;
            case ZYDIS_AVX512_BCSTMODE_16:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {1to16}"));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        }

        if ((operand->id == (info->operandCount - 1)) || 
            ((operand->id != (info->operandCount - 1)) && 
             (info->operands[operand->id + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)))
        {
            switch (info->avx.roundingMode)
            {
            case ZYDIS_AVX_RNDMODE_INVALID:
                if (info->avx.hasSAE)
                {
                    ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                        ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {sae}"));    
                }
                break;
            case ZYDIS_AVX_RNDMODE_RN:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rn-sae}"));
                break;
            case ZYDIS_AVX_RNDMODE_RD:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rd-sae}"));
                break;
            case ZYDIS_AVX_RNDMODE_RU:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {ru-sae}"));
                break;
            case ZYDIS_AVX_RNDMODE_RZ:
                ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 
                    ZYDIS_STRBUF_APPEND_MODE_DEFAULT, " {rz-sae}"));
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

static ZydisStatus ZydisFormatterFormatInstrIntel(ZydisInstructionFormatter* formatter,
    char** buffer, size_t bufferLen, ZydisInstructionInfo* info)
{
    if (!formatter || !buffer || !*buffer || (bufferLen <= 0) || !info)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    char* bufEnd   = *buffer + bufferLen;
    ZYDIS_CHECK(formatter->funcPrintPrefixes(formatter, buffer, bufEnd - *buffer, info));
    ZYDIS_CHECK(formatter->funcPrintMnemonic(formatter, buffer, bufEnd - *buffer, info));

    char* bufRestore = *buffer;
    if (info->operandCount > 0)
    {
        ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 0, " "));
    }

    for (uint8_t i = 0; i < info->operandCount; ++i)
    {
        if (i != 0)
        {
            bufRestore = *buffer;
            ZYDIS_CHECK(ZydisStringBufferAppend(buffer, bufEnd - *buffer, 0, ", "));
        }

        const char* bufPreOperand = *buffer;
        switch (info->operands[i].type)
        {
        case ZYDIS_OPERAND_TYPE_UNUSED:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        case ZYDIS_OPERAND_TYPE_REGISTER:
            ZYDIS_CHECK(formatter->funcFormatOperandReg(formatter, buffer, bufEnd - *buffer, 
                info, &info->operands[i]));
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
        {
            ZYDIS_CHECK(formatter->funcPrintOperandSize(formatter, buffer, bufEnd - *buffer, 
                info, &info->operands[i]));
            ZYDIS_CHECK(formatter->funcPrintSegment(formatter, buffer, bufEnd - *buffer, 
                info, &info->operands[i]));
            const char* bufTemp = *buffer;
            ZYDIS_CHECK(formatter->funcFormatOperandMem(formatter, buffer, bufEnd - *buffer, 
                info, &info->operands[i]));
            if (bufTemp == *buffer)
            {
                *buffer = (char*)bufPreOperand;
            }
            break;
        }
        case ZYDIS_OPERAND_TYPE_POINTER:
            ZYDIS_CHECK(formatter->funcFormatOperandPtr(formatter, buffer, bufEnd - *buffer, 
                info, &info->operands[i]));
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            ZYDIS_CHECK(formatter->funcFormatOperandImm(formatter, buffer, bufEnd - *buffer, 
                info, &info->operands[i]));
            break;
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        
        if (bufPreOperand == *buffer)
        {
            // Omit whole operands, if the buffer did not change during the formatting-callback
            *buffer = bufRestore;
            *buffer[0] = 0;
        } else
        {
            if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX)
            {
                ZYDIS_CHECK(formatter->funcPrintDecorator(formatter, buffer, bufEnd - *buffer, 
                    info, &info->operands[i]));
            }
        }
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisFormatterInitInstructionFormatter(
    ZydisInstructionFormatter* formatter, ZydisFormatterStyle style)
{
    return ZydisFormatterInitInstructionFormatterEx(formatter, style, 0, 
        ZYDIS_FORMATTER_ADDR_DEFAULT, ZYDIS_FORMATTER_DISP_DEFAULT, ZYDIS_FORMATTER_IMM_DEFAULT);    
}

ZydisStatus ZydisFormatterInitInstructionFormatterEx(
    ZydisInstructionFormatter* formatter, ZydisFormatterStyle style, ZydisFormatterFlags flags,
    ZydisFormatterAddressFormat addressFormat, ZydisFormatterDisplacementFormat displacementFormat,
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
         (immmediateFormat != ZYDIS_FORMATTER_IMM_HEX_SIGNED) &&
         (immmediateFormat != ZYDIS_FORMATTER_IMM_HEX_UNSIGNED)))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    memset(formatter, 0, sizeof(ZydisInstructionFormatter));
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

ZydisStatus ZydisFormatterSetHook(ZydisInstructionFormatter* formatter, 
    ZydisFormatterHookType hook, const void** callback)
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
        formatter->funcPrintDecorator = *(ZydisFormatterFormatOperandFunc*)&temp;
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
        break;
    }

    return ZYDIS_STATUS_INVALID_PARAMETER;
}

ZydisStatus ZydisFormatterFormatInstruction(
    ZydisInstructionFormatter* formatter, ZydisInstructionInfo* info, char* buffer,
    size_t bufferLen)
{
    if (!formatter || !info || !buffer || (bufferLen == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (formatter->funcPre)
    {
        ZYDIS_CHECK(formatter->funcPre(formatter, info));
    }
    ZYDIS_CHECK(formatter->funcFormatInstruction(formatter, &buffer, bufferLen, info));
    if (formatter->funcPost)
    {
        return formatter->funcPost(formatter, info);
    }
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
