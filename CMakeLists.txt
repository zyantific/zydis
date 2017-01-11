cmake_minimum_required(VERSION 2.8.12)
include(GenerateExportHeader)

project(Zydis)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ZYDIS_BUILD_SHARED_LIBS 
    "Build shared libraries rather than static ones" 
    FALSE)
option(ZYDIS_FORCE_SHARED_CRT 
    "Forces shared linkage against the CRT even when building a static library" 
    FALSE)
option(ZYDIS_FEATURE_IMPLICITLY_USED_REGISTERS 
    "Include information about implicitly used registers" 
    TRUE)
option(ZYDIS_FEATURE_AFFECTED_FLAGS 
    "Include information about affected flags"
    TRUE)
option(ZYDIS_FEATURE_CPUID 
    "Include information about CPUID feature-flags"
    FALSE)
option(ZYDIS_BUILD_EXAMPLES "Build examples" TRUE)
option(ZYDIS_BUILD_TOOLS "Build tools" TRUE)

if (NOT CONFIGURED_ONCE)
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
            "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
        set(compiler_specific "-std=c99 -pedantic -Wextra -Werror")
    elseif (MSVC)
        set(compiler_specific "/WX /W4 /TC")
    endif ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_specific}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif ()

# CMake always orders MSVC to build with a shared CRT. Hack CMake variables in order
# to generate with a statically linked CRT when we build a static library.
if (("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC") AND NOT ZYDIS_FORCE_SHARED_CRT)
    foreach(flag_var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif ()
    endforeach ()
endif ()

# Library
set(headers
    "include/Zydis/Decoder.h"
    "include/Zydis/Defines.h"
    "include/Zydis/Formatter.h"
    "include/Zydis/InstructionInfo.h"
    "include/Zydis/Mnemonic.h"
    "include/Zydis/Register.h"
    "include/Zydis/Status.h"
    "include/Zydis/Types.h"
    "include/Zydis/Utils.h"
    "include/Zydis/Zydis.h"
    "include/Zydis/Internal/InstructionTable.h")
set(sources
    "src/Decoder.c"
    "src/Formatter.c"
    "src/InstructionTable.c"
    "src/Mnemonic.c"
    "src/Register.c"
    "src/Utils.c"
    "src/Zydis.c")

if (ZYDIS_BUILD_SHARED_LIBS AND WIN32)
    set(sources ${sources} "src/VersionInfo.rc")
endif ()

add_library("Zydis" ${headers} ${sources})
target_include_directories("Zydis" PUBLIC "include/" ${PROJECT_BINARY_DIR})
target_compile_definitions("Zydis" PRIVATE "_CRT_SECURE_NO_WARNINGS" "ZYDIS_EXPORTS")
generate_export_header("Zydis" BASE_NAME "ZYDIS" EXPORT_FILE_NAME "ZydisExportConfig.h")

if (ZYDIS_FEATURE_IMPLICITLY_USED_REGISTERS)
    target_compile_definitions("Zydis" PRIVATE "ZYDIS_ENABLE_FEATURE_IMPLICITLY_USED_REGISTERS")
endif ()
if (ZYDIS_FEATURE_AFFECTED_FLAGS)
    target_compile_definitions("Zydis" PRIVATE "ZYDIS_ENABLE_FEATURE_AFFECTED_FLAGS")
endif ()
if (ZYDIS_FEATURE_CPUID)
    target_compile_definitions("Zydis" PRIVATE "ZYDIS_ENABLE_FEATURE_CPUID")
endif ()

# Examples
if (ZYDIS_BUILD_EXAMPLES)
    add_executable("FormatterHooks" 
        "examples/FormatterHooks.c"
        "examples/FormatHelper.h")
    target_link_libraries("FormatterHooks" "Zydis")
    set_target_properties ("FormatterHooks" PROPERTIES FOLDER "Examples/Formatter")
endif ()

# Tools
if (ZYDIS_BUILD_TOOLS)
    add_executable("ZydisDisasm" "tools/ZydisDisasm.c")
    target_link_libraries("ZydisDisasm" "Zydis")
    set_target_properties ("ZydisDisasm" PROPERTIES FOLDER "Tools")

    add_executable("ZydisFuzzIn" "tools/ZydisFuzzIn.c")
    target_link_libraries("ZydisFuzzIn" "Zydis")
    set_target_properties("ZydisFuzzIn" PROPERTIES FOLDER "Tools")
endif ()
