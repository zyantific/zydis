/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Joel Höner

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
 * @brief   Functions for (re-)encoding instructions.
 */

#ifndef ZYDIS_ENCODER_H
#define ZYDIS_ENCODER_H

#include <Zydis/Defines.h>
#include <Zydis/Status.h>
#include <Zydis/Register.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/SharedTypes.h>
#ifdef ZYDIS_ENABLE_FEATURE_DECODER
#   include <Zydis/DecoderTypes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Constants                                                                                      */
/* ============================================================================================== */

/**
 * @brief  Defines a mask of attributes users may excplicitly ask for.
 */
#define ZYDIS_USER_ENCODABLE_ATTRIB_MASK (    \
    ZYDIS_ATTRIB_HAS_LOCK                   | \
    ZYDIS_ATTRIB_HAS_REP                    | \
    ZYDIS_ATTRIB_HAS_REPE                   | \
    ZYDIS_ATTRIB_HAS_REPNE                  | \
    ZYDIS_ATTRIB_HAS_BOUND                  | \
    ZYDIS_ATTRIB_HAS_XACQUIRE               | \
    ZYDIS_ATTRIB_HAS_XRELEASE               | \
    ZYDIS_ATTRIB_HAS_BRANCH_TAKEN           | \
    ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN         \
)

/* ============================================================================================== */
/* Structs                                                                                        */
/* ============================================================================================== */

#define ZYDIS_ENCODER_MAX_OPERANDS (5)

typedef struct ZydisEncoderOperand_
{
    ZydisOperandType type;
    ZydisRegister reg;
    struct
    {
        ZydisRegister segment;
        ZydisRegister base;
        ZydisRegister index;
        uint8_t scale;
        uint8_t dispSize;
        int64_t disp;
    } mem;
    struct
    {
        uint16_t segment;
        uint32_t offset;
    } ptr;
    union
    {
        uint64_t u;
        int64_t s;
    } imm;
} ZydisEncoderOperand;

typedef struct ZydisEncoderRequest_
{
    ZydisMachineMode machineMode;
    ZydisMnemonic mnemonic;
    ZydisInstructionAttributes attributes;
    ZydisInstructionEncoding encoding;
    uint8_t operandCount;
    ZydisEncoderOperand operands[ZYDIS_ENCODER_MAX_OPERANDS];

    struct
    {
        ZydisVectorLength vectorLength;
        struct
        {
            ZydisMaskMode mode;
            ZydisRegister reg;
        } mask;
    } avx;
    // TODO: mvex stuff
} ZydisEncoderRequest;

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

#ifdef ZYDIS_ENABLE_FEATURE_DECODER
ZYDIS_EXPORT ZydisStatus ZydisEncoderDecodedInstructionToRequest(
    const ZydisDecodedInstruction* in, ZydisEncoderRequest* out);
#endif

/**
 * @brief   Encodes the given instruction request to byte-code.
 *
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 * @param   request     A pointer to the @c ZydisEncoderRequest encode.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisEncoderEncodeInstruction(void* buffer, size_t* bufferLen, 
    const ZydisEncoderRequest* request);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_ENCODER_H */
