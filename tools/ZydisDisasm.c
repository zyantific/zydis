/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Florian Bernd, Joel Hoener

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
//#include "Zydis/Encoder.h"

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(int argc, char** argv)
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        fputs("Invalid zydis version\n", stderr);
        return EXIT_FAILURE;
    }

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

    ZydisDecoder decoder;
    if (!ZYDIS_SUCCESS(
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64)))
    {
        fputs("Failed to initialize decoder\n", stderr);
        return EXIT_FAILURE;
    }

    ZydisFormatter formatter;
    if (!ZYDIS_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL)) ||
        !ZYDIS_SUCCESS(ZydisFormatterSetProperty(&formatter,
            ZYDIS_FORMATTER_PROP_FORCE_MEMSEG, ZYDIS_TRUE)) ||
        !ZYDIS_SUCCESS(ZydisFormatterSetProperty(&formatter,
            ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE, ZYDIS_TRUE)))
    {
        fputs("Failed to initialized instruction-formatter\n", stderr);
        return EXIT_FAILURE;
    }

    uint8_t readBuf[ZYDIS_MAX_INSTRUCTION_LENGTH * 1024];
    size_t numBytesRead;
    do
    {
        numBytesRead = fread(readBuf, 1, sizeof(readBuf), file);

        ZydisDecodedInstruction instruction;
        ZydisStatus status;
        size_t readOffs = 0;
        while ((status = ZydisDecoderDecodeBuffer(&decoder, readBuf + readOffs,
            numBytesRead - readOffs, readOffs, &instruction)) != ZYDIS_STATUS_NO_MORE_DATA)
        {
            if (!ZYDIS_SUCCESS(status))
            {
                ++readOffs;
                printf("db %02X\n", instruction.data[0]);
                continue;
            }

            char printBuffer[256];
            ZydisFormatterFormatInstruction(
                &formatter, &instruction, printBuffer, sizeof(printBuffer));
            puts(printBuffer);

            // TODO: Remove
            // DEBUG CODE START
#if 0
            for (size_t i = 0; i < instruction.length; ++i)
            {
                printf("%02X ", *(readBuf + readOffs + i));
            }
            putchar('\n');

            ZydisEncoderRequest req;
            ZydisStatus transStatus = ZydisEncoderDecodedInstructionToRequest(
                &instruction, &req
            );
            (void)transStatus;
            ZYDIS_ASSERT(ZYDIS_SUCCESS(transStatus));

            uint8_t encBuffer[15];
            size_t encBufferSize = sizeof(encBuffer);
            ZydisStatus encStatus = ZydisEncoderEncodeInstruction(
                encBuffer, &encBufferSize, &req
            );
            (void)encStatus;
            ZYDIS_ASSERT(ZYDIS_SUCCESS(encStatus));
            for (size_t i = 0; i < encBufferSize; ++i)
            {
                printf("%02X ", encBuffer[i]);
            }
            putchar('\n');
            ZYDIS_ASSERT(encBufferSize == instruction.length);
            ZYDIS_ASSERT(!memcmp(encBuffer, readBuf + readOffs, encBufferSize));
#endif
            // DEBUG CODE END

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
