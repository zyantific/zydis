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

/**
 * @file
 * @brief Includes and defines some default datatypes.
 */

#ifndef ZYDIS_COMMONTYPES_H
#define ZYDIS_COMMONTYPES_H

#include <Zydis/Defines.h>

/* ============================================================================================== */
/* Integral types                                                                                 */
/* ============================================================================================== */

// Fixed width integer types.
#if defined(ZYDIS_WINKERNEL)
#   if !defined(ZYDIS_MSVC)
#       error "Windows kernel drivers are only supported with MSVC"
#   endif
    typedef unsigned __int8  uint8_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int64 uint64_t;
    typedef __int8           int8_t;
    typedef __int16          int16_t;
    typedef __int32          int32_t;
    typedef __int64          int64_t;
#   define UINT8_MAX  (255)
#   define UINT16_MAX (65535U)
#   define UINT32_MAX (4294967295UL)
#   define UINT64_MAX (18446744073709551615ULL)
#   define INT8_MAX   (127)
#   define INT8_MIN   (-128)
#   define INT16_MAX  (32767)
#   define INT16_MIN  (-32767-1)
#   define INT32_MIN  (-2147483647L-1)
#   define INT32_MAX  (2147483647L)
#   define INT64_MIN  (-9223372036854775807LL-1)
#   define INT64_MAX  (9223372036854775807LL)
#   define PRIX8      "hhX"
#   define PRIX16     "hX"
#   define PRIX32     "X"
#   define PRIX64     "llX"
#else
#   include <stdint.h>
#   include <inttypes.h>
#endif

// size_t, ptrdiff_t
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Boolean                                                                                        */
/* ============================================================================================== */

#define ZYDIS_FALSE 0
#define ZYDIS_TRUE  1

/**
 * @briefs  Defines the @c ZydisBool datatype.
 */
typedef uint8_t ZydisBool;

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_COMMONTYPES_H */
