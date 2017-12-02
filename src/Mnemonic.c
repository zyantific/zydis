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

#include <Zydis/Mnemonic.h>

/* ============================================================================================== */
/* Mnemonic strings                                                                               */
/* ============================================================================================== */

#pragma pack(push, 1)

/**
 * @brief   Defines the `ZydisGeneratedString` struct. 
 */
typedef struct ZydisGeneratedString_
{
    /**
     * @brief   Contains the actual string.
    */
    char* buffer;
    /**
     * @brief   The length of the string (without 0-termination).
    */
    ZydisU8 length;
} ZydisGeneratedString;

#pragma pack(pop)

#include <Generated/EnumMnemonic.inc>

/**
 * @brief   Contains all strings that were accessed by `ZydisMnemonicGetStringEx`.
 * 
 * We could store `ZydisString` structs instead of `ZydisInternalString` ones in the 
 * `zydisMnemonicStrings` array, but this would significantly increase the table-size.  
 */
static ZydisString stringTable[ZYDIS_MNEMONIC_MAX_VALUE + 1];

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

const char* ZydisMnemonicGetString(ZydisMnemonic mnemonic)
{
    if (mnemonic > ZYDIS_ARRAY_SIZE(zydisMnemonicStrings) - 1)
    {
        return ZYDIS_NULL;
    }
    return (const char*)zydisMnemonicStrings[mnemonic].buffer;
}

const ZydisString* ZydisMnemonicGetStringEx(ZydisMnemonic mnemonic)
{
    if (mnemonic > ZYDIS_ARRAY_SIZE(zydisMnemonicStrings) - 1)
    {
        return ZYDIS_NULL;
    }
    if (!stringTable[mnemonic].buffer)
    {
        stringTable[mnemonic].buffer   = zydisMnemonicStrings[mnemonic].buffer;
        stringTable[mnemonic].length   = zydisMnemonicStrings[mnemonic].length;
        stringTable[mnemonic].capacity = zydisMnemonicStrings[mnemonic].length;
    }
    return &stringTable[mnemonic];
}

/* ============================================================================================== */
