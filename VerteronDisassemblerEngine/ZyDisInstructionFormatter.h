/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 14. March 2015

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

#ifndef _VDE_ZyDisINSTRUCTIONFORMATTERC_H_
#define _VDE_ZyDisINSTRUCTIONFORMATTERC_H_

#include "ZyDisDisassemblerTypes.h"
#include "ZyDisDisassemblerUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ZyDisBaseSymbolResolver ======================================================================== */

typedef struct _ZyDisBaseSymbolResolverContext 
{ 
    ZyDisContextDescriptor d; 
} ZyDisBaseSymbolResolverContext;

/**
 * @brief   Releases a symbol resolver.
 * @param   ctx The context of the symbol resolver to free.
 * The context may no longer used after it was released.
 */
ZYDIS_EXPORT void ZyDisBaseSymbolResolver_Release(
    ZyDisBaseSymbolResolverContext *ctx);

/**
 * @brief   Resolves a symbol.
 * @param   ctx     The symbol resolver context.
 * @param   info    The instruction info.
 * @param   address The address.
 * @param   offset  Pointer to an unsigned 64 bit integer that receives an offset relative to 
 *                  the base address of the symbol.
 * @return  The name of the symbol if the symbol was found, else @c NULL.
 */
ZYDIS_EXPORT const char* ZyDisBaseSymbolResolver_ResolveSymbol(
    ZyDisBaseSymbolResolverContext *ctx,
    const ZyDisInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset);

/* ZyDisCustomSymbolResolver ====================================================================== */

typedef const char* (*ZyDisCustomSymbolResolver_ResolveSymbolCallback)(
    const ZyDisInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset,
    void *userData);

/**
 * @brief   Creates a custom symbol resolver.
 * @param   resolverCb  The resolver callback consulted when symbols need to be resolved.
 * @param   userData    A pointer to arbitrary data passed to the resolver callback.
 *                      May also be @c NULL.
 * @return  @c NULL if it fails, else a symbol resolver context.
 */
ZYDIS_EXPORT ZyDisBaseSymbolResolverContext* ZyDisCustomSymbolResolver_Create(
    ZyDisCustomSymbolResolver_ResolveSymbolCallback resolverCb,
    void *userData);

/* ZyDisBaseInstructionFormatter ================================================================== */

typedef struct _ZyDisBaseInstructionFormatterContext
{
    ZyDisContextDescriptor d;
} ZyDisBaseInstructionFormatterContext;

typedef void(*ZyDisBaseInstructionFormatter_InternalFormatInstructionCallback)(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info);

/**
 * @brief   Formats a decoded instruction.
 * @param   ctx     The instruction formatter context.
 * @param   info    The instruction info.
 * @return  Pointer to the formatted instruction string. This pointer remains valid until 
 *          this function is called again or the context is released.
 */
ZYDIS_EXPORT const char* ZyDisBaseInstructionFormatter_FormatInstruction(
    ZyDisBaseInstructionFormatterContext *ctx,
    const ZyDisInstructionInfo *info);

/**
 * @brief   Returns a pointer to the current symbol resolver.
 * @param   ctx     The instruction formatter context.
 * @return  Pointer to the current symbol resolver or @c NULL if no symbol resolver is used.
 */
ZYDIS_EXPORT ZyDisBaseSymbolResolverContext* ZyDisBaseInstructionFormatter_GetSymbolResolver(
    const ZyDisBaseInstructionFormatterContext *ctx);

/**
 * @brief   Sets a new symbol resolver.
 * @param   ctx             The instruction formatter context.
 * @param   symbolResolver  Pointer to a symbol resolver instance or @c NULL, if no smybol
 *                          resolver should be used.
 */
ZYDIS_EXPORT void ZyDisBaseInstructionFormatter_SetSymbolResolver(
    ZyDisBaseInstructionFormatterContext *ctx,
    ZyDisBaseSymbolResolverContext *resolver);

/**
 * @brief   Releases an instruction formatter.
 * @param   ctx The context of the instruction formatter to release.
 * The context may no longer used after it has been released.
 */
ZYDIS_EXPORT void ZyDisBaseInstructionFormatter_Release(
    ZyDisBaseInstructionFormatterContext *ctx);

/* ZyDisIntelInstructionFormatter ================================================================= */

/**
 * @brief   Creates an Intel-syntax instruction formatter.
 * @return  @c NULL if it fails, else an Intel instruction formatter context.
 * @see     ZyDisBaseInstructionFormatter_Release
 */
ZYDIS_EXPORT ZyDisBaseInstructionFormatterContext* ZyDisIntelInstructionFormatter_Create(void);

/**
 * @brief   Creates an Intel-syntax instruction formatter.
 * @param   resolver The symbol resolver consulted to resolve symbols on formatting.
 * @return  @c NULL if it fails, else an Intel instruction formatter context.
 * @see     ZyDisBaseInstructionFormatter_Release
 */
ZYDIS_EXPORT ZyDisBaseInstructionFormatterContext* ZyDisIntelInstructionFormatter_CreateEx(
    ZyDisBaseSymbolResolverContext *resolver);

/* ZyDisCustomInstructionFormatter ================================================================ */

/**
 * @brief   Creats a custom instruction formatter.
 * @param   formatInsnCb    The callback formatting the instruction.
 * @return  @c NULL if it fails, else a custom instruction formatter context.
 */
ZYDIS_EXPORT ZyDisBaseInstructionFormatterContext* ZyDisCustomInstructionFormatter_Create(
    ZyDisBaseInstructionFormatter_InternalFormatInstructionCallback formatInsnCb);

/* ============================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _VDE_ZyDisINSTRUCTIONFORMATTERC_H_ */