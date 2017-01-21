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

#ifndef ZYDIS_STATUS_H
#define ZYDIS_STATUS_H

#include <Zydis/Types.h>

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
    /* ------------------------------------------------------------------------------------------ */
    /* General                                                                                    */
    /* ------------------------------------------------------------------------------------------ */

    /**
     * @brief   The operation completed successfully.
     */
    ZYDIS_STATUS_SUCCESS                                                            = 0x00000000,
    /**
     * @brief   An invalid parameter was passed to a function.
     */
    ZYDIS_STATUS_INVALID_PARAMETER,
    /**
     * @brief   An attempt was made to perform an invalid operation.
     */
    ZYDIS_STATUS_INVALID_OPERATION,

    /* ------------------------------------------------------------------------------------------ */
    /* Decoder                                                                                    */
    /* ------------------------------------------------------------------------------------------ */

    /**
     * @brief   An attempt was made to read data from an input data-source that has no more data 
     *          available.
     */
    ZYDIS_STATUS_NO_MORE_DATA,
    /**
     * @brief   An general error occured while decoding the current instruction. The instruction
     *          might be undefined.
     */
    ZYDIS_STATUS_DECODING_ERROR, 
    /**
     * @brief   The instruction exceeded the maximum length of 15 bytes.
     */
    ZYDIS_STATUS_INSTRUCTION_TOO_LONG,
    /**
     * @brief   The instruction encoded an invalid register.
     */
    ZYDIS_STATUS_BAD_REGISTER,
    /**
     * @brief   A lock-prefix (F0) was found while decoding an instruction that does not support
     *          locking. 
     */
    ZYDIS_STATUS_ILLEGAL_LOCK,
    /**
     * @brief   A legacy-prefix (F2, F3, 66) was found while decoding a XOP/VEX/EVEX instruction. 
     */
    ZYDIS_STATUS_ILLEGAL_LEGACY_PFX,
    /**
     * @brief   A rex-prefix was found while decoding a XOP/VEX/EVEX instruction. 
     */
    ZYDIS_STATUS_ILLEGAL_REX,
    /**
     * @brief   An invalid opcode-map value was found while decoding a XOP/VEX/EVEX-prefix.  
     */
    ZYDIS_STATUS_INVALID_MAP,
    /**
     * @brief   An error occured while decoding the EVEX-prefix.  
     */
    ZYDIS_STATUS_MALFORMED_EVEX,
    // TODO:
    ZYDIS_STATUS_INVALID_MASK,
    ZYDIS_STATUS_INVALID_VSIB,

    /* ------------------------------------------------------------------------------------------ */
    /* Encoder                                                                                    */
    /* ------------------------------------------------------------------------------------------ */

    // TODO:
    ZYDIS_STATUS_IMPOSSIBLE_INSTRUCTION,

    /* ------------------------------------------------------------------------------------------ */
    /* Formatter                                                                                  */
    /* ------------------------------------------------------------------------------------------ */

    /**
     * @brief   A buffer passed to a function was too small to complete the requested operation.
     */
    ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE,

    /* ------------------------------------------------------------------------------------------ */
    /* Misc                                                                                       */
    /* ------------------------------------------------------------------------------------------ */

    /**
     * @brief   The base value for user-defined status codes.
     */
    ZYDIS_STATUS_USER                                                               = 0x10000000
};

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/**
 * @brief   Checks if a zydis operation was successfull.
 *
 * @param   status  The zydis status-code to check.
 */
#define ZYDIS_SUCCESS(status) (status == ZYDIS_STATUS_SUCCESS)

/**
 * @brief   Checks if a zydis operation was successfull and returns the status-code, if not.
 *
 * @param   status  The zydis status-code to check.
 */
#define ZYDIS_CHECK(status) \
    do \
    { \
        ZydisStatus s = status; \
        if (!ZYDIS_SUCCESS(s)) \
        { \
            return s; \
        } \
    } while(0)

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_STATUS_H */
