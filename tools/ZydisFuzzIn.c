/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

  Original Author : Joel Höner

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
 * 
 * This file implements a tool that is supposed to be fed as input for fuzzers like AFL,
 * reading a control block from stdin, allowing the fuzzer to reach every possible
 * code-path, testing any possible combination of disassembler configurations.
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <Zydis/Zydis.h>

typedef struct ZydisFuzzControlBlock_ {
    ZydisDisassemblerMode disasMode;
    ZydisDecoderFlags decoderFlags;  
    ZydisFormatterStyle formatterStyle;
    ZydisFormatterFlags formatterFlags;
    ZydisFormatterAddressFormat formatterAddrFormat;
    ZydisFormatterDisplacementFormat formatterDispFormat;
    ZydisFormatterImmediateFormat formatterImmFormat;
    uint8_t bufSize;
} ZydisFuzzControlBlock;

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main()
{
    ZydisFuzzControlBlock controlBlock;
    if (fread(&controlBlock, 1, sizeof(controlBlock), stdin) != sizeof(controlBlock))
    {
        fputs("not enough bytes to fuzz\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisFileInput input;
    if (!ZYDIS_SUCCESS(ZydisInputInitFileInput(&input, stdin)))
    {
        fputs("failed to initialize file-input\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisInstructionFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInitInstructionFormatterEx(&formatter,
        controlBlock.formatterStyle, controlBlock.formatterFlags, controlBlock.formatterAddrFormat,
        controlBlock.formatterDispFormat, controlBlock.formatterImmFormat)))
    {
        fputs("failed to initialized instruction-formatter\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisInstructionDecoder decoder;
    if (!ZYDIS_SUCCESS(ZydisDecoderInitInstructionDecoderEx(&decoder, controlBlock.disasMode, 
        (ZydisCustomInput*)&input, controlBlock.decoderFlags)))
    {
        fputs("Failed to initialize instruction-decoder\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisInstructionInfo info;
    char *outBuf = malloc(controlBlock.bufSize);
    while (ZYDIS_SUCCESS(ZydisDecoderDecodeNextInstruction(&decoder, &info)))
    {
        if (info.instrFlags & ZYDIS_INSTRFLAG_ERROR_MASK)
        {
            printf("db %02X\n", info.data[0]);
            continue;
        }

        ZydisFormatterFormatInstruction(&formatter, &info, outBuf, controlBlock.bufSize);
        puts(outBuf);
    }

    free(outBuf);
    return 0;
}

/* ============================================================================================== */

