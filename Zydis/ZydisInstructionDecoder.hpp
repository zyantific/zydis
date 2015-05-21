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

#ifndef _ZYDIS_INSTRUCTIONDECODER_HPP_
#define _ZYDIS_INSTRUCTIONDECODER_HPP_

#include <type_traits>
#include <istream>
#include "ZydisTypes.hpp"

namespace Zydis
{

/* BaseInput ==================================================================================== */

/**
 * @brief   The base class for all data-source implementations.
 */
class BaseInput 
{
friend class InstructionDecoder;
private:
    uint8_t m_currentInput;
private:
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position or the @c length field of the @c info parameter. 
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputPeek(InstructionInfo& info);
    /**
     * @brief   Reads the next byte from the data source. This method increases the current
     *          input position and the @c length field of the @c info parameter. 
     *          This method also appends the new byte to to @c data field of the @c info 
     *          parameter.
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputNext(InstructionInfo& info);
    /**
     * @brief   Reads the next byte(s) from the data source. This method increases the current
     *          input position and the @c length field of the @c info parameter. 
     *          This method also appends the new byte(s) to to @c data field of the @c info 
     *          parameter.
     * @param   info    The instruction info.
     * @return  The current input data. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    template <typename T>
    T inputNext(InstructionInfo& info);
    /**
     * @brief   Returns the current input byte. The current input byte is set everytime the 
     *          @c inputPeek or @c inputNext method is called.
     * @return  The current input byte.
     */
    uint8_t inputCurrent() const;
protected:
    /**
     * @brief   Override this method in your custom data source implementations.
     *          Reads the next byte from the data source. This method increases the current
     *          input position by one.  
     * @return  The current input byte.
     */
    virtual uint8_t internalInputPeek() = 0;
    /**
     * @brief   Override this method in your custom data source implementations.
     *          Reads the next byte from the data source. This method does NOT increase the 
     *          current input position.
     * @return  The current input byte.
     */
    virtual uint8_t internalInputNext() = 0;
protected:
    /**
     * @brief   Default constructor.
     */
    BaseInput() { };
public:
    /**
     * @brief   Destructor.
     */
    virtual ~BaseInput() { };
public:
    /**
     * @brief   Override this method in your custom data source implementations.
     *          Signals, if the end of the data source is reached.
     * @return  True if end of input, false if not.
     */
    virtual bool isEndOfInput() const = 0;
    /**
     * @brief   Override this method in your custom data source implementations.
     *          Returns the current input position.
     * @return  The current input position.
     */
    virtual uint64_t getPosition() const = 0;
    /**
     * @brief   Override this method in your custom data source implementations.
     *          Sets a new input position.
     * @param   position    The new input position.
     * @return  Returns false, if the new position exceeds the maximum input length.
     */
    virtual bool setPosition(uint64_t position) = 0;
};

inline uint8_t BaseInput::inputPeek(InstructionInfo& info)
{
    if (info.length == 15)
    {
        info.flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (isEndOfInput())
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    m_currentInput = internalInputPeek();
    return m_currentInput;
}

inline uint8_t BaseInput::inputNext(InstructionInfo& info)
{
    if (info.length == 15)
    {
        info.flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (isEndOfInput())
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    m_currentInput = internalInputNext();
    info.data[info.length] = m_currentInput;
    info.length++;
    return m_currentInput;
}

template <typename T>
inline T BaseInput::inputNext(InstructionInfo& info)
{
    static_assert(std::is_integral<T>::value, "integral type required");
    T result = 0;
    for (unsigned i = 0; i < (sizeof(T) / sizeof(uint8_t)); ++i)
    {
        T b = inputNext(info);
        if (!b && (info.flags & IF_ERROR_MASK))
        {
            return 0;
        }
        result |= (b << (i * 8));   
    }
    return result;
}

inline uint8_t BaseInput::inputCurrent() const
{
    return m_currentInput;
}

/* MemoryInput ================================================================================== */

/**
 * @brief   A memory-buffer based data source for the @c InstructionDecoder class.
 */
class MemoryInput : public BaseInput
{
private:
    const void* m_inputBuffer;
    uint64_t    m_inputBufferLen;
    uint64_t    m_inputBufferPos;
protected:
    /**
     * @brief   Reads the next byte from the data source. This method increases the current
     *          input position by one.  
     * @return  The current input byte.
     */
    uint8_t internalInputPeek() override;
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position.
     * @return  The current input byte.
     */
    uint8_t internalInputNext() override;
public:
    /**
     * @brief   Constructor.
     * @param   buffer      The input buffer.
     * @param   bufferLen   The length of the input buffer.
     */
    MemoryInput(const void* buffer, size_t bufferLen)
        : m_inputBuffer(buffer)
        , m_inputBufferLen(bufferLen)
        , m_inputBufferPos(0) { };
public:
    /**
     * @brief   Signals, if the end of the data source is reached.
     * @return  True if end of input, false if not.
     */
    bool isEndOfInput() const override;
    /**
     * @brief   Returns the current input position.
     * @return  The current input position.
     */
    uint64_t getPosition() const override;
    /**
     * @brief   Sets a new input position.
     * @param   position    The new input position.
     * @return  Returns false, if the new position exceeds the maximum input length.
     */
    bool setPosition(uint64_t position) override;
};

inline uint8_t MemoryInput::internalInputPeek()
{
    return *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferPos);
}

inline uint8_t MemoryInput::internalInputNext()
{
    ++m_inputBufferPos;
    return *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferPos - 1);
}

inline bool MemoryInput::isEndOfInput() const
{
    return (m_inputBufferPos >= m_inputBufferLen);
}

inline uint64_t MemoryInput::getPosition() const
{
    return m_inputBufferPos;
}

inline bool MemoryInput::setPosition(uint64_t position)
{
    m_inputBufferPos = position;
    return isEndOfInput();
}

/* StreamInput ================================================================================== */

/**
 * @brief   A stream based data source for the @c InstructionDecoder class.
 */
class StreamInput : public BaseInput
{
private:
    std::istream* m_inputStream;
protected:
    /**
     * @brief   Reads the next byte from the data source. This method increases the current
     *          input position by one.  
     * @return  The current input byte.
     */
    uint8_t internalInputPeek() override;
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position.
     * @return  The current input byte.
     */
    uint8_t internalInputNext() override;
public:
    /**
     * @brief   Constructor.
     * @param   stream  The input stream.
     */
    explicit StreamInput(std::istream* stream)
        : m_inputStream(stream) { };
public:
    /**
     * @brief   Signals, if the end of the data source is reached.
     * @return  True if end of input, false if not.
     */
    bool isEndOfInput() const override;
    /**
     * @brief   Returns the current input position.
     * @return  The current input position.
     */
    uint64_t getPosition() const override;
    /**
     * @brief   Sets a new input position.
     * @param   position    The new input position.
     * @return  Returns false, if the new position exceeds the maximum input length.
     */
    bool setPosition(uint64_t position) override;
};

inline uint8_t StreamInput::internalInputPeek()
{
    if (!m_inputStream)
    {
        return 0;
    }
    return static_cast<uint8_t>(m_inputStream->peek());
}

inline uint8_t StreamInput::internalInputNext()
{
    if (!m_inputStream)
    {
        return 0;
    }
    return static_cast<uint8_t>(m_inputStream->get());
}

inline bool StreamInput::isEndOfInput() const
{
    if (!m_inputStream)
    {
        return true;
    }
    // We use good() instead of eof() to make sure the decoding will fail, if an stream internal
    // error occured.
    return !m_inputStream->good();
}

inline uint64_t StreamInput::getPosition() const
{
    if (!m_inputStream)
    {
        return 0;
    }
    return m_inputStream->tellg();
}

inline bool StreamInput::setPosition(uint64_t position)
{
    if (!m_inputStream)
    {
        return false;
    }
    m_inputStream->seekg(position);
    return isEndOfInput();
}

/* Enums ======================================================================================== */

/**
 * @brief   Values that represent a disassembler mode.
 */
enum class DisassemblerMode : uint8_t
{
    M16BIT,
    M32BIT,
    M64BIT
};

/**
 * @brief   Values that represent an instruction-set vendor.
 */
enum class InstructionSetVendor : uint8_t
{
    ANY,
    INTEL,
    AMD
};

/* InstructionDecoder =========================================================================== */

/**
 * @brief   The @c InstructionDecoder class decodes x86/x86-64 assembly instructions from a 
 *          given data source.
 */
class InstructionDecoder
{
private:
    enum class RegisterClass : uint8_t
    {
        GENERAL_PURPOSE,
        MMX,
        CONTROL,
        DEBUG,
        SEGMENT,
        XMM
    };
private:
    BaseInput*           m_input;
    DisassemblerMode     m_disassemblerMode;
    InstructionSetVendor m_preferredVendor;
    uint64_t             m_instructionPointer;
private:
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position or the @c length field of the @c info parameter. 
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputPeek(InstructionInfo& info);
    /**
     * @brief   Reads the next byte from the data source. This method increases the current
     *          input position and the @c length field of the @info parameter. 
     *          This method also appends the new byte to to @c data field of the @c info 
     *          parameter.
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputNext(InstructionInfo& info);
    /**
     * @brief   Reads the next byte(s) from the data source. This method increases the current
     *          input position and the @c length field of the @info parameter. 
     *          This method also appends the new byte(s) to to @c data field of the @c info 
     *          parameter.
     * @param   info    The instruction info.
     * @return  The current input data. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    template <typename T>
    T inputNext(InstructionInfo& info);
    /**
     * @brief   Returns the current input byte. The current input byte is set everytime the 
     *          @c inputPeek or @c inputNext method is called.
     * @return  The current input byte.
     */
    uint8_t inputCurrent() const;
private:
    /**
     * @brief   Decodes a register operand.
     * @param   info            The instruction info.
     * @param   operand         The @c OperandInfo struct that receives the decoded data.
     * @param   registerClass   The register class to use.
     * @param   registerId      The register id.
     * @param   operandSize     The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeRegisterOperand(InstructionInfo& info, OperandInfo& operand, 
        RegisterClass registerClass, uint8_t registerId, DefinedOperandSize operandSize) const;
    /**
     * @brief   Decodes a register/memory operand.
     * @param   info            The instruction info.
     * @param   operand         The @c OperandInfo struct that receives the decoded data.
     * @param   registerClass   The register class to use.
     * @param   operandSize     The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeRegisterMemoryOperand(InstructionInfo& info, OperandInfo& operand,
        RegisterClass registerClass, DefinedOperandSize operandSize);
    /**
     * @brief   Decodes an immediate operand.
     * @param   info        The instruction info.
     * @param   operand     The @c OperandInfo struct that receives the decoded data.
     * @param   operandSize The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeImmediate(InstructionInfo& info, OperandInfo& operand, 
        DefinedOperandSize operandSize);
    /**
     * @brief   Decodes a displacement operand.
     * @param   info    The instruction info.
     * @param   operand The @c OperandInfo struct that receives the decoded data.
     * @param   size    The size of the displacement data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeDisplacement(InstructionInfo& info, OperandInfo& operand, uint8_t size);
private:
    /**
     * @brief   Decodes the modrm field of the instruction. This method reads an additional 
     *          input byte.
     * @param   The @c InstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeModrm(InstructionInfo& info);
    /**
     * @brief   Decodes the sib field of the instruction. This method reads an additional 
     *          input byte.
     * @param   info    The @c InstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeSIB(InstructionInfo& info);
    /**
     * @brief   Decodes vex prefix of the instruction. This method takes the current input byte
     *          to determine the vex prefix type and reads one or two additional input bytes
     *          on demand.
     * @param   info    The @c InstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeVex(InstructionInfo& info);
private:
    /**
     * @brief   Returns the effective operand size.
     * @param   info        The instruction info.
     * @param   operandSize The defined operand size.
     * @return  The effective operand size.
     */
    uint16_t getEffectiveOperandSize(const InstructionInfo& info, 
        DefinedOperandSize operandSize) const;
    /**
     * @brief   Decodes all instruction operands.
     * @param   info    The @c InstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOperands(InstructionInfo& info);
    /**
     * @brief   Decodes the specified instruction operand.
     * @param   info        The instruction info.
     * @param   operand     The @c OperandInfo struct that receives the decoded data.
     * @param   operandType The defined type of the operand.
     * @param   operandSize The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOperand(InstructionInfo& info, OperandInfo& operand, 
        DefinedOperandType operandType, DefinedOperandSize operandSize);
private:
    /**
     * @brief   Resolves the effective operand and address mode of the instruction.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c InstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void resolveOperandAndAddressMode(InstructionInfo& info) const;
    /**
     * @brief   Calculates the effective REX/VEX.w, r, x, b, l values.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c InstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void calculateEffectiveRexVexValues(InstructionInfo& info) const;
private:
    /**
     * @brief   Collects and decodes optional instruction prefixes.
     * @param   info    The @c InstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodePrefixes(InstructionInfo& info);
    /**
     * @brief   Collects and decodes the instruction opcodes using the opcode tree.
     * @param   info    The @c InstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOpcode(InstructionInfo& info);
public:
    /**
     * @brief   Default constructor.
     */
    InstructionDecoder();
    /**
     * @brief   Constructor.
     * @param   input               A reference to the input data source.
     * @param   disassemblerMode    The disasasembler mode.                            
     * @param   preferredVendor     The preferred instruction-set vendor.
     * @param   instructionPointer  The initial instruction pointer.                            
     */
    explicit InstructionDecoder(BaseInput* input, 
        DisassemblerMode disassemblerMode = DisassemblerMode::M32BIT,
        InstructionSetVendor preferredVendor = InstructionSetVendor::ANY, 
        uint64_t instructionPointer = 0);
public:
    /**
     * @brief   Decodes the next instruction from the input data source.
     * @param   info    The @c InstructionInfo struct that receives the information about the
     *                  decoded instruction.
     * @return  This method returns false, if the current position has exceeded the maximum input 
     *          length.
     *          In all other cases (valid and invalid instructions) the return value is true.
     */
    bool decodeInstruction(InstructionInfo& info);
public:
    /**
     * @brief   Returns a pointer to the current data source.
     * @return  A pointer to the current data source.
     */
    BaseInput* getDataSource() const;
    /**
     * @brief   Sets a new data source.
     * @param   input   A reference to the new input data source.
     */
    void setDataSource(BaseInput* input);
    /**
     * @brief   Returns the current disassembler mode.
     * @return  The current disassembler mode.
     */
    DisassemblerMode getDisassemblerMode() const;
    /**
     * @brief   Sets the current disassembler mode.
     * @param   disassemblerMode    The new disassembler mode.
     */
    void setDisassemblerMode(DisassemblerMode disassemblerMode);
    /**
     * @brief   Returns the preferred instruction-set vendor.
     * @return  The preferred instruction-set vendor.
     */
    InstructionSetVendor getPreferredVendor() const;
    /**
     * @brief   Sets the preferred instruction-set vendor.
     * @param   preferredVendor The new preferred instruction-set vendor.
     */
    void setPreferredVendor(InstructionSetVendor preferredVendor);
    /**
     * @brief   Returns the current instruction pointer.
     * @return  The current instruction pointer.
     */
    uint64_t getInstructionPointer() const;
    /**
     * @brief   Sets a new instruction pointer.
     * @param   instructionPointer  The new instruction pointer.
     */
    void setInstructionPointer(uint64_t instructionPointer);
};

inline uint8_t InstructionDecoder::inputPeek(InstructionInfo& info)
{
    if (!m_input)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_input->inputPeek(info);
}

inline uint8_t InstructionDecoder::inputNext(InstructionInfo& info)
{
    if (!m_input)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_input->inputNext(info);
}

template <typename T>
inline T InstructionDecoder::inputNext(InstructionInfo& info)
{
    if (!m_input)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_input->inputNext<T>(info);
}

inline uint8_t InstructionDecoder::inputCurrent() const
{
    if (!m_input)
    {
        return 0;
    }
    return m_input->inputCurrent();
}

inline BaseInput *InstructionDecoder::getDataSource() const
{
    return m_input;
}

inline void InstructionDecoder::setDataSource(BaseInput* input)
{
    m_input = input;
}

inline DisassemblerMode InstructionDecoder::getDisassemblerMode() const
{
    return m_disassemblerMode;
}

inline void InstructionDecoder::setDisassemblerMode(DisassemblerMode disassemblerMode)
{
    m_disassemblerMode = disassemblerMode;
}

inline InstructionSetVendor InstructionDecoder::getPreferredVendor() const
{
    return m_preferredVendor;
}

inline void InstructionDecoder::setPreferredVendor(InstructionSetVendor preferredVendor)
{
    m_preferredVendor = preferredVendor;
}

inline uint64_t InstructionDecoder::getInstructionPointer() const
{
    return m_instructionPointer;
}

inline void InstructionDecoder::setInstructionPointer(uint64_t instructionPointer)
{
    m_instructionPointer = instructionPointer;
}

/* ============================================================================================== */

}

#endif /* _ZYDIS_INSTRUCTIONDECODER_HPP_ */