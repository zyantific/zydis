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

ZyanStatus ZydisCalcAbsoluteAddress(const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, ZyanU64 runtime_address, ZyanU64* target_address)
{
    if (!instruction || !operand || !target_address)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
    switch (operand->type)
    {
    case ZYDIS_OPERAND_TYPE_MEMORY:
        if (!operand->mem.disp.has_displacement)
        {
            return ZYAN_STATUS_INVALID_ARGUMENT;
        }
        if (operand->mem.base == ZYDIS_REGISTER_EIP)
        {
            *target_address = ((ZyanU32)runtime_address + instruction->length +
                (ZyanU32)operand->mem.disp.value);
            return ZYAN_STATUS_SUCCESS;
        }
        if (operand->mem.base == ZYDIS_REGISTER_RIP)
        {
            *target_address = (ZyanU64)(runtime_address + instruction->length +
                operand->mem.disp.value);
            return ZYAN_STATUS_SUCCESS;
        }
        if ((operand->mem.base == ZYDIS_REGISTER_NONE) &&
            (operand->mem.index == ZYDIS_REGISTER_NONE))
        {
            switch (instruction->address_width)
            {
            case 16:
                *target_address = (ZyanU64)operand->mem.disp.value & 0x000000000000FFFF;
                return ZYAN_STATUS_SUCCESS;
            case 32:
                *target_address = (ZyanU64)operand->mem.disp.value & 0x00000000FFFFFFFF;
                return ZYAN_STATUS_SUCCESS;
            case 64:
                *target_address = (ZyanU64)operand->mem.disp.value;
                return ZYAN_STATUS_SUCCESS;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
        }
        break;
    case ZYDIS_OPERAND_TYPE_IMMEDIATE:
        if (operand->imm.is_signed && operand->imm.is_relative)
        {
            *target_address = (ZyanU64)((ZyanI64)runtime_address + instruction->length +
                operand->imm.value.s);
            switch (instruction->machine_mode)
            {
            case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
            case ZYDIS_MACHINE_MODE_LEGACY_16:
            case ZYDIS_MACHINE_MODE_REAL_16:
            case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
            case ZYDIS_MACHINE_MODE_LEGACY_32:
                if (operand->size == 16)
                {
                    *target_address &= 0xFFFF;
                }
                break;
            case ZYDIS_MACHINE_MODE_LONG_64:
                break;
            default:
                return ZYAN_STATUS_INVALID_ARGUMENT;
            }
            return ZYAN_STATUS_SUCCESS;
        }
        break;
    default:
        break;
    }
    return ZYAN_STATUS_INVALID_ARGUMENT;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Flags                                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisGetAccessedFlagsByAction(const ZydisDecodedInstruction* instruction,
    ZydisCPUFlagAction action, ZydisCPUFlags* flags)
{
    if (!instruction)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }
    *flags = 0;
    for (ZyanU8 i = 0; i < ZYAN_ARRAY_LENGTH(instruction->accessedFlags); ++i)
    {
        if (instruction->accessedFlags[i].action == action)
        {
            *flags |= (1 << i);
        }
    }
    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
