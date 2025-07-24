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

#include <Zydis/SharedTypes.h>
#include <Zydis/Internal/DecoderData.h>

/* ============================================================================================== */
/* Data tables                                                                                    */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Physical instruction encodings                                                                 */
/* ---------------------------------------------------------------------------------------------- */

#include <Generated/InstructionEncodings.inc>

/* ---------------------------------------------------------------------------------------------- */
/* Decoder tree                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

ZYAN_STATIC_ASSERT(ZYDIS_NODETYPE_REQUIRED_BITS <= 8);

/**
 * Defines a decoder tree node header.
 *
 * @param type  The node type, see `ZydisDecoderTreeNodeTypes`.
 * @param arg0  The first argument (if applicable).
 *
 * Encoding: [15..8] = ARG0, [7..0] = TYPE.
 */
#define ZYDIS_DT_HEADER(type, arg0) \
    (0x0000 | (((ZyanU8)(arg0)) << 8) | ((ZyanU8)(type)))

/**
 * Defines an arbitrary value decoder tree node entry.
 *
 * @param value The value.
 */
#define ZYDIS_DT_VALUE(value) \
    ((ZyanU16)(value))

/**
 * Defines an invalid (unused) decoder tree node entry.
 */
#define ZYDIS_DT_INVALID \
    0x0000

/**
 * Defines the offset to the next node in the decoder tree, relative to the start of the current
 * node.
 *
 * @param offset    The offset to the next node.
 */
#define ZYDIS_DT_OFFSET(offset) \
    ((ZyanU16)(offset))

/**
 * Defines an opcode table switch decoder tree node header that instructs the decoder to switch
 * to the opcode table with the given `opcode_table_id`.
 *
 * @param opcode_table_id   The id of the opcode table to switch to.
 */
#define ZYDIS_DT_SWITCH_TABLE_HEADER(opcode_table_id) \
    ZYDIS_DT_HEADER(ZYDIS_NODETYPE_SWITCH_TABLE, (opcode_table_id))

/**
 * Defines a definition node decoder tree node header.
 *
 * @param encoding_id   The id of the physical instruction encoding entry for the definition.
 *                      See `INSTR_ENCODINGS`.
 */
#define ZYDIS_DT_DEFINITION_HEADER(encoding_id) \
    ZYDIS_DT_HEADER(ZYDIS_NODETYPE_DEFINITION, (encoding_id))

/**
 * Represents an instruction definition reference. Only valid in combination with the corresponding
 * instruction encoding.
 *
 * @param id    The instruction definition.
 */
#define ZYDIS_DT_DEFINITION(id) \
    ((ZyanU16)(id))

#include <Generated/DecoderTables.inc>

#undef ZYDIS_DT_HEADER
#undef ZYDIS_DT_VALUE
#undef ZYDIS_DT_INVALID
#undef ZYDIS_DT_OFFSET
#undef ZYDIS_DT_SWITCH_TABLE_HEADER
#undef ZYDIS_DT_DEFINITION_HEADER
#undef ZYDIS_DT_DEFINITION

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* API                                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Decoder tree                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

const ZydisDecoderTreeNode* ZydisGetOpcodeTableRootNode(ZyanU8 opcode_table_id)
{
    ZYAN_ASSERT((ZyanUSize)opcode_table_id < ZYAN_ARRAY_LENGTH(OPCODE_TABLE_TREES));

    return OPCODE_TABLE_TREES[opcode_table_id];
}

void ZydisGetInstructionEncodingInfo(const ZydisDecoderTreeNode* node,
    const ZydisInstructionEncodingInfo** info)
{
    ZYAN_ASSERT(ZYDIS_DT_GET_TYPE(node) == ZYDIS_NODETYPE_DEFINITION);
    const ZyanU8 encoding_id = ZYDIS_DT_GET_ARG0(node);

    ZYAN_ASSERT((ZyanUSize)encoding_id < ZYAN_ARRAY_LENGTH(INSTR_ENCODINGS));
    *info = &INSTR_ENCODINGS[encoding_id];
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
