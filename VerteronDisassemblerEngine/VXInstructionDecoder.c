/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 13. March 2015

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

#include "VXInstructionDecoder.h"
#include "VXInternalHelpers.h"
#include "VXOpcodeTableInternal.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Internal interface ========================================================================== */

/* VXBaseDataSource ---------------------------------------------------------------------------- */

typedef void(*VXBaseDataSource_DestructionCallback)(VXBaseDataSourceContext *ctx);
typedef uint8_t(*VXBaseDataSource_InputCallback)(VXBaseDataSourceContext *ctx);
typedef bool(*VXBaseDataSource_IsEndOfInputCallback)(const VXBaseDataSourceContext *ctx);
typedef uint64_t(*VXBaseDataSource_GetPositionCallback)(const VXBaseDataSourceContext *ctx);
typedef bool(*VXBaseDataSource_SetPositionCallback)(
    VXBaseDataSourceContext *ctx, uint64_t position);

typedef struct _VXBaseDataSource
{
    uint8_t currentInput;
    VXBaseDataSource_DestructionCallback destruct; // may be NULL
    VXBaseDataSource_InputCallback internalInputPeek;
    VXBaseDataSource_InputCallback internalInputNext;
    VXBaseDataSource_IsEndOfInputCallback isEndOfInput;
    VXBaseDataSource_GetPositionCallback getPosition;
    VXBaseDataSource_SetPositionCallback setPosition;
} VXBaseDataSource;

static void VXBaseDataSource_Construct(VXBaseDataSourceContext *ctx);
static void VXBaseDataSource_Destruct(VXBaseDataSourceContext *ctx);
uint8_t VXBaseDataSource_InputPeek(VXBaseDataSourceContext *ctx, VXInstructionInfo *info);
uint8_t VXBaseDataSource_InputNext8(VXBaseDataSourceContext *ctx, VXInstructionInfo *info);
uint16_t VXBaseDataSource_InputNext16(VXBaseDataSourceContext *ctx, VXInstructionInfo *info);
uint32_t VXBaseDataSource_InputNext32(VXBaseDataSourceContext *ctx, VXInstructionInfo *info);
uint64_t VXBaseDataSource_InputNext64(VXBaseDataSourceContext *ctx, VXInstructionInfo *info);
uint8_t VXBaseDataSource_InputCurrent(const VXBaseDataSourceContext *ctx);

/* VXMemoryDataSource -------------------------------------------------------------------------- */

typedef struct _VXMemoryDataSource
{
    VXBaseDataSource super;
    const void *inputBuffer;
    uint64_t inputBufferLen;
    uint64_t inputBufferPos;
} VXMemoryDataSource;

static void VXMemoryDataSource_Construct(VXBaseDataSourceContext *ctx, const void* buffer, size_t bufferLen);
static void VXMemoryDataSource_Destruct(VXBaseDataSourceContext *ctx);
VXBaseDataSourceContext* VXMemoryDataSource_Create(const void* buffer, size_t bufferLen);
static uint8_t VXMemoryDataSource_InternalInputPeek(VXBaseDataSourceContext *ctx);
static uint8_t VXMemoryDataSource_InternalInputNext(VXBaseDataSourceContext *ctx);
static bool VXMemoryDataSource_IsEndOfInput(const VXBaseDataSourceContext *ctx);
static uint64_t VXMemoryDataSource_GetPosition(const VXBaseDataSourceContext *ctx);
static bool VXMemoryDataSource_SetPosition(VXBaseDataSourceContext *ctx, uint64_t position);

/* VXInstructionDecoder ------------------------------------------------------------------------ */

typedef struct _VXInstructionDecoder
{
    VXBaseDataSourceContext *dataSource;
    VXDisassemblerMode      disassemblerMode;
    VXInstructionSetVendor  preferredVendor;
    uint64_t                instructionPointer;
} VXInstructionDecoder;

typedef enum _VXRegisterClass /* : uint8_t */
{
    RC_GENERAL_PURPOSE,
    RC_MMX,
    RC_CONTROL,
    RC_DEBUG,
    RC_SEGMENT,
    RC_XMM
} VXRegisterClass;

static uint8_t VXInstructionDecoder_InputPeek(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static uint8_t VXInstructionDecoder_InputNext8(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static uint16_t VXInstructionDecoder_InputNext16(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static uint32_t VXInstructionDecoder_InputNext32(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static uint64_t VXInstructionDecoder_InputNext64(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static uint8_t VXInstructionDecoder_InputCurrent(const VXInstructionDecoderContext *ctx);
VXBaseDataSourceContext* VXInstructionDecoder_GetDataSource(const VXInstructionDecoderContext *ctx);
void VXInstructionDecoder_SetDataSource(VXInstructionDecoderContext *ctx, VXBaseDataSourceContext *input);
VXDisassemblerMode VXInstructionDecoder_GetDisassemblerMode(const VXInstructionDecoderContext *ctx);
void VXInstructionDecoder_SetDisassemblerMode(VXInstructionDecoderContext *ctx, VXDisassemblerMode disassemblerMode);
VXInstructionSetVendor VXInstructionDecoder_GetPreferredVendor(const VXInstructionDecoderContext *ctx);
void VXInstructionDecoder_SetPreferredVendor(VXInstructionDecoderContext *ctx, VXInstructionSetVendor preferredVendor);
uint64_t VXInstructionDecoder_GetInstructionPointer(const VXInstructionDecoderContext *ctx);
void VXInstructionDecoder_SetInstructionPointer(VXInstructionDecoderContext *ctx, uint64_t instructionPointer);
static bool VXInstructionDecoder_DecodeRegisterOperand(const VXInstructionDecoderContext *ctx, VXInstructionInfo *info, VXOperandInfo *operand, VXRegisterClass registerClass, uint8_t registerId, VXDefinedOperandSize operandSize);
static bool VXInstructionDecoder_DecodeRegisterMemoryOperand(VXInstructionDecoderContext *ctx, VXInstructionInfo *info, VXOperandInfo *operand, VXRegisterClass registerClass, VXDefinedOperandSize operandSize);
static bool VXInstructionDecoder_DecodeImmediate(VXInstructionDecoderContext *ctx, VXInstructionInfo *info, VXOperandInfo *operand, VXDefinedOperandSize operandSize);
static bool VXInstructionDecoder_DecodeDisplacement(VXInstructionDecoderContext *ctx, VXInstructionInfo *info, VXOperandInfo *operand, uint8_t size);
static bool VXInstructionDecoder_DecodeModrm(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static bool VXInstructionDecoder_DecodeSIB(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static bool VXInstructionDecoder_DecodeVex(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static uint16_t VXInstructionDecoder_GetEffectiveOperandSize(const VXInstructionDecoderContext *ctx, const VXInstructionInfo *info, VXDefinedOperandSize operandSize);
static bool VXInstructionDecoder_DecodeOperands(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static bool VXInstructionDecoder_DecodeOperand(VXInstructionDecoderContext *ctx, VXInstructionInfo *info, VXOperandInfo *operand, VXDefinedOperandType operandType, VXDefinedOperandSize operandSize);
static void VXInstructionDecoder_ResolveOperandAndAddressMode(const VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static void VXInstructionDecoder_CalculateEffectiveRexVexValues(const VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static bool VXInstructionDecoder_DecodePrefixes(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
static bool VXInstructionDecoder_DecodeOpcode(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);
VXInstructionDecoderContext* VXInstructionDecoder_Create(void);
VXInstructionDecoderContext* VXInstructionDecoder_CreateEx(VXBaseDataSourceContext *input, VXDisassemblerMode disassemblerMode, VXInstructionSetVendor preferredVendor, uint64_t instructionPointer);
bool VXInstructionDecoder_DecodeInstruction(VXInstructionDecoderContext *ctx, VXInstructionInfo *info);

/* Implementation ============================================================================== */

/* VXBaseDataSource ---------------------------------------------------------------------------- */

static void VXBaseDataSource_Construct(VXBaseDataSourceContext *ctx)
{
    VXBaseDataSource *thiz = VXBaseDataSource_thiz(ctx);
    memset(thiz, 0, sizeof(*thiz));
}

static void VXBaseDataSource_Destruct(VXBaseDataSourceContext *ctx)
{
    
}

void VXBaseDataSource_Release(VXBaseDataSourceContext *ctx)
{
    VXBaseDataSource *thiz = VXBaseDataSource_thiz(ctx);

    if (thiz->destruct)
    {
        thiz->destruct(ctx);
    }

    free(thiz);
    free(ctx);
}

uint8_t VXBaseDataSource_InputPeek(VXBaseDataSourceContext *ctx, VXInstructionInfo *info)
{
    VXBaseDataSource *thiz = VXBaseDataSource_thiz(ctx);

    if (info->length == 15)
    {
        info->flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (VXBaseDataSource_IsEndOfInput(ctx))
    {
        info->flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }

    thiz->currentInput = thiz->internalInputPeek(ctx);
    return thiz->currentInput;
}

uint8_t VXBaseDataSource_InputNext8(VXBaseDataSourceContext *ctx, VXInstructionInfo *info)
{
    VXBaseDataSource *thiz = VXBaseDataSource_thiz(ctx);

    if (info->length == 15)
    {
        info->flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (VXBaseDataSource_IsEndOfInput(ctx))
    {
        info->flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    thiz->currentInput = thiz->internalInputNext(ctx);
    info->data[info->length] = thiz->currentInput;
    info->length++;
    return thiz->currentInput;
}

#define VXBASEDATASOURCE_INPUTNEXT_N(n)                                                           \
    uint##n##_t VXBaseDataSource_InputNext##n(                                                    \
        VXBaseDataSourceContext *ctx, VXInstructionInfo *info)                                    \
    {                                                                                             \
        uint##n##_t result = 0;                                                                   \
        for (unsigned i = 0; i < (sizeof(uint##n##_t) / sizeof(uint8_t)); ++i)                    \
        {                                                                                         \
            uint##n##_t b = VXBaseDataSource_InputNext8(ctx, info);                               \
            if (!b && (info->flags & IF_ERROR_MASK))                                              \
            {                                                                                     \
                return 0;                                                                         \
            }                                                                                     \
            result |= (b << (i * 8));                                                             \
        }                                                                                         \
        return result;                                                                            \
    }

VXBASEDATASOURCE_INPUTNEXT_N(16)
VXBASEDATASOURCE_INPUTNEXT_N(32)
VXBASEDATASOURCE_INPUTNEXT_N(64)
#undef VXBASEDATASOURCE_INPUTNEXT_N

uint8_t VXBaseDataSource_InputCurrent(const VXBaseDataSourceContext *ctx)
{
    return VXBaseDataSource_cthiz(ctx)->currentInput;
}

bool VXBaseDataSource_IsEndOfInput(const VXBaseDataSourceContext *ctx)
{
    assert(VXBaseDataSource_cthiz(ctx)->isEndOfInput);
    return VXBaseDataSource_cthiz(ctx)->isEndOfInput(ctx);
}

uint64_t VXBaseDataSource_GetPosition(const VXBaseDataSourceContext *ctx)
{
    assert(VXBaseDataSource_cthiz(ctx)->getPosition);
    return VXBaseDataSource_cthiz(ctx)->getPosition(ctx);
}

bool VXBaseDataSource_SetPosition(VXBaseDataSourceContext *ctx, uint64_t position)
{
    assert(VXBaseDataSource_thiz(ctx)->setPosition);
    return VXBaseDataSource_thiz(ctx)->setPosition(ctx, position);
}

/* VXMemoryDataSource -------------------------------------------------------------------------- */

void VXMemoryDataSource_Construct(
    VXBaseDataSourceContext *ctx, const void* buffer, size_t bufferLen)
{
    VXBaseDataSource_Construct(ctx);
    VXMemoryDataSource *thiz = VXMemoryDataSource_thiz(ctx);

    thiz->super.destruct          = &VXMemoryDataSource_Destruct;
    thiz->super.internalInputPeek = &VXMemoryDataSource_InternalInputPeek;
    thiz->super.internalInputNext = &VXMemoryDataSource_InternalInputNext;
    thiz->super.isEndOfInput      = &VXMemoryDataSource_IsEndOfInput;
    thiz->super.getPosition       = &VXMemoryDataSource_GetPosition;
    thiz->super.setPosition       = &VXMemoryDataSource_SetPosition;

    thiz->inputBuffer    = buffer;
    thiz->inputBufferLen = bufferLen;
    thiz->inputBufferPos = 0;
}

void VXMemoryDataSource_Destruct(VXBaseDataSourceContext *ctx)
{
    // Nothing to destruct ourselfes, just call parent destructor
    VXBaseDataSource_Destruct(ctx);
}

VXBaseDataSourceContext* VXMemoryDataSource_Create(
    const void* buffer, size_t bufferLen)
{
    VXMemoryDataSource      *thiz = malloc(sizeof(VXMemoryDataSource));
    VXBaseDataSourceContext *ctx  = malloc(sizeof(VXBaseDataSourceContext));

    if (!thiz || !ctx)
    {
        return NULL;
    }

    ctx->d.type = TYPE_MEMORYDATASOURCE;
    ctx->d.ptr  = thiz;

    VXMemoryDataSource_Construct(ctx, buffer, bufferLen);

    return ctx;
}

static uint8_t VXMemoryDataSource_InternalInputPeek(VXBaseDataSourceContext *ctx)
{
    VXMemoryDataSource *thiz = VXMemoryDataSource_thiz(ctx);
    return *((const uint8_t*)thiz->inputBuffer + thiz->inputBufferPos);
}

static uint8_t VXMemoryDataSource_InternalInputNext(VXBaseDataSourceContext *ctx)
{
    VXMemoryDataSource *thiz = VXMemoryDataSource_thiz(ctx);
    ++thiz->inputBufferPos;
    return *((const uint8_t*)thiz->inputBuffer + thiz->inputBufferPos - 1);
}

static bool VXMemoryDataSource_IsEndOfInput(const VXBaseDataSourceContext *ctx)
{
    const VXMemoryDataSource *thiz = VXMemoryDataSource_cthiz(ctx);
    return (thiz->inputBufferPos >= thiz->inputBufferLen);
}

static uint64_t VXMemoryDataSource_GetPosition(const VXBaseDataSourceContext *ctx)
{
    return VXMemoryDataSource_cthiz(ctx)->inputBufferPos;
}

static bool VXMemoryDataSource_SetPosition(VXBaseDataSourceContext *ctx, uint64_t position)
{
    VXMemoryDataSource *thiz = VXMemoryDataSource_thiz(ctx);
    thiz->inputBufferPos = position;
    return thiz->super.isEndOfInput(ctx);
}

/* VXInstructionDecoder ------------------------------------------------------------------------ */

void VXInstructionDecoder_Construct(
    VXInstructionDecoderContext *ctx,
    VXBaseDataSourceContext *input, 
    VXDisassemblerMode disassemblerMode,
    VXInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer)
{
    VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);

    thiz->dataSource            = input;
    thiz->disassemblerMode      = disassemblerMode;
    thiz->preferredVendor       = preferredVendor;
    thiz->instructionPointer    = instructionPointer;
}

void VXInstructionDecoder_Destruct(VXInstructionDecoderContext *ctx)
{
    
}

VXInstructionDecoderContext* VXInstructionDecoder_Create(void)
{
    return VXInstructionDecoder_CreateEx(NULL, DM_M32BIT, ISV_ANY, 0);
}   

VXInstructionDecoderContext* VXInstructionDecoder_CreateEx(
    VXBaseDataSourceContext *input, 
    VXDisassemblerMode disassemblerMode,
    VXInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer)
{
    VXInstructionDecoder *thiz       = malloc(sizeof(VXInstructionDecoder));
    VXInstructionDecoderContext *ctx = malloc(sizeof(VXInstructionDecoderContext));

    if (!thiz || !ctx)
    {
        return NULL;
    }

    ctx->d.ptr  = thiz;
    ctx->d.type = TYPE_INSTRUCTIONDECODER;

    VXInstructionDecoder_Construct(ctx, input, disassemblerMode, 
        preferredVendor, instructionPointer);

    return ctx;
}

void VXInstructionDecoder_Release(VXInstructionDecoderContext *ctx)
{
    VXInstructionDecoder_Destruct(ctx);

    free(ctx->d.ptr);
    free(ctx);
}

static uint8_t VXInstructionDecoder_InputPeek(
    VXInstructionDecoderContext *ctx, VXInstructionInfo *info)
{
    VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);

    if (!thiz->dataSource)
    {
        info->flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }

    return VXBaseDataSource_InputPeek(thiz->dataSource, info);
}

#define VXINSTRUCTIONDECODER_INPUTNEXT_N(n)                                                       \
    static uint##n##_t VXInstructionDecoder_InputNext##n(                                         \
        VXInstructionDecoderContext *ctx, VXInstructionInfo *info)                                \
    {                                                                                             \
        VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);                              \
                                                                                                  \
        if (!thiz->dataSource)                                                                    \
        {                                                                                         \
            info->flags |= IF_ERROR_END_OF_INPUT;                                                 \
            return 0;                                                                             \
        }                                                                                         \
                                                                                                  \
        return VXBaseDataSource_InputNext##n(thiz->dataSource, info);                             \
    }

VXINSTRUCTIONDECODER_INPUTNEXT_N(8)
VXINSTRUCTIONDECODER_INPUTNEXT_N(16)
VXINSTRUCTIONDECODER_INPUTNEXT_N(32)
VXINSTRUCTIONDECODER_INPUTNEXT_N(64)
#undef VXINSTRUCTIONDECODER_INPUTNEXT_N

static uint8_t VXInstructionDecoder_InputCurrent(const VXInstructionDecoderContext *ctx)
{
    const VXInstructionDecoder *thiz = VXInstructionDecoder_cthiz(ctx);

    if (!thiz->dataSource)
    {
        return 0;
    }

    return VXBaseDataSource_InputCurrent(thiz->dataSource);
}

VXBaseDataSourceContext* VXInstructionDecoder_GetDataSource(
    const VXInstructionDecoderContext *ctx)
{
    return VXInstructionDecoder_cthiz(ctx)->dataSource;
}

void VXInstructionDecoder_SetDataSource(
    VXInstructionDecoderContext *ctx, VXBaseDataSourceContext *input)
{
    VXInstructionDecoder_thiz(ctx)->dataSource = input;
}

VXDisassemblerMode VXInstructionDecoder_GetDisassemblerMode(
    const VXInstructionDecoderContext *ctx)
{
    return VXInstructionDecoder_cthiz(ctx)->disassemblerMode;
}

void VXInstructionDecoder_SetDisassemblerMode(VXInstructionDecoderContext *ctx, 
    VXDisassemblerMode disassemblerMode)
{
    VXInstructionDecoder_thiz(ctx)->disassemblerMode = disassemblerMode;
}

VXInstructionSetVendor VXInstructionDecoder_GetPreferredVendor(
    const VXInstructionDecoderContext *ctx)
{
    return VXInstructionDecoder_cthiz(ctx)->preferredVendor;
}

void VXInstructionDecoder_SetPreferredVendor(VXInstructionDecoderContext *ctx, 
    VXInstructionSetVendor preferredVendor)
{
    VXInstructionDecoder_thiz(ctx)->preferredVendor = preferredVendor;
}

uint64_t VXInstructionDecoder_GetInstructionPointer(
    const VXInstructionDecoderContext *ctx)
{
    return VXInstructionDecoder_cthiz(ctx)->instructionPointer;
}

void VXInstructionDecoder_SetInstructionPointer(VXInstructionDecoderContext *ctx, 
    uint64_t instructionPointer)
{
    VXInstructionDecoder_thiz(ctx)->instructionPointer = instructionPointer;
}

static bool VXInstructionDecoder_DecodeRegisterOperand(
    const VXInstructionDecoderContext *ctx, VXInstructionInfo *info, VXOperandInfo *operand, 
    VXRegisterClass registerClass, uint8_t registerId, VXDefinedOperandSize operandSize)
{
    VXRegister reg = REG_NONE;
    uint16_t size = VXInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
    const VXInstructionDecoder *thiz = VXInstructionDecoder_cthiz(ctx);

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

static bool VXInstructionDecoder_DecodeRegisterMemoryOperand(VXInstructionDecoderContext *ctx,
    VXInstructionInfo *info, VXOperandInfo *operand, VXRegisterClass registerClass, 
    VXDefinedOperandSize operandSize)
{
    if (!VXInstructionDecoder_DecodeModrm(ctx, info))
    {
        return false;
    }
    assert(info->flags & IF_MODRM);
    // Decode register operand
    if (info->modrm_mod == 3)
    {
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, registerClass, 
            info->modrm_rm_ext, operandSize);
    }
    // Decode memory operand
    uint8_t offset = 0;
    operand->type = OPTYPE_MEMORY;
    operand->size = VXInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
    switch (info->address_mode)
    {
    case 16:
        {
            static const VXRegister bases[] = { 
                REG_BX, REG_BX, REG_BP, REG_BP, 
                REG_SI, REG_DI, REG_BP, REG_BX };
            static const VXRegister indices[] = { 
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
            if (!VXInstructionDecoder_DecodeSIB(ctx, info))
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
            if (!VXInstructionDecoder_DecodeSIB(ctx, info))
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
        if (!VXInstructionDecoder_DecodeDisplacement(ctx, info, operand, offset))
        {
            return false;
        }
    } else
    {
        operand->offset = 0;
    }
    return true;
}

static bool VXInstructionDecoder_DecodeImmediate(VXInstructionDecoderContext *ctx,
    VXInstructionInfo *info, VXOperandInfo *operand, VXDefinedOperandSize operandSize)
{
    operand->type = OPTYPE_IMMEDIATE;
    operand->size = VXInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
    switch (operand->size) 
    {
        case 8: 
            operand->lval.ubyte = VXInstructionDecoder_InputNext8(ctx, info);
            break;
        case 16: 
            operand->lval.uword = VXInstructionDecoder_InputNext16(ctx, info);
            break;
        case 32: 
            operand->lval.udword = VXInstructionDecoder_InputNext32(ctx, info);
            break;
        case 64: 
            operand->lval.uqword = VXInstructionDecoder_InputNext64(ctx, info);
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

static bool VXInstructionDecoder_DecodeDisplacement(VXInstructionDecoderContext *ctx,
    VXInstructionInfo *info, VXOperandInfo *operand, uint8_t size)
{
    switch (size)
    {
    case 8:
        operand->offset = 8;
        operand->lval.ubyte = VXInstructionDecoder_InputNext8(ctx, info);
        break;
    case 16:
        operand->offset = 16;
        operand->lval.uword = VXInstructionDecoder_InputNext16(ctx, info);
        break;
    case 32:
        operand->offset = 32;
        operand->lval.udword = VXInstructionDecoder_InputNext32(ctx, info);
        break;
    case 64:
        operand->offset = 64;
        operand->lval.uqword = VXInstructionDecoder_InputNext64(ctx, info);
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

static bool VXInstructionDecoder_DecodeModrm(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    if (!(info->flags & IF_MODRM))
    {
        info->modrm = VXInstructionDecoder_InputNext8(ctx, info);
        if (!info->modrm && (info->flags & IF_ERROR_MASK))
        {
            return false;
        }
        info->flags |= IF_MODRM;
        info->modrm_mod = (info->modrm >> 6) & 0x03;
        info->modrm_reg = (info->modrm >> 3) & 0x07;
        info->modrm_rm  = (info->modrm >> 0) & 0x07;
    }

    // The @c decodeModrm method might get called multiple times during the opcode- and the
    // operand decoding, but the effective REX/VEX fields are not initialized before the end of  
    // the opcode decoding process-> As the extended values are only used for the operand decoding,
    // we should have no problems->
    info->modrm_reg_ext = (info->eff_rexvex_r << 3) | info->modrm_reg;
    info->modrm_rm_ext  = (info->eff_rexvex_b << 3) | info->modrm_rm;
    return true;
}

static bool VXInstructionDecoder_DecodeSIB(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    assert(info->flags & IF_MODRM);
    assert((info->modrm_rm & 0x7) == 4);
    if (!(info->flags & IF_SIB))
    {
        info->sib = VXInstructionDecoder_InputNext8(ctx, info);
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

static bool VXInstructionDecoder_DecodeVex(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    if (!(info->flags & IF_PREFIX_VEX))
    {
        info->vex_op = VXInstructionDecoder_InputCurrent(ctx);
        switch (info->vex_op)
        {
        case 0xC4:
            info->vex_b1 = VXInstructionDecoder_InputNext8(ctx, info);
            if (!info->vex_b1 || (info->flags & IF_ERROR_MASK))
            {
                return false;
            }

            info->vex_b2 = VXInstructionDecoder_InputNext8(ctx, info);
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
            info->vex_b1 = VXInstructionDecoder_InputNext8(ctx, info);
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

static uint16_t VXInstructionDecoder_GetEffectiveOperandSize(
    const VXInstructionDecoderContext *ctx, const VXInstructionInfo *info, 
    VXDefinedOperandSize operandSize)
{
    const VXInstructionDecoder *thiz = VXInstructionDecoder_cthiz(ctx);

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
            VXInstructionDecoder_GetEffectiveOperandSize(ctx, info, DOS_QQ) : 
            VXInstructionDecoder_GetEffectiveOperandSize(ctx, info, DOS_DQ);
    case DOS_RDQ: 
        return (thiz->disassemblerMode == DM_M64BIT) ? 64 : 32;
    default: 
        return VXGetSimpleOperandSize(operandSize);
    }
}

static bool VXInstructionDecoder_DecodeOperands(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    assert(info->instrDefinition);
    // Always try to decode the first operand
    if (!VXInstructionDecoder_DecodeOperand(ctx, info, &info->operand[0], 
        info->instrDefinition->operand[0].type, info->instrDefinition->operand[0].size))
    {
        return false;
    }

    // Decode other operands on demand
    for (unsigned int i = 1; i < 4; ++i)
    {
        if (info->operand[i - 1].type != OPTYPE_NONE)
        {
            if (!VXInstructionDecoder_DecodeOperand(ctx, info, &info->operand[i], 
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

static bool VXInstructionDecoder_DecodeOperand(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info, VXOperandInfo *operand, VXDefinedOperandType operandType, 
    VXDefinedOperandSize operandSize)
{
    const VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);

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
            operand->lval.ptr.off = VXInstructionDecoder_InputNext16(ctx, info);
            operand->lval.ptr.seg = VXInstructionDecoder_InputNext16(ctx, info);
        } 
        else 
        {
            operand->size = 48;
            operand->lval.ptr.off = VXInstructionDecoder_InputNext32(ctx, info);
            operand->lval.ptr.seg = VXInstructionDecoder_InputNext16(ctx, info);
        }

        if ((!operand->lval.ptr.off || !operand->lval.ptr.seg) && (info->flags & IF_ERROR_MASK))
        {
            return false;
        }

        break;
    case DOT_C: 
        if (!VXInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_CONTROL, 
            info->modrm_reg_ext, operandSize);
    case DOT_D: 
        if (!VXInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_DEBUG, 
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
        return VXInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, 
            RC_GENERAL_PURPOSE, operandSize);
    case DOT_G: 
        if (!VXInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            info->modrm_reg_ext, operandSize);
    case DOT_H: 
        assert(info->vex_op != 0);
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_XMM, 
            (0xF & ~info->vex_vvvv), operandSize);
    case DOT_sI:
        operand->signed_lval = true;
    case DOT_I: 
        return VXInstructionDecoder_DecodeImmediate(ctx, info, operand, operandSize);
    case DOT_I1: 
        operand->type = OPTYPE_CONSTANT;
        operand->lval.udword = 1;
        break;
    case DOT_J: 
        if (!VXInstructionDecoder_DecodeImmediate(ctx, info, operand, operandSize))
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
            uint8_t imm = VXInstructionDecoder_InputNext8(ctx, info);
            if (!imm && (info->flags & IF_ERROR_MASK))
            {
                return false;
            }
            uint8_t mask = (thiz->disassemblerMode == DM_M64BIT) ? 0xF : 0x7;
            return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_XMM, 
                mask & (imm >> 4), operandSize);
        }
    case DOT_MR: 
        return VXInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, 
            RC_GENERAL_PURPOSE, info->modrm_mod == 3 ? 
            VXGetComplexOperandRegSize(operandSize) : VXGetComplexOperandMemSize(operandSize));
    case DOT_MU: 
        return VXInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, RC_XMM, 
            info->modrm_mod == 3 ? 
            VXGetComplexOperandRegSize(operandSize) : VXGetComplexOperandMemSize(operandSize));
    case DOT_N: 
        // ModR/M byte may refer only to memory
        if (info->modrm_mod != 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
    case DOT_Q: 
        return VXInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, RC_MMX, 
            operandSize);
    case DOT_O: 
        operand->type = OPTYPE_MEMORY;
        operand->base = REG_NONE;
        operand->index = REG_NONE;
        operand->scale = 0;
        operand->size = VXInstructionDecoder_GetEffectiveOperandSize(ctx, info, operandSize);
        return VXInstructionDecoder_DecodeDisplacement(ctx, info, operand, info->address_mode);
    case DOT_P: 
        if (!VXInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_MMX, 
            info->modrm_reg_ext, operandSize);
    case DOT_R: 
        // ModR/M byte may refer only to memory
        if (info->modrm_mod != 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, 
            RC_GENERAL_PURPOSE, operandSize);
    case DOT_S: 
        if (!VXInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_SEGMENT, 
            info->modrm_reg_ext, operandSize);
    case DOT_U: 
        // ModR/M byte may refer only to memory
        if (info->modrm_mod != 3)
        {
            info->flags |= IF_ERROR_OPERAND;
            return false;
        }
     case DOT_W: 
        return VXInstructionDecoder_DecodeRegisterMemoryOperand(ctx, info, operand, RC_XMM, 
            operandSize);
    case DOT_V: 
        if (!VXInstructionDecoder_DecodeModrm(ctx, info))
        {
            return false;
        }
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_XMM, 
            info->modrm_reg_ext, operandSize);
    case DOT_R0: 
    case DOT_R1: 
    case DOT_R2: 
    case DOT_R3: 
    case DOT_R4: 
    case DOT_R5: 
    case DOT_R6: 
    case DOT_R7: 
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            ((info->eff_rexvex_b << 3) | operandType - DOT_R0), operandSize);
    case DOT_AL: 
    case DOT_AX: 
    case DOT_EAX: 
    case DOT_RAX: 
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            0, operandSize);
    case DOT_CL: 
    case DOT_CX: 
    case DOT_ECX: 
    case DOT_RCX: 
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
            1, operandSize);
    case DOT_DL: 
    case DOT_DX: 
    case DOT_EDX: 
    case DOT_RDX: 
        return VXInstructionDecoder_DecodeRegisterOperand(ctx, info, operand, RC_GENERAL_PURPOSE, 
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
        operand->base = operandType - DOT_ES + REG_ES;
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
        operand->base = operandType - DOT_ST0 + REG_ST0;
        operand->size = 80;
        break;
    default: 
        assert(0);
    }
    return true;
}

static void VXInstructionDecoder_ResolveOperandAndAddressMode(
    const VXInstructionDecoderContext *ctx, VXInstructionInfo *info)
{
    const VXInstructionDecoder *thiz = VXInstructionDecoder_cthiz(ctx);

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

static void VXInstructionDecoder_CalculateEffectiveRexVexValues(
    const VXInstructionDecoderContext *ctx, VXInstructionInfo *info)
{
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

static bool VXInstructionDecoder_DecodePrefixes(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);

    bool done = false;
    do
    {
        switch (VXInstructionDecoder_InputPeek(ctx, info))
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
                (VXInstructionDecoder_InputCurrent(ctx) & 0xF0) == 0x40)
            {
                info->flags |= IF_PREFIX_REX;
                info->rex = VXInstructionDecoder_InputCurrent(ctx); 
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
            if (!VXInstructionDecoder_InputNext8(ctx, info) && (info->flags & IF_ERROR_MASK))
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

static bool VXInstructionDecoder_DecodeOpcode(VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);

    // Read first opcode byte
    if (!VXInstructionDecoder_InputNext8(ctx, info) && (info->flags & IF_ERROR_MASK))
    {
        return false;
    }

    // Update instruction info
    info->opcode[0] = VXInstructionDecoder_InputCurrent(ctx);
    info->opcode_length = 1;

    // Iterate through opcode tree
    VXOpcodeTreeNode node = VXGetOpcodeTreeChild(VXGetOpcodeTreeRoot(), 
        VXInstructionDecoder_InputCurrent(ctx));
    VXOpcodeTreeNodeType nodeType;

    do
    {
        uint16_t index = 0;
        nodeType = VXGetOpcodeNodeType(node);
        switch (nodeType)
        {
        case OTNT_INSTRUCTION_DEFINITION: 
            {
                // Check for invalid instruction
                if (VXGetOpcodeNodeValue(node) == 0)
                {
                    info->flags |= IF_ERROR_INVALID;
                    return false;
                }
                // Get instruction definition
                const VXInstructionDefinition *instrDefinition = VXGetInstructionDefinition(node);
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
                VXInstructionDecoder_CalculateEffectiveRexVexValues(ctx, info);
                // Resolve operand and address mode
                VXInstructionDecoder_ResolveOperandAndAddressMode(ctx, info);
                // Decode operands
                if (!VXInstructionDecoder_DecodeOperands(ctx, info))
                {
                    return false;
                }
            }  
            return true;
        case OTNT_TABLE: 
            // Read next opcode byte
            if (!VXInstructionDecoder_InputNext8(ctx, info) && (info->flags & IF_ERROR_MASK))
            {
                return false;
            }
            // Update instruction info
            assert((info->opcode_length > 0) && (info->opcode_length < 3));
            info->opcode[info->opcode_length] = VXInstructionDecoder_InputCurrent(ctx);
            info->opcode_length++;
            // Set child node index for next iteration
            index = VXInstructionDecoder_InputCurrent(ctx);
            break;
        case OTNT_MODRM_MOD: 
            // Decode modrm byte
            if (!VXInstructionDecoder_DecodeModrm(ctx, info))
            {
                return false;
            }
            index = (info->modrm_mod == 0x3) ? 1 : 0;
            break;
        case OTNT_MODRM_REG: 
            // Decode modrm byte
            if (!VXInstructionDecoder_DecodeModrm(ctx, info))
            {
                return false;
            }
            index = info->modrm_reg;
            break;
        case OTNT_MODRM_RM: 
            // Decode modrm byte
            if (!VXInstructionDecoder_DecodeModrm(ctx, info))
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

            if (VXGetOpcodeTreeChild(node, index) == 0)
            {
                index = 0;
            }

            if (index && (VXGetOpcodeTreeChild(node, index) != 0))
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
            if (!VXInstructionDecoder_DecodeModrm(ctx, info))
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
                index = (VXGetOpcodeTreeChild(node, 0) != 0) ? 0 : 1;
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
                assert(VXGetOpcodeTreeChild(node, 0x0C) != 0);
                const VXInstructionDefinition *instrDefinition =
                    VXGetInstructionDefinition(VXGetOpcodeTreeChild(node, 0x0C));
                // Update instruction info
                info->instrDefinition = instrDefinition;
                info->mnemonic = instrDefinition->mnemonic;
                // Update effective REX/VEX values
                VXInstructionDecoder_CalculateEffectiveRexVexValues(ctx, info);
                // Resolve operand and address mode
                VXInstructionDecoder_ResolveOperandAndAddressMode(ctx, info);
                // Decode operands
                if (!VXInstructionDecoder_DecodeOperands(ctx, info))
                {
                    return false;
                }
                // Read the actual 3dnow opcode
                info->opcode[2] = VXInstructionDecoder_InputNext8(ctx, info);
                if (!info->opcode[2] && (info->flags & IF_ERROR_MASK))
                {
                    return false;
                }
                // Update instruction info
                instrDefinition = 
                    VXGetInstructionDefinition(VXGetOpcodeTreeChild(node, info->opcode[2]));
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
                || (((VXInstructionDecoder_InputCurrent(ctx) >> 6) & 0x03) == 0x03))
            {
                // Decode vex prefix
                if (!VXInstructionDecoder_DecodeVex(ctx, info))
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
        node = VXGetOpcodeTreeChild(node, index);
    } while (nodeType != OTNT_INSTRUCTION_DEFINITION);

    return false;
}

bool VXInstructionDecoder_DecodeInstruction(
    VXInstructionDecoderContext *ctx, 
    VXInstructionInfo *info)
{
    VXInstructionDecoder *thiz = VXInstructionDecoder_thiz(ctx);

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
    if (!VXInstructionDecoder_DecodePrefixes(ctx, info) 
        || !VXInstructionDecoder_DecodeOpcode(ctx, info))
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
    info->instrDefinition = VXGetInstructionDefinition(0);

    // Decrement the input position, if more than one byte was read from the input data 
    // source while decoding the invalid instruction
    if (info->length != 1)
    {
        VXBaseDataSource_SetPosition(thiz->dataSource, 
            VXBaseDataSource_GetPosition(thiz->dataSource) - info->length + 1);
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