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
 * @brief   Defines the basic @c ZydisDecodedInstruction and @c ZydisDecodedOperand structs.
 */

#ifndef ZYDIS_INSTRUCTIONINFO_H
#define ZYDIS_INSTRUCTIONINFO_H

#include <Zydis/CommonTypes.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/Register.h>
#include <Zydis/SharedTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Decoded operand                                                                                */
/* ============================================================================================== */

/**
 * @brief   Defines the @c ZydisDecodedOperand struct.
 */
typedef struct ZydisDecodedOperand_
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
     * @brief   The logical size of the operand (in bits).
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
            int64_t value;
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
            uint64_t u;
            int64_t s;         
        } value;
    } imm;
} ZydisDecodedOperand;

/* ============================================================================================== */
/* Decoded instruction                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction attributes                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionAttributes datatype.
 */
typedef uint64_t ZydisInstructionAttributes;

// TODO: Update values

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
/* R/E/FLAGS info                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisCPUFlag datatype.
 */
typedef uint8_t ZydisCPUFlag;

/**
 * @brief   Defines the @c ZydisCPUFlagMask datatype.
 */
typedef uint32_t ZydisCPUFlagMask;

/**
 * @brief   Values that represent CPU-flags.
 */
enum ZydisCPUFlags
{
    /**
     * @brief   Carry flag.
     */
    ZYDIS_CPUFLAG_CF,
    /**
     * @brief   Parity flag.
     */
    ZYDIS_CPUFLAG_PF,
    /**
     * @brief   Adjust flag.
     */
    ZYDIS_CPUFLAG_AF,
    /**
     * @brief   Zero flag.
     */
    ZYDIS_CPUFLAG_ZF,
    /**
     * @brief   Sign flag.
     */
    ZYDIS_CPUFLAG_SF,
    /**
     * @brief   Trap flag.
     */
    ZYDIS_CPUFLAG_TF,
    /**
     * @brief   Interrupt enable flag.
     */
    ZYDIS_CPUFLAG_IF,
    /**
     * @brief   Direction flag.
     */
    ZYDIS_CPUFLAG_DF,
    /**
     * @brief   Overflow flag.
     */
    ZYDIS_CPUFLAG_OF,
    /**
     * @brief   I/O privilege level flag.
     */
    ZYDIS_CPUFLAG_IOPL,
    /**
     * @brief   Nested task flag.
     */
    ZYDIS_CPUFLAG_NT,
    /**
     * @brief   Resume flag.
     */
    ZYDIS_CPUFLAG_RF,
    /**
     * @brief   Virtual 8086 mode flag.
     */
    ZYDIS_CPUFLAG_VM,
    /**
     * @brief   Alignment check.
     */
    ZYDIS_CPUFLAG_AC,
    /**
     * @brief   Virtual interrupt flag.
     */
    ZYDIS_CPUFLAG_VIF,
    /**
     * @brief   Virtual interrupt pending.
     */
    ZYDIS_CPUFLAG_VIP,
    /**
     * @brief   Able to use CPUID instruction.
     */
    ZYDIS_CPUFLAG_ID,
    /**
     * @brief   FPU condition-code flag 0.
     */
    ZYDIS_CPUFLAG_C0,
    /**
     * @brief   FPU condition-code flag 1.
     */
    ZYDIS_CPUFLAG_C1,
    /**
     * @brief   FPU condition-code flag 2.
     */
    ZYDIS_CPUFLAG_C2,
    /**
     * @brief   FPU condition-code flag 3.
     */
    ZYDIS_CPUFLAG_C3,

    /**
     * @brief   Marker value.
     */
    ZYDIS_CPUFLAG_ENUM_COUNT
};

/**
 * @brief   Defines the @c ZydisCPUFlagAction datatype.
 */
typedef uint8_t ZydisCPUFlagAction;

/**
 * @brief   Values that represent CPU-flag actions.
 */
enum ZydisCPUFlagActions
{
    ZYDIS_CPUFLAG_ACTION_NONE,
    ZYDIS_CPUFLAG_ACTION_TESTED,
    ZYDIS_CPUFLAG_ACTION_MODIFIED,
    ZYDIS_CPUFLAG_ACTION_SET_0,
    ZYDIS_CPUFLAG_ACTION_SET_1,
    ZYDIS_CPUFLAG_ACTION_UNDEFINED
};

/* ---------------------------------------------------------------------------------------------- */
/* SSE/AVX exception-class                                                                        */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisExceptionClass datatype.
 */
typedef uint16_t ZydisExceptionClass;

/**
 * @brief   Values that represent exception-classes.
 */
enum ZydisExceptionClasses
{
    ZYDIS_EXCEPTION_CLASS_NONE,
    // TODO: SSE and AVX
    ZYDIS_EXCEPTION_CLASS_E1,
    ZYDIS_EXCEPTION_CLASS_E1NF,
    ZYDIS_EXCEPTION_CLASS_E2,
    ZYDIS_EXCEPTION_CLASS_E2NF,
    ZYDIS_EXCEPTION_CLASS_E3,
    ZYDIS_EXCEPTION_CLASS_E3NF,
    ZYDIS_EXCEPTION_CLASS_E4,
    ZYDIS_EXCEPTION_CLASS_E4NF,
    ZYDIS_EXCEPTION_CLASS_E5,
    ZYDIS_EXCEPTION_CLASS_E5NF,
    ZYDIS_EXCEPTION_CLASS_E6,
    ZYDIS_EXCEPTION_CLASS_E6NF,
    ZYDIS_EXCEPTION_CLASS_E7NM,
    ZYDIS_EXCEPTION_CLASS_E7NM128,
    ZYDIS_EXCEPTION_CLASS_E9NF,
    ZYDIS_EXCEPTION_CLASS_E10,
    ZYDIS_EXCEPTION_CLASS_E10NF,
    ZYDIS_EXCEPTION_CLASS_E11,
    ZYDIS_EXCEPTION_CLASS_E12,
    ZYDIS_EXCEPTION_CLASS_E12NP,
    ZYDIS_EXCEPTION_CLASS_K20,
    ZYDIS_EXCEPTION_CLASS_K21
};

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
    ZYDIS_MASK_MODE_INVALID,
    /**
     * @brief   The embedded mask register is used as a merge-mask. This is the default mode for 
     *          all EVEX/MVEX-instructions.
     */
    ZYDIS_MASK_MODE_MERGE,
    /**
     * @brief   The embedded mask register is used as a zero-mask.
     */
    ZYDIS_MASK_MODE_ZERO
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
    ZYDIS_BROADCAST_MODE_INVALID,
    ZYDIS_BROADCAST_MODE_1_TO_2,
    ZYDIS_BROADCAST_MODE_1_TO_4,
    ZYDIS_BROADCAST_MODE_1_TO_8,
    ZYDIS_BROADCAST_MODE_1_TO_16,
    ZYDIS_BROADCAST_MODE_1_TO_32,
    ZYDIS_BROADCAST_MODE_1_TO_64,
    ZYDIS_BROADCAST_MODE_2_TO_4,
    ZYDIS_BROADCAST_MODE_2_TO_8,
    ZYDIS_BROADCAST_MODE_2_TO_16,
    ZYDIS_BROADCAST_MODE_4_TO_8,
    ZYDIS_BROADCAST_MODE_4_TO_16,
    ZYDIS_BROADCAST_MODE_8_TO_16
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
    ZYDIS_ROUNDING_MODE_INVALID,
    /**
     * @brief   Round to nearest.
     */
    ZYDIS_ROUNDING_MODE_RN,
    /**
     * @brief   Round down.
     */
    ZYDIS_ROUNDING_MODE_RD,
    /**
     * @brief   Round up.
     */
    ZYDIS_ROUNDING_MODE_RU,
    /**
     * @brief   Round towards zero.
     */
    ZYDIS_ROUNDING_MODE_RZ
};

/* ---------------------------------------------------------------------------------------------- */
/* KNC swizzle-mode                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisSwizzleMode datatype.
 */
typedef uint16_t ZydisSwizzleMode;

/**
 * @brief   Values that represent swizzle-modes.
 */
enum ZydisSwizzleModes
{
    ZYDIS_SWIZZLE_MODE_INVALID,
    ZYDIS_SWIZZLE_MODE_DCBA,
    ZYDIS_SWIZZLE_MODE_CDAB,
    ZYDIS_SWIZZLE_MODE_BADC,
    ZYDIS_SWIZZLE_MODE_DACB,
    ZYDIS_SWIZZLE_MODE_AAAA,
    ZYDIS_SWIZZLE_MODE_BBBB,
    ZYDIS_SWIZZLE_MODE_CCCC,
    ZYDIS_SWIZZLE_MODE_DDDD
};

/* ---------------------------------------------------------------------------------------------- */
/* KNC conversion-mode                                                                            */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisConversionMode datatype.
 */
typedef uint16_t ZydisConversionMode;

/**
 * @brief   Values that represent conversion-modes.
 */
enum ZydisConversionModes
{
    ZYDIS_CONVERSION_MODE_INVALID,
    ZYDIS_CONVERSION_MODE_FLOAT16,
    ZYDIS_CONVERSION_MODE_SINT8,
    ZYDIS_CONVERSION_MODE_UINT8,
    ZYDIS_CONVERSION_MODE_SINT16,
    ZYDIS_CONVERSION_MODE_UINT16
};

/* ---------------------------------------------------------------------------------------------- */
/* Decoded instruction                                                                            */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisDecodedInstruction struct.
 */
typedef struct ZydisDecodedInstruction_
{
    /**
     * @brief   The machine mode used to decode this instruction.
     */
    ZydisMachineMode machineMode;
    /**
     * @brief   The instruction-mnemonic.
     */
    ZydisMnemonic mnemonic;  
    /**
     * @brief   The length of the decoded instruction.
     */
    uint8_t length;
    /**
     * @brief   The raw bytes of the decoded instruction.
     */
    uint8_t data[ZYDIS_MAX_INSTRUCTION_LENGTH];
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
     * @brief   The stack width.
     */
    uint8_t stackWidth;
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
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
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
     * @brief   Information about accessed CPU flags.
     */
    struct
    {
        /**
         * @brief   The CPU-flag action.
         * 
         * You can call `ZydisGetCPUFlagsByAction` to get a mask with all flags matching a specific
         * action.
         */
        ZydisCPUFlagAction action;
    } flags[ZYDIS_CPUFLAG_ENUM_COUNT];
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
         * @brief   Info about the embedded writemask-register.
         */
        struct
        {
            /**
             * @brief   The masking mode.
             */
            ZydisMaskMode mode;
            /**
             * @brief   The mask register.
             */
            ZydisRegister reg;
            /**
             * @brief   Signals, if the mask-register is used as a control mask. 
             */
            ZydisBool isControlMask;
        } mask;
        /**
         * @brief   Contains info about the AVX broadcast-factor.
         */
        struct
        {
            /**
             * @brief   Signals, if the broadcast is a static broadcast.
             * 
             * This is the case for instructions with inbuild broadcast functionality, that is
             * always active and not be controlled by a flag in the XOP/VEX/EVEX/MVEX-prefix.
             */
            ZydisBool isStatic;
            /**
             * @brief   The AVX broadcast-mode.
             */
            ZydisBroadcastMode mode;
        } broadcast;
        /**
         * @brief   The AVX rounding-mode.
         */
        ZydisRoundingMode roundingMode;
        /**
         * @brief   The AVX register-swizzle mode (MVEX only).
         */
        ZydisSwizzleMode swizzleMode;
        /**
         * @brief   The AVX data-conversion mode (MVEX only).
         */
        ZydisConversionMode conversionMode;
        /**
         * @brief   Signals, if the sae functionality is enabled for the instruction.
         */
        ZydisBool hasSAE;
        /**
         * @brief   Signals, if the instruction has a memory eviction-hint (MVEX only).
         */
        ZydisBool hasEvictionHint;
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
            int64_t value;
            /**
             * @brief   The physical displacement size, in bits.
             */
            uint8_t size;
            /**
             * @brief   The offset of the displacement data, relative to the beginning of the
             *          instruction, in bytes.
             */
            uint8_t offset;
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
                uint64_t u;
                int64_t s;
            } value;
            /**
             * @brief   The physical immediate size, in bits.
             */
            uint8_t size;
            /**
             * @brief   The offset of the immediate data, relative to the beginning of the
             *          instruction, in bytes.
             */
            uint8_t offset;
        } imm[2];
    } raw;
    /**
     * @brief   This field is intended for custom data and may be freely set by the user.
     */
    void* userData;
} ZydisDecodedInstruction;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INSTRUCTIONINFO_H */
