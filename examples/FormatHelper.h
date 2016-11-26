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

#ifndef ZYDIS_FORMATHELPER_H
#define ZYDIS_FORMATHELPER_H

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <Zydis/Defines.h>
#include <Zydis/Status.h>

/* ============================================================================================== */
/* Format helper functions                                                                        */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 *  @brief  Defines the @c ZydisStringBufferAppendMode datatype.
 */
typedef uint8_t ZydisStringBufferAppendMode;

/**
 * @brief   Values that represent zydis string-buffer append-modes.
 */
enum ZydisStringBufferAppendModes
{
    /**
     *  @brief  Appends the string as it is.
     */
    ZYDIS_STRBUF_APPEND_MODE_DEFAULT,
    /**
     *  @brief  Converts the string to lowercase characters.
     */
    ZYDIS_STRBUF_APPEND_MODE_LOWERCASE,
    /**
     *  @brief  Converts the string to uppercase characters.
     */
    ZYDIS_STRBUF_APPEND_MODE_UPPERCASE
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Appends the @c text to the given @c buffer and increases the string-buffer pointer by
 *          the number of chars written.
 *
 * @param   buffer      A pointer to the string-buffer.
 * @param   bufferLen   The length of the string-buffer.
 * @param   mode        The append-mode.
 * @param   text        The text to append.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given @c text.
 */
ZYDIS_INLINE ZydisStatus ZydisStringBufferAppend(char** buffer, size_t bufferLen, 
    ZydisStringBufferAppendMode mode, const char* text)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(text);

    size_t strLen = strlen(text);
    if (strLen >= bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    strncpy(*buffer, text, strLen + 1);
    switch (mode)
    {
    case ZYDIS_STRBUF_APPEND_MODE_LOWERCASE:
        for (size_t i = 0; i < strLen; ++i)
        {
            (*buffer[i]) = (char)tolower((*buffer)[i]);    
        }
        break;
    case ZYDIS_STRBUF_APPEND_MODE_UPPERCASE:
        for (size_t i = 0; i < strLen; ++i)
        {
            (*buffer)[i] = (char)toupper((*buffer)[i]);    
        }
        break;
    default:
        break;
    }
    *buffer += strLen;
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Appends formatted text to the given @c buffer and increases the string-buffer pointer 
 *          by the number of chars written.
 *
 * @param   buffer      A pointer to the string-buffer.
 * @param   bufferLen   The length of the string-buffer.
 * @param   mode        The append-mode.
 * @param   format      The format string.
 *
 * @return  @c ZYDIS_STATUS_SUCCESS, if the function succeeded, or 
 *          @c ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE, if the size of the buffer was not 
 *          sufficient to append the given text.
 */
ZYDIS_INLINE ZydisStatus ZydisStringBufferAppendFormat(char** buffer, size_t bufferLen, 
    ZydisStringBufferAppendMode mode, const char* format, ...)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen != 0);
    ZYDIS_ASSERT(format);

    va_list arglist;
    va_start(arglist, format);
    int w = vsnprintf(*buffer, bufferLen, format, arglist);
    if ((w < 0) || ((size_t)w >= bufferLen))
    {
        va_end(arglist);
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    switch (mode)
    {
    case ZYDIS_STRBUF_APPEND_MODE_LOWERCASE:
        for (size_t i = 0; i < (size_t)w; ++i)
        {
            (*buffer)[i] = (char)tolower((*buffer)[i]);    
        }
        break;
    case ZYDIS_STRBUF_APPEND_MODE_UPPERCASE:
        for (size_t i = 0; i < (size_t)w; ++i)
        {
            (*buffer)[i] = (char)toupper((*buffer)[i]);    
        }
        break;
    default:
        break;
    }
    *buffer += (size_t)w;
    va_end(arglist);
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#endif /* ZYDIS_FORMATHELPER_H */
