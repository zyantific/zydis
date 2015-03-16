cmake_minimum_required(VERSION 2.8.12)

project(VerteronDisassemblerEngine)

option(BUILD_SHARED "Build shared libraries rather than static ones" FALSE)
option(BUILD_EXAMPLES "Build examples" TRUE)
option(BUILD_CPP_BINDINGS "Build C++ bindings" TRUE)

if (NOT CONFIGURED_ONCE)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(compiler_specific "-Werror")
        set(compiler_specific_cxx "-std=c++0x")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(compiler_specific "/WX /D_CRT_SECURE_NO_WARNINGS")
    endif ()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_specific} ${compiler_specific_cxx}"
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
    "VerteronDisassemblerEngine/VXOpcodeTable.h"
    "VerteronDisassemblerEngine/VXOpcodeTableInternal.h"
    "VerteronDisassemblerEngine/VXInternalHelpers.h"
    "VerteronDisassemblerEngine/VXInternalConfig.h")
set(vde_sources
    "VerteronDisassemblerEngine/VXDisassemblerUtils.c"
    "VerteronDisassemblerEngine/VXInstructionFormatter.c"
    "VerteronDisassemblerEngine/VXOpcodeTable.c"
    "VerteronDisassemblerEngine/VXInstructionDecoder.c")

#if (BUILD_SHARED)
#    add_definitions("-DVX_BUILD_SHARED")
#    add_library("VerteronDisassemblerEngine" SHARED ${vde_headers} ${vde_sources})
#else ()
    add_library("VerteronDisassemblerEngine" STATIC ${vde_headers} ${vde_sources})
#endif ()

# C++ bindings
if (BUILD_CPP_BINDINGS)
    set(vdecpp_headers
        "Bindings/Cpp/VXDisassembler.hpp"
        "Bindings/Cpp/VXDisassemblerTypes.hpp"
        "Bindings/Cpp/VXDisassemblerUtils.hpp"
        "Bindings/Cpp/VXInstructionDecoder.hpp"
        "Bindings/Cpp/VXInstructionFormatter.hpp"
        "Bindings/Cpp/VXOpcodeTable.hpp")
    set(vdecpp_sources
        "Bindings/Cpp/VXDisassemblerUtils.cpp"
        "Bindings/Cpp/VXInstructionFormatter.cpp"
        "Bindings/Cpp/VXOpcodeTable.cpp"
        "Bindings/Cpp/VXInstructionDecoder.cpp")
    add_library("VerteronDisassemblerEngineCpp" ${vdecpp_headers} ${vdecpp_sources})
    target_link_libraries("VerteronDisassemblerEngineCpp" "VerteronDisassemblerEngine")
endif ()

# Examples
if (BUILD_EXAMPLES)
    include_directories("VerteronDisassemblerEngine")

    add_executable("CustomDataSource" "Examples/CustomDataSource/Main.c")
    target_link_libraries("CustomDataSource" "VerteronDisassemblerEngine")

    add_executable("PerformanceTest" "Examples/PerformanceTest/Main.c")
    target_link_libraries("PerformanceTest" "VerteronDisassemblerEngine")

    add_executable("SimpleDemo" "Examples/SimpleDemo/Main.c")
    target_link_libraries("SimpleDemo" "VerteronDisassemblerEngine")

    if (BUILD_CPP_BINDINGS)
        add_executable("CppBindingsTest" "Examples/CppBindings/Main.cpp")
        include_directories("Bindings/Cpp")
        target_link_libraries("CppBindingsTest" "VerteronDisassemblerEngineCpp")
    endif ()

    if (WIN32)
        add_executable("SymbolResolver" "Examples/SymbolResolver/Main.c")
        target_link_libraries("SymbolResolver" "VerteronDisassemblerEngine")
    else ()
        message(STATUS "Example 'SymbolResolver' not compatible with platform, ignoring.")
    endif ()
endif ()

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "CMake has configured at least once.")
