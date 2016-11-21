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

#include <assert.h>
#include <string.h>
#include <Zydis/Internal/InstructionTable.h>

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Generated types & Macros                                                                       */
/* ---------------------------------------------------------------------------------------------- */

// TODO: Auto generate these structs and macros

typedef struct ZydisInternalInstructionTableNode_
{
    ZydisInstructionTableNodeType type;
    ZydisInstructionTableNodeValue value;
} ZydisInternalInstructionTableNode;

#define ZYDIS_MAKE_INSTRUCTIONTABLENODE(type, value) \
    { type, value }
#define ZYDIS_GET_INSTRUCTIONTABLENODE_TYPE(node) \
    node.type
#define ZYDIS_GET_INSTRUCTIONTABLENODE_VALUE(node) \
    node.value

//typedef struct ZydisInternalOperandDefinition_
//{
//    unsigned int type : 8;
//    unsigned int encoding : 8;
//    unsigned int access : 2;
//} ZydisInternalOperandDefinition;
//
//#define ZYDIS_MAKE_OPERANDDEFINITION(type, encoding, access) \
//    { type, encoding, access }
//#define ZYDIS_GET_OPERANDDEFINITION_TYPE(def) \
//    (ZydisSemanticOperandType)def.type
//#define ZYDIS_GET_OPERANDDEFINITION_ENCODING(def) \
//    (ZydisOperandEncoding)def.encoding
//#define ZYDIS_GET_OPERANDDEFINITION_ACCESS(def) \
//    (ZydisOperandAccess)def.access

typedef uint8_t ZydisInternalOperandDefinition[2];

#define ZYDIS_MAKE_OPERANDDEFINITION(type, encoding, access) \
    { type, ((encoding & 0x3F) << 2) | (access & 0x03) }
#define ZYDIS_GET_OPERANDDEFINITION_TYPE(def) \
    def[0]
#define ZYDIS_GET_OPERANDDEFINITION_ENCODING(def) \
    ((def[1] >> 2) & 0x3F)
#define ZYDIS_GET_OPERANDDEFINITION_ACCESS(def) \
    (def[1] & 0x03)

typedef struct ZydisInternalInstructionDefinition_
{
    unsigned int mnemonic : 11;
    unsigned int operandRef : 9;
    unsigned int evexBFunctionality : 2;
    unsigned int hasEvexAAA : 1;
    unsigned int hasEvexZ : 1;
} ZydisInternalInstructionDefinition;

#define ZYDIS_MAKE_INSTRUCTIONDEFINITION(mnemonic, operandRef, evexBFunctionality, hasEvexAAA, hasEvexZ) \
    { mnemonic, operandRef, evexBFunctionality, hasEvexAAA, hasEvexZ }
#define ZYDIS_GET_INSTRUCTIONDEFINITION_MNEMONIC(def) \
    (ZydisInstructionMnemonic)def.mnemonic
#define ZYDIS_GET_INSTRUCTIONDEFINITION_OPERANDREF(def) \
    def.operandRef
#define ZYDIS_GET_INSTRUCTIONDEFINITION_EVEXBFUNCTIONALITY(def) \
    (ZydisEvexBFunctionality)def.evexBFunctionality
#define ZYDIS_GET_INSTRUCTIONDEFINITION_HASEVEXAAA(def) \
    def.hasEvexAAA
#define ZYDIS_GET_INSTRUCTIONDEFINITION_HASEVEXZ(def) \
    def.hasEvexZ

/* ---------------------------------------------------------------------------------------------- */
/* Forward declarations                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all opcode filters.
 *          
 *          Indexed by the numeric value of the opcode.
 */
extern const ZydisInternalInstructionTableNode filterOpcode[][256];

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
extern const ZydisInternalInstructionTableNode filterVEX[][16];

/**
 * @brief   Contains all xop-map filters.
 *          
 *          Index values:
 *          0 = POP instruction (default encoding)
 *          1 = xop8
 *          2 = xop9
 *          3 = xopA
 */
extern const ZydisInternalInstructionTableNode filterXOP[][4];

/**
 * @brief   Contains all instruction-mode filters.
 *          
 *          Index values:
 *          0 = 64 bit mode required
 *          1 = 64 bit mode excluded
 */
extern const ZydisInternalInstructionTableNode filterMode[][2];

/**
 * @brief   Contains all mandatory-prefix switch tables.
 *          
 *          Index values:
 *          0 = none
 *          1 = 66  
 *          2 = F3  
 *          3 = F2
 */
extern const ZydisInternalInstructionTableNode filterMandatoryPrefix[][4];

/**
 * @brief   Contains all modrm.mod filters.
 *          
 *          Index values:
 *          0 = [modrm_mod == !11] = memory
 *          1 = [modrm_mod ==  11] = register
 */
extern const ZydisInternalInstructionTableNode filterModrmMod[][2];

/**
 * @brief   Contains all modrm.reg filters.
 *          
 *          Indexed by the numeric value of the modrm_reg field.
 */
extern const ZydisInternalInstructionTableNode filterModrmReg[][8];

/**
 * @brief   Contains all modrm.rm filters.
 *          
 *          Indexed by the numeric value of the modrm_rm field.
 */
extern const ZydisInternalInstructionTableNode filterModrmRm[][8];

/**
 * @brief   Contains all operand-size filters.
 *          
 *          Index values:
 *          0 = 16bit = 0x66 prefix in 32 bit mode
 *          1 = 32bit = 0x66 prefix in 16 bit mode  
 */
extern const ZydisInternalInstructionTableNode filterOperandSize[][2];

/**
 * @brief   Contains all address-size filters.
 *          
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const ZydisInternalInstructionTableNode filterAddressSize[][3];

/**
 * @brief   Contains all rex/vex/evex.w filters.
 *          
 *          Indexed by the numeric value of the rex/vex/evex.w field.
 */
extern const ZydisInternalInstructionTableNode filterREXW[][2];

/**
 * @brief   Contains all vex.l filters.
 *          
 *          Indexed by the numeric value of the vex/evex.l field.
 */
extern const ZydisInternalInstructionTableNode filterVEXL[][2];

/**
 * @brief   Contains all evex.l' filters.
 *          
 *          Indexed by the numeric value of the evex.l' field.
 */
extern const ZydisInternalInstructionTableNode filterEVEXL2[][2];

/**
 * @brief   Contains all evex.b filters.
 *          
 *          Indexed by the numeric value of the evex.b field.
 */
extern const ZydisInternalInstructionTableNode filterEVEXB[][2];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all operand-definitions with 1 operand.
 */
extern const ZydisInternalOperandDefinition operandDefinitions1[][1];

/**
 * @brief   Contains all operand-definitions with 2 operands.
 */
extern const ZydisInternalOperandDefinition operandDefinitions2[][2];

/**
 * @brief   Contains all operand-definitions with 3 operands.
 */
extern const ZydisInternalOperandDefinition operandDefinitions3[][3];

/**
 * @brief   Contains all operand-definitions with 4 operands.
 */
extern const ZydisInternalOperandDefinition operandDefinitions4[][4];

/**
 * @brief   Contains all operand-definitions with 5 operands.
 */
extern const ZydisInternalOperandDefinition operandDefinitions5[][5];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all instruction-definitions.
 */
extern const ZydisInternalInstructionDefinition instructionDefinitions[];

/* ---------------------------------------------------------------------------------------------- */
/* Functions                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

ZydisInstructionTableNodeType ZydisInstructionTableGetNodeType(
    const ZydisInstructionTableNode node)
{
    return (ZydisInstructionTableNodeType)
        ZYDIS_GET_INSTRUCTIONTABLENODE_TYPE((*(ZydisInternalInstructionTableNode*)node));    
}

ZydisInstructionTableNodeValue ZydisInstructionTableGetNodeValue(
    const ZydisInstructionTableNode* node)
{
    return (ZydisInstructionTableNodeValue)
        ZYDIS_GET_INSTRUCTIONTABLENODE_VALUE((*(ZydisInternalInstructionTableNode*)node));     
}

/* ---------------------------------------------------------------------------------------------- */

ZydisInstructionTableNode ZydisInstructionTableGetRootNode()
{
    static const ZydisInternalInstructionTableNode root = 
        ZYDIS_MAKE_INSTRUCTIONTABLENODE(ZYDIS_NODETYPE_FILTER_OPCODE, 0x00000000);  
    return (ZydisInstructionTableNode)&root;
}

ZydisInstructionTableNode ZydisInstructionTableGetChildNode(
    const ZydisInstructionTableNode parent, uint16_t index)
{
    ZydisInstructionTableNodeType nodeType = ZydisInstructionTableGetNodeType(parent);
    uint16_t tableIndex = ZydisInstructionTableGetNodeValue(parent);
    switch (nodeType)
    {
    case ZYDIS_NODETYPE_FILTER_OPCODE:
        ZYDIS_ASSERT(index < 256);
        return (ZydisInstructionTableNode*)&filterOpcode[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_VEX:
        ZYDIS_ASSERT(index <  16);
        return (ZydisInstructionTableNode*)&filterVEX[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_XOP:
        ZYDIS_ASSERT(index <   4);
        return (ZydisInstructionTableNode*)&filterXOP[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODE:
        ZYDIS_ASSERT(index <   3);
        return (ZydisInstructionTableNode*)&filterMode[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MANDATORYPREFIX:
        ZYDIS_ASSERT(index <   4);
        return (ZydisInstructionTableNode*)&filterMandatoryPrefix[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODRMMOD:
        ZYDIS_ASSERT(index <   2);
        return (ZydisInstructionTableNode*)&filterModrmMod[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODRMREG:
        ZYDIS_ASSERT(index <   8);
        return (ZydisInstructionTableNode*)&filterModrmReg[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_MODRMRM:
        ZYDIS_ASSERT(index <   8);
        return (ZydisInstructionTableNode*)&filterModrmRm[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_OPERANDSIZE:
        ZYDIS_ASSERT(index <   2);
        return (ZydisInstructionTableNode*)&filterOperandSize[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_ADDRESSSIZE:
        ZYDIS_ASSERT(index <   3);
        return (ZydisInstructionTableNode*)&filterAddressSize[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_REXW:
        ZYDIS_ASSERT(index <   2);
        return (ZydisInstructionTableNode*)&filterREXW[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_VEXL:
        ZYDIS_ASSERT(index <   2);
        return (ZydisInstructionTableNode*)&filterVEXL[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_EVEXL2:
        ZYDIS_ASSERT(index <   2);
        return (ZydisInstructionTableNode*)&filterEVEXL2[tableIndex][index];
    case ZYDIS_NODETYPE_FILTER_EVEXB:
        ZYDIS_ASSERT(index <   2);
        return (ZydisInstructionTableNode*)&filterEVEXB[tableIndex][index];
    default:
        ZYDIS_UNREACHABLE;
    }
    static const ZydisInternalInstructionTableNode invalid = 
        ZYDIS_MAKE_INSTRUCTIONTABLENODE(ZYDIS_NODETYPE_INVALID, 0x00000000); 
    return (ZydisInstructionTableNode)&invalid;    
}

ZydisInstructionDefinition ZydisInstructionDefinitionByNode(
    const ZydisInstructionTableNode node)
{
    ZydisInstructionDefinition result;
    memset(&result, 0, sizeof(result));

    const ZydisInternalInstructionDefinition* definition = 
        &instructionDefinitions[ZydisInstructionTableGetNodeValue(node)];
    result.mnemonic = ZYDIS_GET_INSTRUCTIONDEFINITION_MNEMONIC((*definition));
    result.evexBFunctionality = ZYDIS_GET_INSTRUCTIONDEFINITION_EVEXBFUNCTIONALITY((*definition));
    result.hasEvexAAA = ZYDIS_GET_INSTRUCTIONDEFINITION_HASEVEXAAA((*definition));
    result.hasEvexZ = ZYDIS_GET_INSTRUCTIONDEFINITION_HASEVEXZ((*definition));

    const ZydisInternalOperandDefinition* operand = NULL;
    switch (ZydisInstructionTableGetNodeType(node))
    {
    case ZYDIS_NODETYPE_DEFINITION_0OP:
        result.operandCount = 0;
        break;
    case ZYDIS_NODETYPE_DEFINITION_1OP:
        result.operandCount = 1;
        operand = operandDefinitions1[ZYDIS_GET_INSTRUCTIONDEFINITION_OPERANDREF((*definition))];
        break;
    case ZYDIS_NODETYPE_DEFINITION_2OP:
        result.operandCount = 2;
        operand = operandDefinitions2[ZYDIS_GET_INSTRUCTIONDEFINITION_OPERANDREF((*definition))];
        break;
    case ZYDIS_NODETYPE_DEFINITION_3OP:
        result.operandCount = 3;
        operand = operandDefinitions3[ZYDIS_GET_INSTRUCTIONDEFINITION_OPERANDREF((*definition))];
        break;
    case ZYDIS_NODETYPE_DEFINITION_4OP:
        result.operandCount = 4;
        operand = operandDefinitions4[ZYDIS_GET_INSTRUCTIONDEFINITION_OPERANDREF((*definition))];
        break;
    case ZYDIS_NODETYPE_DEFINITION_5OP:
        result.operandCount = 5;
        operand = operandDefinitions5[ZYDIS_GET_INSTRUCTIONDEFINITION_OPERANDREF((*definition))];
        break;
    default:
        ZYDIS_UNREACHABLE;
    } 
    if (result.operandCount > 0)
    {
        for (int i = 0; i < result.operandCount; ++i)
        {
            result.operands[i].type = ZYDIS_GET_OPERANDDEFINITION_TYPE((*operand));
            result.operands[i].encoding = ZYDIS_GET_OPERANDDEFINITION_ENCODING((*operand));
            result.operands[i].access = ZYDIS_GET_OPERANDDEFINITION_ACCESS((*operand));
            ++operand;
        } 
    }
    return result;
}

/* ---------------------------------------------------------------------------------------------- */
/* Main instruction-table                                                                         */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_INVALID \
    ZYDIS_MAKE_INSTRUCTIONTABLENODE(ZYDIS_NODETYPE_INVALID, 0x00000000)
#define ZYDIS_FILTER(type, id) \
    { type, id }
#define ZYDIS_DEFINITION_0OP(id) \
    { ZYDIS_NODETYPE_DEFINITION_0OP, id }
#define ZYDIS_DEFINITION_1OP(id) \
    { ZYDIS_NODETYPE_DEFINITION_1OP, id }
#define ZYDIS_DEFINITION_2OP(id) \
    { ZYDIS_NODETYPE_DEFINITION_2OP, id }
#define ZYDIS_DEFINITION_3OP(id) \
    { ZYDIS_NODETYPE_DEFINITION_3OP, id }
#define ZYDIS_DEFINITION_4OP(id) \
    { ZYDIS_NODETYPE_DEFINITION_4OP, id }
#define ZYDIS_DEFINITION_5OP(id) \
    { ZYDIS_NODETYPE_DEFINITION_5OP, id }

#include <Zydis/Internal/InstructionFilters.inc>

#undef ZYDIS_INVALID
#undef ZYDIS_FILTER
#undef ZYDIS_DEFINITION_0OP
#undef ZYDIS_DEFINITION_1OP
#undef ZYDIS_DEFINITION_2OP
#undef ZYDIS_DEFINITION_3OP
#undef ZYDIS_DEFINITION_4OP
#undef ZYDIS_DEFINITION_5OP

#undef ZYDIS_MAKE_INSTRUCTIONTABLENODE

/* ---------------------------------------------------------------------------------------------- */
/* Operand definitions                                                                            */
/* ---------------------------------------------------------------------------------------------- */

#include <Zydis/Internal/OperandDefinitions.inc>

#undef ZYDIS_MAKE_OPERANDDEFINITION

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definitions                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#include <Zydis/Internal/InstructionDefinitions.inc>

#undef ZYDIS_MAKE_AVX512INFO
#undef ZYDIS_MAKE_INSTRUCTIONDEFINITION

/* ============================================================================================== */
