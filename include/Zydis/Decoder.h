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
#include <Zydis/Input.h>
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

/**
 * @brief   Set this flag if you do not want @c ZydisDecoderDecodeNextInstruction to fail with
 *          @c ZYDIS_STATUS_DECODING_ERROR, if an invalid instruction was found.
 *          
 * If this flag is set, @c ZydisDecoderDecodeNextInstruction just skips one byte and
 * returns @c ZYDIS_STATUS_SUCCESS. The returned @c ZydisInstructionInfo struct will
 * have one of the @c ZYDIS_INSTRFLAG_ERROR_MASK flags set. 
 */
#define ZYDIS_DECODER_FLAG_SKIP_DATA                0x00000001

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
    /**
     * @brief   A pointer to the current input data-source.
     */
    ZydisCustomInput* input;
    /**
     * @brief   Decoder flags.
     */
    ZydisDecoderFlags flags;
    /**
     * @brief   The current instruction-pointer value.
     */
    uint64_t instructionPointer;
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
    /**
     * @brief   Internal buffer.
     */
    struct 
    {
        uint8_t data[30];
        uint8_t count;
        uint8_t posRead;
        uint8_t posWrite;
    } buffer;
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
 * @param   input               A pointer to the input data-source.
 *                  
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderInitInstructionDecoder(ZydisInstructionDecoder* decoder,
    ZydisDisassemblerMode disassemblerMode, ZydisCustomInput* input);

/**
 * @brief   Initializes the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   disassemblerMode    The desired disassembler-mode.
 * @param   input               A pointer to the input data-source.
 * @param   flags               Additional flags for the instruction-decoder.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderInitInstructionDecoderEx(ZydisInstructionDecoder* decoder,
    ZydisDisassemblerMode disassemblerMode, ZydisCustomInput* input, ZydisDecoderFlags flags);

/**
 * @brief   Returns the current input data-source of the given @c ZydisInstructionDecoder
 *          instance.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   input   A pointer to the memory that receives the current input data-source pointer.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderGetInput(const ZydisInstructionDecoder* decoder,
    ZydisCustomInput** input);

/**
 * @brief   Changes the input data-source of the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   input   A pointer to the new input data-source.
 *
 * @return  A zydis status code.
 * 
 * This function flushes the internal input-buffer.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderSetInput(ZydisInstructionDecoder* decoder,
    ZydisCustomInput* input);

/**
 * @brief   Returns the current instruction-pointer of the given @c ZydisInstructionDecoder
 *          instance.
 *          
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   instructionPointer  A pointer to the memory that receives the current 
 *                              instruction-pointer.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderGetInstructionPointer(
    const ZydisInstructionDecoder* decoder, uint64_t* instructionPointer);

/**
 * @brief   Changes the instruction-pointer of the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   instructionPointer  The new instruction-pointer value.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderSetInstructionPointer(ZydisInstructionDecoder* decoder, 
    uint64_t instructionPointer);

/**
 * @brief   Decodes the next instruction from the decoders input data-source.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   info    A pointer to the @c ZydisInstructionInfo struct, that receives the details
 *                  about the decoded instruction.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderDecodeNextInstruction(ZydisInstructionDecoder* decoder,
    ZydisInstructionInfo* info);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_DECODER_H */
