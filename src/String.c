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

#include <Zydis/String.h>

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Defines                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_MAXCHARS_DEC_32 10
#define ZYDIS_MAXCHARS_DEC_64 20
#define ZYDIS_MAXCHARS_HEX_32  8
#define ZYDIS_MAXCHARS_HEX_64 16

/* ---------------------------------------------------------------------------------------------- */
/* Lookup Tables                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

static const char* decimalLookup =
    "00010203040506070809"
    "10111213141516171819"
    "20212223242526272829"
    "30313233343536373839"
    "40414243444546474849"
    "50515253545556575859"
    "60616263646566676869"
    "70717273747576777879"
    "80818283848586878889"
    "90919293949596979899";

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Internal Functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Formatting                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

#if defined(ZYAN_X86) || defined(ZYAN_ARM) || defined(ZYAN_EMSCRIPTEN)
ZyanStatus ZydisStringAppendDecU32(ZydisString* string, ZyanU32 value, ZyanU8 padding_length)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(string->buffer);

    char temp[ZYDIS_MAXCHARS_DEC_32 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_32];
    while (value >= 100)
    {
        ZyanU32 const old = value;
        p -= 2;
        value /= 100;
        ZYAN_MEMCPY(p, &decimalLookup[(old - (value * 100)) * 2], sizeof(ZyanU16));
    }
    p -= 2;
    ZYAN_MEMCPY(p, &decimalLookup[value * 2], sizeof(ZyanU16));

    const ZyanUSize n = &temp[ZYDIS_MAXCHARS_DEC_32] - p;
    if ((string->capacity - string->length < (ZyanUSize)(n + 1)) ||
        (string->capacity - string->length < (ZyanUSize)(padding_length + 1)))
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZyanUSize offset = 0;
    if (n <= padding_length)
    {
        offset = padding_length - n + 1;
        ZYAN_MEMSET(string->buffer + string->length, '0', offset);
    }

    ZYAN_MEMCPY(string->buffer + string->length + offset, &p[value < 10], n + 1);
    string->length += n + offset - (ZyanU8)(value < 10);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisStringAppendHexU32(ZydisString* string, ZyanU32 value, ZyanU8 padding_length,
    ZyanBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(string->buffer);

    if (prefix)
    {
        ZYAN_CHECK(ZydisStringAppend(string, prefix));
    }

    char* buffer = string->buffer + string->length;
    const ZyanUSize remaining = string->capacity - string->length;

    if (remaining < (ZyanUSize)padding_length)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZyanU8 n = (padding_length ? padding_length : 1);

        if (remaining < (ZyanUSize)n)
        {
            return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZYAN_MEMSET(buffer, '0', n);
        string->length += n;

        return ZYAN_STATUS_SUCCESS;
    }

    ZyanU8 n = 0;
    for (ZyanI8 i = ZYDIS_MAXCHARS_HEX_32 - 1; i >= 0; --i)
    {
        const ZyanU8 v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (remaining <= (ZyanU8)(i + 1)) // TODO: +1?
            {
                return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }
            if (padding_length > i)
            {
                n = padding_length - i - 1;
                ZYAN_MEMSET(buffer, '0', n);
            }
        }
        if (uppercase)
        {
            buffer[n++] = "0123456789ABCDEF"[v];
        } else
        {
            buffer[n++] = "0123456789abcdef"[v];
        }
    }
    string->length += n;

    if (suffix)
    {
        ZYAN_CHECK(ZydisStringAppend(string, suffix));
    }

    return ZYAN_STATUS_SUCCESS;
}
#endif

ZyanStatus ZydisStringAppendDecU64(ZydisString* string, ZyanU64 value, ZyanU8 padding_length)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(string->buffer);

    char temp[ZYDIS_MAXCHARS_DEC_64 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_64];
    while (value >= 100)
    {
        ZyanU64 const old = value;
        p -= 2;
        value /= 100;
        ZYAN_MEMCPY(p, &decimalLookup[(old - (value * 100)) * 2], 2);
    }
    p -= 2;
    ZYAN_MEMCPY(p, &decimalLookup[value * 2], sizeof(ZyanU16));

    const ZyanUSize n = &temp[ZYDIS_MAXCHARS_DEC_64] - p;
    if ((string->capacity - string->length < (ZyanUSize)(n + 1)) ||
        (string->capacity - string->length < (ZyanUSize)(padding_length + 1)))
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZyanUSize offset = 0;
    if (n <= padding_length)
    {
        offset = padding_length - n + 1;
        ZYAN_MEMSET(string->buffer + string->length, '0', offset);
    }

    ZYAN_MEMCPY(string->buffer + string->length + offset, &p[value < 10], n + 1);
    string->length += n + offset - (ZyanU8)(value < 10);

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisStringAppendHexU64(ZydisString* string, ZyanU64 value, ZyanU8 padding_length,
    ZyanBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(string->buffer);

    if (prefix)
    {
        ZYAN_CHECK(ZydisStringAppend(string, prefix));
    }

    char* buffer = string->buffer + string->length;
    const ZyanUSize remaining = string->capacity - string->length;

    if (remaining < (ZyanUSize)padding_length)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZyanU8 n = (padding_length ? padding_length : 1);

        if (remaining < (ZyanUSize)n)
        {
            return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZYAN_MEMSET(buffer, '0', n);
        string->length += n;

        return ZYAN_STATUS_SUCCESS;
    }

    ZyanU8 n = 0;
    const ZyanU8 c =
        ((value & 0xFFFFFFFF00000000) ? ZYDIS_MAXCHARS_HEX_64 : ZYDIS_MAXCHARS_HEX_32);
    for (ZyanI8 i = c - 1; i >= 0; --i)
    {
        const ZyanU8 v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (remaining <= (ZyanU8)(i + 1)) // TODO: +1?
            {
                return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }
            if (padding_length > i)
            {
                n = padding_length - i - 1;
                ZYAN_MEMSET(buffer, '0', n);
            }
        }
        if (uppercase)
        {
            buffer[n++] = "0123456789ABCDEF"[v];
        } else
        {
            buffer[n++] = "0123456789abcdef"[v];
        }
    }
    string->length += n;

    if (suffix)
    {
        ZYAN_CHECK(ZydisStringAppend(string, suffix));
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Public Functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Basic Operations                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisStringInit(ZydisString* string, char* text)
{
    if (!string || !text)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZyanUSize length = ZYAN_STRLEN(text);
    string->buffer   = text;
    string->length   = length;
    string->capacity = length;

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisStringFinalize(ZydisString* string)
{
    if (!string)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
    if (string->length >= string->capacity)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    string->buffer[string->length] = 0;
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisStringAppend(ZydisString* string, const ZydisString* text)
{
    return ZydisStringAppendEx(string, text, ZYDIS_LETTER_CASE_DEFAULT);
}

ZyanStatus ZydisStringAppendEx(ZydisString* string, const ZydisString* text,
    ZydisLetterCase letter_case)
{
    if (!string || !text)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (string->length + text->length >= string->capacity)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZYAN_MEMCPY(string->buffer + string->length, text->buffer, text->length);
    switch (letter_case)
    {
    case ZYDIS_LETTER_CASE_DEFAULT:
        break;
    case ZYDIS_LETTER_CASE_LOWER:
    {
        const signed char rebase = 'a' - 'A';
        char* c = string->buffer + string->length;
        for (ZyanUSize i = 0; i < text->length; ++i)
        {
            if ((*c >= 'A') && (*c <= 'Z'))
            {
                *c += rebase;
            }
            ++c;
        }
        break;
    }
    case ZYDIS_LETTER_CASE_UPPER:
    {
        const signed char rebase = 'A' - 'a';
        char* c = string->buffer + string->length;
        for (ZyanUSize i = 0; i < text->length; ++i)
        {
            if ((*c >= 'a') && (*c <= 'z'))
            {
                *c += rebase;
            }
            ++c;
        }
        break;
    }
    default:
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
    string->length += text->length;

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisStringAppendC(ZydisString* string, const char* text)
{
    ZydisString other;
    ZYAN_CHECK(ZydisStringInit(&other, (char*)text));

    return ZydisStringAppendEx(string, &other, ZYDIS_LETTER_CASE_DEFAULT);
}

ZyanStatus ZydisStringAppendExC(ZydisString* string, const char* text, ZydisLetterCase letter_case)
{
    ZydisString other;
    ZYAN_CHECK(ZydisStringInit(&other, (char*)text));

    return ZydisStringAppendEx(string, &other, letter_case);
}

ZyanStatus ZydisStringAppendStatic(ZydisString* string, const ZydisStaticString* text)
{
    if (!text || !text->buffer)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZydisString other;
    other.buffer = (char*)text->buffer;
    other.length = text->length;

    return ZydisStringAppendEx(string, &other, ZYDIS_LETTER_CASE_DEFAULT);
}

ZyanStatus ZydisStringAppendExStatic(ZydisString* string, const ZydisStaticString* text,
    ZydisLetterCase letter_case)
{
    if (!text || !text->buffer)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    ZydisString other;
    other.buffer = (char*)text->buffer;
    other.length = text->length;

    return ZydisStringAppendEx(string, &other, letter_case);
}

/* ---------------------------------------------------------------------------------------------- */
/* Formatting                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisStringAppendDecU(ZydisString* string, ZyanU64 value, ZyanU8 padding_length)
{
#if defined(ZYAN_X64) || defined(ZYAN_AARCH64)
    return ZydisStringAppendDecU64(string, value, padding_length);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisStringAppendDecU64(string, value, padding_length);
   } else
   {
       return ZydisStringAppendDecU32(string, (ZyanU32)value, padding_length);
   }
#endif
}

ZyanStatus ZydisStringAppendDecS(ZydisString* string, ZyanI64 value, ZyanU8 padding_length)
{
    if (value < 0)
    {
        ZYAN_CHECK(ZydisStringAppendC(string, "-"));
        return ZydisStringAppendDecU(string, -value, padding_length);
    }
    return ZydisStringAppendDecU(string, value, padding_length);
}

ZyanStatus ZydisStringAppendHexU(ZydisString* string, ZyanU64 value, ZyanU8 padding_length,
    ZyanBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
#if defined(ZYAN_X64) || defined(ZYAN_AARCH64)
    return ZydisStringAppendHexU64(string, value, padding_length, uppercase, prefix, suffix);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisStringAppendHexU64(string, value, padding_length, uppercase, prefix, suffix);
   } else
   {
       return ZydisStringAppendHexU32(
           string, (ZyanU32)value, padding_length, uppercase, prefix, suffix);
   }
#endif
}

ZyanStatus ZydisStringAppendHexS(ZydisString* string, ZyanI64 value, ZyanU8 padding_length,
    ZyanBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
    if (value < 0)
    {
        ZYAN_CHECK(ZydisStringAppendC(string, "-"));
        if (prefix)
        {
            ZYAN_CHECK(ZydisStringAppend(string, prefix));
        }
        return ZydisStringAppendHexU(string, -value, padding_length, uppercase, ZYAN_NULL, suffix);
    }
    return ZydisStringAppendHexU(string, value, padding_length, uppercase, prefix, suffix);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
