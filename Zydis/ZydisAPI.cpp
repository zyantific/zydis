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

/* Static Checks ================================================================================ */

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

typedef enum _ZydisClassType
{
    ZYDIS_CONTEXT_INPUT                         = 0x00000080,
    ZYDIS_CONTEXT_INPUT_CUSTOM                  = ZYDIS_CONTEXT_INPUT                | 0x00000001,
    ZYDIS_CONTEXT_INPUT_MEMORY                  = ZYDIS_CONTEXT_INPUT                | 0x00000002,
    ZYDIS_CONTEXT_INSTRUCTIONDECODER            = 0x00000040,
    ZYDIS_CONTEXT_INSTRUCTIONFORMATTER          = 0x00000020,
    ZYDIS_CONTEXT_INSTRUCTIONFORMATTER_CUSTOM   = ZYDIS_CONTEXT_INSTRUCTIONFORMATTER | 0x00000001,
    ZYDIS_CONTEXT_INSTRUCTIONFORMATTER_INTEL    = ZYDIS_CONTEXT_INSTRUCTIONFORMATTER | 0x00000002,
    ZYDIS_CONTEXT_SYMBOLRESOLVER                = 0x00000010,
    ZYDIS_CONTEXT_SYMBOLRESOLVER_CUSTOM         = ZYDIS_CONTEXT_SYMBOLRESOLVER       | 0x00000001,
    ZYDIS_CONTEXT_SYMBOLRESOLVER_EXACT          = ZYDIS_CONTEXT_SYMBOLRESOLVER       | 0x00000002
} ZydisClassType;

/**
 * @brief   This helper class extends a zydis class with a type field. It is used by the C-bindings 
 *          to check type correctness for input parameters.
 * @param   ZydisClassT The zydis class type.
 */
#pragma pack(push, 1)    
template <typename ZydisClassT>
class ZydisClassEx final
{
private:
    using FullClassT = ZydisClassEx<ZydisClassT>;
public:
    uint32_t type;
    uint32_t align;
    std::conditional_t<std::is_abstract<ZydisClassT>::value, char, ZydisClassT> instance;
public:
    /**
     * @brief   Constructor
     * @param   InstanceCtorArgsT   The argument types for the constructor of the zydis class. 
     * @param   classType           The type of the zydis class.
     * @param   args...             The arguments for the constructor of the zydis class.
     */
    template<
        typename ZydisClassTT=ZydisClassT, 
        std::enable_if_t<!std::is_abstract<ZydisClassTT>::value, int> = 0, 
        typename... InstanceCtorArgsT>
    ZydisClassEx(uint32_t classType, InstanceCtorArgsT... args) 
        : type(classType)
        , align(0)
        , instance(args...) { };
public:
    /**
     * @brief   Returns the class type.
     * @return  The assigned class type.
     */
    uint32_t getClassType() const
    {
        return type;
    }
    /**
     * @brief   Returns the zydis class instance.
     * @return  Pointer to the zydis class instance.
     */
    ZydisClassT* getInstance()
    {
        return reinterpret_cast<ZydisClassT*>(&instance);
    }
public:
    /**
     * @brief   Casts the given instance to @c ZydisClassEx. 
     * @param   instance    The zydis class instance.   
     * @return  Pointer to the @c ZydisClassEx instance.
     */
    static FullClassT* fromInstance(ZydisClassT* instance)
    {
        return reinterpret_cast<FullClassT*>(
            reinterpret_cast<uintptr_t>(instance) 
                - sizeof(std::declval<FullClassT>().type)
                - sizeof(std::declval<FullClassT>().align));
    }
};
#pragma pack(pop)

/**
 * @brief   Creates a context by constructing a new wrapped zydis class instance.
 * @param   ContextClassT       The context class.
 * @param   ZydisClassT         The zydis class type.
 * @param   ZydisClassCtorArgsT The argument types for the constructor of the zydis class.
 * @param   classType           The type of the zydis class.
 * @param   args...             The arguments for the constructor of the zydis class.
 */
template <typename ContextClassT, typename ZydisClassT, typename... ZydisClassCtorArgsT>
ContextClassT* ZydisCreateContext(uint32_t classType, ZydisClassCtorArgsT... args)
{
    auto instanceEx = new (std::nothrow) ZydisClassEx<ZydisClassT>(classType, args...);
    if (!instanceEx)
    {
        ZydisSetLastError(ZYDIS_ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;
    }
    // Return the original instance as context.
    return reinterpret_cast<ContextClassT*>(instanceEx->getInstance());
}

/**
 * @brief   Retrieves the zydis class instance of the given context.
 * @param   ContextClassT       The context class.
 * @param   ZydisClassT         The zydis class type.
 * @param   expectedType        The expected type of the zydis class.
 */
template <typename ContextClassT, typename ZydisClassT>
ZydisClassT* ZydisRetrieveInstance(uint32_t expectedType, const ContextClassT* context)
{
    auto instanceEx = ZydisClassEx<ZydisClassT>::fromInstance(
        reinterpret_cast<ZydisClassT*>(const_cast<ContextClassT*>(context)));
    if ((instanceEx->getClassType() & expectedType) != expectedType)
    {
        ZydisSetLastError(ZYDIS_ERROR_INVALID_PARAMETER);
        return nullptr;
    }
    // The context points to the same address as the instance. We just need to cast it.
    return reinterpret_cast<ZydisClassT*>(const_cast<ContextClassT*>(context));
}

/**
 * @brief   Creates a context by constructing a new wrapped zydis instance.
 * @param   ContextClassT       The context class.
 * @param   ZydisClassT         The zydis class type.
 * @param   expectedType        The expected type of the zydis class.
 */
template <typename ContextClassT, typename ZydisClassT>
bool ZydisFreeContext(uint32_t expectedType, const ContextClassT* context)
{
    auto instanceEx = ZydisClassEx<ZydisClassT>::fromInstance(
        reinterpret_cast<ZydisClassT*>(const_cast<ContextClassT*>(context)));
    if ((instanceEx->getClassType() & expectedType) != expectedType)
    {
        ZydisSetLastError(ZYDIS_ERROR_INVALID_PARAMETER);
        return false;
    }
    delete instanceEx;
    return true;
}

/* Input ======================================================================================== */

/**
 * @brief   Helper class for custom input implementations.
 */
class ZydisCustomInput : public Zydis::BaseInput
{
private:
    void*                           m_userData;
    ZydisCustomDestructorT          m_cbDestructor;
    ZydisCustomInputPeekT           m_cbPeek;
    ZydisCustomInputNextT           m_cbNext;
    ZydisCustomInputIsEndOfInputT   m_cbIsEndOfInput;
    ZydisCustomInputGetPositionT    m_cbGetPosition;
    ZydisCustomInputSetPositionT    m_cbSetPosition;
protected:
    uint8_t internalInputPeek() override
    {
        return m_cbPeek(m_userData);
    }

    uint8_t internalInputNext() override
    {
        return m_cbNext(m_userData);
    }
public:
    ZydisCustomInput(void* userData, 
        ZydisCustomInputPeekT cbPeek, ZydisCustomInputNextT cbNext, 
        ZydisCustomInputIsEndOfInputT cbIsEndOfInput, ZydisCustomInputGetPositionT cbGetPosition,
        ZydisCustomInputSetPositionT cbSetPosition, ZydisCustomDestructorT cbDestructor)
        : m_userData(userData)
        , m_cbDestructor(cbDestructor)
        , m_cbPeek(cbPeek)
        , m_cbNext(cbNext)
        , m_cbIsEndOfInput(cbIsEndOfInput)
        , m_cbGetPosition(cbGetPosition)
        , m_cbSetPosition(cbSetPosition)
    {
        
    }

    ~ZydisCustomInput() override
    {
        if (m_cbDestructor)
        {
            m_cbDestructor(m_userData);
        }
    }
public:
    bool isEndOfInput() const override
    {
        return m_cbIsEndOfInput(m_userData);
    }

    uint64_t getPosition() const override
    {
        return m_cbGetPosition(m_userData);
    }

    bool setPosition(uint64_t position) override
    {
        return m_cbSetPosition(m_userData, position);
    }
};

ZydisInputContext* ZydisCreateCustomInput(void* userData, 
    ZydisCustomInputPeekT cbPeek, ZydisCustomInputNextT cbNext, 
    ZydisCustomInputIsEndOfInputT cbIsEndOfInput, ZydisCustomInputGetPositionT cbGetPosition,
    ZydisCustomInputSetPositionT cbSetPosition, ZydisCustomDestructorT cbDestructor)
{
    if (!cbPeek || !cbNext || !cbIsEndOfInput || !cbGetPosition || !cbSetPosition)
    {
        ZydisSetLastError(ZYDIS_ERROR_INVALID_PARAMETER);
        return nullptr;
    }
    return ZydisCreateContext<ZydisInputContext, ZydisCustomInput>(ZYDIS_CONTEXT_INPUT_CUSTOM, 
        userData, cbPeek, cbNext, cbIsEndOfInput, cbGetPosition, cbSetPosition, cbDestructor);
}

ZydisInputContext* ZydisCreateMemoryInput(const void* buffer, size_t bufferLen)
{
    return ZydisCreateContext<ZydisInputContext, Zydis::MemoryInput>(
        ZYDIS_CONTEXT_INPUT_MEMORY, buffer, bufferLen);
}

bool ZydisIsEndOfInput(const ZydisInputContext* input, bool* isEndOfInput)
{
    Zydis::BaseInput* instance = 
        ZydisRetrieveInstance<ZydisInputContext, Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, input);
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
        ZydisRetrieveInstance<ZydisInputContext, Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, input);
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
        ZydisRetrieveInstance<ZydisInputContext, Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, input);
    if (!instance)
    {
        return false;
    }
    ZydisSetLastError(ZYDIS_ERROR_SUCCESS);
    return instance->setPosition(position);
}

bool ZydisFreeInput(const ZydisInputContext* input)
{
    return ZydisFreeContext<ZydisInputContext, Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, input);
}

/* InstructionDecoder =========================================================================== */

ZydisInstructionDecoderContext* ZydisCreateInstructionDecoder()
{
    return ZydisCreateContext<ZydisInstructionDecoderContext, Zydis::InstructionDecoder>(
        ZYDIS_CONTEXT_INSTRUCTIONDECODER);
}

ZydisInstructionDecoderContext* ZydisCreateInstructionDecoderEx(
    const ZydisInputContext* input, ZydisDisassemblerMode disassemblerMode,
    ZydisInstructionSetVendor preferredVendor, uint64_t instructionPointer)
{
    Zydis::BaseInput* object = 
        ZydisRetrieveInstance<ZydisInputContext, Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, input);
    if (!object)
    {
        return nullptr;
    }
    return ZydisCreateContext<ZydisInstructionDecoderContext, Zydis::InstructionDecoder>(
        ZYDIS_CONTEXT_INSTRUCTIONDECODER, object, 
        static_cast<Zydis::DisassemblerMode>(disassemblerMode), 
        static_cast<Zydis::InstructionSetVendor>(preferredVendor), instructionPointer);
}

bool ZydisDecodeInstruction(const ZydisInstructionDecoderContext* decoder, 
    ZydisInstructionInfo* info)
{
    Zydis::InstructionDecoder* instance = 
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
    if (!instance)
    {
        return false;
    }
    *input = reinterpret_cast<ZydisInputContext*>(instance->getDataSource());
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
    if (!instance)
    {
        return false;
    }
    Zydis::BaseInput* object = 
        ZydisRetrieveInstance<ZydisInputContext, Zydis::BaseInput>(ZYDIS_CONTEXT_INPUT, input);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
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
        ZydisRetrieveInstance<ZydisInstructionDecoderContext, 
        Zydis::InstructionDecoder>(ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);
    if (!instance)
    {
        return false;
    }
    instance->setInstructionPointer(instructionPointer);
    return true;  
}

bool ZydisFreeInstructionDecoder(const ZydisInstructionDecoderContext* decoder)
{
    return ZydisFreeContext<ZydisInstructionDecoderContext, Zydis::InstructionDecoder>(
        ZYDIS_CONTEXT_INSTRUCTIONDECODER, decoder);  
}

/* InstructionFormatter ========================================================================= */

ZydisInstructionFormatterContext* ZydisCreateCustomInstructionFormatter(/* TODO */)
{
    return nullptr;
}

ZydisInstructionFormatterContext* ZydisCreateIntelInstructionFormatter()
{
    return ZydisCreateContext<ZydisInstructionFormatterContext, 
        Zydis::IntelInstructionFormatter>(ZYDIS_CONTEXT_INSTRUCTIONFORMATTER_INTEL);    
}

bool ZydisFormatInstruction(const ZydisInstructionFormatterContext* formatter,
    const ZydisInstructionInfo* info, const char** instructionText)
{
    Zydis::BaseInstructionFormatter* instance = 
        ZydisRetrieveInstance<ZydisInstructionFormatterContext, 
        Zydis::BaseInstructionFormatter>(ZYDIS_CONTEXT_INSTRUCTIONFORMATTER, formatter);
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
    Zydis::BaseInstructionFormatter* instance = 
        ZydisRetrieveInstance<ZydisInstructionFormatterContext, 
        Zydis::BaseInstructionFormatter>(ZYDIS_CONTEXT_INSTRUCTIONFORMATTER, formatter);
    if (!instance)
    {
        return false;
    } 
    *resolver = reinterpret_cast<ZydisSymbolResolverContext*>(instance->getSymbolResolver());
    if (!resolver)
    {
        return false;
    }
    return true;
}

bool ZydisSetSymbolResolver(const ZydisInstructionFormatterContext* formatter,
    ZydisSymbolResolverContext* resolver)
{
    Zydis::BaseInstructionFormatter* instance = 
        ZydisRetrieveInstance<ZydisInstructionFormatterContext, 
        Zydis::BaseInstructionFormatter>(ZYDIS_CONTEXT_INSTRUCTIONFORMATTER, formatter);
    if (!instance)
    {
        return false;
    } 
    Zydis::BaseSymbolResolver* object = 
        ZydisRetrieveInstance<ZydisSymbolResolverContext, 
        Zydis::BaseSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER, resolver);
    if (!object)
    {
        return false;
    }
    instance->setSymbolResolver(object);
    return true;
}

bool ZydisFreeInstructionFormatter(const ZydisInstructionFormatterContext* formatter)
{
    return ZydisFreeContext<ZydisInstructionFormatterContext, Zydis::BaseInstructionFormatter>(
        ZYDIS_CONTEXT_INSTRUCTIONFORMATTER, formatter);
}

/* SymbolResolver =============================================================================== */

ZydisSymbolResolverContext* ZydisCreateCustomSymbolResolver(/*TODO*/)
{
    return nullptr;
}

ZydisSymbolResolverContext* ZydisCreateExactSymbolResolver()
{
    return ZydisCreateContext<ZydisSymbolResolverContext, Zydis::ExactSymbolResolver>(
        ZYDIS_CONTEXT_SYMBOLRESOLVER_EXACT);
}

bool ZydisResolveSymbol(const ZydisSymbolResolverContext* resolver, 
    const ZydisInstructionInfo* info, uint64_t address, const char** symbol, uint64_t* offset)
{
    Zydis::BaseSymbolResolver* instance = 
        ZydisRetrieveInstance<ZydisSymbolResolverContext, 
        Zydis::BaseSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER, resolver);
    if (!instance)
    {
        return false;
    }    
    *symbol = instance->resolveSymbol(*reinterpret_cast<const Zydis::InstructionInfo*>(info), 
        address, *offset);
    return true;
}

bool ZydisExactSymbolResolverContainsSymbol(
    const ZydisSymbolResolverContext* resolver, uint64_t address, bool* containsSymbol)
{
    Zydis::ExactSymbolResolver* instance = 
        ZydisRetrieveInstance<ZydisSymbolResolverContext, 
        Zydis::ExactSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER_EXACT, resolver);
    if (!instance)
    {
        return false;
    }   
    *containsSymbol = instance->containsSymbol(address);
    return true;
}

bool ZydisExactSymbolResolverSetSymbol(const ZydisSymbolResolverContext* resolver, 
    uint64_t address, const char* name)
{
    Zydis::ExactSymbolResolver* instance = 
        ZydisRetrieveInstance<ZydisSymbolResolverContext, 
        Zydis::ExactSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER_EXACT, resolver);
    if (!instance)
    {
        return false;
    }   
    instance->setSymbol(address, name);
    return true;
}

bool ZydisExactSymbolResolverRemoveSymbol(const ZydisSymbolResolverContext* resolver, 
    uint64_t address)
{
    Zydis::ExactSymbolResolver* instance = 
        ZydisRetrieveInstance<ZydisSymbolResolverContext, 
        Zydis::ExactSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER_EXACT, resolver);
    if (!instance)
    {
        return false;
    }   
    instance->removeSymbol(address);
    return true;    
}

bool ZydisExactSymbolResolverClear(const ZydisSymbolResolverContext* resolver)
{
    Zydis::ExactSymbolResolver* instance = 
        ZydisRetrieveInstance<ZydisSymbolResolverContext, 
        Zydis::ExactSymbolResolver>(ZYDIS_CONTEXT_SYMBOLRESOLVER_EXACT, resolver);
    if (!instance)
    {
        return false;
    }   
    instance->clear();
    return true;
}

bool ZydisFreeSymbolResolver(const ZydisSymbolResolverContext* resolver)
{
    return ZydisFreeContext<ZydisSymbolResolverContext, Zydis::BaseSymbolResolver>(
        ZYDIS_CONTEXT_SYMBOLRESOLVER, resolver);
}

/* ============================================================================================== */