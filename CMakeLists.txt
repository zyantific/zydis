cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.15")
    # Enable runtime library selection via CMAKE_MSVC_RUNTIME_LIBRARY
    cmake_policy(SET CMP0091 NEW)
endif ()

project(Zydis VERSION 4.0.0.0 LANGUAGES C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set ZYDIS_ROOT_PROJECT to ON if this is the top-level project otherwise OFF by default.
set(ZYDIS_ROOT_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(ZYDIS_ROOT_PROJECT ON)
endif()

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
option(ZYDIS_FEATURE_SEGMENT
    "Enable instruction segment API"
    ON)

# Build configuration
option(ZYDIS_BUILD_SHARED_LIB
    "Build shared library"
    OFF)
option(ZYDIS_BUILD_EXAMPLES
    "Build examples"
    ${ZYDIS_ROOT_PROJECT})
option(ZYDIS_BUILD_TOOLS
    "Build tools"
    ${ZYDIS_ROOT_PROJECT})
option(ZYDIS_BUILD_MAN
    "Build manpages for the tools (requires Ronn-NG)"
    OFF)
option(ZYDIS_BUILD_DOXYGEN
    "Build doxygen documentation (requires Doxygen)"
    ${ZYDIS_ROOT_PROJECT})
option(ZYDIS_BUILD_TESTS
    "Build tests"
    ${ZYDIS_ROOT_PROJECT})
option(ZYDIS_FUZZ_AFL_FAST
    "Enables AFL persistent mode and reduces prints in ZydisFuzzIn"
    OFF)
option(ZYDIS_LIBFUZZER
    "Enables LLVM libfuzzer mode and reduces prints in ZydisFuzzIn"
    OFF)

# Dependencies
option(ZYAN_SYSTEM_ZYCORE
    "Force using system installed Zycore library"
    OFF)
set(ZYAN_ZYCORE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/dependencies/zycore"
    CACHE
    PATH
    "The path to look for Zycore")

# =============================================================================================== #
# Dependencies                                                                                    #
# =============================================================================================== #

# Tries to make Zycore available.
#
# Priorities:
#
# - ZYAN_ZYCORE_PATH specified path always takes maximum precedence if it exists.
#   - Default value is the sub-module path. So if the sub-module is present, we pick that.
#     Allows hacking on Zydis/Zycore even if a Zydis OS package is installed.
# - Look for a system-installed Zycore package (via find_package).
# - If git is installed & this is a git repository, try cloning the sub-module.
# - Give up.
#
# This is in a function so we can elegantly early-exit once the library is found.
function (locate_zycore)
    if (NOT ${ZYAN_SYSTEM_ZYCORE} AND EXISTS "${ZYAN_ZYCORE_PATH}/CMakeLists.txt")
        message(VERBOSE "Using ZYAN_ZYCORE_PATH specified Zycore")
        add_subdirectory(${ZYAN_ZYCORE_PATH} "zycore" EXCLUDE_FROM_ALL)
        return ()
    endif ()

    if (NOT "${ZYAN_ZYCORE_PATH}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}/dependencies/zycore")
        message(FATAL_ERROR "No CMake project found at explicitly set ZYAN_ZYCORE_PATH")
    endif ()

    find_package(Zycore QUIET)
    if (Zycore_FOUND)
        message(VERBOSE "Using system Zycore")
        return ()
    endif ()

    if (ZYAN_SYSTEM_ZYCORE)
        message(FATAL_ERROR "ZYAN_SYSTEM_ZYCORE set but no system-installed Zycore found")
    endif ()

    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        message(VERBOSE "Pulling Zycore submodule with git.")
        execute_process(
                COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        add_subdirectory(${ZYAN_ZYCORE_PATH} "zycore" EXCLUDE_FROM_ALL)
        return ()
    endif()

    message(
        FATAL_ERROR
        "Can't find Zycore. Please make sure to clone the repo recursively.\n"
        "You can fix this by running\n"
        "    git submodule update --init\n"
        "or by cloning using\n"
        "    git clone --recursive <url>\n"
        "Alternatively, you can manually clone zycore to some path and set ZYDIS_ZYCORE_PATH."
    )
endfunction ()

locate_zycore()

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
zyan_maybe_enable_wpo("Zydis")

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
if (NOT ZYDIS_FEATURE_SEGMENT)
    target_compile_definitions("Zydis" PUBLIC "ZYDIS_DISABLE_SEGMENT")
endif ()

target_sources("Zydis"
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Defines.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/MetaInfo.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Mnemonic.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Register.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Segment.h"
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
        "src/Segment.c"
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
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Disassembler.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Formatter.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/FormatterBuffer.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/FormatterATT.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/FormatterBase.h"
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Internal/FormatterIntel.h"
                "src/Disassembler.c"
                "src/Formatter.c"
                "src/FormatterBuffer.c"
                "src/FormatterATT.c"
                "src/FormatterBase.c"
                "src/FormatterIntel.c")
    endif ()
    if (ZYDIS_FEATURE_SEGMENT)
        target_sources("Zydis"
            PRIVATE
                "${CMAKE_CURRENT_LIST_DIR}/include/Zydis/Segment.h"
                "src/Segment.c")
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

function(_add_example target source_file sub_folder)
    add_executable("${target}" "examples/${source_file}")
    target_link_libraries("${target}" "Zydis")
    set_target_properties("${target}" PROPERTIES FOLDER "Examples/${sub_folder}")
    target_compile_definitions("${target}" PRIVATE "_CRT_SECURE_NO_WARNINGS")
    zyan_set_common_flags("${target}")
    zyan_maybe_enable_wpo("${target}")
    _maybe_set_emscripten_cfg("${target}")
endfunction()

# =============================================================================================== #
# Examples                                                                                        #
# =============================================================================================== #

if (ZYDIS_BUILD_EXAMPLES AND NOT ZYAN_NO_LIBC)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        _add_example("DisassembleSimple" "DisassembleSimple.c" "Decoder")
        _add_example("Disassemble" "Disassemble.c" "Decoder")
        _add_example("Formatter01" "Formatter01.c" "Decoder")
        _add_example("Formatter02" "Formatter02.c" "Decoder")
        _add_example("Formatter03" "Formatter03.c" "Decoder")
        _add_example("ZydisPerfTest" "ZydisPerfTest.c" "Decoder")
        if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux"
                OR ${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
            target_compile_definitions("ZydisPerfTest" PRIVATE "_GNU_SOURCE")
            find_package(Threads REQUIRED)
            target_link_libraries("ZydisPerfTest" Threads::Threads)
        endif ()
    endif ()

    if (ZYDIS_FEATURE_ENCODER)
        _add_example("EncodeMov" "EncodeMov.c" "Encoder")
        _add_example("EncodeFromScratch" "EncodeFromScratch.c" "Encoder")
        _add_example("RewriteCode" "RewriteCode.c" "Encoder")
    endif ()
endif ()

# =============================================================================================== #
# Tools                                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_TOOLS AND NOT ZYAN_NO_LIBC)
    if (ZYDIS_FEATURE_DECODER AND ZYDIS_FEATURE_FORMATTER AND (NOT ZYDIS_MINIMAL_MODE))
        add_executable("ZydisDisasm"
            "tools/ZydisDisasm.c"
            "tools/ZydisToolsShared.c"
            "tools/ZydisToolsShared.h")
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
        if (NOT ZYDIS_FEATURE_ENCODER)
            # For 'ZydisFuzzShared.c'
            target_compile_definitions("ZydisFuzzDecoder" PUBLIC "ZYDIS_DISABLE_ENCODER")
        endif ()
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

            if (NOT ZYDIS_BUILD_SHARED_LIB)
                add_executable("ZydisTestEncoderAbsolute"
                    "tools/ZydisTestEncoderAbsolute.c")
                target_link_libraries("ZydisTestEncoderAbsolute" "Zydis")
                set_target_properties("ZydisTestEncoderAbsolute" PROPERTIES FOLDER "Tools")
                target_compile_definitions("ZydisTestEncoderAbsolute" PRIVATE "_CRT_SECURE_NO_WARNINGS")
                zyan_set_common_flags("ZydisTestEncoderAbsolute")
                zyan_maybe_enable_wpo("ZydisTestEncoderAbsolute")
                _maybe_set_emscripten_cfg("ZydisTestEncoderAbsolute")
            endif ()
        endif ()

        add_executable("ZydisInfo"
            "tools/ZydisInfo.c"
            "tools/ZydisToolsShared.c"
            "tools/ZydisToolsShared.h")
        target_link_libraries("ZydisInfo" "Zydis")
        set_target_properties ("ZydisInfo" PROPERTIES FOLDER "Tools")
        target_compile_definitions("ZydisInfo" PRIVATE "_CRT_SECURE_NO_WARNINGS")
        if (NOT ZYDIS_FEATURE_ENCODER)
            target_compile_definitions("ZydisInfo" PUBLIC "ZYDIS_DISABLE_ENCODER")
        endif ()
        zyan_set_common_flags("ZydisInfo")
        zyan_maybe_enable_wpo("ZydisInfo")
        _maybe_set_emscripten_cfg("ZydisInfo")
        install(TARGETS "ZydisInfo" RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    endif ()
endif ()

# =============================================================================================== #
# Doxygen documentation                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_DOXYGEN)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # Read Doxygen options from the Doxyfile and set them as CMake variables
        # to accomodate doxygen_add_docs()
        file(READ "Doxyfile" DOXYFILE)
        # Remove comments
        string(REGEX REPLACE "\n?#[^\n]*\n" "" DOXYFILE ${DOXYFILE})
        # Remove empty lines
        string(REGEX REPLACE "\n[ \t\r\n]" "\n" DOXYFILE "${DOXYFILE}")
        # Strip leading and trailing spaces
        string(STRIP "${DOXYFILE}" DOXYFILE)
        # Tranform the file in a list of '='-separated options
        string(REPLACE "\n" ";" DOXYFILE "${DOXYFILE}")

        foreach(option IN LISTS DOXYFILE)
            string(REPLACE "=" ";" option "${option}")
            list(GET option 0 opt_name)
            list(GET option 1 opt_value)
            string(STRIP "${opt_name}" opt_name)
            string(STRIP "${opt_value}" opt_value)

            if (opt_name STREQUAL "INPUT")
                # Save the INPUTs in a list to be used later
                string(REGEX REPLACE "[ ]+" ";" DOC_PATHS "${opt_value}")
                # Skip as the input files are not set by a DOXYGEN_INPUT variable
                continue()
            endif()

            if (opt_name STREQUAL "OUTPUT_DIRECTORY")
                # Skip as CMake writes the output files in the build directory
                continue()
            endif()

            set("DOXYGEN_${opt_name}" ${opt_value})
        endforeach()

        set(DOXYGEN_QUIET YES)
        set(DOXYGEN_WARNINGS NO)
        set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)

        doxygen_add_docs(ZydisDoc ${DOC_PATHS} ALL)

        install(
            DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/"
            DESTINATION "${CMAKE_INSTALL_DOCDIR}/api"
            COMPONENT Documentation
        )
    else ()
        message("Can't generate documentation, Doxygen not found.")
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
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MAN_NAME}" DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
    endforeach()
    add_custom_target(man ALL DEPENDS ${MAN_NAMES})
endif ()

# =============================================================================================== #
# Tests                                                                                           #
# =============================================================================================== #

if (ZYDIS_BUILD_TESTS)
    enable_testing()
    find_package(Python 3 REQUIRED)

    if (TARGET ZydisInfo)
        add_test(
            NAME "ZydisRegression"
            COMMAND 
                "${Python_EXECUTABLE}"
                regression.py
                test
                $<TARGET_FILE:ZydisInfo>
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests"
        )
    endif ()

    if (TARGET ZydisFuzzReEncoding AND TARGET ZydisFuzzEncoder AND TARGET ZydisTestEncoderAbsolute)
        add_test(
            NAME "ZydisRegressionEncoder"
            COMMAND 
                "${Python_EXECUTABLE}"
                regression_encoder.py
                $<TARGET_FILE:ZydisFuzzReEncoding>
                $<TARGET_FILE:ZydisFuzzEncoder>
                $<TARGET_FILE:ZydisTestEncoderAbsolute>
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests"
        )
    endif ()
endif ()
