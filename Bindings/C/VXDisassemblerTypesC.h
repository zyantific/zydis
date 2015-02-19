/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

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

#ifndef _VDE_VXDISASSEMBLERTYPESC_H_
#define _VDE_VXDISASSEMBLERTYPESC_H_

#include <stdint.h>
#include <stdbool.h>
#include "VXOpcodeTableC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   Values that represent additional flags of a decoded instruction.
 */
typedef enum _VXInstructionFlags /* : uint32_t */
{
    IF_NONE                         = 0x00000000,
    /**
     * @brief   The instruction was decoded in 16 bit disassembler mode.
     */
    IF_DISASSEMBLER_MODE_16         = 0x00000001,
    /**
     * @brief   The instruction was decoded in 32 bit disassembler mode.
     */
    IF_DISASSEMBLER_MODE_32         = 0x00000002,
    /**
     * @brief   The instruction was decoded in 64 bit disassembler mode.
     */
    IF_DISASSEMBLER_MODE_64         = 0x00000004,
    /**
     * @brief   The instruction has a segment prefix (0x26, 0x2E, 0x36, 0x3E, 0x64, 0x65).   
     */
    IF_PREFIX_SEGMENT               = 0x00000008, 
    /**
     * @brief   The instruction has a lock prefix (0xF0).   
     */
    IF_PREFIX_LOCK                  = 0x00000010,  
    /**
     * @brief   The instruction has a repne prefix (0xF2).   
     */
    IF_PREFIX_REPNE                 = 0x00000020,  
    /**
     * @brief   The instruction has a rep prefix (0xF3).   
     */
    IF_PREFIX_REP                   = 0x00000040,  
    /**
     * @brief   The instruction has an operand size prefix (0x66).  
     */
    IF_PREFIX_OPERAND_SIZE          = 0x00000080, 
    /**
     * @brief   The instruction has an address size prefix (0x67).   
     */
    IF_PREFIX_ADDRESS_SIZE          = 0x00000100, 
    /**
     * @brief   The instruction has a rex prefix (0x40 - 0x4F).  
     */
    IF_PREFIX_REX                   = 0x00000200, 
    /**
     * @brief   The instruction has a vex prefix (0xC4 or 0xC5).  
     */
    IF_PREFIX_VEX                   = 0x00000400,
    /**
     * @brief   The instruction has a modrm byte.  
     */
    IF_MODRM                        = 0x00000800,
    /**
     * @brief   The instruction has a sib byte.  
     */
    IF_SIB                          = 0x00001000,
    /**
     * @brief   The instruction has an operand with a relative address.
     */
    IF_RELATIVE                     = 0x00002000,
    /**
     * @brief   An error occured while decoding the instruction.  
     */
    IF_ERROR_MASK                   = 0xFFF00000,
    /**
     * @brief   End of input reached while decoding the instruction.  
     */
    IF_ERROR_END_OF_INPUT           = 0x00100000,
    /**
     * @brief   The instruction length has exceeded the maximum of 15 bytes.  
     */
    IF_ERROR_LENGTH                 = 0x00200000,
    /**
     * @brief   The instruction is invalid.   
     */
    IF_ERROR_INVALID                = 0x00400000,
    /**
     * @brief   The instruction is invalid in 64 bit mode.   
     */
    IF_ERROR_INVALID_64             = 0x00800000,
    /**
     * @brief   An error occured while decoding the instruction operands.  
     */
    IF_ERROR_OPERAND                = 0x01000000,

    IF_FORCE_DWORD                  = 0x7FFFFFFF
} VXInstructionFlags;

/**
 * @brief   Values that represent a cpu register.
 */
typedef enum _VXRegister /* : uint16_t */
{
    REG_NONE,
    /* 8 bit general purpose registers */
    REG_AL,     REG_CL,     REG_DL,     REG_BL,
    REG_AH,     REG_CH,     REG_DH,     REG_BH,
    REG_SPL,    REG_BPL,    REG_SIL,    REG_DIL,
    REG_R8B,    REG_R9B,    REG_R10B,   REG_R11B,
    REG_R12B,   REG_R13B,   REG_R14B,   REG_R15B,
    /* 16 bit general purpose registers */
    REG_AX,     REG_CX,     REG_DX,     REG_BX,
    REG_SP,     REG_BP,     REG_SI,     REG_DI,
    REG_R8W,    REG_R9W,    REG_R10W,   REG_R11W,
    REG_R12W,   REG_R13W,   REG_R14W,   REG_R15W,
    /* 32 bit general purpose registers */
    REG_EAX,    REG_ECX,    REG_EDX,    REG_EBX,
    REG_ESP,    REG_EBP,    REG_ESI,    REG_EDI,
    REG_R8D,    REG_R9D,    REG_R10D,   REG_R11D,
    REG_R12D,   REG_R13D,   REG_R14D,   REG_R15D,
    /* 64 bit general purpose registers */
    REG_RAX,    REG_RCX,    REG_RDX,    REG_RBX,
    REG_RSP,    REG_RBP,    REG_RSI,    REG_RDI,
    REG_R8,     REG_R9,     REG_R10,    REG_R11,
    REG_R12,    REG_R13,    REG_R14,    REG_R15,
    /* segment registers */
    REG_ES,     REG_CS,     REG_SS,     
    REG_DS,     REG_FS,     REG_GS,
    /* control registers */
    REG_CR0,    REG_CR1,    REG_CR2,    REG_CR3,
    REG_CR4,    REG_CR5,    REG_CR6,    REG_CR7,
    REG_CR8,    REG_CR9,    REG_CR10,   REG_CR11,
    REG_CR12,   REG_CR13,   REG_CR14,   REG_CR15,
    /* debug registers */
    REG_DR0,    REG_DR1,    REG_DR2,    REG_DR3,
    REG_DR4,    REG_DR5,    REG_DR6,    REG_DR7,
    REG_DR8,    REG_DR9,    REG_DR10,   REG_DR11,
    REG_DR12,   REG_DR13,   REG_DR14,   REG_DR15,
    /* mmx registers */
    REG_MM0,    REG_MM1,    REG_MM2,    REG_MM3,
    REG_MM4,    REG_MM5,    REG_MM6,    REG_MM7,
    /* x87 registers */
    REG_ST0,    REG_ST1,    REG_ST2,    REG_ST3,
    REG_ST4,    REG_ST5,    REG_ST6,    REG_ST7,
    /* extended multimedia registers */
    REG_XMM0,   REG_XMM1,   REG_XMM2,   REG_XMM3,
    REG_XMM4,   REG_XMM5,   REG_XMM6,   REG_XMM7,
    REG_XMM8,   REG_XMM9,   REG_XMM10,  REG_XMM11,
    REG_XMM12,  REG_XMM13,  REG_XMM14,  REG_XMM15,
    /* 256 bit multimedia registers */
    REG_YMM0,   REG_YMM1,   REG_YMM2,   REG_YMM3,
    REG_YMM4,   REG_YMM5,   REG_YMM6,   REG_YMM7,
    REG_YMM8,   REG_YMM9,   REG_YMM10,  REG_YMM11,
    REG_YMM12,  REG_YMM13,  REG_YMM14,  YMM15,
    /* instruction pointer register */
    REG_RIP,

    REG_FORCE_WORD = 0x7FFF
} VXRegister;

/**
 * @brief   Values that represent the type of a decoded operand.
 */
typedef enum _VXOperandType /*: uint8_t*/
{
    /**
     * @brief   The operand is not used.
     */
    OPTYPE_NONE,
    /**
     * @brief   The operand is a register operand.
     */
    OPTYPE_REGISTER,
    /**
     * @brief   The operand is a memory operand.
     */
    OPTYPE_MEMORY,
    /**
     * @brief   The operand is a pointer operand.
     */
    OPTYPE_POINTER,
    /**
     * @brief   The operand is an immediate operand.
     */
    OPTYPE_IMMEDIATE,
    /**
     * @brief   The operand is a relative immediate operand.
     */
    OPTYPE_REL_IMMEDIATE,
    /**
     * @brief   The operand is a constant value.
     */
    OPTYPE_CONSTANT
} VXOperandType;

/**
 * @brief   Values that represent the operand access mode.
 */
typedef enum _VXOperandAccessMode /* : uint8_t */
{
    OPACCESSMODE_NA,
    /**
     * @brief   The operand is accessed in read-only mode.
     */
    OPACCESSMODE_READ,
    /**
     * @brief   The operand is accessed in write mode.
     */
    OPACCESSMODE_WRITE,
    /**
     * @brief   The operand is accessed in read-write mode.
     */
    OPACCESSMODE_READWRITE
} VXOperandAccessMode;

/**
 * @brief   This struct holds information about a decoded operand.
 */
typedef struct _VXOperandInfo
{
    /**
     * @brief   The type of the operand.
     * @see     VXOperandType
     */
    uint8_t type;
    /**
     * @brief   The size of the operand.
     */
    uint16_t size;
    /**
     * @brief   The operand access mode.
     * @see     VXOperandAccessMode
     */
    uint8_t access_mode;
    /**
     * @brief   The base register.
     * @see     VXRegister
     */
    uint16_t base;
    /**
     * @brief   The index register.
     * @see     VXRegister
     */
    uint16_t index;
    /**
     * @brief   The scale factor.
     */
    uint8_t scale;
    /**
     * @brief   The lvalue offset. If the @c offset is zero and the operand @c type is not 
     *          @c CONSTANT, no lvalue is present.
     */
    uint8_t offset;
    /**
     * @brief   Signals, if the lval is signed.
     */
    bool signed_lval;
    /**
     * @brief   The lvalue.
     */
    union {
        int8_t sbyte;
        uint8_t ubyte;
        int16_t sword;
        uint16_t uword;
        int32_t sdword;
        uint32_t udword;
        int64_t sqword;
        uint64_t uqword;
        struct {
            uint16_t seg;
            uint32_t off;
        } ptr;
    } lval;   
} VXOperandInfo;

/**
 * @brief   This struct holds information about a decoded instruction.
 */
typedef struct _VXInstructionInfo
{
    /**
     * @brief   The instruction flags.
     */
    uint32_t flags;
    /**
     * @brief   The instruction mnemonic.
     * @see     VXInstructionMnemonic
     */
    uint16_t mnemonic;
    /**
     * @brief   The total length of the instruction.
     */
    uint8_t length;
    /**
     * @brief   Contains all bytes of the instruction.
     */
    uint8_t data[15];
    /**
     * @brief   The length of the instruction opcodes.
     */
    uint8_t opcode_length;
    /**
     * @brief   The instruction opcodes.
     */
    uint8_t opcode[3];
    /**
     * @brief   The operand mode.
     */
    uint8_t operand_mode;
    /**
     * @brief   The address mode.
     */
    uint8_t address_mode;
    /**
     * @brief   The decoded operands.
     */
    VXOperandInfo operand[4];
    /**
     * @brief   The segment register. This value will default to @c NONE, if no segment register 
     *          prefix is present.
     * @see     VXRegister
     */
    uint16_t segment;
    /**
     * @brief   The rex prefix byte.
     */
    uint8_t rex;
    /**
     * @brief   When 1, a 64-bit operand size is used. Otherwise, when 0, the default operand size 
     *          is used.
     */
    uint8_t rex_w;
    /**
     * @brief   This 1-bit value is an extension to the MODRM.reg field.
     */
    uint8_t rex_r;
    /**
     * @brief   This 1-bit value is an extension to the SIB.index field.
     */
    uint8_t rex_x;
    /**
     * @brief   This 1-bit value is an extension to the MODRM.rm field or the SIB.base field.
     */
    uint8_t rex_b;
    /**
     * @brief   The modrm byte.
     */
    uint8_t modrm;
    /**
     * @brief   The modrm modus bits. When this field is b11, then register-direct addressing mode 
     *          is used; otherwise register-indirect addressing mode is used. 
     */
    uint8_t modrm_mod;
    /**
     * @brief   The modrm register bits. The REX.R, VEX.~R or XOP.~R field can extend this field 
     *          with 1 most-significant bit to 4 bits total. 
     */
    uint8_t modrm_reg;
    /**
     * @brief   The extended modrm register bits. If the instruction definition does not have the
     *          @c IDF_ACCEPTS_REXR flag set, this value defaults to the normal @c modrm_reg 
     *          field.
     */
    uint8_t modrm_reg_ext;
    /**
     * @brief   The modrm register/memory bits. Specifies a direct or indirect register operand, 
     *          optionally with a displacement. The REX.B, VEX.~B or XOP.~B field can extend this 
     *          field with 1 most-significant bit to 4 bits total. 
     */
    uint8_t modrm_rm;
    /**
     * @brief   The extended modrm register/memory bits. If the instruction definition does not 
     *          have the @c IDF_ACCEPTS_REXB flag set, this value defaults to the normal 
     *          @c modrm_rm field.
     */
    uint8_t modrm_rm_ext;
    /**
     * @brief   The sib byte.
     */
    uint8_t sib;
    /**
     * @brief   This field indicates the scaling factor of SIB.index.
     */
    uint8_t sib_scale;
    /**
     * @brief   The index register to use. The REX.X, VEX.~X or XOP.~X field can extend this field 
     *          with 1 most-significant bit to 4 bits total.
     */
    uint8_t sib_index;
    /**
     * @brief   The extended index register. If the instruction definition does not have the
     *          @c IDF_ACCEPTS_REXX flag set, this value defaults to the normal @c sib_index 
     *          field.
     */
    uint8_t sib_index_ext;
    /**
     * @brief   The base register to use. The REX.B, VEX.~B or XOP.~B field can extend this field 
     *          with 1 most-significant bit to 4 bits total.
     */
    uint8_t sib_base;
    /**
     * @brief   The extended base register. If the instruction definition does not have the
     *          @c IDF_ACCEPTS_REXB flag set, this value defaults to the normal @c sib_index 
     *          field.
     */
    uint8_t sib_base_ext;
    /**
     * @brief   The primary vex prefix byte.
     */
    uint8_t vex_op;
    /**
     * @brief   The second vex prefix byte.
     */
    uint8_t vex_b1;
    /**
     * @brief   The third vex prefix byte.
     */
    uint8_t vex_b2;
    /**
     * @brief   This 1-bit value is an 'inverted' extension to the MODRM.reg field. The inverse of 
     *          REX.R.
     */
    uint8_t vex_r;     
    /**
     * @brief   This 1-bit value is an 'inverted' extension to the SIB.index field. The inverse of 
     *          REX.X.
     */
    uint8_t vex_x;
    /**
     * @brief   This 1-bit value is an 'inverted' extension to the MODRM.rm field or the SIB.base 
     *          field. The inverse of REX.B.
     */
    uint8_t vex_b;
    /**
     * @brief   Specifies the opcode map to use. 
     *          00 = 0x0F
     *          01 = 0x0F 0x38
     *          02 = 0x0F 0x3A
     */
    uint8_t vex_m_mmmm;
    /**
     * @brief   For integer instructions: when 1, a 64-bit operand size is used; otherwise, 
     *          when 0, the default operand size is used (equivalent with REX.W). For non-integer 
     *          instructions, this bit is a general opcode extension bit.
     */
    uint8_t vex_w;   
    /**
     * @brief   An additional operand for the instruction. The value of the XMM or YMM register 
     *          is 'inverted'. 
     */
    uint8_t vex_vvvv;
    /**
     * @brief   When 0, a 128-bit vector lengh is used. Otherwise, when 1, a 256-bit vector length 
     *          is used. 
     */
    uint8_t vex_l;     
    /**
     * @brief   Specifies an implied mandatory prefix for the opcode.
     *          00 = none
     *          01 = 0x66 
     *          10 = 0xF3
     *          11 = 0xF2
     */
    uint8_t vex_pp;
    /**
     * @brief   The effectively used REX/VEX.w value. If the instruction definition does not have 
     *          the @c IDF_ACCEPTS_REXW flag set, this value defaults to zero.
     */
    uint8_t eff_rexvex_w;
    /**
     * @brief   The effectively used REX/VEX.r value. If the instruction definition does not have 
     *          the @c IDF_ACCEPTS_REXR flag set, this value defaults to zero.
     */
    uint8_t eff_rexvex_r;
    /**
     * @brief   The effectively used REX/VEX.x value. If the instruction definition does not have 
     *          the @c IDF_ACCEPTS_REXX flag set, this value defaults to zero.
     */
    uint8_t eff_rexvex_x;
    /**
     * @brief   The effectively used REX/VEX.b value. If the instruction definition does not have 
     *          the @c IDF_ACCEPTS_REXB flag set, this value defaults to zero.
     */
    uint8_t eff_rexvex_b;
    /**
     * @brief   The effectively used VEX.l value. If the instruction definition does not have 
     *          the @c IDF_ACCEPTS_VEXL flag set, this value defaults to zero.
     */
    uint8_t eff_vex_l;
    /**
     * @brief   The instruction definition.
     */
    const VXInstructionDefinition *instrDefinition;
    /**
     * @brief   The instruction address points to the current instruction (relative to the 
     *          initial instruction pointer).
     */
    uint64_t instrAddress;
    /**
     * @brief   The instruction pointer points to the address of the next instruction (relative
     *          to the initial instruction pointer). 
     *          This field is used to properly format relative instructions.         
     */
    uint64_t instrPointer;
} VXInstructionInfo;

#ifdef __cplusplus
}
#endif

#endif /* _VDE_VXDISASSEMBLERTYPESC_H_ */