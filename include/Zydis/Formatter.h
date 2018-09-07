/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

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

/**
 * @file
 * @brief   Functions for formatting human-readable instructions.
 */

#ifndef ZYDIS_FORMATTER_H
#define ZYDIS_FORMATTER_H

#include <Zydis/DecoderTypes.h>
#include <Zydis/Defines.h>
#include <Zydis/Status.h>
#include <Zydis/String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Formatter style                                                                                */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisFormatterStyle` datatype.
 */
typedef ZydisU8 ZydisFormatterStyle;

/**
 * @brief   Values that represent formatter-styles.
 */
enum ZydisFormatterStyles
{
    /**
     * @brief   Generates intel-style disassembly.
     */
    ZYDIS_FORMATTER_STYLE_INTEL,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_FORMATTER_STYLE_MAX_VALUE = ZYDIS_FORMATTER_STYLE_INTEL
};

/* ---------------------------------------------------------------------------------------------- */
/* Attributes                                                                                     */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisFormatterProperty` datatype.
 */
typedef ZydisU8 ZydisFormatterProperty;

/**
 * @brief   Values that represent formatter-properties.
 */
enum ZydisFormatterProperties
{
    /**
     * @brief   Controls the letter-case.
     *
     * Pass `ZYDIS_TRUE` as value to format in uppercase and `ZYDIS_FALSE` to format in lowercase.
     *
     * The default value is `ZYDIS_FALSE`.
     */
    ZYDIS_FORMATTER_PROP_UPPERCASE,
    /**
     * @brief   Controls the printing of segment prefixes.
     *
     * Pass `ZYDIS_TRUE` as value to force the formatter to always print the segment register of
     * memory-operands or `ZYDIS_FALSE` to ommit implicit DS/SS segments.
     *
     * The default value is `ZYDIS_FALSE`.
     */
    ZYDIS_FORMATTER_PROP_FORCE_MEMSEG,
    /**
     * @brief   Controls the printing of memory-operand sizes.
     *
     * Pass `ZYDIS_TRUE` as value to force the formatter to always print the size of memory-operands
     * or `ZYDIS_FALSE` to only print it on demand.
     *
     * The default value is `ZYDIS_FALSE`.
     */
    ZYDIS_FORMATTER_PROP_FORCE_MEMSIZE,

    /**
     * @brief   Controls the format of addresses.
     *
     * The default value is `ZYDIS_ADDR_FORMAT_ABSOLUTE`.
     */
    ZYDIS_FORMATTER_PROP_ADDR_FORMAT,
    /**
     * @brief   Controls the format of displacement values.
     *
     * The default value is `ZYDIS_DISP_FORMAT_HEX_SIGNED`.
     */
    ZYDIS_FORMATTER_PROP_DISP_FORMAT,
    /**
     * @brief   Controls the format of immediate values.
     *
     * The default value is `ZYDIS_IMM_FORMAT_HEX_UNSIGNED`.
     */
    ZYDIS_FORMATTER_PROP_IMM_FORMAT,

    /**
     * @brief   Controls the letter-case of hexadecimal values.
     *
     * Pass `ZYDIS_TRUE` as value to format in uppercase and `ZYDIS_FALSE` to format in lowercase.
     *
     * The default value is `ZYDIS_TRUE`.
     */
    ZYDIS_FORMATTER_PROP_HEX_UPPERCASE,
    /**
     * @brief   Sets the prefix for hexadecimal values.
     *
     * The default value is `"0x"`.
     */
    ZYDIS_FORMATTER_PROP_HEX_PREFIX,
    /**
     * @brief   Sets the suffix for hexadecimal values.
     *
     * The default value is `NULL`.
     */
    ZYDIS_FORMATTER_PROP_HEX_SUFFIX,
    /**
     * @brief   Controls the padding (minimum number of chars) of hexadecimal address values.
     *
     * The default value is `2`.
     */
    ZYDIS_FORMATTER_PROP_HEX_PADDING_ADDR,
    /**
     * @brief   Controls the padding (minimum number of chars) of hexadecimal displacement values.
     *
     * The default value is `2`.
     */
    ZYDIS_FORMATTER_PROP_HEX_PADDING_DISP,
    /**
     * @brief   Controls the padding (minimum number of chars) of hexadecimal immediate values.
     *
     * The default value is `2`.
     */
    ZYDIS_FORMATTER_PROP_HEX_PADDING_IMM,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_FORMATTER_PROP_MAX_VALUE = ZYDIS_FORMATTER_PROP_HEX_PADDING_IMM
};

/* ---------------------------------------------------------------------------------------------- */
/* Address format                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent address-formats.
 */
enum ZydisAddressFormat
{
    /**
     * @brief   Displays absolute addresses instead of relative ones.
     *
     * Using this value will cause the formatter to invoke `ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS`
     * for every address.
     */
    ZYDIS_ADDR_FORMAT_ABSOLUTE,
    /**
     * @brief   Uses signed hexadecimal values to display relative addresses.
     *
     * Using this value will cause the formatter to either invoke
     * `ZYDIS_FORMATTER_HOOK_PRINT_DISP` or `ZYDIS_FORMATTER_HOOK_PRINT_IMM` to format addresses.
     *
     * Examples:
     * - `"JMP  0x20"`
     * - `"JMP -0x20"`
     */
    ZYDIS_ADDR_FORMAT_RELATIVE_SIGNED,
    /**
     * @brief   Uses unsigned hexadecimal values to display relative addresses.
     *
     * Using this value will cause the formatter to either invoke
     * `ZYDIS_FORMATTER_HOOK_PRINT_DISP` or `ZYDIS_FORMATTER_HOOK_PRINT_IMM` to format addresses.
     *
     * Examples:
     * - `"JMP 0x20"`
     * - `"JMP 0xE0"`
     */
    ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_ADDR_FORMAT_MAX_VALUE = ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED
};

/* ---------------------------------------------------------------------------------------------- */
/* Displacement format                                                                            */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent displacement-formats.
 */
enum ZydisDisplacementFormat
{
    /**
     * @brief   Formats displacements as signed hexadecimal values.
     *
     * Examples:
     * - `"MOV EAX, DWORD PTR SS:[ESP+0x400]"`
     * - `"MOV EAX, DWORD PTR SS:[ESP-0x400]"`
     */
    ZYDIS_DISP_FORMAT_HEX_SIGNED,
    /**
     * @brief   Formats displacements as unsigned hexadecimal values.
     *
     * Examples:
     * - `"MOV EAX, DWORD PTR SS:[ESP+0x400]"`
     * - `"MOV EAX, DWORD PTR SS:[ESP+0xFFFFFC00]"`
     */
    ZYDIS_DISP_FORMAT_HEX_UNSIGNED,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_DISP_FORMAT_MAX_VALUE = ZYDIS_DISP_FORMAT_HEX_UNSIGNED
};

/* ---------------------------------------------------------------------------------------------- */
/* Immediate format                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent formatter immediate-formats.
 */
enum ZydisImmediateFormat
{
    /**
     * @brief   Automatically chooses the most suitable formatting-mode based on the operands
     *          `ZydisOperandInfo.imm.isSigned` attribute.
     */
    ZYDIS_IMM_FORMAT_HEX_AUTO,
    /**
     * @brief   Formats immediates as signed hexadecimal values.
     *
     * Examples:
     * - `"MOV EAX, 0x400"`
     * - `"MOV EAX, -0x400"`
     */
    ZYDIS_IMM_FORMAT_HEX_SIGNED,
    /**
     * @brief   Formats immediates as unsigned hexadecimal values.
     *
     * Examples:
     * - `"MOV EAX, 0x400"`
     * - `"MOV EAX, 0xFFFFFC00"`
     */
    ZYDIS_IMM_FORMAT_HEX_UNSIGNED,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_IMM_FORMAT_MAX_VALUE = ZYDIS_IMM_FORMAT_HEX_UNSIGNED
};

/* ---------------------------------------------------------------------------------------------- */
/* Hooks                                                                                          */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisFormatterHookType` datatype.
 */
typedef ZydisU8 ZydisFormatterHookType;

/**
 * @brief   Values that represent formatter hook-types.
 */
enum ZydisFormatterHookTypes
{
    /**
     * @brief   This function is invoked before the formatter formats an instruction.
     */
    ZYDIS_FORMATTER_HOOK_PRE_INSTRUCTION,
    /**
     * @brief   This function is invoked after the formatter formatted an instruction.
     */
    ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION,
    /**
     * @brief   This function is invoked before the formatter formats an operand.
     */
    ZYDIS_FORMATTER_HOOK_PRE_OPERAND,
    /**
     * @brief   This function is invoked after the formatter formatted an operand.
     */
    ZYDIS_FORMATTER_HOOK_POST_OPERAND,

    /**
     * @brief   This function refers to the main formatting function.
     *
     * Replacing this function allows for complete custom formatting, but indirectly disables all
     * other hooks except for `ZYDIS_FORMATTER_HOOK_PRE_INSTRUCTION` and
     * `ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION`.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION,
    /**
     * @brief   This function is invoked to format a register operand.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG,
    /**
     * @brief   This function is invoked to format a memory operand.
     *
     * Replacing this function might indirectly disable some specific calls to the
     * `ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE`, `ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS` and
     * `ZYDIS_FORMATTER_HOOK_PRINT_DISP` functions.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM,
    /**
     * @brief   This function is invoked to format a pointer operand.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR,
    /**
     * @brief   This function is invoked to format an immediate operand.
     *
     * Replacing this function might indirectly disable some specific calls to the
     * `ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS` and `ZYDIS_FORMATTER_HOOK_PRINT_IMM` functions.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM,

    /**
     * @brief   This function is invoked to print the instruction mnemonic.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC,
    /**
     * @brief   This function is invoked to print a register.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_REGISTER,
    /**
     * @brief   This function is invoked to print an absolute address.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS,
    /**
     * @brief   This function is invoked to print a memory displacement value.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_DISP,
    /**
     * @brief   This function is invoked to print an immediate value.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_IMM,

    /**
     * @brief   This function is invoked to print the size of a memory operand.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE,
    /**
     * @brief   This function is invoked to print the instruction prefixes.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES,
    /**
     * @brief   This function is invoked after formatting an operand to print a `EVEX`/`MVEX`
     *          decorator.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_FORMATTER_HOOK_MAX_VALUE = ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisDecoratorType` datatype.
 */
typedef ZydisU8 ZydisDecoratorType;

/**
 * @brief   Values that represent decorator-types.
 */
enum ZydisDecoratorTypes
{
    ZYDIS_DECORATOR_TYPE_INVALID,
    /**
     * @brief   The embedded-mask decorator.
     */
    ZYDIS_DECORATOR_TYPE_MASK,
    /**
     * @brief   The broadcast decorator.
     */
    ZYDIS_DECORATOR_TYPE_BC,
    /**
     * @brief   The rounding-control decorator.
     */
    ZYDIS_DECORATOR_TYPE_RC,
    /**
     * @brief   The suppress-all-exceptions decorator.
     */
    ZYDIS_DECORATOR_TYPE_SAE,
    /**
     * @brief   The register-swizzle decorator.
     */
    ZYDIS_DECORATOR_TYPE_SWIZZLE,
    /**
     * @brief   The conversion decorator.
     */
    ZYDIS_DECORATOR_TYPE_CONVERSION,
    /**
     * @brief   The eviction-hint decorator.
     */
    ZYDIS_DECORATOR_TYPE_EH,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_DECORATOR_TYPE_MAX_VALUE = ZYDIS_DECORATOR_TYPE_EH
};

/* ---------------------------------------------------------------------------------------------- */

typedef struct ZydisFormatter_ ZydisFormatter;

/**
 * @brief   Defines the `ZydisFormatterFunc` function pointer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   string      A pointer to the string.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   userData    A pointer to user-defined data.
 *
 * @return  A zydis status code.
 *
 * Returning a status code other than `ZYDIS_STATUS_SUCCESS` will immediately cause the formatting
 * process to fail.
 *
 * This function type is used for:
 * - `ZYDIS_FORMATTER_HOOK_PRE_INSTRUCTION`
 * - `ZYDIS_FORMATTER_HOOK_POST_INSTRUCTION`
 * - `ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION`
 * - `ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC`
 * - `ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES`
 */
typedef ZydisStatus (*ZydisFormatterFunc)(const ZydisFormatter* formatter,
    ZydisString* string, const ZydisDecodedInstruction* instruction, void* userData);

/**
 * @brief   Defines the `ZydisFormatterOperandFunc` function pointer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   string      A pointer to the string.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   operand     A pointer to the `ZydisDecodedOperand` struct.
 * @param   userData    A pointer to user-defined data.
 *
 * @return  A zydis status code.
 *
 * Returning a status code other than `ZYDIS_STATUS_SUCCESS` will immediately cause the formatting
 * process to fail (see exceptions below).
 *
 * Returning `ZYDIS_STATUS_SKIP_OPERAND` is valid for `ZYDIS_FORMATTER_HOOK_PRE_OPERAND`,
 * `ZYDIS_FORMATTER_HOOK_POST_OPERAND` and all of the `ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_XXX`
 * callbacks. This will cause the formatter to omit the current operand.
 *
 * DEPRECATED:
 * Returning `ZYDIS_STATUS_SUCCESS` without writing to the string is valid for
 * `ZYDIS_FORMATTER_HOOK_PRE_OPERAND`, `ZYDIS_FORMATTER_HOOK_POST_OPERAND` and all of the
 * `ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_XXX`. This will cause the formatter to omit the current
 * operand.
 *
 * This function type is used for:
 * - `ZYDIS_FORMATTER_HOOK_PRE_OPERAND`
 * - `ZYDIS_FORMATTER_HOOK_POST_OPERAND`
 * - `ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG`
 * - `ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM`
 * - `ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR`
 * - `ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM`
 * - `ZYDIS_FORMATTER_HOOK_PRINT_DISP`
 * - `ZYDIS_FORMATTER_HOOK_PRINT_IMM`
 * - `ZYDIS_FORMATTER_HOOK_PRINT_MEMSIZE`
 */
typedef ZydisStatus (*ZydisFormatterOperandFunc)(const ZydisFormatter* formatter,
    ZydisString* string, const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, void* userData);

 /**
 * @brief   Defines the `ZydisFormatterRegisterFunc` function pointer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   string      A pointer to the string.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   operand     A pointer to the `ZydisDecodedOperand` struct.
 * @param   reg         The register.
 * @param   userData    A pointer to user-defined data.
 *
 * @return  Returning a status code other than `ZYDIS_STATUS_SUCCESS` will immediately cause the
 *          formatting process to fail.
 *
 * This function type is used for:
 * - `ZYDIS_FORMATTER_HOOK_PRINT_REGISTER`.
 */
typedef ZydisStatus (*ZydisFormatterRegisterFunc)(const ZydisFormatter* formatter,
    ZydisString* string, const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, ZydisRegister reg, void* userData);

 /**
 * @brief   Defines the `ZydisFormatterAddressFunc` function pointer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   string      A pointer to the string.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   operand     A pointer to the `ZydisDecodedOperand` struct.
 * @param   address     The address.
 * @param   userData    A pointer to user-defined data.
 *
 * @return  Returning a status code other than `ZYDIS_STATUS_SUCCESS` will immediately cause the
 *          formatting process to fail.
 *
 * This function type is used for:
 * - `ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS`
 */
typedef ZydisStatus (*ZydisFormatterAddressFunc)(const ZydisFormatter* formatter,
    ZydisString* string, const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, ZydisU64 address, void* userData);

/**
 * @brief   Defines the `ZydisFormatterDecoratorFunc` function pointer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   string      A pointer to the string.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   operand     A pointer to the `ZydisDecodedOperand` struct.
 * @param   decorator   The decorator type.
 * @param   userData    A pointer to user-defined data.
 *
 * @return  Returning a status code other than `ZYDIS_STATUS_SUCCESS` will immediately cause the
 *          formatting process to fail.
 *
 * This function type is used for:
 * - `ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR`
 */
typedef ZydisStatus (*ZydisFormatterDecoratorFunc)(const ZydisFormatter* formatter,
    ZydisString* string, const ZydisDecodedInstruction* instruction,
    const ZydisDecodedOperand* operand, ZydisDecoratorType decorator, void* userData);

/* ---------------------------------------------------------------------------------------------- */
/* Formatter struct                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the `ZydisFormatter` struct.
 */
struct ZydisFormatter_
{
    ZydisLetterCase letterCase;
    ZydisBool forceMemorySegment;
    ZydisBool forceMemorySize;
    ZydisU8 formatAddress;
    ZydisU8 formatDisp;
    ZydisU8 formatImm;
    ZydisBool hexUppercase;
    ZydisString* hexPrefix;
    ZydisString hexPrefixData;
    ZydisString* hexSuffix;
    ZydisString hexSuffixData;
    ZydisU8 hexPaddingAddress;
    ZydisU8 hexPaddingDisp;
    ZydisU8 hexPaddingImm;
    ZydisFormatterFunc funcPreInstruction;
    ZydisFormatterFunc funcPostInstruction;
    ZydisFormatterOperandFunc funcPreOperand;
    ZydisFormatterOperandFunc funcPostOperand;
    ZydisFormatterFunc funcFormatInstruction;
    ZydisFormatterOperandFunc funcFormatOperandReg;
    ZydisFormatterOperandFunc funcFormatOperandMem;
    ZydisFormatterOperandFunc funcFormatOperandPtr;
    ZydisFormatterOperandFunc funcFormatOperandImm;
    ZydisFormatterFunc funcPrintMnemonic;
    ZydisFormatterRegisterFunc funcPrintRegister;
    ZydisFormatterAddressFunc funcPrintAddress;
    ZydisFormatterOperandFunc funcPrintDisp;
    ZydisFormatterOperandFunc funcPrintImm;
    ZydisFormatterOperandFunc funcPrintMemSize;
    ZydisFormatterFunc funcPrintPrefixes;
    ZydisFormatterDecoratorFunc funcPrintDecorator;
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Initializes the given `ZydisFormatter` instance.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   style       The formatter style.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style);

/**
 * @brief   Sets the value of the specified formatter `attribute`.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   property    The id of the formatter-property.
 * @param   value       The new value.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterSetProperty(ZydisFormatter* formatter,
    ZydisFormatterProperty property, ZydisUPointer value);

/**
 * @brief   Replaces a formatter function with a custom callback and/or retrieves the currently
 *          used function.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   hook        The formatter hook-type.
 * @param   callback    A pointer to a variable that contains the pointer of the callback function
 *                      and receives the pointer of the currently used function.
 *
 * @return  A zydis status code.
 *
 * Call this function with `callback` pointing to a `NULL` value to retrieve the currently used
 * function without replacing it.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterSetHook(ZydisFormatter* formatter,
    ZydisFormatterHookType hook, const void** callback);

/**
 * @brief   Formats the given instruction and writes it into the output buffer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterFormatInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZydisUSize bufferLen);

/**
 * @brief   Formats the given instruction and writes it into the output buffer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 * @param   userData    A pointer to user-defined data which can be used in custom formatter
 *                      callbacks.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, char* buffer, ZydisUSize bufferLen, void* userData);

/**
 * @brief   Formats the given operand and writes it into the output buffer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   index       The index of the operand to format.
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 *
 * @return  A zydis status code.
 *
 * Use `ZydisFormatterFormatInstruction` or `ZydisFormatterFormatInstructionEx` to format a
 * complete instruction.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterFormatOperand(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZydisU8 index, char* buffer, ZydisUSize bufferLen);

/**
 * @brief   Formats the given operand and writes it into the output buffer.
 *
 * @param   formatter   A pointer to the `ZydisFormatter` instance.
 * @param   instruction A pointer to the `ZydisDecodedInstruction` struct.
 * @param   index       The index of the operand to format.
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 * @param   userData    A pointer to user-defined data which can be used in custom formatter
 *                      callbacks.
 *
 * @return  A zydis status code.
 *
 * Use `ZydisFormatterFormatInstruction` or `ZydisFormatterFormatInstructionEx` to format a
 * complete instruction.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterFormatOperandEx(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, ZydisU8 index, char* buffer, ZydisUSize bufferLen,
    void* userData);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_FORMATTER_H */
