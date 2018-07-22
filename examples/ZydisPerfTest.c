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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <Zydis/Zydis.h>
#include <inttypes.h>

#if defined(ZYDIS_WINDOWS)
#   include <Windows.h>
#elif defined(ZYDIS_APPLE)
#   include <mach/mach_time.h>
#elif defined(ZYDIS_LINUX)
#   include <sys/time.h>
#   include <pthread.h>
#elif defined(ZYDIS_FREEBSD)
#   include <sys/time.h>
#   include <pthread.h>
#   include <pthread_np.h>
#else
#   error "Unsupported platform detected"
#endif

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Time measurement                                                                               */
/* ---------------------------------------------------------------------------------------------- */

#if defined(ZYDIS_WINDOWS)
double   CounterFreq  = 0.0;
uint64_t CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
    {
        fputs("Error: QueryPerformanceFrequency failed!\n", stderr);
    }
    CounterFreq = (double)li.QuadPart / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - CounterStart) / CounterFreq;
}
#elif defined(ZYDIS_APPLE)
uint64_t counterStart = 0;
mach_timebase_info_data_t timebaseInfo;

void StartCounter()
{
    counterStart = mach_absolute_time();
}

double GetCounter()
{
    uint64_t elapsed = mach_absolute_time() - counterStart;

    if (timebaseInfo.denom == 0)
    {
        mach_timebase_info(&timebaseInfo);
    }

    return (double)elapsed * timebaseInfo.numer / timebaseInfo.denom / 1000000;
}
#elif defined(ZYDIS_LINUX) || defined(ZYDIS_FREEBSD)
struct timeval t1;

void StartCounter()
{
    gettimeofday(&t1, NULL);
}

double GetCounter()
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

void adjustProcessAndThreadPriority()
{
#ifdef ZYDIS_WINDOWS
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
#if defined(ZYDIS_LINUX)
    pthread_t thread = pthread_self();
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    pthread_setaffinity_np(thread, sizeof(cpus), &cpus);
#elif defined(ZYDIS_FREEBSD)
    pthread_t thread = pthread_self();
    cpuset_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    pthread_setaffinity_np(thread, sizeof(cpus), &cpus);
#endif
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Internal functions                                                                             */
/* ============================================================================================== */

uint64_t processBuffer(const char* buffer, size_t length, ZydisBool minimalMode, ZydisBool format)
{
    ZydisDecoder decoder;
    if (!ZYDIS_SUCCESS(
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64)))
    {
        fputs("Failed to initialize decoder\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!ZYDIS_SUCCESS(
        ZydisDecoderEnableMode(&decoder, ZYDIS_DECODER_MODE_MINIMAL, minimalMode)))
    {
        fputs("Failed to adjust decoder-mode\n", stderr);
        exit(EXIT_FAILURE);
    }

    ZydisFormatter formatter;
    if (format)
    {
        if (!ZYDIS_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL)) ||
            !ZYDIS_SUCCESS(ZydisFormatterSetProperty(&formatter,
                ZYDIS_FORMATTER_PROP_FORCE_MEMSEG, ZYDIS_TRUE)) ||
            !ZYDIS_SUCCESS(ZydisFormatterSetProperty(&formatter,
                ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE, ZYDIS_TRUE)))
        {
            fputs("Failed to initialize instruction-formatter\n", stderr);
            exit(EXIT_FAILURE);
        }
    }

    uint64_t count = 0;
    size_t offset = 0;
    ZydisStatus status;
    ZydisDecodedInstruction instruction;
    char formatBuffer[256];
    while ((status = ZydisDecoderDecodeBuffer(&decoder, buffer + offset, length - offset, offset,
        &instruction)) != ZYDIS_STATUS_NO_MORE_DATA)
    {
        ZYDIS_ASSERT(ZYDIS_SUCCESS(status));
        if (!ZYDIS_SUCCESS(status))
        {
            fputs("Unexpected decoding error\n", stderr);
            exit(EXIT_FAILURE);
        }
        ++count;
        if (format)
        {
            ZydisFormatterFormatInstruction(
                &formatter, &instruction, formatBuffer, sizeof(formatBuffer));
        }
        offset += instruction.length;
    }

    return count;
}

void testPerformance(const char* buffer, size_t length, ZydisBool minimalMode, ZydisBool format)
{
    // Cache warmup
    processBuffer(buffer, length, minimalMode, format);

    // Testing
    uint64_t count = 0;
    StartCounter();
    for (uint8_t j = 0; j < 100; ++j)
    {
        count += processBuffer(buffer, length, minimalMode, format);
    }
    printf("Minimal-Mode %d, Formatting %d, Instructions: %6.2fM, Time: %8.2f msec\n",
        minimalMode, format, (double)count / 1000000, GetCounter());
}

void generateTestData(FILE* file, uint8_t encoding)
{
    ZydisDecoder decoder;
    if (!ZYDIS_SUCCESS(
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64)))
    {
        fputs("Failed to initialize decoder\n", stderr);
        exit(EXIT_FAILURE);
    }

    uint8_t last = 0;
    uint32_t count = 0;
    ZydisDecodedInstruction instruction;
    while (count < 100000)
    {
        uint8_t data[ZYDIS_MAX_INSTRUCTION_LENGTH];
        for (int i = 0; i < ZYDIS_MAX_INSTRUCTION_LENGTH; ++i)
        {
            data[i] = rand() % 256;
        }
        const uint8_t offset = rand() % (ZYDIS_MAX_INSTRUCTION_LENGTH - 2);
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
            ZYDIS_UNREACHABLE;
        }
        if (ZYDIS_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, data, sizeof(data), 0, &instruction)))
        {
            ZydisBool b = ZYDIS_FALSE;
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
                ZYDIS_UNREACHABLE;
            }
            if (b)
            {
                fwrite(&instruction.data[0], 1, instruction.length, file);
                ++count;

                const uint8_t p = (uint8_t)((double)count / 100000 * 100);
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

    ZydisBool generate = ZYDIS_FALSE;
    if (!strcmp(argv[1], "-generate"))
    {
        generate = ZYDIS_TRUE;
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
        adjustProcessAndThreadPriority();
    }

    for (uint8_t i = 0; i < ZYDIS_ARRAY_SIZE(tests); ++i)
    {
        FILE* file;

        const size_t len = strlen(directory);
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
            fprintf(stderr, "Can not open file \"%s\": %s\n", &buf[0], strerror(errno));
            continue;
        }

        if (generate)
        {
            printf("Generating %s ...\n", tests[i].encoding);
            generateTestData(file, i);
        } else
        {
            fseek(file, 0L, SEEK_END);
            const long length = ftell(file);
            void* buffer = malloc(length);
            if (!buffer)
            {
                fprintf(stderr,
                    "Failed to allocate %" PRIu64 " bytes on the heap", (uint64_t)length);
                goto NextFile2;
            }

            rewind(file);
            if (fread(buffer, 1, length, file) != (size_t)length)
            {
                fprintf(stderr,
                    "Could not read %" PRIu64 " bytes from file \"%s\"", (uint64_t)length, &buf[0]);
                goto NextFile1;
            }

            printf("Testing %s ...\n", tests[i].encoding);
            testPerformance(buffer, length, ZYDIS_TRUE , ZYDIS_FALSE);
            testPerformance(buffer, length, ZYDIS_FALSE, ZYDIS_FALSE);
            testPerformance(buffer, length, ZYDIS_FALSE, ZYDIS_TRUE );
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
