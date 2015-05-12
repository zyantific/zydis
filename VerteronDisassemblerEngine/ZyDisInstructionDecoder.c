/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 19. March 2015

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

#include "ZyDisInstructionDecoder.h"
#include "ZyDisInternalHelpers.h"
#include "ZyDisOpcodeTableInternal.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Internal interface ========================================================================== */

/* ZyDisBaseDataSource ---------------------------------------------------------------------------- */

typedef struct _ZyDisBaseDataSource
{
    uint8_t currentInput;
    ZyDisBaseDataSource_DestructionCallback destruct; // may be NULL
    ZyDisBaseDataSource_InputCallback internalInputPeek;
    ZyDisBaseDataSource_InputCallback internalInputNext;
    ZyDisBaseDataSource_IsEndOfInputCallback isEndOfInput;
    ZyDisBaseDataSource_GetPositionCallback getPosition;
    ZyDisBaseDataSource_SetPositionCallback setPosition;
} ZyDisBaseDataSource;

/**
 * @brief   Constructor.
 * @param   ctx The context.
 */
static void ZyDisBaseDataSource_Construct(ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisBaseDataSource_Destruct(ZyDisBaseDataSourceContext *ctx);

/* ZyDisMemoryDataSource -------------------------------------------------------------------------- */

typedef struct _ZyDisMemoryDataSource
{
    ZyDisBaseDataSource super;
    const void *inputBuffer;
    uint64_t inputBufferLen;
    uint64_t inputBufferPos;
} ZyDisMemoryDataSource;

/**
 * @brief   Constructor.
 * @param   ctx         The context.
 * @param   buffer      The buffer.
 * @param   bufferLen   Length of the buffer.
 */
static void ZyDisMemoryDataSource_Construct(ZyDisBaseDataSourceContext *ctx, const void* buffer, 
    size_t bufferLen);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisMemoryDataSource_Destruct(ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Reads the next byte from the data source.
 * @param   ctx The context.
 * @return  The current input byte.
 * This method increases the current input position by one.  
 */
static uint8_t ZyDisMemoryDataSource_InternalInputPeek(ZyDisBaseDataSourceContext *ctx);

/**
 * @brief   Reads the next byte from the data source.
 * @param   ctx The context.
 * @return  The current input byte.
 * This method does NOT increase the current input position.
 */
static uint8_t ZyDisMemoryDataSource_InternalInputNext(ZyDisBaseDataSourceContext *ctx);

/**
 * @copydoc ZyDisBaseDataSource_IsEndOfInput
 */
static bool ZyDisMemoryDataSource_IsEndOfInput(const ZyDisBaseDataSourceContext *ctx);

/**
 * @copydoc ZyDisBaseDataSource_GetPosition
 */
static uint64_t ZyDisMemoryDataSource_GetPosition(const ZyDisBaseDataSourceContext *ctx);

/**
 * @copydoc ZyDisBaseDataSource_SetPosition
 */
static bool ZyDisMemoryDataSource_SetPosition(ZyDisBaseDataSourceContext *ctx, uint64_t position);

/* ZyDisCustomDataSource -------------------------------------------------------------------------- */

typedef struct _ZyDisCustomDataSource
{
    ZyDisBaseDataSource super;
    ZyDisBaseDataSource_DestructionCallback userDestruct; // may be NULL
} ZyDisCustomDataSource;

/**
 * @brief   Constructor.
 * @param   ctx             The context.
 * @param   inputPeekCb     The callback peeking the next input byte.
 * @param   inputNextCb     The callback consuming the next input byte.
 * @param   isEndOfInputCb  The callback determining if the end of input was reached.
 * @param   getPositionCb   The callback obtaining the current input position.
 * @param   setPositionCb   The callback setting the current input position.
 * @param   destructionCb   The destruction callback. May be @c NULL.
 */
static void ZyDisCustomDataSource_Construct(ZyDisBaseDataSourceContext *ctx,
    ZyDisBaseDataSource_InputCallback inputPeekCb,
    ZyDisBaseDataSource_InputCallback inputNextCb,
    ZyDisBaseDataSource_IsEndOfInputCallback isEndOfInputCb,
    ZyDisBaseDataSource_GetPositionCallback getPositionCb,
    ZyDisBaseDataSource_SetPositionCallback setPositionCb,
    ZyDisBaseDataSource_DestructionCallback destructionCb);

/**
 * @brief   Destructor.
 * @param   The context.
 */
static void ZyDisCustomDataSource_Destruct(ZyDisBaseDataSourceContext *ctx);

/* ZyDisInstructionDecoder ------------------------------------------------------------------------ */

typedef struct _ZyDisInstructionDecoder
{
    ZyDisBaseDataSourceContext *dataSource;
    ZyDisDisassemblerMode      disassemblerMode;
    ZyDisInstructionSetVendor  preferredVendor;
    uint64_t                instructionPointer;
} ZyDisInstructionDecoder;

typedef enum _ZyDisRegisterClass /* : uint8_t */
{
    RC_GENERAL_PURPOSE,
    RC_MMX,
    RC_CONTROL,
    RC_DEBUG,
    RC_SEGMENT,
    RC_XMM
} ZyDisRegisterClass;

/**
 * @brief   Reads the next byte from the data source.
 * @param   ctx     The context.
 * @param   info    The instruction info.
 * @return  The current input byte. If the result is zero, you should always check the 
 *          @c flags field of the @c info parameter for error flags.
 *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
 * This method does NOT increase the current input position or the @c length field of the 
 * @c info parameter. 
 */
static uint8_t ZyDisInstructionDecoder_InputPeek(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Reads the next byte(s) from the data source.
 * @param   ctx     The context.
 * @param   info    The instruction info.
 * @return  The current input data. If the result is zero, you should always check the 
 *          @c flags field of the @c info parameter for error flags.
 *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
 * This method increases the current input position and the @c length field of the @info 
 * parameter. This method also appends the new byte(s) to to @c data field of the @c info 
 * parameter.
 */
static uint8_t ZyDisInstructionDecoder_InputNext8(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @copydoc ZyDisInstructionDecoder_InputNext8
 */
static uint16_t ZyDisInstructionDecoder_InputNext16(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @copydoc ZyDisInstructionDecoder_InputNext8
 */
static uint32_t ZyDisInstructionDecoder_InputNext32(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @copydoc ZyDisInstructionDecoder_InputNext8
 */
static uint64_t ZyDisInstructionDecoder_InputNext64(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Returns the current input byte. 
 * @param   ctx     The context.
 * @return  The current input byte.
 * The current input byte is set everytime the @c ZyDisInstructionDecoder_InputPeek or 
 * @c ZyDisInstructionDecoder_InputNextXX function is called.
 */
static uint8_t ZyDisInstructionDecoder_InputCurrent(const ZyDisInstructionDecoderContext *ctx);

/**
 * @brief   Decodes a register operand.
 * @param   ctx             The context.
 * @param   info            The instruction info.
 * @param   operand         The @c ZyDisOperandInfo struct that receives the decoded data.
 * @param   registerClass   The register class to use.
 * @param   registerId      The register id.
 * @param   operandSize     The defined size of the operand.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeRegisterOperand(const ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisRegisterClass registerClass, 
    uint8_t registerId, ZyDisDefinedOperandSize operandSize);

/**
 * @brief   Decodes a register/memory operand.
 * @param   ctx             The context.
 * @param   info            The instruction info.
 * @param   operand         The @c ZyDisOperandInfo struct that receives the decoded data.
 * @param   registerClass   The register class to use.
 * @param   operandSize     The defined size of the operand.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisRegisterClass registerClass, 
    ZyDisDefinedOperandSize operandSize);

/**
 * @brief   Decodes an immediate operand.
 * @param   ctx         The context.
 * @param   info        The instruction info.
 * @param   operand     The @c ZyDisOperandInfo struct that receives the decoded data.
 * @param   operandSize The defined size of the operand.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeImmediate(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisDefinedOperandSize operandSize);

/**
 * @brief   Decodes a displacement operand.
 * @param   ctx     The context.
 * @param   info    The instruction info.
 * @param   operand The @c ZyDisOperandInfo struct that receives the decoded data.
 * @param   size    The size of the displacement data.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeDisplacement(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, uint8_t size);

/**
 * @brief   Decodes the ModRM field of the instruction.
 * @param   ctx The context.
 * @param   The @c ZyDisInstructionInfo struct that receives the decoded data.
 * @return  @c true if it succeeds, @c false if it fails.
 * This method reads an additional input byte.
 */
static bool ZyDisInstructionDecoder_DecodeModrm(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Decodes the SIB field of the instruction.
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
 * @return  @c true if it succeeds, @c false if it fails.1
 * This method reads an additional input byte.
 */
static bool ZyDisInstructionDecoder_DecodeSIB(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Decodes VEX prefix of the instruction. 
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
 * @return  @c true if it succeeds, @c false if it fails.
 * This method takes the current input byte to determine the vex prefix type and reads one or 
 * two additional input bytes on demand.
 */
static bool ZyDisInstructionDecoder_DecodeVex(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Returns the effective operand size.
 * @param   ctx         The context.
 * @param   info        The instruction info.
 * @param   operandSize The defined operand size.
 * @return  The effective operand size.
 */
static uint16_t ZyDisInstructionDecoder_GetEffectiveOperandSize(
    const ZyDisInstructionDecoderContext *ctx, const ZyDisInstructionInfo *info, 
    ZyDisDefinedOperandSize operandSize);

/**
 * @brief   Decodes all instruction operands.
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeOperands(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Decodes the specified instruction operand.
 * @param   ctx         The context.
 * @param   info        The instruction info.
 * @param   operand     The @c ZyDisOperandInfo struct that receives the decoded data.
 * @param   operandType The defined type of the operand.
 * @param   operandSize The defined size of the operand.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeOperand(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisDefinedOperandType operandType, 
    ZyDisDefinedOperandSize operandSize);

/**
 * @brief   Resolves the effective operand and address mode of the instruction.
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the effective operand and
 *                  address mode.
 * @remarks This function requires a non-null value in the @c instrDefinition field of the 
 *          @c info struct.
 */
static void ZyDisInstructionDecoder_ResolveOperandAndAddressMode(
    const ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info);

/**
 * @brief   Calculates the effective REX/VEX.w, r, x, b, l values.
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the effective operand and
 *                  address mode.
 * @remarks This method requires a non-null value in the @c instrDefinition field of the 
 *          @c info struct.
 */
static void ZyDisInstructionDecoder_CalculateEffectiveRexVexValues(
    const ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info);

/**
 * @brief   Collects and decodes optional instruction prefixes.
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodePrefixes(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/**
 * @brief   Collects and decodes the instruction opcodes using the opcode tree.
 * @param   ctx     The context.
 * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
 * @return  @c true if it succeeds, @c false if it fails.
 */
static bool ZyDisInstructionDecoder_DecodeOpcode(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info);

/* Implementation ============================================================================== */

/* ZyDisBaseDataSource ---------------------------------------------------------------------------- */

static void ZyDisBaseDataSource_Construct(ZyDisBaseDataSourceContext *ctx)
{
    ZyDisBaseDataSource *thiz = ZyDisBaseDataSource_thiz(ctx);
    memset(thiz, 0, sizeof(*thiz));
}

static void ZyDisBaseDataSource_Destruct(ZyDisBaseDataSourceContext *ctx)
{
    ZYDIS_UNUSED(ctx);
}

void ZyDisBaseDataSource_Release(ZyDisBaseDataSourceContext *ctx)
{
    ZyDisBaseDataSource *thiz = ZyDisBaseDataSource_thiz(ctx);

    if (thiz->destruct)
    {
        thiz->destruct(ctx);
    }

    free(thiz);
    free(ctx);
}

uint8_t ZyDisBaseDataSource_InputPeek(ZyDisBaseDataSourceContext *ctx, ZyDisInstructionInfo *info)
{
    ZyDisBaseDataSource *thiz = ZyDisBaseDataSource_thiz(ctx);

    if (info->length == 15)
    {
        info->flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (ZyDisBaseDataSource_IsEndOfInput(ctx))
    {
        info->flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }

    thiz->currentInput = thiz->internalInputPeek(ctx);
    return thiz->currentInput;
}

uint8_t ZyDisBaseDataSource_InputNext8(ZyDisBaseDataSourceContext *ctx, ZyDisInstructionInfo *info)
{
    ZyDisBaseDataSource *thiz = ZyDisBaseDataSource_thiz(ctx);

    if (info->length == 15)
    {
        info->flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (ZyDisBaseDataSource_IsEndOfInput(ctx))
    {
        info->flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    thiz->currentInput = thiz->internalInputNext(ctx);
    info->data[info->length] = thiz->currentInput;
    info->length++;
    return thiz->currentInput;
}

#define ZyDisBASEDATASOURCE_INPUTNEXT_N(n)                                                           \
    uint##n##_t ZyDisBaseDataSource_InputNext##n(                                                    \
        ZyDisBaseDataSourceContext *ctx, ZyDisInstructionInfo *info)                                    \
    {                                                                                             \
        uint##n##_t result = 0;                                                                   \
        for (unsigned i = 0; i < (sizeof(uint##n##_t) / sizeof(uint8_t)); ++i)                    \
        {                                                                                         \
            uint##n##_t b = ZyDisBaseDataSource_InputNext8(ctx, info);                               \
            if (!b && (info->flags & IF_ERROR_MASK))                                              \
            {                                                                                     \
                return 0;                                                                         \
            }                                                                                     \
            result |= (b << (i * 8));                                                             \
        }                                                                                         \
        return result;                                                                            \
    }

ZyDisBASEDATASOURCE_INPUTNEXT_N(16)
ZyDisBASEDATASOURCE_INPUTNEXT_N(32)
ZyDisBASEDATASOURCE_INPUTNEXT_N(64)
#undef ZyDisBASEDATASOURCE_INPUTNEXT_N

uint8_t ZyDisBaseDataSource_InputCurrent(const ZyDisBaseDataSourceContext *ctx)
{
    return ZyDisBaseDataSource_cthiz(ctx)->currentInput;
}

bool ZyDisBaseDataSource_IsEndOfInput(const ZyDisBaseDataSourceContext *ctx)
{
    assert(ZyDisBaseDataSource_cthiz(ctx)->isEndOfInput);
    return ZyDisBaseDataSource_cthiz(ctx)->isEndOfInput(ctx);
}

uint64_t ZyDisBaseDataSource_GetPosition(const ZyDisBaseDataSourceContext *ctx)
{
    assert(ZyDisBaseDataSource_cthiz(ctx)->getPosition);
    return ZyDisBaseDataSource_cthiz(ctx)->getPosition(ctx);
}

bool ZyDisBaseDataSource_SetPosition(ZyDisBaseDataSourceContext *ctx, uint64_t position)
{
    assert(ZyDisBaseDataSource_thiz(ctx)->setPosition);
    return ZyDisBaseDataSource_thiz(ctx)->setPosition(ctx, position);
}

/* ZyDisMemoryDataSource -------------------------------------------------------------------------- */

void ZyDisMemoryDataSource_Construct(
    ZyDisBaseDataSourceContext *ctx, const void* buffer, size_t bufferLen)
{
    ZyDisBaseDataSource_Construct(ctx);
    ZyDisMemoryDataSource *thiz = ZyDisMemoryDataSource_thiz(ctx);

    thiz->super.destruct          = &ZyDisMemoryDataSource_Destruct;
    thiz->super.internalInputPeek = &ZyDisMemoryDataSource_InternalInputPeek;
    thiz->super.internalInputNext = &ZyDisMemoryDataSource_InternalInputNext;
    thiz->super.isEndOfInput      = &ZyDisMemoryDataSource_IsEndOfInput;
    thiz->super.getPosition       = &ZyDisMemoryDataSource_GetPosition;
    thiz->super.setPosition       = &ZyDisMemoryDataSource_SetPosition;

    thiz->inputBuffer    = buffer;
    thiz->inputBufferLen = bufferLen;
    thiz->inputBufferPos = 0;
}

void ZyDisMemoryDataSource_Destruct(ZyDisBaseDataSourceContext *ctx)
{
    // Nothing to destruct ourselfes, just call parent destructor
    ZyDisBaseDataSource_Destruct(ctx);
}

ZyDisBaseDataSourceContext* ZyDisMemoryDataSource_Create(
    const void* buffer, size_t bufferLen)
{
    ZyDisMemoryDataSource      *thiz = malloc(sizeof(ZyDisMemoryDataSource));
    ZyDisBaseDataSourceContext *ctx  = malloc(sizeof(ZyDisBaseDataSourceContext));

    if (!thiz || !ctx)
    {
        if (thiz)
        {
            free(thiz);
        }
        if (ctx)
        {
            free(ctx);
        }

        return NULL;
    }

    ctx->d.type = TYPE_MEMORYDATASOURCE;
    ctx->d.ptr  = thiz;

    ZyDisMemoryDataSource_Construct(ctx, buffer, bufferLen);

    return ctx;
}

static uint8_t ZyDisMemoryDataSource_InternalInputPeek(ZyDisBaseDataSourceContext *ctx)
{
    ZyDisMemoryDataSource *thiz = ZyDisMemoryDataSource_thiz(ctx);
    return *((const uint8_t*)thiz->inputBuffer + thiz->inputBufferPos);
}

static uint8_t ZyDisMemoryDataSource_InternalInputNext(ZyDisBaseDataSourceContext *ctx)
{
    ZyDisMemoryDataSource *thiz = ZyDisMemoryDataSource_thiz(ctx);
    ++thiz->inputBufferPos;
    return *((const uint8_t*)thiz->inputBuffer + thiz->inputBufferPos - 1);
}

static bool ZyDisMemoryDataSource_IsEndOfInput(const ZyDisBaseDataSourceContext *ctx)
{
    const ZyDisMemoryDataSource *thiz = ZyDisMemoryDataSource_cthiz(ctx);
    return (thiz->inputBufferPos >= thiz->inputBufferLen);
}

static uint64_t ZyDisMemoryDataSource_GetPosition(const ZyDisBaseDataSourceContext *ctx)
{
    return ZyDisMemoryDataSource_cthiz(ctx)->inputBufferPos;
}

static bool ZyDisMemoryDataSource_SetPosition(ZyDisBaseDataSourceContext *ctx, uint64_t position)
{
    ZyDisMemoryDataSource *thiz = ZyDisMemoryDataSource_thiz(ctx);
    thiz->inputBufferPos = position;
    return thiz->super.isEndOfInput(ctx);
}

/* ZyDisCustomDataSource -------------------------------------------------------------------------- */

static void ZyDisCustomDataSource_Construct(ZyDisBaseDataSourceContext *ctx,
    ZyDisBaseDataSource_InputCallback inputPeekCb,
    ZyDisBaseDataSource_InputCallback inputNextCb,
    ZyDisBaseDataSource_IsEndOfInputCallback isEndOfInputCb,
    ZyDisBaseDataSource_GetPositionCallback getPositionCb,
    ZyDisBaseDataSource_SetPositionCallback setPositionCb,
    ZyDisBaseDataSource_DestructionCallback destructionCb)
{
    ZyDisBaseDataSource_Construct(ctx);

    ZyDisCustomDataSource *thiz      = ZyDisCustomDataSource_thiz(ctx);
    thiz->super.destruct          = &ZyDisCustomDataSource_Destruct;
    thiz->super.internalInputPeek = inputPeekCb;
    thiz->super.internalInputNext = inputNextCb;
    thiz->super.isEndOfInput      = isEndOfInputCb;
    thiz->super.getPosition       = getPositionCb;
    thiz->super.setPosition       = setPositionCb;

    thiz->userDestruct = destructionCb;
}

static void ZyDisCustomDataSource_Destruct(ZyDisBaseDataSourceContext *ctx)
{
    ZyDisCustomDataSource *thiz = ZyDisCustomDataSource_thiz(ctx);
    
    if (thiz->userDestruct)
    {
        thiz->userDestruct(ctx);
    }

    ZyDisBaseDataSource_Destruct(ctx);
}

ZyDisBaseDataSourceContext* ZyDisCustomDataSource_Create(
    ZyDisBaseDataSource_InputCallback inputPeekCb,
    ZyDisBaseDataSource_InputCallback inputNextCb,
    ZyDisBaseDataSource_IsEndOfInputCallback isEndOfInputCb,
    ZyDisBaseDataSource_GetPositionCallback getPositionCb,
    ZyDisBaseDataSource_SetPositionCallback setPositionCb,
    ZyDisBaseDataSource_DestructionCallback destructionCb)
{
    ZyDisCustomDataSource *thiz     = malloc(sizeof(ZyDisCustomDataSource));
    ZyDisBaseDataSourceContext *ctx = malloc(sizeof(ZyDisBaseDataSourceContext));

    if (!thiz || !ctx)
    {
        if (thiz)
        {
            free(thiz);
        }
        if (ctx)
        {
            free(ctx);
        }

        return NULL;
    }

    ctx->d.type = TYPE_CUSTOMDATASOURCE;
    ctx->d.ptr  = thiz;

    ZyDisCustomDataSource_Construct(ctx, inputPeekCb, inputNextCb, isEndOfInputCb, getPositionCb,
        setPositionCb, destructionCb);

    return ctx;
}

/* ZyDisInstructionDecoder ------------------------------------------------------------------------ */

void ZyDisInstructionDecoder_Construct(ZyDisInstructionDecoderContext *ctx,
    ZyDisBaseDataSourceContext *input, ZyDisDisassemblerMode disassemblerMode, 
    ZyDisInstructionSetVendor preferredVendor, uint64_t instructionPointer)
{
    ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);

    thiz->dataSource            = input;
    thiz->disassemblerMode      = disassemblerMode;
    thiz->preferredVendor       = preferredVendor;
    thiz->instructionPointer    = instructionPointer;
}

void ZyDisInstructionDecoder_Destruct(ZyDisInstructionDecoderContext *ctx)
{
    ZYDIS_UNUSED(ctx);
}

ZyDisInstructionDecoderContext* ZyDisInstructionDecoder_Create(void)
{
    return ZyDisInstructionDecoder_CreateEx(NULL, DM_M32BIT, ISV_ANY, 0);
}   

ZyDisInstructionDecoderContext* ZyDisInstructionDecoder_CreateEx(ZyDisBaseDataSourceContext *input, 
    ZyDisDisassemblerMode disassemblerMode, ZyDisInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer)
{
    ZyDisInstructionDecoder *thiz       = malloc(sizeof(ZyDisInstructionDecoder));
    ZyDisInstructionDecoderContext *ctx = malloc(sizeof(ZyDisInstructionDecoderContext));

    if (!thiz || !ctx)
    {
        if (thiz)
        {
            free(thiz);
        }
        if (ctx)
        {
            free(ctx);
        }

        return NULL;
    }

    ctx->d.ptr  = thiz;
    ctx->d.type = TYPE_INSTRUCTIONDECODER;

    ZyDisInstructionDecoder_Construct(ctx, input, disassemblerMode, 
        preferredVendor, instructionPointer);

    return ctx;
}

void ZyDisInstructionDecoder_Release(ZyDisInstructionDecoderContext *ctx)
{
    ZyDisInstructionDecoder_Destruct(ctx);

    free(ctx->d.ptr);
    free(ctx);
}

static uint8_t ZyDisInstructionDecoder_InputPeek(
    ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info)
{
    ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);

    if (!thiz->dataSource)
    {
        info->flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }

    return ZyDisBaseDataSource_InputPeek(thiz->dataSource, info);
}

#define ZyDisINSTRUCTIONDECODER_INPUTNEXT_N(n)                                                       \
    static uint##n##_t ZyDisInstructionDecoder_InputNext##n(                                         \
        ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info)                                \
    {                                                                                             \
        ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);                              \
                                                                                                  \
        if (!thiz->dataSource)                                                                    \
        {                                                                                         \
            info->flags |= IF_ERROR_END_OF_INPUT;                                                 \
            return 0;                                                                             \
        }                                                                                         \
                                                                                                  \
        return ZyDisBaseDataSource_InputNext##n(thiz->dataSource, info);                             \
    }

ZyDisINSTRUCTIONDECODER_INPUTNEXT_N(8)
ZyDisINSTRUCTIONDECODER_INPUTNEXT_N(16)
ZyDisINSTRUCTIONDECODER_INPUTNEXT_N(32)
ZyDisINSTRUCTIONDECODER_INPUTNEXT_N(64)
#undef ZyDisINSTRUCTIONDECODER_INPUTNEXT_N

static uint8_t ZyDisInstructionDecoder_InputCurrent(const ZyDisInstructionDecoderContext *ctx)
{
    const ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_cthiz(ctx);

    if (!thiz->dataSource)
    {
        return 0;
    }

    return ZyDisBaseDataSource_InputCurrent(thiz->dataSource);
}

ZyDisBaseDataSourceContext* ZyDisInstructionDecoder_GetDataSource(
    const ZyDisInstructionDecoderContext *ctx)
{
    return ZyDisInstructionDecoder_cthiz(ctx)->dataSource;
}

void ZyDisInstructionDecoder_SetDataSource(
    ZyDisInstructionDecoderContext *ctx, ZyDisBaseDataSourceContext *input)
{
    ZyDisInstructionDecoder_thiz(ctx)->dataSource = input;
}

ZyDisDisassemblerMode ZyDisInstructionDecoder_GetDisassemblerMode(
    const ZyDisInstructionDecoderContext *ctx)
{
    return ZyDisInstructionDecoder_cthiz(ctx)->disassemblerMode;
}

void ZyDisInstructionDecoder_SetDisassemblerMode(ZyDisInstructionDecoderContext *ctx, 
    ZyDisDisassemblerMode disassemblerMode)
{
    ZyDisInstructionDecoder_thiz(ctx)->disassemblerMode = disassemblerMode;
}

ZyDisInstructionSetVendor ZyDisInstructionDecoder_GetPreferredVendor(
    const ZyDisInstructionDecoderContext *ctx)
{
    return ZyDisInstructionDecoder_cthiz(ctx)->preferredVendor;
}

void ZyDisInstructionDecoder_SetPreferredVendor(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionSetVendor preferredVendor)
{
    ZyDisInstructionDecoder_thiz(ctx)->preferredVendor = preferredVendor;
}

uint64_t ZyDisInstructionDecoder_GetInstructionPointer(
    const ZyDisInstructionDecoderContext *ctx)
{
    return ZyDisInstructionDecoder_cthiz(ctx)->instructionPointer;
}

void ZyDisInstructionDecoder_SetInstructionPointer(ZyDisInstructionDecoderContext *ctx, 
    uint64_t instructionPointer)
{
    ZyDisInstructionDecoder_thiz(ctx)->instructionPointer = instructionPointer;
}

static bool ZyDisInstructionDecoder_DecodeRegisterOperand(
    const ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, 
    ZyDisRegisterClass registerClass, uint8_t registerId, ZyDisDefinedOperandSize operandSize)
{
    ZyDisRegister reg = REG_NONE;
    uint16_t size = ZyDisInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
    const ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_cthiz(ctx);

    switch (registerClass)
    {
    case RC_GENERAL_PURPOSE: 
        switch (size) 
        {
        case 64:
            reg = REG_RAX + registerId;
            break;
        case 32:
            reg = REG_EAX + registerId;
            break;
        case 16:
            reg = REG_AX + registerId;
            break;
        case 8:
            // TODO: Only REX? Or VEX too?
            if (thiz->disassemblerMode == DM_M64BIT && (info->flags & IF_PREFIX_REX)) 
            {
                if (registerId >= 4)
                {
                    reg = REG_SPL + (registerId - 4);
                } 
                else
                {
                    reg = REG_AL + registerId;
                }
            } 
            else 
            {
                reg = REG_AL + registerId;
            }
            break;
        case 0:
            // TODO: Error?
            reg = REG_NONE;
            break;
        default:
            assert(0);
        }
        break;
    case RC_MMX: 
        reg = REG_MM0 + (registerId & 0x07);
        break;
    case RC_CONTROL: 
        reg = REG_CR0 + registerId;
        break;
    case RC_DEBUG: 
        reg = REG_DR0 + registerId;
        break;
    case RC_SEGMENT: 
        if ((registerId & 7) > 5) 
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
        reg = REG_ES + (registerId & 0x07);
        break;
    case RC_XMM:  
        reg = registerId + ((size == 256) ? REG_YMM0 : REG_XMM0);
        break;
    default: 
        assert(0);
    }

    operand->type = OPTYPE_REGISTER;
    operand->base = reg;
    operand->size = size;

    return true;
}

static bool ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ZyDisInstructionDecoderContext *ctx,
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisRegisterClass registerClass, 
    ZyDisDefinedOperandSize operandSize)
{
    if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
    {
        return false;
    }
    assert(info->flags & IF_MODRM);
    // Decode register operand
    if (info->modrm_mod == 3)
    {
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, registerClass, 
            info->modrm_rm_ext, operandSize);
    }
    // Decode memory operand
    uint8_t offset = 0;
    operand->type = OPTYPE_MEMORY;
    operand->size = ZyDisInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
    switch (info->address_mode)
    {
    case 16:
        {
            static const ZyDisRegister bases[] = { 
                REG_BX, REG_BX, REG_BP, REG_BP, 
                REG_SI, REG_DI, REG_BP, REG_BX };
            static const ZyDisRegister indices[] = { 
                REG_SI, REG_DI, REG_SI, REG_DI,
                REG_NONE, REG_NONE, REG_NONE, REG_NONE };
            operand->base = bases[info->modrm_rm_ext & 0x07];
            operand->index = indices[info->modrm_rm_ext & 0x07];
            operand->scale = 0;
            if (info->modrm_mod == 0 && info->modrm_rm_ext == 6) {
                offset = 16;
                operand->base = REG_NONE;
            } else if (info->modrm_mod == 1) {
                offset = 8;
            } else if (info->modrm_mod == 2) {
                offset = 16;
            }
        }
        break;
    case 32:
        operand->base = REG_EAX + info->modrm_rm_ext;
        switch (info->modrm_mod)
        {
        case 0:
            if (info->modrm_rm_ext == 5)
            {
                operand->base = REG_NONE;
                offset = 32;
            }
            break;
        case 1:
            offset = 8;
            break;
        case 2:
            offset = 32;
            break;
        default:
            assert(0);
        }
        if ((info->modrm_rm_ext & 0x07) == 4)
        {
            if (!ZyDisInstructionDecoder_DecodeSIB(ctx, info))
            { 
                return false;
            }
            operand->base = REG_EAX + info->sib_base_ext;
            operand->index = REG_EAX + info->sib_index_ext;
            operand->scale = (1 << info->sib_scale) & ~1;
            if (operand->index == REG_ESP)  
            {
                operand->index = REG_NONE;
                operand->scale = 0;
            } 
            if (operand->base == REG_EBP)
            {
                if (info->modrm_mod == 0)
                {
                    operand->base = REG_NONE;
                } 

                if (info->modrm_mod == 1)
                {
                    offset = 8;
                } 
                else
                {
                    offset = 32;
                }
            }
        } 
        else
        {
            operand->index = REG_NONE;
            operand->scale = 0;    
        }
        break;
    case 64:
        operand->base = REG_RAX + info->modrm_rm_ext;
        switch (info->modrm_mod)
        {
        case 0:
            if ((info->modrm_rm_ext & 0x07) == 5)
            {
                info->flags |= IF_RELATIVE;
                operand->base = REG_RIP;
                offset = 32;
            }
            break;
        case 1:
            offset = 8;
            break;
        case 2:
            offset = 32;
            break;
        default:
            assert(0);
        }
        if ((info->modrm_rm_ext & 0x07) == 4)
        {
            if (!ZyDisInstructionDecoder_DecodeSIB(ctx, info))
            {
                return false;
            }

            operand->base = REG_RAX + info->sib_base_ext;
            operand->index = REG_RAX + info->sib_index_ext;
            if (operand->index == REG_RSP) 
            {
                operand->index = REG_NONE;
                operand->scale = 0;
            } 
            else
            {
                operand->scale = (1 << info->sib_scale) & ~1;
            }

            if ((operand->base == REG_RBP) || (operand->base == REG_R13))
            {
                if (info->modrm_mod == 0)
                {
                    operand->base = REG_NONE;
                }

                if (info->modrm_mod == 1)
                {
                    offset = 8;    
                } 
                else
                {
                    offset = 32;    
                }
            }
        } else
        {
            operand->index = REG_NONE;
            operand->scale = 0;
        }
        break;
    }
    if (offset)
    {
        if (!ZyDisInstructionDecoder_DecodeDisplacement(ctx, info, operand, offset))
        {
            return false;
        }
    } else
    {
        operand->offset = 0;
    }
    return true;
}

static bool ZyDisInstructionDecoder_DecodeImmediate(ZyDisInstructionDecoderContext *ctx,
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisDefinedOperandSize operandSize)
{
    operand->type = OPTYPE_IMMEDIATE;
    operand->size = ZyDisInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
    switch (operand->size) 
    {
        case 8: 
            operand->lval.ubyte = ZyDisInstructionDecoder_InputNext8(ctx, info);
            break;
        case 16: 
            operand->lval.uword = ZyDisInstructionDecoder_InputNext16(ctx, info);
            break;
        case 32: 
            operand->lval.udword = ZyDisInstructionDecoder_InputNext32(ctx, info);
            break;
        case 64: 
            operand->lval.uqword = ZyDisInstructionDecoder_InputNext64(ctx, info);
            break;
        default: 
            // TODO: Maybe return false instead of assert
            assert(0);
    }
    if (!operand->lval.uqword && (info->flags & IF_ERROR_MASK))
    {
        return false;
    }
    return true;
}

static bool ZyDisInstructionDecoder_DecodeDisplacement(ZyDisInstructionDecoderContext *ctx,
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, uint8_t size)
{
    switch (size)
    {
    case 8:
        operand->offset = 8;
        operand->lval.ubyte = ZyDisInstructionDecoder_InputNext8(ctx, info);
        break;
    case 16:
        operand->offset = 16;
        operand->lval.uword = ZyDisInstructionDecoder_InputNext16(ctx, info);
        break;
    case 32:
        operand->offset = 32;
        operand->lval.udword = ZyDisInstructionDecoder_InputNext32(ctx, info);
        break;
    case 64:
        operand->offset = 64;
        operand->lval.uqword = ZyDisInstructionDecoder_InputNext64(ctx, info);
        break;
    default:
        // TODO: Maybe return false instead of assert
        assert(0);
    }
    if (!operand->lval.uqword && (info->flags & IF_ERROR_MASK))
    {
        return false;
    }
    return true;
}

static bool ZyDisInstructionDecoder_DecodeModrm(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    if (!(info->flags & IF_MODRM))
    {
        info->modrm = ZyDisInstructionDecoder_InputNext8(ctx, info);
        if (!info->modrm && (info->flags & IF_ERROR_MASK))
        {
            return false;
        }
        info->flags |= IF_MODRM;
        info->modrm_mod = (info->modrm >> 6) & 0x03;
        info->modrm_reg = (info->modrm >> 3) & 0x07;
        info->modrm_rm  = (info->modrm >> 0) & 0x07;
    }

    // This function might get called multiple times during the opcode- and the operand decoding, 
    // but the effective REX/VEX fields are not initialized before the end of  the opcode 
    // decoding process-> As the extended values are only used for the operand decoding, we 
    // should have no problems->
    info->modrm_reg_ext = (info->eff_rexvex_r << 3) | info->modrm_reg;
    info->modrm_rm_ext  = (info->eff_rexvex_b << 3) | info->modrm_rm;
    return true;
}

static bool ZyDisInstructionDecoder_DecodeSIB(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    assert(info->flags & IF_MODRM);
    assert((info->modrm_rm & 0x7) == 4);

    if (!(info->flags & IF_SIB))
    {
        info->sib = ZyDisInstructionDecoder_InputNext8(ctx, info);
        if (!info->sib && (info->flags & IF_ERROR_MASK))
        {
            return false;
        }
        info->flags |= IF_SIB;
        info->sib_scale  = (info->sib >> 6) & 0x03;
        info->sib_index  = (info->sib >> 3) & 0x07;
        info->sib_base   = (info->sib >> 0) & 0x07;
        // The @c decodeSib method is only called during the operand decoding, so updating the
        // extended values at this point should be safe->
        info->sib_index_ext = (info->eff_rexvex_x << 3) | info->sib_index;
        info->sib_base_ext  = (info->eff_rexvex_b << 3) | info->sib_base;
    }

    return true;
}

static bool ZyDisInstructionDecoder_DecodeVex(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    if (!(info->flags & IF_PREFIX_VEX))
    {
        info->vex_op = ZyDisInstructionDecoder_InputCurrent(ctx);
        switch (info->vex_op)
        {
        case 0xC4:
            info->vex_b1 = ZyDisInstructionDecoder_InputNext8(ctx, info);
            if (!info->vex_b1 || (info->flags & IF_ERROR_MASK))
            {
                return false;
            }

            info->vex_b2 = ZyDisInstructionDecoder_InputNext8(ctx, info);
            if (!info->vex_b2 || (info->flags & IF_ERROR_MASK))
            {
                return false;
            }

            info->vex_r      = (info->vex_b1 >> 7) & 0x01;
            info->vex_x      = (info->vex_b1 >> 6) & 0x01;
            info->vex_b      = (info->vex_b1 >> 5) & 0x01;
            info->vex_m_mmmm = (info->vex_b1 >> 0) & 0x1F;
            info->vex_w      = (info->vex_b2 >> 7) & 0x01;
            info->vex_vvvv   = (info->vex_b2 >> 3) & 0x0F;
            info->vex_l      = (info->vex_b2 >> 2) & 0x01;
            info->vex_pp     = (info->vex_b2 >> 0) & 0x03;
            break;
        case 0xC5:
            info->vex_b1 = ZyDisInstructionDecoder_InputNext8(ctx, info);
            if (!info->vex_b1 || (info->flags & IF_ERROR_MASK))
            {
                return false;
            }

            info->vex_r      = (info->vex_b1 >> 7) & 0x01;
            info->vex_x      = 1;
            info->vex_b      = 1;
            info->vex_m_mmmm = 1;
            info->vex_w      = 0;
            info->vex_vvvv   = (info->vex_b1 >> 3) & 0x0F;
            info->vex_l      = (info->vex_b1 >> 2) & 0x01;
            info->vex_pp     = (info->vex_b1 >> 0) & 0x03;
            break;
        default:
            assert(0);
        }

        if (info->vex_m_mmmm > 3)
        {
            // TODO: Add proper error flag
            info->flags |= IF_ERROR_MASK;
            return false;
        }
        info->flags |= IF_PREFIX_VEX;
    }
    return true;
}

static uint16_t ZyDisInstructionDecoder_GetEffectiveOperandSize(
    const ZyDisInstructionDecoderContext *ctx, const ZyDisInstructionInfo *info, 
    ZyDisDefinedOperandSize operandSize)
{
    const ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_cthiz(ctx);

    switch (operandSize)
    {
    case DOS_NA: 
        return 0;
    case DOS_Z: 
        return (info->operand_mode == 16) ? 16 : 32;
    case DOS_V: 
        return info->operand_mode;
    case DOS_Y: 
        return (info->operand_mode == 16) ? 32 : info->operand_mode;
    case DOS_X: 
        assert(info->vex_op != 0);
        return (info->eff_vex_l) ? 
            ZyDisInstructionDecoder_GetEffectiveOperandSize(ctx, info, DOS_QQ) : 
            ZyDisInstructionDecoder_GetEffectiveOperandSize(ctx, info, DOS_DQ);
    case DOS_RDQ: 
        return (thiz->disassemblerMode == DM_M64BIT) ? 64 : 32;
    default: 
        return ZyDisGetSimpleOperandSize(operandSize);
    }
}

static bool ZyDisInstructionDecoder_DecodeOperands(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    assert(info->instrDefinition);
    // Always try to decode the first operand
    if (!ZyDisInstructionDecoder_DecodeOperand(ctx, info, &info->operand[0], 
        info->instrDefinition->operand[0].type, info->instrDefinition->operand[0].size))
    {
        return false;
    }

    // Decode other operands on demand
    for (unsigned int i = 1; i < 4; ++i)
    {
        if (info->operand[i - 1].type != OPTYPE_NONE)
        {
            if (!ZyDisInstructionDecoder_DecodeOperand(ctx, info, &info->operand[i], 
                info->instrDefinition->operand[i].type, info->instrDefinition->operand[i].size))
            {
                return false;
            }
        }    
    }

    // Update operand access modes
    for (unsigned int i = 0; i < 4; ++i)
    {
        if (info->operand[i].type != OPTYPE_NONE)
        {
            info->operand[i].access_mode = OPACCESSMODE_READ;
            if (i == 0)
            {
                if (info->instrDefinition->flags & IDF_OPERAND1_WRITE)
                {
                    info->operand[0].access_mode = OPACCESSMODE_WRITE;
                } 
                else if (info->instrDefinition->flags & IDF_OPERAND1_READWRITE)
                {
                    info->operand[0].access_mode = OPACCESSMODE_READWRITE;
                }
            } 
            else if (i == 1)
            {
                if (info->instrDefinition->flags & IDF_OPERAND2_WRITE)
                {
                    info->operand[1].access_mode = OPACCESSMODE_WRITE;
                } 
                else if (info->instrDefinition->flags & IDF_OPERAND2_READWRITE)
                {
                    info->operand[1].access_mode = OPACCESSMODE_READWRITE;
                }    
            }
        }
    }

    return true;
}

static bool ZyDisInstructionDecoder_DecodeOperand(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info, ZyDisOperandInfo *operand, ZyDisDefinedOperandType operandType, 
    ZyDisDefinedOperandSize operandSize)
{
    const ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);

    operand->type = OPTYPE_NONE;
    switch (operandType)
    {
    case DOT_NONE:
        break;
    case DOT_A: 
        operand->type = OPTYPE_POINTER;
        if (info->operand_mode == 16)
        {
            operand->size = 32;
            operand->lval.ptr.off = ZyDisInstructionDecoder_InputNext16(ctx, info);
            operand->lval.ptr.seg = ZyDisInstructionDecoder_InputNext16(ctx, info);
        } 
        else 
        {
            operand->size = 48;
            operand->lval.ptr.off = ZyDisInstructionDecoder_InputNext32(ctx, info);
            operand->lval.ptr.seg = ZyDisInstructionDecoder_InputNext16(ctx, info);
        }

        if ((!operand->lval.ptr.off || !operand->lval.ptr.seg) && (info->flags & IF_ERROR_MASK))
        {
            return false;
        }

        break;
    case DOT_C: 
        if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_CONTROL, 
            info->modrm_reg_ext, operandSize);
    case DOT_D: 
        if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_DEBUG, 
            info->modrm_reg_ext, operandSize);
    case DOT_F: 
        // TODO: FAR flag
    case DOT_M: 
        // ModR/M byte may refer only to a register
        if (info->modrm_mod == 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
    case DOT_E: 
        return ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, 
            RC_GENERAL_PURPOSE, operandSize);
    case DOT_G: 
        if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            info->modrm_reg_ext, operandSize);
    case DOT_H: 
        assert(info->vex_op != 0);
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_XMM, 
            (0xF & ~info->vex_vvvv), operandSize);
    case DOT_sI:
        operand->signed_lval = true;
    case DOT_I: 
        return ZyDisInstructionDecoder_DecodeImmediate(ctx, info, operand, operandSize);
    case DOT_I1: 
        operand->type = OPTYPE_CONSTANT;
        operand->lval.udword = 1;
        break;
    case DOT_J: 
        if (!ZyDisInstructionDecoder_DecodeImmediate(ctx, info, operand, operandSize))
        {
            return false;
        }
        operand->type = OPTYPE_REL_IMMEDIATE;
        operand->signed_lval = true;
        info->flags |= IF_RELATIVE;
        break;
    case DOT_L: 
        {
            assert(info->vex_op != 0);
            uint8_t imm = ZyDisInstructionDecoder_InputNext8(ctx, info);
            if (!imm && (info->flags & IF_ERROR_MASK))
            {
                return false;
            }
            uint8_t mask = (thiz->disassemblerMode == DM_M64BIT) ? 0xF : 0x7;
            return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_XMM, 
                mask & (imm >> 4), operandSize);
        }
    case DOT_MR: 
        return ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, 
            RC_GENERAL_PURPOSE, info->modrm_mod == 3 ? 
            ZyDisGetComplexOperandRegSize(operandSize) : ZyDisGetComplexOperandMemSize(operandSize));
    case DOT_MU: 
        return ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, RC_XMM, 
            info->modrm_mod == 3 ? 
            ZyDisGetComplexOperandRegSize(operandSize) : ZyDisGetComplexOperandMemSize(operandSize));
    case DOT_N: 
        // ModR/M byte may refer only to memory
        if (info->modrm_mod != 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
    case DOT_Q: 
        return ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, RC_MMX, 
            operandSize);
    case DOT_O: 
        operand->type = OPTYPE_MEMORY;
        operand->base = REG_NONE;
        operand->index = REG_NONE;
        operand->scale = 0;
        operand->size = ZyDisInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
        return ZyDisInstructionDecoder_DecodeDisplacement(ctx, info, operand, info->address_mode);
    case DOT_P: 
        if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_MMX, 
            info->modrm_reg_ext, operandSize);
    case DOT_R: 
        // ModR/M byte may refer only to memory
        if (info->modrm_mod != 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, 
            RC_GENERAL_PURPOSE, operandSize);
    case DOT_S: 
        if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_SEGMENT, 
            info->modrm_reg_ext, operandSize);
    case DOT_U: 
        // ModR/M byte may refer only to memory
        if (info->modrm_mod != 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
     case DOT_W: 
        return ZyDisInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, RC_XMM, 
            operandSize);
    case DOT_V: 
        if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_XMM, 
            info->modrm_reg_ext, operandSize);
    case DOT_R0: 
    case DOT_R1: 
    case DOT_R2: 
    case DOT_R3: 
    case DOT_R4: 
    case DOT_R5: 
    case DOT_R6: 
    case DOT_R7: 
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            (uint8_t)((info->eff_rexvex_b << 3) | operandType - DOT_R0), operandSize);
    case DOT_AL: 
    case DOT_AX: 
    case DOT_EAX: 
    case DOT_RAX: 
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            0, operandSize);
    case DOT_CL: 
    case DOT_CX: 
    case DOT_ECX: 
    case DOT_RCX: 
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            1, operandSize);
    case DOT_DL: 
    case DOT_DX: 
    case DOT_EDX: 
    case DOT_RDX: 
        return ZyDisInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            2, operandSize);
    case DOT_ES: 
    case DOT_CS: 
    case DOT_SS: 
    case DOT_DS: 
    case DOT_FS: 
    case DOT_GS: 
        if (thiz->disassemblerMode == DM_M64BIT)
        {
            if ((operandType != DOT_FS) && (operandType != DOT_GS))
            {
                info->flags |= IF_ERROR_OPERAND;
                return false;
            }
        }
        operand->type = OPTYPE_REGISTER;
        operand->base = (uint16_t)(operandType - DOT_ES + REG_ES);
        operand->size = 16;
        break;
    case DOT_ST0: 
    case DOT_ST1: 
    case DOT_ST2: 
    case DOT_ST3: 
    case DOT_ST4: 
    case DOT_ST5: 
    case DOT_ST6: 
    case DOT_ST7: 
        operand->type = OPTYPE_REGISTER;
        operand->base = (uint16_t)(operandType - DOT_ST0 + REG_ST0);
        operand->size = 80;
        break;
    default: 
        assert(0);
    }
    return true;
}

static void ZyDisInstructionDecoder_ResolveOperandAndAddressMode(
    const ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info)
{
    const ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_cthiz(ctx);

    assert(info->instrDefinition);
    switch (thiz->disassemblerMode)
    {
    case DM_M16BIT:
        info->operand_mode = (info->flags & IF_PREFIX_OPERAND_SIZE) ? 32 : 16;
        info->address_mode = (info->flags & IF_PREFIX_ADDRESS_SIZE) ? 32 : 16;
        break;
    case DM_M32BIT:
        info->operand_mode = (info->flags & IF_PREFIX_OPERAND_SIZE) ? 16 : 32;
        info->address_mode = (info->flags & IF_PREFIX_ADDRESS_SIZE) ? 16 : 32;
        break;
    case DM_M64BIT:
        if (info->eff_rexvex_w)
        {
            info->operand_mode = 64;
        } 
        else if ((info->flags & IF_PREFIX_OPERAND_SIZE))
        {
            info->operand_mode = 16;
        } 
        else
        {
            info->operand_mode = (info->instrDefinition->flags & IDF_DEFAULT_64) ? 64 : 32;
        }

        info->address_mode = (info->flags & IF_PREFIX_ADDRESS_SIZE) ? 32 : 64;
        break;
    default: 
        assert(0);
    }
}

static void ZyDisInstructionDecoder_CalculateEffectiveRexVexValues(
    const ZyDisInstructionDecoderContext *ctx, ZyDisInstructionInfo *info)
{
    ZYDIS_UNUSED(ctx);

    assert(info->instrDefinition);
    uint8_t rex = info->rex;
    if (info->flags & IF_PREFIX_VEX)
    {
        switch (info->vex_op)
        {
        case 0xC4:
            rex = ((~(info->vex_b1 >> 5) & 0x07) | ((info->vex_b2 >> 4) & 0x08));
            break;
        case 0xC5:
            rex = (~(info->vex_b1 >> 5)) & 4;
            break;
        default:
            assert(0);
        }    
    }
    rex &= (info->instrDefinition->flags & 0x000F);
    info->eff_rexvex_w = (rex >> 3) & 0x01;
    info->eff_rexvex_r = (rex >> 2) & 0x01;
    info->eff_rexvex_x = (rex >> 1) & 0x01;
    info->eff_rexvex_b = (rex >> 0) & 0x01;
    info->eff_vex_l    = info->vex_l && (info->instrDefinition->flags & IDF_ACCEPTS_VEXL);
}

static bool ZyDisInstructionDecoder_DecodePrefixes(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);

    bool done = false;
    do
    {
        switch (ZyDisInstructionDecoder_InputPeek(ctx, info))
        {
        case 0xF0:
            info->flags |= IF_PREFIX_LOCK;
            break;
        case 0xF2:
            // REPNZ and REPZ are mutally exclusive. The one that comes later has precedence.
            info->flags |= IF_PREFIX_REP;
            info->flags &= ~IF_PREFIX_REPNE;
            break;
        case 0xF3:
            // REPNZ and REPZ are mutally exclusive. The one that comes later has precedence.
            info->flags |= IF_PREFIX_REP;
            info->flags &= ~IF_PREFIX_REPNE;
            break;
        case 0x2E: 
            info->flags |= IF_PREFIX_SEGMENT;
            info->segment = REG_CS;
            break;
        case 0x36:
            info->flags |= IF_PREFIX_SEGMENT;
            info->segment = REG_SS;
            break;
        case 0x3E: 
            info->flags |= IF_PREFIX_SEGMENT;
            info->segment = REG_DS;
            break;
        case 0x26: 
            info->flags |= IF_PREFIX_SEGMENT;
            info->segment = REG_ES;
            break;
        case 0x64:
            info->flags |= IF_PREFIX_SEGMENT;
            info->segment = REG_FS;
            break;
        case 0x65: 
            info->flags |= IF_PREFIX_SEGMENT;
            info->segment = REG_GS;
            break;
        case 0x66:
            info->flags |= IF_PREFIX_OPERAND_SIZE;
            break;
        case 0x67:
            info->flags |= IF_PREFIX_ADDRESS_SIZE;
            break;
        default:
            if ((thiz->disassemblerMode == DM_M64BIT) && 
                (ZyDisInstructionDecoder_InputCurrent(ctx) & 0xF0) == 0x40)
            {
                info->flags |= IF_PREFIX_REX;
                info->rex = ZyDisInstructionDecoder_InputCurrent(ctx); 
            } 
            else
            {
                done = true;
            }
            break;
        }
        // Increase the input offset, if a prefix was found
        if (!done)
        {
            if (!ZyDisInstructionDecoder_InputNext8(ctx, info) && (info->flags & IF_ERROR_MASK))
            {
                return false;
            }
        }
    } while (!done);
    // TODO: Check for multiple prefixes of the same group
    // Parse REX Prefix
    if (info->flags & IF_PREFIX_REX)
    {
        info->rex_w = (info->rex >> 3) & 0x01;
        info->rex_r = (info->rex >> 2) & 0x01;
        info->rex_x = (info->rex >> 1) & 0x01;
        info->rex_b = (info->rex >> 0) & 0x01;
    }
    return true;
}

static bool ZyDisInstructionDecoder_DecodeOpcode(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);

    // Read first opcode byte
    if (!ZyDisInstructionDecoder_InputNext8(ctx, info) && (info->flags & IF_ERROR_MASK))
    {
        return false;
    }

    // Update instruction info
    info->opcode[0] = ZyDisInstructionDecoder_InputCurrent(ctx);
    info->opcode_length = 1;

    // Iterate through opcode tree
    ZyDisOpcodeTreeNode node = ZyDisGetOpcodeTreeChild(ZyDisGetOpcodeTreeRoot(), 
        ZyDisInstructionDecoder_InputCurrent(ctx));
    ZyDisOpcodeTreeNodeType nodeType;

    do
    {
        uint16_t index = 0;
        nodeType = ZyDisGetOpcodeNodeType(node);
        switch (nodeType)
        {
        case OTNT_INSTRUCTION_DEFINITION: 
            {
                // Check for invalid instruction
                if (ZyDisGetOpcodeNodeValue(node) == 0)
                {
                    info->flags |= IF_ERROR_INVALID;
                    return false;
                }
                // Get instruction definition
                const ZyDisInstructionDefinition *instrDefinition = ZyDisGetInstructionDefinition(node);
                // Check for invalid 64 bit instruction
                if ((thiz->disassemblerMode == DM_M64BIT) && 
                    (instrDefinition->flags & IDF_INVALID_64))
                {
                    info->flags |= IF_ERROR_INVALID_64;
                    return false;
                }
                // Update instruction info
                info->instrDefinition = instrDefinition;
                info->mnemonic = instrDefinition->mnemonic;
                // Update effective REX/VEX values
                ZyDisInstructionDecoder_CalculateEffectiveRexVexValues(ctx, info);
                // Resolve operand and address mode
                ZyDisInstructionDecoder_ResolveOperandAndAddressMode(ctx, info);
                // Decode operands
                if (!ZyDisInstructionDecoder_DecodeOperands(ctx, info))
                {
                    return false;
                }
            }  
            return true;
        case OTNT_TABLE: 
            // Read next opcode byte
            if (!ZyDisInstructionDecoder_InputNext8(ctx, info) && (info->flags & IF_ERROR_MASK))
            {
                return false;
            }
            // Update instruction info
            assert((info->opcode_length > 0) && (info->opcode_length < 3));
            info->opcode[info->opcode_length] = ZyDisInstructionDecoder_InputCurrent(ctx);
            info->opcode_length++;
            // Set child node index for next iteration
            index = ZyDisInstructionDecoder_InputCurrent(ctx);
            break;
        case OTNT_MODRM_MOD: 
            // Decode modrm byte
            if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
            {
                return false;
            }
            index = (info->modrm_mod == 0x3) ? 1 : 0;
            break;
        case OTNT_MODRM_REG: 
            // Decode modrm byte
            if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
            {
                return false;
            }
            index = info->modrm_reg;
            break;
        case OTNT_MODRM_RM: 
            // Decode modrm byte
            if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
            {
                return false;
            }
            index = info->modrm_rm;
            break;
        case OTNT_MANDATORY: 
            // Check if there are any prefixes present
            if (info->flags & IF_PREFIX_REP)
            {
                index = 1; // F2
            } 
            else if (info->flags & IF_PREFIX_REPNE)
            {
                index = 2; // F3
            } 
            else if (info->flags & IF_PREFIX_OPERAND_SIZE)
            {
                index = 3; // 66
            }

            if (ZyDisGetOpcodeTreeChild(node, index) == 0)
            {
                index = 0;
            }

            if (index && (ZyDisGetOpcodeTreeChild(node, index) != 0))
            {
                // Remove REP and REPNE prefix
                info->flags &= ~IF_PREFIX_REP;
                info->flags &= ~IF_PREFIX_REPNE;
                // Remove OPERAND_SIZE prefix, if it was used as mandatory prefix for the 
                // instruction
                if (index == 3)
                {
                    info->flags &= ~IF_PREFIX_OPERAND_SIZE;
                }
            }
            break;
        case OTNT_X87: 
            // Decode modrm byte
            if (!ZyDisInstructionDecoder_DecodeModrm(ctx, info))
            {
                return false;
            }
            index = info->modrm - 0xC0;
            break;
        case OTNT_ADDRESS_SIZE: 
            switch (thiz->disassemblerMode)
            {
            case DM_M16BIT:
                index = (info->flags & IF_PREFIX_ADDRESS_SIZE) ? 1 : 0;
                break;
            case DM_M32BIT:
                index = (info->flags & IF_PREFIX_ADDRESS_SIZE) ? 0 : 1;
                break;
            case DM_M64BIT:
                index = (info->flags & IF_PREFIX_ADDRESS_SIZE) ? 1 : 2;
                break;
            default:
                assert(0);
            }
            break;
        case OTNT_OPERAND_SIZE: 
            switch (thiz->disassemblerMode)
            {
            case DM_M16BIT:
                index = (info->flags & IF_PREFIX_OPERAND_SIZE) ? 1 : 0;
                break;
            case DM_M32BIT:
                index = (info->flags & IF_PREFIX_OPERAND_SIZE) ? 0 : 1;
                break;
            case DM_M64BIT:
                index = (info->rex_w) ? 2 : ((info->flags & IF_PREFIX_OPERAND_SIZE) ? 0 : 1);
                break;
            default:
                assert(0);
            }
            break;
        case OTNT_MODE: 
            index = (thiz->disassemblerMode != DM_M64BIT) ? 0 : 1;
            break;
        case OTNT_VENDOR:
            switch (thiz->preferredVendor)
            {
            case ISV_ANY: 
                index = (ZyDisGetOpcodeTreeChild(node, 0) != 0) ? 0 : 1;
                break;
            case ISV_INTEL: 
                index = 1;
                break;
            case ISV_AMD: 
                index = 0;
                break;
            default: 
                assert(0);
            }
            break;
        case OTNT_AMD3DNOW: 
            {     
                // As all 3dnow instructions got the same operands and flag definitions, we just
                // decode a random instruction and determine the specific opcode later->
                assert(ZyDisGetOpcodeTreeChild(node, 0x0C) != 0);
                const ZyDisInstructionDefinition *instrDefinition =
                    ZyDisGetInstructionDefinition(ZyDisGetOpcodeTreeChild(node, 0x0C));
                // Update instruction info
                info->instrDefinition = instrDefinition;
                info->mnemonic = instrDefinition->mnemonic;
                // Update effective REX/VEX values
                ZyDisInstructionDecoder_CalculateEffectiveRexVexValues(ctx, info);
                // Resolve operand and address mode
                ZyDisInstructionDecoder_ResolveOperandAndAddressMode(ctx, info);
                // Decode operands
                if (!ZyDisInstructionDecoder_DecodeOperands(ctx, info))
                {
                    return false;
                }
                // Read the actual 3dnow opcode
                info->opcode[2] = ZyDisInstructionDecoder_InputNext8(ctx, info);
                if (!info->opcode[2] && (info->flags & IF_ERROR_MASK))
                {
                    return false;
                }
                // Update instruction info
                instrDefinition = 
                    ZyDisGetInstructionDefinition(ZyDisGetOpcodeTreeChild(node, info->opcode[2]));
                if (!instrDefinition || 
                    (instrDefinition->mnemonic == MNEM_INVALID))
                {
                    info->flags |= IF_ERROR_INVALID;
                    return false;
                }
                info->instrDefinition = instrDefinition;
                info->mnemonic = instrDefinition->mnemonic; 
                // Update operand access modes
                for (unsigned int i = 0; i < 4; ++i)
                {
                    if (info->operand[i].type != OPTYPE_NONE)
                    {
                        info->operand[i].access_mode = OPACCESSMODE_READ;
                    }    
                }
                if (info->operand[0].type != OPTYPE_NONE)
                {
                    if (info->instrDefinition->flags & IDF_OPERAND1_WRITE)
                    {
                        info->operand[0].access_mode = OPACCESSMODE_WRITE;
                    } 
                    else if (info->instrDefinition->flags & IDF_OPERAND1_READWRITE)
                    {
                        info->operand[0].access_mode = OPACCESSMODE_READWRITE;
                    }
                }
                if (info->operand[1].type != OPTYPE_NONE)
                {
                    if (info->instrDefinition->flags & IDF_OPERAND2_WRITE)
                    {
                        info->operand[1].access_mode = OPACCESSMODE_WRITE;
                    } 
                    else if (info->instrDefinition->flags & IDF_OPERAND2_READWRITE)
                    {
                        info->operand[1].access_mode = OPACCESSMODE_READWRITE;
                    }
                }
                // Terminate loop
                return true;
            }
        case OTNT_VEX: 
            if ((thiz->disassemblerMode == DM_M64BIT) 
                || (((ZyDisInstructionDecoder_InputCurrent(ctx) >> 6) & 0x03) == 0x03))
            {
                // Decode vex prefix
                if (!ZyDisInstructionDecoder_DecodeVex(ctx, info))
                {
                    return false;
                }

                // Update instruction info (error cases are checked by the @c decodeVex method)
                switch (info->vex_m_mmmm)
                {
                case 1:
                    info->opcode_length = 1;
                    info->opcode[0] = 0x0F;
                    break;
                case 2:
                    info->opcode_length = 2;
                    info->opcode[0] = 0x0F;
                    info->opcode[1] = 0x38;
                    break;
                case 3:
                    info->opcode_length = 2;
                    info->opcode[0] = 0x0F;
                    info->opcode[1] = 0x3A;
                    break;
                }

                // Set child node index for next iteration
                index = info->vex_m_mmmm + (info->vex_pp << 2);
            } 
            else
            {
                index = 0;
            }
            break;
        case OTNT_VEXW: 
            assert(info->flags & IF_PREFIX_VEX);
            index = info->vex_w;
            break;
        case OTNT_VEXL: 
            assert(info->flags & IF_PREFIX_VEX);
            index = info->vex_l;
            break;
        default: 
            assert(0);
        }
        node = ZyDisGetOpcodeTreeChild(node, index);
    } while (nodeType != OTNT_INSTRUCTION_DEFINITION);

    return false;
}

bool ZyDisInstructionDecoder_DecodeInstruction(ZyDisInstructionDecoderContext *ctx, 
    ZyDisInstructionInfo *info)
{
    ZyDisInstructionDecoder *thiz = ZyDisInstructionDecoder_thiz(ctx);

    // Clear instruction info
    memset(info, 0, sizeof(*info));

    // Set disassembler mode flags
    switch (thiz->disassemblerMode)
    {
    case DM_M16BIT: 
        info->flags |= IF_DISASSEMBLER_MODE_16;
        break;
    case DM_M32BIT: 
        info->flags |= IF_DISASSEMBLER_MODE_32;
        break;
    case DM_M64BIT: 
        info->flags |= IF_DISASSEMBLER_MODE_64;
        break;
    default: 
        assert(0);
    }

    // Set instruction address
    info->instrAddress = thiz->instructionPointer;

    // Decode
    if (!ZyDisInstructionDecoder_DecodePrefixes(ctx, info) 
        || !ZyDisInstructionDecoder_DecodeOpcode(ctx, info))
    {
        goto DecodeError;
    }

    // SWAPGS is only valid in 64 bit mode
    if ((info->mnemonic == MNEM_SWAPGS) && 
        (thiz->disassemblerMode != DM_M64BIT))
    {
        info->flags &= IF_ERROR_INVALID;
        goto DecodeError;
    }

    // Handle aliases
    if (info->mnemonic == MNEM_XCHG)
    {
        if ((info->operand[0].type == OPTYPE_REGISTER && 
            info->operand[0].base == REG_AX &&
            info->operand[1].type == OPTYPE_REGISTER && 
            info->operand[1].base == REG_AX) || 
            (info->operand[0].type == OPTYPE_REGISTER && 
            info->operand[0].base == REG_EAX &&
            info->operand[1].type == OPTYPE_REGISTER && 
            info->operand[1].base == REG_EAX))
        {
            info->mnemonic = MNEM_NOP;
            info->operand[0].type = OPTYPE_NONE;    
            info->operand[1].type = OPTYPE_NONE; 
            info->operand[0].access_mode = OPACCESSMODE_NA;
            info->operand[1].access_mode = OPACCESSMODE_NA;
        }
    }

    if ((info->mnemonic == MNEM_NOP) && (info->flags & IF_PREFIX_REP))
    {
        info->mnemonic = MNEM_PAUSE;
        info->flags &= ~IF_PREFIX_REP;
    }

    // Increment instruction pointer
    thiz->instructionPointer += info->length;
    // Set instruction pointer
    info->instrPointer = thiz->instructionPointer;
    return true;

DecodeError:
    ++thiz->instructionPointer;

    // Backup all error flags, the instruction length and the instruction address
    uint32_t flags = info->flags & (IF_ERROR_MASK | 0x00000007);
    uint8_t length = info->length;
    uint8_t firstByte = info->data[0];
    uint64_t instrAddress = info->instrAddress;

    // Clear instruction info
    memset(info, 0, sizeof(*info));

    // Restore saved values
    info->flags = flags;
    info->length = length;
    info->data[0] = firstByte;
    info->instrAddress = instrAddress;
    info->instrDefinition = ZyDisGetInstructionDefinition(0);

    // Decrement the input position, if more than one byte was read from the input data 
    // source while decoding the invalid instruction
    if (info->length != 1)
    {
        ZyDisBaseDataSource_SetPosition(thiz->dataSource, 
            ZyDisBaseDataSource_GetPosition(thiz->dataSource) - info->length + 1);
        info->length = 1;
    }

    // Return with error, if the end of the input source was reached while decoding the 
    // invalid instruction
    if (info->flags & IF_ERROR_END_OF_INPUT)
    {
        info->length = 0;
        return false;
    }

    return true;
}

/* ============================================================================================= */