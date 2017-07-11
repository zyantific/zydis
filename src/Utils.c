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

#include <stdint.h>
#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Address calculation                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisUtilsCalcAbsoluteTargetAddress(const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, uint64_t* address)
{
    if (!instruction || !operand || !address)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    switch (operand->type)
    {
    case ZYDIS_OPERAND_TYPE_MEMORY:
        if (!operand->mem.disp.hasDisplacement)
        {
            return ZYDIS_STATUS_INVALID_PARAMETER;
        }
        if (operand->mem.base == ZYDIS_REGISTER_EIP)
        {
            *address = 
                (uint64_t)((uint32_t)instruction->instrPointer + (uint32_t)operand->mem.disp.value);
            return ZYDIS_STATUS_SUCCESS;   
        }
        if (operand->mem.base == ZYDIS_REGISTER_RIP)
        {
            *address = (uint64_t)(instruction->instrPointer + operand->mem.disp.value);
            return ZYDIS_STATUS_SUCCESS;   
        }
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        if (operand->imm.isSigned && operand->imm.isRelative)
        {
            *address = (uint64_t)((int64_t)instruction->instrPointer + operand->imm.value.s);
            switch (instruction->machineMode)
            {
            case 16:
            case 32:
                if (operand->size == 16)
                {
                    *address &= 0xFFFF;
                }
                break;
            case 64:
                break;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
            return ZYDIS_STATUS_SUCCESS;     
        }
        break;
    default:
        break;
    }
    return ZYDIS_STATUS_INVALID_PARAMETER;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Flags                                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisGetCPUFlagsByAction(const ZydisDecodedInstruction* instruction, 
    ZydisCPUFlagAction action, ZydisCPUFlagMask* flags)
{
    if (!instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *flags = 0;
    for (uint8_t i = 0; i < ZYDIS_ARRAY_SIZE(instruction->flags); ++i)
    {
        if (instruction->flags[i].action == action)
        {
            *flags |= (1 << i);
        }
    }
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
