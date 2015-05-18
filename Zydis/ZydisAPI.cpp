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

#include "ZydisAPI.h"
#include "ZydisInstructionDecoder.hpp"
#include "ZydisInstructionFormatter.hpp"

static_assert(
    sizeof(ZydisOperandInfo)     == sizeof(Zydis::OperandInfo),
    "struct size mismatch");

static_assert(
    sizeof(ZydisInstructionInfo) == sizeof(Zydis::InstructionInfo), 
    "struct size mismatch");

/* Error Handling =============================================================================== */

static uint32_t g_zydisLastError = ZYDIS_ERROR_SUCCESS;

uint32_t ZydisGetLastError()
{
    return g_zydisLastError;
}

void ZydisSetLastError(uint32_t errorCode)
{
    g_zydisLastError = errorCode;
}

/* Conversion Helper ============================================================================ */

template <typename ContextT, typename InstanceT, typename... InstanceCtorArgsT>
ContextT* ZydisCreateContextInplace(uint8_t contextType, InstanceCtorArgsT... args)
{
    ContextT* context = new (std::nothrow) ContextT;
    if (!context)
    {
        ZydisSetLastError(ZYDIS_ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;
    }
    context->type = contextType;
    context->object = new (std::nothrow) InstanceT(args...);
    if (!context->object)
    {
        delete context;
        ZydisSetLastError(ZYDIS_ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;   
    }
    return context;        
}

template <typename ContextT, typename InstanceT>
ContextT* ZydisCreateContext(uint8_t contextType, InstanceT* instance)
{
    ContextT* context = new (std::nothrow) ContextT;
    if (!context)
    {
        ZydisSetLastError(ZYDIS_ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;
    }
    context->type = contextType;
    context->object = instance;
    return context;        
}

template <typename ContextT, typename InstanceT>
bool ZydisFreeContext(const ContextT* context, uint8_t expectedType)
{
    InstanceT* instance = ZydisCast<ContextT, InstanceT>(context, expectedType);   
    if (!instance)
    {
        return false;
    }
    delete instance;
    delete context;
    return true; 
}

template <typename ContextT, typename InstanceT>
InstanceT* ZydisCast(const ContextT* input, uint8_t expectedType)
{
    if (!input || !input->object || ((input->type & expectedType) != expectedType))
    {
        ZydisSetLastError(ZYDIS_ERROR_INVALID_PARAMETER);
        return nullptr;
    }
    return reinterpret_cast<InstanceT*>(input->object);
}

/* Input ======================================================================================== */

ZydisInputContext* ZydisCreateCustomInput(/* TODO */)
{
    return nullptr;
}

ZydisInputContext* ZydisCreateMemoryInput(const void* buffer, size_t bufferLen)
{
    return ZydisCreateContextInplace<ZydisInputContext, Zydis::MemoryInput>(
        ZYDIS_CONTEXT_INPUT | ZYDIS_CONTEXT_INPUT_MEMORY, buffer, bufferLen);
}

bool ZydisIsEndOfInput(const ZydisInputContext* input, bool* isEndOfInput)
{
    Zydis::BaseInput* instance = 
        ZydisCast<ZydisInputContext, Zydis::BaseInput>(input, ZYDIS_CONTEXT_INPUT);
    if (!instance)
    {
        return false;
    }
    *isEndOfInput = instance->isEndOfInput();
    return true;
}

bool ZydisGetInputPosition(const ZydisInputContext* input, uint64_t* position)
{
    Zydis::BaseInput* instance = 
        ZydisCast<ZydisInputContext, Zydis::BaseInput>(input, ZYDIS_CONTEXT_INPUT);
    if (!instance)
    {
        return false;
    }
    *position = instance->getPosition();   
    return true;
}

bool ZydisSetInputPosition(const ZydisInputContext* input, uint64_t position)
{
    Zydis::BaseInput* instance = 
        ZydisCast<ZydisInputContext, Zydis::BaseInput>(input, ZYDIS_CONTEXT_INPUT);
    if (!instance)
    {
        return false;
    }
    ZydisSetLastError(ZYDIS_ERROR_SUCCESS);
    return instance->setPosition(position);
}

bool ZydisFreeInput(const ZydisInputContext* input)
{
    return ZydisFreeContext<ZydisInputContext, Zydis::BaseInput>(input, ZYDIS_CONTEXT_INPUT);
}

/* InstructionDecoder =========================================================================== */

ZydisInstructionDecoderContext* ZydisCreateInstructionDecoder()
{
    return ZydisCreateContextInplace<ZydisInstructionDecoderContext, Zydis::InstructionDecoder>(
        ZYDIS_CONTEXT_INSTRUCTIONDECODER);
}

bool ZydisDecodeInstruction(const ZydisInstructionDecoderContext* decoder, 
    ZydisInstructionInfo* info)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    ZydisSetLastError(ZYDIS_ERROR_SUCCESS);
    return instance->decodeInstruction(*reinterpret_cast<Zydis::InstructionInfo*>(info));
}

bool ZydisGetDataSource(const ZydisInstructionDecoderContext* decoder,
    ZydisInputContext** input)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    *input = ZydisCreateContext<ZydisInputContext, 
        Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, instance->getDataSource());
    if (!input)
    {
        return false;
    }
    return true;
}

bool ZydisSetDataSource(const ZydisInstructionDecoderContext* decoder,
    ZydisInputContext* input)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    Zydis::BaseInput* object = 
        ZydisCast<ZydisInputContext, Zydis::BaseInput>(input, ZYDIS_CONTEXT_INPUT);
    if (!object)
    {
        return false;
    }
    instance->setDataSource(object);
    return true;    
}

bool ZydisGetDisassemblerMode(const ZydisInstructionDecoderContext* decoder,
    ZydisDisassemblerMode* disassemblerMode)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    *disassemblerMode = static_cast<ZydisDisassemblerMode>(instance->getDisassemblerMode());
    return true;
}

bool ZydisSetDisassemblerMode(const ZydisInstructionDecoderContext* decoder,
    ZydisDisassemblerMode disassemblerMode)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    instance->setDisassemblerMode(static_cast<Zydis::DisassemblerMode>(disassemblerMode));
    return true;    
}

bool ZydisGetPreferredVendor(const ZydisInstructionDecoderContext* decoder,
    ZydisInstructionSetVendor* preferredVendor)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    *preferredVendor = static_cast<ZydisInstructionSetVendor>(instance->getPreferredVendor());
    return true;    
}

bool ZydisSetPreferredVendor(const ZydisInstructionDecoderContext* decoder,
    ZydisInstructionSetVendor preferredVendor)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    instance->setPreferredVendor(static_cast<Zydis::InstructionSetVendor>(preferredVendor));
    return true;  
}

 bool ZydisGetInstructionPointer(const ZydisInstructionDecoderContext* decoder,
    uint64_t* instructionPointer)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    *instructionPointer = instance->getInstructionPointer();
    return true; 
}

bool ZydisSetInstructionPointer(const ZydisInstructionDecoderContext* decoder,
    uint64_t instructionPointer)
{
    Zydis::InstructionDecoder* instance = 
        ZydisCast<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);
    if (!instance)
    {
        return false;
    }
    instance->setInstructionPointer(instructionPointer);
    return true;  
}

bool ZydisFreeInstructionDecoder(const ZydisInstructionDecoderContext* decoder)
{
    return ZydisFreeContext<
        ZydisInstructionDecoderContext, Zydis::InstructionDecoder>(
        decoder, ZYDIS_CONTEXT_INSTRUCTIONDECODER);  
}

/* InstructionFormatter ========================================================================= */

ZydisInstructionFormatterContext* ZydisCreateCustomInstructionFormatter(/* TODO */)
{
    return nullptr;
}

ZydisInstructionFormatterContext* ZydisCreateIntelInstructionFormatter()
{
    return ZydisCreateContextInplace<ZydisInstructionFormatterContext, 
        Zydis::IntelInstructionFormatter>(
        ZYDIS_CONTEXT_INSTRUCTIONFORMATTER | ZYDIS_CONTEXT_INSTRUCTIONFORMATTER_INTEL);    
}

bool ZydisFormatInstruction(const ZydisInstructionFormatterContext* formatter,
    const ZydisInstructionInfo* info, const char** instructionText)
{
    Zydis::IntelInstructionFormatter* instance = 
        ZydisCast<ZydisInstructionFormatterContext, 
        Zydis::IntelInstructionFormatter>(formatter, ZYDIS_CONTEXT_INSTRUCTIONFORMATTER);
    if (!instance)
    {
        return false;
    } 
    *instructionText = 
        instance->formatInstruction(*reinterpret_cast<const Zydis::InstructionInfo*>(info));
    return true;
}

bool ZydisGetSymbolResolver(const ZydisInstructionFormatterContext* formatter,
    ZydisSymbolResolverContext** resolver)
{
    Zydis::IntelInstructionFormatter* instance = 
        ZydisCast<ZydisInstructionFormatterContext, 
        Zydis::IntelInstructionFormatter>(formatter, ZYDIS_CONTEXT_INSTRUCTIONFORMATTER);
    if (!instance)
    {
        return false;
    } 
    *resolver = ZydisCreateContext<ZydisSymbolResolverContext, 
        Zydis::BaseSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER, instance->getSymbolResolver());
    if (!resolver)
    {
        return false;
    }
    return true;
}

bool ZydisSetSymbolResolver(const ZydisInstructionFormatterContext* formatter,
    ZydisSymbolResolverContext* resolver)
{
    Zydis::IntelInstructionFormatter* instance = 
        ZydisCast<ZydisInstructionFormatterContext, 
        Zydis::IntelInstructionFormatter>(formatter, ZYDIS_CONTEXT_INSTRUCTIONFORMATTER);
    if (!instance)
    {
        return false;
    } 
    Zydis::BaseSymbolResolver* object = 
        ZydisCast<ZydisSymbolResolverContext, 
        Zydis::BaseSymbolResolver>(resolver, ZYDIS_CONTEXT_SYMBOLRESOLVER);
    if (!object)
    {
        return false;
    }
    instance->setSymbolResolver(object);
    return true;
}

bool ZydisFreeInstructionFormatter(const ZydisInstructionFormatterContext* formatter)
{
    return ZydisFreeContext<
        ZydisInstructionFormatterContext, Zydis::BaseInstructionFormatter>(
        formatter, ZYDIS_CONTEXT_INSTRUCTIONFORMATTER);
}

/* SymbolResolver =============================================================================== */

ZYDIS_EXPORT ZydisSymbolResolverContext* ZydisCreateCustomSymbolResolver(/*TODO*/);

ZYDIS_EXPORT ZydisSymbolResolverContext* ZydisCreateExactSymbolResolver();

ZYDIS_EXPORT bool ZydisResolveSymbol(const ZydisSymbolResolverContext* resolver, 
    const ZydisInstructionInfo* info, uint64_t address, const char** symbol, uint64_t* offset);

ZYDIS_EXPORT bool ZydisExactSymbolResolverContainsSymbol(
    const ZydisSymbolResolverContext* resolver, uint64_t address, bool* containsSymbol);

ZYDIS_EXPORT bool ZydisExactSymbolResolverSetSymbol(const ZydisSymbolResolverContext* resolver, 
    uint64_t address, const char* symbol);

ZYDIS_EXPORT bool ZydisExactSymbolResolverRemoveSymbol(const ZydisSymbolResolverContext* resolver, 
    uint64_t address);

ZYDIS_EXPORT bool ZydisExactSymbolResolverClear(const ZydisSymbolResolverContext* resolver);

ZYDIS_EXPORT bool ZydisFreeSymbolResolver(const ZydisSymbolResolverContext* resolver);

/* ============================================================================================== */