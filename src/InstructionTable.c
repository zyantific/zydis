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
 * @brief   Contains all XOP-map filters.
 *          
 *          Index values:
 *          0 = POP instruction (default encoding)
 *          1 = xop8
 *          2 = xop9
 *          3 = xopA
 */
extern const ZydisInstructionTreeNode filtersXOP[][4];

/**
 * @brief   Contains all VEX-map filters.
 *          
 *          Index values:
 *          00 = LES or LDS instruction (default encoding)
 *          01 = VEX MAP0
 *          02 = 0F  
 *          03 = 0F38  
 *          04 = 0F3A  
 *          05 = 66  
 *          06 = 66_0F  
 *          07 = 66_0F38  
 *          08 = 66_0F3A  
 *          09 = F3  
 *          0A = F3_0F
 *          0B = F3_0F38
 *          0C = F3_0F3A
 *          0D = F2
 *          0E = F2_0F
 *          0F = F2_0F38
 *          10 = F2_0F3A
 */
extern const ZydisInstructionTreeNode filtersVEX[][17];

/**
 * @brief   Contains all EVEX/MVEX-map filters.
 *          
 *          Index values:
 *          00 = BOUND instruction (default encoding)
 *          01 = EVEX MAP0
 *          02 = EVEX 0F  
 *          03 = EVEX 0F38  
 *          04 = EVEX 0F3A  
 *          05 = EVEX 66  
 *          06 = EVEX 66_0F  
 *          07 = EVEX 66_0F38  
 *          08 = EVEX 66_0F3A  
 *          09 = EVEX F3  
 *          0A = EVEX F3_0F
 *          0B = EVEX F3_0F38
 *          0C = EVEX F3_0F3A
 *          0D = EVEX EVEX F2
 *          0E = EVEX F2_0F
 *          0F = EVEX 
 *          10 = EVEX F2_0F3A
 *          11 = MVEX MAP0
 *          12 = MVEX 0F  
 *          13 = MVEX 0F38  
 *          14 = MVEX 0F3A  
 *          15 = MVEX 66  
 *          16 = MVEX 66_0F  
 *          17 = MVEX 66_0F38  
 *          18 = MVEX 66_0F3A  
 *          19 = MVEX F3  
 *          1A = MVEX F3_0F
 *          1B = MVEX F3_0F38
 *          1C = MVEX F3_0F3A
 *          1D = MVEX EVEX F2
 *          1E = MVEX F2_0F
 *          1F = MVEX F2_0F38
 *          20 = MVEX F2_0F3A
 */
extern const ZydisInstructionTreeNode filtersEMVEX[][33];

/**
 * @brief   Contains all opcode filters.
 *          
 *          Indexed by the numeric value of the opcode.
 */
extern const ZydisInstructionTreeNode filtersOpcode[][256];

/**
 * @brief   Contains all instruction-mode filters.
 *          
 *          Index values:
 *          0 = 16 bit mode
 *          1 = 32 bit mode
 *          2 = 64 bit mode
 */
extern const ZydisInstructionTreeNode filtersMode[][3];

/**
 * @brief   Contains all compacted instruction-mode filters.
 *          
 *          Index values:
 *          0 = 64 bit mode
 *          1 = not 64 bit mode
 */
extern const ZydisInstructionTreeNode filtersModeCompact[][2];

/**
 * @brief   Contains all ModRM.mod filters.
 *          
 *          Indexed by the ordinal value of the ModRM.mod field.
 */
extern const ZydisInstructionTreeNode filtersModrmMod[][4];

/**
 * @brief   Contains all compacted ModRM.mod filters.
 *          
 *          Index values:
 *          0 = [ModRM.mod ==  11] = register
 *          1 = [ModRM.mod == !11] = memory
 */
extern const ZydisInstructionTreeNode filtersModrmModCompact[][2];

/**
 * @brief   Contains all ModRM.reg filters.
 *          
 *          Indexed by the numeric value of the ModRM.reg field.
 */
extern const ZydisInstructionTreeNode filtersModrmReg[][8];

/**
 * @brief   Contains all ModRM.rm filters.
 *          
 *          Indexed by the numeric value of the ModRM.rm field.
 */
extern const ZydisInstructionTreeNode filtersModrmRm[][8];

/**
 * @brief   Contains all mandatory-prefix switch tables.
 *          
 *          Index values:
 *          0 = ignored (prefixes are not interpreted as mandatory-prefix)
 *          1 = none
 *          2 = 66  
 *          3 = F3  
 *          4 = F2
 */
extern const ZydisInstructionTreeNode filtersMandatoryPrefix[][5];

/**
 * @brief   Contains all operand-size filters.
 *          
 *          Index values:
 *          0 = 16 bit
 *          1 = 32 bit
 *          2 = 64 bit 
 */
extern const ZydisInstructionTreeNode filtersOperandSize[][3];

/**
 * @brief   Contains all address-size filters.
 *          
 *          Index values:
 *          0 = 16 bit
 *          1 = 32 bit 
 *          2 = 64 bit
 */
extern const ZydisInstructionTreeNode filtersAddressSize[][3];

/**
 * @brief   Contains all vector-length filters.
 *          
 *          Index values:
 *          0 = 128 bit
 *          1 = 256 bit 
 *          2 = 512 bit
 */
extern const ZydisInstructionTreeNode filtersVectorLength[][3];

/**
 * @brief   Contains all REX/VEX/EVEX.w filters.
 *          
 *          Indexed by the numeric value of the REX/VEX/EVEX.w field.
 */
extern const ZydisInstructionTreeNode filtersREXW[][2];

/**
 * @brief   Contains all REX/VEX/EVEX.B filters.
 *          
 *          Indexed by the numeric value of the REX/VEX/EVEX.B field.
 */
extern const ZydisInstructionTreeNode filtersREXB[][2];

/**
 * @brief   Contains all EVEX.b filters.
 *          
 *          Indexed by the numeric value of the EVEX.b field.
 */
extern const ZydisInstructionTreeNode filtersEVEXB[][2];

/**
 * @brief   Contains all EVEX.z filters.
 *          
 *          Indexed by the numeric value of the EVEX.z field.
 */
extern const ZydisInstructionTreeNode filtersEVEXZ[][2];

/**
 * @brief   Contains all MVEX.E filters.
 *          
 *          Indexed by the numeric value of the MVEX.E field.
 */
extern const ZydisInstructionTreeNode filtersMVEXE[][2];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all operand-definitions.
 */
extern const ZydisOperandDefinition operandDefinitions[];

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Contains all instruction-definitions with @c DEFAULT encoding.
 */
extern const ZydisInstructionDefinitionDEFAULT instructionDefinitionsDEFAULT[];

/**
 * @brief   Contains all instruction-definitions with @c 3DNOW encoding.
 */
extern const ZydisInstructionDefinition3DNOW instructionDefinitions3DNOW[];

/**
 * @brief   Contains all instruction-definitions with @c XOP encoding.
 */
extern const ZydisInstructionDefinitionXOP instructionDefinitionsXOP[];

/**
 * @brief   Contains all instruction-definitions with @c VEX encoding.
 */
extern const ZydisInstructionDefinitionVEX instructionDefinitionsVEX[];

/**
 * @brief   Contains all instruction-definitions with @c EVEX encoding.
 */
extern const ZydisInstructionDefinitionEVEX instructionDefinitionsEVEX[];

/**
 * @brief   Contains all instruction-definitions with @c MVEX encoding.
 */
extern const ZydisInstructionDefinitionMVEX instructionDefinitionsMVEX[];

/* ---------------------------------------------------------------------------------------------- */
/* Physical instruction encodings                                                                 */
/* ---------------------------------------------------------------------------------------------- */

#include <Zydis/Internal/InstructionClassMap.inc>

/* ---------------------------------------------------------------------------------------------- */
/* Instruction tree                                                                               */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_INVALID \
    { ZYDIS_NODETYPE_INVALID, 0x00000000 }
#define ZYDIS_FILTER(type, id) \
    { type, id }
#define ZYDIS_DEFINITION(encoding, instrclass, id) \
    { ZYDIS_NODETYPE_DEFINITION_MASK | instrclass, (encoding << 13) | id }

#include <Zydis/Internal/InstructionFilters.inc>

#undef ZYDIS_INVALID
#undef ZYDIS_FILTER
#undef ZYDIS_DEFINITION

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definitions                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#include <Zydis/Internal/InstructionDefinitions.inc>

/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------- */
/* Operand definitions                                                                            */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_OPERAND_DEFINITION(type, encoding, access) \
    { type, encoding, access }

#include <Zydis/Internal/OperandDefinitions.inc>

#undef ZYDIS_OPERAND_DEFINITION

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Instruction tree                                                                               */
/* ---------------------------------------------------------------------------------------------- */

const ZydisInstructionTreeNode* ZydisInstructionTreeGetRootNode()
{
    static const ZydisInstructionTreeNode root = { ZYDIS_NODETYPE_FILTER_OPCODE, 0x00000000 };  
    return &root;
}

const ZydisInstructionTreeNode* ZydisInstructionTreeGetChildNode(
    const ZydisInstructionTreeNode* parent, uint16_t index)
{
    switch (parent->type)
    {
    case ZYDIS_NODETYPE_FILTER_XOP:
        ZYDIS_ASSERT(index <   4);
        return &filtersXOP[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_VEX:
        ZYDIS_ASSERT(index <  17);
        return &filtersVEX[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_EMVEX:
        ZYDIS_ASSERT(index <  33);
        return &filtersEMVEX[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_OPCODE:
        ZYDIS_ASSERT(index < 256);
        return &filtersOpcode[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE:
        ZYDIS_ASSERT(index <   4);
        return &filtersMode[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE_COMPACT:
        ZYDIS_ASSERT(index <   3);
        return &filtersModeCompact[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRM_MOD:
        ZYDIS_ASSERT(index <   4);
        return &filtersModrmMod[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRM_MOD_COMPACT:
        ZYDIS_ASSERT(index <   2);
        return &filtersModrmModCompact[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRM_REG:
        ZYDIS_ASSERT(index <   8);
        return &filtersModrmReg[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODRM_RM:
        ZYDIS_ASSERT(index <   8);
        return &filtersModrmRm[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MANDATORY_PREFIX:
        ZYDIS_ASSERT(index <   5);
        return &filtersMandatoryPrefix[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_OPERAND_SIZE:
        ZYDIS_ASSERT(index <   3);
        return &filtersOperandSize[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_ADDRESS_SIZE:
        ZYDIS_ASSERT(index <   3);
        return &filtersAddressSize[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_VECTOR_LENGTH:
        ZYDIS_ASSERT(index <   3);
        return &filtersVectorLength[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_REX_W:
        ZYDIS_ASSERT(index <   2);
        return &filtersREXW[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_REX_B:
        ZYDIS_ASSERT(index <   2);
        return &filtersREXB[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_EVEX_B:
        ZYDIS_ASSERT(index <   2);
        return &filtersEVEXB[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_EVEX_Z:
        ZYDIS_ASSERT(index <   2);
        return &filtersEVEXZ[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MVEX_E:
        ZYDIS_ASSERT(index <   2);
        return &filtersMVEXE[parent->value][index];
    default:
        ZYDIS_UNREACHABLE;
    }
    static const ZydisInstructionTreeNode invalid = { ZYDIS_NODETYPE_INVALID, 0x00000000 }; 
    return &invalid;    
}

/* ---------------------------------------------------------------------------------------------- */
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

void ZydisGetInstructionDefinition(const ZydisInstructionTreeNode* node,
    const ZydisInstructionDefinition** definition)
{
    ZYDIS_ASSERT(node->type & ZYDIS_NODETYPE_DEFINITION_MASK);
    switch ((node->value >> 13) & 0x07)
    {
    case ZYDIS_INSTRUCTION_ENCODING_DEFAULT:
        *definition = 
            (ZydisInstructionDefinition*)&instructionDefinitionsDEFAULT[node->value & 0x1FFF];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        *definition = 
            (ZydisInstructionDefinition*)&instructionDefinitions3DNOW[node->value & 0x1FFF];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        *definition = 
            (ZydisInstructionDefinition*)&instructionDefinitionsXOP[node->value & 0x1FFF];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        *definition = 
            (ZydisInstructionDefinition*)&instructionDefinitionsVEX[node->value & 0x1FFF];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        *definition = 
            (ZydisInstructionDefinition*)&instructionDefinitionsEVEX[node->value & 0x1FFF];
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        *definition = 
            (ZydisInstructionDefinition*)&instructionDefinitionsMVEX[node->value & 0x1FFF];
        break;
    default:
        ZYDIS_UNREACHABLE;
    }
}

void ZydisGetOptionalInstructionParts(const ZydisInstructionTreeNode* node, 
    const ZydisInstructionParts** info)
{
    ZYDIS_ASSERT(node->type & ZYDIS_NODETYPE_DEFINITION_MASK);
    uint8_t class = (node->type) & 0x7F;
    ZYDIS_ASSERT(class < ZYDIS_ARRAY_SIZE(instructionClassMap));
    *info = &instructionClassMap[class];
}

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

uint8_t ZydisGetOperandDefinitions(const ZydisInstructionDefinition* definition, 
    const ZydisOperandDefinition** operands)
{
    if (definition->operandCount == 0)
    {
        *operands = NULL;
        return 0;
    }
    ZYDIS_ASSERT(definition->operandReference != 0xFFFF);
    *operands = &operandDefinitions[definition->operandReference];
    return definition->operandCount;
}

/* ---------------------------------------------------------------------------------------------- */
/* Element info                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

void ZydisGetElementInfo(ZydisInternalElementType element, ZydisElementType* type,
    ZydisElementSize* size)
{
    static const struct
    {
        ZydisElementType type;
        ZydisElementSize size;
    } lookup[21] =
    {
        { ZYDIS_ELEMENT_TYPE_INVALID  ,   0 },
        { ZYDIS_ELEMENT_TYPE_INVALID  ,   0 },
        { ZYDIS_ELEMENT_TYPE_STRUCT   ,   0 },
        { ZYDIS_ELEMENT_TYPE_INT      ,   0 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,   0 },
        { ZYDIS_ELEMENT_TYPE_INT      ,   1 },
        { ZYDIS_ELEMENT_TYPE_INT      ,   8 },
        { ZYDIS_ELEMENT_TYPE_INT      ,  16 },
        { ZYDIS_ELEMENT_TYPE_INT      ,  32 },
        { ZYDIS_ELEMENT_TYPE_INT      ,  64 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,   8 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,  16 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,  32 },
        { ZYDIS_ELEMENT_TYPE_UINT     ,  64 },
        { ZYDIS_ELEMENT_TYPE_UINT     , 128 },
        { ZYDIS_ELEMENT_TYPE_UINT     , 256 },
        { ZYDIS_ELEMENT_TYPE_FLOAT16  ,  16 },
        { ZYDIS_ELEMENT_TYPE_FLOAT32  ,  32 },
        { ZYDIS_ELEMENT_TYPE_FLOAT64  ,  64 },
        { ZYDIS_ELEMENT_TYPE_FLOAT80  ,  80 },
        { ZYDIS_ELEMENT_TYPE_LONGBCD  ,  80 }
    };

    ZYDIS_ASSERT((element >= 0) && (element < ZYDIS_ARRAY_SIZE(lookup)));

    *type = lookup[element].type;
    *size = lookup[element].size;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
