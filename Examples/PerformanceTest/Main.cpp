/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   :

  Last change     : 29. October 2014

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
#include <tchar.h>
#include <iostream>
#include <iomanip>
#include "VXDisassembler.h"
#include <Windows.h>

using namespace Verteron;
using namespace Disassembler;

void testDecodingAndFormatting(uintptr_t baseAddress, PIMAGE_NT_HEADERS ntHeaders)
{
    VXInstructionInfo info;
    VXInstructionDecoder decoder;
    VXIntelInstructionFormatter formatter;
    decoder.setDisassemblerMode(VXDisassemblerMode::M64BIT);
    PIMAGE_SECTION_HEADER sectionHeader = 
        reinterpret_cast<PIMAGE_SECTION_HEADER>(
        reinterpret_cast<uintptr_t>(ntHeaders) + sizeof(IMAGE_NT_HEADERS) 
            + ntHeaders->FileHeader.SizeOfOptionalHeader - sizeof(IMAGE_OPTIONAL_HEADER));
    // Decode all code sections
    for (unsigned int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
    {
        if (sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE)
        {
            std::cout << sectionHeader->SizeOfRawData / 1024 << " KiB" << std::endl;
            VXMemoryDataSource input(reinterpret_cast<const void*>(
                baseAddress + sectionHeader->VirtualAddress), sectionHeader->SizeOfRawData);
            decoder.setDataSource(&input);
            decoder.setInstructionPointer(baseAddress + sectionHeader->VirtualAddress);
            while (decoder.decodeInstruction(info))
            {
   
            }
        }
        sectionHeader++;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{

    // Find kernel32.dll in memory
    void *ntdllBase = GetModuleHandle(L"kernel32.dll");
    PIMAGE_DOS_HEADER dosHeader = static_cast<PIMAGE_DOS_HEADER>(ntdllBase);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        std::cout << "Error: kernel32.dll is corrupted.";
        return 1;
    }
    PIMAGE_NT_HEADERS ntHeaders = 
        reinterpret_cast<PIMAGE_NT_HEADERS>(
        reinterpret_cast<uintptr_t>(dosHeader) + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        std::cout << "Error: kernel32.dll is corrupted.";
        return 1;
    }

    double pcFrequency = 0.0;
    uint64_t pcStart = 0;
    LARGE_INTEGER li;

    // Start the performance counter
    if (!QueryPerformanceFrequency(&li))
    {
        std::cout << "Error: QueryPerformanceFrequency failed.";
        return 1;
    }
    pcFrequency = static_cast<double>(li.QuadPart) / 1000.0;
    if (!QueryPerformanceCounter(&li))
    {
        std::cout << "Error: QueryPerformanceCounter failed.";
        return 1;
    }
    pcStart = li.QuadPart;
    // Perform decoding test
    testDecodingAndFormatting(reinterpret_cast<uintptr_t>(ntdllBase), ntHeaders);
    // Stop the performance counter
    if (!QueryPerformanceCounter(&li))
    {
        std::cout << "Error: QueryPerformanceCounter failed.";
        return 1;
    }
    std::cout << "Time: " << static_cast<double>(li.QuadPart - pcStart) / pcFrequency 
              << std::endl;

    std::cin.get();

    return 0;
}
