/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Joel Hoener

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

/**
 * @file Example on assembling a basic function returning `0x1337` in `rax`.
 */

#include <Zydis/Zydis.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

static void ExpectSuccess(ZyanStatus status)
{
    if (ZYAN_FAILED(status))
    {
        fprintf(stderr, "Something failed: 0x%08X\n", status);
        exit(EXIT_FAILURE);
    }
}

static void AppendInstruction(ZydisEncoderRequest* req, ZyanU8** buffer, ZyanUSize* buffer_length)
{
    ZYAN_ASSERT(req);
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(buffer_length);

    ZyanUSize instr_length = *buffer_length;
    ExpectSuccess(ZydisEncoderEncodeInstruction(req, *buffer, &instr_length));
    *buffer += instr_length;
    *buffer_length -= instr_length;
}

static ZyanUSize AssembleCode(ZyanU8* buffer, ZyanUSize buffer_length)
{
    ZYAN_ASSERT(buffer);
    ZYAN_ASSERT(buffer_length);

    ZyanU8* write_ptr = buffer;
    ZyanUSize remaining_length = buffer_length;

    // Assemble `mov rax, 0x1337`.
    ZydisEncoderRequest req;
    memset(&req, 0, sizeof(req));
    req.mnemonic = ZYDIS_MNEMONIC_MOV;
    req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
    req.operand_count = 2;
    req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
    req.operands[0].reg.value = ZYDIS_REGISTER_RAX;
    req.operands[1].type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
    req.operands[1].imm.u = 0x1337;
    AppendInstruction(&req, &write_ptr, &remaining_length);

    // Assemble `ret`.
    memset(&req, 0, sizeof(req));
    req.mnemonic = ZYDIS_MNEMONIC_RET;
    req.branch_type = ZYDIS_ENCODABLE_BRANCH_TYPE_NEAR64;
    req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
    AppendInstruction(&req, &write_ptr, &remaining_length);

    return buffer_length - remaining_length;
}

int main(void)
{
    ZyanU8 buffer[64];
    ZyanUSize length = AssembleCode(buffer, sizeof(buffer));

    puts("Created byte-code:");
    for (ZyanUSize i = 0; i < length; ++i)
    {
        printf("%02X ", buffer[i]);
    }
    puts("");
}

/* ============================================================================================== */