/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : athre0z
  Modifications   :

  Last change     : 04. February 2015

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

#include "VXInstructionFormatterC.h"
#include "VXInstructionFormatter.h"

/* Helpers ===================================================================================== */

namespace
{

inline Verteron::VXBaseSymbolResolver* VXBaseSymbolResolver_CppPtr(
    VXBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<Verteron::VXBaseSymbolResolver*>(ctx);
}

inline const Verteron::VXBaseSymbolResolver* VXBaseSymbolResolver_CppPtr(
    const VXBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<const Verteron::VXBaseSymbolResolver*>(ctx);
}

inline VXBaseSymbolResolverContext* VXBaseSymbolResolver_CPtr(
    Verteron::VXBaseSymbolResolver *ptr)
{
    return reinterpret_cast<VXBaseSymbolResolverContext*>(ptr);
}

inline const VXBaseSymbolResolverContext* VXBaseSymbolResolver_CPtr(
    const Verteron::VXBaseSymbolResolver *ptr)
{
    return reinterpret_cast<const VXBaseSymbolResolverContext*>(ptr);
}

inline Verteron::VXExactSymbolResolver* VXExactSymbolResolver_CppPtr(
    VXBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<Verteron::VXExactSymbolResolver*>(ctx);
}

inline const Verteron::VXExactSymbolResolver* VXExactSymbolResolver_CppPtr(
    const VXBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<const Verteron::VXExactSymbolResolver*>(ctx);
}

inline VXBaseSymbolResolverContext* VXExactSymbolResolver_CPtr(
    Verteron::VXExactSymbolResolver *ptr)
{
    return reinterpret_cast<VXBaseSymbolResolverContext*>(ptr);
}

inline const VXBaseSymbolResolverContext* VXExactSymbolResolver_CPtr(
    const Verteron::VXExactSymbolResolver *ptr)
{
    return reinterpret_cast<const VXBaseSymbolResolverContext*>(ptr);
}

inline Verteron::VXInstructionInfo* VXInstructionInfo_CppPtr(
    VXInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Verteron::VXInstructionInfo), "broken struct");
    return reinterpret_cast<Verteron::VXInstructionInfo*>(ptr);
}

inline const Verteron::VXInstructionInfo* VXInstructionInfo_CppPtr(
    const VXInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Verteron::VXInstructionInfo), "broken struct");
    return reinterpret_cast<const Verteron::VXInstructionInfo*>(ptr);
}

inline Verteron::VXBaseInstructionFormatter* VXBaseInstructionFormatter_CppPtr(
    VXBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<Verteron::VXBaseInstructionFormatter*>(ctx);
}

inline const Verteron::VXBaseInstructionFormatter* VXBaseInstructionFormatter_CppPtr(
    const VXBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<const Verteron::VXBaseInstructionFormatter*>(ctx);
}

inline Verteron::VXBaseInstructionFormatter* VXIntelInstructionFormatter_CppPtr(
    VXBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<Verteron::VXBaseInstructionFormatter*>(ctx);
}

inline const Verteron::VXBaseInstructionFormatter* VXIntelInstructionFormatter_CppPtr(
    const VXBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<const Verteron::VXBaseInstructionFormatter*>(ctx);
}

inline VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_CPtr(
    Verteron::VXBaseInstructionFormatter *ctx)
{
    return reinterpret_cast<VXBaseInstructionFormatterContext*>(ctx);
}

inline const VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_CPtr(
    const Verteron::VXBaseInstructionFormatter *ctx)
{
    return reinterpret_cast<const VXBaseInstructionFormatterContext*>(ctx);
}

}

/* VXBaseSymbolResolver ======================================================================== */

VXBaseSymbolResolverContext* VXBaseSymbolResolver_Create()
{
    return VXBaseSymbolResolver_CPtr(new Verteron::VXBaseSymbolResolver);
}

void VXBaseSymbolResolver_Release(
    VXBaseSymbolResolverContext *ctx)
{
    delete VXBaseSymbolResolver_CppPtr(ctx);
}

const char* VXBaseSymbolResolver_ResolveSymbol(
    VXBaseSymbolResolverContext *ctx,
    const VXInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset)
{
    return VXBaseSymbolResolver_CppPtr(ctx)->resolveSymbol(
        *VXInstructionInfo_CppPtr(info),
        address,
        *offset);
}

/* VXExactSymbolResolver ======================================================================= */

VXBaseSymbolResolverContext* VXExactSymbolResolver_Create(void)
{
    return VXExactSymbolResolver_CPtr(new Verteron::VXExactSymbolResolver);
}

bool VXExactSymbolResolver_ContainsSymbol(
    VXBaseSymbolResolverContext *ctx,
    uint64_t address)
{
    return VXExactSymbolResolver_CppPtr(ctx)->containsSymbol(address);
}

void VXExactSymbolResolverContext_SetSymbol(
    VXBaseSymbolResolverContext *ctx,
    uint64_t address, 
    const char* name)
{
    VXExactSymbolResolver_CppPtr(ctx)->setSymbol(address, name);
}

void VXExactSymbolResolverContext_RemoveSymbol(
    VXBaseSymbolResolverContext *ctx,
    uint64_t address)
{
    VXExactSymbolResolver_CppPtr(ctx)->removeSymbol(address);
}

void VXExactSymbolResolverContext_Clear(
    VXBaseSymbolResolverContext *ctx)
{
    VXExactSymbolResolver_CppPtr(ctx)->clear();
}

/* VXBaseInstructionFormatter ================================================================== */

const char* VXBaseInstructionFormatter_FormatInstruction(
    VXBaseInstructionFormatterContext *ctx,
    const VXInstructionInfo *info)
{
    return VXBaseInstructionFormatter_CppPtr(ctx)->formatInstruction(
        *VXInstructionInfo_CppPtr(info));
}

VXBaseSymbolResolverContext* VXBaseInstructionFormatter_GetSymbolResolver(
    const VXBaseInstructionFormatterContext *ctx)
{
    return VXBaseSymbolResolver_CPtr(
        VXBaseInstructionFormatter_CppPtr(ctx)->getSymbolResolver());
}

void VXBaseInstructionFormatter_SetSymbolResolver(
    VXBaseInstructionFormatterContext *ctx,
    VXBaseSymbolResolverContext *resolver)
{
    VXBaseInstructionFormatter_CppPtr(ctx)->setSymbolResolver(
        VXBaseSymbolResolver_CppPtr(resolver));
}

void VXBaseInstructionFormatter_Release(
    VXBaseInstructionFormatterContext *ctx)
{
    delete VXBaseInstructionFormatter_CppPtr(ctx);
}

/* VXIntelInstructionFormatter ================================================================ */

VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_Create(void)
{
    return VXIntelInstructionFormatter_CPtr(new Verteron::VXIntelInstructionFormatter);
}

VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_CreateEx(
    VXBaseSymbolResolverContext *resolver)
{
    return VXIntelInstructionFormatter_CPtr(new Verteron::VXIntelInstructionFormatter(
        VXBaseSymbolResolver_CppPtr(resolver)));
}

/* ============================================================================================= */