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
    ZYDIS_OPERAND_ENCODING_MODRM_REG,
    ZYDIS_OPERAND_ENCODING_MODRM_RM,
    ZYDIS_OPERAND_ENCODING_OPCODE,
    ZYDIS_OPERAND_ENCODING_NDS,
    ZYDIS_OPERAND_ENCODING_MASK,
    ZYDIS_OPERAND_ENCODING_UIMM8_LO,
    ZYDIS_OPERAND_ENCODING_UIMM8_HI,
    ZYDIS_OPERAND_ENCODING_DISP8,
    ZYDIS_OPERAND_ENCODING_DISP16,
    ZYDIS_OPERAND_ENCODING_DISP32,
    ZYDIS_OPERAND_ENCODING_DISP64,
    ZYDIS_OPERAND_ENCODING_DISP16_32_64,
    ZYDIS_OPERAND_ENCODING_DISP32_32_64,
    ZYDIS_OPERAND_ENCODING_DISP16_32_32,
    ZYDIS_OPERAND_ENCODING_UIMM_CONST1,
    ZYDIS_OPERAND_ENCODING_UIMM8,
    ZYDIS_OPERAND_ENCODING_UIMM16,
    ZYDIS_OPERAND_ENCODING_UIMM32,
    ZYDIS_OPERAND_ENCODING_UIMM64,
    ZYDIS_OPERAND_ENCODING_UIMM16_32_64,
    ZYDIS_OPERAND_ENCODING_UIMM32_32_64,
    ZYDIS_OPERAND_ENCODING_UIMM16_32_32,
    ZYDIS_OPERAND_ENCODING_SIMM8,
    ZYDIS_OPERAND_ENCODING_SIMM16,
    ZYDIS_OPERAND_ENCODING_SIMM32,
    ZYDIS_OPERAND_ENCODING_SIMM64,
    ZYDIS_OPERAND_ENCODING_SIMM16_32_64,
    ZYDIS_OPERAND_ENCODING_SIMM32_32_64,
    ZYDIS_OPERAND_ENCODING_SIMM16_32_32,
    ZYDIS_OPERAND_ENCODING_JIMM8,
    ZYDIS_OPERAND_ENCODING_JIMM16,
    ZYDIS_OPERAND_ENCODING_JIMM32,
    ZYDIS_OPERAND_ENCODING_JIMM64,
    ZYDIS_OPERAND_ENCODING_JIMM16_32_64,
    ZYDIS_OPERAND_ENCODING_JIMM32_32_64,
    ZYDIS_OPERAND_ENCODING_JIMM16_32_32
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
    ZYDIS_OPERAND_VISIBILITY_INVALID,
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
    ZYDIS_OPERAND_ACTION_INVALID,
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
    ZYDIS_OPERAND_ACTION_CONDREAD,
    /**
     * @brief   The operand is conditionally written by the instruction (may write).
     */
    ZYDIS_OPERAND_ACTION_CONDWRITE,
    /**
     * @brief   The operand is read and conditionally written by the instruction (may write).
     */
    ZYDIS_OPERAND_ACTION_READ_CONDWRITE,
    /**
     * @brief   The operand is written and conditionally read by the instruction (must write).
     */
    ZYDIS_OPERAND_ACTION_CONDREAD_WRITE, 
};

/* ---------------------------------------------------------------------------------------------- */
/* Elements                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisElementType datatype.
 */
typedef uint8_t ZydisElementType;

/**
 * @brief   Values that represent element-types.
 */
enum ZydisElementTypes
{
    ZYDIS_ELEMENT_TYPE_INVALID,
    ZYDIS_ELEMENT_TYPE_VARIABLE,  // TODO: Remove
    ZYDIS_ELEMENT_TYPE_STRUCT,
    ZYDIS_ELEMENT_TYPE_UINT,
    ZYDIS_ELEMENT_TYPE_INT,
    ZYDIS_ELEMENT_TYPE_FLOAT16,
    ZYDIS_ELEMENT_TYPE_FLOAT32,
    ZYDIS_ELEMENT_TYPE_FLOAT64,
    ZYDIS_ELEMENT_TYPE_FLOAT80,
    ZYDIS_ELEMENT_TYPE_LONGBCD
};

/**
 * @brief   Defines the @c ZydisElementSize datatype.
 */
typedef uint16_t ZydisElementSize;

/* ---------------------------------------------------------------------------------------------- */
/* Operand info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandInfo struct.
 */
typedef struct ZydisOperandInfo_
{
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
     * @brief   The operand-action.
     */
    ZydisOperandAction action; 
    /**
     * @brief   The operand-encoding.
     */
    ZydisOperandEncoding encoding;
    /**
     * @brief   The logical size of the operand (in bytes).
     */
    uint16_t size; 
    /**
     * @brief   The element-type.
     */
    ZydisElementType elementType;
    /**
     * @brief   The size of a single element.
     */
    ZydisElementSize elementSize;
    /**
     * @brief   The number of elements.
     */
    uint16_t elementCount;
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
         * @brief   Signals, if the memory operand is only used for address generation.
         */
        ZydisBool isAddressGenOnly;
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
             * @brief   Signals, if the displacement value is used.
             */
            ZydisBool hasDisplacement;
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
         * @brief   Signals, if the immediate value contains a relative offset. You can use 
         *          @c ZydisUtilsCalcAbsoluteTargetAddress to determine the absolute address value.
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
    } imm;
} ZydisOperandInfo;

/* ============================================================================================== */
/* Instruction info                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Machine mode                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisMachineMode datatype.
 */
typedef uint8_t ZydisMachineMode;

/**
 * @brief   Values that represent machine modes.
 */
enum ZydisMachineModes
{
    ZYDIS_MACHINE_MODE_INVALID          =  0,
    /**
     * @brief 64 bit mode.
     */
    ZYDIS_MACHINE_MODE_LONG_64          = 64,
    /**
     * @brief 32 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LONG_COMPAT_32   = 32,
    /**
     * @brief 16 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LONG_COMPAT_16   = 16,
    /**
     * @brief 32 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LEGACY_32        = 32,
    /**
     * @brief 16 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LEGACY_16        = 16,
    /**
     * @brief 16 bit real mode.
     */
    ZYDIS_MACHINE_MODE_REAL_16          = 16 
};

/* ---------------------------------------------------------------------------------------------- */
/* Address width                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAddressWidth datatype.
 */
typedef uint8_t ZydisAddressWidth;

/**
 * @brief   Values that represent address widths.
 */
enum ZydisAddressWidths
{
    ZYDIS_ADDRESS_WIDTH_INVALID         =  0,
    ZYDIS_ADDRESS_WIDTH_16              = 16,
    ZYDIS_ADDRESS_WIDTH_32              = 32,
    ZYDIS_ADDRESS_WIDTH_64              = 64
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
     * @brief   The instruction uses the default encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_DEFAULT  = 0x00,
    /**
     * @brief   The instruction uses the AMD 3DNow-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_3DNOW    = 0x01,
    /**
     * @brief   The instruction uses the AMD XOP-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_XOP      = 0x02,
    /**
     * @brief   The instruction uses the VEX-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_VEX      = 0x03,
    /**
     * @brief   The instruction uses the EVEX-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_EVEX     = 0x04,
    /**
     * @brief   The instruction uses the MVEX-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_MVEX     = 0x05
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
    ZYDIS_OPCODE_MAP_EX0        = 0x01,
    ZYDIS_OPCODE_MAP_0F         = 0x02,
    ZYDIS_OPCODE_MAP_0F38       = 0x03,
    ZYDIS_OPCODE_MAP_0F3A       = 0x04,
    ZYDIS_OPCODE_MAP_XOP8       = 0x05,
    ZYDIS_OPCODE_MAP_XOP9       = 0x06,
    ZYDIS_OPCODE_MAP_XOPA       = 0x07
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction attributes                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionAttributes datatype.
 */
typedef uint64_t ZydisInstructionAttributes;

// TODO: Update values

// TODO: Add IsAtomic

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
 * Priviliged instructions are any instructions that require a current ring level below 3.
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
/* AVX vector-length                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisVectorLength datatype.
 */
typedef uint16_t ZydisVectorLength;

/**
 * @brief   Values that represent vector-lengths.
 */
enum ZydisVectorLengths
{
    ZYDIS_VECTOR_LENGTH_INVALID =   0,
    ZYDIS_VECTOR_LENGTH_128     = 128,
    ZYDIS_VECTOR_LENGTH_256     = 256,
    ZYDIS_VECTOR_LENGTH_512     = 512
};

/* ---------------------------------------------------------------------------------------------- */
/* EVEX tuple-type                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisTupleType datatype.
 */
typedef uint8_t ZydisTupleType;

/**
 * @brief   Values that represent EVEX tuple-types.
 */
enum ZydisTupleTypes
{
    ZYDIS_TUPLETYPE_INVALID,
    /**
     * @brief   Full Vector
     */
    ZYDIS_TUPLETYPE_FV,
    /**
     * @brief   Half Vector
     */
    ZYDIS_TUPLETYPE_HV,
    /**
     * @brief   Full Vector Mem
     */
    ZYDIS_TUPLETYPE_FVM,
    /**
     * @brief   Tuple1 Scalar
     */
    ZYDIS_TUPLETYPE_T1S,
    /**
     * @brief   Tuple1 Fixed
     */
    ZYDIS_TUPLETYPE_T1F,
    /**
     * @brief   Tuple1 4x32
     */
    ZYDIS_TUPLETYPE_T1_4X,
    /**
     * @brief   Gather / Scatter
     */
    ZYDIS_TUPLETYPE_GSCAT,
    /**
     * @brief   Tuple2
     */
    ZYDIS_TUPLETYPE_T2,
    /**
     * @brief   Tuple4
     */
    ZYDIS_TUPLETYPE_T4,
    /**
     * @brief   Tuple8
     */
    ZYDIS_TUPLETYPE_T8,
    /**
     * @brief   Half Mem
     */
    ZYDIS_TUPLETYPE_HVM,
    /**
     * @brief   QuarterMem
     */
    ZYDIS_TUPLETYPE_QVM,
    /**
     * @brief   OctMem
     */
    ZYDIS_TUPLETYPE_OVM,
    /**
     * @brief   Mem128
     */
    ZYDIS_TUPLETYPE_M128,
    /**
     * @brief   MOVDDUP
     */
    ZYDIS_TUPLETYPE_DUP
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX mask mode                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisMaskMode datatype.
 */
typedef uint8_t ZydisMaskMode;

/**
 * @brief   Values that represent AVX mask-modes.
 */
enum ZydisMaskModes
{
    ZYDIS_MASKMODE_INVALID,
    /**
     * @brief   Merge mode. This is the default mode for all EVEX-instructions.
     */
    ZYDIS_MASKMODE_MERGE,
    /**
     * @brief   The zeroing mode is enabled for this instruction.
     */
    ZYDIS_MASKMODE_ZERO
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX broadcast-mode                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisBroadcastMode datatype.
 */
typedef uint16_t ZydisBroadcastMode;

/**
 * @brief   Values that represent AVX broadcast-modes.
 */
enum ZydisBroadcastModes
{
    ZYDIS_BCSTMODE_INVALID,
    ZYDIS_BCSTMODE_1_TO_2,
    ZYDIS_BCSTMODE_1_TO_4,
    ZYDIS_BCSTMODE_1_TO_8,
    ZYDIS_BCSTMODE_1_TO_16
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX rounding-mode                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisRoundingMode datatype.
 */
typedef uint8_t ZydisRoundingMode;

/**
 * @brief   Values that represent AVX rounding-modes.
 */
enum ZydisRoundingModes
{
    ZYDIS_RNDMODE_INVALID,
    /**
     * @brief   Round to nearest.
     */
    ZYDIS_RNDMODE_RN,
    /**
     * @brief   Round down.
     */
    ZYDIS_RNDMODE_RD,
    /**
     * @brief   Round up.
     */
    ZYDIS_RNDMODE_RU,
    /**
     * @brief   Round towards zero.
     */
    ZYDIS_RNDMODE_RZ,
    /**
     * @brief   Round to nearest and suppress all exceptions.
     */
    ZYDIS_RNDMODE_RN_SAE,
    /**
     * @brief   Round down and suppress all exceptions.
     */
    ZYDIS_RNDMODE_RD_SAE,
    /**
     * @brief   Round up and suppress all exceptions.
     */
    ZYDIS_RNDMODE_RU_SAE,
    /**
     * @brief   Round towards zero and suppress all exceptions.
     */
    ZYDIS_RNDMODE_RZ_SAE
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
     * @brief   The machine mode used to decode this instruction.
     */
    ZydisMachineMode machineMode;
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
     * @brief   The effective operand size.
     */
    uint8_t operandSize;
    /**
     * @brief   The effective address width.
     */
    uint8_t addressWidth;
    /**
     * @brief   The number of instruction-operands.
     */
    uint8_t operandCount;
    /**
     * @brief   Detailed info for all instruction operands.
     */
    ZydisOperandInfo operands[10];
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
     * @brief   Extended info for AVX instructions.
     */
    struct
    {
        /**
         * @brief   The AVX vector-length.
         */
        ZydisVectorLength vectorLength;
        /**
         * @brief   The AVX tuple-type (EVEX only).
         */
        ZydisTupleType tupleType;
        /**
         * @brief   The AVX element-size.
         */
        uint8_t elementSize;
        /**
         * @brief   The scale-factor for compressed 8-bit displacement values.
         */
        uint8_t compressedDisp8Scale;
        /**
         * @brief   The AVX mask-mode.
         */
        ZydisMaskMode maskMode;
        /**
         * @brief   The AVX broadcast-mode.
         */
        ZydisBroadcastMode broadcastMode;
        /**
         * @brief   The AVX rounding-mode.
         */
        ZydisRoundingMode roundingMode;
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
            uint8_t data[ZYDIS_MAX_INSTRUCTION_LENGTH - 1];
            uint8_t count;
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
        * @brief    Detailed info about the MVEX-prefix.
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
            uint8_t mmmm;
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
             * @brief   Non-temporal/eviction hint.
             */
            uint8_t E;
            /**
             * @brief   Swizzle/broadcast/up-convert/down-convert/static-rounding controls.
             */
            uint8_t SSS;
            /**
             * @brief   High-16 NDS/VIDX register specifier.
             */
            uint8_t V2;
            /**
             * @brief   Embedded opmask register specifier.
             */
            uint8_t kkk;
        } mvex;
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
         * @brief   Detailed info about displacement-bytes.
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
        /**
         * @brief   Detailed info about immediate-bytes.
         */
        struct
        {
            /**
             * @brief   Signals, if the immediate value is signed.
             */
            ZydisBool isSigned;  
            /**
             * @brief   Signals, if the immediate value contains a relative offset. You can use 
             *          @c ZydisUtilsCalcAbsoluteTargetAddress to determine the absolute address 
             *          value.
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
        } imm[2];
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
