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

#ifndef _ZYDIS_SYMBOLRESOLVER_H_
#define _ZYDIS_SYMBOLRESOLVER_H_

#include "ZydisTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* BaseSymbolResolver ======================================================================== */

typedef struct _ZydisBaseSymbolResolverContext { int a; } ZydisBaseSymbolResolverContext;

/**
 * @brief   Releases a symbol resolver.
 * @param   ctx The context of the symbol resolver to free.
 * The context may no longer used after it was released.
 */
void ZydisBaseSymbolResolver_Release(ZydisBaseSymbolResolverContext *ctx);

/**
 * @brief   Resolves a symbol.
 * @param   ctx     The symbol resolver context.
 * @param   info    The instruction info.
 * @param   address The address.
 * @param   offset  Pointer to an unsigned 64 bit integer that receives an offset relative to 
 *                  the base address of the symbol.
 * @return  The name of the symbol if the symbol was found, else @c NULL.
 */
const char* ZydisBaseSymbolResolver_ResolveSymbol(ZydisBaseSymbolResolverContext *ctx,
    const ZydisInstructionInfo *info, uint64_t address, uint64_t *offset);

/* ExactSymbolResolver ======================================================================= */

/**
 * @brief   Creates an exact symbol resolver.
 * @return  @c NULL if it fails, else a symbol resolver context.
 * @see     BaseSymbolResolver_Release
 * An exact resolver is a simple symbol resolver that only matches exact addresses.
 */
// TODO: verify return value
ZydisBaseSymbolResolverContext* ZydisExactSymbolResolver_Create(void);

/**
 * @brief   Query if the given address is a known symbol.
 * @param   ctx     The exact symbol resolver context.
 * @param   address The address.
 * @return  @c true if the address is known, @c false if not.
 */
bool ZydisExactSymbolResolver_ContainsSymbol(ZydisBaseSymbolResolverContext *ctx, uint64_t address);

/**
 * @brief   Adds or changes a symbol.
 * @param   ctx     The exact symbol resolver context.
 * @param   address The address.
 * @param   name    The symbol name.
 */
void ZydisExactSymbolResolverContext_SetSymbol(ZydisBaseSymbolResolverContext *ctx, 
    uint64_t address, const char* name);

/**
 * @brief   Removes the symbol described by address.
 * @param   ctx     The exact symbol resolver context.
 * @param   address The address.
 * This will invalidate all char-pointers to the affected symbol name.
 */
void ZydisExactSymbolResolverContext_RemoveSymbol(ZydisBaseSymbolResolverContext *ctx,
    uint64_t address);

/**
 * @brief   Clears the symbol tree.
 * @param   ctx The exact symbol resolver context.
 */
void ExactSymbolResolverContext_Clear(ZydisBaseSymbolResolverContext *ctx);

/* CustomSymbolResolver ====================================================================== */

typedef const char* (*ZydisResolveSymbol_t)(const ZydisInstructionInfo *info, uint64_t address, 
    uint64_t *offset, void *userData);

/**
 * @brief   Creates a custom symbol resolver.
 * @param   resolverCb  The resolver callback consulted when symbols need to be resolved.
 * @param   userData    A pointer to arbitrary data passed to the resolver callback.
 *                      May also be @c NULL.
 * @return  @c NULL if it fails, else a symbol resolver context.
 */
ZydisBaseSymbolResolverContext* CustomSymbolResolver_Create(ZydisResolveSymbol_t resolverCb,
    void *userData);

#ifdef __cplusplus
}
#endif

#endif /* _ZYDIS_SYMBOLRESOLVER_H_ */