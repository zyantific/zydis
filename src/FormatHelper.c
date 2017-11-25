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
#include <LibC.h>

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

#ifdef ZYDIS_X86
ZydisStatus ZydisPrintDecU32(char** buffer, ZydisUSize bufferLen, ZydisU32 value, ZydisU8 paddingLength)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen > 0);

    char temp[ZYDIS_MAXCHARS_DEC_32 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_32];
    *p = '\0';
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
    if ((bufferLen < (ZydisUSize)(n + 1)) || (bufferLen < (ZydisUSize)(paddingLength + 1)))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisUSize offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        ZydisMemorySet(*buffer, '0', offset);
    }

    ZydisMemoryCopy(&(*buffer)[offset], &p[value < 10], n + 1);
    *buffer += n + offset - (ZydisU8)(value < 10);

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintHexU32(char** buffer, ZydisUSize bufferLen, ZydisU32 value, ZydisU8 paddingLength, 
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen);

    if (prefix)
    {
        const char* bufEnd = *buffer + bufferLen;
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, prefix, ZYDIS_LETTER_CASE_DEFAULT));
        bufferLen = bufEnd - *buffer;
    }
    if (bufferLen < (ZydisUSize)(paddingLength + 1))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZydisU8 n = (paddingLength ? paddingLength : 1);

        if (bufferLen < (ZydisUSize)(n + 1))
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZydisMemorySet(*buffer, '0', n);
        (*buffer)[n] = '\0'; 
        *buffer += n;    
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
            if (bufferLen <= (ZydisU8)(i + 1))
            {
                return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
            } 
            if (paddingLength > i)
            {
                n = paddingLength - i - 1;
                ZydisMemorySet(*buffer, '0', n);
            }
        }
        if (uppercase)
        {
            (*buffer)[n++] = "0123456789ABCDEF"[v];    
        } else
        {
            (*buffer)[n++] = "0123456789abcdef"[v];
        }     
    }
    (*buffer)[n] = '\0';
    *buffer += n;

    if (suffix)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen - n, suffix, ZYDIS_LETTER_CASE_DEFAULT));    
    }

    return ZYDIS_STATUS_SUCCESS;
}
#endif

ZydisStatus ZydisPrintDecU64(char** buffer, ZydisUSize bufferLen, ZydisU64 value, ZydisU8 paddingLength)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen > 0);

    char temp[ZYDIS_MAXCHARS_DEC_64 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_64];
    *p = '\0';
    while (value >= 100)
    {
        ZydisU64 const old = value;
        p -= 2;
        value /= 100;
        ZydisMemoryCopy(p, &decimalLookup[(old - (value * 100)) * 2], 2);
    }
    p -= 2;
    ZydisMemoryCopy(p, &decimalLookup[value * 2], 2);

    const ZydisUSize n = &temp[ZYDIS_MAXCHARS_DEC_64] - p;
    if ((bufferLen < (ZydisUSize)(n + 1)) || (bufferLen < (ZydisUSize)(paddingLength + 1)))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisUSize offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        ZydisMemorySet(*buffer, '0', offset);
    }

    ZydisMemoryCopy(&(*buffer)[offset], &p[value < 10], n + 1);
    *buffer += n + offset - (ZydisU8)(value < 10);

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintHexU64(char** buffer, ZydisUSize bufferLen, ZydisU64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen);

    if (prefix)
    {
        const char* bufEnd = *buffer + bufferLen;
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, prefix, ZYDIS_LETTER_CASE_DEFAULT));
        bufferLen = bufEnd - *buffer;
    }
    if (bufferLen < (ZydisUSize)(paddingLength + 1))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        const ZydisU8 n = (paddingLength ? paddingLength : 1);

        if (bufferLen < (ZydisUSize)(n + 1))
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZydisMemorySet(*buffer, '0', n);
        (*buffer)[n] = '\0'; 
        *buffer += n;    
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
            if (bufferLen <= (ZydisU8)(i + 1))
            {
                return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }  
            if (paddingLength > i)
            {
                n = paddingLength - i - 1;
                ZydisMemorySet(*buffer, '0', n);
            }
        }
        if (uppercase)
        {
            (*buffer)[n++] = "0123456789ABCDEF"[v];    
        } else
        {
            (*buffer)[n++] = "0123456789abcdef"[v];
        }     
    }
    (*buffer)[n] = '\0';
    *buffer += n;

    if (suffix)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen - n, suffix, ZYDIS_LETTER_CASE_DEFAULT));    
    }

    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Public Functions                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisPrintStr(char** buffer, ZydisUSize bufferLen, const char* text, 
    ZydisLetterCase letterCase)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen > 0);
    ZYDIS_ASSERT(text);

    const ZydisUSize strLen = ZydisStrLen(text);
    if (strLen >= bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisMemoryCopy(*buffer, text, strLen + 1);
    switch (letterCase)
    {
    case ZYDIS_LETTER_CASE_DEFAULT:
        break;
    case ZYDIS_LETTER_CASE_LOWER:
        ZydisToLowerCase(*buffer, strLen);
        break;
    case ZYDIS_LETTER_CASE_UPPER:
        ZydisToUpperCase(*buffer, strLen);
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
    *buffer += strLen;
    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintDecU(char** buffer, ZydisUSize bufferLen, ZydisU64 value, ZydisU8 paddingLength)
{
#ifdef ZYDIS_X64
    return ZydisPrintDecU64(buffer, bufferLen, value, paddingLength);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisPrintDecU64(buffer, bufferLen, value, paddingLength);
   } else
   {
       return ZydisPrintDecU32(buffer, bufferLen, (ZydisU32)value, paddingLength);
   }
#endif    
}

ZydisStatus ZydisPrintDecS(char** buffer, ZydisUSize bufferLen, ZydisI64 value, ZydisU8 paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
        return ZydisPrintDecU(buffer, bufferLen - 1, -value, paddingLength);
    }
    return ZydisPrintDecU(buffer, bufferLen, value, paddingLength);
}

ZydisStatus ZydisPrintHexU(char** buffer, ZydisUSize bufferLen, ZydisU64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
#ifdef ZYDIS_X64
    return ZydisPrintHexU64(buffer, bufferLen, value, paddingLength, uppercase, prefix, suffix);
#else
   if (value & 0xFFFFFFFF00000000)
   {
       return ZydisPrintHexU64(buffer, bufferLen, value, paddingLength, uppercase, prefix, suffix);
   } else
   {
       return ZydisPrintHexU32(buffer, bufferLen, (ZydisU32)value, paddingLength, uppercase, 
           prefix, suffix);
   }
#endif
}

ZydisStatus ZydisPrintHexS(char** buffer, ZydisUSize bufferLen, ZydisI64 value, ZydisU8 paddingLength,
    ZydisBool uppercase, const char* prefix, const char* suffix)
{
    if (value < 0)
    {
        const char* bufEnd = *buffer + bufferLen;
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
        if (prefix)
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufEnd - *buffer, prefix, ZYDIS_LETTER_CASE_DEFAULT));
        }
        return ZydisPrintHexU(buffer, bufEnd - *buffer, -value, paddingLength, uppercase, 
            ZYDIS_NULL, suffix);
    }
    return ZydisPrintHexU(buffer, bufferLen, value, paddingLength, uppercase, prefix, suffix);  
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
