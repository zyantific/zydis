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
#include "VXDisassemblerUtils.h"
#include <cstdarg>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <string>

namespace Verteron
{

///////////////////////////////////////////////////////////////////////////////////////////////////

VXBaseSymbolResolver::~VXBaseSymbolResolver()
{

}

const char* VXBaseSymbolResolver::resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
    uint64_t &offset)
{
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

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

void VXBaseInstructionFormatter::internalFormatInstruction(const VXInstructionInfo &info)
{
    // Nothing to do here
}

VXBaseInstructionFormatter::VXBaseInstructionFormatter()
    : m_symbolResolver(nullptr)
    , m_outputStringLen(0)
    , m_outputUppercase(false)
{

}

VXBaseInstructionFormatter::VXBaseInstructionFormatter(VXBaseSymbolResolver *symbolResolver)
    : m_symbolResolver(symbolResolver)
    , m_outputStringLen(0)
    , m_outputUppercase(false)
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
        return Internal::VDEGetInstructionMnemonicString(info.mnemonic);
    } 
    // Return the formatted instruction string
    return outputString();
}

VXBaseInstructionFormatter::~VXBaseInstructionFormatter()
{

}

void VXBaseInstructionFormatter::outputClear()
{
    m_outputStringLen = 0;
}

char const* VXBaseInstructionFormatter::outputString()
{
    return &m_outputBuffer[0];
}

 void VXBaseInstructionFormatter::outputAppend(char const *text)
 {
    // Get the string length including the null-terminator char
    size_t strLen = strlen(text) + 1;
    // Get the buffer size
    size_t bufLen = m_outputBuffer.size();
    // Decrease the offset by one, to exclude already existing null-terminator chars in the
    // output buffer
    size_t offset = (m_outputStringLen) ? m_outputStringLen - 1 : 0;
    // Resize capacity of the output buffer on demand and add some extra space to improve the
    // performance
    if (bufLen <= (m_outputStringLen + strLen))
    {
        m_outputBuffer.resize(bufLen + strLen + 512);
    }
    // Write the text to the output buffer
    memcpy(&m_outputBuffer[offset], text, strLen);
    // Increase the string length
    m_outputStringLen = offset + strLen;
    // Convert to uppercase
    if (m_outputUppercase)
    {
        for (size_t i = offset; i < m_outputStringLen - 1; ++i)
        {
            m_outputBuffer[i] = toupper(m_outputBuffer[i]);
        }
    }
 }

 void VXBaseInstructionFormatter::outputAppendFormatted(char const *format, ...)
 {
    va_list arguments;
    va_start(arguments, format);
    // Get the buffer size
    size_t bufLen = m_outputBuffer.size();
    // Decrease the offset by one, to exclude already existing null-terminator chars in the
    // output buffer
    size_t offset = (m_outputStringLen) ? m_outputStringLen - 1 : 0;
    // Resize the output buffer on demand and add some extra space to improve the performance
    if ((bufLen - m_outputStringLen) < 256)
    {
        bufLen = bufLen + 512;
        m_outputBuffer.resize(bufLen);
    }
    int strLen = 0;
    do
    {
        // If the formatted text did not fit in the output buffer, resize it, and try again
        if (strLen < 0)
        {
            m_outputBuffer.resize(bufLen + 512);
            return outputAppendFormatted(format, arguments);
        }
        // Write the formatted text to the output buffer
        assert((bufLen - offset) > 0);
        strLen =
            std::vsnprintf(&m_outputBuffer[offset], bufLen - offset, format, arguments);
    } while (strLen < 0);
    // Increase the string length
    m_outputStringLen = offset + strLen + 1;
    // Convert to uppercase
    if (m_outputUppercase)
    {
        for (size_t i = offset; i < m_outputStringLen - 1; ++i)
        {
            m_outputBuffer[i] = toupper(m_outputBuffer[i]);
        }
    }
    va_end(arguments);
}

void VXBaseInstructionFormatter::outputAppendAddress(const VXInstructionInfo &info, 
    uint64_t address, bool resolveSymbols)
{
    uint64_t offset = 0;
    const char* name = nullptr;
    if (resolveSymbols)
    {
        name = resolveSymbol(info, address, offset);
    }
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

void VXBaseInstructionFormatter::outputAppendImmediate(const VXInstructionInfo &info, 
    const VXOperandInfo &operand, bool resolveSymbols)
{
    assert(operand.type == VXOperandType::IMMEDIATE);
    uint64_t value = 0;
    if (operand.signed_lval && (operand.size != info.operand_mode)) 
    {
        if (operand.size == 8) 
        {
            value = static_cast<int64_t>(operand.lval.sbyte);
        } else 
        {
            assert(operand.size == 32);
            value = static_cast<int64_t>(operand.lval.sdword);
        }
        if (info.operand_mode < 64) 
        {
            value = value & ((1ull << info.operand_mode) - 1ull);
        }
    } else 
    {
        switch (operand.size) 
        {
        case 8: 
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
    }
    uint64_t offset = 0;
    const char* name = nullptr;
    if (resolveSymbols)
    {
        name = resolveSymbol(info, value, offset);
    }
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
        outputAppendFormatted("%.2llX", value);
    }
}

void VXBaseInstructionFormatter::outputAppendDisplacement(const VXInstructionInfo &info, 
    const VXOperandInfo &operand)
{
    assert(operand.offset > 0);
    if ((operand.base == VXRegister::NONE) && (operand.index == VXRegister::NONE))
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

///////////////////////////////////////////////////////////////////////////////////////////////////

void VXIntelInstructionFormatter::outputAppendOperandCast(const VXInstructionInfo &info, 
    const VXOperandInfo &operand)
{
    switch(operand.size) 
    {
    case 8:     
        outputAppend("byte ptr " ); 
        break;
    case 16:    
        outputAppend("word ptr " ); 
        break;
    case 32:    
        outputAppend("dword ptr "); 
        break;
    case 64:    
        outputAppend("qword ptr "); 
        break;
    case 80:    
        outputAppend("tword ptr "); 
        break;
    case 128:   
        outputAppend("oword ptr "); 
        break;
    case 256:   
        outputAppend("yword ptr "); 
        break;
    default: 
        break;
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
        if (info.flags & IF_PREFIX_SEGMENT)
        {
            outputAppendFormatted("%s:", registerToString(info.segment));    
        }
        outputAppend("[");
        if (operand.base == VXRegister::RIP)
        {
            // TODO: Add option
            outputAppendAddress(info, VDECalcAbsoluteTarget(info, operand), true);   
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
            if (operand.offset) 
            {
                outputAppendDisplacement(info, operand);
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
            outputAppendImmediate(info, operand, true);
        }
        break;
    case VXOperandType::REL_IMMEDIATE: 
        {
            if (operand.size == 8)
            {
                outputAppend("short ");
            }
            outputAppendAddress(info, VDECalcAbsoluteTarget(info, operand), true);
        }
        break;
    case VXOperandType::CONSTANT: 
        outputAppendFormatted("%.2X", operand.lval.udword);
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
    if (info.flags & IF_PREFIX_REP)
    {
        outputAppend("rep ");
    } else if (info.flags & IF_PREFIX_REPNE)
    {
        outputAppend("repne ");
    }
    // Append the instruction mnemonic
    outputAppend(Internal::VDEGetInstructionMnemonicString(info.mnemonic));
    // Append the first operand
    if (info.operand[0].type != VXOperandType::NONE)
    {
        outputAppend(" ");
        bool cast = false;
        if (info.operand[0].type == VXOperandType::MEMORY) 
        {
            if (info.operand[1].type == VXOperandType::IMMEDIATE ||
                info.operand[1].type == VXOperandType::CONSTANT ||
                info.operand[1].type == VXOperandType::NONE ||
                (info.operand[0].size != info.operand[1].size)) 
            {
                cast = true;
            } else if (info.operand[1].type == VXOperandType::REGISTER &&
                info.operand[1].base == VXRegister::CL) 
            {
                switch (info.mnemonic) 
                {
                case VXInstructionMnemonic::RCL:
                case VXInstructionMnemonic::ROL:
                case VXInstructionMnemonic::ROR:
                case VXInstructionMnemonic::RCR:
                case VXInstructionMnemonic::SHL:
                case VXInstructionMnemonic::SHR:
                case VXInstructionMnemonic::SAR:
                    cast = true;
                    break;
                default: 
                    break;
                }
            }
        }
        if (cast)
        {
            outputAppendOperandCast(info, info.operand[0]);
        }
        formatOperand(info, info.operand[0]);
    }
    // Append the second operand
    if (info.operand[1].type != VXOperandType::NONE)
    {
        outputAppend(", ");
        bool cast = false;
        if (info.operand[1].type == VXOperandType::MEMORY &&
            info.operand[0].size != info.operand[1].size &&
            ((info.operand[0].type != VXOperandType::REGISTER) ||
             ((info.operand[0].base != VXRegister::ES) && 
             (info.operand[0].base != VXRegister::CS) &&
             (info.operand[0].base != VXRegister::SS) &&
             (info.operand[0].base != VXRegister::DS) &&
             (info.operand[0].base != VXRegister::FS) &&
             (info.operand[0].base != VXRegister::GS)))) 
        {
            cast = true;
        }
        if (cast)
        {
            outputAppendOperandCast(info, info.operand[1]);
        }
        formatOperand(info, info.operand[1]);
    }
    // Append the third operand
    if (info.operand[2].type != VXOperandType::NONE)
    {
        outputAppend(", ");
        bool cast = false;
        if (info.operand[2].type == VXOperandType::MEMORY && 
            (info.operand[2].size != info.operand[1].size)) 
        {
            cast = true;
        }
        if (cast)
        {
            outputAppendOperandCast(info, info.operand[2]);
        }
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

///////////////////////////////////////////////////////////////////////////////////////////////////

VXExactSymbolResolver::~VXExactSymbolResolver()
{

}

const char* VXExactSymbolResolver::resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
    uint64_t &offset)
{
    std::unordered_map<uint64_t, std::string>::const_iterator iterator = m_symbolMap.find(address);
    if (iterator != m_symbolMap.cend())
    {
        offset = 0;
        return iterator->second.c_str();
    }
    return nullptr;
}

bool VXExactSymbolResolver::containsSymbol(uint64_t address) const
{
    std::unordered_map<uint64_t, std::string>::const_iterator iterator = m_symbolMap.find(address);
    return (iterator != m_symbolMap.end());
}

void VXExactSymbolResolver::setSymbol(uint64_t address, const char* name)
{
    m_symbolMap[address].assign(name);
}

void VXExactSymbolResolver::removeSymbol(uint64_t address)
{
    m_symbolMap.erase(address);
}

void VXExactSymbolResolver::clear()
{
    m_symbolMap.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

}
