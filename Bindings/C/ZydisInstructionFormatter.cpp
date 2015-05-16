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

#include "ZydisInstructionFormatter.h"
#include "ZydisInstructionFormatter.hpp"

/* Helpers ===================================================================================== */

namespace
{

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

inline Zydis::ExactSymbolResolver* ZydisExactSymbolResolver_CppPtr(
    ZydisBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<Zydis::ExactSymbolResolver*>(ctx);
}

inline const Zydis::ExactSymbolResolver* ZydisExactSymbolResolver_CppPtr(
    const ZydisBaseSymbolResolverContext *ctx)
{
    return reinterpret_cast<const Zydis::ExactSymbolResolver*>(ctx);
}

inline ZydisBaseSymbolResolverContext* ZydisExactSymbolResolver_CPtr(
    Zydis::ExactSymbolResolver *ptr)
{
    return reinterpret_cast<ZydisBaseSymbolResolverContext*>(ptr);
}

inline const ZydisBaseSymbolResolverContext* ZydisExactSymbolResolver_CPtr(
    const Zydis::ExactSymbolResolver *ptr)
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

inline Zydis::BaseInstructionFormatter* ZydisBaseInstructionFormatter_CppPtr(
    ZydisBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<Zydis::BaseInstructionFormatter*>(ctx);
}

inline const Zydis::BaseInstructionFormatter* ZydisBaseInstructionFormatter_CppPtr(
    const ZydisBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<const Zydis::BaseInstructionFormatter*>(ctx);
}

inline Zydis::BaseInstructionFormatter* ZydisIntelInstructionFormatter_CppPtr(
    ZydisBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<Zydis::BaseInstructionFormatter*>(ctx);
}

inline const Zydis::BaseInstructionFormatter* ZydisIntelInstructionFormatter_CppPtr(
    const ZydisBaseInstructionFormatterContext *ctx)
{
    return reinterpret_cast<const Zydis::BaseInstructionFormatter*>(ctx);
}

inline ZydisBaseInstructionFormatterContext* ZydisIntelInstructionFormatter_CPtr(
    Zydis::BaseInstructionFormatter *ctx)
{
    return reinterpret_cast<ZydisBaseInstructionFormatterContext*>(ctx);
}

inline const ZydisBaseInstructionFormatterContext* ZydisIntelInstructionFormatter_CPtr(
    const Zydis::BaseInstructionFormatter *ctx)
{
    return reinterpret_cast<const ZydisBaseInstructionFormatterContext*>(ctx);
}

}

/* BaseSymbolResolver ======================================================================== */

void ZydisBaseSymbolResolver_Release(
    ZydisBaseSymbolResolverContext *ctx)
{
    delete ZydisBaseSymbolResolver_CppPtr(ctx);
}

const char* ZydisBaseSymbolResolver_ResolveSymbol(
    ZydisBaseSymbolResolverContext *ctx,
    const ZydisInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset)
{
    return ZydisBaseSymbolResolver_CppPtr(ctx)->resolveSymbol(
        *ZydisInstructionInfo_CppPtr(info),
        address,
        *offset);
}

/* ExactSymbolResolver ======================================================================= */

ZydisBaseSymbolResolverContext* ZydisExactSymbolResolver_Create(void)
{
    return ZydisExactSymbolResolver_CPtr(new Zydis::ExactSymbolResolver);
}

bool EZydisxactSymbolResolver_ContainsSymbol(
    ZydisBaseSymbolResolverContext *ctx,
    uint64_t address)
{
    return ZydisExactSymbolResolver_CppPtr(ctx)->containsSymbol(address);
}

void ZydisExactSymbolResolverContext_SetSymbol(
    ZydisBaseSymbolResolverContext *ctx,
    uint64_t address, 
    const char* name)
{
    ZydisExactSymbolResolver_CppPtr(ctx)->setSymbol(address, name);
}

void ZydisExactSymbolResolverContext_RemoveSymbol(
    ZydisBaseSymbolResolverContext *ctx,
    uint64_t address)
{
    ZydisExactSymbolResolver_CppPtr(ctx)->removeSymbol(address);
}

void ZydisExactSymbolResolverContext_Clear(
    ZydisBaseSymbolResolverContext *ctx)
{
    ZydisExactSymbolResolver_CppPtr(ctx)->clear();
}

/* BaseInstructionFormatter ================================================================== */

const char* ZydisBaseInstructionFormatter_FormatInstruction(
    ZydisBaseInstructionFormatterContext *ctx,
    const ZydisInstructionInfo *info)
{
    return ZydisBaseInstructionFormatter_CppPtr(ctx)->formatInstruction(
        *ZydisInstructionInfo_CppPtr(info));
}

ZydisBaseSymbolResolverContext* ZydisBaseInstructionFormatter_GetSymbolResolver(
    const ZydisBaseInstructionFormatterContext *ctx)
{
    return ZydisBaseSymbolResolver_CPtr(
        ZydisBaseInstructionFormatter_CppPtr(ctx)->getSymbolResolver());
}

void ZydisBaseInstructionFormatter_SetSymbolResolver(
    ZydisBaseInstructionFormatterContext *ctx,
    ZydisBaseSymbolResolverContext *resolver)
{
    ZydisBaseInstructionFormatter_CppPtr(ctx)->setSymbolResolver(
        ZydisBaseSymbolResolver_CppPtr(resolver));
}

void ZydisBaseInstructionFormatter_Release(
    ZydisBaseInstructionFormatterContext *ctx)
{
    delete ZydisBaseInstructionFormatter_CppPtr(ctx);
}

/* IntelInstructionFormatter ================================================================ */

ZydisBaseInstructionFormatterContext* ZydisIntelInstructionFormatter_Create(void)
{
    return ZydisIntelInstructionFormatter_CPtr(new Zydis::IntelInstructionFormatter);
}

ZydisBaseInstructionFormatterContext* ZydisIntelInstructionFormatter_CreateEx(
    ZydisBaseSymbolResolverContext *resolver)
{
    return ZydisIntelInstructionFormatter_CPtr(new Zydis::IntelInstructionFormatter(
        ZydisBaseSymbolResolver_CppPtr(resolver)));
}

/* ============================================================================================= */