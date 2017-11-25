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
 * @brief   Defines decoder/encoder-shared macros and types.
 */

#ifndef ZYDIS_SHAREDTYPES_H
#define ZYDIS_SHAREDTYPES_H

#include <Zydis/CommonTypes.h>

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
#define ZYDIS_MAX_OPERAND_COUNT      10

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Machine mode                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisMachineMode datatype.
 */
typedef ZydisU8 ZydisMachineMode;

/**
 * @brief   Values that represent machine modes.
 */
enum ZydisMachineModes
{
    ZYDIS_MACHINE_MODE_INVALID,
    /**
     * @brief 64 bit mode.
     */
    ZYDIS_MACHINE_MODE_LONG_64,
    /**
     * @brief 32 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LONG_COMPAT_32,
    /**
     * @brief 16 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LONG_COMPAT_16,
    /**
     * @brief 32 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LEGACY_32,
    /**
     * @brief 16 bit protected mode.
     */
    ZYDIS_MACHINE_MODE_LEGACY_16,
    /**
     * @brief 16 bit real mode.
     */
    ZYDIS_MACHINE_MODE_REAL_16,
     /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_MACHINE_MODE_MAX_VALUE = ZYDIS_MACHINE_MODE_REAL_16
};

/* ---------------------------------------------------------------------------------------------- */
/* Address width                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisAddressWidth datatype.
 */
typedef ZydisU8 ZydisAddressWidth;

/**
 * @brief   Values that represent address widths.
 */
enum ZydisAddressWidths
{
    ZYDIS_ADDRESS_WIDTH_INVALID         =  0,
    ZYDIS_ADDRESS_WIDTH_16              = 16,
    ZYDIS_ADDRESS_WIDTH_32              = 32,
    ZYDIS_ADDRESS_WIDTH_64              = 64,
    ZYDIS_ADDRESS_WIDTH_MAX_VALUE       = ZYDIS_ADDRESS_WIDTH_64
};

/* ---------------------------------------------------------------------------------------------- */
/* Element types                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisElementType datatype.
 */
typedef ZydisU8 ZydisElementType;

/**
 * @brief   Values that represent element-types.
 */
enum ZydisElementTypes
{
    ZYDIS_ELEMENT_TYPE_INVALID,
    ZYDIS_ELEMENT_TYPE_STRUCT,
    ZYDIS_ELEMENT_TYPE_UINT,
    ZYDIS_ELEMENT_TYPE_INT,
    ZYDIS_ELEMENT_TYPE_FLOAT16,
    ZYDIS_ELEMENT_TYPE_FLOAT32,
    ZYDIS_ELEMENT_TYPE_FLOAT64,
    ZYDIS_ELEMENT_TYPE_FLOAT80,
    ZYDIS_ELEMENT_TYPE_LONGBCD,
    ZYDIS_ELEMENT_TYPE_MAX_VALUE = ZYDIS_ELEMENT_TYPE_LONGBCD
};

/**
 * @brief   Defines the @c ZydisElementSize datatype.
 */
typedef ZydisU16 ZydisElementSize;

/* ---------------------------------------------------------------------------------------------- */
/* Operand type                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandType datatype.
 */
typedef ZydisU8 ZydisOperandType;

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
    ZYDIS_OPERAND_TYPE_IMMEDIATE,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_OPERAND_TYPE_MAX_VALUE = ZYDIS_OPERAND_TYPE_IMMEDIATE
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand encoding                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandEncoding datatype.
 */
typedef ZydisU8 ZydisOperandEncoding;

/**
 * @brief   Values that represent operand-encodings.
 */
enum ZydisOperandEncodings
{
    ZYDIS_OPERAND_ENCODING_NONE,
    ZYDIS_OPERAND_ENCODING_MODRM_REG,
    ZYDIS_OPERAND_ENCODING_MODRM_RM,
    ZYDIS_OPERAND_ENCODING_OPCODE,
    ZYDIS_OPERAND_ENCODING_NDSNDD,
    ZYDIS_OPERAND_ENCODING_IS4,
    ZYDIS_OPERAND_ENCODING_MASK,
    ZYDIS_OPERAND_ENCODING_DISP8,
    ZYDIS_OPERAND_ENCODING_DISP16,
    ZYDIS_OPERAND_ENCODING_DISP32,
    ZYDIS_OPERAND_ENCODING_DISP64,
    ZYDIS_OPERAND_ENCODING_DISP16_32_64,
    ZYDIS_OPERAND_ENCODING_DISP32_32_64,
    ZYDIS_OPERAND_ENCODING_DISP16_32_32,
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
    ZYDIS_OPERAND_ENCODING_JIMM16_32_32,
    ZYDIS_OPERAND_ENCODING_MAX_VALUE = ZYDIS_OPERAND_ENCODING_JIMM16_32_32
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand visibility                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandVisibility datatype.
 */
typedef ZydisU8 ZydisOperandVisibility;

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
    ZYDIS_OPERAND_VISIBILITY_HIDDEN,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_OPERAND_VISIBILITY_MAX_VALUE = ZYDIS_OPERAND_VISIBILITY_HIDDEN
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand action                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOperandAction datatype.
 */
typedef ZydisU8 ZydisOperandAction;

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

    /**
     * @brief   Mask combining all writing access flags.
     */
    ZYDIS_OPERAND_ACTION_MASK_WRITE = ZYDIS_OPERAND_ACTION_WRITE |
        ZYDIS_OPERAND_ACTION_READWRITE | ZYDIS_OPERAND_ACTION_CONDWRITE | 
        ZYDIS_OPERAND_ACTION_READ_CONDWRITE | ZYDIS_OPERAND_ACTION_CONDREAD_WRITE,
    /**
     * @brief   Mask combining all reading access flags.
     */
    ZYDIS_OPERAND_ACTION_MASK_READ = ZYDIS_OPERAND_ACTION_READ | ZYDIS_OPERAND_ACTION_READWRITE | 
        ZYDIS_OPERAND_ACTION_CONDREAD | ZYDIS_OPERAND_ACTION_READ_CONDWRITE | 
        ZYDIS_OPERAND_ACTION_CONDREAD_WRITE,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_OPERAND_ACTION_MAX_VALUE = ZYDIS_OPERAND_ACTION_CONDREAD_WRITE
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction encoding                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionEncoding datatype.
 */
typedef ZydisU8 ZydisInstructionEncoding;

/**
 * @brief   Values that represent instruction-encodings.
 */
enum ZydisInstructionEncodings
{
    ZYDIS_INSTRUCTION_ENCODING_INVALID,
    /**
     * @brief   The instruction uses the default encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_DEFAULT,
    /**
     * @brief   The instruction uses the AMD 3DNow-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_3DNOW,
    /**
     * @brief   The instruction uses the AMD XOP-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_XOP,
    /**
     * @brief   The instruction uses the VEX-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_VEX,
    /**
     * @brief   The instruction uses the EVEX-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_EVEX,
    /**
     * @brief   The instruction uses the MVEX-encoding.
     */
    ZYDIS_INSTRUCTION_ENCODING_MVEX,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_INSTRUCTION_ENCODING_MAX_VALUE = ZYDIS_INSTRUCTION_ENCODING_MVEX
};

/* ---------------------------------------------------------------------------------------------- */
/* Opcode map                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisOpcodeMap map.
 */
typedef ZydisU8 ZydisOpcodeMap;

/**
 * @brief   Values that represent opcode-maps.
 */
enum ZydisOpcodeMaps
{
    ZYDIS_OPCODE_MAP_DEFAULT,
    ZYDIS_OPCODE_MAP_0F,
    ZYDIS_OPCODE_MAP_0F38,
    ZYDIS_OPCODE_MAP_0F3A,
    ZYDIS_OPCODE_MAP_0F0F,
    ZYDIS_OPCODE_MAP_XOP8,
    ZYDIS_OPCODE_MAP_XOP9,
    ZYDIS_OPCODE_MAP_XOPA,
    ZYDIS_OPCODE_MAP_MAX_VALUE = ZYDIS_OPCODE_MAP_XOP9
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_SHAREDTYPES_H */
