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

#ifndef _ZYDIS_INSTRUCTIONFORMATTER_H_
#define _ZYDIS_INSTRUCTIONFORMATTER_H_

#include "ZydisTypes.h"
#include "ZydisSymbolResolver.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* BaseInstructionFormatter ================================================================== */

typedef struct _ZydisBaseInstructionFormatterContext {int a;} ZydisBaseInstructionFormatterContext;

/**
 * @brief   Formats a decoded instruction.
 * @param   ctx     The instruction formatter context.
 * @param   info    The instruction info.
 * @return  Pointer to the formatted instruction string. This pointer remains valid until 
 *          this function is called again or the context is released.
 */
const char* ZydisBaseInstructionFormatter_FormatInstruction(
    ZydisBaseInstructionFormatterContext *ctx, const ZydisInstructionInfo *info);

/**
 * @brief   Returns a pointer to the current symbol resolver.
 * @param   ctx     The instruction formatter context.
 * @return  Pointer to the current symbol resolver or @c NULL if no symbol resolver is used.
 */
ZydisBaseSymbolResolverContext* ZydisBaseInstructionFormatter_GetSymbolResolver(
    const ZydisBaseInstructionFormatterContext *ctx);

/**
 * @brief   Sets a new symbol resolver.
 * @param   ctx             The instruction formatter context.
 * @param   symbolResolver  Pointer to a symbol resolver instance or @c NULL, if no smybol
 *                          resolver should be used.
 */
void ZydisBaseInstructionFormatter_SetSymbolResolver(ZydisBaseInstructionFormatterContext *ctx,
    ZydisBaseSymbolResolverContext *resolver);

/**
 * @brief   Releases an instruction formatter.
 * @param   ctx The context of the instruction formatter to release.
 * The context may no longer used after it has been released.
 */
void ZydisBaseInstructionFormatter_Release(ZydisBaseInstructionFormatterContext *ctx);

/* IntelInstructionFormatter ================================================================ */

/**
 * @brief   Creates an Intel-syntax instruction formatter.
 * @return  @c NULL if it fails, else an Intel instruction formatter context.
 * @see     BaseInstructionFormatter_Release
 */
ZydisBaseInstructionFormatterContext* ZydisIntelInstructionFormatter_Create(void);

/**
 * @brief   Creates an Intel-syntax instruction formatter.
 * @param   resolver The symbol resolver consulted to resolve symbols on formatting.
 * @return  @c NULL if it fails, else an Intel instruction formatter context.
 * @see     BaseInstructionFormatter_Release
 */
ZydisBaseInstructionFormatterContext* ZydisIntelInstructionFormatter_CreateEx(
    ZydisBaseSymbolResolverContext *resolver);

/* ============================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _ZYDIS_INSTRUCTIONFORMATTER_H_ */