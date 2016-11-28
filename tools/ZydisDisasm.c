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
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", (argc > 0 ? argv[0] : "ZydisDisasm"));
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file)
    {
        fprintf(stderr, "Can not open file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    ZydisFileInput input;
    if (!ZYDIS_SUCCESS(ZydisInputInitFileInput(&input, file)))
    {
        fputs("Failed to initialize file-input\n", stderr);
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
    if (!ZYDIS_SUCCESS(ZydisDecoderInitInstructionDecoderEx(&decoder, ZYDIS_DISASSEMBLER_MODE_64BIT, 
        (ZydisCustomInput*)&input, ZYDIS_DECODER_FLAG_SKIP_DATA)))
    {
        fputs("Failed to initialize instruction-decoder\n", stderr);
        return EXIT_FAILURE;
    }

    char buffer[256];
    ZydisInstructionInfo info;
    while (ZYDIS_SUCCESS(ZydisDecoderDecodeNextInstruction(&decoder, &info)))
    {
        if (info.instrFlags & ZYDIS_INSTRFLAG_ERROR_MASK)
        {
            printf("db %02X\n", info.data[0]);
            continue;
        }

        ZydisFormatterFormatInstruction(&formatter, &info, buffer, sizeof(buffer));
        puts(buffer);
    }
}

/* ============================================================================================== */
