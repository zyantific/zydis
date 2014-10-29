/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   :

  Last change     : 29. October 2014

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

#include <string>
#include <unordered_map>
#include "VXDisassemblerTypes.h"

namespace Verteron
{

namespace Disassembler
{

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

}

}
