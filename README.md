Zyan Disassembler Engine (Zydis)
================================

Fast and lightweight x86/x86-64 disassembler library.

## Features ##

- Supports all x86 and x86-64 (AMD64) general-purpose and system instructions.
- Supported ISA extensions:
 - FPU (x87), MMX
 - SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, SSE4A, AESNI
 - AVX, AVX2, AVX512BW, AVX512CD, AVX512DQ, AVX512ER, AVX512F, AVX512PF, AVX512VL
 - ADX, BMI1, BMI2, FMA, FMA4
 - ..
- Optimized for high performance
- No dynamic memory allocation
 - Perfect for kernel-mode drivers and embedded devices
- Very small file-size overhead compared to other common disassembler libraries
- Language bindings
 - C++, Delphi, Python, ..
- Complete doxygen documentation

## Quick Example ##

The following example program uses Zydis to disassemble a given memory buffer and prints the output to the console.

```C
#include <stdio.h>
#include <Zydis/Zydis.h>

int main()
{
    uint8_t data[] =
    {
        0x51, 0x8D, 0x45, 0xFF, 0x50, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 
        0x08, 0xFF, 0x15, 0xA0, 0xA5, 0x48, 0x76, 0x85, 0xC0, 0x0F, 
        0x88, 0xFC, 0xDA, 0x02, 0x00
    };

    ZydisMemoryInput input;
    ZydisInputInitMemoryInput(&input, &data, sizeof(data));

    ZydisInstructionDecoder decoder;
    ZydisDecoderInitInstructionDecoderEx(&decoder, ZYDIS_DISASSEMBLER_MODE_64BIT, 
        (ZydisCustomInput*)&input, ZYDIS_DECODER_FLAG_SKIP_DATA); 
    ZydisDecoderSetInstructionPointer(&decoder, 0x007FFFFFFF400000);

    ZydisInstructionFormatter formatter;
    ZydisFormatterInitInstructionFormatterEx(&formatter, 
        ZYDIS_FORMATTER_STYLE_INTEL, ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SEGMENT);
  
    ZydisInstructionInfo info;
    char buffer[256];
    while (ZYDIS_SUCCESS(ZydisDecoderDecodeNextInstruction(&decoder, &info)))
    {
        printf("%016llX  ", info.instrAddress);
        if (info.flags & ZYDIS_IFLAG_ERROR_MASK)
        {
            printf(" db %02x\n", info.data[0]);    
            continue;
        }
        ZydisFormatterFormatInstruction(&formatter, &info, &buffer[0], sizeof(buffer));  
        printf(" %s\n", &buffer[0]);
    }
}
```

## Sample Output ##

The above example program generates the following output:

```
007FFFFFFF400000   push rcx
007FFFFFFF400001   lea eax, dword ptr ss:[rbp-0x01]
007FFFFFFF400004   push rax
007FFFFFFF400005   push qword ptr ss:[rbp+0x0C]
007FFFFFFF400008   push qword ptr ss:[rbp+0x08]
007FFFFFFF40000B   call qword ptr ds:[0x008000007588A5B1]
007FFFFFFF400011   test eax, eax
007FFFFFFF400013   js 0x007FFFFFFF42DB15
```

## Compilation ##

Zydis builds cleanly on most platforms without any external dependencies. You can use CMake to generate project files for your favorite C99 compiler.

## License ##

Zyan Disassembler Engine is licensed under the MIT License. Dependencies are under their respective licenses.
