cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
include(GenerateExportHeader)
include(GNUInstallDirs)

project(Zydis VERSION 2.0)

# =============================================================================================== #
# Overridable options                                                                             #
# =============================================================================================== #

# Features
option(ZYDIS_FEATURE_DECODER
    "Enable instruction decoding functionality"
    ON)
option(ZYDIS_FEATURE_FORMATTER
    "Enable instruction formatting functionality"
    ON)
option(ZYDIS_FEATURE_EVEX
    "Enable support for EVEX instructions"
    ON)
option(ZYDIS_FEATURE_MVEX
    "Enable support for MVEX instructions"
    ON)

# Build configuration
option(BUILD_SHARED_LIBS
    "Build shared libraries"
    OFF)
option(ZYDIS_WHOLE_PROGRAM_OPTIMIZATION
    "Enable whole program optimization"
    OFF)
option(ZYDIS_NO_LIBC
    "Don't use any C standard library functions (for exotic build-envs like kernel drivers)"
    OFF)
option(ZYDIS_BUILD_EXAMPLES
    "Build examples"
    ON)
option(ZYDIS_BUILD_TOOLS
    "Build tools"
    ON)
option(ZYDIS_FUZZ_AFL_FAST
    "Enables AFL persistent mode and reduces prints in ZydisFuzzIn"
    OFF)
option(ZYDIS_DEV_MODE
    "Enable developer mode (-Wall, -Werror, ...)"
    OFF)

# =============================================================================================== #
# Developer mode                                                                                  #
# =============================================================================================== #

# If in developer mode, hack global compiler flags.
if (ZYDIS_DEV_MODE)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
            "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
            "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
        set(compiler_specific "-pedantic -Wextra -Werror")
    elseif (MSVC)
        set(compiler_specific "/WX /W4 /TC")
    endif ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_specific}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif ()

# =============================================================================================== #
# Library configuration                                                                           #
# =============================================================================================== #

function (_set_common_flags target)
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
        "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
        target_compile_options("${target}" PRIVATE "-std=c99")
    endif ()
    if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
        target_compile_options("${target}" PRIVATE "-fPIC")
    endif ()
endfunction ()

add_library("Zydis")
_set_common_flags("Zydis")
target_include_directories("Zydis"
    PUBLIC "include" ${PROJECT_BINARY_DIR}
    PRIVATE "src")
target_compile_definitions("Zydis" PRIVATE "_CRT_SECURE_NO_WARNINGS" "ZYDIS_EXPORTS")
if (ZYDIS_WHOLE_PROGRAM_OPTIMIZATION AND MSVC)
    set_target_properties("Zydis" PROPERTIES COMPILE_FLAGS "/GL")
    set_target_properties("Zydis" PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
    set_target_properties("Zydis" PROPERTIES STATIC_LIBRARY_FLAGS_RELEASE "/LTCG")
endif ()
generate_export_header("Zydis" BASE_NAME "ZYDIS" EXPORT_FILE_NAME "ZydisExportConfig.h")

if (NOT ZYDIS_FEATURE_ENCODER AND NOT ZYDIS_FEATURE_DECODER)
    message(
        FATAL_ERROR
        "\nIt's dangerous to go alone! Take at least one of these:\n"
        "[ ] ZYDIS_FEATURE_ENCODER [ ] ZYDIS_FEATURE_DECODER"
    )
endif ()

if (ZYDIS_FEATURE_FORMATTER AND NOT ZYDIS_FEATURE_DECODER)
    message(
        FATAL_ERROR
        "\nZYDIS_FEATURE_FORMATTER requires ZYDIS_FEATURE_DECODER to be enabled"
    )
endif ()

if (NOT ZYDIS_FEATURE_DECODER)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_DECODER")
endif ()
if (NOT ZYDIS_FEATURE_FORMATTER)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_FORMATTER")
endif ()
if (NOT ZYDIS_FEATURE_EVEX)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_EVEX")
endif ()
if (NOT ZYDIS_FEATURE_MVEX)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_MVEX")
endif ()
if (ZYDIS_NO_LIBC)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_NO_LIBC")
endif ()

target_sources("Zydis"
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/CommonTypes.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Defines.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/MetaInfo.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Mnemonic.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Register.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/SharedTypes.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Status.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/String.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Utils.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Zydis.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/LibC.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/SharedData.h"
        "src/MetaInfo.c"
        "src/Mnemonic.c"
        "src/Register.c"
        "src/SharedData.c"
        "src/String.c"
        "src/Utils.c"
        "src/Zydis.c")

if (ZYDIS_FEATURE_DECODER)
    target_sources("Zydis"
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Decoder.h"
            "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/DecoderTypes.h"
            "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/DecoderData.h"
            "src/Decoder.c"
            "src/DecoderData.c")
    if (ZYDIS_FEATURE_FORMATTER)
        target_sources("Zydis"
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Formatter.h"
                "src/Formatter.c")
    endif ()
endif ()

if (BUILD_SHARED_LIBS AND WIN32)
    target_sources("Zydis" PRIVATE "src/VersionInfo.rc")
endif ()

# TODO: Install CMake config.
install(TARGETS "Zydis"
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES
    "${PROJECT_BINARY_DIR}/ZydisExportConfig.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# =============================================================================================== #
# Examples                                                                                        #
# =============================================================================================== #

if (ZYDIS_BUILD_EXAMPLES)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER)
        add_executable("FormatterHooks" "examples/FormatterHooks.c")
        _set_common_flags("FormatterHooks")
        target_link_libraries("FormatterHooks" "Zydis")
        set_target_properties("FormatterHooks" PROPERTIES FOLDER "Examples/Formatter")
        target_compile_definitions("FormatterHooks" PRIVATE "_CRT_SECURE_NO_WARNINGS")

        add_executable("ZydisFuzzIn" "examples/ZydisFuzzIn.c")
        _set_common_flags("ZydisFuzzIn")
        target_link_libraries("ZydisFuzzIn" "Zydis")
        set_target_properties("FormatterHooks" PROPERTIES FOLDER "Examples")
        target_compile_definitions("ZydisFuzzIn" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        if (ZYDIS_WHOLE_PROGRAM_OPTIMIZATION AND MSVC)
            set_target_properties("ZydisFuzzIn" PROPERTIES COMPILE_FLAGS "/GL")
            set_target_properties("ZydisFuzzIn" PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
        endif ()
        if (ZYDIS_FUZZ_AFL_FAST)
            target_compile_definitions("ZydisFuzzIn" PRIVATE "ZYDIS_FUZZ_AFL_FAST")
        endif ()

        add_executable("ZydisPerfTest" "examples/ZydisPerfTest.c")
        _set_common_flags("ZydisPerfTest")
        target_link_libraries("ZydisPerfTest" "Zydis")
        set_target_properties("FormatterHooks" PROPERTIES FOLDER "Examples")
        target_compile_definitions("ZydisPerfTest" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        if (ZYDIS_WHOLE_PROGRAM_OPTIMIZATION AND MSVC)
            set_target_properties("ZydisPerfTest" PROPERTIES COMPILE_FLAGS "/GL")
            set_target_properties("ZydisPerfTest" PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
        endif ()
        if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            target_compile_definitions("ZydisPerfTest" PRIVATE "_GNU_SOURCE")
            find_package(Threads REQUIRED)
            target_link_libraries("ZydisPerfTest" Threads::Threads)
        endif ()
        if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
            find_package(Threads REQUIRED)
            target_link_libraries("ZydisPerfTest" Threads::Threads)
        endif ()
    endif ()
endif ()

# =============================================================================================== #
# Tools                                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_TOOLS)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER)
        add_executable("ZydisDisasm" "tools/ZydisDisasm.c")
        _set_common_flags("ZydisDisasm")
        target_link_libraries("ZydisDisasm" "Zydis")
        set_target_properties ("ZydisDisasm" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisDisasm" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        if (ZYDIS_WHOLE_PROGRAM_OPTIMIZATION AND MSVC)
            set_target_properties("ZydisDisasm" PROPERTIES COMPILE_FLAGS "/GL")
            set_target_properties("ZydisDisasm" PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
        endif ()

        add_executable("ZydisInfo" "tools/ZydisInfo.c")
        _set_common_flags("ZydisInfo")
        target_link_libraries("ZydisInfo" "Zydis")
        set_target_properties ("ZydisInfo" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisInfo" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        if (ZYDIS_WHOLE_PROGRAM_OPTIMIZATION AND MSVC)
            set_target_properties("ZydisInfo" PROPERTIES COMPILE_FLAGS "/GL")
            set_target_properties("ZydisInfo" PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
        endif ()
    endif ()
endif ()
