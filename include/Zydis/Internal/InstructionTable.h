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

#ifndef ZYDIS_INSTRUCTIONTABLE_H
#define ZYDIS_INSTRUCTIONTABLE_H

#include <Zydis/Defines.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/InstructionInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ZYDIS_BITFIELD(x) : x

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
/* Instruction tree                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionTreeNodeType datatype.
 */                                 
typedef uint8_t ZydisInstructionTreeNodeType;

/**
 * @brief   Defines the @c ZydisInstructionTreeNodeValue datatype.
 */
typedef uint16_t ZydisInstructionTreeNodeValue;

/**
 * @brief   Defines the @c ZydisInstructionTreeNode struct.
 */
typedef struct ZydisInstructionTreeNode_
{
    ZydisInstructionTreeNodeType type;
    ZydisInstructionTreeNodeValue value;
} ZydisInstructionTreeNode;

/**
 * @brief   Values that represent zydis instruction tree node types.
 */
enum ZydisInstructionTreeNodeTypes
{
    ZYDIS_NODETYPE_INVALID                  = 0x00,
    /**
     * @brief   Reference to an instruction-definition.
     */
    ZYDIS_NODETYPE_DEFINITION_MASK          = 0x80,
    /**
     * @brief   Reference to an XOP-map filter.
     */
    ZYDIS_NODETYPE_FILTER_XOP               = 0x01,
    /**
     * @brief   Reference to an VEX-map filter.
     */
    ZYDIS_NODETYPE_FILTER_VEX               = 0x02,
    /**
     * @brief   Reference to an EVEX/MVEX-map filter.
     */
    ZYDIS_NODETYPE_FILTER_EMVEX             = 0x03,
    /**
     * @brief   Reference to an opcode filter.
     */
    ZYDIS_NODETYPE_FILTER_OPCODE            = 0x04,
    /**
     * @brief   Reference to an instruction-mode filter.
     */
    ZYDIS_NODETYPE_FILTER_MODE              = 0x05,
    /**
     * @brief   Reference to an compacted instruction-mode filter.
     */
    ZYDIS_NODETYPE_FILTER_MODE_COMPACT      = 0x06,
    /**
     * @brief   Reference to a ModRM.mod filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRM_MOD         = 0x07,
    /**
     * @brief   Reference to a compacted ModRM.mod filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRM_MOD_COMPACT = 0x08,
    /**
     * @brief   Reference to a ModRM.reg filter.
     */                                                                                      
    ZYDIS_NODETYPE_FILTER_MODRM_REG         = 0x09,
    /**
     * @brief   Reference to a ModRM.rm filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRM_RM          = 0x0A,
    /**
     * @brief   Reference to a mandatory-prefix filter.
     */
    ZYDIS_NODETYPE_FILTER_MANDATORY_PREFIX  = 0x0B,
    /**
     * @brief   Reference to an operand-size filter.
     */
    ZYDIS_NODETYPE_FILTER_OPERAND_SIZE      = 0x0C,
    /**
     * @brief   Reference to an address-size filter.
     */
    ZYDIS_NODETYPE_FILTER_ADDRESS_SIZE      = 0x0D,
    /**
     * @brief   Reference to a vector-length filter.
     */
    ZYDIS_NODETYPE_FILTER_VECTOR_LENGTH     = 0x0E,
    /**
     * @brief   Reference to an REX/VEX/EVEX.W filter.
     */
    ZYDIS_NODETYPE_FILTER_REX_W             = 0x0F,
    /**
     * @brief   Reference to an REX/VEX/EVEX.B filter.
     */
    ZYDIS_NODETYPE_FILTER_REX_B             = 0x10,
    /**
     * @brief   Reference to an EVEX.b filter.
     */
    ZYDIS_NODETYPE_FILTER_EVEX_B            = 0x11,
    /**
     * @brief   Reference to an EVEX.z filter.
     */
    ZYDIS_NODETYPE_FILTER_EVEX_Z            = 0x12,
    /**
     * @brief   Reference to an MVEX.E filter.
     */
    ZYDIS_NODETYPE_FILTER_MVEX_E            = 0x13,
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisSemanticOperandType datatype.
 */
typedef uint8_t ZydisSemanticOperandType;

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
    ZYDIS_SEMANTIC_OPTYPE_MOFFS    
};

/**
 * @brief   Defines the @c ZydisInternalElementType datatype.
 */
typedef uint8_t ZydisInternalElementType;

/**
 * @brief   Values that represent internal element-types.
 */
enum ZydisInternalElementTypes
{
    ZYDIS_IELEMENT_TYPE_INVALID,
    ZYDIS_IELEMENT_TYPE_VARIABLE, // TODO: Remove
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
    uint16_t size[3];
    ZydisInternalElementType elementType    ZYDIS_BITFIELD(5);
    union
    {
        uint8_t encoding; 
        struct
        {
            uint8_t type                    ZYDIS_BITFIELD(3);
            union
            {
                ZydisRegister reg;
                uint8_t id                  ZYDIS_BITFIELD(6);
            } reg;
        } reg;
        struct 
        {
            uint8_t seg                     ZYDIS_BITFIELD(3);
            uint8_t base                    ZYDIS_BITFIELD(3); 
            ZydisOperandAction baseAction   ZYDIS_BITFIELD(3);
        } mem;
    } op;
} ZydisOperandDefinition;

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

enum ZydisImplicitMemBase
{
    ZYDIS_IMPLMEM_BASE_ABX,
    ZYDIS_IMPLMEM_BASE_ABP,
    ZYDIS_IMPLMEM_BASE_ASI,
    ZYDIS_IMPLMEM_BASE_ADI    
};

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInternalVectorLength datatype.
 */
typedef uint8_t ZydisInternalVectorLength;

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
typedef uint8_t ZydisInternalElementSize;

/**
 * @brief   Values that represent internal element-sizes.
 */
enum ZydisInternalElementSizes
{
    ZYDIS_IELEMENT_SIZE_INVALID,
    ZYDIS_IELEMENT_SIZE_8,
    ZYDIS_IELEMENT_SIZE_16,
    ZYDIS_IELEMENT_SIZE_32,
    ZYDIS_IELEMENT_SIZE_64
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEVEXFunctionality datatype.
 */
typedef uint8_t ZydisEVEXFunctionality;

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
typedef uint8_t ZydisEVEXTupleType;

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
typedef uint8_t ZydisMVEXFunctionality;

/**
 * @brief   Values that represent MVEX-functionalities.
 */
enum ZydisMVEXFunctionalities
{
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
typedef uint8_t ZydisVEXStaticBroadcast;

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
    ZYDIS_VEX_STATIC_BROADCAST_2_TO_4   
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEVEXStaticBroadcast datatype.
 */
typedef uint8_t ZydisEVEXStaticBroadcast;

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
    ZYDIS_EVEX_STATIC_BROADCAST_8_TO_16   
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisMVEXStaticBroadcast datatype.
 */
typedef uint8_t ZydisMVEXStaticBroadcast;

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
typedef uint8_t ZydisMaskPolicy;

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
    ZydisInstructionMnemonic mnemonic       ZYDIS_BITFIELD(11); \
    uint8_t operandCount                    ZYDIS_BITFIELD( 4); \
    uint16_t operandReference               ZYDIS_BITFIELD(15); \
    uint8_t operandSizeMap                  ZYDIS_BITFIELD( 3)

/**
 * @brief   Defines the @c ZydisInstructionDefinition struct.
 */
typedef struct ZydisInstructionDefinition_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
} ZydisInstructionDefinition;

typedef struct ZydisInstructionDefinitionDEFAULT_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
    ZydisBool acceptsLock                   ZYDIS_BITFIELD(1);
    ZydisBool acceptsREP                    ZYDIS_BITFIELD(1);
    ZydisBool acceptsREPEREPZ               ZYDIS_BITFIELD(1);
    ZydisBool acceptsREPNEREPNZ             ZYDIS_BITFIELD(1);
    ZydisBool acceptsBOUND                  ZYDIS_BITFIELD(1);
    ZydisBool acceptsXACQUIRE               ZYDIS_BITFIELD(1);
    ZydisBool acceptsXRELEASE               ZYDIS_BITFIELD(1);
    ZydisBool acceptsHLEWithoutLock         ZYDIS_BITFIELD(1);
    ZydisBool acceptsBranchHints            ZYDIS_BITFIELD(1);
    ZydisBool acceptsSegment                ZYDIS_BITFIELD(1);
} ZydisInstructionDefinitionDEFAULT;

typedef struct ZydisInstructionDefinition3DNOW_
{
    ZydisInstructionDefinition base;
} ZydisInstructionDefinition3DNOW;

typedef struct ZydisInstructionDefinitionXOP_
{
    ZydisInstructionDefinition base;
} ZydisInstructionDefinitionXOP;

typedef struct ZydisInstructionDefinitionVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
    ZydisVEXStaticBroadcast broadcast       ZYDIS_BITFIELD(3);
} ZydisInstructionDefinitionVEX;

typedef struct ZydisInstructionDefinitionEVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
    ZydisInternalVectorLength vectorLength  ZYDIS_BITFIELD(2);
    ZydisEVEXTupleType tupleType            ZYDIS_BITFIELD(4);
    ZydisInternalElementSize elementSize    ZYDIS_BITFIELD(4);
    ZydisEVEXFunctionality functionality    ZYDIS_BITFIELD(2);
    ZydisMaskPolicy maskPolicy              ZYDIS_BITFIELD(2);
    ZydisEVEXStaticBroadcast broadcast      ZYDIS_BITFIELD(4);
} ZydisInstructionDefinitionEVEX;

typedef struct ZydisInstructionDefinitionMVEX_
{
    ZYDIS_INSTRUCTION_DEFINITION_BASE;
    ZydisMVEXFunctionality functionality    ZYDIS_BITFIELD(5);
    ZydisMaskPolicy maskPolicy              ZYDIS_BITFIELD(2);
    ZydisBool hasElementGranularity         ZYDIS_BITFIELD(1);
    ZydisMVEXStaticBroadcast broadcast      ZYDIS_BITFIELD(3);
} ZydisInstructionDefinitionMVEX;

/* ---------------------------------------------------------------------------------------------- */

#pragma pack(pop)

#ifdef ZYDIS_MSVC
#   pragma warning(pop)
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Physical instruction info                                                                      */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionPartFlags datatype.
 */
typedef uint8_t ZydisInstructionPartFlags;

/**
 * @brief   The instruction has an optional modrm byte.
 */
#define ZYDIS_INSTRPART_FLAG_HAS_MODRM      0x01

/**
 * @brief   The instruction has an optional displacement value.
 */
#define ZYDIS_INSTRPART_FLAG_HAS_DISP       0x02

/**
 * @brief   The instruction has an optional immediate value.
 */
#define ZYDIS_INSTRPART_FLAG_HAS_IMM0       0x04

/**
 * @brief   The instruction has a second optional immediate value.
 */
#define ZYDIS_INSTRPART_FLAG_HAS_IMM1       0x08

typedef struct ZydisInstructionParts_
{
    /**
     * @brief   
     */
    ZydisInstructionPartFlags flags;
    /**
     * @brief   Displacement info.
     */
    struct
    {
        /**
         * @brief   The size of the displacement value.
         */
        uint8_t size[3];
    } disp;
    /**
     * @brief   Immediate info.
     */
    struct
    {
        /**
         * @brief   The size of the immediate value.
         */
        uint8_t size[3];
        /**
         * @brief   Signals, if the value is signed.
         */
        ZydisBool isSigned;
        /**
         * @brief   Signals, if the value is a relative offset.
         */
        ZydisBool isRelative;
    } imm[2];
} ZydisInstructionParts;

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction tree                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the root node of the instruction tree.
 *
 * @return  The root node of the instruction tree.
 */
ZYDIS_NO_EXPORT const ZydisInstructionTreeNode* ZydisInstructionTreeGetRootNode();

/**
 * @brief   Returns the child node of @c parent specified by @c index.
 *
 * @param   parent  The parent node.
 * @param   index   The index of the child node to retrieve.
 *                  
 * @return  The specified child node.
 */
ZYDIS_NO_EXPORT const ZydisInstructionTreeNode* ZydisInstructionTreeGetChildNode(
    const ZydisInstructionTreeNode* parent, uint16_t index);

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the instruction- and operand-definition that is linked to the given @c node.
 *
 * @param   node            The instruction definition node.
 * @param   definition      A pointer to a variable that receives a pointer to the 
 */
ZYDIS_NO_EXPORT void ZydisGetInstructionDefinition(const ZydisInstructionTreeNode* node,
    const ZydisInstructionDefinition** definition);

/**
 * @brief   Returns information about optional instruction parts (like modrm, displacement or 
 *          immediates) for the instruction that is linked to the given @c node.
 *
 * @param   node    The instruction definition node.
 * @param   info    A pointer to the @c ZydisInstructionParts struct.        
 */
ZYDIS_NO_EXPORT void ZydisGetOptionalInstructionParts(const ZydisInstructionTreeNode* node, 
    const ZydisInstructionParts** info);

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the instruction- and operand-definition that is linked to the given @c node.
 *
 * @param   definition      A pointer to the instruction-definition.
 * @param   operands        A pointer to a variable that receives a pointer to the first 
 *                          operand-definition of the instruction.
 *                          
 * @return  The number of operands for the given instruction-definition.
 */
ZYDIS_NO_EXPORT uint8_t ZydisGetOperandDefinitions(const ZydisInstructionDefinition* definition, 
    const ZydisOperandDefinition** operands);

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

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INSTRUCTIONTABLE_H */
