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
 * @brief   Provides formatter functions that are shared between the different formatters.
 */

#ifndef ZYDIS_FORMATTER_SHARED_H
#define ZYDIS_FORMATTER_SHARED_H

#include <Zydis/Formatter.h>
#include <Zydis/Internal/String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Buffer                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Invokes the `ZydisFormatterBufferAppend` routine, if tokenization is enabled for the
 *          current pass.
 *
 * @param   buffer  A pointer to the `ZydisFormatterBuffer` struct.
 * @param   type    The token type.
 *
 * Using this macro instead of direct calls to `ZydisFormatterBufferAppend` greatly improves the
 * performance for non-tokenizing passes.
 */
#define ZYDIS_BUFFER_APPEND_TOKEN(buffer, type) \
    if ((buffer)->tokenized) \
    { \
        ZYAN_CHECK(ZydisFormatterBufferAppend(buffer, type)); \
    }

/**
 * @brief   Returns a snapshot of the buffer-state.
 *
 * @param   buffer  A pointer to the `ZydisFormatterBuffer` struct.
 * @param   state   Receives a snapshot of the buffer-state.
 *
 * Using this macro instead of direct calls to `ZydisFormatterBufferRemember` improves the
 * performance for non-tokenizing passes.
 */
#define ZYDIS_BUFFER_REMEMBER(buffer, state) \
    if ((buffer)->tokenized) \
    { \
        (state) = (ZyanUPointer)(buffer)->last; \
    } else \
    { \
        (state) = (ZyanUPointer)(buffer)->string.vector.size; \
    }

/* ---------------------------------------------------------------------------------------------- */
/* String                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Appends an unsigned numeric value to the given string.
 *
 * @param   formatter       A pointer to the `ZydisFormatter` instance.
 * @param   base            The numeric base.
 * @param   str             The destination string.
 * @param   value           The value.
 * @param   padding_length  The padding length.
 */
#define ZYDIS_STRING_APPEND_NUM_U(formatter, base, str, value, padding_length) \
    switch (base) \
    { \
    case ZYDIS_NUMERIC_BASE_DEC: \
        ZYAN_CHECK(ZydisStringAppendDecU(str, value, padding_length, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    case ZYDIS_NUMERIC_BASE_HEX: \
        ZYAN_CHECK(ZydisStringAppendHexU(str, value, padding_length, \
            (formatter)->hex_uppercase, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    default: \
        return ZYAN_STATUS_INVALID_ARGUMENT; \
    }

/**
 * @brief   Appends a signed numeric value to the given string.
 *
 * @param   formatter       A pointer to the `ZydisFormatter` instance.
 * @param   base            The numeric base.
 * @param   str             The destination string.
 * @param   value           The value.
 * @param   padding_length  The padding length.
 * @param   force_sign      Forces printing of the '+' sign for positive numbers.
 */
#define ZYDIS_STRING_APPEND_NUM_S(formatter, base, str, value, padding_length, force_sign) \
    switch (base) \
    { \
    case ZYDIS_NUMERIC_BASE_DEC: \
        ZYAN_CHECK(ZydisStringAppendDecS(str, value, padding_length, force_sign, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    case ZYDIS_NUMERIC_BASE_HEX: \
        ZYAN_CHECK(ZydisStringAppendHexS(str, value, padding_length,  \
            (formatter)->hex_uppercase, force_sign, \
            (formatter)->number_format[base][0].string, \
            (formatter)->number_format[base][1].string)); \
        break; \
    default: \
        return ZYAN_STATUS_INVALID_ARGUMENT; \
    }

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* General                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the size to be used as explicit size suffix (`AT&T`) or explicit typecast
 *          (`INTEL`), if required.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   context     A pointer to the `ZydisFormatterContext` struct.
 * @param   memop_id    The operand-id of the instructions first memory operand.
 *
 * @return  Returns the explicit size, if required, or `0`, if not needed.
 *
 * This function always returns a size different to `0`, if the `ZYDIS_FORMATTER_PROP_FORCE_SIZE`
 * is set to `ZYAN_TRUE`.
 */
ZyanU32 ZydisFormatterHelperGetExplicitSize(const ZydisFormatter* formatter,
    ZydisFormatterContext* context, ZyanU8 memop_id);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Formatter functions                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Operands                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterSharedFormatOperandREG(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterSharedFormatOperandPTR(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterSharedFormatOperandIMM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */
/* Elemental tokens                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterSharedPrintAddressABS(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterSharedPrintAddressREL(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterSharedPrintIMM(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

/* ---------------------------------------------------------------------------------------------- */
/* Optional tokens                                                                                */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterSharedPrintSegment(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterSharedPrintPrefixes(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context);

ZyanStatus ZydisFormatterSharedPrintDecorator(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context, ZydisDecorator decorator);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif // ZYDIS_FORMATTER_SHARED_H
