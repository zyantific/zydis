![zydis logo](https://mainframe.pw/u/P94JAqY9XSDdPedv.svg?x)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Gitter](https://badges.gitter.im/zyantific/zyan-disassembler-engine.svg)](https://gitter.im/zyantific/zyan-disassembler-engine?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=body_badge) [![Build status](https://ci.appveyor.com/api/projects/status/2tad27q0b9v6qtga/branch/master?svg=true)](https://ci.appveyor.com/project/athre0z/zydis/branch/master)

Fast and lightweight x86/x86-64 disassembler library.

## Features

- Supports all x86 and x86-64 (AMD64) instructions.
- Supports pretty much all ISA extensions (list incomplete):
  - FPU (x87), MMX
  - SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, SSE4A, AESNI
  - AVX, AVX2, AVX512BW, AVX512CD, AVX512DQ, AVX512ER, AVX512F, AVX512PF, AVX512VL
  - ADX, BMI1, BMI2, FMA, FMA4
- Optimized for high performance
- No dynamic memory allocation ("malloc")
- Very small file-size overhead compared to other common disassembler libraries
- [Complete doxygen documentation](https://www.zyantific.com/doc/zydis/index.html)
- No dependencies on platform specific APIs
  - Should compile on any platform with a complete libc and CMake
  - Tested on Windows, macOS and Linux

## Roadmap

- Language bindings [v2.0 final]
- Tests [v2.0 final]
- Graphical editor for the instruction-database [v2.0 final]
- Implement CMake feature gates. Currently, everything is always included. [v2.0 final]
- Encoding support [v2.1]

## Quick Example

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

    // Initialize decoder context.
    ZydisDecoder decoder;
    ZydisDecoderInit(
        &decoder, 
        ZYDIS_MACHINE_MODE_LONG_64, 
        ZYDIS_ADDRESS_WIDTH_64);

    // Initialize formatter. Only required when you actually plan to
    // do instruction formatting ("disassembling"), like we do here.
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);
  
    // Loop over the instructions in our buffer.
    uint64_t instructionPointer = 0x007FFFFFFF400000;
    uint8_t* readPointer = data;
    size_t length = sizeof(data);
    ZydisDecodedInstruction instruction;
    while (ZYDIS_SUCCESS(ZydisDecoderDecodeBuffer(
        &decoder, readPointer, length, instructionPointer, &instruction)))
    {
        // Print current instruction pointer.
        printf("%016" PRIX64 "  ", instructionPointer);

        // Format & print the binary instruction 
        // structure to human readable format.
        char buffer[256];
        ZydisFormatterFormatInstruction(
            &formatter, &instruction, buffer, sizeof(buffer));
        puts(buffer);

        readPointer += instruction.length;
        length -= instruction.length;
        instructionPointer += instruction.length;
    }
}
```

## Sample Output

The above example program generates the following output:

```
007FFFFFFF400000   push rcx
007FFFFFFF400001   lea eax, [rbp-0x01]
007FFFFFFF400004   push rax
007FFFFFFF400005   push qword ptr [rbp+0x0C]
007FFFFFFF400008   push qword ptr [rbp+0x08]
007FFFFFFF40000B   call [0x008000007588A5B1]
007FFFFFFF400011   test eax, eax
007FFFFFFF400013   js 0x007FFFFFFF42DB15
```

## Compilation

Zydis builds cleanly on most platforms without any external dependencies. You can use CMake to generate project files for your favorite C99 compiler.

```bash
# Linux and OS X
git clone 'https://github.com/zyantific/zydis.git'
cd zydis
mkdir build && cd build
cmake ..
make
```

## `ZydisInfo` tool
![ZydisInfo](https://raw.githubusercontent.com/zyantific/zydis/master/assets/screenshots/ZydisInfo.png)

## Credits
- Intel (for open-sourcing [XED](https://github.com/intelxed/xed), allowing for automatic comparision of our tables against theirs, improving both)
- LLVM (for providing pretty solid instruction data as well)
- Christian Ludloff (http://sandpile.org, insanely helpful)
- [LekoArts](https://www.lekoarts.de/) (for creating the project logo)
- Our [contributors on GitHub](https://github.com/zyantific/zydis/graphs/contributors)

## License

Zydis is licensed under the MIT license.
