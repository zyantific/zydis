/***************************************************************************************************

  Zyan Disassembler Engine (Zydis)

  Original Author : Florian Bernd

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

***************************************************************************************************/

#ifndef ZYDIS_FORMATTER_H
#define ZYDIS_FORMATTER_H

#include <stdint.h>
#include <Zydis/Defines.h>
#include <Zydis/Status.h>
#include <Zydis/InstructionInfo.h>
#include <Zydis/SymbolResolver.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Instruction formatter                                                                          */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis formatter-style datatype.
 */
typedef uint8_t ZydisFormatterStyle;

/**
 * @brief   Values that represent formatter-styles.
 */
enum ZydisFormatterStyles
{
    /**
     * @brief   Generates intel-style disassembly.
     */
    ZYDIS_FORMATTER_STYLE_INTEL
};

/**
 * @brief   Defines the zydis formatter-flags datatype.
 */
typedef uint8_t ZydisFormatterFlags;

/**
 * @brief   Values that represent formatter-flags.
 */
enum ZydisFormatterFlag
{
    ZYDIS_FORMATTER_FLAG_UPPERCASE                      = 0x01,
    ZYDIS_FORMATTER_FLAG_TAB_AFTER_MNEMONIC             = 0x02,
    ZYDIS_FORMATTER_FLAG_NO_SPACE_BETWEEN_OPERANDS      = 0x04,
    ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SIZE     = 0x08,
    ZYDIS_FORMATTER_FLAG_ALWAYS_DISPLAY_MEMORY_SEGMENT  = 0x10
};

/**
 * @brief   Defines the zydis address-format datatype.
 */
typedef uint8_t ZydisFormatterAddressFormat;

/**
 * @brief   Values that represent address-formats.
 */
enum ZydisFormatterAddressFormat
{   
    /**
     * @brief   Displays absolute addresses instead of relative ones.
     */
    ZYDIS_FORMATTER_ADDRESS_ABSOLUTE,
    /**
     * @brief   Uses signed hexadecimal values to display relative addresses.
     *          
     * Examples:
     * "JMP  0x20"
     * "JMP -0x20"
     */
    ZYDIS_FORMATTER_ADDRESS_RELATIVE_SIGNED,
    /**
     * @brief   Uses unsigned hexadecimal values to display relative addresses.
     *          
     * Examples:
     * "JMP 0x20"
     * "JMP 0xE0"
     */
    ZYDIS_FORMATTER_ADDRESS_RELATIVE_UNSIGNED,
};

/**
 * @brief   Defines the zydis displacement-format datatype.
 */
typedef uint8_t ZydisFormatterDisplacementFormat;

/**
 * @brief   Values that represent displacement-formats.
 */
enum ZydisFormatterDisplacementFormats
{
    /**
     * @brief   Formats displacements as signed hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, DWORD PTR SS:[ESP+0x400]"
     * "MOV EAX, DWORD PTR SS:[ESP-0x400]"
     */
    ZYDIS_FORMATTER_DISP_HEX_SIGNED,
    /**
     * @brief   Formats displacements as unsigned hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, DWORD PTR SS:[ESP+0x400]"
     * "MOV EAX, DWORD PTR SS:[ESP+0xFFFFFC00]"
     */
    ZYDIS_FORMATTER_DISP_HEX_UNSIGNED
};

/**
 * @brief   Defines the zydis formatter immediate-format datatype.
 */
typedef uint8_t ZydisFormatterImmediateFormat;

/**
 * @brief   Values that represent formatter immediate-formats.
 */
enum ZydisFormatterImmediateFormats
{
    /**
     * @brief   Formats immediates as signed hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, 0x400"
     * "MOV EAX, -0x400"
     */
    ZYDIS_FORMATTER_IMM_HEX_SIGNED,
    /**
     * @brief   Formats immediates as unsigned hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, 0x400"
     * "MOV EAX, 0xFFFFFC00"
     */
    ZYDIS_FORMATTER_IMM_HEX_UNSIGNED
};

/**
 * @brief   Defines the zydis instruction-formatter struct.
 */
typedef struct ZydisInstructionFormatter_
{
    ZydisFormatterStyle style;
    ZydisFormatterFlags flags;
    ZydisFormatterAddressFormat addressFormat;
    ZydisFormatterDisplacementFormat displacementFormat;
    ZydisFormatterImmediateFormat immediateFormat;
    ZydisCustomSymbolResolver* symbolResolver;

} ZydisInstructionFormatter;

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Initializes the given @c ZydisInstructionFormatter instance.
 *
 * @param   formatter   A pointer to the instruction-formatter instance.
 * @param   style       The formatter style to use.
 *
 * @return  A zydis status code.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisFormatterInitInstructionFormatter(
    ZydisInstructionFormatter* formatter, ZydisFormatterStyle style);

/**
 * @brief   Initializes the given @c ZydisInstructionFormatter instance.
 *
 * @param   formatter   A pointer to the instruction-formatter instance.
 * @param   style       The formatter style to use.
 * @param   flags       Additional formatter-flags.
 *
 * @return  A zydis status code.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisFormatterInitInstructionFormatterEx(
    ZydisInstructionFormatter* formatter, ZydisFormatterStyle style, ZydisFormatterFlags flags);

/**
 * @brief   Returns the symbol-resolver assigned to the given instruction-formatter instance.
 *
 * @param   formatter       A pointer to the instruction-formatter instance.
 * @param   symbolResolver  A pointer to the memory that receives the current symbol-resolver
 *                          pointer. 
 *
 * @return  A zydis status code.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisFormatterGetSymbolResolver(
    const ZydisInstructionFormatter* formatter, ZydisCustomSymbolResolver** symbolResolver);

/**
 * @brief   Changes the symbol-resolver of the given instruction-formatter instance.
 *
 * @param   formatter       A pointer to the instruction-formatter instance.
 * @param   symbolResolver  A pointer to the new symbol-resolver instance.
 *
 * @return  The ZydisStatus.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisFormatterSetSymbolResolver(
    ZydisInstructionFormatter* formatter, ZydisCustomSymbolResolver* symbolResolver);

/**
 * @brief   Formats the given instruction and writes it into the output buffer.
 *
 * @param   formatter   A pointer to the instruction-formatter instance.
 * @param   info        A pointer to the instruction-info struct.
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 *
 * @return  A zydis status code.
 */
ZYDIS_DLLEXTERN ZydisStatus ZydisFormatterFormatInstruction(
    ZydisInstructionFormatter* formatter, const ZydisInstructionInfo* info, char* buffer,
    size_t bufferLen);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_FORMATTER_H */
