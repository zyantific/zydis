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

#ifndef ZYDIS_INTERNAL_DECODERDATA_H
#define ZYDIS_INTERNAL_DECODERDATA_H

#include <Zycore/Defines.h>
#include <Zycore/Types.h>
#include <Zydis/Defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

// MSVC does not like types other than (un-)signed int for bit-fields
#ifdef ZYAN_MSVC
#   pragma warning(push)
#   pragma warning(disable:4214)
#endif

#pragma pack(push, 1)

/* ---------------------------------------------------------------------------------------------- */
/* Decoder tree                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Defines the `ZydisDecoderTreeNode` data-type.
 */
typedef ZyanU16 ZydisDecoderTreeNode;

/* ---------------------------------------------------------------------------------------------- */

/**
 * Values that represent Zydis decoder tree node types.
 */
typedef enum ZydisDecoderTreeNodeType_
{
    ZYDIS_NODETYPE_INVALID = 0,
    /**
     * Reference to an instruction-definition.
     */
    ZYDIS_NODETYPE_DEFINITION,
    /**
     * A decoder tree node that instructs the decoder to switch to a different opcode table.
     * The `arg0` value of the node header is the id of the opcode table to switch to.
     */
    ZYDIS_NODETYPE_SWITCH_TABLE,
    /**
     * Reference to an XOP-map selector.
     */
    ZYDIS_NODETYPE_SWITCH_TABLE_XOP,
    /**
     * Reference to an VEX-map selector.
     */
    ZYDIS_NODETYPE_SWITCH_TABLE_VEX,
    /**
     * Reference to an EVEX/MVEX-map selector.
     */
    ZYDIS_NODETYPE_SWITCH_TABLE_EMVEX,
    /**
     * Reference to a REX2-map selector.
     */
    ZYDIS_NODETYPE_SWITCH_TABLE_REX2,
    /**
     * Reference to an opcode selector.
     */
    ZYDIS_NODETYPE_OPCODE_TABLE,
    /**
     * Reference to an instruction-mode selector.
     */
    ZYDIS_NODETYPE_MODE,
    /**
     * Reference to an compacted instruction-mode selector.
     */
    ZYDIS_NODETYPE_MODE_COMPACT,
    /**
     * Reference to a ModRM.mod selector.
     */
    ZYDIS_NODETYPE_MODRM_MOD,
    /**
     * Reference to a compacted ModRM.mod selector.
     */
    ZYDIS_NODETYPE_MODRM_MOD_COMPACT,
    /**
     * Reference to a ModRM.reg selector.
     */
    ZYDIS_NODETYPE_MODRM_REG,
    /**
     * Reference to a ModRM.rm selector.
     */
    ZYDIS_NODETYPE_MODRM_RM,
    /**
     * Reference to a PrefixGroup1 selector.
     */
    ZYDIS_NODETYPE_PREFIX_GROUP1,
    /**
     * Reference to a mandatory-prefix selector.
     */
    ZYDIS_NODETYPE_MANDATORY_PREFIX,
    /**
     * Reference to an operand-size selector.
     */
    ZYDIS_NODETYPE_OPERAND_SIZE,
    /**
     * Reference to an address-size selector.
     */
    ZYDIS_NODETYPE_ADDRESS_SIZE,
    /**
     * Reference to a vector-length selector.
     */
    ZYDIS_NODETYPE_VECTOR_LENGTH,
    /**
     * Reference to an REX/VEX/EVEX.W selector.
     */
    ZYDIS_NODETYPE_REX_W,
    /**
     * Reference to an REX/VEX/EVEX.B selector.
     */
    ZYDIS_NODETYPE_REX_B,
    /**
     * Reference to an EVEX.b selector.
     */
    ZYDIS_NODETYPE_EVEX_B,
    /**
     * Reference to an MVEX.E selector.
     */
    ZYDIS_NODETYPE_MVEX_E,
    /**
     * Reference to a AMD-mode selector.
     */
    ZYDIS_NODETYPE_MODE_AMD,
    /**
     * Reference to a KNC-mode selector.
     */
    ZYDIS_NODETYPE_MODE_KNC,
    /**
     * Reference to a MPX-mode selector.
     */
    ZYDIS_NODETYPE_MODE_MPX,
    /**
     * Reference to a CET-mode selector.
     */
    ZYDIS_NODETYPE_MODE_CET,
    /**
     * Reference to a LZCNT-mode selector.
     */
    ZYDIS_NODETYPE_MODE_LZCNT,
    /**
     * Reference to a TZCNT-mode selector.
     */
    ZYDIS_NODETYPE_MODE_TZCNT,
    /**
     * Reference to a WBNOINVD-mode selector.
     */
    ZYDIS_NODETYPE_MODE_WBNOINVD,
    /**
     * Reference to a CLDEMOTE-mode selector.
     */
    ZYDIS_NODETYPE_MODE_CLDEMOTE,
    /**
     * Reference to a IPREFETCH-mode selector.
     */
    ZYDIS_NODETYPE_MODE_IPREFETCH,
    /**
     * Reference to a UD0_COMPAT-mode selector.
     */
    ZYDIS_NODETYPE_MODE_UD0_COMPAT,
    /**
     * Reference to an EVEX.nd selector.
     */
    ZYDIS_NODETYPE_EVEX_ND,
    /**
     * Reference to an EVEX.nf selector.
     */
    ZYDIS_NODETYPE_EVEX_NF,
    /**
     * Reference to an EVEX.scc selector.
     */
    ZYDIS_NODETYPE_EVEX_SCC,
    /**
     * Reference to a REX2-prefix selector.
     */
    ZYDIS_NODETYPE_REX_2,
    /**
     * Reference to a EVEX.U selector.
     */
    ZYDIS_NODETYPE_EVEX_U,

    /**
     * Maximum value of this enum.
     */
    ZYDIS_NODETYPE_MAX_VALUE = ZYDIS_NODETYPE_EVEX_U,
    /**
     * The minimum number of bits required to represent all values of this enum.
     */
    ZYDIS_NODETYPE_REQUIRED_BITS = ZYAN_BITS_TO_REPRESENT(ZYDIS_NODETYPE_MAX_VALUE)
} ZydisDecoderTreeNodeType;

/* ---------------------------------------------------------------------------------------------- */
/* Opcode tables                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

// TODO: Auto generate this.

#define ZYDIS_OPCODE_TABLE_PRIMARY 0x00
#define ZYDIS_OPCODE_TABLE_0F      0x01
#define ZYDIS_OPCODE_TABLE_0F38    0x02
#define ZYDIS_OPCODE_TABLE_0F3A    0x03
#define ZYDIS_OPCODE_TABLE_VEX     0x04
#define ZYDIS_OPCODE_TABLE_EVEX    0x14
#define ZYDIS_OPCODE_TABLE_MVEX    0x34
#define ZYDIS_OPCODE_TABLE_XOP     0x44
#define ZYDIS_OPCODE_TABLE_3DNOW   0x47

/* ---------------------------------------------------------------------------------------------- */

#pragma pack(pop)

#ifdef ZYAN_MSVC
#   pragma warning(pop)
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Physical instruction encoding info                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Defines the `ZydisInstructionEncodingFlags` data-type.
 */
typedef ZyanU8 ZydisInstructionEncodingFlags;

/**
 * The instruction has an optional modrm byte.
 */
#define ZYDIS_INSTR_ENC_FLAG_HAS_MODRM      0x01

/**
 * The instruction has an optional displacement value.
 */
#define ZYDIS_INSTR_ENC_FLAG_HAS_DISP       0x02

/**
 * The instruction has an optional immediate value.
 */
#define ZYDIS_INSTR_ENC_FLAG_HAS_IMM0       0x04

/**
 * The instruction has a second optional immediate value.
 */
#define ZYDIS_INSTR_ENC_FLAG_HAS_IMM1       0x08

/**
 * The instruction ignores the value of `modrm.mod` and always assumes `modrm.mod == 3`
 *          ("reg, reg" - form).
 *
 *          Instructions with this flag can't have a SIB byte or a displacement value.
 */
#define ZYDIS_INSTR_ENC_FLAG_FORCE_REG_FORM 0x10

/**
 * Defines the `ZydisInstructionEncodingInfo` struct.
 */
typedef struct ZydisInstructionEncodingInfo_
{
    /**
     * Contains flags with information about the physical instruction-encoding.
     */
    ZydisInstructionEncodingFlags flags;
    /**
     * Displacement info.
     */
    struct
    {
        /**
         * The size of the displacement value.
         */
        ZyanU8 size[3];
    } disp;
    /**
     * Immediate info.
     */
    struct
    {
        /**
         * The size of the immediate value.
         */
        ZyanU8 size[3];
        /**
         * Signals, if the value is signed.
         */
        ZyanBool is_signed;
        /**
         * Signals, if the value is an address.
         */
        ZyanBool is_address;
        /**
         * Signals, if the value is a relative offset.
         */
        ZyanBool is_relative;
    } imm[2];
} ZydisInstructionEncodingInfo;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Decoder tree                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Gets the type of the given decoder tree node.
 *
 * @param node  The decoder tree node.
 *
 * Encoding: [15..8] = ARG0, [7..0] = TYPE.
 */
#define ZYDIS_DT_GET_TYPE(node) \
    ((ZydisDecoderTreeNodeType)((*(node)) & 0xFF))

/**
 * Gets the first argument of the given decoder tree node.
 *
 * @param node  The decoder tree node.
 *
 * Encoding: [15..8] = ARG0, [7..0] = TYPE.
 */
#define ZYDIS_DT_GET_ARG0(node) \
    ((ZyanU8)(((*(node)) >> 8) & 0xFF))

/**
 * Gets the value at index `index` of the given decoder tree node.
 *
 * @param node  The decoder tree node.
 * @param index The index of the value to retrieve.
 */
#define ZYDIS_DT_GET_VALUE(node, index) \
    ((ZyanU16)(*((node) + 1 + (index))))

/**
 * Returns the root node of the opcode table with the given `opcode_table_id`.
 *
 * @param opcode_table_id   The id of the opcode table to retrieve.
 * @return The root node of the opcode table with the given `opcode_table_id`.
 */
ZYDIS_NO_EXPORT const ZydisDecoderTreeNode* ZydisGetOpcodeTableRootNode(ZyanU8 opcode_table_id);

/**
 * Returns information about optional instruction parts (like modrm, displacement or
 * immediates) for the instruction that is linked to the given `node`.
 *
 * @param   node    The instruction definition node.
 * @param   info    A pointer to the `ZydisInstructionParts` struct.
 */
ZYDIS_NO_EXPORT void ZydisGetInstructionEncodingInfo(const ZydisDecoderTreeNode* node,
    const ZydisInstructionEncodingInfo** info);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INTERNAL_DECODERDATA_H */
