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
#include <Zydis/InstructionInfo.h>

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
 * @brief   Decoders modes defining how granular the instruction should be decoded.
 */
enum ZydisDecodeGranularities
{
    ZYDIS_DECODE_GRANULARITY_DEFAULT,
    ZYDIS_DECODE_GRANULARITY_MINIMAL,
    ZYDIS_DECODE_GRANULARITY_FULL
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Decodes the instruction in the given input @c buffer.
 *
 * @param   operatingMode       The desired operating mode.
 * @param   buffer              A pointer to the input buffer.
 * @param   bufferLen           The length of the input buffer.
 * @param   instructionPointer  The instruction-pointer.
 * @param   info                A pointer to the @c ZydisInstructionInfo struct, that receives the 
 *                              details about the decoded instruction.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisDecode(ZydisOperatingMode operatingMode,
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, ZydisInstructionInfo* info);

/**
 * @brief   Decodes the instruction in the given input @c buffer.
 *
 * @param   operatingMode       The desired operating mode.
 * @param   buffer              A pointer to the input buffer.
 * @param   bufferLen           The length of the input buffer.
 * @param   instructionPointer  The instruction-pointer.
 * @param   granularity         The granularity to decode with.
 * @param   info                A pointer to the @c ZydisInstructionInfo struct, that receives the 
 *                              details about the decoded instruction.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisDecodeEx(ZydisOperatingMode operatingMode,
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, 
    ZydisDecodeGranularity granularity, ZydisInstructionInfo* info);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_DECODER_H */
