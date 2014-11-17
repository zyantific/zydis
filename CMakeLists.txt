cmake_minimum_required(VERSION 2.8.12)

project(VerteronDisassemblerEngine)

option(BUILD_EXAMPLES "Build examples" TRUE)

if (NOT CONFIGURED_ONCE)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(compiler_specific "-std=c++0x -Werror")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(compiler_specific "/WX /D_CRT_SECURE_NO_WARNINGS")
    endif ()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_specific}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_specific}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif ()

# Library
set(vde_headers
    "VerteronDisassemblerEngine/VXDisassembler.h"
    "VerteronDisassemblerEngine/VXDisassemblerTypes.h"
    "VerteronDisassemblerEngine/VXDisassemblerUtils.h"
    "VerteronDisassemblerEngine/VXInstructionDecoder.h"
    "VerteronDisassemblerEngine/VXInstructionFormatter.h"
    "VerteronDisassemblerEngine/VXOpcodeTable.h")
set(vde_sources
    "VerteronDisassemblerEngine/VXDisassemblerUtils.cpp"
    "VerteronDisassemblerEngine/VXInstructionFormatter.cpp"
    "VerteronDisassemblerEngine/VXOpcodeTable.cpp"
    "VerteronDisassemblerEngine/VXInstructionDecoder.cpp")

add_library("VerteronDisassemblerEngine"
    ${vde_headers}
    ${vde_sources})

# Examples
if (BUILD_EXAMPLES)
    include_directories("VerteronDisassemblerEngine")

    add_executable("CustomDataSource"
        "Examples/CustomDataSource/Main.cpp")
    target_link_libraries("CustomDataSource" "VerteronDisassemblerEngine")

    add_executable("PerformanceTest"
        "Examples/PerformanceTest/Main.cpp")
    target_link_libraries("PerformanceTest" "VerteronDisassemblerEngine")

    add_executable("SimpleDemo"
        "Examples/SimpleDemo/Main.cpp")
    target_link_libraries("SimpleDemo" "VerteronDisassemblerEngine")

    if (WIN32)
        add_executable("SymbolResolver"
            "Examples/SymbolResolver/Main.cpp")
        target_link_libraries("SymbolResolver" "VerteronDisassemblerEngine")
    else ()
        message(STATUS "Example 'SymbolResolver' not compatible with platform, ignoring.")
    endif ()
endif ()

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "CMake has configured at least once.")