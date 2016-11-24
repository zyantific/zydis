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

#ifndef ZYDIS_STATUS_H
#define ZYDIS_STATUS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/**
 * @brief   Defines the @c ZydisStatus datatype.
 */
typedef uint32_t ZydisStatus;

/**
 * @brief   Values that represent a zydis status-codes.
 */
enum ZydisStatusCode
{
    /**
     * @brief   The operation completed successfully.
     */
    ZYDIS_STATUS_SUCCESS                    = 0x00000000,
    /**
     * @brief   An invalid parameter was passed to a function.
     */
    ZYDIS_STATUS_INVALID_PARAMETER          = 0x00000001,
    /**
     * @brief   An attempt was made to perform an invalid operation.
     */
    ZYDIS_STATUS_INVALID_OPERATION          = 0x00000002,
    /**
     * @brief   An attempt was made to read data from an input data-source that has no more data 
     *          available.
     */
    ZYDIS_STATUS_NO_MORE_DATA               = 0x00000003,
    /**
     * @brief   An error occured while decoding the current instruction. Check the @c instrFlags 
     *          field of the @c ZydisInstructionInfo struct for further details.
     */
    ZYDIS_STATUS_DECODING_ERROR             = 0x00000004, 
    /**
     * @brief   A buffer passed to a function was too small to complete the requested operation.
     */
    ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE   = 0x00000005,
    /**
     * @brief   The base value for user-defined status codes.
     */
    ZYDIS_STATUS_USER                       = 0x10000000
};

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/**
 * @brief   Checks a zydis status code for success.
 *
 * @param   status  The status code.
 */
#define ZYDIS_SUCCESS(status) (status == ZYDIS_STATUS_SUCCESS)

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_STATUS_H */
