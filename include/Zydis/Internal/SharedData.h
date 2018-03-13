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

#ifndef ZYDIS_INTERNAL_SHAREDDATA_H
#define ZYDIS_INTERNAL_SHAREDDATA_H

#include <Zydis/Defines.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/Register.h>
#include <Zydis/SharedTypes.h>
#include "Zydis/DecoderTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

// MSVC does not like types other than (un-)signed int for bitfields
#ifdef ZYDIS_MSVC
#   pragma warning(push)
#   pragma warning(disable:4214)
#endif

#pragma pack(push, 1)

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisSemanticOperandType` enum.
 */
typedef enum ZydisSemanticOperandType_
{
    ZYDIS_SEMANTIC_OPTYPE_UNUSED,
    ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG,
    ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_MEM,
    ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_IMM1,
    ZYDIS_SEMANTIC_OPTYPE_GPR8,
    ZYDIS_SEMANTIC_OPTYPE_GPR16,
    ZYDIS_SEMANTIC_OPTYPE_GPR32,
    ZYDIS_SEMANTIC_OPTYPE_GPR64,
    ZYDIS_SEMANTIC_OPTYPE_GPR16_32_64,
    ZYDIS_SEMANTIC_OPTYPE_GPR32_32_64,
    ZYDIS_SEMANTIC_OPTYPE_GPR16_32_32,
    ZYDIS_SEMANTIC_OPTYPE_FPR,
    ZYDIS_SEMANTIC_OPTYPE_MMX,
    ZYDIS_SEMANTIC_OPTYPE_XMM,
    ZYDIS_SEMANTIC_OPTYPE_YMM,
    ZYDIS_SEMANTIC_OPTYPE_ZMM,
    ZYDIS_SEMANTIC_OPTYPE_BND,
    ZYDIS_SEMANTIC_OPTYPE_SREG,
    ZYDIS_SEMANTIC_OPTYPE_CR,
    ZYDIS_SEMANTIC_OPTYPE_DR,
    ZYDIS_SEMANTIC_OPTYPE_MASK,
    ZYDIS_SEMANTIC_OPTYPE_MEM,
    ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBX,
    ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBY,
    ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBZ,
    ZYDIS_SEMANTIC_OPTYPE_IMM,
    ZYDIS_SEMANTIC_OPTYPE_REL,
    ZYDIS_SEMANTIC_OPTYPE_PTR,
    ZYDIS_SEMANTIC_OPTYPE_AGEN,
    ZYDIS_SEMANTIC_OPTYPE_MOFFS,
    ZYDIS_SEMANTIC_OPTYPE_MIB,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_SEMANTIC_OPTYPE_MAX_VALUE = ZYDIS_SEMANTIC_OPTYPE_MIB,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_SEMANTIC_OPTYPE_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_SEMANTIC_OPTYPE_MAX_VALUE)
} ZydisSemanticOperandType;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisInternalElementType` enum.
 */
typedef enum ZydisInternalElementType_
{
    ZYDIS_IELEMENT_TYPE_INVALID,
    ZYDIS_IELEMENT_TYPE_VARIABLE,
    ZYDIS_IELEMENT_TYPE_STRUCT,
    ZYDIS_IELEMENT_TYPE_INT,
    ZYDIS_IELEMENT_TYPE_UINT,
    ZYDIS_IELEMENT_TYPE_INT1,
    ZYDIS_IELEMENT_TYPE_INT8,
    ZYDIS_IELEMENT_TYPE_INT16,
    ZYDIS_IELEMENT_TYPE_INT32,
    ZYDIS_IELEMENT_TYPE_INT64,
    ZYDIS_IELEMENT_TYPE_UINT8,
    ZYDIS_IELEMENT_TYPE_UINT16,
    ZYDIS_IELEMENT_TYPE_UINT32,
    ZYDIS_IELEMENT_TYPE_UINT64,
    ZYDIS_IELEMENT_TYPE_UINT128,
    ZYDIS_IELEMENT_TYPE_UINT256,
    ZYDIS_IELEMENT_TYPE_FLOAT16,
    ZYDIS_IELEMENT_TYPE_FLOAT32,
    ZYDIS_IELEMENT_TYPE_FLOAT64,
    ZYDIS_IELEMENT_TYPE_FLOAT80,
    ZYDIS_IELEMENT_TYPE_BCD80,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_IELEMENT_TYPE_MAX_VALUE = ZYDIS_IELEMENT_TYPE_BCD80,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_IELEMENT_TYPE_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_IELEMENT_TYPE_MAX_VALUE)
} ZydisInternalElementType;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisImplicitRegisterType` enum.
 */
typedef enum ZydisImplicitRegisterType_
{
    ZYDIS_IMPLREG_TYPE_STATIC,
    ZYDIS_IMPLREG_TYPE_GPR_OSZ,
    ZYDIS_IMPLREG_TYPE_GPR_ASZ,
    ZYDIS_IMPLREG_TYPE_GPR_SSZ,
    ZYDIS_IMPLREG_TYPE_IP_ASZ,
    ZYDIS_IMPLREG_TYPE_IP_SSZ,
    ZYDIS_IMPLREG_TYPE_FLAGS_SSZ,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_IMPLREG_TYPE_MAX_VALUE = ZYDIS_IMPLREG_TYPE_FLAGS_SSZ,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_IMPLREG_TYPE_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_IMPLREG_TYPE_MAX_VALUE)
} ZydisImplicitRegisterType;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisImplicitMemBase` enum.
 */
typedef enum ZydisImplicitMemBase_
{
    ZYDIS_IMPLMEM_BASE_ABX,
    ZYDIS_IMPLMEM_BASE_ASP,
    ZYDIS_IMPLMEM_BASE_ABP,
    ZYDIS_IMPLMEM_BASE_ASI,
    ZYDIS_IMPLMEM_BASE_ADI,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_IMPLMEM_BASE_MAX_VALUE = ZYDIS_IMPLMEM_BASE_ADI,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_IMPLMEM_BASE_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_IMPLMEM_BASE_MAX_VALUE)
} ZydisImplicitMemBase;

/* ---------------------------------------------------------------------------------------------- */

// MSVC does not correctly execute the `pragma pack(1)` compiler-directive, if we use the correct
// enum types
ZYDIS_STATIC_ASSERT(ZYDIS_SEMANTIC_OPTYPE_REQUIRED_BITS     <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_OPERAND_VISIBILITY_REQUIRED_BITS  <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_OPERAND_ACTION_REQUIRED_BITS      <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_IELEMENT_TYPE_REQUIRED_BITS       <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_OPERAND_ENCODING_REQUIRED_BITS    <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_IMPLREG_TYPE_REQUIRED_BITS        <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_REGISTER_REQUIRED_BITS            <= 16);
ZYDIS_STATIC_ASSERT(ZYDIS_IMPLMEM_BASE_REQUIRED_BITS        <=  8);

/**
 * @brief   Defines the `ZydisOperandDefinition` struct.
 */
typedef struct ZydisOperandDefinition_
{
    ZydisU8 type                            ZYDIS_BITFIELD(ZYDIS_SEMANTIC_OPTYPE_REQUIRED_BITS);
    ZydisU8 visibility                      ZYDIS_BITFIELD(ZYDIS_OPERAND_VISIBILITY_REQUIRED_BITS);
    ZydisU8 action                          ZYDIS_BITFIELD(ZYDIS_OPERAND_ACTION_REQUIRED_BITS);
    ZydisU16 size[3];
    ZydisU8 elementType                     ZYDIS_BITFIELD(ZYDIS_IELEMENT_TYPE_REQUIRED_BITS);
    union
    {
        ZydisU8 encoding                    ZYDIS_BITFIELD(ZYDIS_OPERAND_ENCODING_REQUIRED_BITS);
        struct
        {
            ZydisU8 type                    ZYDIS_BITFIELD(ZYDIS_IMPLREG_TYPE_REQUIRED_BITS);
            union
            {
                ZydisU16 reg                ZYDIS_BITFIELD(ZYDIS_REGISTER_REQUIRED_BITS);
                ZydisU8 id                  ZYDIS_BITFIELD(6);
            } reg;
        } reg;
        struct
        {
            ZydisU8 seg                     ZYDIS_BITFIELD(3);
            ZydisU8 base                    ZYDIS_BITFIELD(ZYDIS_IMPLMEM_BASE_REQUIRED_BITS);
        } mem;
    } op;
} ZydisOperandDefinition;

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisRegisterConstraint` enum.
 */
typedef enum ZydisRegisterConstraint_
{
    ZYDIS_REG_CONSTRAINTS_UNUSED,
    ZYDIS_REG_CONSTRAINTS_NONE,
    ZYDIS_REG_CONSTRAINTS_GPR,
    ZYDIS_REG_CONSTRAINTS_SR_DEST,
    ZYDIS_REG_CONSTRAINTS_SR,
    ZYDIS_REG_CONSTRAINTS_CR,
    ZYDIS_REG_CONSTRAINTS_DR,
    ZYDIS_REG_CONSTRAINTS_MASK,
    ZYDIS_REG_CONSTRAINTS_BND,
    ZYDIS_REG_CONSTRAINTS_VSIB,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_REG_CONSTRAINTS_MAX_VALUE = ZYDIS_REG_CONSTRAINTS_VSIB,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_REG_CONSTRAINTS_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_REG_CONSTRAINTS_MAX_VALUE)
} ZydisRegisterConstraint;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisInternalVectorLength` enum.
 */
typedef enum ZydisInternalVectorLength_
{
    ZYDIS_IVECTOR_LENGTH_DEFAULT,
    ZYDIS_IVECTOR_LENGTH_FIXED_128,
    ZYDIS_IVECTOR_LENGTH_FIXED_256,
    ZYDIS_IVECTOR_LENGTH_FIXED_512,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_IVECTOR_LENGTH_MAX_VALUE = ZYDIS_IVECTOR_LENGTH_FIXED_512,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_IVECTOR_LENGTH_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_IVECTOR_LENGTH_MAX_VALUE)
} ZydisInternalVectorLength;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisInternalElementSize` enum.
 */
typedef enum ZydisInternalElementSize_
{
    ZYDIS_IELEMENT_SIZE_INVALID,
    ZYDIS_IELEMENT_SIZE_8,
    ZYDIS_IELEMENT_SIZE_16,
    ZYDIS_IELEMENT_SIZE_32,
    ZYDIS_IELEMENT_SIZE_64,
    ZYDIS_IELEMENT_SIZE_128,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_IELEMENT_SIZE_MAX_VALUE = ZYDIS_IELEMENT_SIZE_128,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_IELEMENT_SIZE_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_IELEMENT_SIZE_MAX_VALUE)
} ZydisInternalElementSize;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisEVEXFunctionality` enum.
 */
typedef enum ZydisEVEXFunctionality_
{
    ZYDIS_EVEX_FUNC_INVALID,
    /**
     * @brief   @c EVEX.b enables broadcast functionality.
     */
    ZYDIS_EVEX_FUNC_BC,
    /**
     * @brief   @c EVEX.b enables embedded-rounding functionality.
     */
    ZYDIS_EVEX_FUNC_RC,
    /**
     * @brief   @c EVEX.b enables sae functionality.
     */
    ZYDIS_EVEX_FUNC_SAE,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_EVEX_FUNC_MAX_VALUE = ZYDIS_EVEX_FUNC_SAE,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_EVEX_FUNC_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_EVEX_FUNC_MAX_VALUE)
} ZydisEVEXFunctionality;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisEVEXTupleType` enum.
 */
typedef enum ZydisEVEXTupleType_
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
    ZYDIS_TUPLETYPE_DUP,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_TUPLETYPE_MAX_VALUE = ZYDIS_TUPLETYPE_DUP,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_TUPLETYPE_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_TUPLETYPE_MAX_VALUE)
} ZydisEVEXTupleType;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisMVEXFunctionality` enum.
 */
typedef enum ZydisMVEXFunctionality_
{
    /**
     * @brief   @c The MVEX.SSS value is ignored.
     */
    ZYDIS_MVEX_FUNC_IGNORED,
    /**
     * @brief   @c MVEX.SSS must be 000b.
     */
    ZYDIS_MVEX_FUNC_INVALID,
    /**
     * @brief   @c MVEX.SSS controls embedded-rounding functionality.
     */
    ZYDIS_MVEX_FUNC_RC,
    /**
     * @brief   @c MVEX.SSS controls sae functionality.
     */
    ZYDIS_MVEX_FUNC_SAE,
    /**
     * @brief   No special operation (32bit float elements).
     */
    ZYDIS_MVEX_FUNC_F_32,
    /**
     * @brief   No special operation (32bit uint elements).
     */
    ZYDIS_MVEX_FUNC_I_32,
    /**
     * @brief   No special operation (64bit float elements).
     */
    ZYDIS_MVEX_FUNC_F_64,
    /**
     * @brief   No special operation (64bit uint elements).
     */
    ZYDIS_MVEX_FUNC_I_64,
    /**
     * @brief   Sf32(reg) or Si32(reg).
     */
    ZYDIS_MVEX_FUNC_SWIZZLE_32,
    /**
     * @brief   Sf64(reg) or Si64(reg).
     */
    ZYDIS_MVEX_FUNC_SWIZZLE_64,
    /**
     * @brief   Sf32(mem).
     */
    ZYDIS_MVEX_FUNC_SF_32,
    /**
     * @brief   Sf32(mem) broadcast only.
     */
    ZYDIS_MVEX_FUNC_SF_32_BCST,
    /**
     * @brief   Sf32(mem) broadcast 4to16 only.
     */
    ZYDIS_MVEX_FUNC_SF_32_BCST_4TO16,
    /**
     * @brief   Sf64(mem).
     */
    ZYDIS_MVEX_FUNC_SF_64,
    /**
     * @brief   Si32(mem).
     */
    ZYDIS_MVEX_FUNC_SI_32,
    /**
     * @brief   Si32(mem) broadcast only.
     */
    ZYDIS_MVEX_FUNC_SI_32_BCST,
    /**
     * @brief   Si32(mem) broadcast 4to16 only.
     */
    ZYDIS_MVEX_FUNC_SI_32_BCST_4TO16,
    /**
     * @brief   Si64(mem).
     */
    ZYDIS_MVEX_FUNC_SI_64,
    /**
     * @brief   Uf32.
     */
    ZYDIS_MVEX_FUNC_UF_32,
    /**
     * @brief   Uf64.
     */
    ZYDIS_MVEX_FUNC_UF_64,
    /**
     * @brief   Ui32.
     */
    ZYDIS_MVEX_FUNC_UI_32,
    /**
     * @brief   Ui64.
     */
    ZYDIS_MVEX_FUNC_UI_64,
    /**
     * @brief   Df32.
     */
    ZYDIS_MVEX_FUNC_DF_32,
    /**
     * @brief   Df64.
     */
    ZYDIS_MVEX_FUNC_DF_64,
    /**
     * @brief   Di32.
     */
    ZYDIS_MVEX_FUNC_DI_32,
    /**
     * @brief   Di64.
     */
    ZYDIS_MVEX_FUNC_DI_64,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_MVEX_FUNC_MAX_VALUE = ZYDIS_MVEX_FUNC_DI_64,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_MVEX_FUNC_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_MVEX_FUNC_MAX_VALUE)
} ZydisMVEXFunctionality;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisVEXStaticBroadcast` enum.
 */
typedef enum ZydisVEXStaticBroadcast
{
    ZYDIS_VEX_STATIC_BROADCAST_NONE,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_2,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_4,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_8,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_16,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_32,
    ZYDIS_VEX_STATIC_BROADCAST_2_TO_4,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_VEX_STATIC_BROADCAST_MAX_VALUE = ZYDIS_VEX_STATIC_BROADCAST_2_TO_4,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_VEX_STATIC_BROADCAST_REQUIRED_BITS =
        ZYDIS_BITS_TO_REPRESENT(ZYDIS_VEX_STATIC_BROADCAST_MAX_VALUE)
} ZydisVEXStaticBroadcast;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisEVEXStaticBroadcast` enum.
 */
typedef enum ZydisEVEXStaticBroadcast_
{
    ZYDIS_EVEX_STATIC_BROADCAST_NONE,
    ZYDIS_EVEX_STATIC_BROADCAST_1_TO_2,
    ZYDIS_EVEX_STATIC_BROADCAST_1_TO_4,
    ZYDIS_EVEX_STATIC_BROADCAST_1_TO_8,
    ZYDIS_EVEX_STATIC_BROADCAST_1_TO_16,
    ZYDIS_EVEX_STATIC_BROADCAST_1_TO_32,
    ZYDIS_EVEX_STATIC_BROADCAST_1_TO_64,
    ZYDIS_EVEX_STATIC_BROADCAST_2_TO_4,
    ZYDIS_EVEX_STATIC_BROADCAST_2_TO_8,
    ZYDIS_EVEX_STATIC_BROADCAST_2_TO_16,
    ZYDIS_EVEX_STATIC_BROADCAST_4_TO_8,
    ZYDIS_EVEX_STATIC_BROADCAST_4_TO_16,
    ZYDIS_EVEX_STATIC_BROADCAST_8_TO_16,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_EVEX_STATIC_BROADCAST_MAX_VALUE = ZYDIS_EVEX_STATIC_BROADCAST_8_TO_16,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_EVEX_STATIC_BROADCAST_REQUIRED_BITS =
        ZYDIS_BITS_TO_REPRESENT(ZYDIS_EVEX_STATIC_BROADCAST_MAX_VALUE)
} ZydisEVEXStaticBroadcast;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisMVEXStaticBroadcast` enum.
 */
typedef enum ZydisMVEXStaticBroadcast_
{
    ZYDIS_MVEX_STATIC_BROADCAST_NONE,
    ZYDIS_MVEX_STATIC_BROADCAST_1_TO_8,
    ZYDIS_MVEX_STATIC_BROADCAST_1_TO_16,
    ZYDIS_MVEX_STATIC_BROADCAST_4_TO_8,
    ZYDIS_MVEX_STATIC_BROADCAST_4_TO_16,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_MVEX_STATIC_BROADCAST_MAX_VALUE = ZYDIS_MVEX_STATIC_BROADCAST_4_TO_16,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_MVEX_STATIC_BROADCAST_REQUIRED_BITS =
        ZYDIS_BITS_TO_REPRESENT(ZYDIS_MVEX_STATIC_BROADCAST_MAX_VALUE)
} ZydisMVEXStaticBroadcast;

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisMaskPolicy` enum.
 */
typedef enum ZydisMaskPolicy_
{
    ZYDIS_MASK_POLICY_INVALID,
    /**
     * @brief   The instruction accepts mask-registers other than the default-mask (K0), but
     *          does not require them.
     */
    ZYDIS_MASK_POLICY_ALLOWED,
    /**
     * @brief   The instruction requires a mask-register other than the default-mask (K0).
     */
    ZYDIS_MASK_POLICY_REQUIRED,
    /**
     * @brief   The instruction does not allow a mask-register other than the default-mask (K0).
     */
    ZYDIS_MASK_POLICY_FORBIDDEN,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_MASK_POLICY_MAX_VALUE = ZYDIS_MASK_POLICY_FORBIDDEN,
    /**
     * @brief   The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_MASK_POLICY_REQUIRED_BITS = ZYDIS_BITS_TO_REPRESENT(ZYDIS_MASK_POLICY_MAX_VALUE)
} ZydisMaskPolicy;

/* ---------------------------------------------------------------------------------------------- */

// MSVC does not correctly execute the `pragma pack(1)` compiler-directive, if we use the correct
// enum types
ZYDIS_STATIC_ASSERT(ZYDIS_MNEMONIC_REQUIRED_BITS        <= 16);
ZYDIS_STATIC_ASSERT(ZYDIS_CATEGORY_REQUIRED_BITS        <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_ISA_SET_REQUIRED_BITS         <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_ISA_EXT_REQUIRED_BITS         <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_EXCEPTION_CLASS_REQUIRED_BITS <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_REG_CONSTRAINTS_REQUIRED_BITS <=  8);

#define ZYDIS_INSTRUCTION_DEFINITION_BASE \
    ZydisU16 mnemonic                       ZYDIS_BITFIELD(ZYDIS_MNEMONIC_REQUIRED_BITS); \
    ZydisU8 operandCount                    ZYDIS_BITFIELD( 4); \
    ZydisU16 operandReference               ZYDIS_BITFIELD(15); \
    ZydisU8 operandSizeMap                  ZYDIS_BITFIELD( 3); \
    ZydisU8 flagsReference                  ZYDIS_BITFIELD( 7); \
    ZydisBool requiresProtectedMode         ZYDIS_BITFIELD( 1); \
    ZydisBool acceptsAddressSizeOverride    ZYDIS_BITFIELD( 1); \
    ZydisU8 category                        ZYDIS_BITFIELD(ZYDIS_CATEGORY_REQUIRED_BITS); \
    ZydisU8 isaSet                          ZYDIS_BITFIELD(ZYDIS_ISA_SET_REQUIRED_BITS); \
    ZydisU8 isaExt                          ZYDIS_BITFIELD(ZYDIS_ISA_EXT_REQUIRED_BITS); \
    ZydisU8 exceptionClass                  ZYDIS_BITFIELD(ZYDIS_EXCEPTION_CLASS_REQUIRED_BITS); \
    ZydisU8 constrREG                       ZYDIS_BITFIELD(ZYDIS_REG_CONSTRAINTS_REQUIRED_BITS); \
    ZydisU8 constrRM                        ZYDIS_BITFIELD(ZYDIS_REG_CONSTRAINTS_REQUIRED_BITS)

#define ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR \
    ZYDIS_INSTRUCTION_DEFINITION_BASE; \
    ZydisU8 constrNDSNDD                    ZYDIS_BITFIELD(ZYDIS_REG_CONSTRAINTS_REQUIRED_BITS)

#define ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL \
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR; \
    ZydisBool isGather                      ZYDIS_BITFIELD( 1)

/**
 * @brief   Defines the `ZydisInstructionDefinition` struct.
 */
typedef struct ZydisInstructionDefinition_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
} ZydisInstructionDefinition;

/**
 * @brief   Defines the `ZydisInstructionDefinitionDEFAULT` struct.
 */
typedef struct ZydisInstructionDefinitionDEFAULT_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
    ZydisBool isPrivileged                  ZYDIS_BITFIELD( 1);
    ZydisBool isFarBranch                   ZYDIS_BITFIELD( 1);
    ZydisBool acceptsLOCK                   ZYDIS_BITFIELD( 1);
    ZydisBool acceptsREP                    ZYDIS_BITFIELD( 1);
    ZydisBool acceptsREPEREPZ               ZYDIS_BITFIELD( 1);
    ZydisBool acceptsREPNEREPNZ             ZYDIS_BITFIELD( 1);
    ZydisBool acceptsBOUND                  ZYDIS_BITFIELD( 1);
    ZydisBool acceptsXACQUIRE               ZYDIS_BITFIELD( 1);
    ZydisBool acceptsXRELEASE               ZYDIS_BITFIELD( 1);
    ZydisBool acceptsHLEWithoutLock         ZYDIS_BITFIELD( 1);
    ZydisBool acceptsBranchHints            ZYDIS_BITFIELD( 1);
    ZydisBool acceptsSegment                ZYDIS_BITFIELD( 1);
} ZydisInstructionDefinitionDEFAULT;

/**
 * @brief   Defines the `ZydisInstructionDefinition3DNOW` struct.
 */
typedef struct ZydisInstructionDefinition3DNOW_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
} ZydisInstructionDefinition3DNOW;

/**
 * @brief   Defines the `ZydisInstructionDefinitionXOP` struct.
 */
typedef struct ZydisInstructionDefinitionXOP_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR;
} ZydisInstructionDefinitionXOP;

// MSVC does not correctly execute the `pragma pack(1)` compiler-directive, if we use the correct
// enum types
ZYDIS_STATIC_ASSERT(ZYDIS_VEX_STATIC_BROADCAST_REQUIRED_BITS  <=  8);

/**
 * @brief   Defines the `ZydisInstructionDefinitionVEX` struct.
 */
typedef struct ZydisInstructionDefinitionVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL;
    ZydisU8 broadcast                       ZYDIS_BITFIELD(ZYDIS_VEX_STATIC_BROADCAST_REQUIRED_BITS);
} ZydisInstructionDefinitionVEX;

#ifndef ZYDIS_DISABLE_EVEX

// MSVC does not correctly execute the `pragma pack(1)` compiler-directive, if we use the correct
// enum types
ZYDIS_STATIC_ASSERT(ZYDIS_IVECTOR_LENGTH_REQUIRED_BITS        <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_TUPLETYPE_REQUIRED_BITS             <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_IELEMENT_SIZE_REQUIRED_BITS         <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_EVEX_FUNC_REQUIRED_BITS             <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_MASK_POLICY_REQUIRED_BITS           <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_EVEX_STATIC_BROADCAST_REQUIRED_BITS <=  8);

/**
 * @brief   Defines the `ZydisInstructionDefinitionEVEX` struct.
 */
typedef struct ZydisInstructionDefinitionEVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL;
    ZydisU8 vectorLength                    ZYDIS_BITFIELD(ZYDIS_IVECTOR_LENGTH_REQUIRED_BITS);
    ZydisU8 tupleType                       ZYDIS_BITFIELD(ZYDIS_TUPLETYPE_REQUIRED_BITS);
    ZydisU8 elementSize                     ZYDIS_BITFIELD(ZYDIS_IELEMENT_SIZE_REQUIRED_BITS);
    ZydisU8 functionality                   ZYDIS_BITFIELD(ZYDIS_EVEX_FUNC_REQUIRED_BITS);
    ZydisU8 maskPolicy                      ZYDIS_BITFIELD(ZYDIS_MASK_POLICY_REQUIRED_BITS);
    ZydisBool acceptsZeroMask               ZYDIS_BITFIELD( 1);
    ZydisBool isControlMask                 ZYDIS_BITFIELD( 1);
    ZydisU8 broadcast                       ZYDIS_BITFIELD(ZYDIS_EVEX_STATIC_BROADCAST_REQUIRED_BITS);
} ZydisInstructionDefinitionEVEX;
#endif

#ifndef ZYDIS_DISABLE_MVEX

// MSVC does not correctly execute the `pragma pack(1)` compiler-directive, if we use the correct
// enum types
ZYDIS_STATIC_ASSERT(ZYDIS_MVEX_FUNC_REQUIRED_BITS             <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_MASK_POLICY_REQUIRED_BITS           <=  8);
ZYDIS_STATIC_ASSERT(ZYDIS_MVEX_STATIC_BROADCAST_REQUIRED_BITS <=  8);

/**
 * @brief   Defines the `ZydisInstructionDefinitionMVEX` struct.
 */
typedef struct ZydisInstructionDefinitionMVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL;
    ZydisU8 functionality                   ZYDIS_BITFIELD(ZYDIS_MVEX_FUNC_REQUIRED_BITS);
    ZydisU8 maskPolicy                      ZYDIS_BITFIELD(ZYDIS_MASK_POLICY_REQUIRED_BITS);
    ZydisBool hasElementGranularity         ZYDIS_BITFIELD( 1);
    ZydisU8 broadcast                       ZYDIS_BITFIELD(ZYDIS_MVEX_STATIC_BROADCAST_REQUIRED_BITS);
} ZydisInstructionDefinitionMVEX;
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Accessed CPU flags                                                                             */
/* ---------------------------------------------------------------------------------------------- */

typedef struct ZydisAccessedFlags_
{
    ZydisCPUFlagAction action[ZYDIS_CPUFLAG_MAX_VALUE + 1];
} ZydisAccessedFlags;

/* ---------------------------------------------------------------------------------------------- */

#pragma pack(pop)

#ifdef ZYDIS_MSVC
#   pragma warning(pop)
#endif

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the instruction-definition with the given `encoding` and `id`.
 *
 * @param   encoding    The instruction-encoding.
 * @param   id          The definition-id.
 * @param   definition  A pointer to the variable that receives a pointer to the instruction-
 *                      definition.
 */
ZYDIS_NO_EXPORT void ZydisGetInstructionDefinition(ZydisInstructionEncoding encoding,
    ZydisU16 id, const ZydisInstructionDefinition** definition);

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the the operand-definitions for the given instruction-`definition`.
 *
 * @param   definition  A pointer to the instruction-definition.
 * @param   operand     A pointer to the variable that receives a pointer to the first operand-
 *                      definition of the instruction.
 *
 * @return  The number of operands for the given instruction-definition.
 */
ZYDIS_NO_EXPORT ZydisU8 ZydisGetOperandDefinitions(const ZydisInstructionDefinition* definition,
    const ZydisOperandDefinition** operand);

/* ---------------------------------------------------------------------------------------------- */
/* Element info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the actual type and size of an internal element-type.
 *
 * @param   element The internal element type.
 * @param   type    The actual element type.
 * @param   size    The element size.
 */
ZYDIS_NO_EXPORT void ZydisGetElementInfo(ZydisInternalElementType element, ZydisElementType* type,
    ZydisElementSize* size);

/* ---------------------------------------------------------------------------------------------- */
/* Accessed CPU flags                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the the operand-definitions for the given instruction-`definition`.
 *
 * @param   definition  A pointer to the instruction-definition.
 * @param   flags       A pointer to the variable that receives the `ZydisAccessedFlags` struct.
 *
 * @return  `ZYDIS_TRUE`, if the instruction accesses any flags, or `ZYDIS_FALSE`, if not.
 */
ZYDIS_NO_EXPORT ZydisBool ZydisGetAccessedFlags(const ZydisInstructionDefinition* definition,
    const ZydisAccessedFlags** flags);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INTERNAL_SHAREDDATA_H */
