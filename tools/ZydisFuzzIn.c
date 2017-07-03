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
    ZydisMachineMode machineMode;
    ZydisAddressWidth addressWidth;
    ZydisDecodeGranularity granularity;
    ZydisFormatterStyle formatterStyle;
    ZydisFormatterFlags formatterFlags;
    ZydisFormatterAddressFormat formatterAddrFormat;
    ZydisFormatterDisplacementFormat formatterDispFormat;
    ZydisFormatterImmediateFormat formatterImmFormat;
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

    ZydisInstructionDecoder decoder;
    if (!ZYDIS_SUCCESS(ZydisDecoderInitInstructionDecoderEx(
        &decoder, controlBlock.machineMode, controlBlock.addressWidth, controlBlock.granularity)))
    {
        fputs("Failed to initialize decoder\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisInstructionFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInitInstructionFormatterEx(&formatter,
        controlBlock.formatterStyle, controlBlock.formatterFlags, controlBlock.formatterAddrFormat,
        controlBlock.formatterDispFormat, controlBlock.formatterImmFormat)))
    {
        fputs("failed to initialize instruction-formatter\n", stderr);
        return EXIT_FAILURE;
    }

    uint8_t readBuf[ZYDIS_MAX_INSTRUCTION_LENGTH * 1024];
    size_t numBytesRead;
    do
    {
        numBytesRead = fread(readBuf, 1, sizeof(readBuf), stdin);

        ZydisDecodedInstruction instruction;
        ZydisStatus status;
        size_t readOffs = 0;
        while ((status = ZydisDecoderDecodeBuffer(&decoder, readBuf + readOffs, 
            numBytesRead - readOffs, readOffs, &instruction)) != ZYDIS_STATUS_NO_MORE_DATA)
        {
            if (!ZYDIS_SUCCESS(status))
            {
                ++readOffs;
                continue;
            }

            char printBuffer[256];
            ZydisFormatterFormatInstruction(
                &formatter, &instruction, printBuffer, sizeof(printBuffer));
            readOffs += instruction.length;
        }

        if (readOffs < sizeof(readBuf))
        {
            memmove(readBuf, readBuf + readOffs, sizeof(readBuf) - readOffs);
        }
    } while (numBytesRead == sizeof(readBuf));

    return 0;
}

/* ============================================================================================== */

