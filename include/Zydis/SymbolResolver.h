/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

  Original Author : Florian Bernd

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

#ifndef ZYDIS_SYMBOLRESOLVER_H
#define ZYDIS_SYMBOLRESOLVER_H

#include <stdint.h>
#include <Zydis/InstructionInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Custom resolver                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisResolverResolveSymbolFunc function pointer used in the 
 *          @c ZydisCustomSymbolResolver struct.
 *          
 * This function should return the name of the symbol found at the given @c address and an 
 * optional @c offset.
 */
typedef const char* (*ZydisResolverResolveSymbolFunc)(void* context, 
    const ZydisInstructionInfo* info, const ZydisOperandInfo* operand, uint64_t address, 
    int64_t* offset);

typedef struct ZydisCustomSymbolResolver_
{
    ZydisResolverResolveSymbolFunc resolveSymbol;     
} ZydisCustomSymbolResolver;

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_SYMBOLRESOLVER_H */
