/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 13. March 2015

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

#include "VXDisassemblerUtils.h"

#include <assert.h>

uint64_t VXCalcAbsoluteTarget(const VXInstructionInfo *info, const VXOperandInfo *operand)
{
    assert((operand->type == OPTYPE_REL_IMMEDIATE) || 
        ((operand->type == OPTYPE_MEMORY) && (operand->base == REG_RIP)));
   
    uint64_t truncMask = 0xFFFFFFFFFFFFFFFFull;
    if (!(info->flags & IF_DISASSEMBLER_MODE_64)) 
    {
        truncMask >>= (64 - info->operand_mode);
    }

    uint16_t size = operand->size;
    if ((operand->type == OPTYPE_MEMORY) && (operand->base == REG_RIP))
    {
        size = operand->offset;
    }

    switch (size)
    {
    case 8:
        return (info->instrPointer + operand->lval.sbyte) & truncMask;
    case 16:
        {
            uint32_t delta = operand->lval.sword & truncMask;
            if ((info->instrPointer + delta) > 0xFFFF)
            {
                return (info->instrPointer & 0xF0000) + ((info->instrPointer + delta) & 0xFFFF);    
            }
            return info->instrPointer + delta;
        }
    case 32:
        return (info->instrPointer + operand->lval.sdword) & truncMask;
    default:
        assert(0);
    }

    return 0;
}