/***************************************************************************************************

  Zyan Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : Joel Höner

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

#include "ZydisUtils.h"
#include "ZydisUtils.hpp"

static_assert(
    sizeof(ZydisInstructionInfo) == sizeof(Zydis::InstructionInfo), 
    "struct size mismatch");
static_assert(
    sizeof(ZydisOperandInfo)     == sizeof(Zydis::OperandInfo),
    "struct size mismatch");

uint64_t ZydisCalcAbsoluteTarget(const ZydisInstructionInfo *info, const ZydisOperandInfo *operand)
{
    return Zydis::CalcAbsoluteTarget(
        *reinterpret_cast<const Zydis::InstructionInfo*>(info),
        *reinterpret_cast<const Zydis::OperandInfo*>(operand));
}