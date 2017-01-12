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

#include <assert.h>
#include <Zydis/Internal/InstructionTable.h>

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Forward declarations                                                                           */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all opcode filters.
 *          
 *          Indexed by the numeric value of the opcode.
 */
extern const ZydisInstructionTableNode filterOpcode[][256];

/**
 * @brief   Contains all VEX-map filters.
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
 * @brief   Contains all XOP-map filters.
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
 * @brief   Contains all ModRM.mod filters.
 *          
 *          Index values:
 *          0 = [modrm_mod == !11] = memory
 *          1 = [modrm_mod ==  11] = register
 */
extern const ZydisInstructionTableNode filterModrmMod[][2];

/**
 * @brief   Contains all ModRM.reg filters.
 *          
 *          Indexed by the numeric value of the modrm_reg field.
 */
extern const ZydisInstructionTableNode filterModrmReg[][8];

/**
 * @brief   Contains all ModRM.rm filters.
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
 * @brief   Contains all REX/VEX/EVEX.w filters.
 *          
 *          Indexed by the numeric value of the REX/VEX/EVEX.w field.
 */
extern const ZydisInstructionTableNode filterREXW[][2];

/**
 * @brief   Contains all VEX.l filters.
 *          
 *          Indexed by the numeric value of the VEX/EVEX.l field.
 */
extern const ZydisInstructionTableNode filterVEXL[][2];

/**
 * @brief   Contains all EVEX.l' filters.
 *          
 *          Indexed by the numeric value of the EVEX.l' field.
 */
extern const ZydisInstructionTableNode filterEVEXL2[][2];

/**
 * @brief   Contains all EVEX.b filters.
 *          
 *          Indexed by the numeric value of the EVEX.b field.
 */
extern const ZydisInstructionTableNode filterEVEXB[][2];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all operand-definitions with 1 operands.
 */
extern const ZydisOperandDefinition operandDefinitions1[][1];

/**
 * @brief   Contains all operand-definitions with 2 operands.
 */
extern const ZydisOperandDefinition operandDefinitions2[][2];

/**
 * @brief   Contains all operand-definitions with 3 operands.
 */
extern const ZydisOperandDefinition operandDefinitions3[][3];

/**
 * @brief   Contains all operand-definitions with 4 operands.
 */
extern const ZydisOperandDefinition operandDefinitions4[][4];

/**
 * @brief   Contains all operand-definitions with 5 operands.
 */
extern const ZydisOperandDefinition operandDefinitions5[][5];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all instruction-definitions.
 */
extern const ZydisInstructionDefinition instructionDefinitions[];

/* ---------------------------------------------------------------------------------------------- */
/* Functions                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

const ZydisInstructionTableNode* ZydisInstructionTableGetRootNode()
{
    static const ZydisInstructionTableNode root = { ZYDIS_NODETYPE_FILTER_OPCODE, 0x00000000 };  
    return &root;
}

const ZydisInstructionTableNode* ZydisInstructionTableGetChildNode(
    const ZydisInstructionTableNode* parent, uint16_t index)
{
    switch (parent->type)
    {
    case ZYDIS_NODETYPE_FILTER_OPCODE:
        ZYDIS_ASSERT(index < 256);
        return &filterOpcode[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_VEX:
        ZYDIS_ASSERT(index <  16);
        return &filterVEX[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_XOP:
        ZYDIS_ASSERT(index <   4);
        return &filterXOP[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE:
        ZYDIS_ASSERT(index <   3);
        return &filterMode[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MANDATORYPREFIX:
        ZYDIS_ASSERT(index <   4);
        return &filterMandatoryPrefix[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRMMOD:
        ZYDIS_ASSERT(index <   2);
        return &filterModrmMod[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRMREG:
        ZYDIS_ASSERT(index <   8);
        return &filterModrmReg[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRMRM:
        ZYDIS_ASSERT(index <   8);
        return &filterModrmRm[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_OPERANDSIZE:
        ZYDIS_ASSERT(index <   2);
        return &filterOperandSize[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_ADDRESSSIZE:
        ZYDIS_ASSERT(index <   3);
        return &filterAddressSize[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_REXW:
        ZYDIS_ASSERT(index <   2);
        return &filterREXW[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_VEXL:
        ZYDIS_ASSERT(index <   2);
        return &filterVEXL[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_EVEXL2:
        ZYDIS_ASSERT(index <   2);
        return &filterEVEXL2[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_EVEXB:
        ZYDIS_ASSERT(index <   2);
        return &filterEVEXB[parent->value][index];
    default:
        ZYDIS_UNREACHABLE;
    }
    static const ZydisInstructionTableNode invalid = { ZYDIS_NODETYPE_INVALID, 0x00000000 }; 
    return &invalid;    
}

ZydisBool ZydisInstructionTableGetDefinition(const ZydisInstructionTableNode* node,
    const ZydisInstructionDefinition** definition, const ZydisOperandDefinition** operands, 
    uint8_t* operandCount)
{
    *definition = &instructionDefinitions[node->value];
    switch (node->type)
    {
    case ZYDIS_NODETYPE_DEFINITION_0OP:
        *operandCount = 0;
        break;
    case ZYDIS_NODETYPE_DEFINITION_1OP:
        *operandCount = 1;
        *operands = operandDefinitions1[(*definition)->operandsId];
        break;
    case ZYDIS_NODETYPE_DEFINITION_2OP:
        *operandCount = 2;
        *operands = operandDefinitions2[(*definition)->operandsId];
        break;
    case ZYDIS_NODETYPE_DEFINITION_3OP:
        *operandCount = 3;
        *operands = operandDefinitions3[(*definition)->operandsId];
        break;
    case ZYDIS_NODETYPE_DEFINITION_4OP:
        *operandCount = 4;
        *operands = operandDefinitions4[(*definition)->operandsId];
        break;
    case ZYDIS_NODETYPE_DEFINITION_5OP:
        *operandCount = 5;
        *operands = operandDefinitions5[(*definition)->operandsId];
        break;
    default:
        ZYDIS_UNREACHABLE;
        return ZYDIS_FALSE;
    }   
    return ZYDIS_TRUE;
}

/* ---------------------------------------------------------------------------------------------- */
/* Main instruction-table                                                                         */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_INVALID \
    { ZYDIS_NODETYPE_INVALID, 0x00000000 }
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

/* ---------------------------------------------------------------------------------------------- */
/* Operand definitions                                                                            */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_OPERAND_DEFINITION(type, encoding, access) \
    { type, encoding, access }

#include <Zydis/Internal/OperandDefinitions.inc>

#undef ZYDIS_OPERAND_DEFINITION

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definitions                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#include <Zydis/Internal/InstructionDefinitions.inc>

/* ============================================================================================== */
