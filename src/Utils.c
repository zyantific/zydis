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

#include <Zydis/Utils.h>

/* ============================================================================================== */
/* Address calculation                                                                            */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZydisStatus ZydisCalcAbsoluteAddress(const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, ZydisU64* address)
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
            *address = ((ZydisU32)instruction->instrAddress + instruction->length +
                (ZydisU32)operand->mem.disp.value);
            return ZYDIS_STATUS_SUCCESS;
        }
        if (operand->mem.base == ZYDIS_REGISTER_RIP)
        {
            *address = (ZydisU64)(instruction->instrAddress + instruction->length +
                operand->mem.disp.value);
            return ZYDIS_STATUS_SUCCESS;
        }
        if ((operand->mem.base == ZYDIS_REGISTER_NONE) &&
            (operand->mem.index == ZYDIS_REGISTER_NONE))
        {
            switch (instruction->addressWidth)
            {
            case 16:
                *address = (ZydisU64)operand->mem.disp.value & 0x000000000000FFFF;
                return ZYDIS_STATUS_SUCCESS;
            case 32:
                *address = (ZydisU64)operand->mem.disp.value & 0x00000000FFFFFFFF;
                return ZYDIS_STATUS_SUCCESS;
            case 64:
                *address = (ZydisU64)operand->mem.disp.value;
                return ZYDIS_STATUS_SUCCESS;
            default:
                return ZYDIS_STATUS_INVALID_PARAMETER;
            }
        }
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        if (operand->imm.isSigned && operand->imm.isRelative)
        {
            *address = (ZydisU64)((ZydisI64)instruction->instrAddress + instruction->length +
                operand->imm.value.s);
            switch (instruction->machineMode)
            {
            case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
            case ZYDIS_MACHINE_MODE_LEGACY_16:
            case ZYDIS_MACHINE_MODE_REAL_16:
            case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
            case ZYDIS_MACHINE_MODE_LEGACY_32:
                if (operand->size == 16)
                {
                    *address &= 0xFFFF;
                }
                break;
            case ZYDIS_MACHINE_MODE_LONG_64:
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

ZydisStatus ZydisGetAccessedFlagsByAction(const ZydisDecodedInstruction* instruction,
    ZydisCPUFlagAction action, ZydisCPUFlagMask* flags)
{
    if (!instruction)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    *flags = 0;
    for (ZydisU8 i = 0; i < ZYDIS_ARRAY_SIZE(instruction->accessedFlags); ++i)
    {
        if (instruction->accessedFlags[i].action == action)
        {
            *flags |= (1 << i);
        }
    }
    return ZYDIS_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
