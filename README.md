Zyan Disassembler Engine (Zydis) [![Build Status](https://travis-ci.org/zyantific/zyan-disassembler-engine.svg?branch=master)](https://travis-ci.org/zyantific/zyan-disassembler-engine)
================================

Fast and lightweight x86/x86-64 disassembler library.

## Features ##

- Supports all x86 and x86-64 (AMD64) General purpose and System instructions.
- Supported ISA extensions:
 - MMX, FPU (x87), AMD 3DNow
 - SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, AES,
 - AMD-V, INTEL-VMX, SMX
- Optimized for high performance
- Very small overhead compared to other common disassembler libraries (about 60KiB)
- Abstract formatter and symbol-resolver classes for custom syntax implementations.
 - Intel syntax is implemented by default
- Complete doxygen documentation

## Quick Example ##

The following example program uses Zydis to disassemble a given memory buffer and prints the output to the console.

```c++
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <Zydis.hpp>

int main()
{
    uint8_t data[] =
    {
        0x51, 0x8D, 0x45, 0xFF, 0x50, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 
        0x08, 0xFF, 0x15, 0xA0, 0xA5, 0x48, 0x76, 0x85, 0xC0, 0x0F, 
        0x88, 0xFC, 0xDA, 0x02, 0x00
    };

    Zydis::MemoryInput input(&data[0], sizeof(data));
    Zydis::InstructionInfo info;
    Zydis::InstructionDecoder decoder;
    decoder.setDisassemblerMode(Zydis::DisassemblerMode::M32BIT);
    decoder.setDataSource(&input);
    decoder.setInstructionPointer(0x00400000);
    Zydis::IntelInstructionFormatter formatter;

    while (decoder.decodeInstruction(info))
    {
        std::cout << std::hex << std::setw(8) << std::setfill('0') 
                  << std::uppercase << info.instrAddress << " "; 

        if (info.flags & Zydis::IF_ERROR_MASK)
        {
            std::cout << "db " << std::setw(2) 
                      << static_cast<int>(info.data[0]) 
                      << std::endl;    
        } 
        else
        {
            std::cout << formatter.formatInstruction(info) << std::endl;
        }
    }
}
```

## Sample Output ##

The above example program generates the following output:

```
00400000 push ecx
00400001 lea eax, [ebp-01]
00400004 push eax
00400005 push dword ptr [ebp+0C]
00400008 push dword ptr [ebp+08]
0040000B call dword ptr [7648A5A0]
00400011 test eax, eax
00400013 js 0042DB15
```

## Compilation ##

Zydis builds cleanly on most platforms without any external dependencies. You can use CMake to generate project files for your favorite C++14 compiler.

## Documentation ##

[The HTML Doxygen documentation](https://www.zyantific.com/doc/zydis/index.html) is automatically built from master every 12 hours.

## License ##

Zyan Disassembler Engine is licensed under the MIT License. Dependencies are under their respective licenses.
