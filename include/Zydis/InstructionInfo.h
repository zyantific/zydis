/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

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
 * @brief TODO
 */

#ifndef ZYDIS_INSTRUCTIONINFO_H
#define ZYDIS_INSTRUCTIONINFO_H

#include <stdint.h>
#include <stdbool.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/Register.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Disassembler mode                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis disassembler-mode datatype.
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
/* Instruction flags                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionFlags datatype.
 */
typedef uint32_t ZydisInstructionFlags;

/**
 * @brief   The instruction has the modrm byte.
 */
#define ZYDIS_INSTRFLAG_HAS_MODRM               0x00000001
/**
 * @brief   The instruction has the sib byte.
 */
#define ZYDIS_INSTRFLAG_HAS_SIB                 0x00000002
/**
 * @brief   The instruction has one or more operands with position-relative offsets.
 */
#define ZYDIS_INSTRFLAG_IS_RELATIVE             0x00000004
/**
 * @brief   The instruction is privileged and may only be executed in kernel-mode (ring0).
 */
#define ZYDIS_INSTRFLAG_IS_PRIVILEGED           0x00000008
/**
 * @brief   An error occured while decoding the current instruction. 
 */
#define ZYDIS_INSTRFLAG_ERROR_MASK              0x7F000000
/**
 * @brief   The instruction is undefined.  
 */
#define ZYDIS_INSTRFLAG_ERROR_UNDEFINED         0x01000000
/**
 * @brief   The instruction length has exceeded the maximum of 15 bytes.  
 */
#define ZYDIS_INSTRFLAG_ERROR_MAXLENGTH         0x02000000
/**
 * @brief   An error occured while decoding the vex-prefix.  
 */
#define ZYDIS_INSTRFLAG_ERROR_MALFORMED_VEX     0x04000000
/**
 * @brief   An error occured while decoding the evex-prefix.  
 */
#define ZYDIS_INSTRFLAG_ERROR_MALFORMED_EVEX    0x08000000
/**
 * @brief   An error occured while decoding the xop-prefix.  
 */
#define ZYDIS_INSTRFLAG_ERROR_MALFORMED_XOP     0x10000000
/**
 * @brief   A rex-prefix was found while decoding a vex/evex/xop instruction. 
 */
#define ZYDIS_INSTRFLAG_ERROR_ILLEGAL_REX       0x20000000
/**
 * @brief   An invalid constellation was found while decoding an instruction that uses the VSIB
 *          addressing mode.
 */
#define ZYDIS_INSTRFLAG_ERROR_INVALID_VSIB      0x40000000
/**
 * @brief   An error occured while decoding the instruction-operands.  
 */
#define ZYDIS_INSTRFLAG_ERROR_OPERANDS          0x40000000

/* ---------------------------------------------------------------------------------------------- */
/* Prefix flags                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisPrefixFlags datatype.
 */
typedef uint32_t ZydisPrefixFlags;

/**
 * @brief   The instruction has the rex-prefix (0x40 - 0x4F).
 */
#define ZYDIS_PREFIXFLAG_HAS_REX                0x00000001
/**
 * @brief   The instruction has the xop-prefix (0x8F).  
 */
#define ZYDIS_PREFIXFLAG_HAS_XOP                0x00000002
/**
 * @brief   The instruction has the vex-prefix (0xC4 or 0xC5).  
 */
#define ZYDIS_PREFIXFLAG_HAS_VEX                0x00000004
/**
 * @brief   The instruction has the evex-prefix (0x62).  
 */
#define ZYDIS_PREFIXFLAG_HAS_EVEX               0x00000008
/**
 * @brief   The instruction has the lock-prefix (0x0F)
 */
#define ZYDIS_PREFIXFLAG_HAS_LOCK               0x00000010
/**
 * @brief   The instruction has the rep/repe/repz-prefix (0xF3)
 */
#define ZYDIS_PREFIXFLAG_HAS_REP                0x00000020
/**
 * @brief   The instruction has the rep/repe/repz-prefix (0xF3)
 */
#define ZYDIS_PREFIXFLAG_HAS_REPE               0x00000020
/**
 * @brief   The instruction has the rep/repe/repz-prefix (0xF3)
 */
#define ZYDIS_PREFIXFLAGG_HAS_REPZ              0x00000020
/**
 * @brief   The instruction has the repne/repnz-prefix (0xF2)
 */
#define ZYDIS_PREFIXFLAG_HAS_REPNE              0x00000040
/**
 * @brief   The instruction has the repne/repnz-prefix (0xF2)
 */
#define ZYDIS_PREFIXFLAG_HAS_REPNZ              0x00000040
/**
 * @brief   The instruction has a segment-override prefix.
 */
#define ZYDIS_PREFIXFLAG_SEGMENT_MASK           0x00001F80
/**
 * @brief   The instruction has the cs segment-override prefix (0x2E).
 */
#define ZYDIS_PREFIXFLAG_HAS_SEGMENT_CS         0x00000080
/**
 * @brief   The instruction has the ss segment-override prefix (0x36).
 */
#define ZYDIS_PREFIXFLAG_HAS_SEGMENT_SS         0x00000100
/**
 * @brief   The instruction has the ds segment-override prefix (0x3E).
 */
#define ZYDIS_PREFIXFLAG_HAS_SEGMENT_DS         0x00000200
/**
 * @brief   The instruction has the es segment-override prefix (0x26).
 */
#define ZYDIS_PREFIXFLAG_HAS_SEGMENT_ES         0x00000400
/**
 * @brief   The instruction has the fs segment-override prefix (0x64).
 */
#define ZYDIS_PREFIXFLAG_HAS_SEGMENT_FS         0x00000800
/**
 * @brief   The instruction has the gs segment-override prefix (0x65).
 */
#define ZYDIS_PREFIXFLAG_HAS_SEGMENT_GS         0x00001000
/**
 * @brief   The instruction has the operand-size-override prefix (0x66).
 */
#define ZYDIS_PREFIXFLAG_HAS_OPERANDSIZE        0x00002000
/**
 * @brief   The instruction has the address-size-override prefix (0x67).
 */
#define ZYDIS_PREFIXFLAG_HAS_ADDRESSSIZE        0x00004000
/**
 * @brief   The instruction has the xacquire prefix (0xF2).
 */
#define ZYDIS_PREFIXFLAG_HAS_XACQUIRE           0x00008000
/**
 * @brief   The instruction has the xrelease prefix (0xF3).
 */
#define ZYDIS_PREFIXFLAG_HAS_XRELEASE           0x00010000
/**
 * @brief   The instruction has the branch-not-taken hint (0x2E).
 */
#define ZYDIS_PREFIXFLAG_HAS_BRANCH_NOT_TAKEN   0x00020000
/**
 * @brief   The instruction has the branch-taken hint (0x3E).
 */
#define ZYDIS_PREFIXFLAG_HAS_BRANCH_TAKEN       0x00040000
/**
 * @brief   The instruction accepts the operand-size override prefix (0x66)
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_OPERANDSIZE    0x00080000
/**
 * @brief   The instruction accepts the adress-size override prefix (0x67)
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_ADDRESSSIZE    0x00100000
/**
 * @brief   The instruction accepts the lock-prefix.
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_LOCK           0x00200000
/**
 * @brief   The instruction accepts the string prefixes (rep/repe/repz/repne/repnz).
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_REP            0x00400000
/**
 * @brief   The instruction accepts the string prefixes (rep/repe/repz/repne/repnz).
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_REPE           0x00400000
/**
 * @brief   The instruction accepts the string prefixes (rep/repe/repz/repne/repnz).
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_REPZ           0x00400000
/**
 * @brief   The instruction accepts the string prefixes (rep/repe/repz/repne/repnz).
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_REPNE          0x00400000
/**
 * @brief   The instruction accepts the string prefixes (rep/repe/repz/repne/repnz).
 */
#define ZYDIS_PREFIXFLAG_ACCEPTS_REPNZ          0x00400000
/**
 * @brief   The instruction has multiple prefixes of the first prefix-group (0x0F, 0xF3, 0xF2).
 */
#define ZYDIS_PREFIXFLAG_MULTIPLE_GRP1          0x00800000
/**
 * @brief   The instruction has multiple prefixes of the second prefix-group (0x2E, 0x36, 
 *          0x3E, 0x26, 0x64, 0x65).
 */
#define ZYDIS_PREFIXFLAG_MULTIPLE_GRP2          0x01000000
/**
 * @brief   The instruction has multiple prefixes of the third prefix-group (0x66).
 */
#define ZYDIS_PREFIXFLAG_MULTIPLE_GRP3          0x02000000
/**
 * @brief   The instruction has multiple prefixes of the fourth prefix-group (0x67).
 */
#define ZYDIS_PREFIXFLAG_MULTIPLE_GRP4          0x04000000

/* ---------------------------------------------------------------------------------------------- */
/* Instruction encoding                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionEncoding datatype.
 */
typedef uint8_t ZydisInstructionEncoding;

/**
 * @brief   Values that represent instruction encodings.
 */
enum ZydisInstructionEncodings
{
    ZYDIS_INSTRUCTION_ENCODING_DEFAULT  = 0x00,
    ZYDIS_INSTRUCTION_ENCODING_3DNOW    = 0x01,
    ZYDIS_INSTRUCTION_ENCODING_XOP      = 0x02,
    ZYDIS_INSTRUCTION_ENCODING_VEX      = 0x03,
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
     * @brief   The operand is a mem operand.
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
    ZYDIS_OPERAND_ENCODING_REG,
    ZYDIS_OPERAND_ENCODING_RM,
    ZYDIS_OPERAND_ENCODING_RM_CD2,
    ZYDIS_OPERAND_ENCODING_RM_CD4,
    ZYDIS_OPERAND_ENCODING_RM_CD8,
    ZYDIS_OPERAND_ENCODING_RM_CD16,
    ZYDIS_OPERAND_ENCODING_RM_CD32,
    ZYDIS_OPERAND_ENCODING_RM_CD64,
    ZYDIS_OPERAND_ENCODING_OPCODE,
    ZYDIS_OPERAND_ENCODING_VVVV,
    ZYDIS_OPERAND_ENCODING_AAA,
    ZYDIS_OPERAND_ENCODING_IMM8_LO,
    ZYDIS_OPERAND_ENCODING_IMM8_HI,
    ZYDIS_OPERAND_ENCODING_IMM8,
    ZYDIS_OPERAND_ENCODING_IMM16,
    ZYDIS_OPERAND_ENCODING_IMM32,
    ZYDIS_OPERAND_ENCODING_IMM64
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand access mode                                                                            */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandAccess datatype.
 */
typedef uint8_t ZydisOperandAccess;

/**
 * @brief   Values that represent operand-access-modes.
 */
enum ZydisOperandAccessModes
{
    /**
     * @brief   The operand gets read by the instruction.
     */
    ZYDIS_OPERAND_ACCESS_READ,
    /**
     * @brief   The operand gets written by the instruction.
     */
    ZYDIS_OPERAND_ACCESS_WRITE,
    /**
     * @brief   The operand gets read and written by the instruction.
     */
    ZYDIS_OPERAND_ACCESS_READWRITE
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX mask mode                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVXMaskMode datatype.
 */
typedef uint8_t ZydisAVXMaskMode;

/**
 * @brief   Values that represent zydis avx mask-modes.
 */
enum ZydisAVXMaskModes
{
    ZYDIS_AVX_MASKMODE_INVALID,
    /**
     * @brief   Merge mode. This is the default mode for all evex-instructions.
     */
    ZYDIS_AVX_MASKMODE_MERGE,
    /**
     * @brief   The zeroing mode is enabled for this instruction.
     */
    ZYDIS_AVX_MASKMODE_ZERO
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX broadcast type                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVXBroadcastType datatype.
 */
typedef uint8_t ZydisAVXBroadcastType;

/**
 * @brief   Values that represent zydis avx broadcast-types.
 */
enum ZydisAVXBroadcastTypes
{
    ZYDIS_AVX_BCSTMODE_INVALID,
    /**
     * @brief   1to2 broadcast.
     */
    ZYDIS_AVX_BCSTMODE_2,
    /**
     * @brief   1to4 broadcast.
     */
    ZYDIS_AVX_BCSTMODE_4,
    /**
     * @brief   1to8 broadcast.
     */
    ZYDIS_AVX_BCSTMODE_8,
    /**
     * @brief   1to16 broadcast.
     */
    ZYDIS_AVX_BCSTMODE_16
};

/* ---------------------------------------------------------------------------------------------- */
/* AVX rounding mode                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAVXRoundingMode datatype.
 */
typedef uint8_t ZydisAVXRoundingMode;

/**
 * @brief   Values that represent zydis avx rounding-mode.
 */
enum ZydisAVXRoundingModes                // TODO: Mirror "real" values from documentation
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
/* Operand info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis operand info struct.
 */
typedef struct ZydisOperandInfo_
{
    /**
     * @brief   The type of the operand.
     */
    ZydisOperandType type;
    /**
     * @brief   The logical size of the operand.
     */
    uint16_t size;
    /**
     * @brief   The operand encoding.
     */
    ZydisOperandEncoding encoding;
    /**
     * @brief   The operand access mode.
     */
    ZydisOperandAccess access;
    /**
     * @brief   Specifies the register for register-operands.
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
         * @brief   Extended info for memory-operand with displacement.
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
             * @brief   The physical displacement size.
             */
            uint8_t dataSize;
            /**
             * @brief   The offset of the displacement data, relative to the beginning of the 
             *          instruction.
             */
            uint8_t dataOffset;
        } disp;
    } mem;
    /**
     * @brief   Extended info for pointer operands.
     */
    struct 
    {
        uint16_t segment;
        uint32_t offset;
    } ptr;
    /**
     * @brief   Extended info for immediate operands.
     */
    struct
    {
        /**
         * @brief   Signals, if the immediate value is signed.
         */
        bool isSigned;
        /**
         * @brief   Signals, if the immediate value contains a relative offset.
         */
        bool isRelative;
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
         * @brief   The physical immediate size.
         */
        uint8_t dataSize;
        /**
         * @brief   The offset of the immediate data, relative to the beginning of the instruction.
         */
        uint8_t dataOffset;
    } imm;
    /**
     * @brief   This field is intended for custom data and may be freely set by the user.
     */
    void* userData;
} ZydisOperandInfo;

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
     * @brief   Instruction specific info- and error-flags.
     */
    ZydisInstructionFlags instrFlags;
    /**
     * @brief   Prefix flags.
     */
    ZydisPrefixFlags prefixFlags;
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
     * @brief   The instruction-encoding (default, 3dnow, vex, evex, xop).
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
    ZydisOperandInfo operand[5];
    /**
     * @brief   Extended info for avx-related instructions.
     */
    struct
    {
        /**
         * @brief   The AVX mask-register.
         */
        ZydisRegister maskRegister;
        /**
         * @brief   The AVX mask-mode.
         */
        ZydisAVXMaskMode maskMode;    
        /**
         * @brief   The AVX broadcast-type.
         */
        ZydisAVXBroadcastType broadcast;
        /**
         * @brief   The AVX rounding-mode.
         */
        ZydisAVXRoundingMode roundingMode;
        /**
         * @brief   @c TRUE, if the AVX suppress-all-exceptions flag is set.
         */
        bool sae;
    } avx;
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
     * @brief   Extended info about different instruction-parts like modrm, sib or 
     *          encoding-prefixes.
     */
    struct
    {
        // TODO: uint8_t map[15];
        /**
         * @brief   Detailed info about the rex-prefix.
         */
        struct
        {
            /**
             * @brief   True if the prefix got already decoded.
             */
            bool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[1];
            /**
             * @brief   64 bit operand-size override.
             */
            uint8_t w;
            /**
             * @brief   Extension of the modrm.reg field.
             */
            uint8_t r;
            /**
             * @brief   Extension of the sib.index field.
             */
            uint8_t x;
            /**
             * @brief   Extension of the modrm.rm field, sib.base field, or opcode.reg field.
             */
            uint8_t b;
        } rex; 
        /**
         * @brief   Detailed info about the vex-prefix.
         */
        struct
        {
            /**
             * @brief   True if the prefix got already decoded.
             */
            bool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[3];
            uint8_t r;
            uint8_t x;
            uint8_t b;
            uint8_t m_mmmm;
            uint8_t w;
            uint8_t vvvv;
            uint8_t l;
            uint8_t pp;
        } vex;
        /**
         * @brief   Detailed info about the evex-prefix.
         */
        struct
        {
            /**
             * @brief   True if the prefix got already decoded.
             */
            bool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[4];
            /**
             * @brief   TODO:
             */
            uint8_t r;
            /**
             * @brief   TODO:
             */
            uint8_t x;
            /**
             * @brief   TODO:
             */
            uint8_t b;
            /**
             * @brief   High-16 register specifier modifier.
             */
            uint8_t r2;
            /**
             * @brief   Compressed legacy escape.
             */
            uint8_t mm;
            /**
             * @brief   Osize promotion/Opcode extension.
             */
            uint8_t w;
            /**
             * @brief   NDS register specifier.
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
             * @brief   Vector length/RC (most significant bit).
             */
            uint8_t l2;
            /**
             * @brief   Vector length/RC (least significant bit).
             */
            uint8_t l;
            /**
             * @brief   Broadcast/RC/SAE Context.
             */
            uint8_t b0;
            /**
             * @brief   High-16 NDS/VIDX register specifier.
             */
            uint8_t v2;
            /**
             * @brief   Embedded opmask register specifier.
             */
            uint8_t aaa;
        } evex;
        /**
         * @brief   Detailed info about the xop-prefix.
         */
        struct
        {
            /**
             * @brief   True if the prefix got already decoded.
             */
            bool isDecoded;
            /**
             * @brief   The raw bytes of the prefix.
             */
            uint8_t data[3];
            uint8_t r;
            uint8_t x;
            uint8_t b;
            uint8_t m_mmmm;
            uint8_t w;
            uint8_t vvvv;
            uint8_t l;
            uint8_t pp;
        } xop;
        /**
         * @brief   Detailed info about the modrm-byte.
         */
        struct
        {
            bool isDecoded;
            uint8_t data[1];
            uint8_t mod;
            uint8_t reg;
            uint8_t rm;
        } modrm;
        /**
         * @brief   Detailed info about the sib-byte.
         */
        struct
        {
            bool isDecoded;
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
            uint8_t w;
            uint8_t r;
            uint8_t x;
            uint8_t b;
            uint8_t l;
        } internal;
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
