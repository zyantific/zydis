/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

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

#include <Zydis/Internal/SharedData.h>

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definitions                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#ifdef ZYDIS_MINIMAL_MODE
#   define ZYDIS_NOTMIN(x)
#else
#   define ZYDIS_NOTMIN(x) , x
#endif

#include <Generated/InstructionDefinitions.inc>

#undef ZYDIS_NOTMIN

/* ---------------------------------------------------------------------------------------------- */
/* Operand definitions                                                                            */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_OPERAND_DEFINITION(type, encoding, access) \
    { type, encoding, access }

#include <Generated/OperandDefinitions.inc>

#undef ZYDIS_OPERAND_DEFINITION

/* ---------------------------------------------------------------------------------------------- */
/* Accessed CPU flags                                                                             */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/AccessedFlags.inc>

/* ---------------------------------------------------------------------------------------------- */
/* Element info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

#ifndef ZYDIS_MINIMAL_MODE
const ZydisElementInfo ELEMENT_INFO[ZYDIS_IELEMENT_TYPE_MAX_VALUE + 1] =
{
    { ZYDIS_ELEMENT_TYPE_INVALID  ,   0, 0 },
    { ZYDIS_ELEMENT_TYPE_INVALID  ,   0, 0 },
    { ZYDIS_ELEMENT_TYPE_STRUCT   ,   0, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      ,   0, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     ,   0, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      ,   1, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      ,   8, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      ,  16, 0 }, // TODO: Should indicate 2 INT8 elements
    { ZYDIS_ELEMENT_TYPE_INT      ,  32, 0 }, // TODO: Should indicate 4 INT8 elements
    { ZYDIS_ELEMENT_TYPE_INT      ,  16, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      ,  32, 0 }, // TODO: Should indicate 2 INT16 elements
    { ZYDIS_ELEMENT_TYPE_INT      ,  32, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      ,  64, 0 },
    { ZYDIS_ELEMENT_TYPE_INT      , 128, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     ,   8, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     ,  32, 0 }, // TODO: Should indicate 4 UINT8 elements
    { ZYDIS_ELEMENT_TYPE_UINT     ,  16, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     ,  32, 0 }, // TODO: Should indicate 2 UINT16 elements
    { ZYDIS_ELEMENT_TYPE_UINT     ,  32, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     ,  64, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     , 128, 0 },
    { ZYDIS_ELEMENT_TYPE_UINT     , 256, 0 },
    { ZYDIS_ELEMENT_TYPE_FLOAT16  ,  16, 0 },
    { ZYDIS_ELEMENT_TYPE_FLOAT16  ,  32, 0 }, // TODO: Should indicate 2 FLOAT16 elements
    { ZYDIS_ELEMENT_TYPE_FLOAT32  ,  32, 0 },
    { ZYDIS_ELEMENT_TYPE_FLOAT64  ,  64, 0 },
    { ZYDIS_ELEMENT_TYPE_FLOAT80  ,  80, 0 },
    { ZYDIS_ELEMENT_TYPE_BFLOAT16 ,  16, 0 },
    { ZYDIS_ELEMENT_TYPE_BFLOAT16 ,  32, 0 }, // TODO: Should indicate 2 BFLOAT16 elements
    { ZYDIS_ELEMENT_TYPE_BFLOAT8  ,   8, 0 },
    { ZYDIS_ELEMENT_TYPE_HFLOAT8  ,   8, 0 },
    { ZYDIS_ELEMENT_TYPE_BFLOAT8  ,  32, 0 }, // TODO: Should indicate 4 BFLOAT8 elements
    { ZYDIS_ELEMENT_TYPE_HFLOAT8  ,  32, 0 }, // TODO: Should indicate 4 HFLOAT8 elements
    { ZYDIS_ELEMENT_TYPE_BFLOAT4  ,   4, 0 },
    { ZYDIS_ELEMENT_TYPE_BFLOAT6  ,   6, 8 },
    { ZYDIS_ELEMENT_TYPE_HFLOAT6  ,   6, 8 },
    { ZYDIS_ELEMENT_TYPE_LONGBCD  ,  80, 0 },
    { ZYDIS_ELEMENT_TYPE_CC       ,   3, 0 },
    { ZYDIS_ELEMENT_TYPE_CC       ,   5, 0 }
};
#endif

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
