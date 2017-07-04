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

#ifndef ZYDIS_DECODER_H
#define ZYDIS_DECODER_H

#include <Zydis/Defines.h>
#include <Zydis/Types.h>
#include <Zydis/Status.h>
#include <Zydis/DecoderTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/**
 * @brief   Defines the @c ZydisDecodeGranularity datatype.
 */
typedef uint32_t ZydisDecodeGranularity;

/**
 * @brief   Decoder modes defining how granular the instruction should be decoded.
 */
enum ZydisDecodeGranularities
{
    /**
     * @brief   Defaults to `ZYDIS_DECODE_GRANULARITY_FULL`. 
     */
    ZYDIS_DECODE_GRANULARITY_DEFAULT,
    /**
     * @brief   Minimal instruction decoding without semantic analysis.
     * 
     * This mode provides access to the mnemonic, the instruction-length, the effective 
     * operand-size, the effective address-width, some attributes (e.g. `ZYDIS_ATTRIB_IS_RELATIVE`) 
     * and all of the information in the `raw` field of the `ZydisDecodedInstruction` struct.
     * 
     * Operands, most attributes and other specific information (like AVX info) are not 
     * accessible in this mode.
     */
    ZYDIS_DECODE_GRANULARITY_MINIMAL,
    /**
     * @brief   Full physical and semantic instruction-decoding.
     */
    ZYDIS_DECODE_GRANULARITY_FULL
};

/**
 * @brief   Defines the @c ZydisDecoder datatype.
 */
typedef struct ZydisDecoder_
{
    ZydisMachineMode machineMode;
    ZydisAddressWidth addressWidth;
    ZydisDecodeGranularity decodeGranularity;
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
 * @param   decoder             A pointer to the @c ZydisDecoder instance.
 * @param   machineMode         The machine mode.
 * @param   addressWidth        The address width.
 * @param   decodeGranularity   The decode granularity.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderInitEx(ZydisDecoder* decoder, ZydisMachineMode machineMode, 
    ZydisAddressWidth addressWidth, ZydisDecodeGranularity decodeGranularity);

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
