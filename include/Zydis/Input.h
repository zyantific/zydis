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

#ifndef ZYDIS_INPUT_H
#define ZYDIS_INPUT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <Zydis/Defines.h>
#include <Zydis/Status.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Custom input                                                                                   */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInputNextFunc function pointer used in the @c ZydisCustomInput
 *          struct.
 *          
 * This function should return the byte at the current input-position and increase the position
 * by one. If the input data-source has no more data available, return @c FALSE. 
 */
typedef bool (*ZydisInputNextFunc)(void* context, uint8_t* data);

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis custom input struct.
 */
typedef struct ZydisCustomInput_
{
    /**
     * @brief   The @c ZydisInputNextFunc callback.
     */
    ZydisInputNextFunc  inputNext;
} ZydisCustomInput;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Memory input                                                                                   */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis memory input struct.
 */
typedef struct ZydisMemoryInput_
{
    /**
     * @brief   The @c ZydisCustomInput base struct. 
     *          
     * This has to be the first element in every custom input data-source struct to ensure we
     * can safely downcast it.
     */
    ZydisCustomInput input;
    /**
     * @brief   A pointer to the mem buffer. 
     */
    const uint8_t* inputBuffer;
    /**
     * @brief   The length of the mem buffer. 
     */
    uint64_t inputBufferLen;
    /**
     * @brief   The current input position.
     */
    uint64_t inputBufferPos;
} ZydisMemoryInput;

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Initializes the given @c ZydisMemoryInput instance.
 *
 * @param   input   A pointer to the input data-source instance.
 * @param   buffer  The mem buffer to use.
 * @param   length  The length of the mem buffer.
 *                  
 * @return  A zydis status code.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisInputInitMemoryInput(ZydisMemoryInput* input, const void* buffer, 
    uint64_t length);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* File input                                                                                     */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
* @brief   Defines the zydis file input struct.
*/
typedef struct ZydisFileInput_
{
    /**
     * @brief   The @c ZydisCustomInput base struct.
     *
     * This has to be the first element in every custom input data-source struct to ensure we can
     * safely downcast it.
     */
    ZydisCustomInput input;
    /**
     * @brief   The input file.
     */
    FILE* file;
} ZydisFileInput;

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief Initializes the given @c ZydisFileInput instance.
 *
 * @param   input   A pointer to the input data-source instance.
 * @param   file    The file to use. You may freely `fseek` around after creation of the source.
 *
 * @return  A zydis status code.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisInputInitFileInput(ZydisFileInput* input, FILE* file);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INPUT_H */
