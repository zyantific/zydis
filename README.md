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
- Very small overhead compared to other common disassembler libraries 
 - Only 44.00 KiB (64 bit: 47.00 KiB) for the decoder and 62.00 KiB (64 bit: 69.50 KiB) with the optional formatting functionality
- Abstract formatter and symbol-resolver classes for custom syntax implementations.
 - Intel syntax is implemented by default
- Complete doxygen documentation

## Compilation ##
 
- While VDE supports other compilers in theory, compilation has not been tested with any other compiler than MSVC12 (Visual Studio 2013)
- Multi-compiler support might be added in the future
 
## License ##
Verteron Disassembler Engine is licensed under the MIT License. Dependencies are under their respective licenses.
