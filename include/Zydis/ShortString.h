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
 * Defines the immutable and storage-efficient `ZydisShortString` struct, which
 * is used to store strings in the generated tables.
 */

#ifndef ZYDIS_SHORTSTRING_H
#define ZYDIS_SHORTSTRING_H

#include <Zycore/Defines.h>
#include <Zycore/Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

// MSVC does not like the C99 flexible-array extension
#ifdef ZYAN_MSVC
#   pragma warning(push)
#   pragma warning(disable:4200)
#endif

/**
 * Defines the `ZydisShortString` struct.
 *
 * This compact struct is mainly used for internal string-tables to save up some bytes.
 *
 * All fields in this struct should be considered as "private". Any changes may lead to unexpected
 * behavior.
 */
typedef struct ZydisShortString_
{
    /**
     * The length (number of characters) of the string (without 0-termination).
    */
    ZyanU8 size;

    /**
     * The buffer that contains the actual (null-terminated) string.
    */
    const char data[];
} ZydisShortString;

#ifdef ZYAN_MSVC
#   pragma warning(pop)
#endif

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/**
 * Defines a constant variable of an inline struct that is compatible to `ZydisShortString`.
 *
 * @param   name    Name for the symbols, prefixed by STR_DATA_, will also be used as a suffix for
 *                  the inline struct name.
 * @param   string  The C-string constant.
 */
#define ZYDIS_MAKE_SHORTSTRING(name, string) \
    static const struct ZydisShortString_ ## name ## _ \
    { \
        ZyanU8 size; \
        const char data[sizeof(string)]; \
    } STR_DATA_ ## name = { sizeof(string) - 1, string } \

/**
 * Access a previously defined shortstring as (const ZydisShortString*)
 *
 * @param   name    The name that was passed to ZYDIS_DEFINE_SHORTSTRING_DATA()
 */
#define ZYDIS_SHORTSTRING(name) ((const ZydisShortString*)&STR_DATA_ ## name)

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_SHORTSTRING_H */
