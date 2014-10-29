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
#include "VXDisassemblerTypes.h"

namespace Verteron
{

namespace Disassembler
{

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   The base class for all data-source implementations.
 */
class VXBaseDataSource 
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
    VXBaseDataSource() { };
public:
    /**
     * @brief   Destructor.
     */
    virtual ~VXBaseDataSource() { };
public:
    /**
     * @brief   Reads the next byte from the data source. This method does NOT increase the 
     *          current input position or the @c length field of the @c info parameter. 
     * @param   info    The instruction info.
     * @return  The current input byte. If the result is zero, you should always check the 
     *          @c flags field of the @c info parameter for error flags.
     *          Possible error values are @c IF_ERROR_END_OF_INPUT or @c IF_ERROR_LENGTH.
     */
    uint8_t inputPeek(VXInstructionInfo &info);
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
    uint8_t inputNext(VXInstructionInfo &info);
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
    T inputNext(VXInstructionInfo &info);
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

inline uint8_t VXBaseDataSource::inputPeek(VXInstructionInfo &info)
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

inline uint8_t VXBaseDataSource::inputNext(VXInstructionInfo &info)
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
inline T VXBaseDataSource::inputNext(VXInstructionInfo &info)
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

inline uint8_t VXBaseDataSource::inputCurrent() const
{
    return m_currentInput;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Implements a memory buffer based data source.
 */
class VXMemoryDataSource : public VXBaseDataSource
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
    VXMemoryDataSource(const void* buffer, size_t bufferLen)
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

inline uint8_t VXMemoryDataSource::internalInputPeek()
{
    return *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferPos);
}

inline uint8_t VXMemoryDataSource::internalInputNext()
{
    ++m_inputBufferPos;
    return *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferPos - 1);
}

inline bool VXMemoryDataSource::isEndOfInput() const
{
    return (m_inputBufferPos >= m_inputBufferLen);
}

inline uint64_t VXMemoryDataSource::getPosition() const
{
    return m_inputBufferPos;
}

inline bool VXMemoryDataSource::setPosition(uint64_t position)
{
    m_inputBufferPos = position;
    return isEndOfInput();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Implements a stream based data source.
 */
class VXStreamDataSource : public VXBaseDataSource
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
    explicit VXStreamDataSource(std::istream *stream)
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

inline uint8_t VXStreamDataSource::internalInputPeek()
{
    if (!m_inputStream)
    {
        return 0;
    }
    return m_inputStream->peek();
}

inline uint8_t VXStreamDataSource::internalInputNext()
{
    if (!m_inputStream)
    {
        return 0;
    }
    return m_inputStream->get();
}

inline bool VXStreamDataSource::isEndOfInput() const
{
    if (!m_inputStream)
    {
        return true;
    }
    // We use good() instead of eof() to make sure the decoding will fail, if an stream internal
    // error occured.
    return !m_inputStream->good();
}

inline uint64_t VXStreamDataSource::getPosition() const
{
    if (!m_inputStream)
    {
        return 0;
    }
    return m_inputStream->tellg();
}

inline bool VXStreamDataSource::setPosition(uint64_t position)
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
enum class VXDisassemblerMode
{
    M16BIT,
    M32BIT,
    M64BIT
};

/**
 * @brief   Values that represent an instruction-set vendor.
 */
enum class VXInstructionSetVendor
{
    ANY,
    INTEL,
    AMD
};

/**
 * @brief   The @c VXInstructionDecoder class decodes x86/x86-64 assembly instructions from a 
 *          given data source.
 */
class VXInstructionDecoder
{
private:
    enum class RegisterClass
    {
        GENERAL_PURPOSE,
        MMX,
        CONTROL,
        DEBUG,
        SEGMENT,
        XMM
    };
private:
    VXBaseDataSource      *m_dataSource;
    VXDisassemblerMode     m_disassemblerMode;
    VXInstructionSetVendor m_preferredVendor;
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
    uint8_t inputPeek(VXInstructionInfo &info);
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
    uint8_t inputNext(VXInstructionInfo &info);
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
    T inputNext(VXInstructionInfo &info);
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
     * @param   operand         The @c VXOperandInfo struct that receives the decoded data.
     * @param   registerClass   The register class to use.
     * @param   registerId      The register id.
     * @param   operandSize     The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeRegisterOperand(VXInstructionInfo &info, VXOperandInfo &operand, 
        RegisterClass registerClass, uint8_t registerId, VXDefinedOperandSize operandSize) const;
    /**
     * @brief   Decodes a register/memory operand.
     * @param   info            The instruction info.
     * @param   operand         The @c VXOperandInfo struct that receives the decoded data.
     * @param   registerClass   The register class to use.
     * @param   operandSize     The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeRegisterMemoryOperand(VXInstructionInfo &info, VXOperandInfo &operand,
        RegisterClass registerClass, VXDefinedOperandSize operandSize);
    /**
     * @brief   Decodes an immediate operand.
     * @param   info        The instruction info.
     * @param   operand     The @c VXOperandInfo struct that receives the decoded data.
     * @param   operandSize The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeImmediate(VXInstructionInfo &info, VXOperandInfo &operand, 
        VXDefinedOperandSize operandSize);
    /**
     * @brief   Decodes a displacement operand.
     * @param   info    The instruction info.
     * @param   operand The @c VXOperandInfo struct that receives the decoded data.
     * @param   size    The size of the displacement data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeDisplacement(VXInstructionInfo &info, VXOperandInfo &operand, uint8_t size);
private:
    /**
     * @brief   Decodes the modrm field of the instruction. This method reads an additional 
     *          input byte.
     * @param   The @c VXInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeModrm(VXInstructionInfo &info);
    /**
     * @brief   Decodes the sib field of the instruction. This method reads an additional 
     *          input byte.
     * @param   info    The @c VXInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeSIB(VXInstructionInfo &info);
    /**
     * @brief   Decodes vex prefix of the instruction. This method takes the current input byte
     *          to determine the vex prefix type and reads one or two additional input bytes
     *          on demand.
     * @param   info    The @c VXInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeVex(VXInstructionInfo &info);
private:
    /**
     * @brief   Returns the effective operand size.
     * @param   info        The instruction info.
     * @param   operandSize The defined operand size.
     * @return  The effective operand size.
     */
    uint16_t getEffectiveOperandSize(const VXInstructionInfo &info, 
        VXDefinedOperandSize operandSize) const;
    /**
     * @brief   Decodes all instruction operands.
     * @param   info    The @c VXInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOperands(VXInstructionInfo &info);
    /**
     * @brief   Decodes the specified instruction operand.
     * @param   info        The instruction info.
     * @param   operand     The @c VXOperandInfo struct that receives the decoded data.
     * @param   operandType The defined type of the operand.
     * @param   operandSize The defined size of the operand.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOperand(VXInstructionInfo &info, VXOperandInfo &operand, 
        VXDefinedOperandType operandType, VXDefinedOperandSize operandSize);
private:
    /**
     * @brief   Resolves the effective operand and address mode of the instruction.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c VXInstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void resolveOperandAndAddressMode(VXInstructionInfo &info) const;
    /**
     * @brief   Calculates the effective REX/VEX.w, r, x, b, l values.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c VXInstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void calculateEffectiveRexVexValues(VXInstructionInfo &info) const;
private:
    /**
     * @brief   Collects and decodes optional instruction prefixes.
     * @param   info    The @c VXInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodePrefixes(VXInstructionInfo &info);
    /**
     * @brief   Collects and decodes the instruction opcodes using the opcode tree.
     * @param   info    The @c VXInstructionInfo struct that receives the decoded data.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeOpcode(VXInstructionInfo &info);
public:
    /**
     * @brief   Default constructor.
     */
    VXInstructionDecoder();
    /**
     * @brief   Constructor.
     * @param   input               A reference to the input data source.
     * @param   disassemblerMode    The disasasembler mode.                            
     * @param   preferredVendor     The preferred instruction-set vendor.
     * @param   instructionPointer  The initial instruction pointer.                            
     */
    explicit VXInstructionDecoder(VXBaseDataSource *input, 
        VXDisassemblerMode disassemblerMode = VXDisassemblerMode::M32BIT,
        VXInstructionSetVendor preferredVendor = VXInstructionSetVendor::ANY, 
        uint64_t instructionPointer = 0);
public:
    /**
     * @brief   Decodes the next instruction from the input data source.
     * @param   info    The @c VXInstructionInfo struct that receives the information about the
     *                  decoded instruction.
     * @return  This method returns false, if the current position has exceeded the maximum input 
     *          length.
     *          In all other cases (valid and invalid instructions) the return value is true.
     */
    bool decodeInstruction(VXInstructionInfo &info);
public:
    /**
     * @brief   Returns a pointer to the current data source.
     * @return  A pointer to the current data source.
     */
    VXBaseDataSource* getDataSource() const;
    /**
     * @brief   Sets a new data source.
     * @param   input   A reference to the new input data source.
     */
    void setDataSource(VXBaseDataSource *input);
    /**
     * @brief   Returns the current disassembler mode.
     * @return  The current disassembler mode.
     */
    VXDisassemblerMode getDisassemblerMode() const;
    /**
     * @brief   Sets the current disassembler mode.
     * @param   disassemblerMode    The new disassembler mode.
     */
    void setDisassemblerMode(VXDisassemblerMode disassemblerMode);
    /**
     * @brief   Returns the preferred instruction-set vendor.
     * @return  The preferred instruction-set vendor.
     */
    VXInstructionSetVendor getPreferredVendor() const;
    /**
     * @brief   Sets the preferred instruction-set vendor.
     * @param   preferredVendor The new preferred instruction-set vendor.
     */
    void setPreferredVendor(VXInstructionSetVendor preferredVendor);
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

inline uint8_t VXInstructionDecoder::inputPeek(VXInstructionInfo &info)
{
    if (!m_dataSource)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_dataSource->inputPeek(info);
}

inline uint8_t VXInstructionDecoder::inputNext(VXInstructionInfo &info)
{
    if (!m_dataSource)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_dataSource->inputNext(info);
}

template <typename T>
inline T VXInstructionDecoder::inputNext(VXInstructionInfo &info)
{
    if (!m_dataSource)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    return m_dataSource->inputNext<T>(info);
}

inline uint8_t VXInstructionDecoder::inputCurrent() const
{
    if (!m_dataSource)
    {
        return 0;
    }
    return m_dataSource->inputCurrent();
}

inline VXBaseDataSource* VXInstructionDecoder::getDataSource() const
{
    return m_dataSource;
}

inline void VXInstructionDecoder::setDataSource(VXBaseDataSource *input)
{
    m_dataSource = input;
}

inline VXDisassemblerMode VXInstructionDecoder::getDisassemblerMode() const
{
    return m_disassemblerMode;
}

inline void VXInstructionDecoder::setDisassemblerMode(VXDisassemblerMode disassemblerMode)
{
    m_disassemblerMode = disassemblerMode;
}

inline VXInstructionSetVendor VXInstructionDecoder::getPreferredVendor() const
{
    return m_preferredVendor;
}

inline void VXInstructionDecoder::setPreferredVendor(VXInstructionSetVendor preferredVendor)
{
    m_preferredVendor = preferredVendor;
}

inline uint64_t VXInstructionDecoder::getInstructionPointer() const
{
    return m_instructionPointer;
}

inline void VXInstructionDecoder::setInstructionPointer(uint64_t instructionPointer)
{
    m_instructionPointer = instructionPointer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

}

}
