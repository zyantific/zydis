/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 19. March 2015

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

**************************************************************************************************/

#ifndef _VDE_VXOPCODETABLEINTERNAL_H_
#define _VDE_VXOPCODETABLEINTERNAL_H_

#include <stdint.h>
#include "VXOpcodeTable.h"

/**
 * @brief   Contains all opcode tables.
 *          Indexed by the numeric value of the opcode.
 */
extern const VXOpcodeTreeNode vxOptreeTable[][256];

/**
 * @brief   Contains all modrm_mod switch tables.
 *          Index values:
 *          0 = [modrm_mod == !11]
 *          1 = [modrm_mod ==  11]
 */
extern const VXOpcodeTreeNode vxOptreeModrmMod[][2];

/**
 * @brief   Contains all modrm_reg switch tables.
 *          Indexed by the numeric value of the modrm_reg field.
 */
extern const VXOpcodeTreeNode vxOptreeModrmReg[][8];

/**
 * @brief   Contains all modrm_rm switch tables.
 *          Indexed by the numeric value of the modrm_rm field.
 */
extern const VXOpcodeTreeNode vxOptreeModrmRm[][8];

/**
 * @brief   Contains all mandatory-prefix switch tables.
 *          Index values:
 *          0 = none
 *          1 = F2  
 *          2 = F3  
 *          3 = 66
 */
extern const VXOpcodeTreeNode vxOptreeMandatory[][4];

/**
 * @brief   Contains all x87 opcode tables.
 *          Indexed by the numeric value of the 6 lowest bits of the modrm byte (modrm_mod should
 *          always be 11). 
 */
extern const VXOpcodeTreeNode vxOptreeX87[][64];

/**
 * @brief   Contains all address-size switch tables.
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const VXOpcodeTreeNode vxOptreeAddressSize[][3];

/**
 * @brief   Contains all operand-size switch tables.
 *          Index values:
 *          0 = 16
 *          1 = 32  
 *          2 = 64
 */
extern const VXOpcodeTreeNode vxOptreeOperandSize[][3];

/**
 * @brief   Contains all cpu-mode switch tables.
 *          Index values:
 *          0 = [!= 64]
 *          1 = 64
 */
extern const VXOpcodeTreeNode vxOptreeMode[][2];

/**
 * @brief   Contains all vendor switch tables. 
 *          Index values:
 *          0 = AMD
 *          1 = Intel  
 */
extern const VXOpcodeTreeNode vxOptreeVendor[][2];

/**
 * @brief   Contains all 3DNow! switch tables.
 *          Indexed by the numeric value of the 3DNow! opcode.
 */
extern const VXOpcodeTreeNode vxOptree3dnow[][256];

/**
 * @brief   Contains all vex switch tables.
 *          Index values:
 *          0 = none
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
extern const VXOpcodeTreeNode vxOptreeVex[][16];

/**
 * @brief   Contains all vex_w switch tables.
 *          Indexed by the numeric value of the vex_w field.
 */
extern const VXOpcodeTreeNode vxOptreeVexW[][2];

/**
 * @brief   Contains all vex_l switch tables.
 *          Indexed by the numeric value of the vex_l field.
 */
extern const VXOpcodeTreeNode vxOptreeVexL[][2];

/**
 * @brief   Contains all instruction definitions.
 */
extern const VXInstructionDefinition vxInstrDefinitions[];

/**
 * @brief   Contains all instruction mnemonic strings.
 */
extern const char* vxInstrMnemonicStrings[];

/**
 * @brief   Returns the type of the specified opcode tree node.
 * @param   node    The node.
 * @return  The type of the specified opcode tree node.
 */
VX_INLINE VXOpcodeTreeNodeType VXGetOpcodeNodeType(VXOpcodeTreeNode node)
{
    return (VXOpcodeTreeNodeType)((node >> 12) & 0x0F);
} 

/**
 * @brief   Returns the value of the specified opcode tree node.
 * @param   node    The node.
 * @return  The value of the specified opcode tree node.
 */
VX_INLINE uint16_t VXGetOpcodeNodeValue(VXOpcodeTreeNode node)
{
    return (node & 0x0FFF);   
}

/**
 * @brief   Returns the root node of the opcode tree.
 * @return  The root node of the opcode tree.
 */
VX_INLINE VXOpcodeTreeNode VXGetOpcodeTreeRoot()
{
    return 0x1000;
}

/**
 * @brief   Returns a child node of @c parent specified by @c index.
 * @param   parent  The parent node.
 * @param   index   The index of the child node to retrieve.
 * @return  The specified child node.
 */
VX_INLINE VXOpcodeTreeNode VXGetOpcodeTreeChild(VXOpcodeTreeNode parent, uint16_t index)
{
    VXOpcodeTreeNodeType nodeType = VXGetOpcodeNodeType(parent);
    uint16_t tableIndex = VXGetOpcodeNodeValue(parent);
    switch (nodeType)
    {
    case OTNT_TABLE:
        assert(index < 256);
        return vxOptreeTable[tableIndex][index];
    case OTNT_MODRM_MOD:
        assert(index < 2);
        return vxOptreeModrmMod[tableIndex][index];
    case OTNT_MODRM_REG:
        assert(index < 8);
        return vxOptreeModrmReg[tableIndex][index];
    case OTNT_MODRM_RM:
        assert(index < 8);
        return vxOptreeModrmRm[tableIndex][index];
    case OTNT_MANDATORY:
        assert(index < 4);
        return vxOptreeMandatory[tableIndex][index];
    case OTNT_X87:
        assert(index < 64);
        return vxOptreeX87[tableIndex][index];
    case OTNT_ADDRESS_SIZE:
        assert(index < 3);
        return vxOptreeAddressSize[tableIndex][index];
    case OTNT_OPERAND_SIZE:
        assert(index < 3);
        return vxOptreeOperandSize[tableIndex][index];
    case OTNT_MODE:
        assert(index < 2);
        return vxOptreeMode[tableIndex][index];
    case OTNT_VENDOR:
        assert(index < 3);
        return vxOptreeVendor[tableIndex][index];
    case OTNT_AMD3DNOW:
        assert(index < 256);
        return vxOptree3dnow[tableIndex][index];
    case OTNT_VEX:
        assert(index < 16);
        return vxOptreeVex[tableIndex][index];
    case OTNT_VEXW:
        assert(index < 2);
        return vxOptreeVexW[tableIndex][index];
    case OTNT_VEXL:
        assert(index < 2);
        return vxOptreeVexL[tableIndex][index];
    default:
        assert(0);
    }
    return 0xFFFF;
}

/**
 * @brief   Returns the instruction definition that is linked to the given @c node.
 * @param   node    The instruction definition node.
 * @return  Pointer to the instruction definition.
 */
VX_INLINE const VXInstructionDefinition* VXGetInstructionDefinition(VXOpcodeTreeNode node)
{
    assert(VXGetOpcodeNodeType(node) == OTNT_INSTRUCTION_DEFINITION);
    return &vxInstrDefinitions[node & 0x0FFF];    
}

/**
 * @brief   Returns the specified instruction mnemonic string.
 * @param   mnemonic    The mnemonic.
 * @return  The instruction mnemonic string.
 */
VX_INLINE const char* VXGetInstructionMnemonicString(VXInstructionMnemonic mnemonic)
{
    return vxInstrMnemonicStrings[(uint16_t)mnemonic];
}

/**
 * @brief   Returns the numeric value for a simple operand size definition.
 * @param   operandSize The defined operand size.
 * @return  The the numeric value for the simple operand size definition.
 */
VX_INLINE uint16_t VXGetSimpleOperandSize(VXDefinedOperandSize operandSize)
{
    static const uint16_t operandSizes[8] =
    {
        8, 16, 32, 64, 80, 12, 128, 256
    };

    uint16_t index = (uint16_t)(operandSize - DOS_B);
    assert(index < 8);
    return operandSizes[index];
}

/**
 * @brief   Returns the memory-size part of a complex operand size definition.
 * @param   operandSize The defined operand size.
 * @return  The memory-size part of the operand size definition.
 */
VX_INLINE VXDefinedOperandSize VXGetComplexOperandMemSize(VXDefinedOperandSize operandSize)
{
    return (VXDefinedOperandSize)(operandSize & 0x0F);
}

/**
 * @brief   Returns the register-size part of a complex operand size definition.
 * @param   operandSize The defined operand size.
 * @return  The register-size part of the operand size definition.
 */
VX_INLINE VXDefinedOperandSize VXGetComplexOperandRegSize(VXDefinedOperandSize operandSize)
{
    return (VXDefinedOperandSize)((operandSize >> 4) & 0x0F);    
}

#endif // _VDE_VXOPCODETABLEINTERNAL_H_