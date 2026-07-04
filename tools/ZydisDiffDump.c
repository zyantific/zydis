/* Differential decode dumper. Decodes an input file at EVERY byte offset in a fixed set of
 * decoder configurations and emits per-block FNV-1a hashes of the full decode results.
 * Two builds of this tool over the same input must produce identical output. */

#include <Zydis/Zydis.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Config_
{
    const char* name;
    ZydisMachineMode machine_mode;
    ZydisStackWidth stack_width;
    ZydisDecoderMode extra_mode; // ZYDIS_DECODER_MODE_MAX_VALUE + 1 == none
} Config;

static const Config CONFIGS[] =
{
    { "long64",     ZYDIS_MACHINE_MODE_LONG_64,   ZYDIS_STACK_WIDTH_64, ZYDIS_DECODER_MODE_MAX_VALUE + 1 },
    { "legacy32",   ZYDIS_MACHINE_MODE_LEGACY_32, ZYDIS_STACK_WIDTH_32, ZYDIS_DECODER_MODE_MAX_VALUE + 1 },
    { "legacy16",   ZYDIS_MACHINE_MODE_LEGACY_16, ZYDIS_STACK_WIDTH_16, ZYDIS_DECODER_MODE_MAX_VALUE + 1 },
    { "long64apx",  ZYDIS_MACHINE_MODE_LONG_64,   ZYDIS_STACK_WIDTH_64, ZYDIS_DECODER_MODE_APX },
    { "long64knc",  ZYDIS_MACHINE_MODE_LONG_64,   ZYDIS_STACK_WIDTH_64, ZYDIS_DECODER_MODE_KNC },
};

static ZyanU64 FnvUpdate(ZyanU64 hash, const void* data, ZyanUSize size)
{
    const ZyanU8* bytes = (const ZyanU8*)data;
    for (ZyanUSize i = 0; i < size; ++i)
    {
        hash = (hash ^ bytes[i]) * 0x100000001B3;
    }
    return hash;
}

static int LoadFile(const char* path, ZyanU8** buffer, ZyanUSize* size)
{
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("fopen");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    const long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    *buffer = (ZyanU8*)malloc((size_t)file_size);
    if (fread(*buffer, 1, (size_t)file_size, file) != (size_t)file_size)
    {
        fclose(file);
        return 1;
    }
    fclose(file);
    *size = (ZyanUSize)file_size;
    return 0;
}

static int CmdGen(const char* path, unsigned mib)
{
    // Deterministic xorshift64 stream so both builds hash the exact same corpus.
    FILE* file = fopen(path, "wb");
    if (!file)
    {
        perror("fopen");
        return 1;
    }
    ZyanU64 x = 0x9E3779B97F4A7C15;
    for (ZyanU64 i = 0; i < (ZyanU64)mib * 1024 * 1024 / 8; ++i)
    {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        fwrite(&x, 8, 1, file);
    }
    fclose(file);
    return 0;
}

static int CmdDump(const char* path, ZyanI64 detail_start, ZyanI64 detail_end)
{
    ZyanU8* buffer;
    ZyanUSize size;
    if (LoadFile(path, &buffer, &size))
    {
        return 1;
    }

    for (ZyanUSize c = 0; c < ZYAN_ARRAY_LENGTH(CONFIGS); ++c)
    {
        ZydisDecoder decoder;
        ZydisDecoderInit(&decoder, CONFIGS[c].machine_mode, CONFIGS[c].stack_width);
        if (CONFIGS[c].extra_mode <= ZYDIS_DECODER_MODE_MAX_VALUE)
        {
            ZydisDecoderEnableMode(&decoder, CONFIGS[c].extra_mode, ZYAN_TRUE);
        }

        ZyanU64 block_hash = 0xCBF29CE484222325;
        for (ZyanUSize offset = 0; offset < size; ++offset)
        {
            ZydisDecodedInstruction instruction;
            ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
            ZydisDecoderContext context;
            const ZyanStatus status = ZydisDecoderDecodeInstruction(&decoder, &context,
                buffer + offset, size - offset, &instruction);
            ZyanU64 entry_hash = 0xCBF29CE484222325;
            entry_hash = FnvUpdate(entry_hash, &status, sizeof(status));
            if (ZYAN_SUCCESS(status))
            {
                // The struct embeds pointers into static tables (cpu_flags/fpu_flags);
                // hash the pointed-to content and null the pointers so the dump is
                // comparable across different binaries.
                ZydisDecodedInstruction insn_copy = instruction;
                if (insn_copy.cpu_flags)
                {
                    entry_hash = FnvUpdate(entry_hash, insn_copy.cpu_flags,
                        sizeof(*insn_copy.cpu_flags));
                }
                if (insn_copy.fpu_flags)
                {
                    entry_hash = FnvUpdate(entry_hash, insn_copy.fpu_flags,
                        sizeof(*insn_copy.fpu_flags));
                }
                insn_copy.cpu_flags = ZYAN_NULL;
                insn_copy.fpu_flags = ZYAN_NULL;
                entry_hash = FnvUpdate(entry_hash, &insn_copy, sizeof(insn_copy));
                const ZyanStatus op_status = ZydisDecoderDecodeOperands(&decoder, &context,
                    &instruction, operands, instruction.operand_count);
                entry_hash = FnvUpdate(entry_hash, &op_status, sizeof(op_status));
                if (ZYAN_SUCCESS(op_status))
                {
                    entry_hash = FnvUpdate(entry_hash, operands,
                        instruction.operand_count * sizeof(operands[0]));
                }
            }
            if ((detail_start >= 0) && ((ZyanI64)offset >= detail_start) &&
                ((ZyanI64)offset < detail_end))
            {
                printf("%s %08" PRIX64 " %08X %016" PRIX64 "\n", CONFIGS[c].name,
                    (ZyanU64)offset, status, entry_hash);
            }
            block_hash = FnvUpdate(block_hash, &entry_hash, sizeof(entry_hash));
            if (((offset + 1) % 65536 == 0) || (offset + 1 == size))
            {
                printf("%s block %08" PRIX64 " %016" PRIX64 "\n", CONFIGS[c].name,
                    (ZyanU64)(offset / 65536), block_hash);
                block_hash = 0xCBF29CE484222325;
            }
        }
    }

    free(buffer);
    return 0;
}

static int CmdBench(const char* path)
{
    ZyanU8* buffer;
    ZyanUSize size;
    if (LoadFile(path, &buffer, &size))
    {
        return 1;
    }

    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    for (int full = 0; full < 2; ++full)
    {
        ZyanU64 total = 0;
        struct timespec ts0, ts1;
        clock_gettime(CLOCK_MONOTONIC, &ts0);
        for (int round = 0; round < 100; ++round)
        {
            ZyanUSize offset = 0;
            while (offset < size)
            {
                ZydisDecodedInstruction instruction;
                ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
                ZydisDecoderContext context;
                if (ZYAN_SUCCESS(ZydisDecoderDecodeInstruction(&decoder, &context,
                    buffer + offset, size - offset, &instruction)))
                {
                    if (full)
                    {
                        ZydisDecoderDecodeOperands(&decoder, &context, &instruction, operands,
                            instruction.operand_count);
                    }
                    offset += instruction.length;
                    ++total;
                }
                else
                {
                    ++offset;
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &ts1);
        const double seconds = (double)(ts1.tv_sec - ts0.tv_sec) +
            (double)(ts1.tv_nsec - ts0.tv_nsec) * 1e-9;
        printf("%-6s %6.2f ns/instr (%.2f Mi instr/s)\n", full ? "full" : "instr",
            seconds / (double)total * 1e9, (double)total / seconds / 1048576.0);
    }

    free(buffer);
    return 0;
}

int main(int argc, char** argv)
{
    if ((argc >= 4) && !strcmp(argv[1], "gen"))
    {
        return CmdGen(argv[2], (unsigned)atoi(argv[3]));
    }
    if ((argc >= 3) && !strcmp(argv[1], "dump"))
    {
        const ZyanI64 start = (argc >= 5) ? strtoll(argv[3], ZYAN_NULL, 0) : -1;
        const ZyanI64 end = (argc >= 5) ? strtoll(argv[4], ZYAN_NULL, 0) : -1;
        return CmdDump(argv[2], start, end);
    }
    if ((argc >= 3) && !strcmp(argv[1], "bench"))
    {
        return CmdBench(argv[2]);
    }
    fprintf(stderr, "usage: %s gen <file> <MiB> | dump <file> [start end] | bench <file>\n",
        argv[0]);
    return 1;
}
