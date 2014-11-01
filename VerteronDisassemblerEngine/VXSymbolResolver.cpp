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
#include "VXSymbolResolver.h"

namespace Verteron
{

namespace Disassembler
{

VXBaseSymbolResolver::~VXBaseSymbolResolver()
{

}

const char* VXBaseSymbolResolver::resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
    uint64_t &offset)
{
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

VXExactSymbolResolver::~VXExactSymbolResolver()
{

}

const char* VXExactSymbolResolver::resolveSymbol(const VXInstructionInfo &info, uint64_t address, 
    uint64_t &offset)
{
    std::unordered_map<uint64_t, std::string>::const_iterator iterator = m_symbolMap.find(address);
    if (iterator != m_symbolMap.end())
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

}

}
