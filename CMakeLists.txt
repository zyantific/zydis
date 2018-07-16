cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
include(GenerateExportHeader)
include(GNUInstallDirs)

project(Zydis VERSION 2.0.1.0 LANGUAGES C CXX)

# =============================================================================================== #
# Overridable options                                                                             #
# =============================================================================================== #

# Features
option(ZYDIS_MINIMAL_MODE
    "Enable minimal mode (forces ZYDIS_DECODER_MODE_MINIMAL runtime option)"
    OFF)
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
option(ZYDIS_BUILD_SHARED_LIB
    "Build shared library"
    OFF)
option(ZYDIS_WHOLE_PROGRAM_OPTIMIZATION
    "Enable whole program optimization"
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

# =============================================================================================== #
# Library configuration                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_SHARED_LIB)
    add_library("Zydis" SHARED)
else ()
    add_library("Zydis" STATIC)
endif ()

# add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../zycore-c" "${CMAKE_CURRENT_BINARY_DIR}/zycore" 
#     EXCLUDE_FROM_ALL)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/dependencies/zycore" EXCLUDE_FROM_ALL)
target_link_libraries("Zydis" PRIVATE "Zycore")

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

if (ZYDIS_MINIMAL_MODE)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_MINIMAL_MODE")
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

target_sources("Zydis"
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/MetaInfo.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Mnemonic.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Register.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/SharedTypes.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Status.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/String.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Utils.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Zydis.h"
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
    if (ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        target_sources("Zydis"
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Formatter.h"
                "src/Formatter.c")
    endif ()
endif ()

if (ZYDIS_BUILD_SHARED_LIB AND WIN32)
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

function (_maybe_set_emscripten_cfg target)
    if (EMSCRIPTEN)
        # Yep, that madness below is how Emscripten likes its quotes.
        set_target_properties("${target}" 
            PROPERTIES COMPILE_FLAGS 
            "-s \"EXPORT_NAME='${target}'\" -s MODULARIZE=1")
        set_target_properties("${target}" 
            PROPERTIES LINK_FLAGS_RELEASE 
            "-s \"EXPORT_NAME='${target}'\" -s MODULARIZE=1")
    endif ()
endfunction ()

function (_maybe_enable_wpo target)
    if (ZYDIS_WHOLE_PROGRAM_OPTIMIZATION AND MSVC)
        set_target_properties("${target}" PROPERTIES COMPILE_FLAGS "/GL")
        set_target_properties("${target}" PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
    endif ()
endfunction ()

# =============================================================================================== #
# Examples                                                                                        #
# =============================================================================================== #

if (ZYDIS_BUILD_EXAMPLES)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        add_executable("FormatterHooks" "examples/FormatterHooks.c")
        target_link_libraries("FormatterHooks" "Zycore")
        target_link_libraries("FormatterHooks" "Zydis")
        set_target_properties("FormatterHooks" PROPERTIES FOLDER "Examples/Formatter")
        target_compile_definitions("FormatterHooks" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        _maybe_set_emscripten_cfg("FormatterHooks")

        add_executable("ZydisFuzzIn" "examples/ZydisFuzzIn.c")
        target_link_libraries("ZydisFuzzIn" "Zycore")
        target_link_libraries("ZydisFuzzIn" "Zydis")
        set_target_properties("FormatterHooks" PROPERTIES FOLDER "Examples")
        target_compile_definitions("ZydisFuzzIn" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        _maybe_set_emscripten_cfg("ZydisFuzzIn")
        _maybe_enable_wpo("ZydisFuzzIn")
        if (ZYDIS_FUZZ_AFL_FAST)
            target_compile_definitions("ZydisFuzzIn" PRIVATE "ZYDIS_FUZZ_AFL_FAST")
        endif ()

        add_executable("ZydisPerfTest" "examples/ZydisPerfTest.c")
        target_link_libraries("ZydisPerfTest" "Zycore")
        target_link_libraries("ZydisPerfTest" "Zydis")
        set_target_properties("FormatterHooks" PROPERTIES FOLDER "Examples")
        target_compile_definitions("ZydisPerfTest" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        _maybe_set_emscripten_cfg("ZydisPerfTest")
        _maybe_enable_wpo("ZydisPerfTest")
        if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            target_compile_definitions("ZydisPerfTest" PRIVATE "_GNU_SOURCE")
            find_package(Threads REQUIRED)
            target_link_libraries("ZydisPerfTest" Threads::Threads)
        endif ()
    endif ()
endif ()

# =============================================================================================== #
# Tools                                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_TOOLS)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        add_executable("ZydisDisasm" "tools/ZydisDisasm.c")
        target_link_libraries("ZydisDisasm" "Zycore")
        target_link_libraries("ZydisDisasm" "Zydis")
        set_target_properties ("ZydisDisasm" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisDisasm" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        _maybe_set_emscripten_cfg("ZydisDisasm")
        _maybe_enable_wpo("ZydisDisasm")

        add_executable("ZydisInfo" "tools/ZydisInfo.c")
        target_link_libraries("ZydisInfo" "Zycore")
        target_link_libraries("ZydisInfo" "Zydis")
        set_target_properties ("ZydisInfo" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisInfo" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        _maybe_set_emscripten_cfg("ZydisInfo")
        _maybe_enable_wpo("ZydisInfo")

        add_executable("ZydisPE" "tools/ZydisPE.c")
        target_link_libraries("ZydisPE" "Zycore")
        target_link_libraries("ZydisPE" "Zydis")
        set_target_properties ("ZydisPE" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisPE" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        _maybe_set_emscripten_cfg("ZydisPE")
        _maybe_enable_wpo("ZydisPE")
    endif ()
endif ()
