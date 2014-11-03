Verteron Disassembler Engine (VDE)
==================================

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

The following example program uses VDE to disassemble a given memory buffer and prints the output to the console.

```C++
#include <tchar.h>
#include <iostream>
#include <stdint.h>
#include "VXDisassembler.h"

using namespace Verteron;

int _tmain(int argc, _TCHAR* argv[])
{
    uint8_t data[] =
    {
        0x90, 0xE9, 0x00, 0x00, 0x00, 0x00, 0xC3
    };
    VXMemoryDataSource input(&data[0], sizeof(data));
    VXInstructionInfo info;
    VXInstructionDecoder decoder;
    decoder.setDisassemblerMode(VXDisassemblerMode::M32BIT);
    decoder.setDataSource(&input);
    decoder.setInstructionPointer(0);
    VXIntelInstructionFormatter formatter;
    while (decoder.decodeInstruction(info))
    {
        std::cout << formatter.formatInstruction(info) << std::endl;
    }
}
```

## Compilation ##
 
- While VDE supports other compilers in theory, compilation has not been tested with any compiler other than MSVC12 (Visual Studio 2013)
- Multi-compiler support might be added in the future
 
## License ##
Verteron Disassembler Engine is licensed under the MIT License. Dependencies are under their respective licenses.
