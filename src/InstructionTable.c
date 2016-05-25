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

#include <Zydis/Internal/InstructionTable.h>

#define ZYDIS_INVALID { ZYDIS_NODETYPE_INVALID, 0x00000000 }
#define ZYDIS_FILTER(type, id) { type, id }
#define ZYDIS_DEFINITION(id) { ZYDIS_NODETYPE_DEFINITION, id }

#include <Zydis/Internal/InstructionTable.inc>

#undef ZYDIS_INVALID
#undef ZYDIS_FILTER
#undef ZYDIS_DEFINITION

#define ZYDIS_MAKE_OPERAND(type, encoding, access) \
    (((uint16_t)type) << 8) | ((((uint16_t)encoding) & 0x3F) << 2)  | (access & 0x03)

#define ZYDIS_MAKE_AVX512INFO(hasEvexB, hasEvexAAA, hasEvexZ) \
    ((((uint8_t)hasEvexB & 0x03) << 2) | (((uint8_t)hasEvexAAA & 0x01) << 1) | (hasEvexZ & 0x01))

//#define ZYDIS_MAKE_DEFINITION(mnemonic, op1, op2, op3, op4, avx512info) \
//    { (((uint16_t)mnemonic & 0xFFF) << 4) | (avx512info & 0xF), { op1, op2, op3, op4 } }
#define ZYDIS_MAKE_DEFINITION(mnemonic, operandsId, avx512info) \
    { (((uint16_t)mnemonic & 0xFFF) << 4) | (avx512info & 0xF), operandsId }

#include <Zydis/Internal/InstructionDefinitions.inc>

#undef ZYDIS_MAKE_OPERAND
#undef ZYDIS_MAKE_AVX512INFO
#undef ZYDIS_MAKE_DEFINITION
