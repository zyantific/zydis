/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

  Original Author : Florian Bernd, Joel Höner

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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <Zydis/Zydis.h>

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(int argc, char** argv)
{
    if (argc < 1 || argc > 2)
    {
        fprintf(stderr, "Usage: %s [input file]\n", (argc > 0 ? argv[0] : "ZydisDisasm"));
        return EXIT_FAILURE;
    }
    
    FILE* file = argc >= 2 ? fopen(argv[1], "rb") : stdin;
    if (!file)
    {
        fprintf(stderr, "Can not open file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    ZydisInstructionFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInitInstructionFormatterEx(&formatter,
        ZYDIS_FORMATTER_STYLE_INTEL, ZYDIS_FMTFLAG_FORCE_SEGMENTS | ZYDIS_FMTFLAG_FORCE_OPERANDSIZE,
        ZYDIS_FORMATTER_ADDR_ABSOLUTE, ZYDIS_FORMATTER_DISP_DEFAULT, ZYDIS_FORMATTER_IMM_DEFAULT)))
    {
        fputs("Failed to initialized instruction-formatter\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisInstructionDecoder decoder;
    if (!ZYDIS_SUCCESS(ZydisDecoderInitInstructionDecoder(&decoder, ZYDIS_DISASSEMBLER_MODE_64BIT)))
    {
        fputs("Failed to initialize instruction-decoder\n", stderr);
        return EXIT_FAILURE;
    }

    uint8_t readBuf[ZYDIS_MAX_INSTRUCTION_LENGTH];
    size_t numBytesRead;
    do
    {
        numBytesRead = fread(readBuf, 1, sizeof(readBuf), file);
    
        ZydisInstructionInfo info;
        ZydisStatus status;
        size_t readOffs = 0;
        while ((status = ZydisDecoderDecodeInstruction(
            &decoder, readBuf + readOffs, numBytesRead - readOffs, &info
        )) != ZYDIS_STATUS_NO_MORE_DATA)
        {
            if (!ZYDIS_SUCCESS(status))
            {
                ++decoder.instructionPointer;
                ++readOffs;
                printf("db %02X\n", info.data[0]);
                continue;
            }

            char printBuffer[256];
            ZydisFormatterFormatInstruction(&formatter, &info, printBuffer, sizeof(printBuffer));
            puts(printBuffer);
            readOffs += info.length;
        }
        
        if (readOffs < sizeof(readBuf))
        {
            memmove(readBuf, readBuf + readOffs, sizeof(readBuf) - readOffs);
        }
    } while (numBytesRead == sizeof(readBuf));

    return 0;
}

/* ============================================================================================== */
