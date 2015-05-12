/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   :

  Last change     : 29. October 2014

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
#pragma once

#include <type_traits>
#include <istream>
#include "ZyDisDisassemblerTypes.hpp"

namespace Verteron
{

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   The base class for all data-source implementations.
 */
class ZyDisBaseDataSource 
{
private:
    uint8_t m_currentInput;
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
    ZyDisBaseDataSource() { };
public:
    /**
     * @brief   Destructor.
     */
    virtual ~ZyDisBaseDataSource() { };
public:
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position or the @c length field of the @c info parameter. 
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputPeek(ZyDisInstructionInfo &info);
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
    uint8_t inputNext(ZyDisInstructionInfo &info);
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
    T inputNext(ZyDisInstructionInfo &info);
    /**
     * @brief   Returns the current input byte. The current input byte is set everytime the 
     *          @c inputPeek or @c inputNext method is called.
     * @return  The current input byte.
     */
    uint8_t inputCurrent() const;
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

inline uint8_t ZyDisBaseDataSource::inputPeek(ZyDisInstructionInfo &info)
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

inline uint8_t ZyDisBaseDataSource::inputNext(ZyDisInstructionInfo &info)
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
inline T ZyDisBaseDataSource::inputNext(ZyDisInstructionInfo &info)
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

inline uint8_t ZyDisBaseDataSource::inputCurrent() const
{
    return m_currentInput;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   A memory-buffer based data source for the @c ZyDisInstructionDecoder class.
 */
class ZyDisMemoryDataSource : public ZyDisBaseDataSource
{
private:
    const void *m_inputBuffer;
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
    ZyDisMemoryDataSource(const void* buffer, size_t bufferLen)
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

inline uint8_t ZyDisMemoryDataSource::internalInputPeek()
{
    return *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferPos);
}

inline uint8_t ZyDisMemoryDataSource::internalInputNext()
{
    ++m_inputBufferPos;
    return *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferPos - 1);
}

inline bool ZyDisMemoryDataSource::isEndOfInput() const
{
    return (m_inputBufferPos >= m_inputBufferLen);
}

inline uint64_t ZyDisMemoryDataSource::getPosition() const
{
    return m_inputBufferPos;
}

inline bool ZyDisMemoryDataSource::setPosition(uint64_t position)
{
    m_inputBufferPos = position;
    return isEndOfInput();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   A stream based data source for the @c ZyDisInstructionDecoder class.
 */
class ZyDisStreamDataSource : public ZyDisBaseDataSource
{
private:
    std::istream *m_inputStream;
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
    explicit ZyDisStreamDataSource(std::istream *stream)
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

inline uint8_t ZyDisStreamDataSource::internalInputPeek()
{
    if (!m_inputStream)
    {
        return 0;
    }
    return static_cast<uint8_t>(m_inputStream->peek());
}

inline uint8_t ZyDisStreamDataSource::internalInputNext()
{
    if (!m_inputStream)
    {
        return 0;
    }
    return static_cast<uint8_t>(m_inputStream->get());
}

inline bool ZyDisStreamDataSource::isEndOfInput() const
{
    if (!m_inputStream)
    {
        return true;
    }
    // We use good() instead of eof() to make sure the decoding will fail, if an stream internal
    // error occured.
    return !m_inputStream->good();
}

inline uint64_t ZyDisStreamDataSource::getPosition() const
{
    if (!m_inputStream)
    {
        return 0;
    }
    return m_inputStream->tellg();
}

inline bool ZyDisStreamDataSource::setPosition(uint64_t position)
{
    if (!m_inputStream)
    {
        return false;
    }
    m_inputStream->seekg(position);
    return isEndOfInput();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Values that represent a disassembler mode.
 */
enum class ZyDisDisassemblerMode : uint8_t
{
    M16BIT,
    M32BIT,
    M64BIT
};

/**
 * @brief   Values that represent an instruction-set vendor.
 */
enum class ZyDisInstructionSetVendor : uint8_t
{
    ANY,
    INTEL,
    AMD
};

/**
 * @brief   The @c ZyDisInstructionDecoder class decodes x86/x86-64 assembly instructions from a 
 *          given data source.
 */
class ZyDisInstructionDecoder
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
    ZyDisBaseDataSource      *m_dataSource;
    ZyDisDisassemblerMode     m_disassemblerMode;
    ZyDisInstructionSetVendor m_preferredVendor;
    uint64_t               m_instructionPointer;
private:
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position or the @c length field of the @c info parameter. 
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputPeek(ZyDisInstructionInfo &info);
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
    uint8_t inputNext(ZyDisInstructionInfo &info);
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
    T inputNext(ZyDisInstructionInfo &info);
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
     * @param   operand         The @c ZyDisOperandInfo struct that receives the decoded data.
     * @param   registerClass   The register class to use.
     * @param   registerId      The register id.
     * @param   operandSize     The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeRegisterOperand(ZyDisInstructionInfo &info, ZyDisOperandInfo &operand, 
        RegisterClass registerClass, uint8_t registerId, ZyDisDefinedOperandSize operandSize) const;
    /**
     * @brief   Decodes a register/memory operand.
     * @param   info            The instruction info.
     * @param   operand         The @c ZyDisOperandInfo struct that receives the decoded data.
     * @param   registerClass   The register class to use.
     * @param   operandSize     The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeRegisterMemoryOperand(ZyDisInstructionInfo &info, ZyDisOperandInfo &operand,
        RegisterClass registerClass, ZyDisDefinedOperandSize operandSize);
    /**
     * @brief   Decodes an immediate operand.
     * @param   info        The instruction info.
     * @param   operand     The @c ZyDisOperandInfo struct that receives the decoded data.
     * @param   operandSize The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeImmediate(ZyDisInstructionInfo &info, ZyDisOperandInfo &operand, 
        ZyDisDefinedOperandSize operandSize);
    /**
     * @brief   Decodes a displacement operand.
     * @param   info    The instruction info.
     * @param   operand The @c ZyDisOperandInfo struct that receives the decoded data.
     * @param   size    The size of the displacement data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeDisplacement(ZyDisInstructionInfo &info, ZyDisOperandInfo &operand, uint8_t size);
private:
    /**
     * @brief   Decodes the modrm field of the instruction. This method reads an additional 
     *          input byte.
     * @param   The @c ZyDisInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeModrm(ZyDisInstructionInfo &info);
    /**
     * @brief   Decodes the sib field of the instruction. This method reads an additional 
     *          input byte.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeSIB(ZyDisInstructionInfo &info);
    /**
     * @brief   Decodes vex prefix of the instruction. This method takes the current input byte
     *          to determine the vex prefix type and reads one or two additional input bytes
     *          on demand.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeVex(ZyDisInstructionInfo &info);
private:
    /**
     * @brief   Returns the effective operand size.
     * @param   info        The instruction info.
     * @param   operandSize The defined operand size.
     * @return  The effective operand size.
     */
    uint16_t getEffectiveOperandSize(const ZyDisInstructionInfo &info, 
        ZyDisDefinedOperandSize operandSize) const;
    /**
     * @brief   Decodes all instruction operands.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOperands(ZyDisInstructionInfo &info);
    /**
     * @brief   Decodes the specified instruction operand.
     * @param   info        The instruction info.
     * @param   operand     The @c ZyDisOperandInfo struct that receives the decoded data.
     * @param   operandType The defined type of the operand.
     * @param   operandSize The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOperand(ZyDisInstructionInfo &info, ZyDisOperandInfo &operand, 
        ZyDisDefinedOperandType operandType, ZyDisDefinedOperandSize operandSize);
private:
    /**
     * @brief   Resolves the effective operand and address mode of the instruction.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void resolveOperandAndAddressMode(ZyDisInstructionInfo &info) const;
    /**
     * @brief   Calculates the effective REX/VEX.w, r, x, b, l values.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void calculateEffectiveRexVexValues(ZyDisInstructionInfo &info) const;
private:
    /**
     * @brief   Collects and decodes optional instruction prefixes.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodePrefixes(ZyDisInstructionInfo &info);
    /**
     * @brief   Collects and decodes the instruction opcodes using the opcode tree.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOpcode(ZyDisInstructionInfo &info);
public:
    /**
     * @brief   Default constructor.
     */
    ZyDisInstructionDecoder();
    /**
     * @brief   Constructor.
     * @param   input               A reference to the input data source.
     * @param   disassemblerMode    The disasasembler mode.                            
     * @param   preferredVendor     The preferred instruction-set vendor.
     * @param   instructionPointer  The initial instruction pointer.                            
     */
    explicit ZyDisInstructionDecoder(ZyDisBaseDataSource *input, 
        ZyDisDisassemblerMode disassemblerMode = ZyDisDisassemblerMode::M32BIT,
        ZyDisInstructionSetVendor preferredVendor = ZyDisInstructionSetVendor::ANY, 
        uint64_t instructionPointer = 0);
public:
    /**
     * @brief   Decodes the next instruction from the input data source.
     * @param   info    The @c ZyDisInstructionInfo struct that receives the information about the
     *                  decoded instruction.
     * @return  This method returns false, if the current position has exceeded the maximum input 
     *          length.
     *          In all other cases (valid and invalid instructions) the return value is true.
     */
    bool decodeInstruction(ZyDisInstructionInfo &info);
public:
    /**
     * @brief   Returns a pointer to the current data source.
     * @return  A pointer to the current data source.
     */
    ZyDisBaseDataSource* getDataSource() const;
    /**
     * @brief   Sets a new data source.
     * @param   input   A reference to the new input data source.
     */
    void setDataSource(ZyDisBaseDataSource *input);
    /**
     * @brief   Returns the current disassembler mode.
     * @return  The current disassembler mode.
     */
    ZyDisDisassemblerMode getDisassemblerMode() const;
    /**
     * @brief   Sets the current disassembler mode.
     * @param   disassemblerMode    The new disassembler mode.
     */
    void setDisassemblerMode(ZyDisDisassemblerMode disassemblerMode);
    /**
     * @brief   Returns the preferred instruction-set vendor.
     * @return  The preferred instruction-set vendor.
     */
    ZyDisInstructionSetVendor getPreferredVendor() const;
    /**
     * @brief   Sets the preferred instruction-set vendor.
     * @param   preferredVendor The new preferred instruction-set vendor.
     */
    void setPreferredVendor(ZyDisInstructionSetVendor preferredVendor);
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

inline uint8_t ZyDisInstructionDecoder::inputPeek(ZyDisInstructionInfo &info)
{
    if (!m_dataSource)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_dataSource->inputPeek(info);
}

inline uint8_t ZyDisInstructionDecoder::inputNext(ZyDisInstructionInfo &info)
{
    if (!m_dataSource)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_dataSource->inputNext(info);
}

template <typename T>
inline T ZyDisInstructionDecoder::inputNext(ZyDisInstructionInfo &info)
{
    if (!m_dataSource)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_dataSource->inputNext<T>(info);
}

inline uint8_t ZyDisInstructionDecoder::inputCurrent() const
{
    if (!m_dataSource)
    {
        return 0;
    }
    return m_dataSource->inputCurrent();
}

inline ZyDisBaseDataSource* ZyDisInstructionDecoder::getDataSource() const
{
    return m_dataSource;
}

inline void ZyDisInstructionDecoder::setDataSource(ZyDisBaseDataSource *input)
{
    m_dataSource = input;
}

inline ZyDisDisassemblerMode ZyDisInstructionDecoder::getDisassemblerMode() const
{
    return m_disassemblerMode;
}

inline void ZyDisInstructionDecoder::setDisassemblerMode(ZyDisDisassemblerMode disassemblerMode)
{
    m_disassemblerMode = disassemblerMode;
}

inline ZyDisInstructionSetVendor ZyDisInstructionDecoder::getPreferredVendor() const
{
    return m_preferredVendor;
}

inline void ZyDisInstructionDecoder::setPreferredVendor(ZyDisInstructionSetVendor preferredVendor)
{
    m_preferredVendor = preferredVendor;
}

inline uint64_t ZyDisInstructionDecoder::getInstructionPointer() const
{
    return m_instructionPointer;
}

inline void ZyDisInstructionDecoder::setInstructionPointer(uint64_t instructionPointer)
{
    m_instructionPointer = instructionPointer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

}
