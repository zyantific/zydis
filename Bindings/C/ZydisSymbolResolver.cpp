/***************************************************************************************************

  Zyan Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : Joel Höner

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

#include "ZydisSymbolResolver.h"
#include <ZydisSymbolResolver.hpp>

/* CustomSymbolResolver ========================================================================= */

inline Zydis::BaseSymbolResolver* ZydisBaseSymbolResolver_CppPtr(
    ZydisBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<Zydis::BaseSymbolResolver*>(ctx);
}

inline const Zydis::BaseSymbolResolver* ZydisBaseSymbolResolver_CppPtr(
    const ZydisBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<const Zydis::BaseSymbolResolver*>(ctx);
}

inline ZydisBaseSymbolResolverContext* ZydisBaseSymbolResolver_CPtr(
    Zydis::BaseSymbolResolver *ptr)
{
    return reinterpret_cast<ZydisBaseSymbolResolverContext*>(ptr);
}

inline const ZydisBaseSymbolResolverContext* ZydisBaseSymbolResolver_CPtr(
    const Zydis::BaseSymbolResolver *ptr)
{
    return reinterpret_cast<const ZydisBaseSymbolResolverContext*>(ptr);
}

inline Zydis::InstructionInfo* ZydisInstructionInfo_CppPtr(
    ZydisInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Zydis::InstructionInfo), "broken struct");
    return reinterpret_cast<Zydis::InstructionInfo*>(ptr);
}

inline const Zydis::InstructionInfo* ZydisInstructionInfo_CppPtr(
    const ZydisInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Zydis::InstructionInfo), "broken struct");
    return reinterpret_cast<const Zydis::InstructionInfo*>(ptr);
}

inline ZydisInstructionInfo* ZydisInstructionInfo_CPtr(
    Zydis::InstructionInfo *ptr)
{
    return reinterpret_cast<ZydisInstructionInfo*>(ptr);
}

inline const ZydisInstructionInfo* ZydisInstructionInfo_CPtr(
    const Zydis::InstructionInfo *ptr)
{
    return reinterpret_cast<const ZydisInstructionInfo*>(ptr);
}

/* Internal helper class ----------------------------------------------------------------------- */

namespace
{

class ZydisCustomSymbolResolver : public Zydis::BaseSymbolResolver
{
    ZydisResolveSymbol_t    m_resolverCb;
    void*                   m_userData;
public:
    /**
     * @brief   Constructor.
     * @param   resolverCb The resolver callback.
     * @param   userData   User provided pointer to arbitrary data passed to resolve callback.
     */
    ZydisCustomSymbolResolver(ZydisResolveSymbol_t resolverCb, void *userData);
    /**
     * @brief   Destructor.
     */
    ~ZydisCustomSymbolResolver() override = default;
public:
    /**
     * @brief   Resolves a symbol.
     * @param   info        The instruction info.
     * @param   address     The address.
     * @param   offset      Reference to an unsigned 64 bit integer that receives an offset 
     *                      relative to the base address of the symbol.
     * @return  The name of the symbol, if the symbol was found, @c NULL if not.
     */
    const char* resolveSymbol(const Zydis::InstructionInfo &info, uint64_t address, 
        uint64_t &offset) override;
};

ZydisCustomSymbolResolver::ZydisCustomSymbolResolver(ZydisResolveSymbol_t resolverCb, 
    void *userData)
    : m_resolverCb(resolverCb)
    , m_userData(userData)
{
    
}

const char* ZydisCustomSymbolResolver::resolveSymbol(
    const Zydis::InstructionInfo &info, uint64_t address, uint64_t &offset)
{
    return m_resolverCb(ZydisInstructionInfo_CPtr(&info), address, &offset, m_userData);
}

} // anon namespace

/* C API implementation ------------------------------------------------------------------------ */

ZydisBaseSymbolResolverContext* ZydisCustomSymbolResolver_Create(
    ZydisResolveSymbol_t resolverCb,
    void *userData)
{
    return ZydisBaseSymbolResolver_CPtr(new ZydisCustomSymbolResolver(resolverCb, userData));
}

/* ============================================================================================= */