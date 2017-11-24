/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Joel Höner

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

#ifndef ZYDIS_LIBC_H
#define ZYDIS_LIBC_H

#include <Zydis/Defines.h>
#include <stdint.h>

#ifndef ZYDIS_NO_LIBC

/* ============================================================================================== */
/* LibC is available                                                                              */
/* ============================================================================================== */

#   define ZydisMemoryCopy memcpy
#   define ZydisMemorySet  memset
#   define ZydisStrLen     strlen

#else

/* ============================================================================================== */
/* No LibC available, use our own functions                                                       */
/* ============================================================================================== */

/*
 * These implementations are by no means optimized and will be outperformed by pretty much any
 * libc implementation out there. We do not aim towards providing competetive implementations here,
 * but towards providing a last resort fallback for environments without a working libc.
 */

ZYDIS_INLINE void* ZydisMemorySet(void* ptr, int value, size_t num)
{
    uint8_t c = value & 0xff;
    for (uint8_t* p = (uint8_t*)ptr; *p; ++p) *p = c;
    return ptr;
}

ZYDIS_INLINE void* ZydisMemoryCopy(void* dst, const void* src, size_t num)
{
    for (size_t i = 0; i < num; ++i)
    {
        ((uint8_t*)dst)[i] = ((const uint8_t*)src)[i];
    }
    return dst;
}

ZYDIS_INLINE size_t ZydisStrLen(const char* str)
{
    const char *s;
    for (s = str; *s; ++s);
    return s - str;
}

/* ============================================================================================== */

#endif

#endif /* ZYDIS_LIBC_H */
