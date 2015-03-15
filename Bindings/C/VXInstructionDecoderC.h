/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 14. March 2015

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

#ifndef _VDE_VXINSTRUCTIONDECODERC_H_
#define _VDE_VXINSTRUCTIONDECODERC_H_

#include "VXDisassemblerTypesC.h"
#include "VXDisassemblerUtilsC.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* VXBaseDataSource ============================================================================ */

typedef struct _VXBaseDataSourceContext { VXContextDescriptor d; } VXBaseDataSourceContext;

/**
 * @brief Releases a data source. 
 * @param ctx The context to release.
 * The context may no longer be used after it was released.
 */
void VXBaseDataSource_Release(
    VXBaseDataSourceContext *ctx);

/**
 * @brief   Reads the next byte from the data source without altering the current input position 
 *          or the @c length field of the @c info parameter. 
 * @param   ctx  The data source context.
 * @param   info The instruction info struct.
 * @return  The current input byte. If the result is zero, you should always check the @c flags 
 *          field of the @c info parameter for error flags. Possible error values are 
 *          @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
 */
uint8_t VXBaseDataSource_InputPeek(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

/**
  * @brief   Reads the next byte from the data source.
  * @param   ctx  The data soruce context.
  * @param   info The instruction info.
  * @return  The current input byte. If the result is zero, you should always check the 
  *          @c flags field of the @c info parameter for error flags.
  *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.        
  * This method increases the current input position and the @c length field of the @c info 
  * parameter. This function also appends the new byte to to @c data field of the @c info 
  * parameter.
  */
uint8_t VXBaseDataSource_InputNext8(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

/**
 * @copydoc VXBaseDataSource_InputNext8
 */
uint16_t VXBaseDataSource_InputNext16(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

/**
 * @copydoc VXBaseDataSource_InputNext8
 */
uint32_t VXBaseDataSource_InputNext32(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

/**
 * @copydoc VXBaseDataSource_InputNext8
 */
uint64_t VXBaseDataSource_InputNext64(
    VXBaseDataSourceContext *ctx, 
    VXInstructionInfo *info);

/**
 * @brief   Returns the current input byte.
 * @param   ctx  The data soruce context.
 * @return  The current input byte.
 * The current input byte is set everytime the @c inputPeek or @c inputNext method is called.
 */
// TODO: check long descr
uint8_t VXBaseDataSource_InputCurrent(
    const VXBaseDataSourceContext *ctx);

/**
 * @brief   Queries if the end of the data source is reached.
 * @param   ctx  The data soruce context.
 * @return  @c true if end of input, @c false if not.
 */
bool VXBaseDataSource_IsEndOfInput(
    const VXBaseDataSourceContext *ctx);

/**
 * @brief   Returns the current input position.
 * @param   ctx  The data soruce context.
 * @return  The current input position.
 */
uint64_t VXBaseDataSource_GetPosition(
    const VXBaseDataSourceContext *ctx);

/**
 * @brief   Sets a new input position.
 * @param   ctx  The data soruce context.
 * @param   position    The new input position.
 * @return  @c false if the new position exceeds the maximum input length.
 */
bool VXBaseDataSource_SetPosition(
    VXBaseDataSourceContext *ctx, 
    uint64_t position);

/* VXMemoryDataSource ========================================================================== */

/**
 * @brief   Creates a memory data source.
 * @param   buffer      The input buffer.
 * @param   bufferLen   THe length of the input buffer.
 * @return  @c NULL if it fails, else a data source context.
 * @see     VXBaseDataSource_Release
 */
// TODO: verify return value
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

typedef struct _VXInstructionDecoderContext 
{ 
    VXContextDescriptor d; 
} VXInstructionDecoderContext;

/**
 * @brief   Creates an instruction decoder.
 * @return  @c NULL if it fails, else an instruction decoder context.
 * @see     VXInstructionDecoder_Release
 */
// TODO: verify return value
VXInstructionDecoderContext* VXInstructionDecoder_Create(void);

/**
 * @brief   Creates an instruction decoder.
 * @param   input               A reference to the input data source.
 * @param   disassemblerMode    The disassembler mode.
 * @param   preferredVendor     The preferred instruction-set vendor.
 * @param   instructionPointer  The initial instruction pointer.
 * @return  @c NULL if it fails, else an instruction decoder context.
 * @see     VXInstructionDecoder_Release
 */
VXInstructionDecoderContext* VXInstructionDecoder_CreateEx(
    VXBaseDataSourceContext *input, 
    VXDisassemblerMode disassemblerMode,
    VXInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer);

/**
 * @brief   Releases an instruction decoder.
 * @param   ctx The context of the instruction decoder to release.
 */
void VXInstructionDecoder_Release(
    VXInstructionDecoderContext *ctx);

/**
 * @brief   Decodes the next instruction from the input data source.
 * @param   ctx  The instruction decoder context.
 * @param   info The @c VXInstructionInfo struct that receives the information about the decoded 
 *               instruction.
 * @return  This function returns @c false if the current position exceeds the maximum input
 *          length. In all other cases (valid and invalid instructions) the return value is 
 *          @c true.
 */
bool VXInstructionDecoder_DecodeInstruction(
    VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info);

/**
 * @brief   Returns a pointer to the current data source.
 * @param   ctx The instruction decoder context.
 * @return  The context of the data source.
 */
VXBaseDataSourceContext* VXInstructionDecoder_GetDataSource(
    const VXInstructionDecoderContext *ctx);

/**
 * @brief   Sets a new data source.
 * @param   ctx   The instruction decoder context.
 * @param   input The context of the new input data source.
 */
void VXInstructionDecoder_SetDataSource(
    VXInstructionDecoderContext *ctx, 
    VXBaseDataSourceContext *input);

/**
 * @brief   Returns the current disassembler mode.
 * @param   ctx The instruction decoder context.
 * @return  The current disassembler mode.
 */
VXDisassemblerMode VXInstructionDecoder_GetDisassemblerMode(
    const VXInstructionDecoderContext *ctx);

/**
 * @brief   Sets the current disassembler mode.
 * @param   ctx                 The instruction decoder context.
 * @param   disassemblerMode    The new disassembler mode.
 */
void VXInstructionDecoder_SetDisassemblerMode(
    VXInstructionDecoderContext *ctx,
    VXDisassemblerMode disassemblerMode);

/**
 * @brief   Returns the preferred instruction-set vendor.
 * @param   ctx The instruction decoder context.
 * @return  The preferred instruction-set vendor.
 */
VXInstructionSetVendor VXInstructionDecoder_GetPreferredVendor(
    const VXInstructionDecoderContext *ctx);

/**
 * @brief   Sets the preferred instruction-set vendor.
 * @param   ctx             The instruction decoder context.
 * @param   preferredVendor The new preferred instruction-set vendor.
 */
void VXInstructionDecoder_SetPreferredVendor(
    VXInstructionDecoderContext *ctx,
    VXInstructionSetVendor preferredVendor);

/**
 * @brief   Returns the current instruction pointer.
 * @param   ctx The instruction decoder context.
 * @return  The current instruction pointer.
 */
uint64_t VXInstructionDecoder_GetInstructionPointer(
    const VXInstructionDecoderContext *ctx);

/**
 * @brief   Sets a new instruction pointer.
 * @param   ctx                 The instruction decoder context.
 * @param   instructionPointer  The new instruction pointer.
 */
void VXInstructionDecoder_SetInstructionPointer(
    VXInstructionDecoderContext *ctx,
    uint64_t instructionPointer);

/* ============================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _VDE_VXINSTRUCTIONDECODERC_H_ */
