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

#ifndef _ZYDIS_TYPES_H_
#define _ZYDIS_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include "ZydisOpcodeTable.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   Values that represent additional flags of a decoded instruction.
 */
typedef enum _ZydisInstructionFlags /* : uint32_t */
{
    ZYDIS_IF_NONE                       = 0x00000000,
    /**
     * @brief   The instruction was decoded in 16 bit disassembler mode.
     */
    ZYDIS_IF_DISASSEMBLER_MODE_16       = 0x00000001,
    /**
     * @brief   The instruction was decoded in 32 bit disassembler mode.
     */
    ZYDIS_IF_DISASSEMBLER_MODE_32       = 0x00000002,
    /**
     * @brief   The instruction was decoded in 64 bit disassembler mode.
     */
    ZYDIS_IF_DISASSEMBLER_MODE_64       = 0x00000004,
    /**
     * @brief   The instruction has a segment prefix (0x26, 0x2E, 0x36, 0x3E, 0x64, 0x65).   
     */
    ZYDIS_IF_PREFIX_SEGMENT             = 0x00000008, 
    /**
     * @brief   The instruction has a lock prefix (0xF0).   
     */
    ZYDIS_IF_PREFIX_LOCK                = 0x00000010,  
    /**
     * @brief   The instruction has a repne prefix (0xF2).   
     */
    ZYDIS_IF_PREFIX_REPNE               = 0x00000020,  
    /**
     * @brief   The instruction has a rep prefix (0xF3).   
     */
    ZYDIS_IF_PREFIX_REP                 = 0x00000040,  
    /**
     * @brief   The instruction has an operand size prefix (0x66).  
     */
    ZYDIS_IF_PREFIX_OPERAND_SIZE        = 0x00000080, 
    /**
     * @brief   The instruction has an address size prefix (0x67).   
     */
    ZYDIS_IF_PREFIX_ADDRESS_SIZE        = 0x00000100, 
    /**
     * @brief   The instruction has a rex prefix (0x40 - 0x4F).  
     */
    ZYDIS_IF_PREFIX_REX                 = 0x00000200, 
    /**
     * @brief   The instruction has a vex prefix (0xC4 or 0xC5).  
     */
    ZYDIS_IF_PREFIX_VEX                 = 0x00000400,
    /**
     * @brief   The instruction has a modrm byte.  
     */
    ZYDIS_IF_MODRM                      = 0x00000800,
    /**
     * @brief   The instruction has a sib byte.  
     */
    ZYDIS_IF_SIB                        = 0x00001000,
    /**
     * @brief   The instruction has an operand with a relative address.
     */
    ZYDIS_IF_RELATIVE                   = 0x00002000,
    /**
     * @brief   An error occured while decoding the instruction.  
     */
    ZYDIS_IF_ERROR_MASK                 = 0xFFF00000,
    /**
     * @brief   End of input reached while decoding the instruction.  
     */
    ZYDIS_IF_ERROR_END_OF_INPUT         = 0x00100000,
    /**
     * @brief   The instruction length has exceeded the maximum of 15 bytes.  
     */
    ZYDIS_IF_ERROR_LENGTH               = 0x00200000,
    /**
     * @brief   The instruction is invalid.   
     */
    ZYDIS_IF_ERROR_INVALID              = 0x00400000,
    /**
     * @brief   The instruction is invalid in 64 bit mode.   
     */
    ZYDIS_IF_ERROR_INVALID_64           = 0x00800000,
    /**
     * @brief   An error occured while decoding the instruction operands.  
     */
    ZYDIS_IF_ERROR_OPERAND              = 0x01000000,

    ZYDIS_IF_FORCE_DWORD                = 0x7FFFFFFF
} ZydisInstructionFlags;

/**
 * @brief   Values that represent a cpu register.
 */
typedef enum _ZydisRegister /* : uint16_t */
{
    ZYDIS_REG_NONE,
    /* 8 bit general purpose registers */
    ZYDIS_REG_AL,     ZYDIS_REG_CL,     ZYDIS_REG_DL,     ZYDIS_REG_BL,
    ZYDIS_REG_AH,     ZYDIS_REG_CH,     ZYDIS_REG_DH,     ZYDIS_REG_BH,
    ZYDIS_REG_SPL,    ZYDIS_REG_BPL,    ZYDIS_REG_SIL,    ZYDIS_REG_DIL,
    ZYDIS_REG_R8B,    ZYDIS_REG_R9B,    ZYDIS_REG_R10B,   ZYDIS_REG_R11B,
    ZYDIS_REG_R12B,   ZYDIS_REG_R13B,   ZYDIS_REG_R14B,   ZYDIS_REG_R15B,
    /* 16 bit general purpose registers */
    ZYDIS_REG_AX,     ZYDIS_REG_CX,     ZYDIS_REG_DX,     ZYDIS_REG_BX,
    ZYDIS_REG_SP,     ZYDIS_REG_BP,     ZYDIS_REG_SI,     ZYDIS_REG_DI,
    ZYDIS_REG_R8W,    ZYDIS_REG_R9W,    ZYDIS_REG_R10W,   ZYDIS_REG_R11W,
    ZYDIS_REG_R12W,   ZYDIS_REG_R13W,   ZYDIS_REG_R14W,   ZYDIS_REG_R15W,
    /* 32 bit general purpose registers */
    ZYDIS_REG_EAX,    ZYDIS_REG_ECX,    ZYDIS_REG_EDX,    ZYDIS_REG_EBX,
    ZYDIS_REG_ESP,    ZYDIS_REG_EBP,    ZYDIS_REG_ESI,    ZYDIS_REG_EDI,
    ZYDIS_REG_R8D,    ZYDIS_REG_R9D,    ZYDIS_REG_R10D,   ZYDIS_REG_R11D,
    ZYDIS_REG_R12D,   ZYDIS_REG_R13D,   ZYDIS_REG_R14D,   ZYDIS_REG_R15D,
    /* 64 bit general purpose registers */
    ZYDIS_REG_RAX,    ZYDIS_REG_RCX,    ZYDIS_REG_RDX,    ZYDIS_REG_RBX,
    ZYDIS_REG_RSP,    ZYDIS_REG_RBP,    ZYDIS_REG_RSI,    ZYDIS_REG_RDI,
    ZYDIS_REG_R8,     ZYDIS_REG_R9,     ZYDIS_REG_R10,    ZYDIS_REG_R11,
    ZYDIS_REG_R12,    ZYDIS_REG_R13,    ZYDIS_REG_R14,    ZYDIS_REG_R15,
    /* segment registers */
    ZYDIS_REG_ES,     ZYDIS_REG_CS,     ZYDIS_REG_SS,     
    ZYDIS_REG_DS,     ZYDIS_REG_FS,     ZYDIS_REG_GS,
    /* control registers */
    ZYDIS_REG_CR0,    ZYDIS_REG_CR1,    ZYDIS_REG_CR2,    ZYDIS_REG_CR3,
    ZYDIS_REG_CR4,    ZYDIS_REG_CR5,    ZYDIS_REG_CR6,    ZYDIS_REG_CR7,
    ZYDIS_REG_CR8,    ZYDIS_REG_CR9,    ZYDIS_REG_CR10,   ZYDIS_REG_CR11,
    ZYDIS_REG_CR12,   ZYDIS_REG_CR13,   ZYDIS_REG_CR14,   ZYDIS_REG_CR15,
    /* debug registers */
    ZYDIS_REG_DR0,    ZYDIS_REG_DR1,    ZYDIS_REG_DR2,    ZYDIS_REG_DR3,
    ZYDIS_REG_DR4,    ZYDIS_REG_DR5,    ZYDIS_REG_DR6,    ZYDIS_REG_DR7,
    ZYDIS_REG_DR8,    ZYDIS_REG_DR9,    ZYDIS_REG_DR10,   ZYDIS_REG_DR11,
    ZYDIS_REG_DR12,   ZYDIS_REG_DR13,   ZYDIS_REG_DR14,   ZYDIS_REG_DR15,
    /* mmx registers */
    ZYDIS_REG_MM0,    ZYDIS_REG_MM1,    ZYDIS_REG_MM2,    ZYDIS_REG_MM3,
    ZYDIS_REG_MM4,    ZYDIS_REG_MM5,    ZYDIS_REG_MM6,    ZYDIS_REG_MM7,
    /* x87 registers */
    ZYDIS_REG_ST0,    ZYDIS_REG_ST1,    ZYDIS_REG_ST2,    ZYDIS_REG_ST3,
    ZYDIS_REG_ST4,    ZYDIS_REG_ST5,    ZYDIS_REG_ST6,    ZYDIS_REG_ST7,
    /* extended multimedia registers */
    ZYDIS_REG_XMM0,   ZYDIS_REG_XMM1,   ZYDIS_REG_XMM2,   ZYDIS_REG_XMM3,
    ZYDIS_REG_XMM4,   ZYDIS_REG_XMM5,   ZYDIS_REG_XMM6,   ZYDIS_REG_XMM7,
    ZYDIS_REG_XMM8,   ZYDIS_REG_XMM9,   ZYDIS_REG_XMM10,  ZYDIS_REG_XMM11,
    ZYDIS_REG_XMM12,  ZYDIS_REG_XMM13,  ZYDIS_REG_XMM14,  ZYDIS_REG_XMM15,
    /* 256 bit multimedia registers */
    ZYDIS_REG_YMM0,   ZYDIS_REG_YMM1,   ZYDIS_REG_YMM2,   ZYDIS_REG_YMM3,
    ZYDIS_REG_YMM4,   ZYDIS_REG_YMM5,   ZYDIS_REG_YMM6,   ZYDIS_REG_YMM7,
    ZYDIS_REG_YMM8,   ZYDIS_REG_YMM9,   ZYDIS_REG_YMM10,  ZYDIS_REG_YMM11,
    ZYDIS_REG_YMM12,  ZYDIS_REG_YMM13,  ZYDIS_REG_YMM14,  YMM15,
    /* instruction pointer register */
    ZYDIS_REG_RIP,

    ZYDIS_REG_FORCE_WORD = 0x7FFF
} ZydisRegister;

/**
 * @brief   Values that represent the type of a decoded operand.
 */
typedef enum _ZydisOperandType /*: uint8_t*/
{
    /**
     * @brief   The operand is not used.
     */
    ZYDIS_OPTYPE_NONE,
    /**
     * @brief   The operand is a register operand.
     */
    ZYDIS_OPTYPE_REGISTER,
    /**
     * @brief   The operand is a memory operand.
     */
    ZYDIS_OPTYPE_MEMORY,
    /**
     * @brief   The operand is a pointer operand.
     */
    ZYDIS_OPTYPE_POINTER,
    /**
     * @brief   The operand is an immediate operand.
     */
    ZYDIS_OPTYPE_IMMEDIATE,
    /**
     * @brief   The operand is a relative immediate operand.
     */
    ZYDIS_OPTYPE_REL_IMMEDIATE,
    /**
     * @brief   The operand is a constant value.
     */
    ZYDIS_OPTYPE_CONSTANT
} ZydisOperandType;

/**
 * @brief   Values that represent the operand access mode.
 */
typedef enum _ZydisOperandAccessMode /* : uint8_t */
{
    ZYDIS_OPACCESSMODE_NA,
    /**
     * @brief   The operand is accessed in read-only mode.
     */
    ZYDIS_OPACCESSMODE_READ,
    /**
     * @brief   The operand is accessed in write mode.
     */
    ZYDIS_OPACCESSMODE_WRITE,
    /**
     * @brief   The operand is accessed in read-write mode.
     */
    ZYDIS_OPACCESSMODE_READWRITE
} ZydisOperandAccessMode;

/**
 * @brief   This struct holds information about a decoded operand.
 */
typedef struct _ZydisOperandInfo
{
    /**
     * @brief   The type of the operand.
     * @see     ZydisOperandType
     */
    uint8_t type;
    /**
     * @brief   The size of the operand.
     */
    uint16_t size;
    /**
     * @brief   The operand access mode.
     * @see     ZydisOperandAccessMode
     */
    uint8_t access_mode;
    /**
     * @brief   The base register.
     * @see     ZydisRegister
     */
    uint16_t base;
    /**
     * @brief   The index register.
     * @see     ZydisRegister
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
} ZydisOperandInfo;

/**
 * @brief   This struct holds information about a decoded instruction.
 */
typedef struct _ZydisInstructionInfo
{
    /**
     * @brief   The instruction flags.
     */
    uint32_t flags;
    /**
     * @brief   The instruction mnemonic.
     * @see     ZydisInstructionMnemonic
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
    ZydisOperandInfo operand[4];
    /**
     * @brief   The segment register. This value will default to @c NONE, if no segment register 
     *          prefix is present.
     * @see     ZydisRegister
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
    const void* instrDefinition; /* TODO: Port instruction definition types */
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
} ZydisInstructionInfo;

#ifdef __cplusplus
}
#endif

#endif /* _ZYDIS_TYPES_H_ */