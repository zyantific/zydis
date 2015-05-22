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

/**
 * @file
 * @brief C API for Zydis.
 */

#ifndef _ZYDIS_API_H_
#define _ZYDIS_API_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "ZydisExportConfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Zydis Types ================================================================================== */

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

/* Context Declarations ========================================================================= */

typedef struct _ZydisInputContext { int dummy; } ZydisInputContext;

typedef struct _ZydisInstructionDecoderContext { int dummy; } ZydisInstructionDecoderContext;

typedef struct _ZydisInstructionFormatterContext { int dummy; } ZydisInstructionFormatterContext;

typedef struct _ZydisSymbolResolverContext { int dummy; } ZydisSymbolResolverContext;

/* Callback Declarations ======================================================================== */

/* General -------------------------------------------------------------------------------------- */

typedef void (*ZydisCustomDestructorT)(void* userData);

/* Input ---------------------------------------------------------------------------------------- */

typedef uint8_t (*ZydisCustomInputPeekT)(void* userData);  
typedef uint8_t (*ZydisCustomInputNextT)(void* userData); 
typedef bool (*ZydisCustomInputIsEndOfInputT)(void* userData); 
typedef uint64_t (*ZydisCustomInputGetPositionT)(void* userData); 
typedef bool (*ZydisCustomInputSetPositionT)(void* userData, uint64_t position); 

/* InstructionFormatter ------------------------------------------------------------------------- */

// TODO:

/* SymbolResolver ------------------------------------------------------------------------------- */

// TODO:

/* Error Handling =============================================================================== */

typedef enum _ZydisErrorCode /* : uint8_t */
{
    ZYDIS_ERROR_SUCCESS,
    ZYDIS_ERROR_UNKNOWN,
    ZYDIS_ERROR_NOT_ENOUGH_MEMORY,
    ZYDIS_ERROR_INVALID_PARAMETER
} ZydisErrorCode;

ZYDIS_EXPORT uint32_t ZydisGetLastError();

/* Input ======================================================================================== */

ZYDIS_EXPORT ZydisInputContext* ZydisCreateCustomInput(void* userData, 
    ZydisCustomInputPeekT cbPeek, ZydisCustomInputNextT cbNext, 
    ZydisCustomInputIsEndOfInputT cbIsEndOfInput, ZydisCustomInputGetPositionT cbGetPosition,
    ZydisCustomInputSetPositionT cbSetPosition, ZydisCustomDestructorT cbDestructor);

ZYDIS_EXPORT ZydisInputContext* ZydisCreateMemoryInput(const void* buffer, size_t bufferLen);

ZYDIS_EXPORT bool ZydisIsEndOfInput(const ZydisInputContext* input, bool* isEndOfInput);

ZYDIS_EXPORT bool ZydisGetInputPosition(const ZydisInputContext* input, uint64_t* position);

ZYDIS_EXPORT bool ZydisSetInputPosition(const ZydisInputContext* input, uint64_t position);

ZYDIS_EXPORT bool ZydisFreeInput(const ZydisInputContext* input);

/* InstructionDecoder =========================================================================== */

/**
 * @brief   Values that represent a disassembler mode.
 */
typedef enum _ZydisDisassemblerMode /* : uint8_t */
{
    ZYDIS_DM_M16BIT,
    ZYDIS_DM_M32BIT,
    ZYDIS_DM_M64BIT
} ZydisDisassemblerMode;

/**
 * @brief   Values that represent an instruction-set vendor.
 */
typedef enum _ZydisInstructionSetVendor /* : uint8_t */
{
    ZYDIS_ISV_ANY,
    ZYDIS_ISV_INTEL,
    ZYDIS_ISV_AMD
} ZydisInstructionSetVendor;

ZYDIS_EXPORT ZydisInstructionDecoderContext* ZydisCreateInstructionDecoder();

ZYDIS_EXPORT ZydisInstructionDecoderContext* ZydisCreateInstructionDecoderEx(
    const ZydisInputContext* input, ZydisDisassemblerMode disassemblerMode,
    ZydisInstructionSetVendor preferredVendor, uint64_t instructionPointer);

ZYDIS_EXPORT bool ZydisDecodeInstruction(const ZydisInstructionDecoderContext* decoder, 
    ZydisInstructionInfo* info);

ZYDIS_EXPORT bool ZydisGetDataSource(const ZydisInstructionDecoderContext* decoder,
    ZydisInputContext** input);

ZYDIS_EXPORT bool ZydisSetDataSource(const ZydisInstructionDecoderContext* decoder,
    ZydisInputContext* input);

ZYDIS_EXPORT bool ZydisGetDisassemblerMode(const ZydisInstructionDecoderContext* decoder,
    ZydisDisassemblerMode* disassemblerMode);

ZYDIS_EXPORT bool ZydisSetDisassemblerMode(const ZydisInstructionDecoderContext* decoder,
    ZydisDisassemblerMode disassemblerMode);

ZYDIS_EXPORT bool ZydisGetPreferredVendor(const ZydisInstructionDecoderContext* decoder,
    ZydisInstructionSetVendor* preferredVendor);

ZYDIS_EXPORT bool ZydisSetPreferredVendor(const ZydisInstructionDecoderContext* decoder,
    ZydisInstructionSetVendor preferredVendor);

 ZYDIS_EXPORT bool ZydisGetInstructionPointer(const ZydisInstructionDecoderContext* decoder,
    uint64_t* instructionPointer);

ZYDIS_EXPORT bool ZydisSetInstructionPointer(const ZydisInstructionDecoderContext* decoder,
    uint64_t instructionPointer);

ZYDIS_EXPORT bool ZydisFreeInstructionDecoder(const ZydisInstructionDecoderContext* decoder);

/* InstructionFormatter ========================================================================= */

ZYDIS_EXPORT ZydisInstructionFormatterContext* ZydisCreateCustomInstructionFormatter(/*TODO*/);

ZYDIS_EXPORT ZydisInstructionFormatterContext* ZydisCreateIntelInstructionFormatter();

ZYDIS_EXPORT bool ZydisFormatInstruction(const ZydisInstructionFormatterContext* formatter,
    const ZydisInstructionInfo* info, const char** instructionText);

ZYDIS_EXPORT bool ZydisGetSymbolResolver(const ZydisInstructionFormatterContext* formatter,
    ZydisSymbolResolverContext** resolver);

ZYDIS_EXPORT bool ZydisSetSymbolResolver(const ZydisInstructionFormatterContext* formatter,
    ZydisSymbolResolverContext* resolver);

ZYDIS_EXPORT bool ZydisFreeInstructionFormatter(const ZydisInstructionFormatterContext* formatter);

/* SymbolResolver =============================================================================== */

ZYDIS_EXPORT ZydisSymbolResolverContext* ZydisCreateCustomSymbolResolver(/*TODO*/);

ZYDIS_EXPORT ZydisSymbolResolverContext* ZydisCreateExactSymbolResolver();

ZYDIS_EXPORT bool ZydisResolveSymbol(const ZydisSymbolResolverContext* resolver, 
    const ZydisInstructionInfo* info, uint64_t address, const char** symbol, uint64_t* offset);

ZYDIS_EXPORT bool ZydisExactSymbolResolverContainsSymbol(
    const ZydisSymbolResolverContext* resolver, uint64_t address, bool* containsSymbol);

ZYDIS_EXPORT bool ZydisExactSymbolResolverSetSymbol(const ZydisSymbolResolverContext* resolver, 
    uint64_t address, const char** symbol);

ZYDIS_EXPORT bool ZydisExactSymbolResolverRemoveSymbol(const ZydisSymbolResolverContext* resolver, 
    uint64_t address);

ZYDIS_EXPORT bool ZydisExactSymbolResolverClear(const ZydisSymbolResolverContext* resolver);

ZYDIS_EXPORT bool ZydisFreeSymbolResolver(const ZydisSymbolResolverContext* resolver);

/* Opcode Table ================================================================================= */

/**
 * @brief   Values that represent an instruction mnemonic.
 */
typedef enum _ZydisInstructionMnemonic /* : uint16_t */
{
    /* 000 */ ZYDIS_MNEM_INVALID,
    /* 001 */ ZYDIS_MNEM_AAA,
    /* 002 */ ZYDIS_MNEM_AAD,
    /* 003 */ ZYDIS_MNEM_AAM,
    /* 004 */ ZYDIS_MNEM_AAS,
    /* 005 */ ZYDIS_MNEM_ADC,
    /* 006 */ ZYDIS_MNEM_ADD,
    /* 007 */ ZYDIS_MNEM_ADDPD,
    /* 008 */ ZYDIS_MNEM_ADDPS,
    /* 009 */ ZYDIS_MNEM_ADDSD,
    /* 00A */ ZYDIS_MNEM_ADDSS,
    /* 00B */ ZYDIS_MNEM_ADDSUBPD,
    /* 00C */ ZYDIS_MNEM_ADDSUBPS,
    /* 00D */ ZYDIS_MNEM_AESDEC,
    /* 00E */ ZYDIS_MNEM_AESDECLAST,
    /* 00F */ ZYDIS_MNEM_AESENC,
    /* 010 */ ZYDIS_MNEM_AESENCLAST,
    /* 011 */ ZYDIS_MNEM_AESIMC,
    /* 012 */ ZYDIS_MNEM_AESKEYGENASSIST,
    /* 013 */ ZYDIS_MNEM_AND,
    /* 014 */ ZYDIS_MNEM_ANDNPD,
    /* 015 */ ZYDIS_MNEM_ANDNPS,
    /* 016 */ ZYDIS_MNEM_ANDPD,
    /* 017 */ ZYDIS_MNEM_ANDPS,
    /* 018 */ ZYDIS_MNEM_ARPL,
    /* 019 */ ZYDIS_MNEM_BLENDPD,
    /* 01A */ ZYDIS_MNEM_BLENDPS,
    /* 01B */ ZYDIS_MNEM_BLENDVPD,
    /* 01C */ ZYDIS_MNEM_BLENDVPS,
    /* 01D */ ZYDIS_MNEM_BOUND,
    /* 01E */ ZYDIS_MNEM_BSF,
    /* 01F */ ZYDIS_MNEM_BSR,
    /* 020 */ ZYDIS_MNEM_BSWAP,
    /* 021 */ ZYDIS_MNEM_BT,
    /* 022 */ ZYDIS_MNEM_BTC,
    /* 023 */ ZYDIS_MNEM_BTR,
    /* 024 */ ZYDIS_MNEM_BTS,
    /* 025 */ ZYDIS_MNEM_CALL,
    /* 026 */ ZYDIS_MNEM_CBW,
    /* 027 */ ZYDIS_MNEM_CDQ,
    /* 028 */ ZYDIS_MNEM_CDQE,
    /* 029 */ ZYDIS_MNEM_CLC,
    /* 02A */ ZYDIS_MNEM_CLD,
    /* 02B */ ZYDIS_MNEM_CLFLUSH,
    /* 02C */ ZYDIS_MNEM_CLGI,
    /* 02D */ ZYDIS_MNEM_CLI,
    /* 02E */ ZYDIS_MNEM_CLTS,
    /* 02F */ ZYDIS_MNEM_CMC,
    /* 030 */ ZYDIS_MNEM_CMOVA,
    /* 031 */ ZYDIS_MNEM_CMOVAE,
    /* 032 */ ZYDIS_MNEM_CMOVB,
    /* 033 */ ZYDIS_MNEM_CMOVBE,
    /* 034 */ ZYDIS_MNEM_CMOVE,
    /* 035 */ ZYDIS_MNEM_CMOVG,
    /* 036 */ ZYDIS_MNEM_CMOVGE,
    /* 037 */ ZYDIS_MNEM_CMOVL,
    /* 038 */ ZYDIS_MNEM_CMOVLE,
    /* 039 */ ZYDIS_MNEM_CMOVNE,
    /* 03A */ ZYDIS_MNEM_CMOVNO,
    /* 03B */ ZYDIS_MNEM_CMOVNP,
    /* 03C */ ZYDIS_MNEM_CMOVNS,
    /* 03D */ ZYDIS_MNEM_CMOVO,
    /* 03E */ ZYDIS_MNEM_CMOVP,
    /* 03F */ ZYDIS_MNEM_CMOVS,
    /* 040 */ ZYDIS_MNEM_CMP,
    /* 041 */ ZYDIS_MNEM_CMPPD,
    /* 042 */ ZYDIS_MNEM_CMPPS,
    /* 043 */ ZYDIS_MNEM_CMPSB,
    /* 044 */ ZYDIS_MNEM_CMPSD,
    /* 045 */ ZYDIS_MNEM_CMPSQ,
    /* 046 */ ZYDIS_MNEM_CMPSS,
    /* 047 */ ZYDIS_MNEM_CMPSW,
    /* 048 */ ZYDIS_MNEM_CMPXCHG,
    /* 049 */ ZYDIS_MNEM_CMPXCHG16B,
    /* 04A */ ZYDIS_MNEM_CMPXCHG8B,
    /* 04B */ ZYDIS_MNEM_COMISD,
    /* 04C */ ZYDIS_MNEM_COMISS,
    /* 04D */ ZYDIS_MNEM_CPUID,
    /* 04E */ ZYDIS_MNEM_CQO,
    /* 04F */ ZYDIS_MNEM_CRC32,
    /* 050 */ ZYDIS_MNEM_CVTDQ2PD,
    /* 051 */ ZYDIS_MNEM_CVTDQ2PS,
    /* 052 */ ZYDIS_MNEM_CVTPD2DQ,
    /* 053 */ ZYDIS_MNEM_CVTPD2PI,
    /* 054 */ ZYDIS_MNEM_CVTPD2PS,
    /* 055 */ ZYDIS_MNEM_CVTPI2PD,
    /* 056 */ ZYDIS_MNEM_CVTPI2PS,
    /* 057 */ ZYDIS_MNEM_CVTPS2DQ,
    /* 058 */ ZYDIS_MNEM_CVTPS2PD,
    /* 059 */ ZYDIS_MNEM_CVTPS2PI,
    /* 05A */ ZYDIS_MNEM_CVTSD2SI,
    /* 05B */ ZYDIS_MNEM_CVTSD2SS,
    /* 05C */ ZYDIS_MNEM_CVTSI2SD,
    /* 05D */ ZYDIS_MNEM_CVTSI2SS,
    /* 05E */ ZYDIS_MNEM_CVTSS2SD,
    /* 05F */ ZYDIS_MNEM_CVTSS2SI,
    /* 060 */ ZYDIS_MNEM_CVTTPD2DQ,
    /* 061 */ ZYDIS_MNEM_CVTTPD2PI,
    /* 062 */ ZYDIS_MNEM_CVTTPS2DQ,
    /* 063 */ ZYDIS_MNEM_CVTTPS2PI,
    /* 064 */ ZYDIS_MNEM_CVTTSD2SI,
    /* 065 */ ZYDIS_MNEM_CVTTSS2SI,
    /* 066 */ ZYDIS_MNEM_CWD,
    /* 067 */ ZYDIS_MNEM_CWDE,
    /* 068 */ ZYDIS_MNEM_DAA,
    /* 069 */ ZYDIS_MNEM_DAS,
    /* 06A */ ZYDIS_MNEM_DEC,
    /* 06B */ ZYDIS_MNEM_DIV,
    /* 06C */ ZYDIS_MNEM_DIVPD,
    /* 06D */ ZYDIS_MNEM_DIVPS,
    /* 06E */ ZYDIS_MNEM_DIVSD,
    /* 06F */ ZYDIS_MNEM_DIVSS,
    /* 070 */ ZYDIS_MNEM_DPPD,
    /* 071 */ ZYDIS_MNEM_DPPS,
    /* 072 */ ZYDIS_MNEM_EMMS,
    /* 073 */ ZYDIS_MNEM_ENTER,
    /* 074 */ ZYDIS_MNEM_EXTRACTPS,
    /* 075 */ ZYDIS_MNEM_F2XM1,
    /* 076 */ ZYDIS_MNEM_FABS,
    /* 077 */ ZYDIS_MNEM_FADD,
    /* 078 */ ZYDIS_MNEM_FADDP,
    /* 079 */ ZYDIS_MNEM_FBLD,
    /* 07A */ ZYDIS_MNEM_FBSTP,
    /* 07B */ ZYDIS_MNEM_FCHS,
    /* 07C */ ZYDIS_MNEM_FCLEX,
    /* 07D */ ZYDIS_MNEM_FCMOVB,
    /* 07E */ ZYDIS_MNEM_FCMOVBE,
    /* 07F */ ZYDIS_MNEM_FCMOVE,
    /* 080 */ ZYDIS_MNEM_FCMOVNB,
    /* 081 */ ZYDIS_MNEM_FCMOVNBE,
    /* 082 */ ZYDIS_MNEM_FCMOVNE,
    /* 083 */ ZYDIS_MNEM_FCMOVNU,
    /* 084 */ ZYDIS_MNEM_FCMOVU,
    /* 085 */ ZYDIS_MNEM_FCOM,
    /* 086 */ ZYDIS_MNEM_FCOM2,
    /* 087 */ ZYDIS_MNEM_FCOMI,
    /* 088 */ ZYDIS_MNEM_FCOMIP,
    /* 089 */ ZYDIS_MNEM_FCOMP,
    /* 08A */ ZYDIS_MNEM_FCOMP3,
    /* 08B */ ZYDIS_MNEM_FCOMP5,
    /* 08C */ ZYDIS_MNEM_FCOMPP,
    /* 08D */ ZYDIS_MNEM_FCOS,
    /* 08E */ ZYDIS_MNEM_FDECSTP,
    /* 08F */ ZYDIS_MNEM_FDIV,
    /* 090 */ ZYDIS_MNEM_FDIVP,
    /* 091 */ ZYDIS_MNEM_FDIVR,
    /* 092 */ ZYDIS_MNEM_FDIVRP,
    /* 093 */ ZYDIS_MNEM_FEMMS,
    /* 094 */ ZYDIS_MNEM_FFREE,
    /* 095 */ ZYDIS_MNEM_FFREEP,
    /* 096 */ ZYDIS_MNEM_FIADD,
    /* 097 */ ZYDIS_MNEM_FICOM,
    /* 098 */ ZYDIS_MNEM_FICOMP,
    /* 099 */ ZYDIS_MNEM_FIDIV,
    /* 09A */ ZYDIS_MNEM_FIDIVR,
    /* 09B */ ZYDIS_MNEM_FILD,
    /* 09C */ ZYDIS_MNEM_FIMUL,
    /* 09D */ ZYDIS_MNEM_FINCSTP,
    /* 09E */ ZYDIS_MNEM_FIST,
    /* 09F */ ZYDIS_MNEM_FISTP,
    /* 0A0 */ ZYDIS_MNEM_FISTTP,
    /* 0A1 */ ZYDIS_MNEM_FISUB,
    /* 0A2 */ ZYDIS_MNEM_FISUBR,
    /* 0A3 */ ZYDIS_MNEM_FLD,
    /* 0A4 */ ZYDIS_MNEM_FLD1,
    /* 0A5 */ ZYDIS_MNEM_FLDCW,
    /* 0A6 */ ZYDIS_MNEM_FLDENV,
    /* 0A7 */ ZYDIS_MNEM_FLDL2E,
    /* 0A8 */ ZYDIS_MNEM_FLDL2T,
    /* 0A9 */ ZYDIS_MNEM_FLDLG2,
    /* 0AA */ ZYDIS_MNEM_FLDLN2,
    /* 0AB */ ZYDIS_MNEM_FLDPI,
    /* 0AC */ ZYDIS_MNEM_FLDZ,
    /* 0AD */ ZYDIS_MNEM_FMUL,
    /* 0AE */ ZYDIS_MNEM_FMULP,
    /* 0AF */ ZYDIS_MNEM_FNDISI,
    /* 0B0 */ ZYDIS_MNEM_FNENI,
    /* 0B1 */ ZYDIS_MNEM_FNINIT,
    /* 0B2 */ ZYDIS_MNEM_FNOP,
    /* 0B3 */ ZYDIS_MNEM_FNSAVE,
    /* 0B4 */ ZYDIS_MNEM_FNSETPM,
    /* 0B5 */ ZYDIS_MNEM_FNSTCW,
    /* 0B6 */ ZYDIS_MNEM_FNSTENV,
    /* 0B7 */ ZYDIS_MNEM_FNSTSW,
    /* 0B8 */ ZYDIS_MNEM_FPATAN,
    /* 0B9 */ ZYDIS_MNEM_FPREM,
    /* 0BA */ ZYDIS_MNEM_FPREM1,
    /* 0BB */ ZYDIS_MNEM_FPTAN,
    /* 0BC */ ZYDIS_MNEM_FRNDINT,
    /* 0BD */ ZYDIS_MNEM_FRSTOR,
    /* 0BE */ ZYDIS_MNEM_FRSTPM,
    /* 0BF */ ZYDIS_MNEM_FSCALE,
    /* 0C0 */ ZYDIS_MNEM_FSIN,
    /* 0C1 */ ZYDIS_MNEM_FSINCOS,
    /* 0C2 */ ZYDIS_MNEM_FSQRT,
    /* 0C3 */ ZYDIS_MNEM_FST,
    /* 0C4 */ ZYDIS_MNEM_FSTP,
    /* 0C5 */ ZYDIS_MNEM_FSTP1,
    /* 0C6 */ ZYDIS_MNEM_FSTP8,
    /* 0C7 */ ZYDIS_MNEM_FSTP9,
    /* 0C8 */ ZYDIS_MNEM_FSUB,
    /* 0C9 */ ZYDIS_MNEM_FSUBP,
    /* 0CA */ ZYDIS_MNEM_FSUBR,
    /* 0CB */ ZYDIS_MNEM_FSUBRP,
    /* 0CC */ ZYDIS_MNEM_FTST,
    /* 0CD */ ZYDIS_MNEM_FUCOM,
    /* 0CE */ ZYDIS_MNEM_FUCOMI,
    /* 0CF */ ZYDIS_MNEM_FUCOMIP,
    /* 0D0 */ ZYDIS_MNEM_FUCOMP,
    /* 0D1 */ ZYDIS_MNEM_FUCOMPP,
    /* 0D2 */ ZYDIS_MNEM_FXAM,
    /* 0D3 */ ZYDIS_MNEM_FXCH,
    /* 0D4 */ ZYDIS_MNEM_FXCH4,
    /* 0D5 */ ZYDIS_MNEM_FXCH7,
    /* 0D6 */ ZYDIS_MNEM_FXRSTOR,
    /* 0D7 */ ZYDIS_MNEM_FXSAVE,
    /* 0D8 */ ZYDIS_MNEM_FXTRACT,
    /* 0D9 */ ZYDIS_MNEM_FYL2X,
    /* 0DA */ ZYDIS_MNEM_FYL2XP1,
    /* 0DB */ ZYDIS_MNEM_GETSEC,
    /* 0DC */ ZYDIS_MNEM_HADDPD,
    /* 0DD */ ZYDIS_MNEM_HADDPS,
    /* 0DE */ ZYDIS_MNEM_HLT,
    /* 0DF */ ZYDIS_MNEM_HSUBPD,
    /* 0E0 */ ZYDIS_MNEM_HSUBPS,
    /* 0E1 */ ZYDIS_MNEM_IDIV,
    /* 0E2 */ ZYDIS_MNEM_IMUL,
    /* 0E3 */ ZYDIS_MNEM_IN,
    /* 0E4 */ ZYDIS_MNEM_INC,
    /* 0E5 */ ZYDIS_MNEM_INSB,
    /* 0E6 */ ZYDIS_MNEM_INSD,
    /* 0E7 */ ZYDIS_MNEM_INSERTPS,
    /* 0E8 */ ZYDIS_MNEM_INSW,
    /* 0E9 */ ZYDIS_MNEM_INT,
    /* 0EA */ ZYDIS_MNEM_INT1,
    /* 0EB */ ZYDIS_MNEM_INT3,
    /* 0EC */ ZYDIS_MNEM_INTO,
    /* 0ED */ ZYDIS_MNEM_INVD,
    /* 0EE */ ZYDIS_MNEM_INVEPT,
    /* 0EF */ ZYDIS_MNEM_INVLPG,
    /* 0F0 */ ZYDIS_MNEM_INVLPGA,
    /* 0F1 */ ZYDIS_MNEM_INVVPID,
    /* 0F2 */ ZYDIS_MNEM_IRETD,
    /* 0F3 */ ZYDIS_MNEM_IRETQ,
    /* 0F4 */ ZYDIS_MNEM_IRETW,
    /* 0F5 */ ZYDIS_MNEM_JA,
    /* 0F6 */ ZYDIS_MNEM_JB,
    /* 0F7 */ ZYDIS_MNEM_JBE,
    /* 0F8 */ ZYDIS_MNEM_JCXZ,
    /* 0F9 */ ZYDIS_MNEM_JE,
    /* 0FA */ ZYDIS_MNEM_JECXZ,
    /* 0FB */ ZYDIS_MNEM_JG,
    /* 0FC */ ZYDIS_MNEM_JGE,
    /* 0FD */ ZYDIS_MNEM_JL,
    /* 0FE */ ZYDIS_MNEM_JLE,
    /* 0FF */ ZYDIS_MNEM_JMP,
    /* 100 */ ZYDIS_MNEM_JNB,
    /* 101 */ ZYDIS_MNEM_JNE,
    /* 102 */ ZYDIS_MNEM_JNO,
    /* 103 */ ZYDIS_MNEM_JNP,
    /* 104 */ ZYDIS_MNEM_JNS,
    /* 105 */ ZYDIS_MNEM_JO,
    /* 106 */ ZYDIS_MNEM_JP,
    /* 107 */ ZYDIS_MNEM_JRCXZ,
    /* 108 */ ZYDIS_MNEM_JS,
    /* 109 */ ZYDIS_MNEM_LAHF,
    /* 10A */ ZYDIS_MNEM_LAR,
    /* 10B */ ZYDIS_MNEM_LDDQU,
    /* 10C */ ZYDIS_MNEM_LDMXCSR,
    /* 10D */ ZYDIS_MNEM_LDS,
    /* 10E */ ZYDIS_MNEM_LEA,
    /* 10F */ ZYDIS_MNEM_LEAVE,
    /* 110 */ ZYDIS_MNEM_LES,
    /* 111 */ ZYDIS_MNEM_LFENCE,
    /* 112 */ ZYDIS_MNEM_LFS,
    /* 113 */ ZYDIS_MNEM_LGDT,
    /* 114 */ ZYDIS_MNEM_LGS,
    /* 115 */ ZYDIS_MNEM_LIDT,
    /* 116 */ ZYDIS_MNEM_LLDT,
    /* 117 */ ZYDIS_MNEM_LMSW,
    /* 118 */ ZYDIS_MNEM_LOCK,
    /* 119 */ ZYDIS_MNEM_LODSB,
    /* 11A */ ZYDIS_MNEM_LODSD,
    /* 11B */ ZYDIS_MNEM_LODSQ,
    /* 11C */ ZYDIS_MNEM_LODSW,
    /* 11D */ ZYDIS_MNEM_LOOP,
    /* 11E */ ZYDIS_MNEM_LOOPE,
    /* 11F */ ZYDIS_MNEM_LOOPNE,
    /* 120 */ ZYDIS_MNEM_LSL,
    /* 121 */ ZYDIS_MNEM_LSS,
    /* 122 */ ZYDIS_MNEM_LTR,
    /* 123 */ ZYDIS_MNEM_MASKMOVDQU,
    /* 124 */ ZYDIS_MNEM_MASKMOVQ,
    /* 125 */ ZYDIS_MNEM_MAXPD,
    /* 126 */ ZYDIS_MNEM_MAXPS,
    /* 127 */ ZYDIS_MNEM_MAXSD,
    /* 128 */ ZYDIS_MNEM_MAXSS,
    /* 129 */ ZYDIS_MNEM_MFENCE,
    /* 12A */ ZYDIS_MNEM_MINPD,
    /* 12B */ ZYDIS_MNEM_MINPS,
    /* 12C */ ZYDIS_MNEM_MINSD,
    /* 12D */ ZYDIS_MNEM_MINSS,
    /* 12E */ ZYDIS_MNEM_MONITOR,
    /* 12F */ ZYDIS_MNEM_MONTMUL,
    /* 130 */ ZYDIS_MNEM_MOV,
    /* 131 */ ZYDIS_MNEM_MOVAPD,
    /* 132 */ ZYDIS_MNEM_MOVAPS,
    /* 133 */ ZYDIS_MNEM_MOVBE,
    /* 134 */ ZYDIS_MNEM_MOVD,
    /* 135 */ ZYDIS_MNEM_MOVDDUP,
    /* 136 */ ZYDIS_MNEM_MOVDQ2Q,
    /* 137 */ ZYDIS_MNEM_MOVDQA,
    /* 138 */ ZYDIS_MNEM_MOVDQU,
    /* 139 */ ZYDIS_MNEM_MOVHLPS,
    /* 13A */ ZYDIS_MNEM_MOVHPD,
    /* 13B */ ZYDIS_MNEM_MOVHPS,
    /* 13C */ ZYDIS_MNEM_MOVLHPS,
    /* 13D */ ZYDIS_MNEM_MOVLPD,
    /* 13E */ ZYDIS_MNEM_MOVLPS,
    /* 13F */ ZYDIS_MNEM_MOVMSKPD,
    /* 140 */ ZYDIS_MNEM_MOVMSKPS,
    /* 141 */ ZYDIS_MNEM_MOVNTDQ,
    /* 142 */ ZYDIS_MNEM_MOVNTDQA,
    /* 143 */ ZYDIS_MNEM_MOVNTI,
    /* 144 */ ZYDIS_MNEM_MOVNTPD,
    /* 145 */ ZYDIS_MNEM_MOVNTPS,
    /* 146 */ ZYDIS_MNEM_MOVNTQ,
    /* 147 */ ZYDIS_MNEM_MOVQ,
    /* 148 */ ZYDIS_MNEM_MOVQ2DQ,
    /* 149 */ ZYDIS_MNEM_MOVSB,
    /* 14A */ ZYDIS_MNEM_MOVSD,
    /* 14B */ ZYDIS_MNEM_MOVSHDUP,
    /* 14C */ ZYDIS_MNEM_MOVSLDUP,
    /* 14D */ ZYDIS_MNEM_MOVSQ,
    /* 14E */ ZYDIS_MNEM_MOVSS,
    /* 14F */ ZYDIS_MNEM_MOVSW,
    /* 150 */ ZYDIS_MNEM_MOVSX,
    /* 151 */ ZYDIS_MNEM_MOVSXD,
    /* 152 */ ZYDIS_MNEM_MOVUPD,
    /* 153 */ ZYDIS_MNEM_MOVUPS,
    /* 154 */ ZYDIS_MNEM_MOVZX,
    /* 155 */ ZYDIS_MNEM_MPSADBW,
    /* 156 */ ZYDIS_MNEM_MUL,
    /* 157 */ ZYDIS_MNEM_MULPD,
    /* 158 */ ZYDIS_MNEM_MULPS,
    /* 159 */ ZYDIS_MNEM_MULSD,
    /* 15A */ ZYDIS_MNEM_MULSS,
    /* 15B */ ZYDIS_MNEM_MWAIT,
    /* 15C */ ZYDIS_MNEM_NEG,
    /* 15D */ ZYDIS_MNEM_NOP,
    /* 15E */ ZYDIS_MNEM_NOT,
    /* 15F */ ZYDIS_MNEM_OR,
    /* 160 */ ZYDIS_MNEM_ORPD,
    /* 161 */ ZYDIS_MNEM_ORPS,
    /* 162 */ ZYDIS_MNEM_OUT,
    /* 163 */ ZYDIS_MNEM_OUTSB,
    /* 164 */ ZYDIS_MNEM_OUTSD,
    /* 165 */ ZYDIS_MNEM_OUTSW,
    /* 166 */ ZYDIS_MNEM_PABSB,
    /* 167 */ ZYDIS_MNEM_PABSD,
    /* 168 */ ZYDIS_MNEM_PABSW,
    /* 169 */ ZYDIS_MNEM_PACKSSDW,
    /* 16A */ ZYDIS_MNEM_PACKSSWB,
    /* 16B */ ZYDIS_MNEM_PACKUSDW,
    /* 16C */ ZYDIS_MNEM_PACKUSWB,
    /* 16D */ ZYDIS_MNEM_PADDB,
    /* 16E */ ZYDIS_MNEM_PADDD,
    /* 16F */ ZYDIS_MNEM_PADDQ,
    /* 170 */ ZYDIS_MNEM_PADDSB,
    /* 171 */ ZYDIS_MNEM_PADDSW,
    /* 172 */ ZYDIS_MNEM_PADDUSB,
    /* 173 */ ZYDIS_MNEM_PADDUSW,
    /* 174 */ ZYDIS_MNEM_PADDW,
    /* 175 */ ZYDIS_MNEM_PALIGNR,
    /* 176 */ ZYDIS_MNEM_PAND,
    /* 177 */ ZYDIS_MNEM_PANDN,
    /* 178 */ ZYDIS_MNEM_PAUSE,
    /* 179 */ ZYDIS_MNEM_PAVGB,
    /* 17A */ ZYDIS_MNEM_PAVGUSB,
    /* 17B */ ZYDIS_MNEM_PAVGW,
    /* 17C */ ZYDIS_MNEM_PBLENDVB,
    /* 17D */ ZYDIS_MNEM_PBLENDW,
    /* 17E */ ZYDIS_MNEM_PCLMULQDQ,
    /* 17F */ ZYDIS_MNEM_PCMPEQB,
    /* 180 */ ZYDIS_MNEM_PCMPEQD,
    /* 181 */ ZYDIS_MNEM_PCMPEQQ,
    /* 182 */ ZYDIS_MNEM_PCMPEQW,
    /* 183 */ ZYDIS_MNEM_PCMPESTRI,
    /* 184 */ ZYDIS_MNEM_PCMPESTRM,
    /* 185 */ ZYDIS_MNEM_PCMPGTB,
    /* 186 */ ZYDIS_MNEM_PCMPGTD,
    /* 187 */ ZYDIS_MNEM_PCMPGTQ,
    /* 188 */ ZYDIS_MNEM_PCMPGTW,
    /* 189 */ ZYDIS_MNEM_PCMPISTRI,
    /* 18A */ ZYDIS_MNEM_PCMPISTRM,
    /* 18B */ ZYDIS_MNEM_PEXTRB,
    /* 18C */ ZYDIS_MNEM_PEXTRD,
    /* 18D */ ZYDIS_MNEM_PEXTRQ,
    /* 18E */ ZYDIS_MNEM_PEXTRW,
    /* 18F */ ZYDIS_MNEM_PF2ID,
    /* 190 */ ZYDIS_MNEM_PF2IW,
    /* 191 */ ZYDIS_MNEM_PFACC,
    /* 192 */ ZYDIS_MNEM_PFADD,
    /* 193 */ ZYDIS_MNEM_PFCMPEQ,
    /* 194 */ ZYDIS_MNEM_PFCMPGE,
    /* 195 */ ZYDIS_MNEM_PFCMPGT,
    /* 196 */ ZYDIS_MNEM_PFMAX,
    /* 197 */ ZYDIS_MNEM_PFMIN,
    /* 198 */ ZYDIS_MNEM_PFMUL,
    /* 199 */ ZYDIS_MNEM_PFNACC,
    /* 19A */ ZYDIS_MNEM_PFPNACC,
    /* 19B */ ZYDIS_MNEM_PFRCP,
    /* 19C */ ZYDIS_MNEM_PFRCPIT1,
    /* 19D */ ZYDIS_MNEM_PFRCPIT2,
    /* 19E */ ZYDIS_MNEM_PFRSQIT1,
    /* 19F */ ZYDIS_MNEM_PFRSQRT,
    /* 1A0 */ ZYDIS_MNEM_PFSUB,
    /* 1A1 */ ZYDIS_MNEM_PFSUBR,
    /* 1A2 */ ZYDIS_MNEM_PHADDD,
    /* 1A3 */ ZYDIS_MNEM_PHADDSW,
    /* 1A4 */ ZYDIS_MNEM_PHADDW,
    /* 1A5 */ ZYDIS_MNEM_PHMINPOSUW,
    /* 1A6 */ ZYDIS_MNEM_PHSUBD,
    /* 1A7 */ ZYDIS_MNEM_PHSUBSW,
    /* 1A8 */ ZYDIS_MNEM_PHSUBW,
    /* 1A9 */ ZYDIS_MNEM_PI2FD,
    /* 1AA */ ZYDIS_MNEM_PI2FW,
    /* 1AB */ ZYDIS_MNEM_PINSRB,
    /* 1AC */ ZYDIS_MNEM_PINSRD,
    /* 1AD */ ZYDIS_MNEM_PINSRQ,
    /* 1AE */ ZYDIS_MNEM_PINSRW,
    /* 1AF */ ZYDIS_MNEM_PMADDUBSW,
    /* 1B0 */ ZYDIS_MNEM_PMADDWD,
    /* 1B1 */ ZYDIS_MNEM_PMAXSB,
    /* 1B2 */ ZYDIS_MNEM_PMAXSD,
    /* 1B3 */ ZYDIS_MNEM_PMAXSW,
    /* 1B4 */ ZYDIS_MNEM_PMAXUB,
    /* 1B5 */ ZYDIS_MNEM_PMAXUD,
    /* 1B6 */ ZYDIS_MNEM_PMAXUW,
    /* 1B7 */ ZYDIS_MNEM_PMINSB,
    /* 1B8 */ ZYDIS_MNEM_PMINSD,
    /* 1B9 */ ZYDIS_MNEM_PMINSW,
    /* 1BA */ ZYDIS_MNEM_PMINUB,
    /* 1BB */ ZYDIS_MNEM_PMINUD,
    /* 1BC */ ZYDIS_MNEM_PMINUW,
    /* 1BD */ ZYDIS_MNEM_PMOVMSKB,
    /* 1BE */ ZYDIS_MNEM_PMOVSXBD,
    /* 1BF */ ZYDIS_MNEM_PMOVSXBQ,
    /* 1C0 */ ZYDIS_MNEM_PMOVSXBW,
    /* 1C1 */ ZYDIS_MNEM_PMOVSXDQ,
    /* 1C2 */ ZYDIS_MNEM_PMOVSXWD,
    /* 1C3 */ ZYDIS_MNEM_PMOVSXWQ,
    /* 1C4 */ ZYDIS_MNEM_PMOVZXBD,
    /* 1C5 */ ZYDIS_MNEM_PMOVZXBQ,
    /* 1C6 */ ZYDIS_MNEM_PMOVZXBW,
    /* 1C7 */ ZYDIS_MNEM_PMOVZXDQ,
    /* 1C8 */ ZYDIS_MNEM_PMOVZXWD,
    /* 1C9 */ ZYDIS_MNEM_PMOVZXWQ,
    /* 1CA */ ZYDIS_MNEM_PMULDQ,
    /* 1CB */ ZYDIS_MNEM_PMULHRSW,
    /* 1CC */ ZYDIS_MNEM_PMULHRW,
    /* 1CD */ ZYDIS_MNEM_PMULHUW,
    /* 1CE */ ZYDIS_MNEM_PMULHW,
    /* 1CF */ ZYDIS_MNEM_PMULLD,
    /* 1D0 */ ZYDIS_MNEM_PMULLW,
    /* 1D1 */ ZYDIS_MNEM_PMULUDQ,
    /* 1D2 */ ZYDIS_MNEM_POP,
    /* 1D3 */ ZYDIS_MNEM_POPA,
    /* 1D4 */ ZYDIS_MNEM_POPAD,
    /* 1D5 */ ZYDIS_MNEM_POPCNT,
    /* 1D6 */ ZYDIS_MNEM_POPFD,
    /* 1D7 */ ZYDIS_MNEM_POPFQ,
    /* 1D8 */ ZYDIS_MNEM_POPFW,
    /* 1D9 */ ZYDIS_MNEM_POR,
    /* 1DA */ ZYDIS_MNEM_PREFETCH,
    /* 1DB */ ZYDIS_MNEM_PREFETCHNTA,
    /* 1DC */ ZYDIS_MNEM_PREFETCHT0,
    /* 1DD */ ZYDIS_MNEM_PREFETCHT1,
    /* 1DE */ ZYDIS_MNEM_PREFETCHT2,
    /* 1DF */ ZYDIS_MNEM_PSADBW,
    /* 1E0 */ ZYDIS_MNEM_PSHUFB,
    /* 1E1 */ ZYDIS_MNEM_PSHUFD,
    /* 1E2 */ ZYDIS_MNEM_PSHUFHW,
    /* 1E3 */ ZYDIS_MNEM_PSHUFLW,
    /* 1E4 */ ZYDIS_MNEM_PSHUFW,
    /* 1E5 */ ZYDIS_MNEM_PSIGNB,
    /* 1E6 */ ZYDIS_MNEM_PSIGND,
    /* 1E7 */ ZYDIS_MNEM_PSIGNW,
    /* 1E8 */ ZYDIS_MNEM_PSLLD,
    /* 1E9 */ ZYDIS_MNEM_PSLLDQ,
    /* 1EA */ ZYDIS_MNEM_PSLLQ,
    /* 1EB */ ZYDIS_MNEM_PSLLW,
    /* 1EC */ ZYDIS_MNEM_PSRAD,
    /* 1ED */ ZYDIS_MNEM_PSRAW,
    /* 1EE */ ZYDIS_MNEM_PSRLD,
    /* 1EF */ ZYDIS_MNEM_PSRLDQ,
    /* 1F0 */ ZYDIS_MNEM_PSRLQ,
    /* 1F1 */ ZYDIS_MNEM_PSRLW,
    /* 1F2 */ ZYDIS_MNEM_PSUBB,
    /* 1F3 */ ZYDIS_MNEM_PSUBD,
    /* 1F4 */ ZYDIS_MNEM_PSUBQ,
    /* 1F5 */ ZYDIS_MNEM_PSUBSB,
    /* 1F6 */ ZYDIS_MNEM_PSUBSW,
    /* 1F7 */ ZYDIS_MNEM_PSUBUSB,
    /* 1F8 */ ZYDIS_MNEM_PSUBUSW,
    /* 1F9 */ ZYDIS_MNEM_PSUBW,
    /* 1FA */ ZYDIS_MNEM_PSWAPD,
    /* 1FB */ ZYDIS_MNEM_PTEST,
    /* 1FC */ ZYDIS_MNEM_PUNPCKHBW,
    /* 1FD */ ZYDIS_MNEM_PUNPCKHDQ,
    /* 1FE */ ZYDIS_MNEM_PUNPCKHQDQ,
    /* 1FF */ ZYDIS_MNEM_PUNPCKHWD,
    /* 200 */ ZYDIS_MNEM_PUNPCKLBW,
    /* 201 */ ZYDIS_MNEM_PUNPCKLDQ,
    /* 202 */ ZYDIS_MNEM_PUNPCKLQDQ,
    /* 203 */ ZYDIS_MNEM_PUNPCKLWD,
    /* 204 */ ZYDIS_MNEM_PUSH,
    /* 205 */ ZYDIS_MNEM_PUSHA,
    /* 206 */ ZYDIS_MNEM_PUSHAD,
    /* 207 */ ZYDIS_MNEM_PUSHFD,
    /* 208 */ ZYDIS_MNEM_PUSHFQ,
    /* 209 */ ZYDIS_MNEM_PUSHFW,
    /* 20A */ ZYDIS_MNEM_PXOR,
    /* 20B */ ZYDIS_MNEM_RCL,
    /* 20C */ ZYDIS_MNEM_RCPPS,
    /* 20D */ ZYDIS_MNEM_RCPSS,
    /* 20E */ ZYDIS_MNEM_RCR,
    /* 20F */ ZYDIS_MNEM_RDMSR,
    /* 210 */ ZYDIS_MNEM_RDPMC,
    /* 211 */ ZYDIS_MNEM_RDRAND,
    /* 212 */ ZYDIS_MNEM_RDTSC,
    /* 213 */ ZYDIS_MNEM_RDTSCP,
    /* 214 */ ZYDIS_MNEM_REP,
    /* 215 */ ZYDIS_MNEM_REPNE,
    /* 216 */ ZYDIS_MNEM_RET,
    /* 217 */ ZYDIS_MNEM_RETF,
    /* 218 */ ZYDIS_MNEM_ROL,
    /* 219 */ ZYDIS_MNEM_ROR,
    /* 21A */ ZYDIS_MNEM_ROUNDPD,
    /* 21B */ ZYDIS_MNEM_ROUNDPS,
    /* 21C */ ZYDIS_MNEM_ROUNDSD,
    /* 21D */ ZYDIS_MNEM_ROUNDSS,
    /* 21E */ ZYDIS_MNEM_RSM,
    /* 21F */ ZYDIS_MNEM_RSQRTPS,
    /* 220 */ ZYDIS_MNEM_RSQRTSS,
    /* 221 */ ZYDIS_MNEM_SAHF,
    /* 222 */ ZYDIS_MNEM_SALC,
    /* 223 */ ZYDIS_MNEM_SAR,
    /* 224 */ ZYDIS_MNEM_SBB,
    /* 225 */ ZYDIS_MNEM_SCASB,
    /* 226 */ ZYDIS_MNEM_SCASD,
    /* 227 */ ZYDIS_MNEM_SCASQ,
    /* 228 */ ZYDIS_MNEM_SCASW,
    /* 229 */ ZYDIS_MNEM_SETA,
    /* 22A */ ZYDIS_MNEM_SETAE,
    /* 22B */ ZYDIS_MNEM_SETB,
    /* 22C */ ZYDIS_MNEM_SETBE,
    /* 22D */ ZYDIS_MNEM_SETE,
    /* 22E */ ZYDIS_MNEM_SETG,
    /* 22F */ ZYDIS_MNEM_SETGE,
    /* 230 */ ZYDIS_MNEM_SETL,
    /* 231 */ ZYDIS_MNEM_SETLE,
    /* 232 */ ZYDIS_MNEM_SETNE,
    /* 233 */ ZYDIS_MNEM_SETNO,
    /* 234 */ ZYDIS_MNEM_SETNP,
    /* 235 */ ZYDIS_MNEM_SETNS,
    /* 236 */ ZYDIS_MNEM_SETO,
    /* 237 */ ZYDIS_MNEM_SETP,
    /* 238 */ ZYDIS_MNEM_SETS,
    /* 239 */ ZYDIS_MNEM_SFENCE,
    /* 23A */ ZYDIS_MNEM_SGDT,
    /* 23B */ ZYDIS_MNEM_SHL,
    /* 23C */ ZYDIS_MNEM_SHLD,
    /* 23D */ ZYDIS_MNEM_SHR,
    /* 23E */ ZYDIS_MNEM_SHRD,
    /* 23F */ ZYDIS_MNEM_SHUFPD,
    /* 240 */ ZYDIS_MNEM_SHUFPS,
    /* 241 */ ZYDIS_MNEM_SIDT,
    /* 242 */ ZYDIS_MNEM_SKINIT,
    /* 243 */ ZYDIS_MNEM_SLDT,
    /* 244 */ ZYDIS_MNEM_SMSW,
    /* 245 */ ZYDIS_MNEM_SQRTPD,
    /* 246 */ ZYDIS_MNEM_SQRTPS,
    /* 247 */ ZYDIS_MNEM_SQRTSD,
    /* 248 */ ZYDIS_MNEM_SQRTSS,
    /* 249 */ ZYDIS_MNEM_STC,
    /* 24A */ ZYDIS_MNEM_STD,
    /* 24B */ ZYDIS_MNEM_STGI,
    /* 24C */ ZYDIS_MNEM_STI,
    /* 24D */ ZYDIS_MNEM_STMXCSR,
    /* 24E */ ZYDIS_MNEM_STOSB,
    /* 24F */ ZYDIS_MNEM_STOSD,
    /* 250 */ ZYDIS_MNEM_STOSQ,
    /* 251 */ ZYDIS_MNEM_STOSW,
    /* 252 */ ZYDIS_MNEM_STR,
    /* 253 */ ZYDIS_MNEM_SUB,
    /* 254 */ ZYDIS_MNEM_SUBPD,
    /* 255 */ ZYDIS_MNEM_SUBPS,
    /* 256 */ ZYDIS_MNEM_SUBSD,
    /* 257 */ ZYDIS_MNEM_SUBSS,
    /* 258 */ ZYDIS_MNEM_SWAPGS,
    /* 259 */ ZYDIS_MNEM_SYSCALL,
    /* 25A */ ZYDIS_MNEM_SYSENTER,
    /* 25B */ ZYDIS_MNEM_SYSEXIT,
    /* 25C */ ZYDIS_MNEM_SYSRET,
    /* 25D */ ZYDIS_MNEM_TEST,
    /* 25E */ ZYDIS_MNEM_UCOMISD,
    /* 25F */ ZYDIS_MNEM_UCOMISS,
    /* 260 */ ZYDIS_MNEM_UD2,
    /* 261 */ ZYDIS_MNEM_UNPCKHPD,
    /* 262 */ ZYDIS_MNEM_UNPCKHPS,
    /* 263 */ ZYDIS_MNEM_UNPCKLPD,
    /* 264 */ ZYDIS_MNEM_UNPCKLPS,
    /* 265 */ ZYDIS_MNEM_VADDPD,
    /* 266 */ ZYDIS_MNEM_VADDPS,
    /* 267 */ ZYDIS_MNEM_VADDSD,
    /* 268 */ ZYDIS_MNEM_VADDSS,
    /* 269 */ ZYDIS_MNEM_VADDSUBPD,
    /* 26A */ ZYDIS_MNEM_VADDSUBPS,
    /* 26B */ ZYDIS_MNEM_VAESDEC,
    /* 26C */ ZYDIS_MNEM_VAESDECLAST,
    /* 26D */ ZYDIS_MNEM_VAESENC,
    /* 26E */ ZYDIS_MNEM_VAESENCLAST,
    /* 26F */ ZYDIS_MNEM_VAESIMC,
    /* 270 */ ZYDIS_MNEM_VAESKEYGENASSIST,
    /* 271 */ ZYDIS_MNEM_VANDNPD,
    /* 272 */ ZYDIS_MNEM_VANDNPS,
    /* 273 */ ZYDIS_MNEM_VANDPD,
    /* 274 */ ZYDIS_MNEM_VANDPS,
    /* 275 */ ZYDIS_MNEM_VBLENDPD,
    /* 276 */ ZYDIS_MNEM_VBLENDPS,
    /* 277 */ ZYDIS_MNEM_VBLENDVPD,
    /* 278 */ ZYDIS_MNEM_VBLENDVPS,
    /* 279 */ ZYDIS_MNEM_VBROADCASTSD,
    /* 27A */ ZYDIS_MNEM_VBROADCASTSS,
    /* 27B */ ZYDIS_MNEM_VCMPPD,
    /* 27C */ ZYDIS_MNEM_VCMPPS,
    /* 27D */ ZYDIS_MNEM_VCMPSD,
    /* 27E */ ZYDIS_MNEM_VCMPSS,
    /* 27F */ ZYDIS_MNEM_VCOMISD,
    /* 280 */ ZYDIS_MNEM_VCOMISS,
    /* 281 */ ZYDIS_MNEM_VCVTDQ2PD,
    /* 282 */ ZYDIS_MNEM_VCVTDQ2PS,
    /* 283 */ ZYDIS_MNEM_VCVTPD2DQ,
    /* 284 */ ZYDIS_MNEM_VCVTPD2PS,
    /* 285 */ ZYDIS_MNEM_VCVTPS2DQ,
    /* 286 */ ZYDIS_MNEM_VCVTPS2PD,
    /* 287 */ ZYDIS_MNEM_VCVTSD2SI,
    /* 288 */ ZYDIS_MNEM_VCVTSD2SS,
    /* 289 */ ZYDIS_MNEM_VCVTSI2SD,
    /* 28A */ ZYDIS_MNEM_VCVTSI2SS,
    /* 28B */ ZYDIS_MNEM_VCVTSS2SD,
    /* 28C */ ZYDIS_MNEM_VCVTSS2SI,
    /* 28D */ ZYDIS_MNEM_VCVTTPD2DQ,
    /* 28E */ ZYDIS_MNEM_VCVTTPS2DQ,
    /* 28F */ ZYDIS_MNEM_VCVTTSD2SI,
    /* 290 */ ZYDIS_MNEM_VCVTTSS2SI,
    /* 291 */ ZYDIS_MNEM_VDIVPD,
    /* 292 */ ZYDIS_MNEM_VDIVPS,
    /* 293 */ ZYDIS_MNEM_VDIVSD,
    /* 294 */ ZYDIS_MNEM_VDIVSS,
    /* 295 */ ZYDIS_MNEM_VDPPD,
    /* 296 */ ZYDIS_MNEM_VDPPS,
    /* 297 */ ZYDIS_MNEM_VERR,
    /* 298 */ ZYDIS_MNEM_VERW,
    /* 299 */ ZYDIS_MNEM_VEXTRACTF128,
    /* 29A */ ZYDIS_MNEM_VEXTRACTPS,
    /* 29B */ ZYDIS_MNEM_VHADDPD,
    /* 29C */ ZYDIS_MNEM_VHADDPS,
    /* 29D */ ZYDIS_MNEM_VHSUBPD,
    /* 29E */ ZYDIS_MNEM_VHSUBPS,
    /* 29F */ ZYDIS_MNEM_VINSERTF128,
    /* 2A0 */ ZYDIS_MNEM_VINSERTPS,
    /* 2A1 */ ZYDIS_MNEM_VLDDQU,
    /* 2A2 */ ZYDIS_MNEM_VMASKMOVDQU,
    /* 2A3 */ ZYDIS_MNEM_VMASKMOVPD,
    /* 2A4 */ ZYDIS_MNEM_VMASKMOVPS,
    /* 2A5 */ ZYDIS_MNEM_VMAXPD,
    /* 2A6 */ ZYDIS_MNEM_VMAXPS,
    /* 2A7 */ ZYDIS_MNEM_VMAXSD,
    /* 2A8 */ ZYDIS_MNEM_VMAXSS,
    /* 2A9 */ ZYDIS_MNEM_VMCALL,
    /* 2AA */ ZYDIS_MNEM_VMCLEAR,
    /* 2AB */ ZYDIS_MNEM_VMINPD,
    /* 2AC */ ZYDIS_MNEM_VMINPS,
    /* 2AD */ ZYDIS_MNEM_VMINSD,
    /* 2AE */ ZYDIS_MNEM_VMINSS,
    /* 2AF */ ZYDIS_MNEM_VMLAUNCH,
    /* 2B0 */ ZYDIS_MNEM_VMLOAD,
    /* 2B1 */ ZYDIS_MNEM_VMMCALL,
    /* 2B2 */ ZYDIS_MNEM_VMOVAPD,
    /* 2B3 */ ZYDIS_MNEM_VMOVAPS,
    /* 2B4 */ ZYDIS_MNEM_VMOVD,
    /* 2B5 */ ZYDIS_MNEM_VMOVDDUP,
    /* 2B6 */ ZYDIS_MNEM_VMOVDQA,
    /* 2B7 */ ZYDIS_MNEM_VMOVDQU,
    /* 2B8 */ ZYDIS_MNEM_VMOVHLPS,
    /* 2B9 */ ZYDIS_MNEM_VMOVHPD,
    /* 2BA */ ZYDIS_MNEM_VMOVHPS,
    /* 2BB */ ZYDIS_MNEM_VMOVLHPS,
    /* 2BC */ ZYDIS_MNEM_VMOVLPD,
    /* 2BD */ ZYDIS_MNEM_VMOVLPS,
    /* 2BE */ ZYDIS_MNEM_VMOVMSKPD,
    /* 2BF */ ZYDIS_MNEM_VMOVMSKPS,
    /* 2C0 */ ZYDIS_MNEM_VMOVNTDQ,
    /* 2C1 */ ZYDIS_MNEM_VMOVNTDQA,
    /* 2C2 */ ZYDIS_MNEM_VMOVNTPD,
    /* 2C3 */ ZYDIS_MNEM_VMOVNTPS,
    /* 2C4 */ ZYDIS_MNEM_VMOVQ,
    /* 2C5 */ ZYDIS_MNEM_VMOVSD,
    /* 2C6 */ ZYDIS_MNEM_VMOVSHDUP,
    /* 2C7 */ ZYDIS_MNEM_VMOVSLDUP,
    /* 2C8 */ ZYDIS_MNEM_VMOVSS,
    /* 2C9 */ ZYDIS_MNEM_VMOVUPD,
    /* 2CA */ ZYDIS_MNEM_VMOVUPS,
    /* 2CB */ ZYDIS_MNEM_VMPSADBW,
    /* 2CC */ ZYDIS_MNEM_VMPTRLD,
    /* 2CD */ ZYDIS_MNEM_VMPTRST,
    /* 2CE */ ZYDIS_MNEM_VMREAD,
    /* 2CF */ ZYDIS_MNEM_VMRESUME,
    /* 2D0 */ ZYDIS_MNEM_VMRUN,
    /* 2D1 */ ZYDIS_MNEM_VMSAVE,
    /* 2D2 */ ZYDIS_MNEM_VMULPD,
    /* 2D3 */ ZYDIS_MNEM_VMULPS,
    /* 2D4 */ ZYDIS_MNEM_VMULSD,
    /* 2D5 */ ZYDIS_MNEM_VMULSS,
    /* 2D6 */ ZYDIS_MNEM_VMWRITE,
    /* 2D7 */ ZYDIS_MNEM_VMXOFF,
    /* 2D8 */ ZYDIS_MNEM_VMXON,
    /* 2D9 */ ZYDIS_MNEM_VORPD,
    /* 2DA */ ZYDIS_MNEM_VORPS,
    /* 2DB */ ZYDIS_MNEM_VPABSB,
    /* 2DC */ ZYDIS_MNEM_VPABSD,
    /* 2DD */ ZYDIS_MNEM_VPABSW,
    /* 2DE */ ZYDIS_MNEM_VPACKSSDW,
    /* 2DF */ ZYDIS_MNEM_VPACKSSWB,
    /* 2E0 */ ZYDIS_MNEM_VPACKUSDW,
    /* 2E1 */ ZYDIS_MNEM_VPACKUSWB,
    /* 2E2 */ ZYDIS_MNEM_VPADDB,
    /* 2E3 */ ZYDIS_MNEM_VPADDD,
    /* 2E4 */ ZYDIS_MNEM_VPADDQ,
    /* 2E5 */ ZYDIS_MNEM_VPADDSB,
    /* 2E6 */ ZYDIS_MNEM_VPADDSW,
    /* 2E7 */ ZYDIS_MNEM_VPADDUSB,
    /* 2E8 */ ZYDIS_MNEM_VPADDUSW,
    /* 2E9 */ ZYDIS_MNEM_VPADDW,
    /* 2EA */ ZYDIS_MNEM_VPALIGNR,
    /* 2EB */ ZYDIS_MNEM_VPAND,
    /* 2EC */ ZYDIS_MNEM_VPANDN,
    /* 2ED */ ZYDIS_MNEM_VPAVGB,
    /* 2EE */ ZYDIS_MNEM_VPAVGW,
    /* 2EF */ ZYDIS_MNEM_VPBLENDVB,
    /* 2F0 */ ZYDIS_MNEM_VPBLENDW,
    /* 2F1 */ ZYDIS_MNEM_VPCLMULQDQ,
    /* 2F2 */ ZYDIS_MNEM_VPCMPEQB,
    /* 2F3 */ ZYDIS_MNEM_VPCMPEQD,
    /* 2F4 */ ZYDIS_MNEM_VPCMPEQQ,
    /* 2F5 */ ZYDIS_MNEM_VPCMPEQW,
    /* 2F6 */ ZYDIS_MNEM_VPCMPESTRI,
    /* 2F7 */ ZYDIS_MNEM_VPCMPESTRM,
    /* 2F8 */ ZYDIS_MNEM_VPCMPGTB,
    /* 2F9 */ ZYDIS_MNEM_VPCMPGTD,
    /* 2FA */ ZYDIS_MNEM_VPCMPGTQ,
    /* 2FB */ ZYDIS_MNEM_VPCMPGTW,
    /* 2FC */ ZYDIS_MNEM_VPCMPISTRI,
    /* 2FD */ ZYDIS_MNEM_VPCMPISTRM,
    /* 2FE */ ZYDIS_MNEM_VPERM2F128,
    /* 2FF */ ZYDIS_MNEM_VPERMILPD,
    /* 300 */ ZYDIS_MNEM_VPERMILPS,
    /* 301 */ ZYDIS_MNEM_VPEXTRB,
    /* 302 */ ZYDIS_MNEM_VPEXTRD,
    /* 303 */ ZYDIS_MNEM_VPEXTRQ,
    /* 304 */ ZYDIS_MNEM_VPEXTRW,
    /* 305 */ ZYDIS_MNEM_VPHADDD,
    /* 306 */ ZYDIS_MNEM_VPHADDSW,
    /* 307 */ ZYDIS_MNEM_VPHADDW,
    /* 308 */ ZYDIS_MNEM_VPHMINPOSUW,
    /* 309 */ ZYDIS_MNEM_VPHSUBD,
    /* 30A */ ZYDIS_MNEM_VPHSUBSW,
    /* 30B */ ZYDIS_MNEM_VPHSUBW,
    /* 30C */ ZYDIS_MNEM_VPINSRB,
    /* 30D */ ZYDIS_MNEM_VPINSRD,
    /* 30E */ ZYDIS_MNEM_VPINSRQ,
    /* 30F */ ZYDIS_MNEM_VPINSRW,
    /* 310 */ ZYDIS_MNEM_VPMADDUBSW,
    /* 311 */ ZYDIS_MNEM_VPMADDWD,
    /* 312 */ ZYDIS_MNEM_VPMAXSB,
    /* 313 */ ZYDIS_MNEM_VPMAXSD,
    /* 314 */ ZYDIS_MNEM_VPMAXSW,
    /* 315 */ ZYDIS_MNEM_VPMAXUB,
    /* 316 */ ZYDIS_MNEM_VPMAXUD,
    /* 317 */ ZYDIS_MNEM_VPMAXUW,
    /* 318 */ ZYDIS_MNEM_VPMINSB,
    /* 319 */ ZYDIS_MNEM_VPMINSD,
    /* 31A */ ZYDIS_MNEM_VPMINSW,
    /* 31B */ ZYDIS_MNEM_VPMINUB,
    /* 31C */ ZYDIS_MNEM_VPMINUD,
    /* 31D */ ZYDIS_MNEM_VPMINUW,
    /* 31E */ ZYDIS_MNEM_VPMOVMSKB,
    /* 31F */ ZYDIS_MNEM_VPMOVSXBD,
    /* 320 */ ZYDIS_MNEM_VPMOVSXBQ,
    /* 321 */ ZYDIS_MNEM_VPMOVSXBW,
    /* 322 */ ZYDIS_MNEM_VPMOVSXWD,
    /* 323 */ ZYDIS_MNEM_VPMOVSXWQ,
    /* 324 */ ZYDIS_MNEM_VPMOVZXBD,
    /* 325 */ ZYDIS_MNEM_VPMOVZXBQ,
    /* 326 */ ZYDIS_MNEM_VPMOVZXBW,
    /* 327 */ ZYDIS_MNEM_VPMOVZXDQ,
    /* 328 */ ZYDIS_MNEM_VPMOVZXWD,
    /* 329 */ ZYDIS_MNEM_VPMOVZXWQ,
    /* 32A */ ZYDIS_MNEM_VPMULDQ,
    /* 32B */ ZYDIS_MNEM_VPMULHRSW,
    /* 32C */ ZYDIS_MNEM_VPMULHUW,
    /* 32D */ ZYDIS_MNEM_VPMULHW,
    /* 32E */ ZYDIS_MNEM_VPMULLD,
    /* 32F */ ZYDIS_MNEM_VPMULLW,
    /* 330 */ ZYDIS_MNEM_VPOR,
    /* 331 */ ZYDIS_MNEM_VPSADBW,
    /* 332 */ ZYDIS_MNEM_VPSHUFB,
    /* 333 */ ZYDIS_MNEM_VPSHUFD,
    /* 334 */ ZYDIS_MNEM_VPSHUFHW,
    /* 335 */ ZYDIS_MNEM_VPSHUFLW,
    /* 336 */ ZYDIS_MNEM_VPSIGNB,
    /* 337 */ ZYDIS_MNEM_VPSIGND,
    /* 338 */ ZYDIS_MNEM_VPSIGNW,
    /* 339 */ ZYDIS_MNEM_VPSLLD,
    /* 33A */ ZYDIS_MNEM_VPSLLDQ,
    /* 33B */ ZYDIS_MNEM_VPSLLQ,
    /* 33C */ ZYDIS_MNEM_VPSLLW,
    /* 33D */ ZYDIS_MNEM_VPSRAD,
    /* 33E */ ZYDIS_MNEM_VPSRAW,
    /* 33F */ ZYDIS_MNEM_VPSRLD,
    /* 340 */ ZYDIS_MNEM_VPSRLDQ,
    /* 341 */ ZYDIS_MNEM_VPSRLQ,
    /* 342 */ ZYDIS_MNEM_VPSRLW,
    /* 343 */ ZYDIS_MNEM_VPSUBB,
    /* 344 */ ZYDIS_MNEM_VPSUBD,
    /* 345 */ ZYDIS_MNEM_VPSUBQ,
    /* 346 */ ZYDIS_MNEM_VPSUBSB,
    /* 347 */ ZYDIS_MNEM_VPSUBSW,
    /* 348 */ ZYDIS_MNEM_VPSUBUSB,
    /* 349 */ ZYDIS_MNEM_VPSUBUSW,
    /* 34A */ ZYDIS_MNEM_VPSUBW,
    /* 34B */ ZYDIS_MNEM_VPTEST,
    /* 34C */ ZYDIS_MNEM_VPUNPCKHBW,
    /* 34D */ ZYDIS_MNEM_VPUNPCKHDQ,
    /* 34E */ ZYDIS_MNEM_VPUNPCKHQDQ,
    /* 34F */ ZYDIS_MNEM_VPUNPCKHWD,
    /* 350 */ ZYDIS_MNEM_VPUNPCKLBW,
    /* 351 */ ZYDIS_MNEM_VPUNPCKLDQ,
    /* 352 */ ZYDIS_MNEM_VPUNPCKLQDQ,
    /* 353 */ ZYDIS_MNEM_VPUNPCKLWD,
    /* 354 */ ZYDIS_MNEM_VPXOR,
    /* 355 */ ZYDIS_MNEM_VRCPPS,
    /* 356 */ ZYDIS_MNEM_VRCPSS,
    /* 357 */ ZYDIS_MNEM_VROUNDPD,
    /* 358 */ ZYDIS_MNEM_VROUNDPS,
    /* 359 */ ZYDIS_MNEM_VROUNDSD,
    /* 35A */ ZYDIS_MNEM_VROUNDSS,
    /* 35B */ ZYDIS_MNEM_VRSQRTPS,
    /* 35C */ ZYDIS_MNEM_VRSQRTSS,
    /* 35D */ ZYDIS_MNEM_VSHUFPD,
    /* 35E */ ZYDIS_MNEM_VSHUFPS,
    /* 35F */ ZYDIS_MNEM_VSQRTPD,
    /* 360 */ ZYDIS_MNEM_VSQRTPS,
    /* 361 */ ZYDIS_MNEM_VSQRTSD,
    /* 362 */ ZYDIS_MNEM_VSQRTSS,
    /* 363 */ ZYDIS_MNEM_VSTMXCSR,
    /* 364 */ ZYDIS_MNEM_VSUBPD,
    /* 365 */ ZYDIS_MNEM_VSUBPS,
    /* 366 */ ZYDIS_MNEM_VSUBSD,
    /* 367 */ ZYDIS_MNEM_VSUBSS,
    /* 368 */ ZYDIS_MNEM_VTESTPD,
    /* 369 */ ZYDIS_MNEM_VTESTPS,
    /* 36A */ ZYDIS_MNEM_VUCOMISD,
    /* 36B */ ZYDIS_MNEM_VUCOMISS,
    /* 36C */ ZYDIS_MNEM_VUNPCKHPD,
    /* 36D */ ZYDIS_MNEM_VUNPCKHPS,
    /* 36E */ ZYDIS_MNEM_VUNPCKLPD,
    /* 36F */ ZYDIS_MNEM_VUNPCKLPS,
    /* 370 */ ZYDIS_MNEM_VXORPD,
    /* 371 */ ZYDIS_MNEM_VXORPS,
    /* 372 */ ZYDIS_MNEM_VZEROALL,
    /* 373 */ ZYDIS_MNEM_VZEROUPPER,
    /* 374 */ ZYDIS_MNEM_WAIT,
    /* 375 */ ZYDIS_MNEM_WBINVD,
    /* 376 */ ZYDIS_MNEM_WRMSR,
    /* 377 */ ZYDIS_MNEM_XADD,
    /* 378 */ ZYDIS_MNEM_XCHG,
    /* 379 */ ZYDIS_MNEM_XCRYPTCBC,
    /* 37A */ ZYDIS_MNEM_XCRYPTCFB,
    /* 37B */ ZYDIS_MNEM_XCRYPTCTR,
    /* 37C */ ZYDIS_MNEM_XCRYPTECB,
    /* 37D */ ZYDIS_MNEM_XCRYPTOFB,
    /* 37E */ ZYDIS_MNEM_XGETBV,
    /* 37F */ ZYDIS_MNEM_XLATB,
    /* 380 */ ZYDIS_MNEM_XOR,
    /* 381 */ ZYDIS_MNEM_XORPD,
    /* 382 */ ZYDIS_MNEM_XORPS,
    /* 383 */ ZYDIS_MNEM_XRSTOR,
    /* 384 */ ZYDIS_MNEM_XSAVE,
    /* 385 */ ZYDIS_MNEM_XSETBV,
    /* 386 */ ZYDIS_MNEM_XSHA1,
    /* 387 */ ZYDIS_MNEM_XSHA256,
    /* 388 */ ZYDIS_MNEM_XSTORE,

    ZYDIS_MNEM_FORCE_WORD = 0x7FFF
} ZydisInstructionMnemonic;

/* TODO: Port instruction definition types */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* _ZYDIS_API_H_ */
