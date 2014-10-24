/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   :

  Last change     : 23. October 2014

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
#include "VXDisassemblerTypes.h"

namespace Verteron
{

namespace Disassembler
{

/**
 * @brief   Values that represent a disassembler mode.
 */
enum class VXDisassemblerMode
{
    M16BIT = 16,
    M32BIT = 32,
    M64BIT = 64
};

/**
 * @brief   Values that represent an instruction vendor.
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
        GENERAL_PURPOSE = 0,
        MMX             = 1,
        CONTROL         = 2,
        DEBUG           = 3,
        SEGMENT         = 4,
        XMM             = 5
    };
private:
    VXDisassemblerMode     m_disassemblerMode;
    VXInstructionSetVendor m_preferredVendor;
    uint64_t               m_instructionPointer;
    const void            *m_inputBuffer;
    size_t                 m_inputBufferLen;
    size_t                 m_inputBufferOffset;
    uint8_t                m_currentInput;
private:
    uint8_t                m_effectiveRexW;
    uint8_t                m_effectiveRexR;
    uint8_t                m_effectiveRexX;
    uint8_t                m_effectiveRexB;
    uint8_t                m_effectiveModrmReg;
    uint8_t                m_effectiveModrmRm;
    bool                   m_effectiveVexL;
private:
    /**
     * @brief   Reads the next byte from the input data source. This method does NOT increase the 
     *          current input offset and the @c length or @c instructionBytes field of the @c info 
     *          parameter. 
     * @param   info    The instruction info.
     * @return  Returns the current input byte. If the result is zero, you should always check
     *          the @flags field of the @c info parameter for the @c IF_ERROR_MASK.
     */
    uint8_t inputPeek(VXInstructionInfo &info);
    /**
     * @brief   Reads the next byte from the input data source. This method increases the current
     *          input offset and the @c length field of the @info parameter. 
     * @param   info    The instruction info.
     * @return  Returns the current input byte. If the result is zero, you should always check
     *          the @flags field of the @c info parameter for the @c IF_ERROR_MASK.
     */
    uint8_t inputNext(VXInstructionInfo &info);
    /**
     * @brief   Reads the next byte(s) from the data source. This method increases the current
     *          input offset and the @c length field of the @info parameter.
     * @tparam  T       Generic integral type parameter.
     * @param   info    The instruction info.
     * @return  Returns the current input byte(s). If the result is zero, you should always check
     *          the @flags field of the @c info parameter for the @c IF_ERROR_MASK.
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
     * @brief   Resolves the effective operand and address mode of the instruction.
     *          This method requires a non-null value in the @c instrDefinition field of the 
     *          @c info struct.
     * @param   info    The @c VXInstructionInfo struct that receives the effective operand and
     *                  address mode.
     */
    void resolveOperandAndAddressMode(VXInstructionInfo &info) const;
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
    /**
     * @brief   Decodes an instruction node.
     * @param   info    The @c VXInstructionInfo struct that receives the decoded data.
     * @param   node    The instruction node.
     * @return  True if it succeeds, false if it fails.
     */
    bool decodeInstructionNode(VXInstructionInfo &info, VXOpcodeTreeNode node);
public:
    /**
     * @brief   Constructor.
     * @param   buffer              The input buffer.
     * @param   bufferLen           The length of the input buffer.
     * @param   disassemblerMode    The disassembler mode.
     * @param   preferredVendor     The preferred instruction-set vendor.
     */
    VXInstructionDecoder(const void *buffer, size_t bufferLen, 
        VXDisassemblerMode disassemblerMode = VXDisassemblerMode::M32BIT,
        VXInstructionSetVendor preferredVendor = VXInstructionSetVendor::ANY);
public:
    /**
     * @brief   Decodes the next instruction from the input data source.
     * @param   info    The @c VXInstructionInfo struct that receives the information about the
     *                  decoded instruction.
     * @return  This method returns false, if the current position has exceeded the maximum input 
     *          length.
     *          In all other cases (valid and invalid instructions) the return value is true.
     */
    bool decodeNextInstruction(VXInstructionInfo &info);
    /**
     * @brief   Decodes a single instruction.
     * @param   info                The @c VXInstructionInfo struct that receives the information 
     *                              about the decoded instruction.
     * @param   buffer              The input buffer.
     * @param   bufferLen           The length of the input buffer.
     * @param   disassemblerMode    The disassembler mode.
     * @param   preferredVendor     The preferred instruction-set vendor.
     * @return  This method returns false, if the current position has exceeded the maximum input 
     *          length.
     *          In all other cases (valid and invalid instructions) the return value is true.
     */
    static bool decodeInstruction(VXInstructionInfo &info, const void *buffer, size_t bufferLen, 
        VXDisassemblerMode disassemblerMode = VXDisassemblerMode::M32BIT,
        VXInstructionSetVendor preferredVendor = VXInstructionSetVendor::ANY);
public:
    /**
     * @brief   Returns the current input position.
     * @return  The current input position.
     */
    uintptr_t getPosition() const;
    /**
     * @brief   Changes the input position.
     * @param   position    The new input position.
     * @return  True if it succeeds, false if the new position exceeds the maximum input length.
     */
    bool setPosition(uintptr_t position);
    /**
     * @brief   Returns the current instruction pointer. The instruction pointer is used to 
     *          properly format relative instructions. 
     * @return  The current instruction pointer.
     */
    uint64_t getInstructionPointer() const;
    /**
     * @brief   Sets the current instruction pointer. The instruction pointer is used to 
     *          properly format relative instructions. 
     * @param   instructionPointer  The new instruction pointer.
     */
    void setInstructionPointer(uint64_t instructionPointer);
};

inline uint8_t VXInstructionDecoder::inputPeek(VXInstructionInfo &info)
{
    if (info.length == 15)
    {
        info.flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (m_inputBufferOffset == m_inputBufferLen)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    m_currentInput = *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferOffset);
    return m_currentInput;
}

inline uint8_t VXInstructionDecoder::inputNext(VXInstructionInfo &info)
{
    if (info.length == 15)
    {
        info.flags |= IF_ERROR_LENGTH;
        return 0;
    }
    if (m_inputBufferOffset == m_inputBufferLen)
    {
        info.flags |= IF_ERROR_END_OF_INPUT;
        return 0;
    }
    m_currentInput = *(static_cast<const uint8_t*>(m_inputBuffer) + m_inputBufferOffset);
    m_inputBufferOffset++;
    info.instructionBytes[info.length] = m_currentInput;
    info.length++;
    return m_currentInput;
}

template <typename T>
inline T VXInstructionDecoder::inputNext(VXInstructionInfo &info)
{
    static_assert(std::is_integral<T>::value, "integral type required");
    T result = 0;
    for (unsigned i = 0; i < (sizeof(T) / sizeof(uint8_t)); i++)
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

inline uint8_t VXInstructionDecoder::inputCurrent() const
{
    return m_currentInput;
}

inline uintptr_t VXInstructionDecoder::getPosition() const
{
    return m_inputBufferOffset;
}

inline bool VXInstructionDecoder::setPosition(uintptr_t position)
{
    if (position < m_inputBufferLen)
    {
        m_inputBufferOffset = position;
        return true;
    } 
    return false;
}

inline uint64_t VXInstructionDecoder::getInstructionPointer() const
{
    return m_instructionPointer;   
}

inline void VXInstructionDecoder::setInstructionPointer(uint64_t instructionPointer)
{
    m_instructionPointer = instructionPointer;    
}

inline bool VXInstructionDecoder::decodeInstruction(VXInstructionInfo &info, const void *buffer, 
    size_t bufferLen, VXDisassemblerMode disassemblerMode, VXInstructionSetVendor preferredVendor)
{
    return VXInstructionDecoder(
        buffer, bufferLen, disassemblerMode, preferredVendor).decodeNextInstruction(info);
}

}

}
