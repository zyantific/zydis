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

#include <stdint.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Operand utils                                                                                  */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisUtilsCalcAbsoluteTargetAddress(const ZydisInstructionInfo* info, 
    const ZydisOperandInfo* operand, uint64_t* address)
{
    if (!info || !operand || !address)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    switch (operand->type)
    {
    case ZYDIS_OPERAND_TYPE_MEMORY:
        if (operand->mem.disp.size == 0)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        if (operand->mem.base == ZYDIS_REGISTER_EIP)
        {
            *address = (uint64_t)((uint32_t)info->instrPointer + operand->mem.disp.value.sdword); 
            return ZYDIS_STATUS_SUCCESS;   
        }
        if (operand->mem.base == ZYDIS_REGISTER_RIP)
        {
            *address = (uint64_t)(info->instrPointer + operand->mem.disp.value.sqword); 
            return ZYDIS_STATUS_SUCCESS;   
        }
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        if (operand->imm.isSigned || operand->imm.isRelative)
        {
            *address = (uint64_t)((int64_t)info->instrPointer + operand->imm.value.sqword);
            switch (info->operandMode)
            {
            case 16:
                *address = (uint16_t)*address;
                break;
            case 32:
                if (info->mode != ZYDIS_DISASSEMBLER_MODE_64BIT)
                {
                    *address = (uint32_t)*address;
                }
                break;
            }
            return ZYDIS_STATUS_SUCCESS;     
        }
        break;
    }
    return ZYDIS_STATUS_INVALID_PARAMETER;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
