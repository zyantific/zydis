/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   :

  Last change     : 22. October 2014

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

**************************************************************************************************/
#include "VXInstructionFormatter.h"
#include <cstdarg>

namespace Verteron
{

namespace Disassembler
{

const char* VXBaseInstructionFormatter::m_registerStrings[] =
{
    /* 8 bit general purpose registers */
    "al",       "cl",       "dl",       "bl",
    "ah",       "ch",       "dh",       "bh",
    "spl",      "bpl",      "sil",      "dil",
    "r8b",      "r9b",      "r10b",     "r11b",
    "r12b",     "r13b",     "r14b",     "r15b",
    /* 16 bit general purpose registers */
    "ax",       "cx",       "dx",       "bx",
    "sp",       "bp",       "si",       "di",
    "r8w",      "r9w",      "r10w",     "r11w",
    "r12w",     "r13w",     "r14w",     "r15w",
    /* 32 bit general purpose registers */
    "eax",      "ecx",      "edx",      "ebx",
    "esp",      "ebp",      "esi",      "edi",
    "r8d",      "r9d",      "r10d",     "r11d",
    "r12d",     "r13d",     "r14d",     "r15d",
    /* 64 bit general purpose registers */
    "rax",      "rcx",      "rdx",      "rbx",
    "rsp",      "rbp",      "rsi",      "rdi",
    "r8",       "r9",       "r10",      "r11",
    "r12",      "r13",      "r14",      "r15",
    /* segment registers */
    "es",       "cs",       "ss",       
    "ds",       "fs",       "gs",
    /* control registers */
    "cr0",      "cr1",      "cr2",      "cr3",
    "cr4",      "cr5",      "cr6",      "cr7",
    "cr8",      "cr9",      "cr10",     "cr11",
    "cr12",     "cr13",     "cr14",     "cr15",
    /* debug registers */
    "dr0",      "dr1",      "dr2",      "dr3",
    "dr4",      "dr5",      "dr6",      "dr7",
    "dr8",      "dr9",      "dr10",     "dr11",
    "dr12",     "dr13",     "dr14",     "dr15",
    /* mmx registers */
    "mm0",      "mm1",      "mm2",      "mm3",
    "mm4",      "mm5",      "mm6",      "mm7",
    /* x87 registers */
    "st0",      "st1",      "st2",      "st3",
    "st4",      "st5",      "st6",      "st7",
    /* extended multimedia registers */
    "xmm0",     "xmm1",     "xmm2",     "xmm3",
    "xmm4",     "xmm5",     "xmm6",     "xmm7",
    "xmm8",     "xmm9",     "xmm10",    "xmm11",
    "xmm12",    "xmm13",    "xmm14",    "xmm15",
    /* 256 bit multimedia registers */
    "ymm0",     "ymm1",     "ymm2",     "ymm3",
    "ymm4",     "ymm5",     "ymm6",     "ymm7",
    "ymm8",     "ymm9",     "ymm10",    "ymm11",
    "ymm12",    "ymm13",    "ymm14",    "ymm15",
    /* instruction pointer register */
    "rip"
};

void VXBaseInstructionFormatter::internalFormatInstruction(VXInstructionInfo const& info)
{
    // Nothing to do here
}

VXBaseInstructionFormatter::VXBaseInstructionFormatter()
    : m_symbolResolver(nullptr)
{

}

VXBaseInstructionFormatter::VXBaseInstructionFormatter(VXBaseSymbolResolver *symbolResolver)
    : m_symbolResolver(symbolResolver)
{

}

const char* VXBaseInstructionFormatter::formatInstruction(const VXInstructionInfo &info)
{
    // Clears the internal string buffer
    outputClear();
    // Calls the virtual format method that actually formats the instruction
    internalFormatInstruction(info);
    if (m_outputBuffer.size() == 0)
    {
        // The basic instruction formatter only returns the instruction menmonic.
        return Internal::GetInstructionMnemonicString(info.mnemonic);
    } 
    // Return the formatted instruction string
    return outputString();
}

VXBaseInstructionFormatter::~VXBaseInstructionFormatter()
{

}

void VXBaseInstructionFormatter::outputClear()
{
    m_outputBuffer.clear();
}

char const* VXBaseInstructionFormatter::outputString()
{
    return &m_outputBuffer[0];
}

void VXBaseInstructionFormatter::outputAppend(char const *text)
{
    // Get the string length including the null-terminator char
    size_t strLen = strlen(text) + 1;
    // Get the buffer capacity and size
    size_t bufCap = m_outputBuffer.capacity();
    size_t bufLen = m_outputBuffer.size();
    // Decrease the offset by one, to exclude already existing null-terminator chars in the 
    // output buffer
    size_t offset = (bufLen) ? bufLen - 1 : 0;
    // Resize capacity of the output buffer on demand and add some extra space to improve the
    // performance 
    if (bufCap <= (bufLen + strLen))
    {
        m_outputBuffer.reserve(bufCap + strLen + 256);
    }
    // Append the text
    m_outputBuffer.resize(offset + strLen);
    memcpy(&m_outputBuffer[offset], text, strLen);
}

void VXBaseInstructionFormatter::outputAppendFormatted(char const *format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    // Get the string length including the null-terminator char
    size_t strLen = _vscprintf(format, arguments) + 1;
    // Get the buffer capacity and size
    size_t bufCap = m_outputBuffer.capacity();
    size_t bufLen = m_outputBuffer.size();
    // Decrease the offset by one, to exclude already existing null-terminator chars in the 
    // output buffer
    size_t offset = (bufLen) ? bufLen - 1 : 0;
    if (strLen > 1)
    {
        // Resize capacity of the output buffer on demand and add some extra space to improve the
        // performance 
        if (bufCap < (bufLen + strLen))
        {
            m_outputBuffer.reserve(bufCap + strLen + 256);
        }
        // Append the formatted text
        m_outputBuffer.resize(offset + strLen);
        vsnprintf_s(&m_outputBuffer[offset], strLen, strLen, format, arguments);
    }
    va_end(arguments);
}

uint64_t VXBaseInstructionFormatter::calcAbsoluteTarget(const VXInstructionInfo &info, 
    const VXOperandInfo &operand) const
{
    switch (operand.size)
    {
    case 8:
        return (info.instructionPointer + info.length + operand.lval.sbyte);
    case 16:
        return (info.instructionPointer + info.length + operand.lval.sword);
    case 32:
    case 64:
        return (info.instructionPointer + info.length + operand.lval.sdword);
    default:
        assert(0);
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void VXIntelInstructionFormatter::outputAppendAddress(const VXInstructionInfo &info, 
    uint64_t address)
{
    uint64_t offset = 0;
    const char* name = resolveSymbol(info, address, offset);
    if (name)
    {
        if (offset)
        {
            outputAppendFormatted("%s+%.2llX", name, offset);   
        } else
        {
            outputAppend(name);     
        }
    } else
    {
        if (info.flags & IF_DISASSEMBLER_MODE_16)
        {
            outputAppendFormatted("%.4X", address);
        } else if (info.flags & IF_DISASSEMBLER_MODE_32)
        {
            outputAppendFormatted("%.8lX", address);
        } else if (info.flags & IF_DISASSEMBLER_MODE_64)
        {
            outputAppendFormatted("%.16llX", address);
        } else
        {
            assert(0);
        }
    }
}

void VXIntelInstructionFormatter::formatOperand(const VXInstructionInfo &info, 
    const VXOperandInfo &operand)
{
    switch (operand.type)
    {
    case VXOperandType::REGISTER: 
        outputAppend(registerToString(operand.base));
        break;
    case VXOperandType::MEMORY: 
        // TODO: resolve symbols for displacement only and RIP based memory operands
        if (info.flags & IF_PREFIX_SEGMENT)
        {
            outputAppendFormatted("%s:", registerToString(info.segmentRegister));    
        }
        outputAppend("[");
        if (operand.base == VXRegister::RIP)
        {
            // TODO: Add option
            outputAppendAddress(info, calcAbsoluteTarget(info, operand));   
        } else
        {
            if (operand.base != VXRegister::NONE)
            {
                outputAppend(registerToString(operand.base)); 
            }
            if (operand.index != VXRegister::NONE) 
            {
                outputAppendFormatted("%s%s", operand.base != VXRegister::NONE ? "+" : "",
                    registerToString(operand.index));
                if (operand.scale) 
                {
                    outputAppendFormatted("*%d", operand.scale);
                }
            }
            if (operand.lval.uqword || 
                (operand.base == VXRegister::NONE && operand.index == VXRegister::NONE)) 
            {
                if (operand.base == VXRegister::NONE && operand.index == VXRegister::NONE)
                {
                    // Assume the displacement value is unsigned
                    assert(operand.scale == 0);
                    assert(operand.offset != 8);
                    uint64_t value = 0;
                    switch (operand.offset)
                    {
                    case 16:
                        value = operand.lval.uword;
                        break;
                    case 32:
                        value = operand.lval.udword;
                        break;
                    case 64:
                        value = operand.lval.uqword;
                        break;
                    default:
                        assert(0);
                    }
                    outputAppendFormatted("%.2llX", value);
                } else
                {
                    // The displacement value might be negative
                    assert(operand.offset != 64);  
                    int64_t value = 0;
                    switch (operand.offset)
                    {
                    case 8:
                        value = operand.lval.sbyte;
                        break;
                    case 16:
                        value = operand.lval.sword;
                        break;
                    case 32:
                        value = operand.lval.sdword;
                        break;
                    default:
                        assert(0);
                    }
                    if (value < 0)
                    {
                        outputAppendFormatted("-%.2lX", -value);
                    } else
                    {
                        outputAppendFormatted("%s%.2lX", (operand.base != VXRegister::NONE || 
                            operand.index != VXRegister::NONE) ? "+" : "", value);
                    }
                }
            }
        }
        outputAppend("]");
        break;
    case VXOperandType::POINTER:
        // TODO: resolve symbols
        switch (operand.size)
        {
        case 32:
            outputAppendFormatted("word %.4X:%.4X", operand.lval.ptr.seg, 
                operand.lval.ptr.off & 0xFFFF);
            break;
        case 48:
            outputAppendFormatted("dword %.4X:%.8lX", operand.lval.ptr.seg, operand.lval.ptr.off);
            break;
        default:
            assert(0);
        }
        break;
    case VXOperandType::IMMEDIATE: 
        {
            // TODO: resolve symbols
            uint64_t value = 0;
            switch (operand.size) 
            {
            case 8 : 
                value = operand.lval.ubyte; 
                break;
            case 16: 
                value = operand.lval.uword; 
                break;
            case 32: 
                value = operand.lval.udword; 
                break;
            case 64: 
                value = operand.lval.uqword; 
                break;
            default: 
                assert(0);
            }   
            outputAppendFormatted("%.2llX", value);
        }
        break;
    case VXOperandType::REL_IMMEDIATE: 
        {
            if (operand.size == 8)
            {
                outputAppend("short ");
            }
            outputAppendAddress(info, calcAbsoluteTarget(info, operand));
        }
        break;
    case VXOperandType::CONSTANT: 
        outputAppendFormatted("%d", operand.lval.udword);
        break;
    default: 
        assert(0);
        break;
    }
}

void VXIntelInstructionFormatter::internalFormatInstruction(const VXInstructionInfo &info)
{
    // Append string prefixes
    if (info.flags & IF_PREFIX_LOCK)
    {
        outputAppend("lock ");
    }
    if (info.flags & IF_PREFIX_REPZ)
    {
        outputAppend("rep ");
    } else if (info.flags & IF_PREFIX_REPNZ)
    {
        outputAppend("repne ");
    }
    // Append the instruction mnemonic
    outputAppend(Internal::GetInstructionMnemonicString(info.mnemonic));
    // Append the first operand
    if (info.operand[0].type != VXOperandType::NONE)
    {
        outputAppend(" ");
        formatOperand(info, info.operand[0]);
    }
    // Append the second operand
    if (info.operand[1].type != VXOperandType::NONE)
    {
        outputAppend(", ");
        formatOperand(info, info.operand[1]);
    }
    // Append the third operand
    if (info.operand[2].type != VXOperandType::NONE)
    {
        outputAppend(", ");
        formatOperand(info, info.operand[2]);
    }
    // Append the fourth operand
    if (info.operand[3].type != VXOperandType::NONE)
    {
        outputAppend(", ");
        formatOperand(info, info.operand[3]);
    }
}

VXIntelInstructionFormatter::VXIntelInstructionFormatter()
    : VXBaseInstructionFormatter()
{

}

VXIntelInstructionFormatter::VXIntelInstructionFormatter(VXBaseSymbolResolver* symbolResolver)
    : VXBaseInstructionFormatter(symbolResolver)
{

}

VXIntelInstructionFormatter::~VXIntelInstructionFormatter()
{

}

}

}
