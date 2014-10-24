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
#include "VXInstructionDecoder.h"
#include <string.h>

namespace Verteron
{

namespace Disassembler
{

bool VXInstructionDecoder::decodeRegisterOperand(VXInstructionInfo &info, VXOperandInfo &operand, 
    RegisterClass registerClass, uint8_t registerId, VXDefinedOperandSize operandSize) const
{
    VXRegister reg = VXRegister::NONE;
    uint16_t size = getEffectiveOperandSize(info, operandSize);
    switch (registerClass)
    {
    case RegisterClass::GENERAL_PURPOSE: 
        switch (size) 
        {
        case 64:
            reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::RAX) + registerId);
            break;
        case 32:
            reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::EAX) + registerId);
            break;
        case 16:
            reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::AX) + registerId);
            break;
        case 8:
            // TODO: Only REX? Or VEX too?
            if (m_disassemblerMode == VXDisassemblerMode::M64BIT && (info.flags & IF_PREFIX_REX)) 
            {
                if (registerId >= 4)
                {
                    reg = static_cast<VXRegister>(
                        static_cast<uint16_t>(VXRegister::SPL) + (registerId - 4));
                } else
                {
                    reg = static_cast<VXRegister>(
                        static_cast<uint16_t>(VXRegister::AL) + registerId);
                }
            } else 
            {
                reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::AL) + registerId);
            }
            break;
        case 0:
            // TODO: Error?
            reg = VXRegister::NONE;
            break;
        default:
            assert(0);
        }
        break;
    case RegisterClass::MMX: 
        reg = 
            static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::MM0) + (registerId & 0x07));
        break;
    case RegisterClass::CONTROL: 
        reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::CR0) + registerId);
        break;
    case RegisterClass::DEBUG: 
        reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::DR0) + registerId);
        break;
    case RegisterClass::SEGMENT: 
        if ((registerId & 7) > 5) 
        {
            info.flags |= IF_ERROR_OPERAND;
            return false;
        }
        reg = static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::ES) + (registerId & 0x07));
        break;
    case RegisterClass::XMM:  
        // TODO: Needs to be tested
        reg = static_cast<VXRegister>(registerId + static_cast<uint16_t>(
            ((size == 256) ? VXRegister::YMM0 : VXRegister::XMM0)));
        break;
    default: 
        assert(0);
    }
    operand.type = VXOperandType::REGISTER;
    operand.base = static_cast<VXRegister>(reg);
    operand.size = size;
    return true;
}

bool VXInstructionDecoder::decodeRegisterMemoryOperand(VXInstructionInfo &info, 
    VXOperandInfo &operand, RegisterClass registerClass, VXDefinedOperandSize operandSize)
{
    assert(info.flags & IF_MODRM);
    // Decode register operand
    if (info.modrm_mod == 3)
    {
        return decodeRegisterOperand(info, operand, registerClass, m_effectiveModrmRm, 
            operandSize);
    }
    // Decode memory operand
    uint8_t offset = 0;
    operand.type = VXOperandType::MEMORY;
    operand.size = getEffectiveOperandSize(info, operandSize);
    switch (info.addressMode)
    {
    case 16:
        {
            static const VXRegister bases[] = { 
                VXRegister::BX, VXRegister::BX, VXRegister::BP, VXRegister::BP, 
                VXRegister::SI, VXRegister::DI, VXRegister::BP, VXRegister::BX };
            static const VXRegister indices[] = { 
                VXRegister::SI, VXRegister::DI, VXRegister::SI, VXRegister::DI,
                VXRegister::NONE, VXRegister::NONE, VXRegister::NONE, VXRegister::NONE };
            operand.base = static_cast<VXRegister>(bases[m_effectiveModrmRm & 0x07]);
            operand.index = static_cast<VXRegister>(indices[m_effectiveModrmRm & 0x07]);
            operand.scale = 0;
            if (info.modrm_mod == 0 && m_effectiveModrmRm == 6) {
                offset = 16;
                operand.base = VXRegister::NONE;
            } else if (info.modrm_mod == 1) {
                offset = 8;
            } else if (info.modrm_mod == 2) {
                offset = 16;
            }
        }
        break;
    case 32:
        operand.base = 
            static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::EAX) + m_effectiveModrmRm);
        switch (info.modrm_mod)
        {
        case 0:
            if (m_effectiveModrmRm == 5)
            {
                operand.base = VXRegister::NONE;
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
        if ((m_effectiveModrmRm & 0x07) == 4)
        {
            if (!decodeSIB(info))
            {
                return false;
            }
            operand.base = 
                static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::EAX) + 
                (info.sib_base | (m_effectiveRexB << 3)));
            operand.index = 
                static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::EAX) + 
                (info.sib_index | (m_effectiveRexX << 3)));
            operand.scale = (1 << info.sib_scale) & ~1;
            if (operand.index == VXRegister::ESP)  
            {
                operand.index = VXRegister::NONE;
                operand.scale = 0;
            } 
            if (operand.base == VXRegister::EBP)
            {
                if (info.modrm_mod == 0)
                {
                    operand.base = VXRegister::NONE;
                } 
                if (info.modrm_mod == 1)
                {
                    offset = 8;
                } else
                {
                    offset = 32;
                }
            }
        } else
        {
            operand.index = VXRegister::NONE;
            operand.scale = 0;    
        }
        break;
    case 64:
        operand.base = 
            static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::RAX) + m_effectiveModrmRm);
        switch (info.modrm_mod)
        {
        case 0:
            if ((m_effectiveModrmRm & 0x07) == 5)
            {
                info.flags |= IF_RELATIVE;
                operand.base = VXRegister::RIP;
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
        if ((m_effectiveModrmRm & 0x07) == 4)
        {
            if (!decodeSIB(info))
            {
                return false;
            }
            operand.base = 
                static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::RAX) + 
                (info.sib_base | (m_effectiveRexB << 3)));
            operand.index = 
                static_cast<VXRegister>(static_cast<uint16_t>(VXRegister::RAX) + 
                (info.sib_index | (m_effectiveRexX << 3)));
            if (operand.index == VXRegister::RSP) 
            {
                operand.index = VXRegister::NONE;
                operand.scale = 0;
            } else
            {
                operand.scale = (1 << info.sib_scale) & ~1;
            }
            if ((operand.base == VXRegister::RBP) || (operand.base == VXRegister::R13))
            {
                if (info.modrm_mod == 0)
                {
                    operand.base = VXRegister::NONE;
                }
                if (info.modrm_mod == 1)
                {
                    offset = 8;    
                } else
                {
                    offset = 32;    
                }
            }
        } else
        {
            operand.index = VXRegister::NONE;
            operand.scale = 0;
        }
        break;
    }
    if (offset)
    {
        if (!decodeDisplacement(info, operand, offset))
        {
            return false;
        }
    } else
    {
        operand.offset = 0;
    }
    return true;
}

bool VXInstructionDecoder::decodeImmediate(VXInstructionInfo &info, VXOperandInfo &operand, 
    VXDefinedOperandSize operandSize)
{
    operand.type = VXOperandType::IMMEDIATE;
    operand.size = getEffectiveOperandSize(info, operandSize);
    switch (operand.size) 
    {
        case 8: 
            operand.lval.ubyte = inputNext(info); 
            break;
        case 16: 
            operand.lval.uword = inputNext<uint16_t>(info); 
            break;
        case 32: 
            operand.lval.udword = inputNext<uint32_t>(info); 
            break;
        case 64: 
            operand.lval.uqword = inputNext<uint64_t>(info); 
            break;
        default: 
            // TODO: Maybe return false instead of assert
            assert(0);
    }
    if (!operand.lval.uqword && (info.flags & IF_ERROR_MASK))
    {
        return false;
    }
    return true;
}

bool VXInstructionDecoder::decodeDisplacement(VXInstructionInfo &info, VXOperandInfo &operand, 
    uint8_t size)
{
    switch (size)
    {
    case 8:
        operand.offset = 8;
        operand.lval.ubyte = inputNext(info);
        break;
    case 16:
        operand.offset = 16;
        operand.lval.uword = inputNext<uint16_t>(info);
        break;
    case 32:
        operand.offset = 32;
        operand.lval.udword = inputNext<uint32_t>(info);
        break;
    case 64:
        operand.offset = 64;
        operand.lval.uqword = inputNext<uint64_t>(info);
        break;
    default:
        // TODO: Maybe return false instead of assert
        assert(0);
    }
    if (!operand.lval.uqword && (info.flags & IF_ERROR_MASK))
    {
        return false;
    }
    return true;
}

bool VXInstructionDecoder::decodeModrm(VXInstructionInfo &info)
{
    if (!(info.flags & IF_MODRM))
    {
        if (!inputNext(info) && (info.flags & IF_ERROR_MASK))
        {
            return false;
        }
        info.flags |= IF_MODRM;
        info.modrm     = inputCurrent();
        info.modrm_mod = (info.modrm >> 6) & 0x03;
        info.modrm_reg = (info.modrm >> 3) & 0x07;
        info.modrm_rm  = (info.modrm >> 0) & 0x07;
    }
    return true;
}

bool VXInstructionDecoder::decodeSIB(VXInstructionInfo &info)
{
    assert(info.flags & IF_MODRM);
    assert((info.modrm_rm & 0x7) == 4);
    if (!(info.flags & IF_SIB))
    {
        if (!inputNext(info) && (info.flags & IF_ERROR_MASK))
        {
            return false;
        }
        info.flags |= IF_SIB;
        info.sib        = inputCurrent();
        info.sib_scale  = (info.sib >> 6) & 0x03;
        info.sib_index  = (info.sib >> 3) & 0x07;
        info.sib_base   = (info.sib >> 0) & 0x07;
    }
    return true;
}

bool VXInstructionDecoder::decodeVex(VXInstructionInfo &info)
{
    if (!(info.flags & IF_PREFIX_VEX))
    {
        info.vex_op = inputCurrent();
        switch (info.vex_op)
        {
        case 0xC4:
            info.vex_b1     = inputNext(info);
            if (!info.vex_b1 || (info.flags & IF_ERROR_MASK))
            {
                return false;
            }
            info.vex_b2     = inputNext(info);
            if (!info.vex_b2 || (info.flags & IF_ERROR_MASK))
            {
                return false;
            }
            info.vex_r      = (info.vex_b1 >> 7) & 0x01;
            info.vex_x      = (info.vex_b1 >> 6) & 0x01;
            info.vex_b      = (info.vex_b1 >> 5) & 0x01;
            info.vex_m_mmmm = (info.vex_b1 >> 0) & 0x1F;
            info.vex_w      = (info.vex_b2 >> 7) & 0x01;
            info.vex_vvvv   = (info.vex_b2 >> 3) & 0x0F;
            info.vex_l      = (info.vex_b2 >> 2) & 0x01;
            info.vex_pp     = (info.vex_b2 >> 0) & 0x03;
            break;
        case 0xC5:
            info.vex_b1     = inputNext(info);
            if (!info.vex_b1 || (info.flags & IF_ERROR_MASK))
            {
                return false;
            }
            info.vex_r      = (info.vex_b1 >> 7) & 0x01;
            info.vex_x      = 1;
            info.vex_b      = 1;
            info.vex_m_mmmm = 1;
            info.vex_w      = 0;
            info.vex_vvvv   = (info.vex_b1 >> 3) & 0x0F;
            info.vex_l      = (info.vex_b1 >> 2) & 0x01;
            info.vex_pp     = (info.vex_b1 >> 0) & 0x03;
            break;
        default:
            assert(0);
        }
        if (info.vex_m_mmmm > 3)
        {
            // TODO: Add proper error flag
            info.flags |= IF_ERROR_MASK;
            return false;
        }
        info.flags |= IF_PREFIX_VEX;
    }
    return true;
}

uint16_t VXInstructionDecoder::getEffectiveOperandSize(const VXInstructionInfo &info, 
    VXDefinedOperandSize operandSize) const
{
    switch (operandSize)
    {
    case VXDefinedOperandSize::NA: 
        return 0;
    case VXDefinedOperandSize::Z: 
        return (info.operandMode == 16) ? 16 : 32;
    case VXDefinedOperandSize::V: 
        return info.operandMode;
    case VXDefinedOperandSize::Y: 
        return (info.operandMode == 16) ? 32 : info.operandMode;
    case VXDefinedOperandSize::X: 
        assert(info.vex_op != 0);
        return m_effectiveVexL ? 
            getEffectiveOperandSize(info, VXDefinedOperandSize::QQ) : 
            getEffectiveOperandSize(info, VXDefinedOperandSize::DQ);
    case VXDefinedOperandSize::RDQ: 
        return (m_disassemblerMode == VXDisassemblerMode::M64BIT) ? 64 : 32;
    case VXDefinedOperandSize::B: 
        return 8;
    case VXDefinedOperandSize::W: 
        return 16;
    case VXDefinedOperandSize::D: 
        return 32;
    case VXDefinedOperandSize::Q: 
        return 64;
    case VXDefinedOperandSize::T: 
        return 80;
    case VXDefinedOperandSize::O: 
        return 12;
    case VXDefinedOperandSize::DQ: 
        return 128;
    case VXDefinedOperandSize::QQ: 
        return 256;
    default: 
        assert(0);
    }
    return 0;
}

bool VXInstructionDecoder::decodeOperands(VXInstructionInfo& info)
{
    assert(info.instrDefinition);
    // Always try to decode the first operand
    if (!decodeOperand(info, info.operand[0], info.instrDefinition->operand[0].type, 
        info.instrDefinition->operand[0].size))
    {
        return false;
    }
    // Decode other operands on demand
    for (unsigned int i = 1; i < 4; ++i)
    {
        if (info.operand[i - 1].type != VXOperandType::NONE)
        {
            if (!decodeOperand(info, info.operand[i], info.instrDefinition->operand[i].type, 
                info.instrDefinition->operand[i].size))
            {
                return false;
            }
        }    
    }
    return true;
}

bool VXInstructionDecoder::decodeOperand(VXInstructionInfo &info, VXOperandInfo &operand, 
    VXDefinedOperandType operandType, VXDefinedOperandSize operandSize)
{
    using namespace Internal;
    operand.type = VXOperandType::NONE;
    switch (operandType)
    {
    case VXDefinedOperandType::NONE:
        break;
    case VXDefinedOperandType::A: 
        operand.type = VXOperandType::POINTER;
        if (info.operandMode == 16)
        {
            operand.size = 32;
            operand.lval.ptr.off = inputNext<uint16_t>(info);
            operand.lval.ptr.seg = inputNext<uint16_t>(info);
        } else {
            operand.size = 48;
            operand.lval.ptr.off = inputNext<uint32_t>(info);
            operand.lval.ptr.seg = inputNext<uint16_t>(info);
        }
        if ((!operand.lval.ptr.off || !operand.lval.ptr.seg) && (info.flags & IF_ERROR_MASK))
        {
            return false;
        }
        break;
    case VXDefinedOperandType::C: 
        return decodeRegisterOperand(info, operand, RegisterClass::CONTROL, m_effectiveModrmReg, 
            operandSize);
    case VXDefinedOperandType::D: 
        return decodeRegisterOperand(info, operand, RegisterClass::DEBUG, m_effectiveModrmReg, 
            operandSize);
    case VXDefinedOperandType::F: 
        // TODO: FAR flag
    case VXDefinedOperandType::M: 
        // ModR/M byte may refer only to a register
        if (info.modrm_mod == 3)
        {
            info.flags |= IF_ERROR_OPERAND;
            return false;
        }
    case VXDefinedOperandType::E: 
        return decodeRegisterMemoryOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 
            operandSize);
    case VXDefinedOperandType::G: 
        return decodeRegisterOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 
            m_effectiveModrmReg, operandSize);
    case VXDefinedOperandType::H: 
        assert(info.vex_op != 0);
        return decodeRegisterOperand(info, operand, RegisterClass::XMM, (0xF & ~info.vex_vvvv), 
            operandSize);
    case VXDefinedOperandType::I: 
        return decodeImmediate(info, operand, operandSize);
    case VXDefinedOperandType::I1: 
        operand.type = VXOperandType::CONSTANT;
        operand.lval.udword = 1;
        break;
    case VXDefinedOperandType::J: 
        if (!decodeImmediate(info, operand, operandSize))
        {
            return false;
        }
        operand.type = VXOperandType::REL_IMMEDIATE;
        info.flags |= IF_RELATIVE;
        break;
    case VXDefinedOperandType::L: 
        {
            assert(info.vex_op != 0);
            uint8_t imm = inputNext(info);
            if (!imm && (info.flags & IF_ERROR_MASK))
            {
                return false;
            }
            uint8_t mask = (m_disassemblerMode == VXDisassemblerMode::M64BIT) ? 0xF : 0x7;
            return decodeRegisterOperand(info, operand, RegisterClass::XMM, mask & (imm >> 4), 
                operandSize);
        }
    case VXDefinedOperandType::MR: 
        return decodeRegisterMemoryOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 
            info.modrm_mod == 3 ? 
            GetComplexOperandRegSize(operandSize) : GetComplexOperandMemSize(operandSize));
    case VXDefinedOperandType::MU: 
        return decodeRegisterMemoryOperand(info, operand, RegisterClass::XMM, 
            info.modrm_mod == 3 ? 
            GetComplexOperandRegSize(operandSize) : GetComplexOperandMemSize(operandSize));
    case VXDefinedOperandType::N: 
        // ModR/M byte may refer only to memory
        if (info.modrm_mod != 3)
        {
            info.flags |= IF_ERROR_OPERAND;
            return false;
        }
    case VXDefinedOperandType::Q: 
        return decodeRegisterMemoryOperand(info, operand, RegisterClass::MMX, operandSize);
    case VXDefinedOperandType::O: 
        operand.type = VXOperandType::MEMORY;
        operand.base = VXRegister::NONE;
        operand.index = VXRegister::NONE;
        operand.scale = 0;
        operand.size = getEffectiveOperandSize(info, operandSize);
        return decodeDisplacement(info, operand, info.addressMode);
    case VXDefinedOperandType::P: 
        return decodeRegisterOperand(info, operand, RegisterClass::MMX, m_effectiveModrmReg, 
            operandSize);
    case VXDefinedOperandType::R: 
        // ModR/M byte may refer only to memory
        if (info.modrm_mod != 3)
        {
            info.flags |= IF_ERROR_OPERAND;
            return false;
        }
        return decodeRegisterMemoryOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 
            operandSize);
    case VXDefinedOperandType::S: 
        return decodeRegisterOperand(info, operand, RegisterClass::SEGMENT, m_effectiveModrmReg, 
            operandSize);
    case VXDefinedOperandType::U: 
        // ModR/M byte may refer only to memory
        if (info.modrm_mod != 3)
        {
            info.flags |= IF_ERROR_OPERAND;
            return false;
        }
     case VXDefinedOperandType::W: 
        return decodeRegisterMemoryOperand(info, operand, RegisterClass::XMM, operandSize);
    case VXDefinedOperandType::V: 
        return decodeRegisterOperand(info, operand, RegisterClass::XMM, m_effectiveModrmReg, 
            operandSize);
    case VXDefinedOperandType::R0: 
    case VXDefinedOperandType::R1: 
    case VXDefinedOperandType::R2: 
    case VXDefinedOperandType::R3: 
    case VXDefinedOperandType::R4: 
    case VXDefinedOperandType::R5: 
    case VXDefinedOperandType::R6: 
    case VXDefinedOperandType::R7: 
        return decodeRegisterOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 
            ((m_effectiveRexB << 3) | (static_cast<uint16_t>(operandType) - 
            static_cast<uint16_t>(VXDefinedOperandType::R0))), operandSize);
    case VXDefinedOperandType::AL: 
    case VXDefinedOperandType::AX: 
    case VXDefinedOperandType::EAX: 
    case VXDefinedOperandType::RAX: 
        return decodeRegisterOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 0, 
            operandSize);
    case VXDefinedOperandType::CL: 
    case VXDefinedOperandType::CX: 
    case VXDefinedOperandType::ECX: 
    case VXDefinedOperandType::RCX: 
        return decodeRegisterOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 1, 
            operandSize);
    case VXDefinedOperandType::DL: 
    case VXDefinedOperandType::DX: 
    case VXDefinedOperandType::EDX: 
    case VXDefinedOperandType::RDX: 
        return decodeRegisterOperand(info, operand, RegisterClass::GENERAL_PURPOSE, 2, 
            operandSize);
    case VXDefinedOperandType::ES: 
    case VXDefinedOperandType::CS: 
    case VXDefinedOperandType::SS: 
    case VXDefinedOperandType::DS: 
    case VXDefinedOperandType::FS: 
    case VXDefinedOperandType::GS: 
        if (m_disassemblerMode == VXDisassemblerMode::M64BIT)
        {
            if ((operandType != VXDefinedOperandType::FS) && 
                (operandType != VXDefinedOperandType::GS))
            {
                info.flags |= IF_ERROR_OPERAND;
                return false;
            }
        }
        operand.type = VXOperandType::REGISTER;
        operand.base = static_cast<VXRegister>((static_cast<uint16_t>(operandType) - 
            static_cast<uint16_t>(VXDefinedOperandType::ES)) + 
            static_cast<uint16_t>(VXRegister::ES));
        operand.size = 16;
        break;
    case VXDefinedOperandType::ST0: 
    case VXDefinedOperandType::ST1: 
    case VXDefinedOperandType::ST2: 
    case VXDefinedOperandType::ST3: 
    case VXDefinedOperandType::ST4: 
    case VXDefinedOperandType::ST5: 
    case VXDefinedOperandType::ST6: 
    case VXDefinedOperandType::ST7: 
        operand.type = VXOperandType::REGISTER;
        operand.base = static_cast<VXRegister>((static_cast<uint16_t>(operandType) - 
            static_cast<uint16_t>(VXDefinedOperandType::ST0)) + 
            static_cast<uint16_t>(VXRegister::ST0));
        operand.size = 80;
        break;
    default: 
        assert(0);
    }
    return true;
}

void VXInstructionDecoder::resolveOperandAndAddressMode(VXInstructionInfo &info) const
{
    assert(info.instrDefinition);
    switch (m_disassemblerMode)
    {
    case VXDisassemblerMode::M16BIT:
        info.operandMode = (info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE) ? 32 : 16;
        info.addressMode = (info.flags & IF_PREFIX_ADDRESS_SIZE_OVERRIDE) ? 32 : 16;
        break;
    case VXDisassemblerMode::M32BIT:
        info.operandMode = (info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE) ? 16 : 32;
        info.addressMode = (info.flags & IF_PREFIX_ADDRESS_SIZE_OVERRIDE) ? 16 : 32;
        break;
    case VXDisassemblerMode::M64BIT:
        if (m_effectiveRexW)
        {
            info.operandMode = 64;
        } else if ((info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE))
        {
            info.operandMode = 16;
        } else
        {
            info.operandMode = (info.instrDefinition->flags & IDF_DEFAULT_64) ? 64 : 32;
        }
        info.addressMode = (info.flags & IF_PREFIX_ADDRESS_SIZE_OVERRIDE) ? 32 : 64;
        break;
    default: 
        assert(0);
    }
}

bool VXInstructionDecoder::decodePrefixes(VXInstructionInfo &info)
{
    bool done = false;
    do
    {
        if (!inputPeek(info) && (info.flags & IF_ERROR_MASK))
        {
            return false;
        }
        switch (inputCurrent())
        {
        case 0xF0:
            info.flags |= IF_PREFIX_LOCK;
            break;
        case 0xF2:
            // REPNZ and REPZ are mutally exclusive. The one that comes later has precedence.
            info.flags |= IF_PREFIX_REPNZ;
            info.flags &= ~IF_PREFIX_REPZ;
            break;
        case 0xF3:
            // REPNZ and REPZ are mutally exclusive. The one that comes later has precedence.
            info.flags |= IF_PREFIX_REPZ;
            info.flags &= ~IF_PREFIX_REPNZ;
            break;
        case 0x2E: 
            info.flags |= IF_PREFIX_SEGMENT;
            info.segmentRegister = VXRegister::CS;
            break;
        case 0x36:
            info.flags |= IF_PREFIX_SEGMENT;
            info.segmentRegister = VXRegister::SS;
            break;
        case 0x3E: 
            info.flags |= IF_PREFIX_SEGMENT;
            info.segmentRegister = VXRegister::DS;
            break;
        case 0x26: 
            info.flags |= IF_PREFIX_SEGMENT;
            info.segmentRegister = VXRegister::ES;
            break;
        case 0x64:
            info.flags |= IF_PREFIX_SEGMENT;
            info.segmentRegister = VXRegister::FS;
            break;
        case 0x65: 
            info.flags |= IF_PREFIX_SEGMENT;
            info.segmentRegister = VXRegister::GS;
            break;
        case 0x66:
            info.flags |= IF_PREFIX_OPERAND_SIZE_OVERRIDE;
            break;
        case 0x67:
            info.flags |= IF_PREFIX_ADDRESS_SIZE_OVERRIDE;
            break;
        default:
            if ((m_disassemblerMode == VXDisassemblerMode::M64BIT) && 
                (inputCurrent() & 0xF0) == 0x40)
            {
                info.flags |= IF_PREFIX_REX;
                info.rex = inputCurrent(); 
            } else
            {
                done = true;
            }
            break;
        }
        // Increase the input offset, if a prefix was found
        if (!done)
        {
            if (!inputNext(info) && (info.flags & IF_ERROR_MASK))
            {
                return false;
            }
        }
    } while (!done);
    // TODO: Add flags for multiple prefixes of the same group
    // Parse REX Prefix
    if (info.flags & IF_PREFIX_REX)
    {
        info.rex_w = (info.rex >> 3) & 0x01;
        info.rex_r = (info.rex >> 2) & 0x01;
        info.rex_x = (info.rex >> 1) & 0x01;
        info.rex_b = (info.rex >> 0) & 0x01;
    }
    return true;
}

bool VXInstructionDecoder::decodeOpcode(VXInstructionInfo &info)
{
    using namespace Internal;
    // Read first opcode byte
    if (!inputNext(info) && (info.flags & IF_ERROR_MASK))
    {
        return false;
    }
    // Update instruction info
    info.opcode[0] = inputCurrent();
    info.opcodeLength = 1;
    // Iterate through opcode tree
    VXOpcodeTreeNode node = GetOpcodeTreeChild(GetOpcodeTreeRoot(), inputCurrent());
    VXOpcodeTreeNodeType nodeType;
    do
    {
        uint16_t index = 0;
        nodeType = GetOpcodeNodeType(node);
        switch (nodeType)
        {
        case VXOpcodeTreeNodeType::INSTRUCTION_DEFINITION: 
            {
                // Decode opcode
                if (!decodeInstructionNode(info, node))
                {
                    return false;
                }
                // Decode operands
                if (!decodeOperands(info))
                {
                    return false;
                }
            }  
            return true;
        case VXOpcodeTreeNodeType::TABLE: 
            // Read next opcode byte
            if (!inputNext(info) && (info.flags & IF_ERROR_MASK))
            {
                return false;
            }
            // Update instruction info
            assert((info.opcodeLength > 0) && (info.opcodeLength < 3));
            info.opcode[info.opcodeLength] = inputCurrent();
            info.opcodeLength++;
            // Set child node index for next iteration
            index = inputCurrent();
            break;
        case VXOpcodeTreeNodeType::MODRM_MOD: 
            // Decode modrm byte
            if (!decodeModrm(info))
            {
                return false;
            }
            index = (info.modrm_mod == 0x3) ? 1 : 0;
            break;
        case VXOpcodeTreeNodeType::MODRM_REG: 
            // Decode modrm byte
            if (!decodeModrm(info))
            {
                return false;
            }
            index = info.modrm_reg;
            break;
        case VXOpcodeTreeNodeType::MODRM_RM: 
            // Decode modrm byte
            if (!decodeModrm(info))
            {
                return false;
            }
            index = info.modrm_rm;
            break;
        case VXOpcodeTreeNodeType::MANDATORY: 
            // Check if there are any prefixes present
            if (info.flags & IF_PREFIX_REPNZ)
            {
                index = 1; // F2
            } else if (info.flags & IF_PREFIX_REPZ)
            {
                index = 2; // F3
            } else if (info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE)
            {
                index = 3; // 66
            }
            if (GetOpcodeTreeChild(node, index) == 0)
            {
                index = 0;
            }
            if (index && (GetOpcodeTreeChild(node, index) != 0))
            {
                // Remove REPNZ and REPZ prefix
                info.flags &= ~IF_PREFIX_REPNZ;
                info.flags &= ~IF_PREFIX_REPZ;
                // Remove OPERAND_SIZE_OVERRIDE prefix, if it was used as mandatory prefix for 
                // the instruction
                if (index == 3)
                {
                    info.flags &= ~IF_PREFIX_OPERAND_SIZE_OVERRIDE;
                }
            }
            break;
        case VXOpcodeTreeNodeType::X87: 
            // Decode modrm byte
            if (!decodeModrm(info))
            {
                return false;
            }
            index = info.modrm - 0xC0;
            break;
        case VXOpcodeTreeNodeType::ADDRESS_SIZE: 
            switch (m_disassemblerMode)
            {
            case VXDisassemblerMode::M16BIT:
                index = (info.flags & IF_PREFIX_ADDRESS_SIZE_OVERRIDE) ? 1 : 0;
                break;
            case VXDisassemblerMode::M32BIT:
                index = (info.flags & IF_PREFIX_ADDRESS_SIZE_OVERRIDE) ? 0 : 1;
                break;
            case VXDisassemblerMode::M64BIT:
                index = (info.flags & IF_PREFIX_ADDRESS_SIZE_OVERRIDE) ? 1 : 2;
                break;
            default:
                assert(0);
            }
            break;
        case VXOpcodeTreeNodeType::OPERAND_SIZE: 
            switch (m_disassemblerMode)
            {
            case VXDisassemblerMode::M16BIT:
                index = (info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE) ? 1 : 0;
                break;
            case VXDisassemblerMode::M32BIT:
                index = (info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE) ? 0 : 1;
                break;
            case VXDisassemblerMode::M64BIT:
                index = 
                    (info.rex_w) ? 2 : ((info.flags & IF_PREFIX_OPERAND_SIZE_OVERRIDE) ? 0 : 1);
                break;
            default:
                assert(0);
            }
            break;
        case VXOpcodeTreeNodeType::MODE: 
            index = (m_disassemblerMode != VXDisassemblerMode::M64BIT) ? 0 : 1;
            break;
        case VXOpcodeTreeNodeType::VENDOR:
            switch (m_preferredVendor)
            {
            case VXInstructionSetVendor::ANY: 
                index = (GetOpcodeTreeChild(node, 0) != 0) ? 0 : 1;
                break;
            case VXInstructionSetVendor::INTEL: 
                index = 1;
                break;
            case VXInstructionSetVendor::AMD: 
                index = 0;
                break;
            default: 
                assert(0);
            }
            break;
        case VXOpcodeTreeNodeType::AMD3DNOW: 
            {     
                // As all 3dnow instructions got the same operands and flag definitions, we just
                // decode a random instruction and determine the specific opcode later.
                assert(GetOpcodeTreeChild(node, 0x0C) != 0);
                if (!decodeInstructionNode(info, GetOpcodeTreeChild(node, 0x0C)))
                {
                    return false;
                }
                // Decode operands
                if (!decodeOperands(info))
                {
                    return false;
                }
                // Read the actual 3dnow opcode
                info.opcode[2] = inputNext(info);
                if (!info.opcode[2] && (info.flags & IF_ERROR_MASK))
                {
                    return false;
                }
                // Update instruction mnemonic
                const VXInstructionDefinition *instrDefinition = 
                    GetInstructionDefinition(GetOpcodeTreeChild(node, info.opcode[2]));
                if (!instrDefinition)
                {
                    info.flags |= IF_ERROR_INVALID;
                    return false;
                }
                info.instrDefinition = instrDefinition;
                info.mnemonic = instrDefinition->mnemonic;
                // Terminate loop
                return true;
            }
        case VXOpcodeTreeNodeType::VEX: 
            if ((m_disassemblerMode == VXDisassemblerMode::M64BIT) ||
                (((inputCurrent() >> 6) & 0x03) == 0x03))
            {
                // Decode vex prefix
                if (!decodeVex(info))
                {
                    return false;
                }
                // Update instruction info
                switch (info.vex_m_mmmm)
                {
                case 1:
                    info.opcodeLength = 1;
                    info.opcode[0] = 0x0F;
                    break;
                case 2:
                    info.opcodeLength = 2;
                    info.opcode[0] = 0x0F;
                    info.opcode[1] = 0x38;
                    break;
                case 3:
                    info.opcodeLength = 2;
                    info.opcode[0] = 0x0F;
                    info.opcode[1] = 0x3A;
                    break;
                default:
                    // TODO: ERROR
                    break;
                }
                // Set child node index for next iteration
                index = info.vex_m_mmmm + (info.vex_pp << 2);
            } else
            {
                index = 0;
            }
            break;
        case VXOpcodeTreeNodeType::VEXW: 
            assert(info.flags & IF_PREFIX_VEX);
            index = info.vex_w;
            break;
        case VXOpcodeTreeNodeType::VEXL: 
            assert(info.flags & IF_PREFIX_VEX);
            index = info.vex_l;
            break;
        default: 
            assert(0);
        }
        node = GetOpcodeTreeChild(node, index);
    } while (nodeType != VXOpcodeTreeNodeType::INSTRUCTION_DEFINITION);
    return false;
}

bool VXInstructionDecoder::decodeInstructionNode(VXInstructionInfo &info, VXOpcodeTreeNode node)
{
    // Check for invalid instruction
    if (Internal::GetOpcodeNodeValue(node) == 0)
    {
        info.flags |= IF_ERROR_INVALID;
        return false;
    }
    // Get instruction definition
    bool hasModrm = false;
    const VXInstructionDefinition *instrDefinition = 
        Internal::GetInstructionDefinition(node, hasModrm);
    // Check for invalid 64 bit instruction
    if ((m_disassemblerMode == VXDisassemblerMode::M64BIT) && 
        (instrDefinition->flags & IDF_INVALID_64))
    {
        info.flags |= IF_ERROR_INVALID_64;
        return false;
    }
    // Update instruction info
    info.instrDefinition = instrDefinition;
    info.mnemonic = instrDefinition->mnemonic;
    // Decode modrm byte
    if (hasModrm && !decodeModrm(info))
    {
        return false;
    }
    // Update values required for operand decoding
    uint8_t rex = info.rex;
    if (info.flags & IF_PREFIX_VEX)
    {
        switch (info.vex_op)
        {
        case 0xC4:
            rex = ((~(info.vex_b1 >> 5) & 0x07) | ((info.vex_b2 >> 4) & 0x08));
            break;
        case 0xC5:
            rex = (~(info.vex_b1 >> 5)) & 4;
            break;
        default:
            assert(0);
        }    
    }
    // Calculate effective values by adding the corresponding part of the flags bitmask
    rex &= (instrDefinition->flags & 0x000F);
    // Store effective values in the current disassembler instance
    m_effectiveRexW     = (rex >> 3) & 0x01;
    m_effectiveRexR     = (rex >> 2) & 0x01;
    m_effectiveRexX     = (rex >> 1) & 0x01;
    m_effectiveRexB     = (rex >> 0) & 0x01;
    m_effectiveModrmReg = (m_effectiveRexR << 3) | info.modrm_reg;
    m_effectiveModrmRm  = (m_effectiveRexB << 3) | info.modrm_rm;
    m_effectiveVexL     = info.vex_l && (instrDefinition->flags & IDF_ACCEPTS_VEXL);
    // Resolve operand and address mode
    resolveOperandAndAddressMode(info);
    return true;
}

VXInstructionDecoder::VXInstructionDecoder(void const *buffer, size_t bufferLen, 
    VXDisassemblerMode disassemblerMode, VXInstructionSetVendor preferredVendor)
    : m_inputBuffer(buffer)
    , m_inputBufferLen(bufferLen)
    , m_inputBufferOffset(0)
    , m_disassemblerMode(disassemblerMode)
    , m_preferredVendor(preferredVendor)
{

}

bool VXInstructionDecoder::decodeNextInstruction(VXInstructionInfo &info)
{
    // Clear instruction info
    memset(&info, 0, sizeof(info));
    // Set disassembler mode flags
    switch (m_disassemblerMode)
    {
    case VXDisassemblerMode::M16BIT: 
        info.flags |= IF_DISASSEMBLER_MODE_16;
        break;
    case VXDisassemblerMode::M32BIT: 
        info.flags |= IF_DISASSEMBLER_MODE_32;
        break;
    case VXDisassemblerMode::M64BIT: 
        info.flags |= IF_DISASSEMBLER_MODE_64;
        break;
    default: 
        assert(0);
    }
    // Set instruction pointer
    info.instructionPointer = m_instructionPointer;
    // Decode
    if (!decodePrefixes(info) || !decodeOpcode(info))
    {
        goto DecodeError;
    }
    // SWAPGS is only valid in 64 bit mode
    if ((info.mnemonic == VXInstructionMnemonic::SWAPGS) && 
        (m_disassemblerMode != VXDisassemblerMode::M64BIT))
    {
        info.flags &= IF_ERROR_INVALID;
        goto DecodeError;
    }
    // Handle aliases
    if (info.mnemonic == VXInstructionMnemonic::XCHG)
    {
        if ((info.operand[0].type == VXOperandType::REGISTER && 
            info.operand[0].base == VXRegister::AX &&
            info.operand[1].type == VXOperandType::REGISTER && 
            info.operand[1].base == VXRegister::AX) || 
            (info.operand[0].type == VXOperandType::REGISTER && 
            info.operand[0].base == VXRegister::EAX &&
            info.operand[1].type == VXOperandType::REGISTER && 
            info.operand[1].base == VXRegister::EAX))
        {
            info.mnemonic = VXInstructionMnemonic::NOP;
            info.operand[0].type = VXOperandType::NONE;    
            info.operand[1].type = VXOperandType::NONE; 
        }
    }
    if ((info.mnemonic == VXInstructionMnemonic::NOP) && (info.flags & IF_PREFIX_REPZ))
    {
        info.mnemonic = VXInstructionMnemonic::PAUSE;
        info.flags &= ~IF_PREFIX_REPZ;
    }
    // Increment instruction pointer
    m_instructionPointer += info.length;
    return true;
DecodeError:
    // Increment instruction pointer. 
    m_instructionPointer += 1;
    // Backup all error flags, the instruction length and the instruction pointer
    uint32_t flags = info.flags & (IF_ERROR_MASK | 0x00000007);
    uint8_t length = info.length;
    uint8_t firstByte = info.instructionBytes[0];
    uint64_t instrPointer = info.instructionPointer;
    // Clear instruction info
    memset(&info, 0, sizeof(info));
    // Restore saved values
    info.flags = flags;
    info.length = length;
    info.instructionBytes[0] = firstByte;
    info.instructionPointer = instrPointer;
    info.instrDefinition = Internal::GetInstructionDefinition(0);
    // Return with error, if the end of the input source was reached while decoding the 
    // invalid instruction
    if (info.flags & IF_ERROR_END_OF_INPUT)
    {
        info.length = 0;
        return false;
    }
    // Decrement the input position, if more than one byte was read from the input data 
    // source while decoding the invalid instruction. 
    if (info.length != 1)
    {
        m_inputBufferOffset = m_inputBufferOffset - info.length + 1;
        info.length = 1;
    }
    return true;
}

}

}
