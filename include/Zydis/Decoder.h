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
 * @brief   Defines the @c ZydisDecoderFlags datatype.
 */
typedef uint32_t ZydisDecoderFlags;

// TODO: Add flags to enable/disable certain decoding-steps like operands, affected flags, ..

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionDecoder struct.
 */
typedef struct ZydisInstructionDecoder_
{
    /**
     * @brief   The current disassembler-mode.
     */
    ZydisDisassemblerMode disassemblerMode;
    // TODO: Remove from this struct and pass as argument
    /**
     * @brief   The current input buffer.
     */
    struct
    {
        const uint8_t* buffer;
        size_t bufferLen;
    } input;
    /**
     * @brief   Internal field. @c TRUE, if the @c imm8 value is already initialized.
     */
    ZydisBool imm8initialized;
    /**
     * @brief   Internal field. We have to store a copy of the imm8 value for instructions that 
     *          encode different operands in the lo and hi part of the immediate.
     */
    uint8_t imm8;

    /**
     * @brief   Internal field. The 0x66 prefix can be consumed, if it is used as mandatory-prefix.
     *          This field contains the prefix-byte, if the prefix is present and not already
     *          consumed.
     */
    uint8_t hasUnusedPrefix66;
    /**
     * @brief   Internal field. The mutally exclusive 0xF2 and 0xF3 prefixs can be consumed, if 
     *          they are used as mandatory-prefix. This field contains the prefix-byte of the 
     *          latest 0xF2 or 0xF3 prefix, if one of the prefixes is present and not already 
     *          consumed.
     */
    uint8_t hasUnusedPrefixF2F3;
    /**
     * @brief   Internal field. Contains the latest (significant) segment prefix.
     */
    uint8_t lastSegmentPrefix;
} ZydisInstructionDecoder;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Initializes the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   disassemblerMode    The desired disassembler-mode.
 *                  
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderInitInstructionDecoder(ZydisInstructionDecoder* decoder,
    ZydisDisassemblerMode disassemblerMode);

/**
 * @brief   Decodes the instruction in the given input @c buffer.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   buffer              A pointer to the input buffer.
 * @param   bufferLen           The length of the input buffer.
 * @param   instructionPointer  The instruction-pointer.
 * @param   info                A pointer to the @c ZydisInstructionInfo struct, that receives the 
 *                              details about the decoded instruction.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderDecodeInstruction(ZydisInstructionDecoder* decoder,
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, ZydisInstructionInfo* info);

/**
 * @brief   Decodes the instruction in the given input @c buffer.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   buffer              A pointer to the input buffer.
 * @param   bufferLen           The length of the input buffer.
 * @param   instructionPointer  The instruction-pointer.
 * @param   flags               Additional decoding flags.
 * @param   info                A pointer to the @c ZydisInstructionInfo struct, that receives the 
 *                              details about the decoded instruction.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderDecodeInstructionEx(ZydisInstructionDecoder* decoder,
    const void* buffer, size_t bufferLen, uint64_t instructionPointer, ZydisDecoderFlags flags, 
    ZydisInstructionInfo* info);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_DECODER_H */
