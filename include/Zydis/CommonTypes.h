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

/**
 * @file
 * @brief Includes and defines some default datatypes.
 */

#ifndef ZYDIS_COMMONTYPES_H
#define ZYDIS_COMMONTYPES_H

#include <Zydis/Defines.h>

/* ============================================================================================== */
/* Integer types                                                                                  */
/* ============================================================================================== */

#if !defined(ZYDIS_NO_LIBC)
    // If is LibC present, we use stdint types.
#   include <stdint.h>
#   include <stddef.h>
    typedef uint8_t   ZydisU8;
    typedef uint16_t  ZydisU16;
    typedef uint32_t  ZydisU32;
    typedef uint64_t  ZydisU64;
    typedef int8_t    ZydisI8;
    typedef int16_t   ZydisI16;
    typedef int32_t   ZydisI32;
    typedef int64_t   ZydisI64;
    typedef size_t    ZydisUSize;
    typedef ptrdiff_t ZydisISize;
    typedef uintptr_t ZydisUPointer;
    typedef intptr_t  ZydisIPointer;
#else
    // No LibC, use compiler built-in types / macros.
#   if defined(ZYDIS_MSVC)
        typedef unsigned __int8  ZydisU8;
        typedef unsigned __int16 ZydisU16;
        typedef unsigned __int32 ZydisU32;
        typedef unsigned __int64 ZydisU64;
        typedef   signed __int8  ZydisI8;
        typedef   signed __int16 ZydisI16;
        typedef   signed __int32 ZydisI32;
        typedef   signed __int64 ZydisI64;
#       if _WIN64
           typedef ZydisU64      ZydisUSize;
           typedef ZydisI64      ZydisISize;
           typedef ZydisU64      ZydisUPointer;
           typedef ZydisI64      ZydisIPointer;
#       else
           typedef ZydisU32      ZydisUSize;
           typedef ZydisI32      ZydisISize;
           typedef ZydisU32      ZydisUPointer;
           typedef ZydisI32      ZydisIPointer;
#       endif
#   elif defined(ZYDIS_GNUC)
        typedef __UINT8_TYPE__   ZydisU8;
        typedef __UINT16_TYPE__  ZydisU16;
        typedef __UINT32_TYPE__  ZydisU32;
        typedef __UINT64_TYPE__  ZydisU64;
        typedef __INT8_TYPE__    ZydisI8;
        typedef __INT16_TYPE__   ZydisI16;
        typedef __INT32_TYPE__   ZydisI32;
        typedef __INT64_TYPE__   ZydisI64;
        typedef __SIZE_TYPE__    ZydisUSize;
        typedef __PTRDIFF_TYPE__ ZydisISize;
        typedef __UINTPTR_TYPE__ ZydisUPointer;
        typedef __INTPTR_TYPE__  ZydisIPointer;
#   else
#       error "Unsupported compiler for no-libc mode."
#   endif
#endif

// Verify size assumptions.
ZYDIS_STATIC_ASSERT(sizeof(ZydisU8      ) == 1            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisU16     ) == 2            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisU32     ) == 4            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisU64     ) == 8            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisI8      ) == 1            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisI16     ) == 2            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisI32     ) == 4            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisI64     ) == 8            );
ZYDIS_STATIC_ASSERT(sizeof(ZydisUSize   ) == sizeof(void*)); // TODO: This one is incorrect!
ZYDIS_STATIC_ASSERT(sizeof(ZydisISize   ) == sizeof(void*)); // TODO: This one is incorrect!
ZYDIS_STATIC_ASSERT(sizeof(ZydisUPointer) == sizeof(void*));
ZYDIS_STATIC_ASSERT(sizeof(ZydisIPointer) == sizeof(void*));

// Verify signedness assumptions (relies on size checks above).
ZYDIS_STATIC_ASSERT((ZydisI8 )-1 >> 1 < (ZydisI8 )((ZydisU8 )-1 >> 1));
ZYDIS_STATIC_ASSERT((ZydisI16)-1 >> 1 < (ZydisI16)((ZydisU16)-1 >> 1));
ZYDIS_STATIC_ASSERT((ZydisI32)-1 >> 1 < (ZydisI32)((ZydisU32)-1 >> 1));
ZYDIS_STATIC_ASSERT((ZydisI64)-1 >> 1 < (ZydisI64)((ZydisU64)-1 >> 1));

/* ============================================================================================== */
/* NULL                                                                                           */
/* ============================================================================================== */

#define ZYDIS_NULL ((void*)0)

/* ============================================================================================== */
/* Boolean                                                                                        */
/* ============================================================================================== */

#define ZYDIS_FALSE 0
#define ZYDIS_TRUE  1

/**
 * @briefs  Defines the @c ZydisBool datatype.
 */
typedef ZydisU8 ZydisBool;

/* ============================================================================================== */

#endif /* ZYDIS_COMMONTYPES_H */
