/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

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

#include <stdint.h>
#include <Zydis/Defines.h>
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
 * @brief   Values that represent zydis decoder-flags.
 */
enum ZydisDecoderFlag
{
    ZYDIS_DECODER_FLAG_SKIP_DATA = 0x00000001    
};

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
 * @brief   Returns the current disassembler-mode of the given @c ZydisInstructionDecoder
 *          instance.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   disassemblerMode    A pointer to the memory that receives the current disassembler-mode. 
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderGetDisassemblerMode(const ZydisInstructionDecoder* decoder, 
    ZydisDisassemblerMode* disassemblerMode);

/**
 * @brief   Changes the disassembler-mode of the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder             A pointer to the @c ZydisInstructionDecoder instance.
 * @param   disassemblerMode    The new disassembler-mode.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderSetDisassemblerMode(ZydisInstructionDecoder* decoder, 
    ZydisDisassemblerMode disassemblerMode);

/**
 * @brief   Returns the current input data-source of the given @c ZydisInstructionDecoder
 *          instance.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   input   A pointer to the memory that receives the current input data-source pointer.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderGetDecoderInput(const ZydisInstructionDecoder* decoder,
    ZydisCustomInput** input);

/**
 * @brief   Changes the input data-source of the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   input   A pointer to the new input data-source.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderSetDecoderInput(ZydisInstructionDecoder* decoder,
    ZydisCustomInput* input);

/**
 * @brief   Returns the current decoder-flags of the given @c ZydisInstructionDecoder instance.
 *          
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   flags   A pointer to the memory that receives the current decoder-flags.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderGetDecoderFlags(const ZydisInstructionDecoder* decoder,
    ZydisDecoderFlags* flags);

/**
 * @brief   Changes the decoder-flags of the given @c ZydisInstructionDecoder instance.
 *
 * @param   decoder A pointer to the @c ZydisInstructionDecoder instance.
 * @param   flags   The new decoder-flags.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisDecoderSetDecoderFlags(ZydisInstructionDecoder* decoder, 
    ZydisDecoderFlags flags);

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
