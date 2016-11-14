/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

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
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <Zydis/Status.h>
#include <Zydis/Formatter.h>
#include <Zydis/SymbolResolver.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Internal macros                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Helper macros                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_CHECK(status) \
    if (status != ZYDIS_STATUS_SUCCESS) \
    { \
        return status; \
    }

/* ============================================================================================== */
/* Instruction formatter                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internal functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Inserts the @c text into the @c buffer at the given @c offset and increases the 
 *          @c offset by the length of the text.
 *
 * @param   buffer      A pointer to the target buffer.
 * @param   bufferLen   The length of the buffer.
 * @param   offset      A pointer to the buffer-offset.
 * @param   text        The text to insert.
 * @param   uppercase   Set true, to convert to uppercase characters.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisBufferAppend(char* buffer, size_t bufferLen, size_t* offset, 
    bool uppercase, const char* text)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(offset);
    ZYDIS_ASSERT(text);

    size_t strLen = strlen(text);
    if ((*offset + strLen) >= bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    strncpy(&buffer[*offset], text, strLen + 1);
    if (uppercase)
    {
        for (size_t i = *offset; i < *offset + strLen; ++i)
        {
            buffer[i] = (char)toupper(buffer[i]);    
        }
    }
    *offset += strLen;
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Inserts formatted text into the @c buffer at the given @c offset and increases the 
 *          @c offset by the length of the text.
 *
 * @param   buffer      A pointer to the target buffer.
 * @param   bufferLen   The length of the buffer.
 * @param   offset      A pointer to the buffer-offset.
 * @param   format      The format string.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisBufferAppendFormat(char* buffer, size_t bufferLen, size_t* offset, 
    bool uppercase, const char* format, ...)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(offset);
    ZYDIS_ASSERT(format);

    va_list arglist;
    va_start(arglist, format);
    size_t n = bufferLen - *offset;
    int w = vsnprintf(&buffer[*offset], n, format, arglist);
    if ((w < 0) || ((size_t)w >= n))
    {
        va_end(arglist);
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    if (uppercase)
    {
        for (size_t i = *offset; i < *offset + (size_t)w; ++i)
        {
            buffer[i] = (char)toupper(buffer[i]);    
        }
    }
    *offset += (size_t)w;
    va_end(arglist);
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisBufferAppendAbsoluteAddress(const ZydisInstructionFormatter* formatter, 
    char* buffer, size_t bufferLen, size_t* offset, const ZydisInstructionInfo* info, 
    const ZydisOperandInfo* operand)
{
    ZYDIS_ASSERT(formatter);
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(offset);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);
    ZYDIS_ASSERT((operand->type == ZYDIS_OPERAND_TYPE_MEMORY) ||
        (operand->type == ZYDIS_OPERAND_TYPE_IMMEDIATE));

    uint64_t address = 0;
    switch (operand->type)
    {
    case ZYDIS_OPERAND_TYPE_MEMORY:
        ZYDIS_ASSERT(operand->mem.disp.dataSize != 0);
        if ((operand->mem.base == ZYDIS_REGISTER_EIP) || (operand->mem.base == ZYDIS_REGISTER_RIP))
        {
            ZYDIS_CHECK(ZydisUtilsCalcAbsoluteTargetAddress(info, operand, &address));    
        } else
        {
            ZYDIS_ASSERT(operand->mem.base == ZYDIS_REGISTER_NONE);
            ZYDIS_ASSERT(operand->mem.index == ZYDIS_REGISTER_NONE);
            ZYDIS_ASSERT(operand->mem.scale == 0);
            address = (uint64_t)operand->mem.disp.value.sqword;
        }
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        ZYDIS_CHECK(ZydisUtilsCalcAbsoluteTargetAddress(info, operand, &address));
        break;
    default:
        break;
    }

    const char* symbol = NULL;
    int64_t symbolOffset = 0;
    if (formatter->symbolResolver)
    {
        symbol = formatter->symbolResolver->resolveSymbol(formatter->symbolResolver, info, operand, 
            address, &symbolOffset);    
    }
    if (symbol)
    {
        if (symbolOffset == 0)
        {
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, false, "%s", symbol);
        }
        if (symbolOffset > 0)
        {
            return ZydisBufferAppendFormat(
                buffer, bufferLen, offset, false, "%s+0x%02llX", symbol, symbolOffset);    
        }
        if (symbolOffset < 0)
        {
            return ZydisBufferAppendFormat(
                buffer, bufferLen, offset, false, "%s-0x%02llX", symbol, -symbolOffset);    
        }
    }
    switch (info->mode)
    {
    case ZYDIS_DISASSEMBLER_MODE_16BIT:
        return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%04X", address);
    case ZYDIS_DISASSEMBLER_MODE_32BIT:
    case ZYDIS_DISASSEMBLER_MODE_64BIT:
        switch (operand->size)
        {
        case 16:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%04X", address);     
        case 32:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%08lX", address);
        case 64:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%016llX", address);
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }     
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

static ZydisStatus ZydisBufferAppendImmediate(const ZydisInstructionFormatter* formatter, 
    char* buffer, size_t bufferLen, size_t* offset, const ZydisInstructionInfo* info, 
    const ZydisOperandInfo* operand)
{
    ZYDIS_ASSERT(formatter);
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(offset);
    ZYDIS_ASSERT(info);
    ZYDIS_ASSERT(operand);

    if ((formatter->addressFormat == ZYDIS_FORMATTER_ADDRESS_ABSOLUTE) && 
        (operand->imm.isRelative))
    {
        return ZydisBufferAppendAbsoluteAddress(formatter, buffer, bufferLen, offset, info, 
            operand);
    }

    bool useSignedHex = ((operand->imm.isSigned && 
        (formatter->addressFormat == ZYDIS_FORMATTER_ADDRESS_RELATIVE_SIGNED)) || 
        (!operand->imm.isSigned && (formatter->immediateFormat == ZYDIS_FORMATTER_IMM_HEX_SIGNED)));

    if (useSignedHex && (operand->imm.value.sqword < 0))
    {
        switch (operand->size)
        {
        case 8:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "-0x%02X", 
                -operand->imm.value.sbyte);
        case 16:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "-0x%02X", 
                -operand->imm.value.sword);
        case 32:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "-0x%02lX", 
                -operand->imm.value.sdword);
        case 64:
            return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "-0x%02llX", 
                -operand->imm.value.sqword);
        default:
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }   
    }

    switch (operand->size)
    {
    case 8:
        return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%02X", 
            operand->imm.value.ubyte);
    case 16:
        return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%02X", 
            operand->imm.value.uword);
    case 32:
        return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%02lX", 
            operand->imm.value.udword);
    case 64:
        return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%02llX", 
            operand->imm.value.uqword);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }    
}

/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisBufferAppendOperandIntelMemory(const ZydisInstructionFormatter* formatter,
    char* buffer, size_t bufferLen, size_t* offset, const ZydisInstructionInfo* info, 
    const ZydisOperandInfo* operand, uint16_t typecast)
{
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
        ZYDIS_CHECK(ZydisBufferAppend(
            buffer, bufferLen, offset, (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), str));
    }
    if (operand->mem.segment != ZYDIS_REGISTER_NONE)
    {
        if ((formatter->flags & ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SEGMENT) || 
            (((operand->mem.segment != ZYDIS_REGISTER_DS) || 
            (info->prefixes & ZYDIS_PREFIX_SEGMENT_DS)) && 
            ((operand->mem.segment != ZYDIS_REGISTER_SS) || 
            (info->prefixes & ZYDIS_PREFIX_SEGMENT_SS))))
        {
            ZYDIS_CHECK(ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "%s:", 
                ZydisRegisterGetString(operand->mem.segment)));   
        }
    }
    ZYDIS_CHECK(ZydisBufferAppend(
        buffer, bufferLen, offset, (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "["));
    if ((operand->mem.disp.dataSize != 0) && ((operand->mem.base == ZYDIS_REGISTER_NONE) ||
        (operand->mem.base == ZYDIS_REGISTER_EIP) || (operand->mem.base == ZYDIS_REGISTER_RIP)) &&
        (operand->mem.index == ZYDIS_REGISTER_NONE) && (operand->mem.scale == 0))
    {
        ZYDIS_CHECK(ZydisBufferAppendAbsoluteAddress(formatter, buffer, bufferLen, offset, info, 
            operand));   
    } else
    {
        if (operand->mem.base != ZYDIS_REGISTER_NONE)
        {
            ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE),
                    ZydisRegisterGetString(operand->mem.base)));
        }
        if (operand->mem.index != ZYDIS_REGISTER_NONE)
        {
            const char* c = (operand->mem.base != ZYDIS_REGISTER_NONE) ? "+" : "";
            ZYDIS_CHECK(ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "%s%s", c, 
                ZydisRegisterGetString(operand->mem.index)));
            if (operand->mem.scale)
            {
                ZYDIS_CHECK(ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                    (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "*%d", 
                    operand->mem.scale));    
            }
        }
        if ((operand->mem.disp.dataSize) && ((operand->mem.disp.value.sqword) || 
            ((operand->mem.base == ZYDIS_REGISTER_NONE) && 
            (operand->mem.index == ZYDIS_REGISTER_NONE))))
        {
            if ((operand->mem.disp.value.sqword < 0) && (
                (operand->mem.base != ZYDIS_REGISTER_NONE) || 
                (operand->mem.index != ZYDIS_REGISTER_NONE)))
            {
                ZYDIS_CHECK(
                    ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                        (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "-0x%02llX",
                        -operand->mem.disp.value.sqword));     
            } else
            {
                const char* sign = 
                    ((operand->mem.base == ZYDIS_REGISTER_NONE) && 
                    (operand->mem.index == ZYDIS_REGISTER_NONE)) ? "" : "+";
                ZYDIS_CHECK(
                    ZydisBufferAppendFormat(buffer, bufferLen, offset, 
                        (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "%s0x%02llX",
                        sign, operand->mem.disp.value.sqword)); 
            }
        }    
    }
    return ZydisBufferAppend(
        buffer, bufferLen, offset, (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "]");    
}

/* ---------------------------------------------------------------------------------------------- */
/* Intel style                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

static ZydisStatus ZydisBufferAppendOperandIntel(const ZydisInstructionFormatter* formatter, 
    char* buffer, size_t bufferLen, size_t* offset, const ZydisInstructionInfo* info, 
    const ZydisOperandInfo* operand, uint16_t typecast)
{
    switch (operand->type)
    {
    case ZYDIS_OPERAND_TYPE_REGISTER:
    {
        const char* reg = ZydisRegisterGetString(operand->reg);
        if (!reg)
        {
            reg = "invalid";
        }
        return ZydisBufferAppend(
            buffer, bufferLen, offset, (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), reg);
    }
    case ZYDIS_OPERAND_TYPE_MEMORY:
        return ZydisBufferAppendOperandIntelMemory(formatter, buffer, bufferLen, offset, info, 
            operand, typecast); 
    case ZYDIS_OPERAND_TYPE_POINTER:
        return ZydisBufferAppendFormat(buffer, bufferLen, offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "0x%02X:0x%02lX", 
            operand->ptr.segment, operand->ptr.offset);
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        return ZydisBufferAppendImmediate(formatter, buffer, bufferLen, offset, info, operand); 
    default:
        break;
    }
    return ZYDIS_STATUS_INVALID_PARAMETER;
}

static ZydisStatus ZydisFormatterFormatInstructionIntel(ZydisInstructionFormatter* formatter,
    const ZydisInstructionInfo* info, char* buffer, size_t bufferLen)
{
    size_t offset = 0;

    if ((info->prefixes & ZYDIS_PREFIX_ACCEPTS_REPNE) && 
        (info->prefixes & ZYDIS_PREFIX_REPNE))
    {
        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "repne "));
    }
    if ((info->prefixes & ZYDIS_PREFIX_ACCEPTS_REP) && (info->prefixes & ZYDIS_PREFIX_REP))
    {
        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "rep "));
    }
    if ((info->prefixes & ZYDIS_PREFIX_ACCEPTS_LOCK) && (info->prefixes & ZYDIS_PREFIX_LOCK))
    {
        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "lock "));
    }
    if (info->prefixes & ZYDIS_PREFIX_XACQUIRE)
    {
        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "xacquire "));
    } else if (info->prefixes & ZYDIS_PREFIX_XRELEASE)
    {
        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "xrelease "));
    }  

    const char* mnemonic = ZydisMnemonicGetString(info->mnemonic);
    if (!mnemonic)
    {
        mnemonic = "invalid";
    }
    ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
        (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), mnemonic));

    uint16_t typecast = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (info->operand[i].type == ZYDIS_OPERAND_TYPE_UNUSED)
        {
            break;
        }
        if (i == 0)
        {
            if (formatter->flags & ZYDIS_FORMATTER_FLAG_TAB_AFTER_MNEMONIC)
            {
                ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                    (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), "\t")); 
            } else
            {
                ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                    (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " "));
            }
        } else
        {
            if (formatter->flags & ZYDIS_FORMATTER_FLAG_NO_SPACE_BETWEEN_OPERANDS)
            {
                ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                    (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), ","));
            } else
            {
                ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                    (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), ", ")); 
            }
        }
        if (formatter->flags & ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SIZE)
        {
            if (info->operand[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
            {
                typecast = info->operand[i].size;
            }
        } else if (info->operand[i].type == ZYDIS_OPERAND_TYPE_MEMORY) 
        {
            switch (i)
            {
            case 0:
                typecast = ((info->operand[1].type == ZYDIS_OPERAND_TYPE_UNUSED) ||
                    (info->operand[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) ||
                    (info->operand[0].size != info->operand[1].size)) ? info->operand[0].size : 0;
                if (!typecast && (info->operand[1].type == ZYDIS_OPERAND_TYPE_REGISTER) && 
                    (info->operand[1].reg == ZYDIS_REGISTER_CL))
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
                        typecast = info->operand[0].size;
                    default:
                        break;
                    }
                }
                break;
            case 1:
            case 2:
                typecast = (info->operand[i - 1].size != info->operand[i].size) ? 
                    info->operand[i].size : 0;
                break;
            default:
                break;
            }
        }
        ZYDIS_CHECK(ZydisBufferAppendOperandIntel(formatter, buffer, bufferLen, &offset, info, 
            &info->operand[i], typecast));
        if (info->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX)
        {
            if (i == 0)
            {
                if (info->avx.maskRegister)
                {
                    ZYDIS_CHECK(ZydisBufferAppendFormat(buffer, bufferLen, &offset, 
                        (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {%s}",
                        ZydisRegisterGetString(info->avx.maskRegister))); 
                }
                if (info->avx.maskMode == ZYDIS_AVX_MASKMODE_ZERO)
                {
                    ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                        (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {z}"));    
                }
            } else
            {
                if (info->operand[i].type == ZYDIS_OPERAND_TYPE_MEMORY)
                {
                    switch (info->avx.broadcast)
                    {
                    case ZYDIS_AVX_BCSTMODE_2:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {1to2}"));
                        break;
                    case ZYDIS_AVX_BCSTMODE_4:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {1to4}"));
                        break;
                    case ZYDIS_AVX_BCSTMODE_8:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {1to8}"));
                        break;
                    case ZYDIS_AVX_BCSTMODE_16:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {1to16}"));
                        break;
                    default:
                        break;
                    }
                }
                if ((i == (info->operandCount - 1)) || ((i != (info->operandCount - 1)) && 
                    (info->operand[i + 1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)))
                {
                    switch (info->avx.roundingMode)
                    {
                    case ZYDIS_AVX_RNDMODE_INVALID:
                        if (info->avx.sae)
                        {
                            ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                                (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {sae}"));    
                        }
                        break;
                    case ZYDIS_AVX_RNDMODE_RN:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {rn-sae}"));
                        break;
                    case ZYDIS_AVX_RNDMODE_RD:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {rd-sae}"));
                        break;
                    case ZYDIS_AVX_RNDMODE_RU:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {ru-sae}"));
                        break;
                    case ZYDIS_AVX_RNDMODE_RZ:
                        ZYDIS_CHECK(ZydisBufferAppend(buffer, bufferLen, &offset, 
                            (formatter->flags & ZYDIS_FORMATTER_FLAG_UPPERCASE), " {rz-sae}"));
                        break;
                    default:
                        return ZYDIS_STATUS_INVALID_PARAMETER;
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

ZydisStatus ZydisFormatterInitInstructionFormatter(ZydisInstructionFormatter* formatter,
    ZydisFormatterStyle style)
{
    return ZydisFormatterInitInstructionFormatterEx(formatter, style, 0);    
}

ZydisStatus ZydisFormatterInitInstructionFormatterEx(
    ZydisInstructionFormatter* formatter, ZydisFormatterStyle style, ZydisFormatterFlags flags)
{
    if (!formatter || (style != ZYDIS_FORMATTER_STYLE_INTEL))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    formatter->style = style;
    formatter->flags = flags;
    formatter->addressFormat = ZYDIS_FORMATTER_ADDRESS_ABSOLUTE;
    formatter->displacementFormat = ZYDIS_FORMATTER_DISP_HEX_SIGNED;
    formatter->immediateFormat = ZYDIS_FORMATTER_IMM_HEX_UNSIGNED;
    formatter->symbolResolver = NULL;
    return ZYDIS_STATUS_SUCCESS;     
}

ZydisStatus ZydisFormatterGetSymbolResolver(const ZydisInstructionFormatter* formatter, 
    ZydisCustomSymbolResolver** symbolResolver)
{
    if (!formatter || !symbolResolver)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *symbolResolver = formatter->symbolResolver;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisFormatterSetSymbolResolver(ZydisInstructionFormatter* formatter, 
    ZydisCustomSymbolResolver* symbolResolver)
{
    if (!formatter)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    formatter->symbolResolver = symbolResolver;
    return ZYDIS_STATUS_SUCCESS;   
}

ZydisStatus ZydisFormatterFormatInstruction(ZydisInstructionFormatter* formatter, 
    const ZydisInstructionInfo* info, char* buffer, size_t bufferLen)
{
    if (!formatter || !info || !buffer || (bufferLen == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    switch (formatter->style)
    {
    case ZYDIS_FORMATTER_STYLE_INTEL:
        return ZydisFormatterFormatInstructionIntel(formatter, info, buffer, bufferLen);
    default:
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
