/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Joel Hoener

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

typedef struct ZydisFuzzControlBlock_
{
    ZydisMachineMode machineMode;
    ZydisAddressWidth addressWidth;
    ZydisBool decoderMode[ZYDIS_DECODER_MODE_MAX_VALUE + 1];
    ZydisFormatterStyle formatterStyle;
    uintptr_t formatterProperties[ZYDIS_FORMATTER_PROP_MAX_VALUE + 1];
    char* string[16];
} ZydisFuzzControlBlock;

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int doIteration();

int main()
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        fputs("Invalid zydis version\n", stderr);
        return EXIT_FAILURE;
    }

#ifdef ZYDIS_FUZZ_AFL_FAST
    int finalRet;
    while (__AFL_LOOP(1000))
    {
        finalRet = doIteration();
    }
    return finalRet;
#else
    return doIteration();
#endif
}

#ifdef ZYDIS_FUZZ_AFL_FAST
#   define ZYDIS_MAYBE_FPUTS(x, y)
#else
#   define ZYDIS_MAYBE_FPUTS(x, y) fputs(x, y)
#endif

int doIteration()
{
    ZydisFuzzControlBlock controlBlock;
    if (fread(&controlBlock, 1, sizeof(controlBlock), stdin) != sizeof(controlBlock))
    {
        ZYDIS_MAYBE_FPUTS("not enough bytes to fuzz\n", stderr);
        return EXIT_FAILURE;
    }
    controlBlock.string[ZYDIS_ARRAY_SIZE(controlBlock.string) - 1] = 0;

    ZydisDecoder decoder;
    if (!ZYDIS_SUCCESS(
        ZydisDecoderInit(&decoder, controlBlock.machineMode, controlBlock.addressWidth)))
    {
        ZYDIS_MAYBE_FPUTS("Failed to initialize decoder\n", stderr);
        return EXIT_FAILURE;
    }
    for (ZydisDecoderMode mode = 0; mode <= ZYDIS_DECODER_MODE_MAX_VALUE; ++mode)
    {
        if (!ZYDIS_SUCCESS(
            ZydisDecoderEnableMode(&decoder, mode, controlBlock.decoderMode[mode] ? 1 : 0)))
        {
            ZYDIS_MAYBE_FPUTS("Failed to adjust decoder-mode\n", stderr);
            return EXIT_FAILURE;
        }
    }

    ZydisFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInit(&formatter, controlBlock.formatterStyle)))
    {
        ZYDIS_MAYBE_FPUTS("Failed to initialize instruction-formatter\n", stderr);
        return EXIT_FAILURE;
    }
    for (ZydisFormatterProperty prop = 0; prop <= ZYDIS_FORMATTER_PROP_MAX_VALUE; ++prop)
    {
        switch (prop)
        {
        case ZYDIS_FORMATTER_PROP_HEX_PREFIX:
        case ZYDIS_FORMATTER_PROP_HEX_SUFFIX:
            controlBlock.formatterProperties[prop] =
                controlBlock.formatterProperties[prop] ? (uintptr_t)&controlBlock.string : 0;
            break;
        default:
            break;
        }
        if (!ZYDIS_SUCCESS(ZydisFormatterSetProperty(&formatter, prop,
            controlBlock.formatterProperties[prop])))
        {
            ZYDIS_MAYBE_FPUTS("Failed to set formatter-attribute\n", stderr);
            return EXIT_FAILURE;
        }
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

    return EXIT_SUCCESS;
}

/* ============================================================================================== */

