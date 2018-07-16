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

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <Zydis/Zydis.h>

#if defined(ZYAN_WINDOWS)
#   include <Windows.h>
#elif defined(ZYAN_APPLE)
#   include <mach/mach_time.h>
#elif defined(ZYAN_LINUX)
#   include <sys/time.h>
#   include <pthread.h>
#else
#   error "Unsupported platform detected"
#endif

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Time measurement                                                                               */
/* ---------------------------------------------------------------------------------------------- */

#if defined(ZYAN_WINDOWS)
double  counter_freq  = 0.0;
ZyanU64 counter_start = 0;

static void StartCounter(void)
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
    {
        fputs("Error: QueryPerformanceFrequency failed!\n", stderr);
    }
    counter_freq = (double)li.QuadPart / 1000.0;
    QueryPerformanceCounter(&li);
    counter_start = li.QuadPart;
}

static double GetCounter(void)
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - counter_start) / counter_freq;
}
#elif defined(ZYAN_APPLE)
ZyanU64 counter_start = 0;
mach_timebase_info_data_t timebase_info;

static void StartCounter(void)
{
    counter_start = mach_absolute_time();
}

static double GetCounter(void)
{
    ZyanU64 elapsed = mach_absolute_time() - counter_start;

    if (timebase_info.denom == 0)
    {
        mach_timebase_info(&timebase_info);
    }

    return (double)elapsed * timebase_info.numer / timebase_info.denom / 1000000;
}
#elif defined(ZYAN_LINUX)
struct timeval t1;

static void StartCounter(void)
{
    gettimeofday(&t1, NULL);
}

static double GetCounter(void)
{
    struct timeval t2;
    gettimeofday(&t2, NULL);

    double t = (t2.tv_sec - t1.tv_sec) * 1000.0;
    return t + (t2.tv_usec - t1.tv_usec) / 1000.0;
}
#endif

/* ---------------------------------------------------------------------------------------------- */
/* Process & Thread Priority                                                                      */
/* ---------------------------------------------------------------------------------------------- */

static void AdjustProcessAndThreadPriority(void)
{
#ifdef ZYAN_WINDOWS
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    if (info.dwNumberOfProcessors > 1)
    {
        if (!SetThreadAffinityMask(GetCurrentThread(), (DWORD_PTR)1))
        {
            fputs("Warning: Could not set thread affinity mask\n", stderr);
        }
        if (!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
        {
            fputs("Warning: Could not set process priority class\n", stderr);
        }
        if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL))
        {
            fputs("Warning: Could not set thread priority class\n", stderr);
        }
    }
#endif
#ifdef ZYAN_LINUX
    pthread_t thread = pthread_self();
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    pthread_setaffinity_np(thread, sizeof(cpus), &cpus);
#endif
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Internal functions                                                                             */
/* ============================================================================================== */

static ZyanU64 ProcessBuffer(const char* buffer, ZyanUSize length, ZyanBool minimalMode,
    ZyanBool format)
{
    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS(
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64)))
    {
        fputs("Failed to initialize decoder\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!ZYAN_SUCCESS(
        ZydisDecoderEnableMode(&decoder, ZYDIS_DECODER_MODE_MINIMAL, minimalMode)))
    {
        fputs("Failed to adjust decoder-mode\n", stderr);
        exit(EXIT_FAILURE);
    }

    ZydisFormatter formatter;
    if (format)
    {
        if (!ZYAN_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL)) ||
            !ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter,
                ZYDIS_FORMATTER_PROP_FORCE_MEMSEG, ZYAN_TRUE)) ||
            !ZYAN_SUCCESS(ZydisFormatterSetProperty(&formatter,
                ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE, ZYAN_TRUE)))
        {
            fputs("Failed to initialize instruction-formatter\n", stderr);
            exit(EXIT_FAILURE);
        }
    }

    ZyanU64 count = 0;
    ZyanUSize offset = 0;
    ZyanStatus status;
    ZydisDecodedInstruction instruction;
    char format_buffer[256];
    while ((status = ZydisDecoderDecodeBuffer(&decoder, buffer + offset, length - offset,
        &instruction)) != ZYDIS_STATUS_NO_MORE_DATA)
    {
        ZYAN_ASSERT(ZYAN_SUCCESS(status));
        if (!ZYAN_SUCCESS(status))
        {
            fputs("Unexpected decoding error\n", stderr);
            exit(EXIT_FAILURE);
        }
        ++count;
        if (format)
        {
            ZydisFormatterFormatInstruction(&formatter, &instruction, format_buffer,
                sizeof(format_buffer), offset);
        }
        offset += instruction.length;
    }

    return count;
}

static void TestPerformance(const char* buffer, ZyanUSize length, ZyanBool minimalMode,
    ZyanBool format)
{
    // Cache warmup
    ProcessBuffer(buffer, length, minimalMode, format);

    // Testing
    ZyanU64 count = 0;
    StartCounter();
    for (ZyanU8 j = 0; j < 100; ++j)
    {
        count += ProcessBuffer(buffer, length, minimalMode, format);
    }
    printf("Minimal-Mode %d, Formatting %d, Instructions: %6.2fM, Time: %8.2f msec\n",
        minimalMode, format, (double)count / 1000000, GetCounter());
}

static void GenerateTestData(FILE* file, ZyanU8 encoding)
{
    ZydisDecoder decoder;
    if (!ZYAN_SUCCESS(
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64)))
    {
        fputs("Failed to initialize decoder\n", stderr);
        exit(EXIT_FAILURE);
    }

    ZyanU8 last = 0;
    ZyanU32 count = 0;
    ZydisDecodedInstruction instruction;
    while (count < 100000)
    {
        ZyanU8 data[ZYDIS_MAX_INSTRUCTION_LENGTH];
        for (int i = 0; i < ZYDIS_MAX_INSTRUCTION_LENGTH; ++i)
        {
            data[i] = rand() % 256;
        }
        const ZyanU8 offset = rand() % (ZYDIS_MAX_INSTRUCTION_LENGTH - 2);
        switch (encoding)
        {
        case 0:
            break;
        case 1:
            data[offset    ] = 0x0F;
            data[offset + 1] = 0x0F;
            break;
        case 2:
            data[offset    ] = 0x8F;
            break;
        case 3:
            data[offset    ] = 0xC4;
            break;
        case 4:
            data[offset    ] = 0xC5;
            break;
        case 5:
        case 6:
            data[offset    ] = 0x62;
            break;
        default:
            ZYAN_UNREACHABLE;
        }
        if (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, data, sizeof(data), &instruction)))
        {
            ZyanBool b = ZYAN_FALSE;
            switch (encoding)
            {
            case 0:
                b = (instruction.encoding == ZYDIS_INSTRUCTION_ENCODING_DEFAULT);
                break;
            case 1:
                b = (instruction.encoding == ZYDIS_INSTRUCTION_ENCODING_3DNOW);
                break;
            case 2:
                b = (instruction.encoding == ZYDIS_INSTRUCTION_ENCODING_XOP);
                break;
            case 3:
            case 4:
                b = (instruction.encoding == ZYDIS_INSTRUCTION_ENCODING_VEX);
                break;
            case 5:
                b = (instruction.encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX);
                break;
            case 6:
                b = (instruction.encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX);
                break;
            default:
                ZYAN_UNREACHABLE;
            }
            if (b)
            {
                fwrite(&instruction.data[0], 1, instruction.length, file);
                ++count;

                const ZyanU8 p = (ZyanU8)((double)count / 100000 * 100);
                if (last < p)
                {
                    last = p;
                    printf("%3.0d%%\n", p);
                }

            }
        }
    }
}

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

    if (argc < 3 || (strcmp(argv[1], "-test") && strcmp(argv[1], "-generate")))
    {
        fputs("Usage: PerfTest -[test|generate] [directory]\n", stderr);
        return EXIT_FAILURE;
    }

    ZyanBool generate = ZYAN_FALSE;
    if (!strcmp(argv[1], "-generate"))
    {
        generate = ZYAN_TRUE;
    }
    const char* directory = argv[2];

    static const struct
    {
        const char* encoding;
        const char* filename;
    } tests[7] =
    {
        { "DEFAULT", "enc_default.dat" },
        { "3DNOW"  , "enc_3dnow.dat"   },
        { "XOP"    , "enc_xop.dat"     },
        { "VEX_C4" , "enc_vex_c4.dat"  },
        { "VEX_C5" , "enc_vex_c5.dat"  },
        { "EVEX"   , "enc_evex.dat"    },
        { "MVEX"   , "enc_mvex.dat"    }
    };

    if (generate)
    {
        time_t t;
        srand((unsigned)time(&t));
    } else
    {
        AdjustProcessAndThreadPriority();
    }

    for (ZyanU8 i = 0; i < ZYAN_ARRAY_LENGTH(tests); ++i)
    {
        FILE* file;

        const ZyanUSize len = strlen(directory);
        char buf[1024];
        strncpy(&buf[0], directory, sizeof(buf) - 1);
        if (generate)
        {
            file = fopen(strncat(buf, tests[i].filename, sizeof(buf) - len - 1), "wb");
        } else
        {
            file = fopen(strncat(buf, tests[i].filename, sizeof(buf) - len - 1), "rb");
        }
        if (!file)
        {
            fprintf(stderr, "Could not open file \"%s\": %s\n", &buf[0], strerror(errno));
            continue;
        }

        if (generate)
        {
            printf("Generating %s ...\n", tests[i].encoding);
            GenerateTestData(file, i);
        } else
        {
            fseek(file, 0L, SEEK_END);
            const long length = ftell(file);
            void* buffer = malloc(length);
            if (!buffer)
            {
                fprintf(stderr,
                    "Failed to allocate %" PRIu64 " bytes on the heap\n", (ZyanU64)length);
                goto NextFile2;
            }

            rewind(file);
            if (fread(buffer, 1, length, file) != (ZyanUSize)length)
            {
                fprintf(stderr,
                    "Could not read %" PRIu64 " bytes from file \"%s\"\n", (ZyanU64)length, &buf[0]);
                goto NextFile1;
            }

            printf("Testing %s ...\n", tests[i].encoding);
            TestPerformance(buffer, length, ZYAN_TRUE , ZYAN_FALSE);
            TestPerformance(buffer, length, ZYAN_FALSE, ZYAN_FALSE);
            TestPerformance(buffer, length, ZYAN_FALSE, ZYAN_TRUE );
            puts("");

        NextFile1:
            free(buffer);
        }

    NextFile2:
        fclose(file);
    }

    return 0;
}

/* ============================================================================================== */
