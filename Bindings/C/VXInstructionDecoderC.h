/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 04. February 2015

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

**************************************************************************************************/

/* NOTE: fully ported to C  */

#ifndef _VDE_VXINSTRUCTIONDECODERC_H_
#define _VDE_VXINSTRUCTIONDECODERC_H_

#include "VXDisassemblerTypesC.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* VXBaseDataSource ============================================================================ */

typedef struct _VXBaseDataSourceContext { int a; } VXBaseDataSourceContext;

void VXBaseDataSource_Release(
    VXBaseDataSourceContext *ctx);

uint8_t VXBaseDataSource_InputPeek(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

uint8_t VXBaseDataSource_InputNext(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

uint8_t VXBaseDataSource_InputCurrent(
    const VXBaseDataSourceContext *ctx);

bool VXBaseDataSource_IsEndOfInput(
    const VXBaseDataSourceContext *ctx);

uint64_t VXBaseDataSource_GetPosition(
    const VXBaseDataSourceContext *ctx);

bool VXBaseDataSource_SetPosition(
    VXBaseDataSourceContext *ctx, 
    uint64_t position);

/* VXMemoryDataSource ========================================================================== */

VXBaseDataSourceContext* VXMemoryDataSource_Create(
    const void* buffer,
    size_t bufferLen);

/* Enums ======================================================================================= */

/**
 * @brief   Values that represent a disassembler mode.
 */
typedef enum _VXDisassemblerMode /* : uint8_t */
{
    DM_M16BIT,
    DM_M32BIT,
    DM_M64BIT
} VXDisassemblerMode;

/**
 * @brief   Values that represent an instruction-set vendor.
 */
typedef enum _VXInstructionSetVendor /* : uint8_t */
{
    ISV_ANY,
    ISV_INTEL,
    ISV_AMD
} VXInstructionSetVendor;

/* VXInstructionDecoder ======================================================================== */

typedef struct _VXInstructionDecoderContext { int a; } VXInstructionDecoderContext;

VXInstructionDecoderContext* VXInstructionDecoder_Create(void);

VXInstructionDecoderContext* VXInstructionDecoder_CreateEx(
    VXBaseDataSourceContext *input, 
    VXDisassemblerMode disassemblerMode = DM_M32BIT,
    VXInstructionSetVendor preferredVendor = ISV_ANY, 
    uint64_t instructionPointer = 0);

void VXInstructionDecoder_Release(
    VXInstructionDecoderContext *ctx);

bool VXInstructionDecoder_DecodeInstruction(
    VXInstructionDecoderContext *ctx, VXInstructionInfo *info);

VXBaseDataSourceContext* VXInstructionDecoder_GetDataSource(
    const VXInstructionDecoderContext *ctx);

void VXInstructionDecoder_SetDataSource(
    VXInstructionDecoderContext *ctx, 
    VXBaseDataSourceContext *input);

VXDisassemblerMode VXInstructionDecoder_GetDisassemblerMode(
    VXInstructionDecoderContext *ctx);

void VXInstructionDecoder_SetDisassemblerMode(
    VXInstructionDecoderContext *ctx,
    VXDisassemblerMode disassemblerMode);

VXInstructionSetVendor VXInstructionDecoder_GetPreferredVendor(
    const VXInstructionDecoderContext *ctx);

void VXInstructionDecoder_SetPreferredVendor(
    VXInstructionDecoderContext *ctx,
    VXInstructionSetVendor preferredVendor);

uint64_t VXInstructionDecoder_GetInstructionPointer(
    VXInstructionDecoderContext *ctx);

void VXInstructionDecoder_SetInstructionPointer(
    VXInstructionDecoderContext *ctx,
    uint64_t instructionPointer);

/* ============================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _VDE_VXINSTRUCTIONDECODERC_H_ */
