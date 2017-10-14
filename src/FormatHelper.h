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
typedef uint8_t ZydisLetterCase;

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
 * @brief   Appends the given @c text to the @c buffer.
 *
 * @param   buffer      A pointer to the string-buffer.
 * @param   bufferLen   The length of the string-buffer.
 * @param   text        The text to append.
 * @param   letterCase  The desired letter-case.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c text.
 *          
 * The string-buffer pointer is increased by the number of chars written, if the call was 
 * successfull.
 */
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintStr(char** buffer, size_t bufferLen, const char* text,
    ZydisLetterCase letterCase);

/**
 * @brief   Rewrites the letter case of a given string.
 *
 * @param   buffer      The string to rewrite.
 * @param   bufferLen   The number of bytes in the buffer to case-rewrite. 
 * @param   letterCase  The desired letter case.
 */     
ZYDIS_NO_EXPORT void ZydisChangeCase(char* buffer, size_t bufferLen, ZydisLetterCase letterCase);

/* ---------------------------------------------------------------------------------------------- */
/* Decimal values                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Formats the given unsigned ordinal @c value to its decimal text-representation and  
 *          appends it to the @c buffer.
 *
 * @param   buffer          A pointer to the string-buffer.
 * @param   bufferLen       The length of the string-buffer.
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
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintDecU(char** buffer, size_t bufferLen, uint64_t value,
    uint8_t paddingLength);

/**
 * @brief   Formats the given signed ordinal @c value to its decimal text-representation and   
 *          appends it to the @c buffer.
 *
 * @param   buffer          A pointer to the string-buffer.
 * @param   bufferLen       The length of the string-buffer.
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
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintDecS(char** buffer, size_t bufferLen, int64_t value, 
    uint8_t paddingLength);

/* ---------------------------------------------------------------------------------------------- */
/* Hexadecimal values                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Formats the given unsigned ordinal @c value to its hexadecimal text-representation and 
 *          appends it to the @c buffer.
 *
 * @param   buffer          A pointer to the string-buffer.
 * @param   bufferLen       The length of the string-buffer.
 * @param   value           The value.
 * @param   paddingLength   Padds the converted value with leading zeros, if the number of chars is
 *                          less than the @c paddingLength.
 * @param   uppercase       Set @c TRUE to print the hexadecimal value in uppercase letters instead 
 *                          of lowercase ones.
 * @param   prefix          Set @c TRUE to add the "0x" prefix to the hexadecimal value.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c value.
 *          
 * The string-buffer pointer is increased by the number of chars written, if the call was 
 * successfull.
 */
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintHexU(char** buffer, size_t bufferLen, uint64_t value,
    uint8_t paddingLength, ZydisBool uppercase, ZydisBool prefix);

/**
 * @brief   Formats the given signed ordinal @c value to its hexadecimal text-representation and 
 *          appends it to the @c buffer.
 *
 * @param   buffer          A pointer to the string-buffer.
 * @param   bufferLen       The length of the string-buffer.
 * @param   value           The value.
 * @param   paddingLength   Padds the converted value with leading zeros, if the number of chars is
 *                          less than the @c paddingLength (the sign char is ignored).
 * @param   uppercase       Set @c TRUE to print the hexadecimal value in uppercase letters instead 
 *                          of lowercase ones.
 * @param   prefix          Set @c TRUE to add the "0x" prefix to the hexadecimal value.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c value.
 *          
 * The string-buffer pointer is increased by the number of chars written, if the call was 
 * successfull.
 */
ZYDIS_NO_EXPORT ZydisStatus ZydisPrintHexS(char** buffer, size_t bufferLen, int64_t value, 
    uint8_t paddingLength, ZydisBool uppercase, ZydisBool prefix);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_FORMATHELPER_H */
