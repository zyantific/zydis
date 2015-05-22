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
        set(compiler_specific_cxx "-std=c++14")
    elseif (MSVC)
        set(compiler_specific "/WX /W4 /D_CRT_SECURE_NO_WARNINGS /GR-")
    endif ()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_specific} ${compiler_specific_cxx}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_specific}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif ()

# CMake always orders MSVC to build with a shared CRT. Hack CMake variables in order
# to generate with a statically linked CRT when we build as a static library.
if (MSVC AND NOT FORCE_SHARED_CRT)
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
    "Zydis/Zydis.hpp"
    "Zydis/ZydisInstructionDecoder.hpp"
    "Zydis/ZydisInstructionFormatter.hpp"
    "Zydis/ZydisOpcodeTable.hpp"
    "Zydis/ZydisSymbolResolver.hpp"
    "Zydis/ZydisTypes.hpp"
    "Zydis/ZydisUtils.hpp")
set(sources
    "Zydis/ZydisInstructionDecoder.cpp"
    "Zydis/ZydisInstructionFormatter.cpp"
    "Zydis/ZydisOpcodeTable.cpp"
    "Zydis/ZydisSymbolResolver.cpp"
    "Zydis/ZydisUtils.cpp")

if (BUILD_SHARED_LIBS AND WIN32)
    set(sources ${sources}
        "Zydis/VersionInfo.rc")
endif ()

if (BUILD_C_BINDINGS)
    set(headers ${headers}
        "Zydis/ZydisAPI.h")
    set(sources ${sources}
        "Zydis/ZydisAPI.cpp")
endif ()

add_library("Zydis" ${headers} ${sources})
set_target_properties("Zydis" PROPERTIES COMPILE_DEFINITIONS "Zydis_EXPORTS")
generate_export_header(
    "Zydis" 
    BASE_NAME "ZYDIS"
    EXPORT_FILE_NAME "ZydisExportConfig.h")
include_directories(${PROJECT_BINARY_DIR})

# Examples
if (BUILD_EXAMPLES)
    include_directories("Zydis")

    add_executable("SimpleDemo_CPP" "Examples/CPP/SimpleDemo/SimpleDemo.cpp")
    target_link_libraries("SimpleDemo_CPP" "Zydis")
    add_executable("CustomDataSource_CPP" "Examples/CPP/CustomDataSource/CustomDataSource.cpp")
    target_link_libraries("CustomDataSource_CPP" "Zydis")

    if (BUILD_C_BINDINGS)
        add_executable("SimpleDemo_C" "Examples/C/SimpleDemo/SimpleDemo.c")
        target_link_libraries("SimpleDemo_C" "Zydis")
    endif ()
endif ()

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "CMake has configured at least once.")
