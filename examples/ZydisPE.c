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

#include <algorithm>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <Zydis/Zydis.h>


typedef unsigned int uint;

inline uint ALIGN_DOWN(uint x, uint align)
{
    return (x & ~(align - 1));
}

inline uint ALIGN_UP(uint x, uint align)
{
    return ((x & (align - 1)) ? ALIGN_DOWN(x, align) + align : x);
}

/* ============================================================================================== */
/* Custom Section search with RVA                                                                 */
/* ============================================================================================== */

/**
 * @brief   Returns pointer to the section containing given @c RVA.
 *
 * @param   ntHeaders    Pointer to NT Header.
 * @param   RVAddress    RVA.
 *
 * @return  Pointer to section containing given @c RVA or NULL if not found.
 */
PIMAGE_SECTION_HEADER GetSection(PIMAGE_NT_HEADERS ntHeaders, DWORD RVAddress)
{
    PIMAGE_SECTION_HEADER pSectHeader = IMAGE_FIRST_SECTION(ntHeaders);
    for (int i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++, ++pSectHeader)
    {
        DWORD sec_size = pSectHeader->SizeOfRawData;
        if (pSectHeader->Misc.VirtualSize > 0)
        {
            sec_size = min(pSectHeader->Misc.VirtualSize, sec_size);
        }
        sec_size = ALIGN_UP(sec_size, ntHeaders->OptionalHeader.FileAlignment);
        if ((RVAddress >= pSectHeader->VirtualAddress) &&
            (RVAddress < (pSectHeader->VirtualAddress + sec_size))) {
            return pSectHeader;
        }
    }
    return NULL;
}

/* ============================================================================================== */
/* Relative Virtual Address to address in file mapping                                            */
/* ============================================================================================== */

/**
 * @brief   Converts relative virtual address to file offset.
 *
 * @param   pBase        Pointer to file in memory.
 * @param   RVAddress    RVA to convert.
 *
 * @return  Address in file mapping corresponding to RVAddress or NULL.
 */
PDWORD RVA2RAW(uint8_t* pBase, DWORD RVAddress) {
    auto pDosHeader = (PIMAGE_DOS_HEADER)pBase;
    auto pHeader = (PIMAGE_NT_HEADERS)(pBase + pDosHeader->e_lfanew);
    PIMAGE_SECTION_HEADER pSectHeader = GetSection(pHeader, RVAddress);
    if (pSectHeader == NULL)
    {
        return PDWORD(pBase + RVAddress);
    }
    PDWORD address = PDWORD(pBase + pSectHeader->PointerToRawData + (RVAddress - pSectHeader->VirtualAddress));
    return address;
}

/* ============================================================================================== */
/* Custom Symbol Resolving                                                                        */
/* ============================================================================================== */

/**
 * @brief   Returns the name of the exported function at the given @c address.
 *
 * @param   moduleHandle    The module handle.
 * @param   address         The function address.
 *
 * @return  The name of the exported function at @c address or @c NULL.
 */
static const char* GetExportName(void* pBase, uintptr_t address)
{
    if (!pBase)
    {
        return NULL;
    }
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)pBase;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        return NULL;
    }
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)dosHeader + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        return NULL;
    }

    DWORD imageBase;
    PIMAGE_DATA_DIRECTORY pImageDataDirectory;

    if (ntHeaders->OptionalHeader.Magic == 0x10b) {
        auto opt_header32 = (PIMAGE_OPTIONAL_HEADER32)&(ntHeaders->OptionalHeader);
        imageBase = opt_header32->ImageBase;
        pImageDataDirectory = opt_header32->DataDirectory;
    }
    else {
        auto opt_header64 = (PIMAGE_OPTIONAL_HEADER64)&(ntHeaders->OptionalHeader);
        imageBase = opt_header64->ImageBase;
        pImageDataDirectory = opt_header64->DataDirectory;
    }
    uintptr_t entryPoint =
        (uintptr_t)(imageBase + ntHeaders->OptionalHeader.AddressOfEntryPoint);
    if (address == entryPoint)
    {
        return "EntryPoint";
    }

    if (pImageDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
    {
        PIMAGE_EXPORT_DIRECTORY exportDirectory = 
            (PIMAGE_EXPORT_DIRECTORY)RVA2RAW((uint8_t*)pBase,
                pImageDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

        PDWORD exportAddresses = RVA2RAW((uint8_t*)pBase, exportDirectory->AddressOfFunctions);
        PDWORD exportNames = RVA2RAW((uint8_t*)pBase, exportDirectory->AddressOfNames);

        for (uint32_t i = 0; i < exportDirectory->NumberOfFunctions; ++i)
        {
            if (address == (uintptr_t)(imageBase + exportAddresses[i]))
            {
                auto exportName = RVA2RAW((uint8_t*)pBase, exportNames[i]);
                return (const char*)exportName;
            }
        }
    }
    return NULL;
}

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", (argc > 0 ? argv[0] : "ZydisPE"));
        return EXIT_FAILURE;
    }

    HANDLE hFile = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Failed to open file. Error code: %d\n", GetLastError());
        return EXIT_FAILURE;
    }
    HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL)
    {
        fprintf(stderr, "Failed to create file mapping. Error code: %d\n", GetLastError());
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }

    void* pBase = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);

    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)pBase;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        fprintf(stderr, "Invalid file signature\n");
        goto FatalError;
    }
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)pBase + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        fprintf(stderr, "Invalid file signature\n");
        goto FatalError;
    }

    bool isPE32 = ntHeaders->OptionalHeader.Magic == 0x10b;
    DWORD imageBase;

    if (isPE32) {
        PIMAGE_OPTIONAL_HEADER32 opt_header32 = (PIMAGE_OPTIONAL_HEADER32)&(ntHeaders->OptionalHeader);
        imageBase = opt_header32->ImageBase;
    }
    else {
        PIMAGE_OPTIONAL_HEADER64 opt_header64 = (PIMAGE_OPTIONAL_HEADER64)&(ntHeaders->OptionalHeader);
        imageBase = opt_header64->ImageBase;
    }

    ZydisDecoder decoder;
    ZydisMachineMode machineMode;
    ZydisAddressWidth addressWidth;

    switch (ntHeaders->FileHeader.Machine)
    {
    case IMAGE_FILE_MACHINE_I386:
        machineMode = ZYDIS_MACHINE_MODE_LONG_COMPAT_32;
        addressWidth = ZYDIS_ADDRESS_WIDTH_32;
        break;
    case IMAGE_FILE_MACHINE_IA64:
    case IMAGE_FILE_MACHINE_AMD64:
        machineMode = ZYDIS_MACHINE_MODE_LONG_64;
        addressWidth = ZYDIS_ADDRESS_WIDTH_64;
        break;
    default:
        fprintf(stderr, "Invalid assembly format\n");
        goto FatalError;
    }

    if (!ZYDIS_SUCCESS(ZydisDecoderInit(&decoder, machineMode, addressWidth))) {
        fprintf(stderr, "Failed to initialize decoder\n");
        goto FatalError;
    }

    ZydisFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL))) {
        fprintf(stderr, "Failed to initialize formatter\n");
        goto FatalError;
    }

    // Disassemble all executable PE-sections
    PIMAGE_SECTION_HEADER sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);

    for (int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
    {
        if (sectionHeader->SizeOfRawData == 0)
        {
            ++sectionHeader;
            continue;
        }
        if (!(sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE))
        {
            ++sectionHeader;
            continue;
        }

        uint8_t* data = (uint8_t*)pBase + sectionHeader->PointerToRawData;
        size_t offset = 0;
        size_t length = sectionHeader->SizeOfRawData;
        ZydisDecodedInstruction instruction;

        DWORD instructionPointer = imageBase + sectionHeader->VirtualAddress;

        while (ZYDIS_SUCCESS(ZydisDecoderDecodeBuffer(
            &decoder, data + offset, length - offset,
            uint64_t(instructionPointer + offset), &instruction)))
        {
            const char* symbol = GetExportName(pBase, instruction.instrAddress);
            if (symbol)
            {
                printf("\n%s:\n", symbol);
            }
            switch (instruction.machineMode)
            {
            case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
                printf("%08llX  ", instruction.instrAddress);
                break;
            case ZYDIS_MACHINE_MODE_LONG_64:
                printf("%08llX  ", instruction.instrAddress);
                break;
            default:
                break;
            }
            for (int j = 0; j < instruction.length; ++j)
            {
                printf("%02X ", instruction.data[j]);
            }
            for (int j = instruction.length; j < 15; ++j)
            {
                printf("   ");
            }

            CHAR buffer[256];
            ZydisFormatterFormatInstruction(
                &formatter, &instruction, buffer, sizeof(buffer));
            printf(" %s\n", buffer);

            offset += instruction.length;
        }
        ++sectionHeader;
    }


FatalError:
    UnmapViewOfFile(hMapping);
    CloseHandle(hMapping);
    CloseHandle(hFile);

    return EXIT_FAILURE;
}
