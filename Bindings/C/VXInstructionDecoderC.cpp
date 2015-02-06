/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : athre0z
  Modifications   :

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

#include "VXInstructionDecoderC.h"
#include "VXInstructionDecoder.h"
#include "VXDisassemblerTypes.h"

/* Helpers ===================================================================================== */

namespace
{

inline Verteron::VXBaseDataSource* VXBaseDataSource_CppPtr(
    VXBaseDataSourceContext *ctx)
{
    return reinterpret_cast<Verteron::VXBaseDataSource*>(ctx);
}

inline const Verteron::VXBaseDataSource* VXBaseDataSource_CppPtr(
    const VXBaseDataSourceContext *ctx)
{
    return reinterpret_cast<const Verteron::VXBaseDataSource*>(ctx);
}

inline VXBaseDataSourceContext* VXBaseDataSource_CPtr(
    Verteron::VXBaseDataSource *ptr)
{
    return reinterpret_cast<VXBaseDataSourceContext*>(ptr);
}

inline const VXBaseDataSourceContext* VXBaseDataSource_CPtr(
    const Verteron::VXBaseDataSource *ptr)
{
    return reinterpret_cast<const VXBaseDataSourceContext*>(ptr);
}

inline Verteron::VXInstructionInfo* VXInstructionInfo_CppPtr(
    VXInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Verteron::VXInstructionInfo), "broken struct");
    return reinterpret_cast<Verteron::VXInstructionInfo*>(ptr);
}

inline const Verteron::VXInstructionInfo* VXInstructionInfo_CppPtr(
    const VXInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Verteron::VXInstructionInfo), "broken struct");
    return reinterpret_cast<const Verteron::VXInstructionInfo*>(ptr);
}

inline VXInstructionDecoderContext* VXInstructionDecoder_CPtr(
    Verteron::VXInstructionDecoder *ptr)
{
    return reinterpret_cast<VXInstructionDecoderContext*>(ptr);
}

inline const VXInstructionDecoderContext* VXInstructionDecoder_CPtr(
    const Verteron::VXInstructionDecoder *ptr)
{
    return reinterpret_cast<const VXInstructionDecoderContext*>(ptr);
}

inline Verteron::VXInstructionDecoder* VXInstructionDecoder_CppPtr(
    VXInstructionDecoderContext *ctx)
{
    return reinterpret_cast<Verteron::VXInstructionDecoder*>(ctx);
}

inline const Verteron::VXInstructionDecoder* VXInstructionDecoder_CppPtr(
    const VXInstructionDecoderContext *ctx)
{
    return reinterpret_cast<const Verteron::VXInstructionDecoder*>(ctx);
}

inline Verteron::VXDisassemblerMode VXDisassemblerMode_CppRepr(
    VXDisassemblerMode val)
{
    return static_cast<Verteron::VXDisassemblerMode>(val);
}

inline VXDisassemblerMode VXDisassemblerMode_CRepr(
    Verteron::VXDisassemblerMode val)
{
    return static_cast<VXDisassemblerMode>(val);
}

inline Verteron::VXInstructionSetVendor VXInstructionSetVendor_CppRepr(
    VXInstructionSetVendor val)
{
    return static_cast<Verteron::VXInstructionSetVendor>(val);
}

inline VXInstructionSetVendor VXInstructionSetVendor_CRepr(
    Verteron::VXInstructionSetVendor val)
{
    return static_cast<VXInstructionSetVendor>(val);
}

}

/* VXBaseDataSource ============================================================================ */

void VXBaseDataSource_Release(VXBaseDataSourceContext *ctx)
{
    delete VXBaseDataSource_CppPtr(ctx);
}

uint8_t VXBaseDataSource_InputPeek(VXBaseDataSourceContext *ctx, VXInstructionInfo *info)
{
    return VXBaseDataSource_CppPtr(ctx)->inputPeek(*VXInstructionInfo_CppPtr(info));
}

uint8_t VXBaseDataSource_InputNext(VXBaseDataSourceContext *ctx, VXInstructionInfo *info)
{
    return VXBaseDataSource_CppPtr(ctx)->inputNext(*VXInstructionInfo_CppPtr(info));
}

uint8_t VXBaseDataSource_InputCurrent(const VXBaseDataSourceContext *ctx)
{
    return VXBaseDataSource_CppPtr(ctx)->inputCurrent();
}

bool VXBaseDataSource_IsEndOfInput(const VXBaseDataSourceContext *ctx)
{
    return VXBaseDataSource_CppPtr(ctx)->isEndOfInput();
}

uint64_t VXBaseDataSource_GetPosition(const VXBaseDataSourceContext *ctx)
{
    return VXBaseDataSource_CppPtr(ctx)->getPosition();
}

bool VXBaseDataSource_SetPosition(VXBaseDataSourceContext *ctx, uint64_t position)
{
    return VXBaseDataSource_CppPtr(ctx)->setPosition(position);
}

/* VXMemoryDataSource ========================================================================== */

VXBaseDataSourceContext* VXMemoryDataSource_Create(const void* buffer, size_t bufferLen)
{
    return reinterpret_cast<VXBaseDataSourceContext*>(
        new Verteron::VXMemoryDataSource(buffer, bufferLen)); 
}

/* VXInstructionDecoder ======================================================================== */

VXInstructionDecoderContext* VXInstructionDecoder_Create()
{
    return reinterpret_cast<VXInstructionDecoderContext*>(new Verteron::VXInstructionDecoder);
}

VXInstructionDecoderContext* VXInstructionDecoder_CreateEx(
    VXBaseDataSourceContext *input, 
    VXDisassemblerMode disassemblerMode,
    VXInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer)
{
    return VXInstructionDecoder_CPtr(new Verteron::VXInstructionDecoder(
        VXBaseDataSource_CppPtr(input),
        VXDisassemblerMode_CppRepr(disassemblerMode), 
        VXInstructionSetVendor_CppRepr(preferredVendor),
        instructionPointer));
}

void VXInstructionDecoder_Release(VXInstructionDecoderContext *ctx)
{
    delete VXInstructionDecoder_CppPtr(ctx);
}

bool VXInstructionDecoder_DecodeInstruction(
    VXInstructionDecoderContext *ctx, VXInstructionInfo *info)
{
    return VXInstructionDecoder_CppPtr(ctx)->decodeInstruction(
        *VXInstructionInfo_CppPtr(info));
}

VXBaseDataSourceContext* VXInstructionDecoder_GetDataSource(
    const VXInstructionDecoderContext *ctx)
{
    return VXBaseDataSource_CPtr(VXInstructionDecoder_CppPtr(ctx)->getDataSource());
}

void VXInstructionDecoder_SetDataSource(
    VXInstructionDecoderContext *ctx, VXBaseDataSourceContext *input)
{
    VXInstructionDecoder_CppPtr(ctx)->setDataSource(VXBaseDataSource_CppPtr(input));
}

VXDisassemblerMode VXInstructionDecoder_GetDisassemblerMode(VXInstructionDecoderContext *ctx)
{
    return VXDisassemblerMode_CRepr(VXInstructionDecoder_CppPtr(ctx)->getDisassemblerMode());
}

void VXInstructionDecoder_SetDisassemblerMode(
    VXInstructionDecoderContext *ctx,
    VXDisassemblerMode disassemblerMode)
{
    VXInstructionDecoder_CppPtr(ctx)->setDisassemblerMode(
        VXDisassemblerMode_CppRepr(disassemblerMode));
}

VXInstructionSetVendor VXInstructionDecoder_GetPreferredVendor(
    const VXInstructionDecoderContext *ctx)
{
    return VXInstructionSetVendor_CRepr(VXInstructionDecoder_CppPtr(ctx)->getPreferredVendor());
}

void VXInstructionDecoder_SetPreferredVendor(
    VXInstructionDecoderContext *ctx,
    VXInstructionSetVendor preferredVendor)
{
    return VXInstructionDecoder_CppPtr(ctx)->setPreferredVendor(
        VXInstructionSetVendor_CppRepr(preferredVendor));
}

uint64_t VXInstructionDecoder_GetInstructionPointer(
    VXInstructionDecoderContext *ctx)
{
    return VXInstructionDecoder_CppPtr(ctx)->getInstructionPointer();
}

void VXInstructionDecoder_SetInstructionPointer(
    VXInstructionDecoderContext *ctx,
    uint64_t instructionPointer)
{
    VXInstructionDecoder_CppPtr(ctx)->setInstructionPointer(instructionPointer);
}

/* ============================================================================================= */