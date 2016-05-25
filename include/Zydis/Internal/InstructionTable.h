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

#ifndef ZYDIS_INSTRUCTIONTABLE_H
#define ZYDIS_INSTRUCTIONTABLE_H

#include <stdint.h>
#include <assert.h>
#include <Zydis/Defines.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/InstructionInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction table                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisInstructionTableNodeType datatype.
 */
typedef uint8_t ZydisInstructionTableNodeType;

/**
 * @brief   Values that represent zydis instruction table node types.
 */
enum ZydisInstructionTableNodeTypes
{
    ZYDIS_NODETYPE_INVALID                  = 0x00,
    /**
     * @brief   Reference to a concrete instruction definition.
     */
    ZYDIS_NODETYPE_DEFINITION               = 0x01,
    /**
     * @brief   Reference to an opcode filter.
     */
    ZYDIS_NODETYPE_FILTER_OPCODE            = 0x02,
    /**
     * @brief   Reference to an vex-map filter.
     */
    ZYDIS_NODETYPE_FILTER_VEX               = 0x03,
    /**
     * @brief   Reference to an xop-map filter.
     */
    ZYDIS_NODETYPE_FILTER_XOP               = 0x04,
    /**
     * @brief   Reference to an instruction-mode filter.
     */
    ZYDIS_NODETYPE_FILTER_MODE              = 0x05,
    /**
     * @brief   Reference to a mandatory-prefix filter.
     */
    ZYDIS_NODETYPE_FILTER_MANDATORYPREFIX   = 0x06,
    /**
     * @brief   Reference to a modrm.mod filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRMMOD          = 0x07,
    /**
     * @brief   Reference to a modrm.reg filter.
     */                                                                                      
    ZYDIS_NODETYPE_FILTER_MODRMREG          = 0x08,
    /**
     * @brief   Reference to a modrm.rm filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRMRM           = 0x09,  
    /**
     * @brief   Reference to an operand-size filter.
     */
    ZYDIS_NODETYPE_FILTER_OPERANDSIZE       = 0x0A,
    /**
     * @brief   Reference to an address-size filter.
     */
    ZYDIS_NODETYPE_FILTER_ADDRESSSIZE       = 0x0B,
    /**
     * @brief   Reference to an rex/vex/evex.w filter.
     */
    ZYDIS_NODETYPE_FILTER_REXW              = 0x0C,
    /**
     * @brief   Reference to an vex/evex.l filter.
     */
    ZYDIS_NODETYPE_FILTER_VEXL              = 0x0D,
    /**
     * @brief   Reference to an evex.l' filter.
     */
    ZYDIS_NODETYPE_FILTER_EVEXL2            = 0x0E,
    /**
     * @brief   Reference to an evex.b filter.
     */
    ZYDIS_NODETYPE_FILTER_EVEXB             = 0x0F
};

/* ---------------------------------------------------------------------------------------------- */

#pragma pack (push, 1)
/**
 * @brief   Defines the @c ZydisInstructionTableNode struct.
 */
typedef struct ZydisInstructionTableNode_
{
    /**
     * @brief   The instruction table node type.
     */
    ZydisInstructionTableNodeType type;
    /**
     * @brief   The instruction table node value.
     */
    uint16_t value;
} ZydisInstructionTableNode;
#pragma pack (pop)

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisSemanticOperandType datatype.
 */
typedef uint8_t ZydisSemanticOperandType;

/**
 * @brief   Values that represent semantic operand types.
 */
enum ZydisSemanticOperandTypes
{
    ZYDIS_SEM_OPERAND_TYPE_UNUSED,
    ZYDIS_SEM_OPERAND_TYPE_GPR8,
    ZYDIS_SEM_OPERAND_TYPE_GPR16,
    ZYDIS_SEM_OPERAND_TYPE_GPR32,
    ZYDIS_SEM_OPERAND_TYPE_GPR64,
    ZYDIS_SEM_OPERAND_TYPE_FPR,
    ZYDIS_SEM_OPERAND_TYPE_VR64,
    ZYDIS_SEM_OPERAND_TYPE_VR128,
    ZYDIS_SEM_OPERAND_TYPE_VR256,
    ZYDIS_SEM_OPERAND_TYPE_VR512,
    ZYDIS_SEM_OPERAND_TYPE_CR,
    ZYDIS_SEM_OPERAND_TYPE_DR,
    ZYDIS_SEM_OPERAND_TYPE_SREG,
    ZYDIS_SEM_OPERAND_TYPE_MSKR,
    ZYDIS_SEM_OPERAND_TYPE_BNDR,
    ZYDIS_SEM_OPERAND_TYPE_MEM,
    ZYDIS_SEM_OPERAND_TYPE_MEM8,
    ZYDIS_SEM_OPERAND_TYPE_MEM16,
    ZYDIS_SEM_OPERAND_TYPE_MEM32,
    ZYDIS_SEM_OPERAND_TYPE_MEM64,
    ZYDIS_SEM_OPERAND_TYPE_MEM80,
    ZYDIS_SEM_OPERAND_TYPE_MEM128,
    ZYDIS_SEM_OPERAND_TYPE_MEM256,
    ZYDIS_SEM_OPERAND_TYPE_MEM512,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST2,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST4,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST8,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_BCST16,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST2,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST4,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST8,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_BCST16,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBX,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBY,
    ZYDIS_SEM_OPERAND_TYPE_MEM32_VSIBZ,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBX,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBY,
    ZYDIS_SEM_OPERAND_TYPE_MEM64_VSIBZ,
    ZYDIS_SEM_OPERAND_TYPE_M1616,
    ZYDIS_SEM_OPERAND_TYPE_M1632,
    ZYDIS_SEM_OPERAND_TYPE_M1664,
    ZYDIS_SEM_OPERAND_TYPE_MEM112,
    ZYDIS_SEM_OPERAND_TYPE_MEM224,
    ZYDIS_SEM_OPERAND_TYPE_IMM8,
    ZYDIS_SEM_OPERAND_TYPE_IMM16,
    ZYDIS_SEM_OPERAND_TYPE_IMM32,
    ZYDIS_SEM_OPERAND_TYPE_IMM64,
    ZYDIS_SEM_OPERAND_TYPE_IMM8U,
    ZYDIS_SEM_OPERAND_TYPE_REL8,
    ZYDIS_SEM_OPERAND_TYPE_REL16,
    ZYDIS_SEM_OPERAND_TYPE_REL32,
    ZYDIS_SEM_OPERAND_TYPE_REL64,
    ZYDIS_SEM_OPERAND_TYPE_PTR1616,
    ZYDIS_SEM_OPERAND_TYPE_PTR1632,
    ZYDIS_SEM_OPERAND_TYPE_PTR1664,
    ZYDIS_SEM_OPERAND_TYPE_MOFFS16,
    ZYDIS_SEM_OPERAND_TYPE_MOFFS32,
    ZYDIS_SEM_OPERAND_TYPE_MOFFS64,
    ZYDIS_SEM_OPERAND_TYPE_SRCIDX8,
    ZYDIS_SEM_OPERAND_TYPE_SRCIDX16,
    ZYDIS_SEM_OPERAND_TYPE_SRCIDX32,
    ZYDIS_SEM_OPERAND_TYPE_SRCIDX64,
    ZYDIS_SEM_OPERAND_TYPE_DSTIDX8,
    ZYDIS_SEM_OPERAND_TYPE_DSTIDX16,
    ZYDIS_SEM_OPERAND_TYPE_DSTIDX32,
    ZYDIS_SEM_OPERAND_TYPE_DSTIDX64,
    ZYDIS_SEM_OPERAND_TYPE_FIXED1,
    ZYDIS_SEM_OPERAND_TYPE_AL,
    ZYDIS_SEM_OPERAND_TYPE_CL,
    ZYDIS_SEM_OPERAND_TYPE_AX,
    ZYDIS_SEM_OPERAND_TYPE_DX,
    ZYDIS_SEM_OPERAND_TYPE_EAX,
    ZYDIS_SEM_OPERAND_TYPE_RAX,
    ZYDIS_SEM_OPERAND_TYPE_ES,
    ZYDIS_SEM_OPERAND_TYPE_CS,
    ZYDIS_SEM_OPERAND_TYPE_SS,
    ZYDIS_SEM_OPERAND_TYPE_DS,
    ZYDIS_SEM_OPERAND_TYPE_GS,
    ZYDIS_SEM_OPERAND_TYPE_FS,
    ZYDIS_SEM_OPERAND_TYPE_ST0
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisEvexBFunctionality datatype .
 */
typedef uint8_t ZydisEvexBFunctionality;

/**
 * @brief   Values that represent zydis evex.b-functionalities.
 */
enum ZydisEvexBFunctionalities
{
    ZYDIS_EVEXB_FUNCTIONALITY_NONE,
    ZYDIS_EVEXB_FUNCTIONALITY_BC,
    ZYDIS_EVEXB_FUNCTIONALITY_RC,
    ZYDIS_EVEXB_FUNCTIONALITY_SAE
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis operand definition datatype.
 */
typedef uint16_t ZydisOperandDefinition;

#pragma pack (push, 1)

/**
 * @brief   Defines the zydis operands definition datatype.
 */
typedef struct ZydisInstructionOperands_
{
    ZydisOperandDefinition operands[4];
} ZydisInstructionOperands;

/**
 * @brief   Defines the zydis instruction definition struct.
 */
typedef struct ZydisInstructionDefinition_
{
    /**
     * @brief   The instruction mnemonic.
     */
    ZydisInstructionMnemonic mnemonic;
    /**
     * @brief   The instruction operand.
     */
    uint16_t operands;
    //ZydisOperandDefinition operands[4];
} ZydisInstructionDefinition;
#pragma pack (pop)

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/**
 * @brief   Contains all opcode filters.
 *          
 *          Indexed by the numeric value of the opcode.
 */
extern const ZydisInstructionTableNode filterOpcode[][256];

/**
 * @brief   Contains all vex-map filters.
 *          
 *          Index values:
 *          0 = LES, LDS or BOUND instruction (default encoding)
 *          1 = 0F  
 *          2 = 0F38  
 *          3 = 0F3A  
 *          4 = 66  
 *          5 = 66_0F  
 *          6 = 66_0F38  
 *          7 = 66_0F3A  
 *          8 = F3  
 *          9 = F3_0F
 *          A = F3_0F38
 *          B = F3_0F3A
 *          C = F2
 *          D = F2_0F
 *          E = F2_0F38
 *          F = F2_0F3A
 */
extern const ZydisInstructionTableNode filterVEX[][16];

/**
 * @brief   Contains all xop-map filters.
 *          
 *          Index values:
 *          0 = POP instruction (default encoding)
 *          1 = xop8
 *          2 = xop9
 *          3 = xopA
 */
extern const ZydisInstructionTableNode filterXOP[][4];

/**
 * @brief   Contains all instruction-mode filters.
 *          
 *          Index values:
 *          0 = 64 bit mode required
 *          1 = 64 bit mode excluded
 */
extern const ZydisInstructionTableNode filterMode[][2];

/**
 * @brief   Contains all mandatory-prefix switch tables.
 *          
 *          Index values:
 *          0 = none
 *          1 = 66  
 *          2 = F3  
 *          3 = F2
 */
extern const ZydisInstructionTableNode filterMandatoryPrefix[][4];

/**
 * @brief   Contains all modrm.mod filters.
 *          
 *          Index values:
 *          0 = [modrm_mod == !11] = memory
 *          1 = [modrm_mod ==  11] = register
 */
extern const ZydisInstructionTableNode filterModrmMod[][2];

/**
 * @brief   Contains all modrm.reg filters.
 *          
 *          Indexed by the numeric value of the modrm_reg field.
 */
extern const ZydisInstructionTableNode filterModrmReg[][8];

/**
 * @brief   Contains all modrm.rm filters.
 *          
 *          Indexed by the numeric value of the modrm_rm field.
 */
extern const ZydisInstructionTableNode filterModrmRm[][8];

/**
 * @brief   Contains all operand-size filters.
 *          
 *          Index values:
 *          0 = 16bit = 0x66 prefix in 32 bit mode
 *          1 = 32bit = 0x66 prefix in 16 bit mode  
 */
extern const ZydisInstructionTableNode filterOperandSize[][2];

/**
 * @brief   Contains all address-size filters.
 *          
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const ZydisInstructionTableNode filterAddressSize[][3];

/**
 * @brief   Contains all rex/vex/evex.w filters.
 *          
 *          Indexed by the numeric value of the rex/vex/evex.w field.
 */
extern const ZydisInstructionTableNode filterREXW[][2];

/**
 * @brief   Contains all vex.l filters.
 *          
 *          Indexed by the numeric value of the vex/evex.l field.
 */
extern const ZydisInstructionTableNode filterVEXL[][2];

/**
 * @brief   Contains all evex.l' filters.
 *          
 *          Indexed by the numeric value of the evex.l' field.
 */
extern const ZydisInstructionTableNode filterEVEXL2[][2];

/**
 * @brief   Contains all evex.b filters.
 *          
 *          Indexed by the numeric value of the evex.b field.
 */
extern const ZydisInstructionTableNode filterEVEXB[][2];

/**
 * @brief   Contains all instruction-definitions.
 */
extern const ZydisInstructionDefinition instructionDefinitions[];

/**
 * @brief   Contains all instruction-operand-definitions.
 */
extern const ZydisInstructionOperands instructionOperands[];

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/**
 * @brief   Returns the type of the specified instruction table node.
 *
 * @param   node    The node.
 *                  
 * @return  The type of the specified instruction table node.
 */
ZYDIS_INLINE ZydisInstructionTableNodeType ZydisInstructionTableGetNodeType(
    ZydisInstructionTableNode node)
{
    return node.type;
} 

/**
 * @brief   Returns the value of the specified instruction table node.
 *
 * @param   node    The node.
 *                  
 * @return  The value of the specified instruction table node.
 */
ZYDIS_INLINE uint16_t ZydisInstructionTableGetNodeValue(ZydisInstructionTableNode node)
{
    return node.value;   
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the root node of the instruction table.
 *
 * @return  The root node of the instruction table.
 */
ZYDIS_INLINE ZydisInstructionTableNode ZydisInstructionTableGetRootNode()
{
    ZydisInstructionTableNode root = { ZYDIS_NODETYPE_FILTER_OPCODE, 0x00000000 };
    return root;
}

/**
 * @brief   Returns the child node of @c parent specified by @c index.
 *
 * @param   parent  The parent node.
 * @param   index   The index of the child node to retrieve.
 *                  
 * @return  The specified child node.
 */
ZYDIS_INLINE ZydisInstructionTableNode ZydisInstructionTableGetChildNode(
    ZydisInstructionTableNode parent, uint16_t index)
{
    ZydisInstructionTableNodeType nodeType = ZydisInstructionTableGetNodeType(parent);
    uint16_t tableIndex = ZydisInstructionTableGetNodeValue(parent);
    switch (nodeType)
    {
    case ZYDIS_NODETYPE_FILTER_OPCODE:
        ZYDIS_ASSERT(index < 256);
        return filterOpcode[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_VEX:
        ZYDIS_ASSERT(index <  16);
        return filterVEX[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_XOP:
        ZYDIS_ASSERT(index <   4);
        return filterXOP[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODE:
        ZYDIS_ASSERT(index <   3);
        return filterMode[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MANDATORYPREFIX:
        ZYDIS_ASSERT(index <   4);
        return filterMandatoryPrefix[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODRMMOD:
        ZYDIS_ASSERT(index <   2);
        return filterModrmMod[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODRMREG:
        ZYDIS_ASSERT(index <   8);
        return filterModrmReg[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODRMRM:
        ZYDIS_ASSERT(index <   8);
        return filterModrmRm[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_OPERANDSIZE:
        ZYDIS_ASSERT(index <   2);
        return filterOperandSize[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_ADDRESSSIZE:
        ZYDIS_ASSERT(index <   3);
        return filterAddressSize[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_REXW:
        ZYDIS_ASSERT(index <   2);
        return filterREXW[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_VEXL:
        ZYDIS_ASSERT(index <   2);
        return filterVEXL[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_EVEXL2:
        ZYDIS_ASSERT(index <   2);
        return filterEVEXL2[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_EVEXB:
        ZYDIS_ASSERT(index <   2);
        return filterEVEXB[tableIndex][index];
    default:
        ZYDIS_UNREACHABLE;
    }
    ZydisInstructionTableNode node = { ZYDIS_NODETYPE_INVALID, 0x00000000 }; 
    return node;
}

/**
 * @brief   Returns the instruction definition that is linked to the given @c node.
 *
 * @param   node    The instruction definition node.
 *                  
 * @return  Pointer to the instruction definition.
 */
ZYDIS_INLINE const ZydisInstructionDefinition* ZydisInstructionDefinitionByNode(
    ZydisInstructionTableNode node)
{
    ZYDIS_ASSERT(ZydisInstructionTableGetNodeType(node) == ZYDIS_NODETYPE_DEFINITION);
    return &instructionDefinitions[ZydisInstructionTableGetNodeValue(node)];    
}

/* ---------------------------------------------------------------------------------------------- */

ZYDIS_INLINE ZydisInstructionMnemonic ZydisInstructionDefinitionGetMnemonic(
    const ZydisInstructionDefinition* definition)
{
    return (definition->mnemonic >> 4) & 0xFFF;
}

ZYDIS_INLINE const ZydisInstructionOperands* ZydisInstructionDefinitionGetOperands(
    const ZydisInstructionDefinition* definition)
{
    return &instructionOperands[definition->operands];
}

ZYDIS_INLINE ZydisEvexBFunctionality ZydisInstructionDefinitionGetEvexBFunctionality(
    const ZydisInstructionDefinition* definition)
{
    return (definition->mnemonic >> 2) & 0x03;
}

ZYDIS_INLINE bool ZydisInstructionDefinitionHasEvexAAA(const ZydisInstructionDefinition* definition)
{
    return (definition->mnemonic >> 1) & 0x01;
}

ZYDIS_INLINE bool ZydisInstructionDefinitionHasEvexZ(const ZydisInstructionDefinition* definition)
{
    return definition->mnemonic & 0x01;
}

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Returns the defined operand-type of the specified operand-definition.
 *
 * @param   definition  The operand definition.
 *
 * @return  The defined operand-type of the specified operand-definition.
 */
ZYDIS_INLINE ZydisSemanticOperandType ZydisOperandDefinitionGetType(
    ZydisOperandDefinition definition)
{
    return ((definition >> 8) & 0xFF);   
}

/**
 * @brief   Returns the operand-encoding of the specified operand-definition.
 *
 * @param   definition  The operand definition.
 *
 * @return  The operand-encoding of the specified operand-definition.
 */
ZYDIS_INLINE ZydisOperandEncoding ZydisOperandDefinitionGetEncoding(
    ZydisOperandDefinition definition)
{
    return ((definition >> 2) & 0x3F);    
}

/**
 * @brief   Returns the access-mode of the specified operand-definition.
 *
 * @param   definition  The operand definition.
 *
 * @return  The access-mode of the specified operand-definition.
 */
ZYDIS_INLINE ZydisOperandAccess ZydisOperandDefinitionGetAccessMode(
    ZydisOperandDefinition definition)
{
    return ((definition >> 0) & 0x03);   
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INSTRUCTIONTABLE_H */
