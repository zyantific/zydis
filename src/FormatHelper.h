/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd, Joel Höner

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

#ifndef ZYDIS_FORMATHELPER_H
#define ZYDIS_FORMATHELPER_H

#include <Zydis/Defines.h>
#include <Zydis/Status.h>
#include <Zydis/String.h>
#include <LibC.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

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
     * @brief   Prints the given text "as it is".
     */
    ZYDIS_LETTER_CASE_DEFAULT,
    /**
     * @brief   Prints the given text in lowercase letters.
     */
    ZYDIS_LETTER_CASE_LOWER,
    /**
     * @brief   Prints the given text in uppercase letters.
     */
    ZYDIS_LETTER_CASE_UPPER
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* String                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Appends the @c ZydisString to another @c ZydisString.
 *
 * @param   buffer      The string to append to.
 * @param   text        The string to append.
 * @param   letterCase  The desired letter-case.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c text.
 */
ZYDIS_NO_EXPORT ZydisStatus ZydisStringAppend(
    ZydisString* s, const ZydisString* text, ZydisLetterCase letterCase);

/**
 * @brief   Appends the given C string to the @c ZydisString.
 *
 * @param   s           The string to append to.
 * @param   text        The text to append.
 * @param   letterCase  The desired letter-case.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c text.
 */
ZYDIS_INLINE ZydisStatus ZydisStringAppendC(
    ZydisString* s, const char* text, ZydisLetterCase letterCase)
{
    ZYDIS_ASSERT(text);

    ZydisUSize len = ZydisStrLen(text);
    ZydisString zyStr = {
        .s          = (char*)text,
        .length     = len,
        .capacity   = len
    };
    
    return ZydisStringAppend(s, &zyStr, letterCase);
}

/* ---------------------------------------------------------------------------------------------- */
/* Decimal values                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Formats the given unsigned ordinal @c value to its decimal text-representation and  
 *          appends it to @c s.
 *
 * @param   s               A pointer to the string.
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
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintDecU(ZydisString* s, ZydisU64 value, ZydisU8 paddingLength);

/**
 * @brief   Formats the given signed ordinal @c value to its decimal text-representation and   
 *          appends it to @c s.
 *
 * @param   s               A pointer to the string.
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
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintDecS(ZydisString* s, ZydisI64 value, 
    ZydisU8 paddingLength);

/* ---------------------------------------------------------------------------------------------- */
/* Hexadecimal values                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Formats the given unsigned ordinal @c value to its hexadecimal text-representation and 
 *          appends it to the @c buffer.
 *
 * @param   s               A pointer to the string.
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
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintHexU(ZydisString* s, ZydisU64 value,
    ZydisU8 paddingLength, ZydisBool uppercase, const char* prefix, const char* suffix);

/**
 * @brief   Formats the given signed ordinal @c value to its hexadecimal text-representation and 
 *          appends it to the @c buffer.
 *
 * @param   s               A pointer to the string.
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
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintHexS(ZydisString* s, ZydisI64 value, 
    ZydisU8 paddingLength, ZydisBool uppercase, const char* prefix, const char* suffix);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_FORMATHELPER_H */
