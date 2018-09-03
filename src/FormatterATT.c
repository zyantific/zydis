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

#include <Zydis/Internal/FormatterATT.h>
#include <Zydis/Internal/String.h>

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTFormatInstruction(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTFormatOperandREG(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTFormatOperandMEM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTFormatOperandPTR(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTFormatOperandIMM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTPrintMnemonic(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintRegister(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context, ZydisRegister reg)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    ZYAN_UNUSED(reg);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintAddressAbsolute(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintAddressRelative(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintDISP(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintIMM(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Optional tokens                                                                                */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterATTPrintMemorySize(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintMemorySegment(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintPrefixes(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterATTPrintDecorator(const ZydisFormatter* formatter,
    ZyanString* string, ZydisFormatterContext* context, ZydisDecorator decorator)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(string);
    ZYAN_UNUSED(context);
    ZYAN_UNUSED(decorator);
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
