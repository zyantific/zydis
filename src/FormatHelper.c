/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

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

#include <string.h>
#include <ctype.h>
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

static uint16_t const decimalLookup[100] = 
{
    0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830, 0x3930,
    0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731, 0x3831, 0x3931,
    0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732, 0x3832, 0x3932,
    0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633, 0x3733, 0x3833, 0x3933,
    0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734, 0x3834, 0x3934,
    0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735, 0x3835, 0x3935,
    0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936,
    0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837, 0x3937,
    0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938,
    0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839, 0x3939 
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Public Functions                                                                               */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisPrintStr(char** buffer, size_t bufferLen, const char* text, 
    ZydisLetterCase letterCase)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen > 0);
    ZYDIS_ASSERT(text);

    size_t strLen = strlen(text);
    if (strLen >= bufferLen)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    memcpy(*buffer, text, strLen + 1);
    switch (letterCase)
    {
    case ZYDIS_LETTER_CASE_LOWER:
        for (size_t i = 0; i < strLen; ++i)
        {
            (*buffer[i]) = (char)tolower((*buffer)[i]);    
        }
        break;
    case ZYDIS_LETTER_CASE_UPPER:
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

ZydisStatus ZydisPrintDec32U(char** buffer, size_t bufferLen, uint32_t value, uint8_t paddingLength)
{
#ifdef ZYDIS_X64
    return ZydisPrintDec64U(buffer, bufferLen, value, paddingLength);
#else
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen > 0);
    ZYDIS_ASSERT(paddingLength <= sizeof(ZYDIS_PADDING_STRING) / sizeof(ZYDIS_PADDING_STRING[0]));

    char temp[ZYDIS_MAXCHARS_DEC_32 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_32];
    *p = '\0';
    while(value >= 100)
    {
        uint32_t const old = value;
        p -= 2;
        value /= 100;
        memcpy(p, &decimalLookup[old - (value * 100)], sizeof(uint16_t));
    }
    p -= 2;
    memcpy(p, &decimalLookup[value], sizeof(uint16_t));

    size_t n = &temp[ZYDIS_MAXCHARS_DEC_32] - p;
    if ((bufferLen < n + 1) || (bufferLen < paddingLength + 1))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    uintptr_t offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        memset((*buffer), '0', offset);
    }

    memcpy(&(*buffer)[offset], &p[value < 10], n + 1);
    *buffer += n + offset - 1;

    return ZYDIS_STATUS_SUCCESS;
#endif
}

ZydisStatus ZydisPrintDec64U(char** buffer, size_t bufferLen, uint64_t value, uint8_t paddingLength)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen > 0);
    ZYDIS_ASSERT(paddingLength <= sizeof(ZYDIS_PADDING_STRING) / sizeof(ZYDIS_PADDING_STRING[0]));

    char temp[ZYDIS_MAXCHARS_DEC_64 + 1];
    char *p = &temp[ZYDIS_MAXCHARS_DEC_64];
    *p = '\0';
    while(value >= 100)
    {
        uint64_t const old = value;
        p -= 2;
        value /= 100;
        memcpy(p, &decimalLookup[old - (value * 100)], sizeof(uint16_t));
    }
    p -= 2;
    memcpy(p, &decimalLookup[value], sizeof(uint16_t));

    size_t n = &temp[ZYDIS_MAXCHARS_DEC_64] - p;
    if ((bufferLen < n + 1) || (bufferLen < paddingLength + 1))
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    uintptr_t offset = 0;
    if (n <= paddingLength)
    {
        offset = paddingLength - n + 1;
        memset((*buffer), '0', offset);
    }

    memcpy(&(*buffer)[offset], &p[value < 20], n + 1);
    *buffer += n + offset - 1;

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintDec8S(char** buffer, size_t bufferLen, int8_t value, uint8_t paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
        return ZydisPrintDec32U(buffer, bufferLen - 1, -value, paddingLength);
    }
    return ZydisPrintDec32U(buffer, bufferLen, value, paddingLength);
}

ZydisStatus ZydisPrintDec16S(char** buffer, size_t bufferLen, int16_t value, uint8_t paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
        return ZydisPrintDec32U(buffer, bufferLen - 1, -value, paddingLength);
    }
    return ZydisPrintDec32U(buffer, bufferLen, value, paddingLength);
}

ZydisStatus ZydisPrintDec32S(char** buffer, size_t bufferLen, int32_t value, uint8_t paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
        return ZydisPrintDec32U(buffer, bufferLen - 1, -value, paddingLength);
    }
    return ZydisPrintDec32U(buffer, bufferLen, value, paddingLength);
}

ZydisStatus ZydisPrintDec64S(char** buffer, size_t bufferLen, int64_t value, uint8_t paddingLength)
{
    if (value < 0)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
        return ZydisPrintDec64U(buffer, bufferLen - 1, -value, paddingLength);
    }
    return ZydisPrintDec64U(buffer, bufferLen, value, paddingLength);
}

ZydisStatus ZydisPrintHex32U(char** buffer, size_t bufferLen, uint32_t value, uint8_t paddingLength, 
    ZydisBool uppercase, ZydisBool prefix)
{
#ifdef ZYDIS_X64
    return ZydisPrintHex64U(buffer, bufferLen, value, paddingLength, uppercase, prefix);
#else
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen);

    if (prefix)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "0x", ZYDIS_LETTER_CASE_DEFAULT));
        bufferLen -= 2;
    }
    if (bufferLen < paddingLength + 1)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        uint8_t n = (paddingLength ? paddingLength : 1);

        if (bufferLen < n + 1)
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        memset((*buffer), '0', n);
        (*buffer)[n] = '\0'; 
        *buffer += n;    
        return ZYDIS_STATUS_SUCCESS;
    }

    char temp[ZYDIS_MAXCHARS_HEX_32];
    uint8_t n = 0;
    for (int8_t i = ZYDIS_MAXCHARS_HEX_32 - 1; i >= 0; --i)
    {
        uint8_t v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (bufferLen <= (uint8_t)(i + 1))
            {
                return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }    
        }
        if (uppercase)
        {
            temp[n++] = "0123456789ABCDEF"[v];    
        } else
        {
            temp[n++] = "0123456789abcdef"[v];
        }     
    }

    uint8_t offset = 0;
    if (paddingLength > n)
    {
        offset = paddingLength - n;
        memset(*buffer, '0', offset);
    }
    memcpy(&(*buffer)[offset], temp, n);
    (*buffer)[offset + n] = '\0';

    *buffer += n + offset;

    return ZYDIS_STATUS_SUCCESS;
#endif
}

ZydisStatus ZydisPrintHex64U(char** buffer, size_t bufferLen, uint64_t value, uint8_t paddingLength,
    ZydisBool uppercase, ZydisBool prefix)
{
    ZYDIS_ASSERT(buffer);
    ZYDIS_ASSERT(bufferLen);

    if (prefix)
    {
        ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "0x", ZYDIS_LETTER_CASE_DEFAULT));
        bufferLen -= 2;
    }
    if (bufferLen < paddingLength + 1)
    {
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    if (!value)
    {
        uint8_t n = (paddingLength ? paddingLength : 1);

        if (bufferLen < n + 1)
        {
            return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        memset((*buffer), '0', n);
        (*buffer)[n] = '\0'; 
        *buffer += n;    
        return ZYDIS_STATUS_SUCCESS;
    }

    char temp[ZYDIS_MAXCHARS_HEX_64];
    uint8_t n = 0;
    for (int8_t i = 
        ((value & 0xFFFFFFFF00000000) ? ZYDIS_MAXCHARS_HEX_64 : ZYDIS_MAXCHARS_HEX_32) - 1; 
        i >= 0; --i)
    {
        uint8_t v = (value >> i * 4) & 0x0F;
        if (!n)
        {
            if (!v)
            {
                continue;
            }
            if (bufferLen <= (uint8_t)(i + 1))
            {
                return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
            }    
        }
        if (uppercase)
        {
            temp[n++] = "0123456789ABCDEF"[v];    
        } else
        {
            temp[n++] = "0123456789abcdef"[v];
        }     
    }

    uint8_t offset = 0;
    if (paddingLength > n)
    {
        offset = paddingLength - n;
        memset(*buffer, '0', offset);
    }
    memcpy(&(*buffer)[offset], temp, n);
    (*buffer)[offset + n] = '\0';

    *buffer += n + offset;

    return ZYDIS_STATUS_SUCCESS;
}

ZydisStatus ZydisPrintHex8S(char** buffer, size_t bufferLen, int8_t value, uint8_t paddingLength,
    ZydisBool uppercase, ZydisBool prefix)
{
    if (value < 0)
    {
        if (prefix)
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-0x", ZYDIS_LETTER_CASE_DEFAULT));
            bufferLen -= 3;
        } else
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
            --bufferLen;
        }
        return ZydisPrintHex32U(buffer, bufferLen, -value, paddingLength, uppercase, ZYDIS_FALSE);
    }
    return ZydisPrintHex32U(buffer, bufferLen, value, paddingLength, uppercase, prefix);   
}

ZydisStatus ZydisPrintHex16S(char** buffer, size_t bufferLen, int16_t value, uint8_t paddingLength,
    ZydisBool uppercase, ZydisBool prefix)
{
    if (value < 0)
    {
        if (prefix)
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-0x", ZYDIS_LETTER_CASE_DEFAULT));
            bufferLen -= 3;
        } else
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
            --bufferLen;
        }
        return ZydisPrintHex32U(buffer, bufferLen, -value, paddingLength, uppercase, ZYDIS_FALSE);
    }
    return ZydisPrintHex32U(buffer, bufferLen, value, paddingLength, uppercase, prefix);
}

ZydisStatus ZydisPrintHex32S(char** buffer, size_t bufferLen, int32_t value, uint8_t paddingLength,
    ZydisBool uppercase, ZydisBool prefix)
{
    if (value < 0)
    {
        if (prefix)
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-0x", ZYDIS_LETTER_CASE_DEFAULT));
            bufferLen -= 3;
        } else
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
            --bufferLen;
        }
        return ZydisPrintHex32U(buffer, bufferLen, -value, paddingLength, uppercase, ZYDIS_FALSE);
    }
    return ZydisPrintHex32U(buffer, bufferLen, value, paddingLength, uppercase, prefix); 
}

ZydisStatus ZydisPrintHex64S(char** buffer, size_t bufferLen, int64_t value, uint8_t paddingLength,
    ZydisBool uppercase, ZydisBool prefix)
{
    if (value < 0)
    {
        if (prefix)
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-0x", ZYDIS_LETTER_CASE_DEFAULT));
            bufferLen -= 3;
        } else
        {
            ZYDIS_CHECK(ZydisPrintStr(buffer, bufferLen, "-", ZYDIS_LETTER_CASE_DEFAULT));
            --bufferLen;
        }
        return ZydisPrintHex64U(buffer, bufferLen, -value, paddingLength, uppercase, ZYDIS_FALSE);
    }
    return ZydisPrintHex64U(buffer, bufferLen, value, paddingLength, uppercase, prefix);  
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
