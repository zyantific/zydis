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

/**
 * @file
 * @brief   Disassembles a given PE file.
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <Zydis/Zydis.h>

// TODO: Get rid of the `Windows.h` include

/* ============================================================================================== */
/* Status codes                                                                                   */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Module IDs                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   The zydis PE tool module id.
 */
#define ZYAN_MODULE_ZYDIS_PE    0x101

/* ---------------------------------------------------------------------------------------------- */
/* Status codes                                                                                   */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   The signature of the PE-files DOS header field is invalid.
 */
#define ZYDIS_STATUS_INVALID_DOS_SIGNATURE \
    ZYAN_MAKE_STATUS(1, ZYAN_MODULE_ZYDIS_PE, 0x00)

/**
 * @brief   The signature of the PE-files NT headers field is invalid.
 */
#define ZYDIS_STATUS_INVALID_NT_SIGNATURE \
    ZYAN_MAKE_STATUS(1, ZYAN_MODULE_ZYDIS_PE, 0x01)

/**
 * @brief   The architecture of the assembly code contained in the PE-file is not supported.
 */
#define ZYDIS_STATUS_UNSUPPORTED_ARCHITECTURE \
    ZYAN_MAKE_STATUS(1, ZYAN_MODULE_ZYDIS_PE, 0x02)

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Symbol lookup functions                                                                        */
/* ============================================================================================== */

/**
 * @brief   Returns the name of the symbol with the given `address` in the export table of the
 *          PE-file.
 *
 * @param   module_handle   The module handle of the mapped PE-file.
 * @param   symbol_address  The symbol address.
 * @param   symbol_name     A pointer to the `ZydisString` variable, that receives the name of the
 *                          export symbol.
 *
 * @return  A zyan status code.
 */
static ZyanStatus LookupExportName(HMODULE module_handle, ZyanUPointer symbol_address,
    ZydisString* symbol_name)
{
    ZYAN_ASSERT(module_handle);
    ZYAN_ASSERT(symbol_name);

    const IMAGE_DOS_HEADER* dos_header = (const IMAGE_DOS_HEADER*)module_handle;
    ZYAN_ASSERT(dos_header->e_magic == IMAGE_DOS_SIGNATURE);
    const IMAGE_NT_HEADERS* nt_headers =
        (const IMAGE_NT_HEADERS*)((ZyanU8*)dos_header + dos_header->e_lfanew);
    ZYAN_ASSERT(nt_headers->Signature == IMAGE_NT_SIGNATURE);

    const ZyanUPointer entry_point =
        (ZyanUPointer)((ZyanU8*)module_handle + nt_headers->OptionalHeader.AddressOfEntryPoint);
    if (symbol_address == entry_point)
    {
        return ZydisStringInit(symbol_name, (char*)"EntryPoint");
    }

    if (nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
    {
        const IMAGE_EXPORT_DIRECTORY* export_directory =
            (const IMAGE_EXPORT_DIRECTORY*)((ZyanU8*)module_handle +
                nt_headers->OptionalHeader.DataDirectory[
                    IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
        const DWORD* export_addresses =
            (const DWORD*)((ZyanU8*)module_handle +export_directory->AddressOfFunctions);
        const DWORD* export_names =
            (const DWORD*)((ZyanU8*)module_handle + export_directory->AddressOfNames);

        for (DWORD i = 0; i < export_directory->NumberOfFunctions; ++i)
        {
            if (symbol_address == (ZyanUPointer)module_handle + export_addresses[i])
            {
                return ZydisStringInit(symbol_name, (char*)module_handle + export_names[i]);
            }
        }
    }

    return ZYAN_STATUS_NOT_FOUND;
}

/**
 * @brief   Returns the name of the symbol with the given `address` in the import table of the
 *          PE-file.
 *
 * @param   module_handle   The module handle of the mapped PE-file.
 * @param   symbol_address  The symbol address.
 * @param   module_name     A pointer to the `ZydisString` variable, that receives the name of the
 *                          import module.
 * @param   symbol_name     A pointer to the `ZydisString` variable, that receives the name of the
 *                          import symbol.
 *
 * @return  A zyan status code.
 */
static ZyanStatus LookupImportName(HMODULE module_handle, ZyanU64 symbol_address,
    ZydisString* module_name, ZydisString* symbol_name)
{
    ZYAN_ASSERT(module_handle);
    ZYAN_ASSERT(module_name);
    ZYAN_ASSERT(symbol_name);

    const IMAGE_DOS_HEADER* dos_header = (const IMAGE_DOS_HEADER*)module_handle;
    ZYAN_ASSERT(dos_header->e_magic == IMAGE_DOS_SIGNATURE);
    const IMAGE_NT_HEADERS* nt_headers =
        (const IMAGE_NT_HEADERS*)((ZyanU8*)dos_header + dos_header->e_lfanew);
    ZYAN_ASSERT(nt_headers->Signature == IMAGE_NT_SIGNATURE);

    if (nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
    {
        PIMAGE_IMPORT_DESCRIPTOR descriptor =
            (PIMAGE_IMPORT_DESCRIPTOR)((ZyanU8*)module_handle +
                nt_headers->OptionalHeader.DataDirectory[
                    IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
        while (descriptor->OriginalFirstThunk)
        {
            ZYAN_CHECK(
                ZydisStringInit(module_name, (char*)((ZyanU8*)module_handle + descriptor->Name)));

            PIMAGE_THUNK_DATA originalThunk =
                (PIMAGE_THUNK_DATA)((ZyanU8*)module_handle + descriptor->OriginalFirstThunk);
            PIMAGE_THUNK_DATA thunk =
                (PIMAGE_THUNK_DATA)((ZyanU8*)module_handle + descriptor->FirstThunk);
            while (originalThunk->u1.ForwarderString)
            {
                if (!(originalThunk->u1.Ordinal & 0x80000000))
                {
                    if (symbol_address == (ZyanU64)&thunk->u1.Function)
                    {
                        const IMAGE_IMPORT_BY_NAME* import =
                            (const IMAGE_IMPORT_BY_NAME*)((ZyanU8*)module_handle +
                                originalThunk->u1.AddressOfData);
                        return ZydisStringInit(symbol_name, (char*)import->Name);
                    }
                }
                ++originalThunk;
                ++thunk;
            }
            ++descriptor;
        }
    }

    return ZYAN_STATUS_NOT_FOUND;
}

/* ============================================================================================== */
/* String functions                                                                               */
/* ============================================================================================== */

/**
 * @brief   Appends the symbol at the given `address` to a `ZydisString` instance.
 *
 * @param   string          The string to append to.
 * @param   module_handle   The module handle of the mapped PE-file.
 * @param   symbol_address  The symbol address.
 *
 * @return  A zyan status code.
 */
static ZyanStatus ZydisStringAppendPEExport(ZydisString* string, HMODULE module_handle,
    ZyanUPointer symbol_address)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(module_handle);

    ZydisString symbol_name;
    ZYAN_CHECK(LookupExportName(module_handle, symbol_address, &symbol_name));

    // Retrieve module filename (without path)
    char buffer[MAX_PATH];
    const DWORD len = GetModuleFileNameA(module_handle, &buffer[0], MAX_PATH);
    if (len == 0)
    {
        return ZYAN_STATUS_BAD_SYSTEMCALL;
    }
    int offset = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (buffer[i] == '\\')
        {
            offset = i + 1;
            break;
        }
    }
    ZydisString module_name;
    ZYAN_CHECK(ZydisStringInit(&module_name, &buffer[offset]));

    // Remove file-extension
    for (ZyanUSize i = module_name.length - 1; i >= 0; --i)
    {
        if (module_name.buffer[i] == '.')
        {
            module_name.length -= (module_name.length - i - 1);
            break;
        }
    }

    ZYAN_CHECK(ZydisStringAppendEx(string, &module_name, ZYDIS_LETTER_CASE_LOWER));
    return ZydisStringAppend(string, &symbol_name);
}

/**
 * @brief   Appends the symbol at the given `address` to a `ZydisString` instance.
 *
 * @param   string          The string to append to.
 * @param   module_handle   The module handle of the mapped PE-file.
 * @param   symbol_address  The symbol address.
 *
 * @return  A zyan status code.
 */
static ZyanStatus ZydisStringAppendPEImport(ZydisString* string, HMODULE module_handle,
    ZyanUPointer symbol_address)
{
    ZYAN_ASSERT(string);
    ZYAN_ASSERT(module_handle);

    ZydisString module_name;
    ZydisString symbol_name;
    ZYAN_CHECK(LookupImportName(module_handle, symbol_address, &module_name, &symbol_name));

    // Remove file-extension
    for (ZyanUSize i = module_name.length - 1; i >= 0; --i)
    {
        if (module_name.buffer[i] == '.')
        {
            module_name.length -= (module_name.length - i - 1);
            break;
        }
    }

    ZYAN_CHECK(ZydisStringAppendEx(string, &module_name, ZYDIS_LETTER_CASE_LOWER));
    return ZydisStringAppend(string, &symbol_name);
}

/* ============================================================================================== */
/* Enums and Types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Custom user data                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Custom user data struct for the formatter.
 */
typedef struct ZydisCustomUserData_
{
    /**
     * @brief   The module handle of the mapped PE-file.
     */
    HMODULE module_handle;
} ZydisCustomUserData;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Hook callbacks                                                                                 */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Address                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

ZydisFormatterAddressFunc default_print_address;

static ZyanStatus ZydisFormatterPrintAddress(const ZydisFormatter* formatter,
    ZydisString* string, ZydisFormatterContext* context, ZyanU64 address)
{
    const ZydisCustomUserData* data = (ZydisCustomUserData*)context->user_data;
    ZYAN_ASSERT(data);

    // Try to resolve and append export table symbol
    ZyanStatus status = ZydisStringAppendPEExport(string, data->module_handle, address);
    if (ZYAN_SUCCESS(status) || (status != ZYAN_STATUS_NOT_FOUND))
    {
        return status;
    }

    // Try to resolve and append import table symbol
    status = ZydisStringAppendPEImport(string, data->module_handle, address);
    if (ZYAN_SUCCESS(status) || (status != ZYAN_STATUS_NOT_FOUND))
    {
        return status;
    }

    // Default address printing
    return default_print_address(formatter, string, context, address);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Main disassemble function                                                                      */
/* ============================================================================================== */

/**
 * @brief   Disassembles a mapped PE-file and prints the output to `stdout`. Automatically resolves
 *          exports and imports.
 *
 * @brief   module_handle   The module handle of the mapped PE-file.
 */
static ZyanStatus DisassembleMappedPEFile(HMODULE module_handle)
{
    // Validate PE file
    const IMAGE_DOS_HEADER* dos_header = (const IMAGE_DOS_HEADER*)module_handle;
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
    {
        fputs("Invalid file signature (DOS header)\n", stderr);
        return ZYDIS_STATUS_INVALID_DOS_SIGNATURE;
    }

    const IMAGE_NT_HEADERS* nt_headers =
        (const IMAGE_NT_HEADERS*)((ZyanU8*)dos_header + dos_header->e_lfanew);
    if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
    {
        fputs("Invalid file signature (NT headers)\n", stderr);
        return ZYDIS_STATUS_INVALID_NT_SIGNATURE;
    }

    ZyanStatus status;

    // Initialize decoder
    ZydisMachineMode machine_mode;
    ZydisAddressWidth address_width;
    switch (nt_headers->FileHeader.Machine)
    {
    case IMAGE_FILE_MACHINE_I386:
        machine_mode  = ZYDIS_MACHINE_MODE_LONG_COMPAT_32;
        address_width = ZYDIS_ADDRESS_WIDTH_32;
        break;
    case IMAGE_FILE_MACHINE_IA64:
    case IMAGE_FILE_MACHINE_AMD64:
        machine_mode  = ZYDIS_MACHINE_MODE_LONG_64;
        address_width = ZYDIS_ADDRESS_WIDTH_64;
        break;
    default:
        fputs("Unsupported architecture\n", stderr);
        return ZYDIS_STATUS_UNSUPPORTED_ARCHITECTURE;
    }
    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS((status = ZydisDecoderInit(&decoder, machine_mode, address_width))))
    {
        fputs("Failed to initialize instruction-decoder\n", stderr);
        return status;
    }

    // Initialize formatter
    default_print_address = (ZydisFormatterAddressFunc)&ZydisFormatterPrintAddress;
    ZydisFormatter formatter;
    if (!ZYAN_SUCCESS((status = ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL))) ||
        !ZYAN_SUCCESS((status = ZydisFormatterSetProperty(&formatter,
            ZYDIS_FORMATTER_PROP_FORCE_MEMSEG, ZYAN_TRUE))) ||
        !ZYAN_SUCCESS((status = ZydisFormatterSetProperty(&formatter,
            ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE, ZYAN_TRUE))) ||
        !ZYAN_SUCCESS(status = ZydisFormatterSetHook(&formatter,
            ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS, (const void**)&default_print_address)))
    {
        fputs("Failed to initialize instruction-formatter\n", stderr);
        return status;
    }

    // Disassemble all executable PE-sections
    ZydisDecodedInstruction instruction;
    PIMAGE_SECTION_HEADER section_header =
        (PIMAGE_SECTION_HEADER)((ZyanU8*)nt_headers + sizeof(IMAGE_NT_HEADERS) -
            sizeof(IMAGE_OPTIONAL_HEADER) + nt_headers->FileHeader.SizeOfOptionalHeader);
    for (WORD i = 0; i < nt_headers->FileHeader.NumberOfSections; ++i)
    {
        if (!section_header->SizeOfRawData || !section_header->VirtualAddress)
        {
            continue;
        }
        if (!(section_header->Characteristics & IMAGE_SCN_CNT_CODE))
        {
            continue;
        }

        const ZyanU8*   buffer           = (ZyanU8*)dos_header + section_header->VirtualAddress;
        const ZyanUSize buffer_size      = section_header->SizeOfRawData;
        const ZyanUSize read_offset_base = (ZyanUPointer)dos_header +
            section_header->VirtualAddress;

        ZyanUSize read_offset = 0;
        while ((status = ZydisDecoderDecodeBuffer(&decoder, buffer + read_offset,
            buffer_size - read_offset, &instruction)) != ZYDIS_STATUS_NO_MORE_DATA)
        {
            const ZyanUPointer runtime_address = read_offset_base + read_offset;

            ZydisString symbol_name;
            if (ZYAN_SUCCESS(LookupExportName(module_handle, runtime_address, &symbol_name)))
            {
                printf("\n%s:\n", symbol_name.buffer);
            }

            switch (instruction.machine_mode)
            {
            case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
                printf("%08llX  ", runtime_address);
                break;
            case ZYDIS_MACHINE_MODE_LONG_64:
                printf("%016llX  ", runtime_address);
                break;
            default:
                ZYAN_UNREACHABLE;
            }
            for (int j = 0; j < instruction.length; ++j)
            {
                printf("%02X ", instruction.data[j]);
            }
            for (int j = instruction.length; j < 15; ++j)
            {
                printf("   ");
            }

            if (ZYAN_SUCCESS(status))
            {
                read_offset += instruction.length;

                ZydisCustomUserData user_data;
                user_data.module_handle = module_handle;
                char format_buffer[256];
                if (!ZYAN_SUCCESS((status = ZydisFormatterFormatInstructionEx(&formatter,
                    &instruction, format_buffer, sizeof(format_buffer), runtime_address,
                    &user_data))))
                {
                    fputs("Failed to format instruction\n", stderr);
                    return status;
                }
                printf(" %s\n", &format_buffer[0]);
            } else
            {
                ++read_offset;
                printf(" db %02x\n", instruction.data[0]);
            }
        }

        ++section_header;
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(int argc, char** argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", (argc > 0 ? argv[0] : "ZydisPE"));
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const HMODULE module_handle =
        LoadLibraryExA(argv[1], 0, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
    if (!module_handle)
    {
        fprintf(stderr, "Could not load PE file. Error code: %u\n", GetLastError());
        return ZYAN_STATUS_BAD_SYSTEMCALL;
    }

    const ZyanStatus status = DisassembleMappedPEFile(module_handle);

    FreeLibrary(module_handle);
    return status;
}

/* ============================================================================================== */
