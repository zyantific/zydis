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
#include <tchar.h>
#include <iostream>
#include <stdint.h>
#include "Zydis.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
    uint8_t data[] =
    {
        0x90, 0xE9, 0x00, 0x00, 0x00, 0x00, 0xC3
    };
    Zydis::MemoryInput input(&data[0], sizeof(data));
    Zydis::InstructionInfo info;
    Zydis::InstructionDecoder decoder;
    decoder.setDisassemblerMode(Zydis::DisassemblerMode::M32BIT);
    decoder.setDataSource(&input);
    decoder.setInstructionPointer(0);
    Zydis::IntelInstructionFormatter formatter;
    while (decoder.decodeInstruction(info))
    {
        std::cout << formatter.formatInstruction(info) << std::endl;
    }
}
```

## Sample Output ##

The above example program generates the following output:

```
nop
jmp 00000006
ret
```

## Compilation ##

Zydis builds cleanly on most platforms without any external dependencies. You can use CMake to generate project files for your favorite C++14 compiler.

## Documentation ##

[The HTML Doxygen documentation](https://www.zyantific.com/doc/zydis/index.html) is automatically built from master every 12 hours.

## License ##

Zyan Disassembler Engine is licensed under the MIT License. Dependencies are under their respective licenses.
