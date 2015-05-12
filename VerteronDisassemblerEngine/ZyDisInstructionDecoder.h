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

#ifndef _VDE_ZyDisINSTRUCTIONDECODERC_H_
#define _VDE_ZyDisINSTRUCTIONDECODERC_H_

#include "ZyDisDisassemblerTypes.h"
#include "ZyDisDisassemblerUtils.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ZyDisBaseDataSource ============================================================================ */

typedef struct _ZyDisBaseDataSourceContext { ZyDisContextDescriptor d; } ZyDisBaseDataSourceContext;

typedef void(*ZyDisBaseDataSource_DestructionCallback)(ZyDisBaseDataSourceContext *ctx);
typedef uint8_t(*ZyDisBaseDataSource_InputCallback)(ZyDisBaseDataSourceContext *ctx);
typedef bool(*ZyDisBaseDataSource_IsEndOfInputCallback)(const ZyDisBaseDataSourceContext *ctx);
typedef uint64_t(*ZyDisBaseDataSource_GetPositionCallback)(const ZyDisBaseDataSourceContext *ctx);
typedef bool(*ZyDisBaseDataSource_SetPositionCallback)(
    ZyDisBaseDataSourceContext *ctx, uint64_t position);

/**
 * @brief Releases a data source. 
 * @param ctx The context to release.
 * The context may no longer be used after it was released.
 */
ZYDIS_EXPORT void ZyDisBaseDataSource_Release(
    ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Reads the next byte from the data source without altering the current input position 
 *          or the @c length field of the @c info parameter. 
 * @param   ctx  The data source context.
 * @param   info The instruction info struct.
 * @return  The current input byte. If the result is zero, you should always check the @c flags 
 *          field of the @c info parameter for error flags. Possible error values are 
 *          @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
 */
ZYDIS_EXPORT uint8_t ZyDisBaseDataSource_InputPeek(
    ZyDisBaseDataSourceContext *ctx, 
    ZyDisInstructionInfo *info);

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
ZYDIS_EXPORT uint8_t ZyDisBaseDataSource_InputNext8(
    ZyDisBaseDataSourceContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @copydoc ZyDisBaseDataSource_InputNext8
 */
ZYDIS_EXPORT uint16_t ZyDisBaseDataSource_InputNext16(
    ZyDisBaseDataSourceContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @copydoc ZyDisBaseDataSource_InputNext8
 */
ZYDIS_EXPORT uint32_t ZyDisBaseDataSource_InputNext32(
    ZyDisBaseDataSourceContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @copydoc ZyDisBaseDataSource_InputNext8
 */
ZYDIS_EXPORT uint64_t ZyDisBaseDataSource_InputNext64(
    ZyDisBaseDataSourceContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Returns the current input byte.
 * @param   ctx  The data soruce context.
 * @return  The current input byte.
 * The current input byte is set everytime the @c inputPeek or @c inputNext method is called.
 */
// TODO: check long descr
ZYDIS_EXPORT uint8_t ZyDisBaseDataSource_InputCurrent(
    const ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Queries if the end of the data source is reached.
 * @param   ctx  The data soruce context.
 * @return  @c true if end of input, @c false if not.
 */
ZYDIS_EXPORT bool ZyDisBaseDataSource_IsEndOfInput(
    const ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Returns the current input position.
 * @param   ctx  The data soruce context.
 * @return  The current input position.
 */
ZYDIS_EXPORT uint64_t ZyDisBaseDataSource_GetPosition(
    const ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Sets a new input position.
 * @param   ctx  The data soruce context.
 * @param   position    The new input position.
 * @return  @c false if the new position exceeds the maximum input length.
 */
ZYDIS_EXPORT bool ZyDisBaseDataSource_SetPosition(
    ZyDisBaseDataSourceContext *ctx, 
    uint64_t position);

/* ZyDisMemoryDataSource ========================================================================== */

/**
 * @brief   Creates a memory data source.
 * @param   buffer      The input buffer.
 * @param   bufferLen   THe length of the input buffer.
 * @return  @c NULL if it fails, else a data source context.
 * @see     ZyDisBaseDataSource_Release
 */
ZYDIS_EXPORT ZyDisBaseDataSourceContext* ZyDisMemoryDataSource_Create(
    const void* buffer,
    size_t bufferLen);

/* ZyDisCustomDataSource ========================================================================== */

/**
 * @brief   Creates a custom daat source.
 * @param   ctx             The context.
 * @param   inputPeekCb     The callback peeking the next input byte.
 * @param   inputNextCb     The callback consuming the next input byte.
 * @param   isEndOfInputCb  The callback determining if the end of input was reached.
 * @param   getPositionCb   The callback obtaining the current input position.
 * @param   setPositionCb   The callback setting the current input position.
 * @param   destructionCb   The destruction callback. May be @c NULL.
 * @return  @c NULL if it fails, else a data source context.
 * @see     ZyDisBaseDataSource_Release
 */
ZYDIS_EXPORT ZyDisBaseDataSourceContext* ZyDisCustomDataSource_Create(
    ZyDisBaseDataSource_InputCallback inputPeekCb,
    ZyDisBaseDataSource_InputCallback inputNextCb,
    ZyDisBaseDataSource_IsEndOfInputCallback isEndOfInputCb,
    ZyDisBaseDataSource_GetPositionCallback getPositionCb,
    ZyDisBaseDataSource_SetPositionCallback setPositionCb,
    ZyDisBaseDataSource_DestructionCallback destructionCb);

/* Enums ======================================================================================= */

/**
 * @brief   Values that represent a disassembler mode.
 */
typedef enum _ZyDisDisassemblerMode /* : uint8_t */
{
    DM_M16BIT,
    DM_M32BIT,
    DM_M64BIT
} ZyDisDisassemblerMode;

/**
 * @brief   Values that represent an instruction-set vendor.
 */
typedef enum _ZyDisInstructionSetVendor /* : uint8_t */
{
    ISV_ANY,
    ISV_INTEL,
    ISV_AMD
} ZyDisInstructionSetVendor;

/* ZyDisInstructionDecoder ======================================================================== */

typedef struct _ZyDisInstructionDecoderContext 
{ 
    ZyDisContextDescriptor d; 
} ZyDisInstructionDecoderContext;

/**
 * @brief   Creates an instruction decoder.
 * @return  @c NULL if it fails, else an instruction decoder context.
 * @see     ZyDisInstructionDecoder_Release
 */
// TODO: verify return value
ZYDIS_EXPORT ZyDisInstructionDecoderContext* ZyDisInstructionDecoder_Create(void);

/**
 * @brief   Creates an instruction decoder.
 * @param   input               A reference to the input data source.
 * @param   disassemblerMode    The disassembler mode.
 * @param   preferredVendor     The preferred instruction-set vendor.
 * @param   instructionPointer  The initial instruction pointer.
 * @return  @c NULL if it fails, else an instruction decoder context.
 * @see     ZyDisInstructionDecoder_Release
 */
ZYDIS_EXPORT ZyDisInstructionDecoderContext* ZyDisInstructionDecoder_CreateEx(
    ZyDisBaseDataSourceContext *input, 
    ZyDisDisassemblerMode disassemblerMode,
    ZyDisInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer);

/**
 * @brief   Releases an instruction decoder.
 * @param   ctx The context of the instruction decoder to release.
 */
ZYDIS_EXPORT void ZyDisInstructionDecoder_Release(
    ZyDisInstructionDecoderContext *ctx);

/**
 * @brief   Decodes the next instruction from the input data source.
 * @param   ctx  The instruction decoder context.
 * @param   info The @c ZyDisInstructionInfo struct that receives the information about the decoded 
 *               instruction.
 * @return  This function returns @c false if the current position exceeds the maximum input
 *          length. In all other cases (valid and invalid instructions) the return value is 
 *          @c true.
 */
ZYDIS_EXPORT bool ZyDisInstructionDecoder_DecodeInstruction(
    ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Returns a pointer to the current data source.
 * @param   ctx The instruction decoder context.
 * @return  The context of the data source.
 */
ZYDIS_EXPORT ZyDisBaseDataSourceContext* ZyDisInstructionDecoder_GetDataSource(
    const ZyDisInstructionDecoderContext *ctx);

/**
 * @brief   Sets a new data source.
 * @param   ctx   The instruction decoder context.
 * @param   input The context of the new input data source.
 */
ZYDIS_EXPORT void ZyDisInstructionDecoder_SetDataSource(
    ZyDisInstructionDecoderContext *ctx, 
    ZyDisBaseDataSourceContext *input);

/**
 * @brief   Returns the current disassembler mode.
 * @param   ctx The instruction decoder context.
 * @return  The current disassembler mode.
 */
ZYDIS_EXPORT ZyDisDisassemblerMode ZyDisInstructionDecoder_GetDisassemblerMode(
    const ZyDisInstructionDecoderContext *ctx);

/**
 * @brief   Sets the current disassembler mode.
 * @param   ctx                 The instruction decoder context.
 * @param   disassemblerMode    The new disassembler mode.
 */
ZYDIS_EXPORT void ZyDisInstructionDecoder_SetDisassemblerMode(
    ZyDisInstructionDecoderContext *ctx,
    ZyDisDisassemblerMode disassemblerMode);

/**
 * @brief   Returns the preferred instruction-set vendor.
 * @param   ctx The instruction decoder context.
 * @return  The preferred instruction-set vendor.
 */
ZYDIS_EXPORT ZyDisInstructionSetVendor ZyDisInstructionDecoder_GetPreferredVendor(
    const ZyDisInstructionDecoderContext *ctx);

/**
 * @brief   Sets the preferred instruction-set vendor.
 * @param   ctx             The instruction decoder context.
 * @param   preferredVendor The new preferred instruction-set vendor.
 */
ZYDIS_EXPORT void ZyDisInstructionDecoder_SetPreferredVendor(
    ZyDisInstructionDecoderContext *ctx,
    ZyDisInstructionSetVendor preferredVendor);

/**
 * @brief   Returns the current instruction pointer.
 * @param   ctx The instruction decoder context.
 * @return  The current instruction pointer.
 */
ZYDIS_EXPORT uint64_t ZyDisInstructionDecoder_GetInstructionPointer(
    const ZyDisInstructionDecoderContext *ctx);

/**
 * @brief   Sets a new instruction pointer.
 * @param   ctx                 The instruction decoder context.
 * @param   instructionPointer  The new instruction pointer.
 */
ZYDIS_EXPORT void ZyDisInstructionDecoder_SetInstructionPointer(
    ZyDisInstructionDecoderContext *ctx,
    uint64_t instructionPointer);

/* ============================================================================================= */

#ifdef __cplusplus
}
#endif

#endif /* _VDE_ZyDisINSTRUCTIONDECODERC_H_ */
