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
 * @brief   Functions for decoding instructions.
 */

#ifndef ZYDIS_DECODER_H
#define ZYDIS_DECODER_H

#include <Zydis/CommonTypes.h>
#include <Zydis/DecoderTypes.h>
#include <Zydis/Defines.h>
#include <Zydis/Status.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Decoder flags                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisDecoderFlags datatype.
 */
typedef uint8_t ZydisDecoderFlags;

/**
 * @brief   Enables minimal instruction decoding without semantic analysis.
 * 
 * This mode provides access to the mnemonic, the instruction-length, the effective 
 * operand-size, the effective address-width, some attributes (e.g. `ZYDIS_ATTRIB_IS_RELATIVE`) 
 * and all of the information in the `raw` field of the `ZydisDecodedInstruction` struct.
 * 
 * Operands, most attributes and other specific information (like AVX info) are not 
 * accessible in this mode.
 */
#define ZYDIS_DECODER_FLAG_MINIMAL      0x01 // (1 << 0)
/**
 * @brief   Enables the AMD-branch mode.
 * 
 * Intel ignores the operand-size override-prefix (`0x66`) for all branches with 32-bit 
 * immediates and forces the operand-size of the instruction to 64-bit in 64-bit mode.
 * In AMD-branch mode `0x66` is not ignored and changes the operand-size and the size of the
 * immediate to 16-bit.
 */
#define ZYDIS_DECODER_FLAG_AMD_BRANCHES 0x02 // (1 << 1)
/**
 * @brief   Enables the MPX mode.
 * 
 * The MPX ISA-extension reuses (overrides) some of the widenop instruction opcodes. 
 * 
 * This mode is enabled by default. 
 */
#define ZYDIS_DECODER_FLAG_MPX          0x04 // (1 << 2)
/**
 * @brief   Enables the CET mode.
 * 
 * The CET ISA-extension reuses (overrides) some of the widenop instruction opcodes. 
 * 
 * This mode is enabled by default.  
 */
#define ZYDIS_DECODER_FLAG_CET          0x08 // (1 << 3)
/**
 * @brief   Enables the LZCNT mode.
 * 
 * The LZCNT ISA-extension reuses (overrides) some of the widenop instruction opcodes.
 * 
 * This mode is enabled by default.   
 */
#define ZYDIS_DECODER_FLAG_LZCNT        0x10 // (1 << 4)
/**
 * @brief   Enables the TZCNT mode.
 * 
 * The TZCNT ISA-extension reuses (overrides) some of the widenop instruction opcodes.  
 * 
 * This mode is enabled by default. 
 */
#define ZYDIS_DECODER_FLAG_TZCNT        0x20 // (1 << 5)

/**
 * @brief   The default set of decoder-flags.
 */
#define ZYDIS_DECODER_FLAG_DEFAULT_MASK ZYDIS_DECODER_FLAG_MPX | \
                                        ZYDIS_DECODER_FLAG_CET | \
                                        ZYDIS_DECODER_FLAG_LZCNT | \
                                        ZYDIS_DECODER_FLAG_TZCNT

/* ---------------------------------------------------------------------------------------------- */
/* Decoder struct                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisDecoder struct.
 */
typedef struct ZydisDecoder_
{
    ZydisMachineMode machineMode;
    ZydisAddressWidth addressWidth;
    ZydisDecoderFlags flags;
} ZydisDecoder;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Initializes the given @c ZydisDecoder instance.
 *
 * @param   decoder         A pointer to the @c ZydisDecoder instance.
 * @param   machineMode     The machine mode.
 * @param   addressWidth    The address width.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderInit(ZydisDecoder* decoder, ZydisMachineMode machineMode, 
    ZydisAddressWidth addressWidth);

/**
 * @brief   Initializes the given @c ZydisDecoder instance.
 *
 * @param   decoder         A pointer to the @c ZydisDecoder instance.
 * @param   machineMode     The machine mode.
 * @param   addressWidth    The address width.
 * @param   flags           Additional decoder flags.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderInitEx(ZydisDecoder* decoder, ZydisMachineMode machineMode, 
    ZydisAddressWidth addressWidth, ZydisDecoderFlags flags);

/**
 * @brief   Decodes the instruction in the given input @c buffer.
 *
 * @param   decoder             A pointer to the @c ZydisDecoder instance.
 * @param   buffer              A pointer to the input buffer.
 * @param   bufferLen           The length of the input buffer.
 * @param   instructionPointer  The instruction-pointer.
 * @param   instruction         A pointer to the @c ZydisDecodedInstruction struct, that receives 
 *                              the details about the decoded instruction.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderDecodeBuffer(const ZydisDecoder* decoder, 
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, 
    ZydisDecodedInstruction* instruction);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_DECODER_H */
