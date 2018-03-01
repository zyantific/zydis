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

/**
 * @file
 * @brief   General helper and platform detection macros.
 */

#ifndef ZYDIS_DEFINES_H
#define ZYDIS_DEFINES_H

#include <ZydisExportConfig.h>

/* ============================================================================================== */
/* Compiler detection                                                                             */
/* ============================================================================================== */

#if defined(__clang__)
#   define ZYDIS_CLANG
#   define ZYDIS_GNUC
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#   define ZYDIS_ICC
#elif defined(__GNUC__) || defined(__GNUG__)
#   define ZYDIS_GCC
#   define ZYDIS_GNUC
#elif defined(_MSC_VER)
#   define ZYDIS_MSVC
#elif defined(__BORLANDC__)
#   define ZYDIS_BORLAND
#else
#   define ZYDIS_UNKNOWN_COMPILER
#endif

/* ============================================================================================== */
/* Platform detection                                                                             */
/* ============================================================================================== */

#if defined(_WIN32)
#   define ZYDIS_WINDOWS
#elif defined(__APPLE__)
#   define ZYDIS_APPLE
#   define ZYDIS_POSIX
#elif defined(__linux)
#   define ZYDIS_LINUX
#   define ZYDIS_POSIX
#elif defined(__unix)
#   define ZYDIS_UNIX
#   define ZYDIS_POSIX
#elif defined(__posix)
#   define ZYDIS_POSIX
#else
#   define ZYDIS_UNKNOWN_PLATFORM
#endif

/* ============================================================================================== */
/* Architecture detection                                                                         */
/* ============================================================================================== */

#if defined(_M_AMD64) || defined(__x86_64__)
#   define ZYDIS_X64
#elif defined(_M_IX86) || defined(__i386__)
#   define ZYDIS_X86
#elif defined(_M_ARM64) || defined(__aarch64__)
#   define ZYDIS_AARCH64
#elif defined(_M_ARM) || defined(_M_ARMT) || defined(__arm__) || defined(__thumb__)
#   define ZYDIS_ARM
#else
#   error "Unsupported architecture detected"
#endif

/* ============================================================================================== */
/* Debug/Release detection                                                                        */
/* ============================================================================================== */

#if defined(ZYDIS_MSVC) || defined(ZYDIS_BORLAND)
#   ifdef _DEBUG
#       define ZYDIS_DEBUG
#   else
#       define ZYDIS_RELEASE
#   endif
#elif defined(ZYDIS_GNUC) || defined(ZYDIS_ICC)
#   ifdef NDEBUG
#       define ZYDIS_RELEASE
#   else
#       define ZYDIS_DEBUG
#   endif
#else
#   define ZYDIS_RELEASE
#endif

/* ============================================================================================== */
/* Misc compatibility macros                                                                      */
/* ============================================================================================== */

#if defined(ZYDIS_MSVC) || defined(ZYDIS_BORLAND)
#   define ZYDIS_INLINE __inline
#else
#   define ZYDIS_INLINE static inline
#endif

/* ============================================================================================== */
/* Debugging and optimization macros                                                              */
/* ============================================================================================== */

#if defined(ZYDIS_NO_LIBC)
#   define ZYDIS_ASSERT(condition)
#else
#   include <assert.h>
#   define ZYDIS_ASSERT(condition) assert(condition)
#endif

#if defined(ZYDIS_RELEASE)
#   if defined(ZYDIS_CLANG) // GCC eagerly evals && RHS, we have to use nested ifs.
#       if __has_builtin(__builtin_unreachable)
#           define ZYDIS_UNREACHABLE __builtin_unreachable()
#       else
#           define ZYDIS_UNREACHABLE for(;;)
#       endif
#   elif defined(ZYDIS_GCC) && ((__GNUC__ == 4 && __GNUC_MINOR__ > 4) || __GNUC__ > 4)
#       define ZYDIS_UNREACHABLE __builtin_unreachable()
#   elif defined(ZYDIS_ICC)
#       ifdef ZYDIS_WINDOWS
#           include <stdlib.h> // "missing return statement" workaround
#           define ZYDIS_UNREACHABLE __assume(0); (void)abort()
#       else
#           define ZYDIS_UNREACHABLE __builtin_unreachable()
#       endif
#   elif defined(ZYDIS_MSVC)
#       define ZYDIS_UNREACHABLE __assume(0)
#   else
#       define ZYDIS_UNREACHABLE for(;;)
#   endif
#elif defined(ZYDIS_NO_LIBC)
#   define ZYDIS_UNREACHABLE for(;;)
#else
#   include <stdlib.h>
#   define ZYDIS_UNREACHABLE { assert(0); abort(); }
#endif

/* ============================================================================================== */
/* Utils                                                                                          */
/* ============================================================================================== */

/**
 * @brief   Compiler-time assertion.
 */
#if __STDC_VERSION__ >= 201112L
#   define ZYDIS_STATIC_ASSERT(x) _Static_assert(x, #x)
#else
#   define ZYDIS_STATIC_ASSERT(x) typedef int ZYDIS_SASSERT_IMPL[(x) ? 1 : -1]
#endif

/**
 * @brief   Declares a bitfield.
 */
#define ZYDIS_BITFIELD(x) : x

/**
 * @brief   Marks the specified parameter as unused.
 */
#define ZYDIS_UNUSED_PARAMETER(x) (void)(x)

/**
 * @brief   Intentional fallthrough.
 */
#define ZYDIS_FALLTHROUGH

/**
 * @brief   Calculates the size of an array.
 */
#define ZYDIS_ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* ============================================================================================== */

#endif /* ZYDIS_DEFINES_H */
