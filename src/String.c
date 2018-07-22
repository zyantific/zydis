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

#if defined(ZYDIS_X86) || defined(ZYDIS_ARM)
ZydisStatus ZydisStringAppendDecU32(ZydisString* string, ZydisU32 value, ZydisU8 paddingLength)
{
    ZYDIS_ASSERT(string);
    ZYDIS_ASSERT(string->buffer);

    char temp[ZYDIS_MAXCHARS_DEC_32 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_32];
    while (value >= 100)
    {
        ZydisU32 const old = value;
        p -= 2;
        value /= 100;
        ZydisMemoryCopy(p, &decimalLookup[(old - (value * 100)) * 2], sizeof(ZydisU16));
    }
    p -= 2;
    ZydisMemoryCopy(p, &decimalLookup[value * 2], sizeof(ZydisU16));

    const ZydisUSize n = &temp[ZYDIS_MAXCHARS_DEC_32] - p;
    if ((string->capacity - string->length < (ZydisUSize)(n + 1)) ||
        (string->capacity - string->length < (ZydisUSize)(paddingLength + 1)))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisUSize offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        ZydisMemorySet(string->buffer + string->length, '0', offset);
    }

    ZydisMemoryCopy(string->buffer + string->length + offset, &p[value < 10], n + 1);
    string->length += n + offset - (ZydisU8)(value < 10);

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisStringAppendHexU32(ZydisString* string, ZydisU32 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
    ZYDIS_ASSERT(string);
    ZYDIS_ASSERT(string->buffer);

    if (prefix)
    {
        ZYDIS_CHECK(ZydisStringAppend(string, prefix));
    }

    char* buffer = string->buffer + string->length;
    const ZydisUSize remaining = string->capacity - string->length;

    if (remaining < (ZydisUSize)paddingLength)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZydisU8 n = (paddingLength ? paddingLength : 1);

        if (remaining < (ZydisUSize)n)
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZydisMemorySet(buffer, '0', n);
        string->length += n;

        if (suffix)
        {
            ZYDIS_CHECK(ZydisStringAppend(string, suffix));
        }

        return ZYDIS_STATUS_SUCCESS;
    }

    ZydisU8 n = 0;
    for (ZydisI8 i = ZYDIS_MAXCHARS_HEX_32 - 1; i >= 0; --i)
    {
        const ZydisU8 v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (remaining <= (ZydisU8)(i + 1)) // TODO: +1?
            {
                return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }
            if (paddingLength > i)
            {
                n = paddingLength - i - 1;
                ZydisMemorySet(buffer, '0', n);
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
        ZYDIS_CHECK(ZydisStringAppend(string, suffix));
    }

    return ZYDIS_STATUS_SUCCESS;
}
#endif

ZydisStatus ZydisStringAppendDecU64(ZydisString* string, ZydisU64 value, ZydisU8 paddingLength)
{
    ZYDIS_ASSERT(string);
    ZYDIS_ASSERT(string->buffer);

    char temp[ZYDIS_MAXCHARS_DEC_64 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_64];
    while (value >= 100)
    {
        ZydisU64 const old = value;
        p -= 2;
        value /= 100;
        ZydisMemoryCopy(p, &decimalLookup[(old - (value * 100)) * 2], 2);
    }
    p -= 2;
    ZydisMemoryCopy(p, &decimalLookup[value * 2], sizeof(ZydisU16));

    const ZydisUSize n = &temp[ZYDIS_MAXCHARS_DEC_64] - p;
    if ((string->capacity - string->length < (ZydisUSize)(n + 1)) ||
        (string->capacity - string->length < (ZydisUSize)(paddingLength + 1)))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisUSize offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        ZydisMemorySet(string->buffer + string->length, '0', offset);
    }

    ZydisMemoryCopy(string->buffer + string->length + offset, &p[value < 10], n + 1);
    string->length += n + offset - (ZydisU8)(value < 10);

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisStringAppendHexU64(ZydisString* string, ZydisU64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
    ZYDIS_ASSERT(string);
    ZYDIS_ASSERT(string->buffer);

    if (prefix)
    {
        ZYDIS_CHECK(ZydisStringAppend(string, prefix));
    }

    char* buffer = string->buffer + string->length;
    const ZydisUSize remaining = string->capacity - string->length;

    if (remaining < (ZydisUSize)paddingLength)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZydisU8 n = (paddingLength ? paddingLength : 1);

        if (remaining < (ZydisUSize)n)
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZydisMemorySet(buffer, '0', n);
        string->length += n;

        if (suffix)
        {
            ZYDIS_CHECK(ZydisStringAppend(string, suffix));
        }

        return ZYDIS_STATUS_SUCCESS;
    }

    ZydisU8 n = 0;
    const ZydisU8 c =
        ((value & 0xFFFFFFFF00000000) ? ZYDIS_MAXCHARS_HEX_64 : ZYDIS_MAXCHARS_HEX_32);
    for (ZydisI8 i = c - 1; i >= 0; --i)
    {
        const ZydisU8 v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (remaining <= (ZydisU8)(i + 1)) // TODO: +1?
            {
                return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }
            if (paddingLength > i)
            {
                n = paddingLength - i - 1;
                ZydisMemorySet(buffer, '0', n);
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
        ZYDIS_CHECK(ZydisStringAppend(string, suffix));
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Public Functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Basic Operations                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisStringInit(ZydisString* string, char* text)
{
    if (!string || !text)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    const ZydisUSize length = ZydisStrLen(text);
    string->buffer   = text;
    string->length   = length;
    string->capacity = length;

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisStringFinalize(ZydisString* string)
{
    if (!string)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    if (string->length >= string->capacity)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    string->buffer[string->length] = 0;
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisStringAppend(ZydisString* string, const ZydisString* text)
{
    return ZydisStringAppendEx(string, text, ZYDIS_LETTER_CASE_DEFAULT);
}

ZydisStatus ZydisStringAppendEx(ZydisString* string, const ZydisString* text,
    ZydisLetterCase letterCase)
{
    if (!string || !text)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    if (string->length + text->length >= string->capacity)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisMemoryCopy(string->buffer + string->length, text->buffer, text->length);
    switch (letterCase)
    {
    case ZYDIS_LETTER_CASE_DEFAULT:
        break;
    case ZYDIS_LETTER_CASE_LOWER:
    {
        const signed char rebase = 'a' - 'A';
        char* c = string->buffer + string->length;
        for (ZydisUSize i = 0; i < text->length; ++i)
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
        for (ZydisUSize i = 0; i < text->length; ++i)
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
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    string->length += text->length;

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisStringAppendC(ZydisString* string, const char* text)
{
    ZydisString other;
    ZYDIS_CHECK(ZydisStringInit(&other, (char*)text));

    return ZydisStringAppendEx(string, &other, ZYDIS_LETTER_CASE_DEFAULT);
}

ZydisStatus ZydisStringAppendExC(ZydisString* string, const char* text, ZydisLetterCase letterCase)
{
    ZydisString other;
    ZYDIS_CHECK(ZydisStringInit(&other, (char*)text));

    return ZydisStringAppendEx(string, &other, letterCase);
}

ZydisStatus ZydisStringAppendStatic(ZydisString* string, const ZydisStaticString* text,
    ZydisLetterCase letterCase)
{
    if (!text || !text->buffer)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisString other;
    other.buffer = (char*)text->buffer;
    other.length = text->length;

    return ZydisStringAppendEx(string, &other, letterCase);
}

ZydisStatus ZydisStringAppendExStatic(ZydisString* string, const ZydisStaticString* text,
    ZydisLetterCase letterCase)
{
    if (!text || !text->buffer)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }

    ZydisString other;
    other.buffer = (char*)text->buffer;
    other.length = text->length;

    return ZydisStringAppendEx(string, &other, letterCase);
}

/* ---------------------------------------------------------------------------------------------- */
/* Formatting                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisStringAppendDecU(ZydisString* string, ZydisU64 value, ZydisU8 paddingLength)
{
#if defined(ZYDIS_X64) || defined(ZYDIS_AARCH64)
    return ZydisStringAppendDecU64(string, value, paddingLength);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisStringAppendDecU64(string, value, paddingLength);
   } else
   {
       return ZydisStringAppendDecU32(string, (ZydisU32)value, paddingLength);
   }
#endif
}

ZydisStatus ZydisStringAppendDecS(ZydisString* string, ZydisI64 value, ZydisU8 paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisStringAppendC(string, "-"));
        return ZydisStringAppendDecU(string, -value, paddingLength);
    }
    return ZydisStringAppendDecU(string, value, paddingLength);
}

ZydisStatus ZydisStringAppendHexU(ZydisString* string, ZydisU64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
#if defined(ZYDIS_X64) || defined(ZYDIS_AARCH64)
    return ZydisStringAppendHexU64(string, value, paddingLength, uppercase, prefix, suffix);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisStringAppendHexU64(string, value, paddingLength, uppercase, prefix, suffix);
   } else
   {
       return ZydisStringAppendHexU32(
           string, (ZydisU32)value, paddingLength, uppercase, prefix, suffix);
   }
#endif
}

ZydisStatus ZydisStringAppendHexS(ZydisString* string, ZydisI64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const ZydisString* prefix, const ZydisString* suffix)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisStringAppendC(string, "-"));
        if (prefix)
        {
            ZYDIS_CHECK(ZydisStringAppend(string, prefix));
        }
        return ZydisStringAppendHexU(string, -value, paddingLength, uppercase, ZYDIS_NULL, suffix);
    }
    return ZydisStringAppendHexU(string, value, paddingLength, uppercase, prefix, suffix);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
