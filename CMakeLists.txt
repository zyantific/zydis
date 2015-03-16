cmake_minimum_required(VERSION 2.8.12)
include(GenerateExportHeader)

project(VerteronDisassemblerEngine)

option(BUILD_SHARED_LIBS "Build shared libraries rather than static ones" FALSE)
option(FORCE_SHARED_CRT 
    "Forces shared linkage against the CRT even when building a static library" 
    FALSE)
option(BUILD_EXAMPLES "Build examples" TRUE)
option(BUILD_CPP_BINDINGS "Build C++ bindings" TRUE)

if (NOT CONFIGURED_ONCE)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(compiler_specific "-Werror")
        set(compiler_specific_cxx "-std=c++0x")
    elseif (MSVC)
        set(compiler_specific "/WX /D_CRT_SECURE_NO_WARNINGS")
    endif ()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_specific} ${compiler_specific_cxx}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_specific}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif ()

# CMake always orders MSVC to build with a shared CRT. Hack CMake variables in order
# to generate with a statically linked CRT when we build as a static library.
if (MSVC AND NOT BUILD_SHARED_LIBS AND NOT FORCE_SHARED_CRT)
    set(manipulated_vars
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO)
    foreach (cur_var ${manipulated_vars})
        string(REPLACE "/MD" "/MT" ${cur_var} "${${cur_var}}")
    endforeach ()
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

add_library("VerteronDisassemblerEngine" ${vde_headers} ${vde_sources})
generate_export_header(
    "VerteronDisassemblerEngine" 
    BASE_NAME "VX"
    EXPORT_FILE_NAME "VXExportConfig.h")
include_directories(${PROJECT_BINARY_DIR})

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
