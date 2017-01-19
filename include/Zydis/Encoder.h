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

#ifndef ZYDIS_ENCODER_H
#define ZYDIS_ENCODER_H

#include <Zydis/Defines.h>
#include <Zydis/Types.h>
#include <Zydis/Status.h>
#include <Zydis/InstructionInfo.h>

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
    ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN       | \
    ZYDIS_ATTRIB_HAS_SEGMENT_CS             | \
    ZYDIS_ATTRIB_HAS_SEGMENT_DS             | \
    ZYDIS_ATTRIB_HAS_SEGMENT_SS             | \
    ZYDIS_ATTRIB_HAS_SEGMENT_ES             | \
    ZYDIS_ATTRIB_HAS_SEGMENT_FS             | \
    ZYDIS_ATTRIB_HAS_SEGMENT_GS               \
)

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Encodes the given instruction info to byte-code.
 *
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 * @param   info        A pointer to the @c ZydisInstructionInfo struct to be encoded.
 *
 * @return  A zydis status code. 
 */
ZYDIS_EXPORT ZydisStatus ZydisEncoderEncodeInstruction(void* buffer, size_t* bufferLen, 
    ZydisInstructionInfo* info);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_ENCODER_H */
