/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd, Joel Hoener

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

/**
 * @file
 * @brief   Implements the `INTEL` style instruction-formatter.
 */

#ifndef ZYDIS_FORMATTER_INTEL_H
#define ZYDIS_FORMATTER_INTEL_H

#include <Zydis/Formatter.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatInstruction(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelFormatInstructionMASM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelFormatOperandREG(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelFormatOperandMEM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelFormatOperandPTR(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelFormatOperandIMM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelPrintMnemonic(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintRegister(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context, ZydisRegister reg);

ZyanStatus ZydisFormatterIntelPrintAddressAbsolute(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintAddressRelative(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintAddressMASM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintDISP(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintIMM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */
/* Optional tokens                                                                                */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterIntelPrintMemorySize(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintMemorySegment(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintPrefixes(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterIntelPrintDecorator(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context, ZydisDecorator decorator);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif // ZYDIS_FORMATTER_INTEL_H
