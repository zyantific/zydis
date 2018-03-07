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

#ifndef ZYDIS_STRING_H
#define ZYDIS_STRING_H

#include <Zydis/CommonTypes.h>
#include <Zydis/Status.h>
#include <Zydis/Internal/LibC.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* String                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisString` struct.
 */
typedef struct ZydisString_
{
    /**
     * @brief   The buffer that contains the actual string (0-termination is optional!).
     */
    char* buffer;
    /**
     * @brief   The length of the string (without 0-termination).
     */
    ZydisUSize length;
    /**
     * @brief   The total buffer capacity.
     */
    ZydisUSize capacity;
} ZydisString;

/* ---------------------------------------------------------------------------------------------- */
/* Static string                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

#pragma pack(push, 1)

/**
 * @brief   Defines the `ZydisStaticString` struct.
 *
 * This more compact struct is mainly used for internal string-tables to save up some bytes.
 */
typedef struct ZydisStaticString_
{
    /**
     * @brief   The buffer that contains the actual string (0-termination is optional!).
    */
    const char* buffer;
    /**
     * @brief   The length of the string (without 0-termination).
    */
    ZydisU8 length;
} ZydisStaticString;

#pragma pack(pop)

/* ---------------------------------------------------------------------------------------------- */
/* Letter Case                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisLetterCase` datatype.
 */
typedef ZydisU8 ZydisLetterCase;

/**
 * @brief   Values that represent letter cases.
 */
enum ZydisLetterCases
{
    /**
     * @brief   Uses the given text "as is".
     */
    ZYDIS_LETTER_CASE_DEFAULT,
    /**
     * @brief   Converts the given text to lowercase letters.
     */
    ZYDIS_LETTER_CASE_LOWER,
    /**
     * @brief   Converts the given text to uppercase letters.
     */
    ZYDIS_LETTER_CASE_UPPER,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_LETTER_CASE_MAX_VALUE = ZYDIS_LETTER_CASE_UPPER
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Helper Macros                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Creates a `ZydisString` struct from a static C-string.
 *
 * @param   string  The C-string constant.
 */
#define ZYDIS_MAKE_STRING(string) \
    { (char*)string, sizeof(string) - 1, sizeof(string) - 1 }

/**
 * @brief   Creates a `ZydisStaticString` from a static C-string.
 *
 * @param   string  The C-string constant.
 */
#define ZYDIS_MAKE_STATIC_STRING(string) \
    { string, sizeof(string) - 1 }

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Basic Operations                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Initializes a `ZydisString` struct with a C-string.
 *
 * @param   string  The string to initialize.
 * @param   text    The C-string constant.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringInit(ZydisString* string, char* text);

/**
 * @brief   Finalizes a `ZydisString` struct by adding a terminating zero byte.
 *
 * @param   string  The string to finalize.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringFinalize(ZydisString* string);

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Appends a `ZydisString` to another `ZydisString`.
 *
 * @param   string      The string to append to.
 * @param   text        The string to append.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c text.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppend(ZydisString* string, const ZydisString* text);

/**
 * @brief   Appends a `ZydisString` to another `ZydisString`, converting it to the specified
 *          letter-case.
 *
 * @param   string      The string to append to.
 * @param   text        The string to append.
 * @param   letterCase  The letter case to use.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c text.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendEx(ZydisString* string, const ZydisString* text,
    ZydisLetterCase letterCase);

/**
 * @brief   Appends the given C-string to a `ZydisString`.
 *
 * @param   string      The string to append to.
 * @param   text        The C-string to append.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c text.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendC(ZydisString* string, const char* text);

/**
 * @brief   Appends the given C-string to a `ZydisString`, converting it to the specified
 *          letter-case.
 *
 * @param   string      The string to append to.
 * @param   text        The C-string to append.
 * @param   letterCase  The letter case to use.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c text.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendExC(ZydisString* string, const char* text,
    ZydisLetterCase letterCase);

/**
 * @brief   Appends the given 'ZydisStaticString' to a `ZydisString`.
 *
 * @param   string      The string to append to.
 * @param   text        The static-string to append.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c text.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendStatic(ZydisString* string,
    const ZydisStaticString* text, ZydisLetterCase letterCase);

/**
 * @brief   Appends the given 'ZydisStaticString' to a `ZydisString`, converting it to the
 *          specified letter-case.
 *
 * @param   string      The string to append to.
 * @param   text        The static-string to append.
 * @param   letterCase  The letter case to use.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c text.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendExStatic(ZydisString* string,
    const ZydisStaticString* text, ZydisLetterCase letterCase);

/* ---------------------------------------------------------------------------------------------- */
/* Formatting                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Formats the given unsigned ordinal @c value to its decimal text-representation and
 *          appends it to the @c string.
 *
 * @param   string          A pointer to the string.
 * @param   value           The value.
 * @param   paddingLength   Padds the converted value with leading zeros, if the number of chars is
 *                          less than the @c paddingLength.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c value.
 *
 * The string-buffer pointer is increased by the number of chars written, if the call was
 * successfull.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendDecU(ZydisString* string, ZydisU64 value,
    ZydisU8 paddingLength);

/**
 * @brief   Formats the given signed ordinal @c value to its decimal text-representation and
 *          appends it to the @c string.
 *
 * @param   string          A pointer to the string.
 * @param   value           The value.
 * @param   paddingLength   Padds the converted value with leading zeros, if the number of chars is
 *                          less than the @c paddingLength (the sign char is ignored).
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c value.
 *
 * The string-buffer pointer is increased by the number of chars written, if the call was
 * successfull.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendDecS(ZydisString* string, ZydisI64 value,
    ZydisU8 paddingLength);

/**
 * @brief   Formats the given unsigned ordinal @c value to its hexadecimal text-representation and
 *          appends it to the @c string.
 *
 * @param   string          A pointer to the string.
 * @param   value           The value.
 * @param   paddingLength   Padds the converted value with leading zeros, if the number of chars is
 *                          less than the @c paddingLength.
 * @param   uppercase       Set @c TRUE to print the hexadecimal value in uppercase letters instead
 *                          of lowercase ones.
 * @param   prefix          The string to use as prefix or `NULL`, if not needed.
 * @param   suffix          The string to use as suffix or `NULL`, if not needed.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c value.
 *
 * The string-buffer pointer is increased by the number of chars written, if the call was
 * successfull.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendHexU(ZydisString* string, ZydisU64 value,
    ZydisU8 paddingLength, ZydisBool uppercase, const ZydisString* prefix,
    const ZydisString* suffix);

/**
 * @brief   Formats the given signed ordinal @c value to its hexadecimal text-representation and
 *          appends it to the @c string.
 *
 * @param   string          A pointer to the string.
 * @param   value           The value.
 * @param   paddingLength   Padds the converted value with leading zeros, if the number of chars is
 *                          less than the @c paddingLength (the sign char is ignored).
 * @param   uppercase       Set @c TRUE to print the hexadecimal value in uppercase letters instead
 *                          of lowercase ones.
 * @param   prefix          The string to use as prefix or `NULL`, if not needed.
 * @param   suffix          The string to use as suffix or `NULL`, if not needed.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not
 *          sufficient to append the given @c value.
 *
 * The string-buffer pointer is increased by the number of chars written, if the call was
 * successfull.
 */
ZYDIS_EXPORT ZydisStatus ZydisStringAppendHexS(ZydisString* string, ZydisI64 value,
    ZydisU8 paddingLength, ZydisBool uppercase, const ZydisString* prefix,
    const ZydisString* suffix);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif // ZYDIS_STRING_H
