/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

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

#ifndef _VDE_VXINSTRUCTIONFORMATTERC_H_
#define _VDE_VXINSTRUCTIONFORMATTERC_H_

#include "VXDisassemblerTypesC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* VXBaseSymbolResolver ======================================================================== */

    typedef struct _VXBaseSymbolResolverContext { int a; } VXBaseSymbolResolverContext;

VXBaseSymbolResolverContext* VXBaseSymbolResolver_Create(void);

void VXBaseSymbolResolver_Release(
    VXBaseSymbolResolverContext *ctx);

const char* VXBaseSymbolResolver_ResolveSymbol(
    VXBaseSymbolResolverContext *ctx,
    const VXInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset);

/* VXExactSymbolResolver ======================================================================= */

VXBaseSymbolResolverContext* VXExactSymbolResolver_Create(void);

bool VXExactSymbolResolver_ContainsSymbol(
    VXBaseSymbolResolverContext *ctx,
    uint64_t address);

void VXExactSymbolResolverContext_SetSymbol(
    VXBaseSymbolResolverContext *ctx,
    uint64_t address, 
    const char* name);

void VXExactSymbolResolverContext_RemoveSymbol(
    VXBaseSymbolResolverContext *ctx,
    uint64_t address);

void VXExactSymbolResolverContext_Clear(
    VXBaseSymbolResolverContext *ctx);

/* VXCustomSymbolResolver ====================================================================== */

/* TODO: actually implement support for custom resolvers in C binding */

typedef const char* (*VXResolveSymbol_t)(
    const VXInstructionInfo *info, 
    uint64_t address, uint64_t *offset);

/* VXBaseInstructionFormatter ================================================================== */

    typedef struct _VXBaseInstructionFormatterContext {int a;} VXBaseInstructionFormatterContext;

VXBaseSymbolResolverContext* VXBaseInstructionFormatter_GetSymbolResolver(
    const VXBaseInstructionFormatterContext *ctx);

void VXBaseInstructionFormatter_SetSymbolResolver(
    VXBaseInstructionFormatterContext *ctx,
    VXBaseSymbolResolverContext *resolver);

void VXBaseInstructionFormatter_Release(VXBaseInstructionFormatterContext *ctx);

/* VXIntelInstructionFormatter ================================================================ */

    typedef struct _VXIntelInstructionFormatterContext {int a;} VXIntelInstructionFormatterContext;

VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_Create(void);

VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_CreateEx(
    VXBaseSymbolResolverContext *resolver);

/* ============================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _VDE_VXINSTRUCTIONFORMATTERC_H_ */