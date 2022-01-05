cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(Zydis VERSION 4.0.0.0 LANGUAGES C CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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
option(ZYDIS_FEATURE_ENCODER
    "Enable instruction encoding functionality"
    ON)
option(ZYDIS_FEATURE_FORMATTER
    "Enable instruction formatting functionality"
    ON)
option(ZYDIS_FEATURE_AVX512
    "Enable support for AVX-512 instructions"
    ON)
option(ZYDIS_FEATURE_KNC
    "Enable support for KNC instructions"
    ON)

# Build configuration
option(ZYDIS_BUILD_SHARED_LIB
    "Build shared library"
    OFF)
option(ZYDIS_BUILD_EXAMPLES
    "Build examples"
    ON)
option(ZYDIS_BUILD_TOOLS
    "Build tools"
    ON)
option(ZYDIS_BUILD_MAN
    "Build manpages for the tools (requires Ronn-NG)"
    OFF)
option(ZYDIS_FUZZ_AFL_FAST
    "Enables AFL persistent mode and reduces prints in ZydisFuzzIn"
    OFF)
option(ZYDIS_LIBFUZZER
    "Enables LLVM libfuzzer mode and reduces prints in ZydisFuzzIn"
    OFF)

# Dependencies
option(ZYAN_SYSTEM_ZYCORE
    "Use system Zycore library"
    OFF)
set(ZYAN_ZYCORE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/dependencies/zycore"
    CACHE
    PATH
    "The path to look for Zycore")

# =============================================================================================== #
# Dependencies                                                                                    #
# =============================================================================================== #

if (ZYAN_SYSTEM_ZYCORE)
    find_package(Zycore)
else ()
    # Try to initialize the Zycore submodule using Git
    if (NOT EXISTS "${ZYAN_ZYCORE_PATH}/CMakeLists.txt" AND 
        "${ZYAN_ZYCORE_PATH}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}/dependencies/zycore")
        find_package(Git QUIET)
        if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
            execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
            )
        endif()
    endif ()

    if (NOT EXISTS "${ZYAN_ZYCORE_PATH}/CMakeLists.txt")
        message(
            FATAL_ERROR
            "Can't find zycore submodule. Please make sure to clone the repo recursively.\n"
            "You can fix this by running\n"
            "    git submodule update --init\n"
            "or by cloning using\n"
            "    git clone --recursive <url>\n"
            "Alternatively, you can manually clone zycore to some path and set ZYDIS_ZYCORE_PATH."
        )
    endif ()

    add_subdirectory(${ZYAN_ZYCORE_PATH} "zycore" EXCLUDE_FROM_ALL)
endif ()

# =============================================================================================== #
# Library configuration                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_SHARED_LIB)
    add_library("Zydis" SHARED)
else ()
    add_library("Zydis" STATIC)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_STATIC_BUILD")
endif ()

target_link_libraries("Zydis" PUBLIC "Zycore")
target_include_directories("Zydis"
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE "src")
target_compile_definitions("Zydis" PRIVATE "_CRT_SECURE_NO_WARNINGS")
set_target_properties("Zydis" PROPERTIES
    VERSION "${Zydis_VERSION}"
    SOVERSION "${Zydis_VERSION_MAJOR}.${Zydis_VERSION_MINOR}"
    DEFINE_SYMBOL "ZYDIS_SHOULD_EXPORT")
zyan_set_common_flags("Zydis")
zyan_maybe_enable_wpo_for_lib("Zydis")

if (ZYDIS_FEATURE_FORMATTER AND NOT ZYDIS_FEATURE_DECODER)
    message(
        FATAL_ERROR
        "\nZYDIS_FEATURE_FORMATTER requires ZYDIS_FEATURE_DECODER to be enabled"
    )
endif ()

if (ZYDIS_FEATURE_ENCODER AND (ZYDIS_MINIMAL_MODE OR
                               NOT ZYDIS_FEATURE_DECODER OR
                               NOT ZYDIS_FEATURE_AVX512 OR
                               NOT ZYDIS_FEATURE_KNC))
    message(
        FATAL_ERROR
        "\nZYDIS_FEATURE_ENCODER requires ZYDIS_FEATURE_DECODER in full mode (ZYDIS_MINIMAL_MODE \
        disabled) with all ISA extensions (ZYDIS_FEATURE_AVX512 and ZYDIS_FEATURE_KNC enabled)"
    )
endif ()

if (ZYDIS_MINIMAL_MODE)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_MINIMAL_MODE")
endif ()
if (NOT ZYDIS_FEATURE_DECODER)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_DECODER")
endif ()
if (NOT ZYDIS_FEATURE_ENCODER)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_ENCODER")
endif ()
if (NOT ZYDIS_FEATURE_FORMATTER)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_FORMATTER")
endif ()
if (NOT ZYDIS_FEATURE_AVX512)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_AVX512")
endif ()
if (NOT ZYDIS_FEATURE_KNC)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_KNC")
endif ()

target_sources("Zydis"
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Defines.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/MetaInfo.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Mnemonic.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Register.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/SharedTypes.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/ShortString.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Status.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Utils.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Zydis.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/SharedData.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/String.h"
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
    if (ZYDIS_FEATURE_ENCODER)
        target_sources("Zydis"
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Encoder.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/EncoderData.h"
                "src/Encoder.c"
                "src/EncoderData.c")
    endif ()
    if (ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        target_sources("Zydis"
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Formatter.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/FormatterBuffer.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/FormatterATT.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/FormatterBase.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/FormatterIntel.h"
                "src/Formatter.c"
                "src/FormatterBuffer.c"
                "src/FormatterATT.c"
                "src/FormatterBase.c"
                "src/FormatterIntel.c")
    endif ()
endif ()

if (ZYDIS_BUILD_SHARED_LIB AND WIN32)
    target_sources("Zydis" PRIVATE "resources/VersionInfo.rc")
endif ()

zyan_set_source_group("Zydis")

configure_package_config_file(cmake/zydis-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/zydis-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/zydis"
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/zydis-config-version.cmake"
    COMPATIBILITY SameMajorVersion
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/zydis-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zydis-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/zydis"
)

install(TARGETS "Zydis"
    EXPORT "zydis-targets"
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT "zydis-targets"
    NAMESPACE "Zydis::"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/zydis")
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

# =============================================================================================== #
# Examples                                                                                        #
# =============================================================================================== #

if (ZYDIS_BUILD_EXAMPLES AND NOT ZYAN_NO_LIBC)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        add_executable("Formatter01" "examples/Formatter01.c")
        target_link_libraries("Formatter01" "Zydis")
        set_target_properties("Formatter01" PROPERTIES FOLDER "Examples/Formatter")
        target_compile_definitions("Formatter01" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("Formatter01")
        zyan_maybe_enable_wpo("Formatter01")
        _maybe_set_emscripten_cfg("Formatter01")

        add_executable("Formatter02" "examples/Formatter02.c")
        target_link_libraries("Formatter02" "Zydis")
        set_target_properties("Formatter02" PROPERTIES FOLDER "Examples/Formatter")
        target_compile_definitions("Formatter02" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("Formatter02")
        zyan_maybe_enable_wpo("Formatter02")
        _maybe_set_emscripten_cfg("Formatter02")

        add_executable("Formatter03" "examples/Formatter03.c")
        target_link_libraries("Formatter03" "Zydis")
        set_target_properties("Formatter03" PROPERTIES FOLDER "Examples/Formatter")
        target_compile_definitions("Formatter03" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("Formatter03")
        zyan_maybe_enable_wpo("Formatter03")
        _maybe_set_emscripten_cfg("Formatter03")

        add_executable("ZydisPerfTest" "examples/ZydisPerfTest.c")
        target_link_libraries("ZydisPerfTest" "Zydis")
        set_target_properties("ZydisPerfTest" PROPERTIES FOLDER "Examples")
        target_compile_definitions("ZydisPerfTest" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("ZydisPerfTest")
        zyan_maybe_enable_wpo("ZydisPerfTest")
        _maybe_set_emscripten_cfg("ZydisPerfTest")
        if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux"
                OR ${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
            target_compile_definitions("ZydisPerfTest" PRIVATE "_GNU_SOURCE")
            find_package(Threads REQUIRED)
            target_link_libraries("ZydisPerfTest" Threads::Threads)
        endif ()
    endif ()

    if (ZYDIS_FEATURE_ENCODER)
        add_executable("EncodeFromScratch" "examples/EncodeFromScratch.c")
        target_link_libraries("EncodeFromScratch" "Zydis")
        set_target_properties("EncodeFromScratch" PROPERTIES FOLDER "Examples/Encoder")
        target_compile_definitions("EncodeFromScratch" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("EncodeFromScratch")
        zyan_maybe_enable_wpo("EncodeFromScratch")
        _maybe_set_emscripten_cfg("EncodeFromScratch")

        add_executable("RewriteCode" "examples/RewriteCode.c")
        target_link_libraries("RewriteCode" "Zydis")
        set_target_properties("RewriteCode" PROPERTIES FOLDER "Examples/Encoder")
        target_compile_definitions("RewriteCode" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("RewriteCode")
        zyan_maybe_enable_wpo("RewriteCode")
        _maybe_set_emscripten_cfg("RewriteCode")
    endif ()
endif ()

# =============================================================================================== #
# Tools                                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_TOOLS AND NOT ZYAN_NO_LIBC)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        add_executable("ZydisDisasm" "tools/ZydisDisasm.c")
        target_link_libraries("ZydisDisasm" "Zydis")
        set_target_properties ("ZydisDisasm" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisDisasm" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("ZydisDisasm")
        zyan_maybe_enable_wpo("ZydisDisasm")
        _maybe_set_emscripten_cfg("ZydisDisasm")
        install(TARGETS "ZydisDisasm" RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

        add_executable("ZydisFuzzDecoder"
            "tools/ZydisFuzzDecoder.c"
            "tools/ZydisFuzzShared.c"
            "tools/ZydisFuzzShared.h")
        target_link_libraries("ZydisFuzzDecoder" "Zydis")
        set_target_properties("ZydisFuzzDecoder" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisFuzzDecoder" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("ZydisFuzzDecoder")
        zyan_maybe_enable_wpo("ZydisFuzzDecoder")
        _maybe_set_emscripten_cfg("ZydisFuzzDecoder")
        if (ZYDIS_FUZZ_AFL_FAST)
            target_compile_definitions("ZydisFuzzDecoder" PRIVATE "ZYDIS_FUZZ_AFL_FAST")
        endif ()
        if (ZYDIS_LIBFUZZER)
            target_compile_definitions("ZydisFuzzDecoder" PRIVATE "ZYDIS_LIBFUZZER")
        endif ()

        if (ZYDIS_FEATURE_ENCODER)
            add_executable("ZydisFuzzEncoder"
                "tools/ZydisFuzzEncoder.c"
                "tools/ZydisFuzzShared.c"
                "tools/ZydisFuzzShared.h")
            target_link_libraries("ZydisFuzzEncoder" "Zydis")
            set_target_properties("ZydisFuzzEncoder" PROPERTIES FOLDER "Tools")
            target_compile_definitions("ZydisFuzzEncoder" PRIVATE "_CRT_SECURE_NO_WARNINGS")
            zyan_set_common_flags("ZydisFuzzEncoder")
            zyan_maybe_enable_wpo("ZydisFuzzEncoder")
            _maybe_set_emscripten_cfg("ZydisFuzzEncoder")
            if (ZYDIS_FUZZ_AFL_FAST)
                target_compile_definitions("ZydisFuzzEncoder" PRIVATE "ZYDIS_FUZZ_AFL_FAST")
            endif ()
            if (ZYDIS_LIBFUZZER)
                target_compile_definitions("ZydisFuzzEncoder" PRIVATE "ZYDIS_LIBFUZZER")
            endif ()

            add_executable("ZydisFuzzReEncoding"
                "tools/ZydisFuzzReEncoding.c"
                "tools/ZydisFuzzShared.c"
                "tools/ZydisFuzzShared.h")
            target_link_libraries("ZydisFuzzReEncoding" "Zydis")
            set_target_properties("ZydisFuzzReEncoding" PROPERTIES FOLDER "Tools")
            target_compile_definitions("ZydisFuzzReEncoding" PRIVATE "_CRT_SECURE_NO_WARNINGS")
            zyan_set_common_flags("ZydisFuzzReEncoding")
            zyan_maybe_enable_wpo("ZydisFuzzReEncoding")
            _maybe_set_emscripten_cfg("ZydisFuzzReEncoding")
            if (ZYDIS_FUZZ_AFL_FAST)
                target_compile_definitions("ZydisFuzzReEncoding" PRIVATE "ZYDIS_FUZZ_AFL_FAST")
            endif ()
            if (ZYDIS_LIBFUZZER)
                target_compile_definitions("ZydisFuzzReEncoding" PRIVATE "ZYDIS_LIBFUZZER")
            endif ()
        endif ()

        add_executable("ZydisInfo" "tools/ZydisInfo.c")
        target_link_libraries("ZydisInfo" "Zydis")
        set_target_properties ("ZydisInfo" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisInfo" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        zyan_set_common_flags("ZydisInfo")
        zyan_maybe_enable_wpo("ZydisInfo")
        _maybe_set_emscripten_cfg("ZydisInfo")
        install(TARGETS "ZydisInfo" RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    endif ()
endif ()

# =============================================================================================== #
# Manpages                                                                                        #
# =============================================================================================== #

if (ZYDIS_BUILD_MAN)
    set(MAN_NAMES "ZydisDisasm.1" "ZydisInfo.1")
    find_program(RONN_BIN "ronn")
    foreach(MAN_NAME ${MAN_NAMES})
        add_custom_command(
            OUTPUT ${MAN_NAME}
            COMMAND ${RONN_BIN} ARGS
                "--roff"
                "--output-dir=${CMAKE_CURRENT_BINARY_DIR}"
                "${CMAKE_CURRENT_SOURCE_DIR}/man/${MAN_NAME}.ronn"
        )
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MAN_NAME}" TYPE MAN)
    endforeach()
    add_custom_target(man ALL DEPENDS ${MAN_NAMES})
endif ()
