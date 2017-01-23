/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd

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
 * @brief Defines the basic @c ZydisInstructionInfo and @c ZydisOperandInfo struct.
 */

#ifndef ZYDIS_INSTRUCTIONINFO_H
#define ZYDIS_INSTRUCTIONINFO_H

#include <Zydis/Types.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/Register.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Constants                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_MAX_INSTRUCTION_LENGTH 15

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Operand info                                                                                   */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Operand type                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandType datatype.
 */
typedef uint8_t ZydisOperandType;

/**
 * @brief   Values that represent operand-types.
 */
enum ZydisOperandTypes
{
    /**
     * @brief   The operand is not used.
     */
    ZYDIS_OPERAND_TYPE_UNUSED,
    /**
     * @brief   The operand is a register operand.
     */
    ZYDIS_OPERAND_TYPE_REGISTER,
    /**
     * @brief   The operand is a memory operand.
     */
    ZYDIS_OPERAND_TYPE_MEMORY,
    /**
     * @brief   The operand is a pointer operand with a segment:offset lvalue.
     */
    ZYDIS_OPERAND_TYPE_POINTER,
    /**
     * @brief   The operand is an immediate operand.
     */
    ZYDIS_OPERAND_TYPE_IMMEDIATE
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand encoding                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandEncoding datatype.
 */
typedef uint8_t ZydisOperandEncoding;

/**
 * @brief   Values that represent operand-encodings.
 */
enum ZydisOperandEncodings
{
    ZYDIS_OPERAND_ENCODING_NONE,
    /**
     * @brief   The operand is encoded in the ModRM.reg field.
     */
    ZYDIS_OPERAND_ENCODING_REG,
    /**
     * @brief   The operand is encoded in the ModRM.rm field.
     */
    ZYDIS_OPERAND_ENCODING_RM,
    /**
     * @brief   The operand is encoded in the ModRM.rm field and uses the compressed-disp8 form.
     */
    ZYDIS_OPERAND_ENCODING_RM_CD2,
    /**
     * @brief   The operand is encoded in the ModRM.rm field and uses the compressed-disp8 form.
     */
    ZYDIS_OPERAND_ENCODING_RM_CD4,
    /**
     * @brief   The operand is encoded in the ModRM.rm field and uses the compressed-disp8 form.
     */
    ZYDIS_OPERAND_ENCODING_RM_CD8,
    /**
     * @brief   The operand is encoded in the ModRM.rm field and uses the compressed-disp8 form.
     */
    ZYDIS_OPERAND_ENCODING_RM_CD16,
    /**
     * @brief   The operand is encoded in the ModRM.rm field and uses the compressed-disp8 form.
     */
    ZYDIS_OPERAND_ENCODING_RM_CD32,
    /**
     * @brief   The operand is encoded in the ModRM.rm field and uses the compressed-disp8 form.
     */
    ZYDIS_OPERAND_ENCODING_RM_CD64,
    /**
     * @brief   The operand is encoded in the lower 4 bits of the opcode (register only).
     */
    ZYDIS_OPERAND_ENCODING_OPCODE,
    /**
     * @brief   The operand is encoded in the VEX/EVEX.vvvv field.
     */
    ZYDIS_OPERAND_ENCODING_VVVV,
    /**
     * @brief   The operand is encoded in the EVEX.aaa field.
     */
    ZYDIS_OPERAND_ENCODING_AAA,
    /**
     * @brief   The operand is encoded in the low-part of an 8-bit immediate value.
     */
    ZYDIS_OPERAND_ENCODING_IMM8_LO,
    /**
     * @brief   The operand is encoded in the high-part of an 8-bit immediate value.
     */
    ZYDIS_OPERAND_ENCODING_IMM8_HI,
    /**
     * @brief   The operand is encoded as an 8-bit immediate value.
     */
    ZYDIS_OPERAND_ENCODING_IMM8,
    /**
     * @brief   The operand is encoded as an 16-bit immediate value.
     */
    ZYDIS_OPERAND_ENCODING_IMM16,
    /**
     * @brief   The operand is encoded as an 32-bit immediate value.
     */
    ZYDIS_OPERAND_ENCODING_IMM32,
    /**
     * @brief   The operand is encoded as an 64-bit immediate value.
     */
    ZYDIS_OPERAND_ENCODING_IMM64
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand visibility                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandVisibility datatype.
 */
typedef uint8_t ZydisOperandVisibility;

/**
 * @brief   Values that represent operand-visibilities.
 */
enum ZydisOperandVisibilities
{
    /**
     * @brief   The operand is explicitly encoded in the instruction. 
     */
    ZYDIS_OPERAND_VISIBILITY_EXPLICIT,
    /**
     * @brief   The operand is part of the opcode, but listed as an operand.
     */
    ZYDIS_OPERAND_VISIBILITY_IMPLICIT,
    /**
     * @brief   The operand is part of the opcode, and not typically listed as an operand.
     */
    ZYDIS_OPERAND_VISIBILITY_HIDDEN
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand action                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandAction datatype.
 */
typedef uint8_t ZydisOperandAction;

/**
 * @brief   Values that represent operand-actions.
 */
enum ZydisOperandActions
{
    /**
     * @brief   The operand is read by the instruction.
     */
    ZYDIS_OPERAND_ACTION_READ,
    /**
     * @brief   The operand is written by the instruction (must write).
     */
    ZYDIS_OPERAND_ACTION_WRITE,
    /**
     * @brief   The operand is read and written by the instruction (must write).
     */
    ZYDIS_OPERAND_ACTION_READWRITE,
    /**
     * @brief   The operand is conditionally read by the instruction.
     */
    ZYDIS_OPERAND_ACTION_COND_READ,
    /**
     * @brief   The operand is conditionally written by the instruction (may write).
     */
    ZYDIS_OPERAND_ACTION_COND_WRITE,
    /**
     * @brief   The operand is read and conditionally written by the instruction (may write).
     */
    ZYDIS_OPERAND_ACTION_READ_COND_WRITE,
    /**
     * @brief   The operand is written conditionally read by the instruction (must write).
     */
    ZYDIS_OPERAND_ACTION_WRITE_COND_READ, 
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandInfo struct.
 */
typedef struct ZydisOperandInfo_
{
    // semantic operand type ... temporary
    uint32_t temp;
    /**
     * @brief   The operand-id.
     */
    uint8_t id;
    /**
     * @brief   The type of the operand.
     */
    ZydisOperandType type;
    /**
     * @brief   The visibility of the operand.
     */
    ZydisOperandVisibility visibility;
    /**
     * @brief   The operand-encoding (only valid for explicit operands).
     */
    ZydisOperandEncoding encoding;
    /**
     * @brief   The operand-action.
     */
    ZydisOperandAction action; 
    /**
     * @brief   The logical size of the operand (in bytes).
     */
    uint16_t size;    
    /**
     * @brief   Extended info for register-operands.
     */
    ZydisRegister reg;
    /**
     * @brief   Extended info for memory-operands.
     */
    struct
    {
        /**
         * @brief   The adress size (16, 32 or 64 bit).
         */
        uint8_t addressSize;
        /**
         * @brief   The segment register.
         */
        ZydisRegister segment;
        /**
         * @brief   The base register.
         */
        ZydisRegister base;
        /**
         * @brief   The index register.
         */
        ZydisRegister index;
        /**
         * @brief   The scale factor.
         */
        uint8_t scale;
        /**
         * @brief   Extended info for memory-operands with displacement.
         */
        struct
        {
            /**
             * @brief   The displacement value
             */
            union
            {
                int8_t sbyte;
                int16_t sword;
                int32_t sdword;
                int64_t sqword;
            } value;
            /**
             * @brief   The physical displacement size, in bits.
             */
            uint8_t dataSize;
            /**
             * @brief   The offset of the displacement data, relative to the beginning of the 
             *          instruction, in bytes.
             */
            uint8_t dataOffset;
        } disp;
    } mem;
    /**
     * @brief   Extended info for pointer-operands.
     */
    struct 
    {
        uint16_t segment;
        uint32_t offset;
    } ptr;
    /**
     * @brief   Extended info for immediate-operands.
     */
    struct
    {
        /**
         * @brief   Signals, if the immediate value is signed.
         */
        ZydisBool isSigned;
        /**
         * @brief   Signals, if the immediate value contains a relative offset.
         */
        ZydisBool isRelative;
        /**
         * @brief   The immediate value.
         */
        union 
        {
            int8_t sbyte;
            uint8_t ubyte;
            int16_t sword;
            uint16_t uword;
            int32_t sdword;
            uint32_t udword;
            int64_t sqword;
            uint64_t uqword;
        } value;
        /**
         * @brief   The physical immediate size, in bits.
         */
        uint8_t dataSize;
        /**
         * @brief   The offset of the immediate data, relative to the beginning of the 
         *          instruction, in bytes.
         */
        uint8_t dataOffset;
    } imm;
} ZydisOperandInfo;

/* ============================================================================================== */
/* Instruction info                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Disassembler mode                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisDisassemblerMode datatype.
 */
typedef uint8_t ZydisDisassemblerMode;

/**
 * @brief   Values that represent disassembler-modes.
 */
enum ZydisDisassemblerModes
{
    ZYDIS_DISASSEMBLER_MODE_16BIT = 16,
    ZYDIS_DISASSEMBLER_MODE_32BIT = 32,
    ZYDIS_DISASSEMBLER_MODE_64BIT = 64    
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction encoding                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionEncoding datatype.
 */
typedef uint8_t ZydisInstructionEncoding;

/**
 * @brief   Values that represent instruction-encodings.
 */
enum ZydisInstructionEncodings
{
    /**
     * @brief   The instruction uses the default operand-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_DEFAULT  = 0x00,
    /**
     * @brief   The instruction uses the AMD 3DNow operand-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_3DNOW    = 0x01,
    /**
     * @brief   The instruction uses the AMD XOP operand-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_XOP      = 0x02,
    /**
     * @brief   The instruction uses the VEX operand-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_VEX      = 0x03,
    /**
     * @brief   The instruction uses the EVEX operand-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_EVEX     = 0x04
};

/* ---------------------------------------------------------------------------------------------- */
/* Opcode map                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOpcodeMap map.
 */
typedef uint8_t ZydisOpcodeMap;

/**
 * @brief   Values that represent opcode-maps.
 */
enum ZydisOpcodeMaps
{
    ZYDIS_OPCODE_MAP_DEFAULT    = 0x00,
    ZYDIS_OPCODE_MAP_0F         = 0x01,
    ZYDIS_OPCODE_MAP_0F38       = 0x02,
    ZYDIS_OPCODE_MAP_0F3A       = 0x03,
    ZYDIS_OPCODE_MAP_XOP8       = 0x04,
    ZYDIS_OPCODE_MAP_XOP9       = 0x05,
    ZYDIS_OPCODE_MAP_XOPA       = 0x06
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction attributes                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionAttributes datatype.
 */
typedef uint64_t ZydisInstructionAttributes;

/**
 * @brief   The instruction has the ModRM byte.
 */
#define ZYDIS_ATTRIB_HAS_MODRM                  0x0000000000000001
/**
 * @brief   The instruction has the SUB byte.
 */
#define ZYDIS_ATTRIB_HAS_SIB                    0x0000000000000002
/**
 * @brief   The instruction has the REX prefix.
 */
#define ZYDIS_ATTRIB_HAS_REX                    0x0000000000000004
/**
 * @brief   The instruction has the XOP prefix.
 */
#define ZYDIS_ATTRIB_HAS_XOP                    0x0000000000000008
/**
 * @brief   The instruction has the VEX prefix.
 */
#define ZYDIS_ATTRIB_HAS_VEX                    0x0000000000000010
/**
 * @brief   The instruction has the EVEX prefix.
 */
#define ZYDIS_ATTRIB_HAS_EVEX                   0x0000000000000020
/**
 * @brief   The instruction has one or more operands with position-relative offsets.
 */
#define ZYDIS_ATTRIB_IS_RELATIVE                0x0000000000000040
/**
 * @brief   The instruction is privileged.
 *
 * Priviliged instructions are any instructions that require a current ring
 * level below 3 or even SMM.
 */
#define ZYDIS_ATTRIB_IS_PRIVILEGED              0x0000000000000080
/**
 * @brief   The instruction accepts the lock prefix (0xF0). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_LOCK               0x0000000000000100
/**
 * @brief   The instruction accepts the rep prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_REP                0x0000000000000200
/**
 * @brief   The instruction accepts the repe/repz prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_REPE               0x0000000000000400
/**
 * @brief   The instruction accepts the repe/repz prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_REPZ               0x0000000000000400
/**
 * @brief   The instruction accepts the repne/repnz prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_REPNE              0x0000000000000800
/**
 * @brief   The instruction accepts the repne/repnz prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_REPNZ              0x0000000000000800
/**
 * @brief   The instruction accepts the bound prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_BOUND              0x0000000000001000
/**
 * @brief   The instruction accepts the xacquire prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_XACQUIRE           0x0000000000002000
/**
 * @brief   The instruction accepts the xrelease prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_ACCEPTS_XRELEASE           0x0000000000004000
/**
 * @brief   The instruction accepts the xacquire/xrelease prefixes (0xF2, 0xF3) without the
 *          lock-prefix (0x0F).
 */
#define ZYDIS_ATTRIB_ACCEPTS_HLE_WITHOUT_LOCK   0x0000000000008000
/**
 * @brief   The instruction accepts branch hints (0x2E, 0x3E).
 */
#define ZYDIS_ATTRIB_ACCEPTS_BRANCH_HINTS       0x0000000000010000
/**
 * @brief   The instruction accepts segment prefixes (0x2E, 0x36, 0x3E, 0x26, 0x64, 0x65).
 */
#define ZYDIS_ATTRIB_ACCEPTS_SEGMENT            0x0000000000020000
/**
 * @brief   The instruction accepts the operand-size prefix (0x66).
 */
#define ZYDIS_ATTRIB_ACCEPTS_OPERANDSIZE        0x0000000000040000
/**
 * @brief   The instruction accepts the address-size prefix (0x67).
 */
#define ZYDIS_ATTRIB_ACCEPTS_ADDRESSSIZE        0x0000000000080000
/**
 * @brief   The instruction has the lock prefix (0xF0). 
 */
#define ZYDIS_ATTRIB_HAS_LOCK                   0x0000000000100000
/**
 * @brief   The instruction has the rep prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_HAS_REP                    0x0000000000200000
/**
 * @brief   The instruction has the repe/repz prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_HAS_REPE                   0x0000000000400000
/**
 * @brief   The instruction has the repe/repz prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_HAS_REPZ                   0x0000000000400000
/**
 * @brief   The instruction has the repne/repnz prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_HAS_REPNE                  0x0000000000800000
/**
 * @brief   The instruction has the repne/repnz prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_HAS_REPNZ                  0x0000000000800000
/**
 * @brief   The instruction has the bound prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_HAS_BOUND                  0x0000000001000000
/**
 * @brief   The instruction has the xacquire prefix (0xF2). 
 */
#define ZYDIS_ATTRIB_HAS_XACQUIRE               0x0000000002000000
/**
 * @brief   The instruction has the xrelease prefix (0xF3). 
 */
#define ZYDIS_ATTRIB_HAS_XRELEASE               0x0000000004000000
/**
 * @brief   The instruction has the branch-not-taken hint (0x2E). 
 */
#define ZYDIS_ATTRIB_HAS_BRANCH_NOT_TAKEN       0x0000000008000000
/**
 * @brief   The instruction has the branch-taken hint (0x3E). 
 */
#define ZYDIS_ATTRIB_HAS_BRANCH_TAKEN           0x0000000010000000
/**
 * @brief   The instruction has a segment modifier.
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT                0x00000007E0000000
/**
 * @brief   The instruction has the CS segment modifier (0x2E). 
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT_CS             0x0000000020000000
/**
 * @brief   The instruction has the SS segment modifier (0x36). 
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT_SS             0x0000000040000000
/**
 * @brief   The instruction has the DS segment modifier (0x3E). 
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT_DS             0x0000000080000000
/**
 * @brief   The instruction has the ES segment modifier (0x26). 
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT_ES             0x0000000100000000
/**
 * @brief   The instruction has the FS segment modifier (0x64). 
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT_FS             0x0000000200000000
/**
 * @brief   The instruction has the GS segment modifier (0x65). 
 */
#define ZYDIS_ATTRIB_HAS_SEGMENT_GS             0x0000000400000000
/**
 * @brief   The instruction has the operand-size prefix (0x66). 
 */
#define ZYDIS_ATTRIB_HAS_OPERANDSIZE            0x0000000800000000
/**
 * @brief   The instruction has the address-size prefix (0x67). 
 */
#define ZYDIS_ATTRIB_HAS_ADDRESSSIZE            0x0000001000000000

/* ---------------------------------------------------------------------------------------------- */
/* AVX mask policy                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVX512MaskPolicy datatype.
 */
typedef uint8_t ZydisAVX512MaskPolicy;

/**
 * @brief   Values that represent avx-512 mask-policies.
 */
enum ZydisAVX512MaskPolicies
{
    ZYDIS_AVX512_MASKPOLICY_INVALID,
    /**
     * @brief   The instruction accepts mask-registers other than the default-mask (@c REG_K0), but
     *          does not require them.
     */
    ZYDIS_AVX512_MASKPOLICY_MASK_ACCEPTED,
    /**
     * @brief   The instruction requires a mask-register other than the default-mask (@c REG_K0).
     */
    ZYDIS_AVX512_MASKPOLICY_MASK_REQUIRED,
    /**
     * @brief   The instruction does not allow a mask-register other than the default-mask 
     *          (@c REG_K0).
     */
    ZYDIS_AVX512_MASKPOLICY_MASK_FORBIDDEN
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX mask mode                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVX512MaskMode datatype.
 */
typedef uint8_t ZydisAVX512MaskMode;

/**
 * @brief   Values that represent avx-512 mask-modes.
 */
enum ZydisAVX512MaskModes
{
    ZYDIS_AVX512_MASKMODE_INVALID,
    /**
     * @brief   Merge mode. This is the default mode for all EVEX-instructions.
     */
    ZYDIS_AVX512_MASKMODE_MERGE,
    /**
     * @brief   The zeroing mode is enabled for this instruction.
     */
    ZYDIS_AVX512_MASKMODE_ZERO
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX broadcast type                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVX512BroadcastType datatype.
 */
typedef uint8_t ZydisAVX512BroadcastType;

/**
 * @brief   Values that represent avx-512 broadcast-types.
 */
enum ZydisAVX512BroadcastTypes
{
    ZYDIS_AVX512_BCSTMODE_INVALID,
    /**
     * @brief   1to2 broadcast.
     */
    ZYDIS_AVX512_BCSTMODE_2,
    /**
     * @brief   1to4 broadcast.
     */
    ZYDIS_AVX512_BCSTMODE_4,
    /**
     * @brief   1to8 broadcast.
     */
    ZYDIS_AVX512_BCSTMODE_8,
    /**
     * @brief   1to16 broadcast.
     */
    ZYDIS_AVX512_BCSTMODE_16
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX rounding mode                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVX512RoundingMode datatype.
 */
typedef uint8_t ZydisAVX512RoundingMode;

/**
 * @brief   Values that represent avx-512 rounding-modes.
 */
enum ZydisAVXRoundingModes
{
    ZYDIS_AVX_RNDMODE_INVALID,
    /**
     * @brief   Round to nearest.
     */
    ZYDIS_AVX_RNDMODE_RN,
    /**
     * @brief   Round down.
     */
    ZYDIS_AVX_RNDMODE_RD,
    /**
     * @brief   Round up.
     */
    ZYDIS_AVX_RNDMODE_RU,
    /**
     * @brief   Round towards zero.
     */
    ZYDIS_AVX_RNDMODE_RZ
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction info                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis instruction info struct.
 */
typedef struct ZydisInstructionInfo_
{
    /**
     * @brief   The disassembler-mode used to decode this instruction.
     */
    ZydisDisassemblerMode mode;
    /**
     * @brief   The instruction-mnemonic.
     */
    ZydisInstructionMnemonic mnemonic;  
    /**
     * @brief   The length of the decoded instruction.
     */
    uint8_t length;
    /**
     * @brief   The raw bytes of the decoded instruction.
     */
    uint8_t data[15];
    /**
     * @brief   The instruction-encoding (default, 3DNow, VEX, EVEX, XOP).
     */
    ZydisInstructionEncoding encoding;
    /**
     * @brief   The opcode-map.
     */
    ZydisOpcodeMap opcodeMap;
    /**
     * @brief   The instruction-opcode.
     */
    uint8_t opcode;
    /**
     * @brief   The number of instruction-operands.
     */
    uint8_t operandCount;
    /**
     * @brief   Detailed info for all instruction operands.
     */
    ZydisOperandInfo operands[5];
    /**
     * @brief  Instruction attributes.
     */
    ZydisInstructionAttributes attributes;
    /**
     * @brief   The instruction address points at the current instruction (relative to the 
     *          initial instruction pointer).
     */
    uint64_t instrAddress;
    /**
     * @brief   The instruction pointer points at the address of the next instruction (relative
     *          to the initial instruction pointer). 
     *          
     * This field is used to properly format relative instructions.
     */
    uint64_t instrPointer;
    /**
     * @brief   Extended info for avx-related instructions.
     */
    struct
    {
        /**
         * @brief   The AVX mask-policy.
         */
        ZydisAVX512MaskPolicy maskPolicy;
        /**
         * @brief   The AVX mask-mode.
         */
        ZydisAVX512MaskMode maskMode; 
        /**
         * @brief   The AVX mask-register.
         */
        ZydisRegister maskRegister;
        /**
         * @brief   The avx-512 broadcast-type.
         */
        ZydisAVX512BroadcastType broadcast;
        /**
         * @brief   The avx-512 rounding-mode.
         */
        ZydisAVX512RoundingMode roundingMode;
        /**
         * @brief   @c TRUE, if the avx-512 suppress-all-exceptions flag is set.
         */
        ZydisBool hasSAE;
    } avx;    
    /**
     * @brief   Extended info about different instruction-parts like ModRM, SIB or 
     *          encoding-prefixes.
     */
    struct
    {
        /**
         * @brief   Detailed info about the legacy prefixes
         */
        struct
        {
            uint8_t hasF0;
            uint8_t hasF3;
            uint8_t hasF2;
            uint8_t has2E;
            uint8_t has36;
            uint8_t has3E;
            uint8_t has26;
            uint8_t has64;
            uint8_t has65;
            uint8_t has66;
            uint8_t has67;
        } prefixes;
        /**
         * @brief   Detailed info about the REX-prefix.
         */
        struct
        {
            /**
             * @brief   @c TRUE if the prefix got already decoded.
             */
            ZydisBool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[1];
            /**
             * @brief   64-bit operand-size promotion.
             */
            uint8_t W;
            /**
             * @brief   Extension of the ModRM.reg field.
             */
            uint8_t R;
            /**
             * @brief   Extension of the SIB.index field.
             */
            uint8_t X;
            /**
             * @brief   Extension of the ModRM.rm, SIB.base, or opcode.reg field.
             */
            uint8_t B;
        } rex; 
        /**
         * @brief   Detailed info about the XOP-prefix.
         */
        struct
        {
            /**
             * @brief   @c TRUE if the prefix got already decoded.
             */
            ZydisBool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[3];
            /**
             * @brief   Extension of the ModRM.reg field (inverted).
             */
            uint8_t R;
            /**
             * @brief   Extension of the SIB.index field (inverted).
             */
            uint8_t X;
            /**
             * @brief   Extension of the ModRM.rm, SIB.base, or opcode.reg field (inverted).
             */
            uint8_t B;
            /**
             * @brief   Opcode-map specifier.
             */
            uint8_t m_mmmm;
            /**
             * @brief   64-bit operand-size promotion or opcode-extension.
             */
            uint8_t W;
            /**
             * @brief   NDS register specifier (inverted).
             */
            uint8_t vvvv;
            /**
             * @brief   Vector-length specifier.
             */
            uint8_t L;
            /**
             * @brief   Compressed legacy prefix.
             */
            uint8_t pp;
        } xop;
        /**
         * @brief   Detailed info about the VEX-prefix.
         */
        struct
        {
            /**
             * @brief   @c TRUE if the prefix got already decoded.
             */
            ZydisBool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[3];
            /**
             * @brief   Extension of the ModRM.reg field (inverted).
             */
            uint8_t R;
            /**
             * @brief   Extension of the SIB.index field (inverted).
             */
            uint8_t X;
            /**
             * @brief   Extension of the ModRM.rm, SIB.base, or opcode.reg field (inverted).
             */
            uint8_t B;
            /**
             * @brief   Opcode-map specifier.
             */
            uint8_t m_mmmm;
            /**
             * @brief   64-bit operand-size promotion or opcode-extension.
             */
            uint8_t W;
            /**
             * @brief   NDS register specifier (inverted).
             */
            uint8_t vvvv;
            /**
             * @brief   Vector-length specifier.
             */
            uint8_t L;
            /**
             * @brief   Compressed legacy prefix.
             */
            uint8_t pp;
        } vex;
        /**
         * @brief   Detailed info about the EVEX-prefix.
         */
        struct
        {
            /**
             * @brief   @c TRUE if the prefix got already decoded.
             */
            ZydisBool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[4];
            /**
             * @brief   Extension of the ModRM.reg field (inverted).
             */
            uint8_t R;
            /**
             * @brief   Extension of the SIB.index/vidx field (inverted).
             */
            uint8_t X;
            /**
             * @brief   Extension of the ModRM.rm or SIB.base field (inverted).
             */
            uint8_t B;
            /**
             * @brief   High-16 register specifier modifier (inverted).
             */
            uint8_t R2;
            /**
             * @brief   Opcode-map specifier.
             */
            uint8_t mm;
            /**
             * @brief   64-bit operand-size promotion or opcode-extension.
             */
            uint8_t W;
            /**
             * @brief   NDS register specifier (inverted).
             */
            uint8_t vvvv;
            /**
             * @brief   Compressed legacy prefix.
             */
            uint8_t pp;
            /**
             * @brief   Zeroing/Merging.
             */
            uint8_t z;
            /**
             * @brief   Vector-length specifier or rounding-control (most significant bit).
             */
            uint8_t L2;
            /**
             * @brief   Vector-length specifier or rounding-control (least significant bit).
             */
            uint8_t L;
            /**
             * @brief   Broadcast/RC/SAE Context.
             */
            uint8_t b;
            /**
             * @brief   High-16 NDS/VIDX register specifier.
             */
            uint8_t V2;
            /**
             * @brief   Embedded opmask register specifier.
             */
            uint8_t aaa;
        } evex;
        /**
         * @brief   Detailed info about the ModRM-byte.
         */
        struct
        {
            ZydisBool isDecoded;
            uint8_t data[1];
            uint8_t mod;
            uint8_t reg;
            uint8_t rm;
        } modrm;
        /**
         * @brief   Detailed info about the SIB-byte.
         */
        struct
        {
            ZydisBool isDecoded;
            uint8_t data[1];
            uint8_t scale;
            uint8_t index;
            uint8_t base;
        } sib;
        /**
         * @brief   Internal data.
         */
        struct
        {
            const void* definition;
            uint8_t W;
            uint8_t R;
            uint8_t X;
            uint8_t B;
            uint8_t L;
            uint8_t L2;
            uint8_t R2;
            uint8_t V2;
        } internal;  // TODO: Move into decoder struct
    } details;
    /**
     * @brief   This field is intended for custom data and may be freely set by the user.
     */
    void* userData;
} ZydisInstructionInfo;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INSTRUCTIONINFO_H */
