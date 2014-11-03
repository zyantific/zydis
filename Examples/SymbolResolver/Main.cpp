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
#include <fstream>
#include <iomanip>
#include <string>
#include "VXDisassembler.h"
#include <Windows.h>

using namespace Verteron;

int _tmain(int argc, _TCHAR* argv[])
{
    // Find module base in memory
    void *moduleBase = GetModuleHandle(L"kernel32.dll");
    uintptr_t baseAddress = reinterpret_cast<uintptr_t>(moduleBase);
    // Parse PE headers
    PIMAGE_DOS_HEADER dosHeader = static_cast<PIMAGE_DOS_HEADER>(moduleBase);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        return 1;
    }
    PIMAGE_NT_HEADERS ntHeaders = 
        reinterpret_cast<PIMAGE_NT_HEADERS>(baseAddress + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        return 1;
    }
    // Initialize disassembler
    VXInstructionInfo info;
    VXInstructionDecoder decoder;
    VXExactSymbolResolver resolver;
    VXIntelInstructionFormatter formatter;
#ifdef _M_X64
    decoder.setDisassemblerMode(VXDisassemblerMode::M64BIT);
#else
    decoder.setDisassemblerMode(VXDisassemblerMode::M32BIT);
#endif
    formatter.setSymbolResolver(&resolver);
    // Initialize output stream
    std::ofstream out;
    out.open(".\\output.txt");
    // Find all call and jump targets
    uint64_t subCount = 0;
    uint64_t locCount = 0;
    PIMAGE_SECTION_HEADER sectionHeader = 
        reinterpret_cast<PIMAGE_SECTION_HEADER>(
        reinterpret_cast<uintptr_t>(ntHeaders) + sizeof(IMAGE_NT_HEADERS) 
            + ntHeaders->FileHeader.SizeOfOptionalHeader - sizeof(IMAGE_OPTIONAL_HEADER));
    for (unsigned int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
    {
        if (sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE)
        {
            VXMemoryDataSource input(reinterpret_cast<const void*>(
                baseAddress + sectionHeader->VirtualAddress), sectionHeader->SizeOfRawData);
            decoder.setDataSource(&input);
            decoder.setInstructionPointer(baseAddress + sectionHeader->VirtualAddress);
            while (decoder.decodeInstruction(info))
            {
                // Skip invalid and non-relative instructions
                if ((info.flags & IF_ERROR_MASK) || !(info.flags & IF_RELATIVE))
                {
                    continue;
                }
                switch (info.mnemonic)
                {
                case VXInstructionMnemonic::CALL:
                    resolver.setSymbol(VDECalcAbsoluteTarget(info, info.operand[0]), 
                        std::string("sub_" + std::to_string(subCount)).c_str());
                    subCount++;
                    break;
                case VXInstructionMnemonic::JMP:
                case VXInstructionMnemonic::JO:
                case VXInstructionMnemonic::JNO:
                case VXInstructionMnemonic::JB:
                case VXInstructionMnemonic::JNB:
                case VXInstructionMnemonic::JE:
                case VXInstructionMnemonic::JNE:
                case VXInstructionMnemonic::JBE:
                case VXInstructionMnemonic::JA:
                case VXInstructionMnemonic::JS:
                case VXInstructionMnemonic::JNS:
                case VXInstructionMnemonic::JP:
                case VXInstructionMnemonic::JNP:
                case VXInstructionMnemonic::JL:
                case VXInstructionMnemonic::JGE:
                case VXInstructionMnemonic::JLE:
                case VXInstructionMnemonic::JG:
                case VXInstructionMnemonic::JCXZ:
                case VXInstructionMnemonic::JECXZ:
                case VXInstructionMnemonic::JRCXZ:
                    resolver.setSymbol(VDECalcAbsoluteTarget(info, info.operand[0]), 
                        std::string("loc_" + std::to_string(locCount)).c_str());
                    locCount++;
                    break;
                default:
                    break;
                }
            }
        }
        sectionHeader++;
    }
    // Add entry point symbol
    resolver.setSymbol(baseAddress + ntHeaders->OptionalHeader.AddressOfEntryPoint, "EntryPoint");
    // Add exported symbols
    if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress > 0)
    {
        PIMAGE_EXPORT_DIRECTORY exports = 
            reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(reinterpret_cast<LPBYTE>(baseAddress) + 
            ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress); 
        PDWORD address = 
            reinterpret_cast<PDWORD>(reinterpret_cast<LPBYTE>(baseAddress) + 
            exports->AddressOfFunctions);
        PDWORD name = 
            reinterpret_cast<PDWORD>(reinterpret_cast<LPBYTE>(baseAddress) + 
            exports->AddressOfNames);
        PWORD ordinal = 
            reinterpret_cast<PWORD>(reinterpret_cast<LPBYTE>(baseAddress) + 
            exports->AddressOfNameOrdinals);
        for(unsigned int i = 0; i < exports->NumberOfNames; ++i)
        {
            resolver.setSymbol(baseAddress + address[ordinal[i]], 
                reinterpret_cast<char*>(baseAddress) + name[i]);
        }
    }
    // Disassemble
    sectionHeader = 
        reinterpret_cast<PIMAGE_SECTION_HEADER>(
        reinterpret_cast<uintptr_t>(ntHeaders) + sizeof(IMAGE_NT_HEADERS) 
            + ntHeaders->FileHeader.SizeOfOptionalHeader - sizeof(IMAGE_OPTIONAL_HEADER));
    for (unsigned int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
    {
        if (sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE)
        {
            VXMemoryDataSource input(reinterpret_cast<const void*>(
                baseAddress + sectionHeader->VirtualAddress), sectionHeader->SizeOfRawData);
            decoder.setDataSource(&input);
            decoder.setInstructionPointer(baseAddress + sectionHeader->VirtualAddress);
            while (decoder.decodeInstruction(info))
            {
                uint64_t offset;
                const char *symbol = resolver.resolveSymbol(info, info.instrAddress, offset);
                if (symbol)
                {
                    out << symbol << ": " << std::endl;     
                }
                out << "  " << std::hex << std::setw(16) << std::setfill('0') 
                    << info.instrAddress << " "; 
                if (info.flags & IF_ERROR_MASK)
                {
                    out << "db " << std::hex << std::setw(2) << std::setfill('0')
                        << static_cast<int>(info.data[0]) << std::endl;
                } else
                {
                    out << formatter.formatInstruction(info) << std::endl;     
                }
            }
        }
        sectionHeader++;
    }
    out.close();
    return 0;
}
