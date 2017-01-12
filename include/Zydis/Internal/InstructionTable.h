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

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Generated types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

// MSVC does not like types other than (un-)signed int for bitfields
#ifdef ZYDIS_MSVC
#   pragma warning(push)
#   pragma warning(disable:4214)
#endif

#pragma pack(push, 1)

/**
 * @brief   Defines the @c ZydisInstructionTableNodeType datatype.
 */
typedef uint8_t ZydisInstructionTableNodeType;

/**
 * @brief   Defines the @c ZydisInstructionTableNodeValue datatype.
 */
typedef uint16_t ZydisInstructionTableNodeValue;

/**
 * @brief   Defines the @c ZydisInstructionTableNode struct.
 * 
 * This struct is static for now, because its size is sufficient to encode up to 65535
 * instruction filters (what is about 10 times more than we currently need).
 */
typedef struct ZydisInstructionTableNode_
{
    ZydisInstructionTableNodeType type;
    ZydisInstructionTableNodeValue value;
} ZydisInstructionTableNode;

/**
 * @brief   Defines the @c ZydisSemanticOperandType datatype.
 */
typedef uint8_t ZydisSemanticOperandType;

/**
 * @brief   Defines the @c ZydisOperandDefinition struct.
 * 
 * This struct is static for now, because adding more operand-types oder encodings requires 
 * code changes anyways.
 */
typedef struct ZydisOperandDefinition_
{
    ZydisSemanticOperandType type : 7;
    ZydisOperandEncoding encoding : 5;
    ZydisOperandAction action : 3;
} ZydisOperandDefinition;

#include <Zydis/Internal/GeneratedTypes.inc>

#pragma pack(pop)

#ifdef ZYDIS_MSVC
#   pragma warning(pop)
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Instruction Table                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent zydis instruction table node types.
 */
enum ZydisInstructionTableNodeTypes
{
    ZYDIS_NODETYPE_INVALID                  = 0x00,
    /**
     * @brief   Reference to an instruction-definition with 0 operands.
     */
    ZYDIS_NODETYPE_DEFINITION_0OP           = 0x01,
    /**
     * @brief   Reference to an instruction-definition with 1 operands.
     */
    ZYDIS_NODETYPE_DEFINITION_1OP           = 0x02,
    /**
     * @brief   Reference to an instruction-definition with 2 operands.
     */
    ZYDIS_NODETYPE_DEFINITION_2OP           = 0x03,
    /**
     * @brief   Reference to an instruction-definition with 3 operands.
     */
    ZYDIS_NODETYPE_DEFINITION_3OP           = 0x04,
    /**
     * @brief   Reference to an instruction-definition with 4 operands.
     */
    ZYDIS_NODETYPE_DEFINITION_4OP           = 0x05,
    /**
     * @brief   Reference to an instruction-definition with 5 operands.
     */
    ZYDIS_NODETYPE_DEFINITION_5OP           = 0x06,
    /**
     * @brief   Reference to an opcode filter.
     */
    ZYDIS_NODETYPE_FILTER_OPCODE            = 0x07,
    /**
     * @brief   Reference to an VEX/EVEX-map filter.
     */
    ZYDIS_NODETYPE_FILTER_VEX               = 0x08,
    /**
     * @brief   Reference to an XOP-map filter.
     */
    ZYDIS_NODETYPE_FILTER_XOP               = 0x09,
    /**
     * @brief   Reference to an instruction-mode filter.
     */
    ZYDIS_NODETYPE_FILTER_MODE              = 0x0A,
    /**
     * @brief   Reference to a mandatory-prefix filter.
     */
    ZYDIS_NODETYPE_FILTER_MANDATORYPREFIX   = 0x0B,
    /**
     * @brief   Reference to a ModRM.mod filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRMMOD          = 0x0C,
    /**
     * @brief   Reference to a ModRM.reg filter.
     */                                                                                      
    ZYDIS_NODETYPE_FILTER_MODRMREG          = 0x0D,
    /**
     * @brief   Reference to a ModRM.rm filter.
     */
    ZYDIS_NODETYPE_FILTER_MODRMRM           = 0x0E,  
    /**
     * @brief   Reference to an operand-size filter.
     */
    ZYDIS_NODETYPE_FILTER_OPERANDSIZE       = 0x0F,
    /**
     * @brief   Reference to an address-size filter.
     */
    ZYDIS_NODETYPE_FILTER_ADDRESSSIZE       = 0x10,
    /**
     * @brief   Reference to an REX/VEX/EVEX.w filter.
     */
    ZYDIS_NODETYPE_FILTER_REXW              = 0x11,
    /**
     * @brief   Reference to an VEX/EVEX.l filter.
     */
    ZYDIS_NODETYPE_FILTER_VEXL              = 0x12,
    /**
     * @brief   Reference to an EVEX.l' filter.
     */
    ZYDIS_NODETYPE_FILTER_EVEXL2            = 0x13,
    /**
     * @brief   Reference to an EVEX.b filter.
     */
    ZYDIS_NODETYPE_FILTER_EVEXB             = 0x14
};

/* ---------------------------------------------------------------------------------------------- */
/* Operand definition                                                                             */
/* ---------------------------------------------------------------------------------------------- */

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
    ZYDIS_SEM_OPERAND_TYPE_TR,
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
    ZYDIS_SEM_OPERAND_TYPE_ECX,
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
/* Instruction definition                                                                         */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent zydis EVEX.b-contexts.
 */
enum ZydisEvexBFunctionalities
{
    ZYDIS_EVEX_CONTEXT_INVALID,
    ZYDIS_EVEX_CONTEXT_BC,
    ZYDIS_EVEX_CONTEXT_RC,
    ZYDIS_EVEX_CONTEXT_SAE
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Functions                                                                                      */
/* ============================================================================================== */

/**
 * @brief   Returns the root node of the instruction table.
 *
 * @return  The root node of the instruction table.
 */
ZYDIS_NO_EXPORT const ZydisInstructionTableNode* ZydisInstructionTableGetRootNode();

/**
 * @brief   Returns the child node of @c parent specified by @c index.
 *
 * @param   parent  The parent node.
 * @param   index   The index of the child node to retrieve.
 *                  
 * @return  The specified child node.
 */
ZYDIS_NO_EXPORT const ZydisInstructionTableNode* ZydisInstructionTableGetChildNode(
    const ZydisInstructionTableNode* parent, uint16_t index);

/**
 * @brief   Returns the instruction- and operand-definition that is linked to the given @c node.
 *
 * @param   node            The instruction definition node.
 * @param   definition      A pointer to a variable that receives a pointer to the 
 *                          instruction-definition.
 * @param   operands        A pointer to a variable that receives a pointer to the first 
 *                          operand-definition of the instruction.
 * @param   operandCount    A pointer to a variable that receives the number of operand-definitions
 *                          for the instruction. 
 *                  
 * @return  @c TRUE, if @c node contained a valid instruction-definition, @c FALSE if not.
 */
ZYDIS_NO_EXPORT ZydisBool ZydisInstructionTableGetDefinition(const ZydisInstructionTableNode* node,
    const ZydisInstructionDefinition** definition, const ZydisOperandDefinition** operands, 
        uint8_t* operandCount);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INSTRUCTIONTABLE_H */
