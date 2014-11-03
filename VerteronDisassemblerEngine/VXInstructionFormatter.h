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
#pragma once

#include <vector>
#include <unordered_map>
#include "VXDisassemblerTypes.h"

namespace Verteron
{

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Base class for all symbol resolver implementations.
 */
class VXBaseSymbolResolver
{
public:
    /**
     * @brief   Destructor.
     */
    virtual ~VXBaseSymbolResolver();
public:
    /**
     * @brief   Resolves a symbol.
     * @param   info        The instruction info.
     * @param   address     The address.
     * @param   offset      Reference to an unsigned 64 bit integer that receives an offset 
     *                      relative to the base address of the symbol.
     * @return  The name of the symbol, if the symbol was found, @c NULL if not.
     */
    virtual const char* resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
        uint64_t &offset);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Base class for all instruction formatter implementations.
 */
class VXBaseInstructionFormatter
{
private:
    static const char    *m_registerStrings[];
    VXBaseSymbolResolver *m_symbolResolver;
    std::vector<char>     m_outputBuffer;
    size_t                m_outputStringLen;
    bool                  m_outputUppercase;
protected:
    /**
     * @brief   Clears the output string buffer.
     */
    void outputClear();
    /**
     * @brief   Returns the content of the output string buffer.
     * @return  Pointer to the content of the ouput string buffer.
     */
    const char* outputString();
    /**
     * @brief   Appends text to the ouput string buffer.
     * @param   text    The text.
     */
    void outputAppend(const char *text);
    /**
     * @brief   Appends formatted text to the output string buffer.
     * @param   format  The format string.
     */
    void outputAppendFormatted(const char *format, ...);
    /**
     * @brief   Changes automatic conversion of characters to uppercase.
     * @param   uppercase   Set true to enable automatic uppercase conversion.
     */
    void outputSetUppercase(bool uppercase);
    /**
     * @brief   Appends a formatted address to the output string buffer.
     * @param   info            The instruction info.
     * @param   address         The address.
     * @param   resolveSymbols  If this parameter is true, the method will try to display a
     *                          smybol name instead of the numeric value.
     */
    void outputAppendAddress(const VXInstructionInfo &info, uint64_t address, 
        bool resolveSymbols = true);
    /**
     * @brief   Appends a formatted immediate value to the output string buffer.
     * @param   info            The instruction info.
     * @param   operand         The immediate operand.
     * @param   resolveSymbols  If this parameter is true, the method will try to display a
     *                          smybol name instead of the numeric value.
     */
    void outputAppendImmediate(const VXInstructionInfo &info, const VXOperandInfo &operand,
        bool resolveSymbols = false);
    /**
     * @brief   Appends a formatted memory displacement value to the output string buffer.
     * @param   info    The instruction info.
     * @param   operand The memory operand.
     */
    void outputAppendDisplacement(const VXInstructionInfo &info, const VXOperandInfo &operand);
protected:
    /**
     * @brief   Returns the string representation of a given register.
     * @param   reg The register.
     * @return  The string representation of the given register.
     */
    const char* registerToString(VXRegister reg) const;
    /**
     * @brief   Resolves a symbol.
     * @param   info        The instruction info.
     * @param   address     The address.
     * @param   offset      Reference to an unsigned 64 bit integer that receives an offset 
     *                      relative to the base address of the symbol.
     * @return  The name of the symbol, if the symbol was found, @c NULL if not.
     */
    const char* resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
        uint64_t &offset) const;
protected:
    /**
     * @brief   Override this method to implement a custom disassembly syntax. Use the 
     *          @c outputAppend and @c outputAppendFormatted methods to fill the internal
     *          string buffer.
     * @param   info    The instruction info.
     */
    virtual void internalFormatInstruction(const VXInstructionInfo &info);
    /**
     * @brief   Default constructor.
     */
    VXBaseInstructionFormatter();
    /**
     * @brief   Constructor.
     * @param   symbolResolver  Pointer to a symbol resolver instance or @c NULL, if no smybol
     *                          resolver should be used.
     */
    explicit VXBaseInstructionFormatter(VXBaseSymbolResolver *symbolResolver);
public:
    /**
     * @brief   Destructor.
     */
    virtual ~VXBaseInstructionFormatter();
public:
    /**
     * @brief   Formats a decoded instruction.
     * @param   info    The instruction info.
     * @return  Pointer to the formatted instruction string.
     */
    const char* formatInstruction(const VXInstructionInfo &info);
public:
    /**
     * @brief   Returns a pointer to the current symbol resolver.
     * @return  Pointer to the current symbol resolver or @c NULL, if no symbol resolver is used.
     */
    VXBaseSymbolResolver* getSymbolResolver() const;
    /**
     * @brief   Sets a new symbol resolver.
     * @param   symbolResolver  Pointer to a symbol resolver instance or @c NULL, if no smybol
     *                          resolver should be used.
     */
    void setSymbolResolver(VXBaseSymbolResolver *symbolResolver);
};

inline void VXBaseInstructionFormatter::outputSetUppercase(bool uppercase)
{
    m_outputUppercase = uppercase;
}

inline char const* VXBaseInstructionFormatter::registerToString(VXRegister reg) const
{
    if (reg == VXRegister::NONE)
    {
        return "error";   
    }
    return m_registerStrings[static_cast<uint16_t>(reg) - 1]; 
}

inline char const* VXBaseInstructionFormatter::resolveSymbol(const VXInstructionInfo &info, 
    uint64_t address, uint64_t &offset) const
{
    if (m_symbolResolver)
    {
        return m_symbolResolver->resolveSymbol(info, address, offset);    
    }
    return nullptr;
}

inline VXBaseSymbolResolver* VXBaseInstructionFormatter::getSymbolResolver() const
{
    return m_symbolResolver;
}

inline void VXBaseInstructionFormatter::setSymbolResolver(VXBaseSymbolResolver *symbolResolver)
{
    m_symbolResolver = symbolResolver;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Intel syntax instruction formatter.
 */
class VXIntelInstructionFormatter : public VXBaseInstructionFormatter
{
private:
    /**
     * @brief   Appends an operand cast to the output string buffer.
     * @param   info    The instruction info.
     * @param   operand The operand.
     */
    void outputAppendOperandCast(const VXInstructionInfo &info, const VXOperandInfo &operand);
    /**
     * @brief   Formats the specified operand and appends the resulting string to the output
     *          buffer.
     * @param   info    The instruction info.
     * @param   operand The operand.
     */
    void formatOperand(const VXInstructionInfo &info, const VXOperandInfo &operand);
protected:
    /**
     * @brief   Fills the internal string buffer with an intel style formatted instruction string.
     * @param   info    The instruction info.
     */
    void internalFormatInstruction(const VXInstructionInfo &info) override;
public:
    /**
     * @brief   Default constructor.
     */
    VXIntelInstructionFormatter();
    /**
     * @brief   Constructor.
     * @param   symbolResolver  Pointer to a symbol resolver instance or @c NULL, if no smybol
     *                          resolver should be used.
     */
    explicit VXIntelInstructionFormatter(VXBaseSymbolResolver *symbolResolver);
    /**
     * @brief   Destructor.
     */
    ~VXIntelInstructionFormatter() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Simple symbol resolver that only matches exact addresses.
 */
class VXExactSymbolResolver : public VXBaseSymbolResolver
{
private:
    std::unordered_map<uint64_t, std::string> m_symbolMap;
public:
    /**
     * @brief   Destructor.
     */
    ~VXExactSymbolResolver() override;
public:
    /**
     * @brief   Resolves a symbol.
     * @param   info        The instruction info.
     * @param   address     The address.
     * @param   offset      Reference to an unsigned 64 bit integer that receives an offset 
     *                      relative to the base address of the symbol.
     * @return  The name of the symbol, if the symbol was found, @c NULL if not.
     */
    const char* resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
        uint64_t &offset) override;
public:
    /**
     * @brief   Query if the given address is a known symbol.
     * @param   address The address.
     * @return  True if the address is known, false if not.
     */
    bool containsSymbol(uint64_t address) const;
    /**
     * @brief   Adds or changes a symbol.
     * @param   address The address.
     * @param   name    The symbol name.
     */
    void setSymbol(uint64_t address, const char* name);
    /**
     * @brief   Removes the symbol described by address. This will invalidate all char pointers 
     *          to the specific symbol name.
     * @param   address The address.
     */
    void removeSymbol(uint64_t address);
    /**
     * @brief   Clears the symbol tree.
     */
    void clear();
};

///////////////////////////////////////////////////////////////////////////////////////////////////

}
