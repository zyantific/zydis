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
 * @brief   Defines the @c ZydisSemanticOperandType datatype.
 */
typedef ZydisU8 ZydisSemanticOperandType;

/**
 * @brief   Values that represent semantic operand-types.
 */
enum ZydisSemanticOperandTypes
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
    ZYDIS_SEMANTIC_OPTYPE_MIB
};

/**
 * @brief   Defines the @c ZydisInternalElementType datatype.
 */
typedef ZydisU8 ZydisInternalElementType;

/**
 * @brief   Values that represent internal element-types.
 */
enum ZydisInternalElementTypes
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
    ZYDIS_IELEMENT_TYPE_BCD80
};

/**
 * @brief   Defines the @c ZydisOperandDefinition struct.
 */
typedef struct ZydisOperandDefinition_
{
    ZydisSemanticOperandType type           ZYDIS_BITFIELD(5);
    ZydisOperandVisibility visibility       ZYDIS_BITFIELD(2);
    ZydisOperandAction action               ZYDIS_BITFIELD(3);
    ZydisU16 size[3];
    ZydisInternalElementType elementType    ZYDIS_BITFIELD(5);
    union
    {
        ZydisOperandEncoding encoding;
        struct
        {
            ZydisU8 type                    ZYDIS_BITFIELD(3);
            union
            {
                ZydisRegister reg           ZYDIS_BITFIELD(ZYDIS_REGISTER_MIN_BITS);
                ZydisU8 id                  ZYDIS_BITFIELD(6);
            } reg;
        } reg;
        struct
        {
            ZydisU8 seg                     ZYDIS_BITFIELD(3);
            ZydisU8 base                    ZYDIS_BITFIELD(3);
        } mem;
    } op;
} ZydisOperandDefinition;

/**
 * @brief   Values that represent implicit-register types.
 */
enum ZydisImplicitRegisterType
{
    ZYDIS_IMPLREG_TYPE_STATIC,
    ZYDIS_IMPLREG_TYPE_GPR_OSZ,
    ZYDIS_IMPLREG_TYPE_GPR_ASZ,
    ZYDIS_IMPLREG_TYPE_GPR_SSZ,
    ZYDIS_IMPLREG_TYPE_IP_ASZ,
    ZYDIS_IMPLREG_TYPE_IP_SSZ,
    ZYDIS_IMPLREG_TYPE_FLAGS_SSZ
};

/**
 * @brief   Values that represent implicit-memory base-registers.
 */
enum ZydisImplicitMemBase
{
    ZYDIS_IMPLMEM_BASE_ABX,
    ZYDIS_IMPLMEM_BASE_ASP,
    ZYDIS_IMPLMEM_BASE_ABP,
    ZYDIS_IMPLMEM_BASE_ASI,
    ZYDIS_IMPLMEM_BASE_ADI
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisRegisterConstraint` datatype.
 */
typedef ZydisU8 ZydisRegisterConstraint;

/**
 * @brief   Values that represent register-constraints.
 */
enum ZydisRegisterConstraints
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

    ZYDIS_REG_CONSTRAINTS_MAX_VALUE = ZYDIS_REG_CONSTRAINTS_VSIB,
    ZYDIS_REG_CONSTRAINTS_MIN_BITS  = 4
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInternalVectorLength datatype.
 */
typedef ZydisU8 ZydisInternalVectorLength;

/**
 * @brief   Values that represent internal vector-lengths.
 */
enum ZydisInternalVectorLengths
{
    ZYDIS_IVECTOR_LENGTH_DEFAULT,
    ZYDIS_IVECTOR_LENGTH_FIXED_128,
    ZYDIS_IVECTOR_LENGTH_FIXED_256,
    ZYDIS_IVECTOR_LENGTH_FIXED_512
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInternalElementSize datatype.
 */
typedef ZydisU8 ZydisInternalElementSize;

/**
 * @brief   Values that represent internal element-sizes.
 */
enum ZydisInternalElementSizes
{
    ZYDIS_IELEMENT_SIZE_INVALID,
    ZYDIS_IELEMENT_SIZE_8,
    ZYDIS_IELEMENT_SIZE_16,
    ZYDIS_IELEMENT_SIZE_32,
    ZYDIS_IELEMENT_SIZE_64,
    ZYDIS_IELEMENT_SIZE_128,

    ZYDIS_IELEMENT_SIZE_MAX_VALUE = ZYDIS_IELEMENT_SIZE_128
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEVEXFunctionality datatype.
 */
typedef ZydisU8 ZydisEVEXFunctionality;

/**
 * @brief   Values that represent EVEX-functionalities.
 */
enum ZydisEVEXFunctionalities
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
    ZYDIS_EVEX_FUNC_SAE
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEVEXTupleType datatype.
 */
typedef ZydisU8 ZydisEVEXTupleType;

/**
 * @brief   Values that represent EVEX tuple-types.
 */
enum ZydisEVEXTupleTypes
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

/**
 * @brief   Defines the @c ZydisMVEXFunctionality datatype.
 */
typedef ZydisU8 ZydisMVEXFunctionality;

/**
 * @brief   Values that represent MVEX-functionalities.
 */
enum ZydisMVEXFunctionalities
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
    ZYDIS_MVEX_FUNC_DI_64
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisVEXStaticBroadcast datatype.
 */
typedef ZydisU8 ZydisVEXStaticBroadcast;

/**
 * @brief   Values that represent static VEX-broadcasts.
 */
enum ZydisVEXStaticBroadcasts
{
    ZYDIS_VEX_STATIC_BROADCAST_NONE,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_2,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_4,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_8,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_16,
    ZYDIS_VEX_STATIC_BROADCAST_1_TO_32,
    ZYDIS_VEX_STATIC_BROADCAST_2_TO_4,

    ZYDIS_VEX_STATIC_BROADCAST_MAX_VALUE = ZYDIS_VEX_STATIC_BROADCAST_2_TO_4
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEVEXStaticBroadcast datatype.
 */
typedef ZydisU8 ZydisEVEXStaticBroadcast;

/**
 * @brief   Values that represent static EVEX-broadcasts.
 */
enum ZydisEVEXStaticBroadcasts
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

    ZYDIS_EVEX_STATIC_BROADCAST_MAX_VALUE = ZYDIS_EVEX_STATIC_BROADCAST_8_TO_16
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisMVEXStaticBroadcast datatype.
 */
typedef ZydisU8 ZydisMVEXStaticBroadcast;

/**
 * @brief   Values that represent static MVEX-broadcasts.
 */
enum ZydisMVEXStaticBroadcasts
{
    ZYDIS_MVEX_STATIC_BROADCAST_NONE,
    ZYDIS_MVEX_STATIC_BROADCAST_1_TO_8,
    ZYDIS_MVEX_STATIC_BROADCAST_1_TO_16,
    ZYDIS_MVEX_STATIC_BROADCAST_4_TO_8,
    ZYDIS_MVEX_STATIC_BROADCAST_4_TO_16
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisMaskPolicy datatype.
 */
typedef ZydisU8 ZydisMaskPolicy;

/**
 * @brief   Values that represent AVX mask policies.
 */
enum ZydisMaskPolicies
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
    ZYDIS_MASK_POLICY_FORBIDDEN
};

/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_INSTRUCTION_DEFINITION_BASE \
    ZydisMnemonic mnemonic                  ZYDIS_BITFIELD(ZYDIS_MNEMONIC_MIN_BITS); \
    ZydisU8 operandCount                    ZYDIS_BITFIELD( 4); \
    ZydisU16 operandReference               ZYDIS_BITFIELD(15); \
    ZydisU8 operandSizeMap                  ZYDIS_BITFIELD( 3); \
    ZydisU8 flagsReference                  ZYDIS_BITFIELD( 7); \
    ZydisBool requiresProtectedMode         ZYDIS_BITFIELD( 1); \
    ZydisBool acceptsAddressSizeOverride    ZYDIS_BITFIELD( 1); \
    ZydisInstructionCategory category       ZYDIS_BITFIELD(ZYDIS_CATEGORY_MIN_BITS); \
    ZydisISASet isaSet                      ZYDIS_BITFIELD(ZYDIS_ISA_SET_MIN_BITS); \
    ZydisISAExt isaExt                      ZYDIS_BITFIELD(ZYDIS_ISA_EXT_MIN_BITS); \
    ZydisExceptionClass exceptionClass      ZYDIS_BITFIELD( 6); \
    ZydisRegisterConstraint constrREG       ZYDIS_BITFIELD(ZYDIS_REG_CONSTRAINTS_MIN_BITS); \
    ZydisRegisterConstraint constrRM        ZYDIS_BITFIELD(ZYDIS_REG_CONSTRAINTS_MIN_BITS)

#define ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR \
    ZYDIS_INSTRUCTION_DEFINITION_BASE; \
    ZydisRegisterConstraint constrNDSNDD    ZYDIS_BITFIELD(ZYDIS_REG_CONSTRAINTS_MIN_BITS)

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

/**
 * @brief   Defines the `ZydisInstructionDefinitionVEX` struct.
 */
typedef struct ZydisInstructionDefinitionVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL;
    ZydisVEXStaticBroadcast broadcast       ZYDIS_BITFIELD( 3);
} ZydisInstructionDefinitionVEX;

#ifndef ZYDIS_DISABLE_EVEX
/**
 * @brief   Defines the `ZydisInstructionDefinitionEVEX` struct.
 */
typedef struct ZydisInstructionDefinitionEVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL;
    ZydisInternalVectorLength vectorLength  ZYDIS_BITFIELD( 2);
    ZydisEVEXTupleType tupleType            ZYDIS_BITFIELD( 4);
    ZydisInternalElementSize elementSize    ZYDIS_BITFIELD( 3);
    ZydisEVEXFunctionality functionality    ZYDIS_BITFIELD( 2);
    ZydisMaskPolicy maskPolicy              ZYDIS_BITFIELD( 2);
    ZydisBool acceptsZeroMask               ZYDIS_BITFIELD( 1);
    ZydisBool isControlMask                 ZYDIS_BITFIELD( 1);
    ZydisEVEXStaticBroadcast broadcast      ZYDIS_BITFIELD( 4);
} ZydisInstructionDefinitionEVEX;
#endif

#ifndef ZYDIS_DISABLE_MVEX
/**
 * @brief   Defines the `ZydisInstructionDefinitionMVEX` struct.
 */
typedef struct ZydisInstructionDefinitionMVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE_VECTOR_INTEL;
    ZydisMVEXFunctionality functionality    ZYDIS_BITFIELD( 5);
    ZydisMaskPolicy maskPolicy              ZYDIS_BITFIELD( 2);
    ZydisBool hasElementGranularity         ZYDIS_BITFIELD( 1);
    ZydisMVEXStaticBroadcast broadcast      ZYDIS_BITFIELD( 3);
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
 */
ZYDIS_NO_EXPORT void ZydisGetAccessedFlags(const ZydisInstructionDefinition* definition,
    const ZydisAccessedFlags** flags);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INTERNAL_SHAREDDATA_H */
