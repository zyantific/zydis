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

#include <FormatHelper.h>

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
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internal Functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

void ZydisToLowerCase(char* buffer, ZydisUSize bufferLen)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen);

    const signed char rebase = 'a' - 'A';
    for (ZydisUSize i = 0; i < bufferLen; ++i)
    {
        char* c = buffer + i;
        if ((*c >= 'A') && (*c <= 'Z'))
        {
            *c += rebase;
        }
    }
}

void ZydisToUpperCase(char* buffer, ZydisUSize bufferLen)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen);

    const signed char rebase = 'A' - 'a';
    for (ZydisUSize i = 0; i < bufferLen; ++i)
    {
        char* c = buffer + i;
        if ((*c >= 'a') && (*c <= 'z'))
        {
            *c += rebase;
        }
    }
}

ZydisStatus ZydisPrintDecU64(ZydisString* s, ZydisU64 value, ZydisU8 paddingLength)
{
    ZYDIS_ASSERT(s);

    char temp[ZYDIS_MAXCHARS_DEC_64 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_64];

    while (value >= 100)
    {
        const ZydisU64 old = value;
        p -= 2;
        value /= 100;
        ZydisMemoryCopy(p, &decimalLookup[(old - (value * 100)) * 2], 2);
    }
    p -= 2;
    ZydisMemoryCopy(p, &decimalLookup[value * 2], 2);

    const ZydisUSize n = &temp[ZYDIS_MAXCHARS_DEC_64] - p;
    if ((s->capacity - s->length < (ZydisUSize)(n + 1)) || 
        (s->capacity - s->length < (ZydisUSize)(paddingLength + 1)))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisUSize offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        ZydisMemorySet(s->s + s->length, '0', offset);
    }

    ZydisMemoryCopy(s->s + s->length + offset, &p[value < 10], n + 1);
    s->length += n + offset - (ZydisU8)(value < 10);

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintHexU64(ZydisString* s, ZydisU64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
    ZYDIS_ASSERT(s);

    if (prefix)
    {
        ZYDIS_CHECK(ZydisStringAppendC(s, prefix, ZYDIS_LETTER_CASE_DEFAULT));
    }

    char* buffer = s->s + s->length;
    ZydisUSize numRemainingBytes = s->capacity - s->length;

    if (numRemainingBytes < (ZydisUSize)paddingLength)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZydisU8 n = (paddingLength ? paddingLength : 1);

        if (numRemainingBytes < (ZydisUSize)n)
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZydisMemorySet(buffer, '0', n);
        s->length += n;    
        return ZYDIS_STATUS_SUCCESS;
    }

    ZydisU8 n = 0;
    const ZydisU8 c = ((value & 0xFFFFFFFF00000000) ? ZYDIS_MAXCHARS_HEX_64 : ZYDIS_MAXCHARS_HEX_32);
    for (ZydisI8 i = c - 1; i >= 0; --i)
    {
        const ZydisU8 v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (numRemainingBytes <= (ZydisU8)(i + 1))
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
    s->length += n;

    if (suffix)
    {
        ZYDIS_CHECK(ZydisStringAppendC(s, suffix, ZYDIS_LETTER_CASE_DEFAULT));    
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Public Functions                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisStringAppend(ZydisString* s, const ZydisString* text, ZydisLetterCase letterCase)
{
    ZYDIS_ASSERT(s);
    ZYDIS_ASSERT(s->capacity >= s->length);
    ZYDIS_ASSERT(text);
    ZYDIS_ASSERT(text->capacity >= s->length);

    if (s->length + text->length >= s->capacity)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisMemoryCopy(s->s + s->length, text->s, text->length);

    switch (letterCase)
    {
    case ZYDIS_LETTER_CASE_DEFAULT:
        break;
    case ZYDIS_LETTER_CASE_LOWER:
        ZydisToLowerCase(s->s + s->length, text->length);
        break;
    case ZYDIS_LETTER_CASE_UPPER:
        ZydisToUpperCase(s->s + s->length, text->length);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }

    s->length += text->length;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintDecU(ZydisString *s, ZydisU64 value, ZydisU8 paddingLength)
{
#if defined(ZYDIS_X64) || defined(ZYDIS_AARCH64)
    return ZydisPrintDecU64(s, value, paddingLength);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisPrintDecU64(s, value, paddingLength);
   } else
   {
       return ZydisPrintDecU32(s, (ZydisU32)value, paddingLength);
   }
#endif    
}

ZydisStatus ZydisPrintDecS(ZydisString *s, ZydisI64 value, ZydisU8 paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisStringAppendC(s, "-", ZYDIS_LETTER_CASE_DEFAULT));
        return ZydisPrintDecU(s, -value, paddingLength);
    }
    return ZydisPrintDecU(s, value, paddingLength);
}

ZydisStatus ZydisPrintHexU(ZydisString *s, ZydisU64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
#if defined(ZYDIS_X64) || defined(ZYDIS_AARCH64)
    return ZydisPrintHexU64(s, value, paddingLength, uppercase, prefix, suffix);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisPrintHexU64(s, value, paddingLength, uppercase, prefix, suffix);
   } else
   {
       return ZydisPrintHexU32(s, (ZydisU32)value, paddingLength, uppercase, prefix, suffix);
   }
#endif
}

ZydisStatus ZydisPrintHexS(ZydisString *s, ZydisI64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisStringAppendC(s, "-", ZYDIS_LETTER_CASE_DEFAULT));
        if (prefix)
        {
            ZYDIS_CHECK(ZydisStringAppendC(s, prefix, ZYDIS_LETTER_CASE_DEFAULT));
        }
        return ZydisPrintHexU(s, -value, paddingLength, uppercase, ZYDIS_NULL, suffix);
    }
    return ZydisPrintHexU(s, value, paddingLength, uppercase, prefix, suffix);  
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
