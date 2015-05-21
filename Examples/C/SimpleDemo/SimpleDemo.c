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

#include <ZydisAPI.h>

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void PrintZydisError()
{
    puts("Zydis error: ");
    switch (ZydisGetLastError())
    {
    case ZYDIS_ERROR_SUCCESS:
        puts("success");
        break;
    case ZYDIS_ERROR_UNKNOWN:
        puts("unknown error");
        break;
    case ZYDIS_ERROR_NOT_ENOUGH_MEMORY:
        puts("not enough memory");
        break;
    case ZYDIS_ERROR_INVALID_PARAMETER:
        puts("invalid parameter");
        break;
    }
}

int main()
{
    uint8_t data32[] =
    {
        0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x6A, 0xFE, 0x68, 0xD8, 0x18, 0x09, 0x77, 0x68, 0x85, 0xD2, 
        0x09, 0x77, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x50, 0x83, 0xEC, 0x14, 0x53, 0x56, 0x57, 
        0xA1, 0x68, 0xEE, 0x13, 0x77, 0x31, 0x45, 0xF8, 0x33, 0xC5, 0x50, 0x8D, 0x45, 0xF0, 0x64, 
        0xA3, 0x00, 0x00, 0x00, 0x00, 0x89, 0x65, 0xE8, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 
        0x8B, 0x5D, 0x08, 0xF6, 0xC3, 0x04, 0x0F, 0x85, 0x57, 0x74, 0x00, 0x00, 0x53, 0x6A, 0x00, 
        0xFF, 0x35, 0xA0, 0xE3, 0x13, 0x77, 0xFF, 0x15, 0x00, 0x10, 0x14, 0x77, 0x85, 0xC0, 0x0F, 
        0x84, 0xC6, 0x48, 0x04, 0x00, 0xC7, 0x45, 0x08, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xFC, 
        0xFE, 0xFF, 0xFF, 0xFF, 0x33, 0xC0, 0x8B, 0x4D, 0xF0, 0x64, 0x89, 0x0D, 0x00, 0x00, 0x00, 
        0x00, 0x59, 0x5F, 0x5E, 0x5B, 0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00
    };
    uint8_t data64[] =
    {
        0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18, 0x89, 0x4C, 0x24, 0x08, 0x57, 
        0x41, 0x54, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57, 0x48, 0x83, 0xEC, 0x40, 0x4C, 0x8B, 0xF2, 
        0x8B, 0xD9, 0x48, 0xC7, 0x44, 0x24, 0x20, 0x00, 0x00, 0x00, 0x00, 0x33, 0xF6, 0x48, 0x89, 
        0x74, 0x24, 0x30, 0x45, 0x33, 0xFF, 0xF7, 0xC1, 0x8D, 0xF0, 0xFF, 0xFF, 0x0F, 0x85, 0xAA, 
        0x53, 0x08, 0x00, 0xF6, 0xC1, 0x40, 0x8B, 0xFE, 0x41, 0xBD, 0x08, 0x00, 0x00, 0x00, 0x41, 
        0x0F, 0x45, 0xFD, 0xF6, 0xC1, 0x02, 0x48, 0x8B, 0x0D, 0x10, 0xD4, 0x0E, 0x00, 0x0F, 0x85, 
        0x40, 0xE1, 0x01, 0x00, 0x8B, 0x15, 0x4C, 0xD5, 0x0E, 0x00, 0x81, 0xC2, 0x00, 0x00, 0x14, 
        0x00, 0x0B, 0xD7, 0x4D, 0x8B, 0xC6, 0xFF, 0x15, 0x3B, 0x2F, 0x10, 0x00, 0x48, 0x8B, 0xD8, 
        0x48, 0x85, 0xC0, 0x0F, 0x84, 0x93, 0x78, 0x0A, 0x00, 0x48, 0x8B, 0xC3, 0x48, 0x8B, 0x5C, 
        0x24, 0x78, 0x48, 0x8B, 0xB4, 0x24, 0x80, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x40, 0x41, 
        0x5F, 0x41, 0x5E, 0x41, 0x5D, 0x41, 0x5C, 0x5F, 0xC3    
    };

    ZydisInstructionInfo info;
    ZydisInstructionDecoderContext* decoder = NULL;
    ZydisInstructionFormatterContext* formatter = NULL;
    ZydisInputContext* input32 = NULL;
    ZydisInputContext* input64 = NULL;

    // Create decoder and formatter instances
    decoder = ZydisCreateInstructionDecoder();
    if (!decoder)
    {
        goto ZydisError;
    }
    formatter = ZydisCreateIntelInstructionFormatter();
    if (!formatter)
    {
        goto FreeZydisDecoder;
    }

    // Create memory data sources
    input32 = ZydisCreateMemoryInput(&data32[0], sizeof(data32));
    if (!input32)
    {
        goto FreeZydisFormatter;
    }
    input64 = ZydisCreateMemoryInput(&data64[0], sizeof(data64));
    if (!input64)
    {
        goto FreeZydisInput32;
    }

    // Set decoder properties
    ZydisSetDisassemblerMode(decoder, ZYDIS_DM_M32BIT);
    ZydisSetDataSource(decoder, input32);
    ZydisSetInstructionPointer(decoder, 0x77091852);

    // Decode and format all instructions
    puts("32 bit test ...\n\n");
    while (ZydisDecodeInstruction(decoder, &info))
    {
        printf("%08X ", (uint32_t)(info.instrAddress & 0xFFFFFFFF));
        if (info.flags & ZYDIS_IF_ERROR_MASK)
        {
            printf("db %02X\n", info.data[0]);
        } 
        else
        {
            const char* instructionText;
            if (!ZydisFormatInstruction(formatter, &info, &instructionText))
            {
                goto FreeZydisInput64;
            }
            printf("%s\n", instructionText);
        }
    }
    // Check if an error occured in ZydisDecodeInstruction or the end of the input was reached.
    if (ZydisGetLastError() != ZYDIS_ERROR_SUCCESS)
    {
        goto FreeZydisInput64;
    }

    puts("\n");

    // Set decoder properties
    ZydisSetDisassemblerMode(decoder, ZYDIS_DM_M64BIT);
    ZydisSetDataSource(decoder, input64);
    ZydisSetInstructionPointer(decoder, 0x00007FFA39A81930ull);

    // Decode and format all instructions
    puts("64 bit test ...\n\n");
    while (ZydisDecodeInstruction(decoder, &info))
    {
        printf("%016"PRIX64" ", info.instrAddress); 
        if (info.flags & ZYDIS_IF_ERROR_MASK)
        {
            printf("db %02X", info.data[0]);
        } 
        else
        {
            const char* instructionText;
            if (!ZydisFormatInstruction(formatter, &info, &instructionText))
            {
                goto FreeZydisInput64;
            }
            printf("%s\n", instructionText);
        }
    } 
    // Check if an error occured in ZydisDecodeInstruction or the end of the input was reached.
    if (ZydisGetLastError() != ZYDIS_ERROR_SUCCESS)
    {
        goto FreeZydisInput64;
    }

    // Cleanup code
FreeZydisInput64:
    ZydisFreeInput(input64);
FreeZydisInput32:
    ZydisFreeInput(input32);
FreeZydisFormatter:
    ZydisFreeInstructionFormatter(formatter);
FreeZydisDecoder:
    ZydisFreeInstructionDecoder(decoder);
ZydisError:

    if (ZydisGetLastError() != ZYDIS_ERROR_SUCCESS)
    {
        PrintZydisError();
        getchar();
        return 1;
    }

    getchar();
    
    return 0;
}