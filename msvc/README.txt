This directory contains MSVC project files to build Zydis and the included tools and examples.

There are three build configurations, each with 32/64 bit and debug/release versions:
- Static (default)
- Dynamic
- Kernel mode

In order to build the kernel mode configuration you must have the Microsoft WDK installed, available at https://developer.microsoft.com/en-us/windows/hardware/windows-driver-kit.
The kernel mode configuration only builds Zydis and the ZydisWinKernel driver sample. The other configurations build all projects except for ZydisWinKernel.

All Zydis features are enabled by default. In order to disable specific features you can define preprocessor directives such as ZYDIS_DISABLE_FORMATTER. Refer to CMakeLists.txt for the full list of feature switches.
