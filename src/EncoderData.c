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

#include <EncoderData.h>

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

// MSVC does not like types other than (un-)signed int for bitfields
#ifdef ZYDIS_MSVC
#   pragma warning(push)
#   pragma warning(disable:4214)
#endif

#pragma pack(push, 1)

/* ---------------------------------------------------------------------------------------------- */
/* Encodable instructions                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEncodableInstructions struct.
 */
typedef struct ZydisEncodableInstructions_
{
    uint8_t count;
    uint16_t reference;
} ZydisEncodableInstructions;

/* ---------------------------------------------------------------------------------------------- */

#pragma pack(pop)

#ifdef ZYDIS_MSVC
#   pragma warning(pop)
#endif

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Forward declarations                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains an item with a reference to all encodable instructions for every mnemonic.
 */
extern const ZydisEncodableInstructions mnemonicLookup[];

/**
 * @brief   Contains the definition-data for all encodable instructions.
 */
extern const ZydisEncodableInstruction encodableInstructions[];

/* ---------------------------------------------------------------------------------------------- */
/* Mnemonic lookup table                                                                          */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/EncoderLookup.inc>

/* ---------------------------------------------------------------------------------------------- */
/* Encodable instructions                                                                         */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/EncodableInstructions.inc>

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Encodable instructions                                                                         */
/* ---------------------------------------------------------------------------------------------- */

uint8_t ZydisGetEncodableInstructions(ZydisMnemonic mnemonic, 
    const ZydisEncodableInstruction** instruction)
{
    if (mnemonic >= ZYDIS_ARRAY_SIZE(mnemonicLookup))
    {
        *instruction = NULL;
        return 0;    
    }
    const ZydisEncodableInstructions* descriptor = &mnemonicLookup[mnemonic];
    *instruction = &encodableInstructions[descriptor->reference];
    return descriptor->count;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
