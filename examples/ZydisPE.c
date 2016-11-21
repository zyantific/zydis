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

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <Zydis/Zydis.h>

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
static const char* GetExportName(HMODULE moduleHandle, uintptr_t address)
{
    if (!moduleHandle)
    {
        return NULL;
    }
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)moduleHandle;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        return NULL;
    }
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)dosHeader + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        return NULL;
    }
    uintptr_t entryPoint = 
        (uintptr_t)((uint8_t*)moduleHandle + ntHeaders->OptionalHeader.AddressOfEntryPoint);
    if (address == entryPoint)
    {
        return "EntryPoint";
    }
    if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
    {
        PIMAGE_EXPORT_DIRECTORY exportDirectory = 
            (PIMAGE_EXPORT_DIRECTORY)((uint8_t*)moduleHandle + 
                ntHeaders->OptionalHeader.DataDirectory[
                    IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
        PDWORD exportAddresses = 
            (PDWORD)((uint8_t*)moduleHandle +exportDirectory->AddressOfFunctions);
        PDWORD exportNames =
            (PDWORD)((uint8_t*)moduleHandle + exportDirectory->AddressOfNames);
 
        for (uint32_t i = 0; i < exportDirectory->NumberOfFunctions; ++i)
        {
            if (address == (uintptr_t)moduleHandle + exportAddresses[i])
            {
                return (const char*)moduleHandle + exportNames[i];     
            }
        }
    }
    return NULL;
}

/**
 * @brief   Inserts formatted text into the @c buffer at the given @c offset and increases the 
 *          @c offset by the length of the text.
 *
 * @param   buffer      A pointer to the target buffer.
 * @param   bufferLen   The length of the buffer.
 * @param   offset      A pointer to the buffer-offset.
 * @param   format      The format string.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisBufferAppendFormat(char* buffer, size_t bufferLen, size_t* offset, 
    const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    size_t n = bufferLen - *offset;
    int w = vsnprintf(&buffer[*offset], n, format, arglist);
    if ((w < 0) || ((size_t)w >= n))
    {
        va_end(arglist);
        return ZYDIS_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }
    *offset += (size_t)w;
    va_end(arglist);
    return ZYDIS_STATUS_SUCCESS;
}

/**
 * @brief   Inserts the name of the exported function at @c address into the @c buffer at the given
 *          @c offset and increases the @c offset by the length of the name.
 *
 * @param   buffer          A pointer to the target buffer.
 * @param   bufferLen       The length of the buffer.
 * @param   offset          A pointer to the buffer-offset.
 * @param   moduleHandle    The module handle.
 * @param   address         The function address.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisBufferAppendExport(char* buffer, size_t bufferLen, size_t* offset, 
    HMODULE moduleHandle, uintptr_t address)
{
    const char* exportName = GetExportName(moduleHandle, address);
    if (!exportName)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    char nameBuffer[MAX_PATH];
    DWORD l = GetModuleFileNameA(moduleHandle, &nameBuffer[0], MAX_PATH);
    if (l == 0)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    for (int i = l - 4; i >= 0; --i)
    {
        if (nameBuffer[i] == '\\')
        {
            memcpy(&nameBuffer[0], &nameBuffer[i + 1], l - i);
            nameBuffer[l - i - 4] = 0;
            break;
        }
    }
    return ZydisBufferAppendFormat(buffer, bufferLen, offset, "%s%s", &nameBuffer[0], exportName); 
}

/**
 * @brief   Inserts the name of the imported function at @c address into the @c buffer at the given
 *          @c offset and increases the @c offset by the length of the name.
 *
 * @param   buffer          A pointer to the target buffer.
 * @param   bufferLen       The length of the buffer.
 * @param   offset          A pointer to the buffer-offset.
 * @param   moduleHandle    The module handle.
 * @param   address         The function address.
 *
 * @return  A zydis status code.
 */
static ZydisStatus ZydisBufferAppendImport(char* buffer, size_t bufferLen, size_t* offset, 
    HMODULE moduleHandle, uintptr_t address)
{
    if (!moduleHandle)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)moduleHandle;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    }
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)dosHeader + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        return ZYDIS_STATUS_INVALID_PARAMETER;
    } 

    if (ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
    {
        PIMAGE_IMPORT_DESCRIPTOR descriptor = 
            (PIMAGE_IMPORT_DESCRIPTOR)((uint8_t*)moduleHandle + 
                ntHeaders->OptionalHeader.DataDirectory[
                    IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
        while (descriptor->OriginalFirstThunk)
        {
            const char* moduleName = (char*)((uint8_t*)moduleHandle + descriptor->Name);
            PIMAGE_THUNK_DATA originalThunk = 
                (PIMAGE_THUNK_DATA)((uint8_t*)moduleHandle + descriptor->OriginalFirstThunk);
            PIMAGE_THUNK_DATA thunk = 
                (PIMAGE_THUNK_DATA)((uint8_t*)moduleHandle + descriptor->FirstThunk);

            while (originalThunk->u1.ForwarderString)
            {
                if (!(originalThunk->u1.Ordinal & 0x80000000))
                {
                    if (address == (uintptr_t)&thunk->u1.Function)
                    {
                        PIMAGE_IMPORT_BY_NAME import = (PIMAGE_IMPORT_BY_NAME)
                            ((uint8_t*)moduleHandle + originalThunk->u1.AddressOfData); 
                        ZydisStatus status = 
                            ZydisBufferAppendFormat(buffer, bufferLen, offset, "%s", moduleName);
                        if (!ZYDIS_SUCCESS(status))
                        {
                            return status;
                        }
                        *offset -= 3;
                        buffer[*offset] = 0;
                        return ZydisBufferAppendFormat(buffer, bufferLen, offset, "%s", 
                            import->Name);
                    }
                }
                ++originalThunk;
                ++thunk;
            }
            ++descriptor;
        }
    }
    return 1337 + 1000;
}

/**
 * @brief   Defines the @c ZydisPESymbolResolver struct.
 */
typedef struct ZydisPESymbolResolver_
{
    ZydisCustomSymbolResolver resolver;
    HMODULE moduleHandle;
    char buffer[256];
} ZydisPESymbolResolver;

/**
 * @brief   The custom symbol resolver callback function.
 *
 * @param   context A pointer to the @c ZydisPESymbolResolver instance. 
 * @param   info    A pointer to the @c ZydisInstructionInfo struct. 
 * @param   operand A pointer to the @c ZydisOperandInfo struct.
 * @param   address The address.
 * @param   offset  A pointer to the memory that receives the optional symbol-offset.
 *
 * @return  The name of the resolved symbol or @c NULL, if no symbol was found at the given 
 *          @c address.
 */
static const char* ResolveSymbol(ZydisPESymbolResolver* context, const ZydisInstructionInfo* info, 
    const ZydisOperandInfo* operand, uint64_t address, int64_t* offset)
{
    (void)context;
    (void)info;
    (void)operand;
    (void)address;

    *offset = 0;   
    size_t bufferOffset = 0;
    if (ZYDIS_SUCCESS(ZydisBufferAppendExport(&context->buffer[0], sizeof(context->buffer), 
        &bufferOffset, context->moduleHandle, (uintptr_t)address)))
    {
        return &context->buffer[0];
    }
    if (ZYDIS_SUCCESS(ZydisBufferAppendImport(&context->buffer[0], sizeof(context->buffer), 
        &bufferOffset, context->moduleHandle, (uintptr_t)address)))
    {
        return &context->buffer[0]; 
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

    // Load PE file
    HMODULE hModule = LoadLibraryExA(argv[1], 0, LOAD_LIBRARY_AS_DATAFILE);
    if (!hModule)
    {
        fprintf(stderr, "Could not load PE file. Error code: %d\n", GetLastError());
        return EXIT_FAILURE;
    }
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        fprintf(stderr, "Invalid file signature\n");
        goto FatalError;
    }
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)dosHeader + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        fprintf(stderr, "Invalid file signature\n");
        goto FatalError;
    }

    // Determine disassembler-mode
    ZydisDisassemblerMode disassemblerMode;
    switch (ntHeaders->FileHeader.Machine)
    {
    case IMAGE_FILE_MACHINE_I386:
        disassemblerMode = ZYDIS_DISASSEMBLER_MODE_32BIT;
        break;
    case IMAGE_FILE_MACHINE_IA64:
    case IMAGE_FILE_MACHINE_AMD64:
        disassemblerMode = ZYDIS_DISASSEMBLER_MODE_64BIT;
        break;
    default:
        fprintf(stderr, "Invalid assembly format\n");
        goto FatalError;
    }

    ZydisMemoryInput input;
    ZydisInstructionDecoder decoder;
    if (!ZYDIS_SUCCESS(ZydisDecoderInitInstructionDecoderEx(&decoder, disassemblerMode, 
        (ZydisCustomInput*)&input, ZYDIS_DECODER_FLAG_SKIP_DATA))) 
    {
        fputs("Failed to initialize instruction-decoder\n", stderr);
        goto FatalError;
    }

    ZydisInstructionFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInitInstructionFormatterEx(&formatter,
        ZYDIS_FORMATTER_STYLE_INTEL, ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SIZE | 
        ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SEGMENT)))
    {
        fputs("Failed to initialize instruction-formatter\n", stderr);
        goto FatalError;
    }

    // Initialize custom symbol resolver
    ZydisPESymbolResolver resolver;
    resolver.resolver.resolveSymbol = (ZydisResolverResolveSymbolFunc)&ResolveSymbol;
    resolver.moduleHandle = hModule;
    ZydisFormatterSetSymbolResolver(&formatter, (ZydisCustomSymbolResolver*)&resolver);

    LARGE_INTEGER frequency;       
    LARGE_INTEGER t1, t2;          
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t1);

    // Disassemble all executable PE-sections
    PIMAGE_SECTION_HEADER sectionHeader = (PIMAGE_SECTION_HEADER)((uint8_t*)ntHeaders + 
        sizeof(IMAGE_NT_HEADERS) - sizeof(IMAGE_OPTIONAL_HEADER) + 
        ntHeaders->FileHeader.SizeOfOptionalHeader);
    for (int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i)
    {
        if (sectionHeader->SizeOfRawData == 0)
        {
            continue;
        }
        if (!(sectionHeader->Characteristics & IMAGE_SCN_CNT_CODE))
        {
            continue;
        }
        void* data = (void*)((uint8_t*)dosHeader + sectionHeader->VirtualAddress);
        if (!ZYDIS_SUCCESS(ZydisDecoderSetInstructionPointer(&decoder, (uint64_t)data)))
        {
            fputs("Failed to set instruction-pointer\n", stderr);
            goto FatalError;
        }
        if (!ZYDIS_SUCCESS(ZydisInputInitMemoryInput(&input, data, sectionHeader->SizeOfRawData)))
        {
            fputs("Failed to initialize memory-input\n", stderr);
            goto FatalError;
        }
        char buffer[256];
        ZydisInstructionInfo info;
        while (ZYDIS_SUCCESS(ZydisDecoderDecodeNextInstruction(&decoder, &info)))
        {
            const char* symbol = GetExportName(hModule, (uintptr_t)info.instrAddress);
            if (symbol)
            {
                printf("\n%s:\n", symbol);
            }
            switch (info.mode)
            {
            case ZYDIS_DISASSEMBLER_MODE_16BIT:
            case ZYDIS_DISASSEMBLER_MODE_32BIT:
                printf("%08llX  ", info.instrAddress);
                break;
            case ZYDIS_DISASSEMBLER_MODE_64BIT:
                printf("%016llX  ", info.instrAddress);
                break;
            default:
                break;
            }
            for (int j = 0; j < info.length; ++j)
            {
                printf("%02X ", info.data[j]);    
            }
            for (int j = info.length; j < 15; ++j)
            {
                printf("   ");    
            }
            if (info.instrFlags & ZYDIS_INSTRFLAG_ERROR_MASK)
            {
                printf(" db %02x\n", info.data[0]);    
                continue;
            }

            if (!ZYDIS_SUCCESS(ZydisFormatterFormatInstruction(&formatter, &info, &buffer[0], 
                sizeof(buffer))))
            {
                fputs("Failed to format decoded instruction\n", stderr);
                goto FatalError;
            }
            printf(" %s\n", &buffer[0]);    
        }
        ++sectionHeader;
    }

    QueryPerformanceCounter(&t2);
    double elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    printf("\n%f", elapsedTime);

    return EXIT_SUCCESS;

FatalError:
    FreeLibrary(hModule);
    return EXIT_FAILURE;
}

/* ============================================================================================== */
