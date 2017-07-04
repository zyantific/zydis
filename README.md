# Zyan Disassembler Engine (Zydis)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Gitter](https://badges.gitter.im/zyantific/zyan-disassembler-engine.svg)](https://gitter.im/zyantific/zyan-disassembler-engine?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=body_badge)

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

    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);

    ZydisFormatter formatter;
    ZydisFormatterInitEx(&formatter, ZYDIS_FORMATTER_STYLE_INTEL,
        ZYDIS_FMTFLAG_FORCE_SEGMENTS | ZYDIS_FMTFLAG_FORCE_OPERANDSIZE,
        ZYDIS_FORMATTER_ADDR_ABSOLUTE, ZYDIS_FORMATTER_DISP_DEFAULT, ZYDIS_FORMATTER_IMM_DEFAULT);
  
    uint64_t instructionPointer = 0x007FFFFFFF400000;

    ZydisDecodedInstruction instruction;
    char buffer[256];
    while (ZYDIS_SUCCESS(
        ZydisDecoderDecodeBuffer(decoder, data, length, instructionPointer, &instruction)))
    {
        data += instruction.length;
        length -= instruction.length;
        instructionPointer += instruction.length;
        printf("%016" PRIX64 "  ", instruction.instrAddress);
        ZydisFormatterFormatInstruction(&formatter, &instruction, &buffer[0], sizeof(buffer));  
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
