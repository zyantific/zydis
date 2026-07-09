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

#include <Zydis/Internal/String.h>

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

static const char* const DECIMAL_LOOKUP =
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
/* Decimal                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#if ZYAN_ARCHITECTURE_WIDTH != 64
static ZyanStatus ZydisStringAppendDecU32(ZyanString* string, ZyanU32 value, ZyanU8 padding_length)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(!string->vector.allocator);

    char buffer[ZYDIS_MAXCHARS_DEC_32];
    char *buffer_end = &buffer[ZYDIS_MAXCHARS_DEC_32];
    char *buffer_write_pointer = buffer_end;
    while (value >= 100)
    {
        const ZyanU32 value_old = value;
        buffer_write_pointer -= 2;
        value /= 100;
        ZYAN_MEMCPY(buffer_write_pointer, &DECIMAL_LOOKUP[(value_old - (value * 100)) * 2], 2);
    }
    buffer_write_pointer -= 2;
    ZYAN_MEMCPY(buffer_write_pointer, &DECIMAL_LOOKUP[value * 2], 2);

    const ZyanUSize offset_odd    = (ZyanUSize)(value < 10);
    const ZyanUSize length_number = buffer_end - buffer_write_pointer - offset_odd;
    const ZyanUSize length_total  = ZYAN_MAX(length_number, padding_length);
    const ZyanUSize length_target = string->vector.size;

    if (string->vector.size + length_total > string->vector.capacity)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZyanUSize offset_write = 0;
    if (padding_length > length_number)
    {
        offset_write = padding_length - length_number;
        ZYAN_MEMSET((char*)string->vector.data + length_target - 1, '0', offset_write);
    }

    ZYAN_MEMCPY((char*)string->vector.data + length_target + offset_write - 1,
        buffer_write_pointer + offset_odd, length_number);
    string->vector.size = length_target + length_total;
    ZYDIS_STRING_NULLTERMINATE(string);

    return ZYAN_STATUS_SUCCESS;
}
#endif

static ZyanStatus ZydisStringAppendDecU64(ZyanString* string, ZyanU64 value, ZyanU8 padding_length)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(!string->vector.allocator);

    char buffer[ZYDIS_MAXCHARS_DEC_64];
    char *buffer_end = &buffer[ZYDIS_MAXCHARS_DEC_64];
    char *buffer_write_pointer = buffer_end;
    while (value >= 100)
    {
        const ZyanU64 value_old = value;
        buffer_write_pointer -= 2;
        ZYAN_DIV64(value, 100);
        ZYAN_MEMCPY(buffer_write_pointer, &DECIMAL_LOOKUP[(value_old - (value * 100)) * 2], 2);
    }
    buffer_write_pointer -= 2;
    ZYAN_MEMCPY(buffer_write_pointer, &DECIMAL_LOOKUP[value * 2], 2);

    const ZyanUSize offset_odd    = (ZyanUSize)(value < 10);
    const ZyanUSize length_number = buffer_end - buffer_write_pointer - offset_odd;
    const ZyanUSize length_total  = ZYAN_MAX(length_number, padding_length);
    const ZyanUSize length_target = string->vector.size;

    if (string->vector.size + length_total > string->vector.capacity)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZyanUSize offset_write = 0;
    if (padding_length > length_number)
    {
        offset_write = padding_length - length_number;
        ZYAN_MEMSET((char*)string->vector.data + length_target - 1, '0', offset_write);
    }

    ZYAN_MEMCPY((char*)string->vector.data + length_target + offset_write - 1,
        buffer_write_pointer + offset_odd, length_number);
    string->vector.size = length_target + length_total;
    ZYDIS_STRING_NULLTERMINATE(string);

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Hexadecimal                                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Returns the number of hexadecimal digits required to represent `value`.
 *
 * @param   value   The value. Must not be `0`.
 *
 * @return  The number of hexadecimal digits (1..16).
 */
ZYAN_INLINE ZyanU8 ZydisHexDigitCount(ZyanU64 value)
{
    ZYAN_ASSERT(value);
#if defined(ZYAN_GCC) || defined(ZYAN_CLANG) || defined(ZYAN_ICC)
    return (ZyanU8)(((63 - __builtin_clzll(value)) >> 2) + 1);
#else
    ZyanU8 count = 1;
    while (value >>= 4)
    {
        ++count;
    }
    return count;
#endif
}

#if ZYAN_ARCHITECTURE_WIDTH != 64
static ZyanStatus ZydisStringAppendHexU32(ZyanString* string, ZyanU32 value, ZyanU8 padding_length,
    ZyanBool force_leading_number, ZyanBool uppercase)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(!string->vector.allocator);

    const ZyanUSize len = string->vector.size;
    const ZyanUSize remaining = string->vector.capacity - len;

    if (!value)
    {
        const ZyanU8 n = (padding_length ? padding_length : 1);

        if (remaining < (ZyanUSize)n)
        {
            return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZYAN_MEMSET((char*)string->vector.data + len - 1, '0', n);
        string->vector.size = len + n;
        ZYDIS_STRING_NULLTERMINATE(string);

        return ZYAN_STATUS_SUCCESS;
    }

    const ZyanU8 digits = ZydisHexDigitCount(value);
    // Padding already yields a leading numeric character; the extra `0` is only needed when the
    // number itself starts with a letter digit
    const ZyanU8 lead_zero = (force_leading_number && (padding_length <= digits) &&
        ((ZyanU8)(value >> ((digits - 1) * 4)) > 9)) ? 1 : 0;
    const ZyanUSize total = (ZyanUSize)ZYAN_MAX(digits, padding_length) + lead_zero;

    if (remaining < total)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    char* buffer = (char*)string->vector.data + len - 1;
    if (total > (ZyanUSize)digits)
    {
        ZYAN_MEMSET(buffer, '0', total - digits);
        buffer += total - digits;
    }

    const char* const digit_chars = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    for (ZyanU8 i = digits; i-- > 0;)
    {
        *buffer++ = digit_chars[(value >> (i * 4)) & 0x0F];
    }

    string->vector.size = len + total;
    ZYDIS_STRING_NULLTERMINATE(string);

    return ZYAN_STATUS_SUCCESS;
}
#endif

static ZyanStatus ZydisStringAppendHexU64(ZyanString* string, ZyanU64 value, ZyanU8 padding_length,
    ZyanBool force_leading_number, ZyanBool uppercase)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(!string->vector.allocator);

    const ZyanUSize len = string->vector.size;
    const ZyanUSize remaining = string->vector.capacity - len;

    if (!value)
    {
        const ZyanU8 n = (padding_length ? padding_length : 1);

        if (remaining < (ZyanUSize)n)
        {
            return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
        }

        ZYAN_MEMSET((char*)string->vector.data + len - 1, '0', n);
        string->vector.size = len + n;
        ZYDIS_STRING_NULLTERMINATE(string);

        return ZYAN_STATUS_SUCCESS;
    }

    const ZyanU8 digits = ZydisHexDigitCount(value);
    // Padding already yields a leading numeric character; the extra `0` is only needed when the
    // number itself starts with a letter digit
    const ZyanU8 lead_zero = (force_leading_number && (padding_length <= digits) &&
        ((ZyanU8)(value >> ((digits - 1) * 4)) > 9)) ? 1 : 0;
    const ZyanUSize total = (ZyanUSize)ZYAN_MAX(digits, padding_length) + lead_zero;

    if (remaining < total)
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    char* buffer = (char*)string->vector.data + len - 1;
    if (total > (ZyanUSize)digits)
    {
        ZYAN_MEMSET(buffer, '0', total - digits);
        buffer += total - digits;
    }

    const char* const digit_chars = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    for (ZyanU8 i = digits; i-- > 0;)
    {
        *buffer++ = digit_chars[(value >> (i * 4)) & 0x0F];
    }

    string->vector.size = len + total;
    ZYDIS_STRING_NULLTERMINATE(string);

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Public Functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Formatting                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisStringAppendDecU(ZyanString* string, ZyanU64 value, ZyanU8 padding_length,
    const ZyanStringView* prefix, const ZyanStringView* suffix)
{
    if (prefix)
    {
        ZYAN_CHECK(ZydisStringAppend(string, prefix));
    }

#if ZYAN_ARCHITECTURE_WIDTH == 64
    ZYAN_CHECK(ZydisStringAppendDecU64(string, value, padding_length));
#else
    if (value & 0xFFFFFFFF00000000)
    {
        ZYAN_CHECK(ZydisStringAppendDecU64(string, value, padding_length));
    }
    else
    {
        ZYAN_CHECK(ZydisStringAppendDecU32(string, (ZyanU32)value, padding_length));
    }
#endif

    if (suffix)
    {
        return ZydisStringAppend(string, suffix);
    }
    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisStringAppendHexU(ZyanString* string, ZyanU64 value, ZyanU8 padding_length,
    ZyanBool force_leading_number, ZyanBool uppercase, const ZyanStringView* prefix,
    const ZyanStringView* suffix)
{
    if (prefix)
    {
        ZYAN_CHECK(ZydisStringAppend(string, prefix));
    }

#if ZYAN_ARCHITECTURE_WIDTH == 64
    ZYAN_CHECK(ZydisStringAppendHexU64(string, value, padding_length, force_leading_number,
        uppercase));
#else
    if (value & 0xFFFFFFFF00000000)
    {
        ZYAN_CHECK(ZydisStringAppendHexU64(string, value, padding_length, force_leading_number,
            uppercase));
    }
    else
    {
        ZYAN_CHECK(ZydisStringAppendHexU32(string, (ZyanU32)value, padding_length,
            force_leading_number, uppercase));
    }
#endif

    if (suffix)
    {
        return ZydisStringAppend(string, suffix);
    }
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
