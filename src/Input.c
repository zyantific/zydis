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

#include <assert.h>
#include <Zydis/Status.h>
#include <Zydis/Input.h>

/* ============================================================================================== */
/* Memory input                                                                                   */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internal functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

static bool ZydisMemoryInputNext(ZydisMemoryInput* context, uint8_t* data)
{
    if (context->inputBufferPos >= context->inputBufferLen)
    {
        return false;
    }
    *data = context->inputBuffer[context->inputBufferPos++]; 
    return true; 
}

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisInputInitMemoryInput(ZydisMemoryInput* input, const void* buffer, uint64_t length)
{
    if (!input || !buffer || (length == 0))
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    input->input.inputNext  = (ZydisInputNextFunc)&ZydisMemoryInputNext;
    input->inputBuffer      = (uint8_t*)buffer;
    input->inputBufferLen   = length;
    input->inputBufferPos   = 0;
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* File input                                                                                     */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Internal functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

static bool ZydisFileInputNext(ZydisFileInput* context, uint8_t* data)
{
    int c = fgetc(context->file);
    *data = (uint8_t)c;
    return (c != EOF);
}

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisInputInitFileInput(ZydisFileInput* input, FILE* file)
{
    if (!file)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    input->input.inputNext  = (ZydisInputNextFunc)&ZydisFileInputNext;
    input->file             = file;
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
