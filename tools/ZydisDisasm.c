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

/**
 * @file
 * Reads a byte-stream from a file or the `stdin` pipe and prints a textual
 * representation of the decoded data.
 */

#include <stdio.h>
#include <Zycore/LibC.h>
#include <Zydis/Zydis.h>

#ifdef ZYAN_WINDOWS
#   include <fcntl.h>
#   include <io.h>
#endif

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(int argc, char** argv)
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        ZYAN_FPUTS("Invalid zydis version\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }

    if (argc < 2 || argc > 3)
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "Usage: %s -[real|16|32|64] [input file]\n",
            (argc > 0 ? argv[0] : "ZydisDisasm"));
        return EXIT_FAILURE;
    }

    ZydisDecoder decoder;
    if (!ZYAN_STRCMP(argv[1], "-real"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_REAL_16, ZYDIS_ADDRESS_WIDTH_16);
    } else
    if (!ZYAN_STRCMP(argv[1], "-16"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_16, ZYDIS_ADDRESS_WIDTH_16);
    } else
    if (!ZYAN_STRCMP(argv[1], "-32"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_ADDRESS_WIDTH_32);
    } else
    if (!ZYAN_STRCMP(argv[1], "-64"))
    {
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
    } else
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "Usage: %s -[real|16|32|64] [input file]\n",
            (argc > 0 ? argv[0] : "ZydisDisasm"));
        return EXIT_FAILURE;
    }

    FILE* file = (argc >= 3) ? fopen(argv[2], "rb") : ZYAN_STDIN;
    if (!file)
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "Can not open file: %s\n", strerror(ZYAN_ERRNO));
        return EXIT_FAILURE;
    }
#ifdef ZYAN_WINDOWS
    // The `stdin` pipe uses text-mode on Windows platforms by default. We need it to be opened in
    // binary mode
    if (file == ZYAN_STDIN)
    {
        _setmode(_fileno(ZYAN_STDIN), _O_BINARY);
    }
#endif

    ZydisFormatter formatter;
    if (!ZYAN_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL)) ||
        !ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter,
            ZYDIS_FORMATTER_PROP_FORCE_SEGMENT, ZYAN_TRUE)) ||
        !ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter,
            ZYDIS_FORMATTER_PROP_FORCE_SIZE, ZYAN_TRUE)))
    {
        ZYAN_FPUTS("Failed to initialized instruction-formatter\n", ZYAN_STDERR);
        return EXIT_FAILURE;
    }

    ZyanU8 buffer[1024];
    ZyanUSize buffer_size;
    ZyanUSize buffer_remaining = 0;
    ZyanUSize read_offset_base = 0;
    do
    {
        buffer_size = fread(buffer + buffer_remaining, 1, sizeof(buffer) - buffer_remaining, file);
        if (buffer_size != (sizeof(buffer) - buffer_remaining))
        {
            if (ferror(file))
            {
                return EXIT_FAILURE;
            }
            ZYAN_ASSERT(feof(file));
        }
        buffer_size += buffer_remaining;

        ZydisDecodedInstruction instruction;
        ZyanStatus status;
        ZyanUSize read_offset = 0;
        char format_buffer[256];

        while ((status = ZydisDecoderDecodeBuffer(&decoder, buffer + read_offset,
            buffer_size - read_offset, &instruction)) != ZYDIS_STATUS_NO_MORE_DATA)
        {
            const ZyanU64 runtime_address = read_offset_base + read_offset;

            if (!ZYAN_SUCCESS(status))
            {
                ZYAN_PRINTF("db %02X\n", buffer[read_offset++]);
                continue;
            }

            ZydisFormatterFormatInstruction(&formatter, &instruction, format_buffer,
                sizeof(format_buffer), runtime_address);
            ZYAN_PUTS(format_buffer);

            read_offset += instruction.length;
        }

        buffer_remaining = 0;
        if (read_offset < sizeof(buffer))
        {
            buffer_remaining = sizeof(buffer) - read_offset;
            memmove(buffer, buffer + read_offset, buffer_remaining);
        }
        read_offset_base += read_offset;
    } while (buffer_size == sizeof(buffer));

    return EXIT_SUCCESS;
}

/* ============================================================================================== */
