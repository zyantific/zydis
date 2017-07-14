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

#ifndef ZYDIS_ENCODERDATA_H
#define ZYDIS_ENCODERDATA_H

#include <Zydis/Defines.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/SharedTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

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
/* Encodable instruction                                                                          */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEncodableInstruction struct.
 */
typedef struct ZydisEncodableInstruction_
{
    uint16_t definitionReference        ZYDIS_BITFIELD(13);
    ZydisInstructionEncoding encoding   ZYDIS_BITFIELD( 3);
    uint8_t opcode                      ZYDIS_BITFIELD( 8);
    ZydisOpcodeMap opcodeMap            ZYDIS_BITFIELD( 3); 
    uint8_t mode                        ZYDIS_BITFIELD( 3); 
    uint8_t operandSize                 ZYDIS_BITFIELD( 3);
    uint8_t addressSize                 ZYDIS_BITFIELD( 3);
    uint8_t modrmMod                    ZYDIS_BITFIELD( 4); 
    ZydisBool forceModrmReg             ZYDIS_BITFIELD( 1);
    uint8_t modrmReg                    ZYDIS_BITFIELD( 8); 
    ZydisBool forceModrmRm              ZYDIS_BITFIELD( 1);
    uint8_t modrmRm                     ZYDIS_BITFIELD( 8); 
    uint8_t mandatoryPrefix             ZYDIS_BITFIELD( 3); 
    uint8_t vectorLength                ZYDIS_BITFIELD( 2);
    uint8_t rexW                        ZYDIS_BITFIELD( 1);
    uint8_t rexB                        ZYDIS_BITFIELD( 2); 
    uint8_t evexB                       ZYDIS_BITFIELD( 1); 
    uint8_t mvexE                       ZYDIS_BITFIELD( 2); 
} ZydisEncodableInstruction;

/* ---------------------------------------------------------------------------------------------- */

#pragma pack(pop)

#ifdef ZYDIS_MSVC
#   pragma warning(pop)
#endif

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Encodable instructions                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns all encodable instructions matching the given `mnemonic`.
 *
 * @param   mnemonic    The mnemonic.
 * @param   instruction A pointer to the variable that receives a pointer to the first 
 *                      `ZydisEncodableInstruction` struct.
 *                          
 * @return  The number of encodable instructions for the given mnemonic.
 */
ZYDIS_NO_EXPORT uint8_t ZydisGetEncodableInstructions(ZydisMnemonic mnemonic, 
    const ZydisEncodableInstruction** instruction);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_ENCODERDATA_H */
