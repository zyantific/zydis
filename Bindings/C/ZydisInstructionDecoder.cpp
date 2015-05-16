/***************************************************************************************************

  Zyan Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : Joel Höner

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

#include "ZydisInstructionDecoder.h"
#include "ZydisInstructionDecoder.hpp"
#include "ZydisTypes.hpp"

/* Helpers ===================================================================================== */

namespace
{

inline Zydis::BaseInput* ZydisBaseInput_CppPtr(
    ZydisBaseInputContext *ctx)
{
    return reinterpret_cast<Zydis::BaseInput*>(ctx);
}

inline const Zydis::BaseInput* ZydisBaseInput_CppPtr(
    const ZydisBaseInputContext *ctx)
{
    return reinterpret_cast<const Zydis::BaseInput*>(ctx);
}

inline ZydisBaseInputContext* ZydisBaseInput_CPtr(
    Zydis::BaseInput *ptr)
{
    return reinterpret_cast<ZydisBaseInputContext*>(ptr);
}

inline const ZydisBaseInputContext* ZydisBaseInput_CPtr(
    const Zydis::BaseInput *ptr)
{
    return reinterpret_cast<const ZydisBaseInputContext*>(ptr);
}

inline Zydis::InstructionInfo* ZydisInstructionInfo_CppPtr(
    ZydisInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Zydis::InstructionInfo), "broken struct");
    return reinterpret_cast<Zydis::InstructionInfo*>(ptr);
}

inline const Zydis::InstructionInfo* ZydisInstructionInfo_CppPtr(
    const ZydisInstructionInfo *ptr)
{
    static_assert(sizeof(*ptr) == sizeof(Zydis::InstructionInfo), "broken struct");
    return reinterpret_cast<const Zydis::InstructionInfo*>(ptr);
}

inline ZydisInstructionDecoderContext* ZydisInstructionDecoder_CPtr(
    Zydis::InstructionDecoder *ptr)
{
    return reinterpret_cast<ZydisInstructionDecoderContext*>(ptr);
}

inline const ZydisInstructionDecoderContext* ZydisInstructionDecoder_CPtr(
    const Zydis::InstructionDecoder *ptr)
{
    return reinterpret_cast<const ZydisInstructionDecoderContext*>(ptr);
}

inline Zydis::InstructionDecoder* ZydisInstructionDecoder_CppPtr(
    ZydisInstructionDecoderContext *ctx)
{
    return reinterpret_cast<Zydis::InstructionDecoder*>(ctx);
}

inline const Zydis::InstructionDecoder* ZydisInstructionDecoder_CppPtr(
    const ZydisInstructionDecoderContext *ctx)
{
    return reinterpret_cast<const Zydis::InstructionDecoder*>(ctx);
}

inline Zydis::DisassemblerMode ZydisDisassemblerMode_CppRepr(
    ZydisDisassemblerMode val)
{
    return static_cast<Zydis::DisassemblerMode>(val);
}

inline ZydisDisassemblerMode ZydisDisassemblerMode_CRepr(
    Zydis::DisassemblerMode val)
{
    return static_cast<ZydisDisassemblerMode>(val);
}

inline Zydis::InstructionSetVendor ZydisInstructionSetVendor_CppRepr(
    ZydisInstructionSetVendor val)
{
    return static_cast<Zydis::InstructionSetVendor>(val);
}

inline ZydisInstructionSetVendor ZydisInstructionSetVendor_CRepr(
    Zydis::InstructionSetVendor val)
{
    return static_cast<ZydisInstructionSetVendor>(val);
}

}

/* BaseInput ============================================================================ */

void ZydisBaseInput_Release(ZydisBaseInputContext *ctx)
{
    delete ZydisBaseInput_CppPtr(ctx);
}

uint8_t ZydisBaseInput_InputPeek(ZydisBaseInputContext *ctx, ZydisInstructionInfo *info)
{
    return ZydisBaseInput_CppPtr(ctx)->inputPeek(*ZydisInstructionInfo_CppPtr(info));
}

uint8_t ZydisBaseInput_InputNext(ZydisBaseInputContext *ctx, ZydisInstructionInfo *info)
{
    return ZydisBaseInput_CppPtr(ctx)->inputNext(*ZydisInstructionInfo_CppPtr(info));
}

uint8_t ZydisBaseInput_InputCurrent(const ZydisBaseInputContext *ctx)
{
    return ZydisBaseInput_CppPtr(ctx)->inputCurrent();
}

bool ZydisBaseInput_IsEndOfInput(const ZydisBaseInputContext *ctx)
{
    return ZydisBaseInput_CppPtr(ctx)->isEndOfInput();
}

uint64_t ZydisBaseInput_GetPosition(const ZydisBaseInputContext *ctx)
{
    return ZydisBaseInput_CppPtr(ctx)->getPosition();
}

bool ZydisBaseInput_SetPosition(ZydisBaseInputContext *ctx, uint64_t position)
{
    return ZydisBaseInput_CppPtr(ctx)->setPosition(position);
}

/* MemoryInput ========================================================================== */

ZydisBaseInputContext* ZydisMemoryInput_Create(const void* buffer, size_t bufferLen)
{
    return reinterpret_cast<ZydisBaseInputContext*>(
        new Zydis::MemoryInput(buffer, bufferLen)); 
}

/* InstructionDecoder ======================================================================== */

ZydisInstructionDecoderContext* ZydisInstructionDecoder_Create()
{
    return reinterpret_cast<ZydisInstructionDecoderContext*>(new Zydis::InstructionDecoder);
}

ZydisInstructionDecoderContext* ZydisInstructionDecoder_CreateEx(
    ZydisBaseInputContext *input, 
    ZydisDisassemblerMode disassemblerMode,
    ZydisInstructionSetVendor preferredVendor, 
    uint64_t instructionPointer)
{
    return ZydisInstructionDecoder_CPtr(new Zydis::InstructionDecoder(
        ZydisBaseInput_CppPtr(input),
        ZydisDisassemblerMode_CppRepr(disassemblerMode), 
        ZydisInstructionSetVendor_CppRepr(preferredVendor),
        instructionPointer));
}

void ZydisInstructionDecoder_Release(ZydisInstructionDecoderContext *ctx)
{
    delete ZydisInstructionDecoder_CppPtr(ctx);
}

bool ZydisInstructionDecoder_DecodeInstruction(
    ZydisInstructionDecoderContext *ctx, ZydisInstructionInfo *info)
{
    return ZydisInstructionDecoder_CppPtr(ctx)->decodeInstruction(
        *ZydisInstructionInfo_CppPtr(info));
}

ZydisBaseInputContext* ZydisInstructionDecoder_GetDataSource(
    const ZydisInstructionDecoderContext *ctx)
{
    return ZydisBaseInput_CPtr(ZydisInstructionDecoder_CppPtr(ctx)->getDataSource());
}

void ZydisInstructionDecoder_SetDataSource(
    ZydisInstructionDecoderContext *ctx, ZydisBaseInputContext *input)
{
    ZydisInstructionDecoder_CppPtr(ctx)->setDataSource(ZydisBaseInput_CppPtr(input));
}

ZydisDisassemblerMode ZydisInstructionDecoder_GetDisassemblerMode(
    ZydisInstructionDecoderContext *ctx)
{
    return ZydisDisassemblerMode_CRepr(ZydisInstructionDecoder_CppPtr(ctx)->getDisassemblerMode());
}

void ZydisInstructionDecoder_SetDisassemblerMode(
    ZydisInstructionDecoderContext *ctx,
    ZydisDisassemblerMode disassemblerMode)
{
    ZydisInstructionDecoder_CppPtr(ctx)->setDisassemblerMode(
        ZydisDisassemblerMode_CppRepr(disassemblerMode));
}

ZydisInstructionSetVendor ZydisInstructionDecoder_GetPreferredVendor(
    const ZydisInstructionDecoderContext *ctx)
{
    return ZydisInstructionSetVendor_CRepr(
        ZydisInstructionDecoder_CppPtr(ctx)->getPreferredVendor());
}

void ZydisInstructionDecoder_SetPreferredVendor(
    ZydisInstructionDecoderContext *ctx,
    ZydisInstructionSetVendor preferredVendor)
{
    return ZydisInstructionDecoder_CppPtr(ctx)->setPreferredVendor(
        ZydisInstructionSetVendor_CppRepr(preferredVendor));
}

uint64_t ZydisInstructionDecoder_GetInstructionPointer(
    ZydisInstructionDecoderContext *ctx)
{
    return ZydisInstructionDecoder_CppPtr(ctx)->getInstructionPointer();
}

void ZydisInstructionDecoder_SetInstructionPointer(
    ZydisInstructionDecoderContext *ctx,
    uint64_t instructionPointer)
{
    ZydisInstructionDecoder_CppPtr(ctx)->setInstructionPointer(instructionPointer);
}

/* ============================================================================================= */