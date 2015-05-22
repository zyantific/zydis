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

/**
 * @file
 * @brief C++ API include file.
 */

 /**
  * @mainpage Zyan Disassembler Engine (Zydis)
  * 
  * Zydis is a fast and lightweight x86/x86-64 disassembler library.
  *
  * @section Features
  * - Supports all x86 and x86-64 (AMD64) General purpose and System instructions.
  * - Supported ISA extensions:
  *  - MMX, FPU (x87), AMD 3DNow
  *  - SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, AES,
  *  - AMD-V, INTEL-VMX, SMX
  * - Optimized for high performance
  * - Very small overhead compared to other common disassembler libraries (about 60KiB)
  * - Abstract formatter and symbol-resolver classes for custom syntax implementations.
  *  - Intel syntax is implemented by default
  * - Complete doxygen documentation
  *
  * @section Quick Example
  * The following example program uses Zydis to disassemble a given memory buffer and prints the 
  * output to the console.
  *
  * @code
  *     #include <tchar.h>
  *     #include <iostream>
  *     #include <stdint.h>
  *     #include "Zydis.hpp"
  * 
  *     int _tmain(int argc, _TCHAR* argv[])
  *     {
  *         uint8_t data[] =
  *         {
  *             0x90, 0xE9, 0x00, 0x00, 0x00, 0x00, 0xC3
  *         };
  *         Zydis::MemoryInput input(&data[0], sizeof(data));
  *         Zydis::InstructionInfo info;
  *         Zydis::InstructionDecoder decoder;
  *         decoder.setDisassemblerMode(Zydis::DisassemblerMode::M32BIT);
  *         decoder.setDataSource(&input);
  *         decoder.setInstructionPointer(0);
  *         Zydis::IntelInstructionFormatter formatter;
  *         while (decoder.decodeInstruction(info))
  *         {
  *             std::cout << formatter.formatInstruction(info) << std::endl;
  *         }
  *     }
  * @endcode
  *
  * @section Compilation
  * Zydis builds cleanly on most platforms without any external dependencies. You can use CMake 
  * to generate project files for your favorite C++14 compiler.
  *
  * @section License
  * Zyan Disassembler Engine is licensed under the MIT License. Dependencies are under their 
  * respective licenses.
  */

#ifndef _ZYDIS_HPP_
#define _ZYDIS_HPP_

#include "ZydisInstructionDecoder.hpp"
#include "ZydisInstructionFormatter.hpp"
#include "ZydisSymbolResolver.hpp"
#include "ZydisUtils.hpp"

#endif /*_ZYDIS_HPP_ */