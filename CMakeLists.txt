cmake_minimum_required(VERSION 2.8.12)
include(GenerateExportHeader)

project(Zydis)

option(BUILD_SHARED_LIBS "Build shared libraries rather than static ones" FALSE)
option(FORCE_SHARED_CRT 
    "Forces shared linkage against the CRT even when building a static library" 
    FALSE)
option(BUILD_EXAMPLES "Build examples" TRUE)
option(BUILD_C_BINDINGS "Build C bindings" TRUE)

if (NOT CONFIGURED_ONCE)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(compiler_specific "-Werror")
        set(compiler_specific_cxx "-std=c++0x")
    elseif (MSVC)
        set(compiler_specific "/WX /W4 /D_CRT_SECURE_NO_WARNINGS")
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
set(headers
    "ZyDis/ZydisSymbolResolver.hpp"
    "ZyDis/ZydisOpcodeTable.hpp"
    "ZyDis/ZydisInstructionDecoder.hpp"
    "ZyDis/ZydisInstructionFormatter.hpp"
    "ZyDis/ZydisTypes.hpp"
    "ZyDis/ZydisUtils.hpp"
    "ZyDis/Zydis.hpp")
set(sources
    "ZyDis/ZydisInstructionDecoder.cpp"
    "ZyDis/ZydisInstructionFormatter.cpp"
    "ZyDis/ZydisOpcodeTable.cpp"
    "ZyDis/ZydisSymbolResolver.cpp"
    "ZyDis/ZydisUtils.cpp")

add_library("Zydis" ${headers} ${sources})
generate_export_header(
    "Zydis" 
    BASE_NAME "Zydis"
    EXPORT_FILE_NAME "ZydisExportConfig.h")
include_directories(${PROJECT_BINARY_DIR})

# C bindings
if (BUILD_C_BINDINGS)
    set(c_headers
        "Bindings/C/Zydis.h"
        "Bindings/C/ZydisInstructionDecoder.h"
        "Bindings/C/ZydisTypes.h"
        "Bindings/C/ZydisInstructionFormatter.h"
        "Bindings/C/ZydisUtils.h"
        "Bindings/C/ZydisSymbolResolver.h"
        "Bindings/C/ZydisOpcodeTable.h")
    set(c_sources
        "Bindings/C/ZydisSymbolResolver.cpp"
        "Bindings/C/ZydisOpcodeTable.cpp"
        "Bindings/C/ZydisInstructionFormatter.cpp"
        "Bindings/C/ZydisInstructionDecoder.cpp"
        "Bindings/C/ZydisUtils.cpp")
    add_library("ZydisC" ${c_headers} ${c_sources})
    include_directories("Zydis")
    target_link_libraries("ZydisC" "Zydis")
endif ()

# Examples
if (BUILD_EXAMPLES)
    include_directories("Bindings/C")

    add_executable("C_SimpleDemo" "Examples/C/SimpleDemo/SimpleDemo.c")
    target_link_libraries("C_SimpleDemo" "ZydisC")
endif ()

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "CMake has configured at least once.")
