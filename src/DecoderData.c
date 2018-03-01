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

#include <Zydis/Internal/DecoderData.h>

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
 *          00 = POP instruction (default encoding)
 *          01 = XOP8
 *          02 = XOP9
 *          03 = XOPA
 *          04 = 66_XOP8
 *          05 = 66_XOP9
 *          06 = 66_XOPA
 *          07 = F3_XOP8
 *          08 = F3_XOP9
 *          09 = F3_XOPA
 *          0A = F2_XOP8
 *          0B = F2_XOP9
 *          0C = F2_XOPA
 */
extern const ZydisDecoderTreeNode filtersXOP[][13];

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
extern const ZydisDecoderTreeNode filtersVEX[][17];

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
extern const ZydisDecoderTreeNode filtersEMVEX[][33];

/**
 * @brief   Contains all opcode filters.
 *
 *          Indexed by the numeric value of the opcode.
 */
extern const ZydisDecoderTreeNode filtersOpcode[][256];

/**
 * @brief   Contains all instruction-mode filters.
 *
 *          Index values:
 *          0 = 16 bit mode
 *          1 = 32 bit mode
 *          2 = 64 bit mode
 */
extern const ZydisDecoderTreeNode filtersMode[][3];

/**
 * @brief   Contains all compacted instruction-mode filters.
 *
 *          Index values:
 *          0 = 64 bit mode
 *          1 = not 64 bit mode
 */
extern const ZydisDecoderTreeNode filtersModeCompact[][2];

/**
 * @brief   Contains all ModRM.mod filters.
 *
 *          Indexed by the ordinal value of the ModRM.mod field.
 */
extern const ZydisDecoderTreeNode filtersModrmMod[][4];

/**
 * @brief   Contains all compacted ModRM.mod filters.
 *
 *          Index values:
 *          0 = [ModRM.mod ==  11] = register
 *          1 = [ModRM.mod == !11] = memory
 */
extern const ZydisDecoderTreeNode filtersModrmModCompact[][2];

/**
 * @brief   Contains all ModRM.reg filters.
 *
 *          Indexed by the numeric value of the ModRM.reg field.
 */
extern const ZydisDecoderTreeNode filtersModrmReg[][8];

/**
 * @brief   Contains all ModRM.rm filters.
 *
 *          Indexed by the numeric value of the ModRM.rm field.
 */
extern const ZydisDecoderTreeNode filtersModrmRm[][8];

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
extern const ZydisDecoderTreeNode filtersMandatoryPrefix[][5];

/**
 * @brief   Contains all operand-size filters.
 *
 *          Index values:
 *          0 = 16 bit
 *          1 = 32 bit
 *          2 = 64 bit
 */
extern const ZydisDecoderTreeNode filtersOperandSize[][3];

/**
 * @brief   Contains all address-size filters.
 *
 *          Index values:
 *          0 = 16 bit
 *          1 = 32 bit
 *          2 = 64 bit
 */
extern const ZydisDecoderTreeNode filtersAddressSize[][3];

/**
 * @brief   Contains all vector-length filters.
 *
 *          Index values:
 *          0 = 128 bit
 *          1 = 256 bit
 *          2 = 512 bit
 */
extern const ZydisDecoderTreeNode filtersVectorLength[][3];

/**
 * @brief   Contains all REX/VEX/EVEX.w filters.
 *
 *          Indexed by the numeric value of the REX/VEX/EVEX.w field.
 */
extern const ZydisDecoderTreeNode filtersREXW[][2];

/**
 * @brief   Contains all REX/VEX/EVEX.B filters.
 *
 *          Indexed by the numeric value of the REX/VEX/EVEX.B field.
 */
extern const ZydisDecoderTreeNode filtersREXB[][2];

#ifndef ZYDIS_DISABLE_EVEX
/**
 * @brief   Contains all EVEX.b filters.
 *
 *          Indexed by the numeric value of the EVEX.b field.
 */
extern const ZydisDecoderTreeNode filtersEVEXB[][2];
#endif

#ifndef ZYDIS_DISABLE_MVEX
/**
 * @brief   Contains all MVEX.E filters.
 *
 *          Indexed by the numeric value of the MVEX.E field.
 */
extern const ZydisDecoderTreeNode filtersMVEXE[][2];
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Physical instruction encodings                                                                 */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/InstructionEncodings.inc>

/* ---------------------------------------------------------------------------------------------- */
/* Decoder tree                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

#define ZYDIS_INVALID \
    { ZYDIS_NODETYPE_INVALID, 0x00000000 }
#define ZYDIS_FILTER(type, id) \
    { type, id }
#define ZYDIS_DEFINITION(encoding_id, id) \
    { ZYDIS_NODETYPE_DEFINITION_MASK | encoding_id, id }

#include <Generated/DecoderTables.inc>

#undef ZYDIS_INVALID
#undef ZYDIS_FILTER
#undef ZYDIS_DEFINITION

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Decoder tree                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

const ZydisDecoderTreeNode* ZydisDecoderTreeGetRootNode(void)
{
    static const ZydisDecoderTreeNode root = { ZYDIS_NODETYPE_FILTER_OPCODE, 0x0000 };
    return &root;
}

const ZydisDecoderTreeNode* ZydisDecoderTreeGetChildNode(const ZydisDecoderTreeNode* parent,
    ZydisU16 index)
{
    switch (parent->type)
    {
    case ZYDIS_NODETYPE_FILTER_XOP:
        ZYDIS_ASSERT(index <  13);
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
#ifndef ZYDIS_DISABLE_EVEX
    case ZYDIS_NODETYPE_FILTER_EVEX_B:
        ZYDIS_ASSERT(index <   2);
        return &filtersEVEXB[parent->value][index];
#endif
#ifndef ZYDIS_DISABLE_MVEX
    case ZYDIS_NODETYPE_FILTER_MVEX_E:
        ZYDIS_ASSERT(index <   2);
        return &filtersMVEXE[parent->value][index];
#endif
    case ZYDIS_NODETYPE_FILTER_MODE_AMD:
        ZYDIS_ASSERT(index <   2);
        return &filtersModeAMD[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE_KNC:
        ZYDIS_ASSERT(index <   2);
        return &filtersModeKNC[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE_MPX:
        ZYDIS_ASSERT(index <   2);
        return &filtersModeMPX[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE_CET:
        ZYDIS_ASSERT(index <   2);
        return &filtersModeCET[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE_LZCNT:
        ZYDIS_ASSERT(index <   2);
        return &filtersModeLZCNT[parent->value][index];
    case ZYDIS_NODETYPE_FILTER_MODE_TZCNT:
        ZYDIS_ASSERT(index <   2);
        return &filtersModeTZCNT[parent->value][index];
    default:
        ZYDIS_UNREACHABLE;
    }
}

void ZydisGetInstructionEncodingInfo(const ZydisDecoderTreeNode* node,
    const ZydisInstructionEncodingInfo** info)
{
    ZYDIS_ASSERT(node->type & ZYDIS_NODETYPE_DEFINITION_MASK);
    const ZydisU8 class = (node->type) & 0x7F;
    ZYDIS_ASSERT(class < ZYDIS_ARRAY_SIZE(instructionEncodings));
    *info = &instructionEncodings[class];
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
