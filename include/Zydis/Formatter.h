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
 * @brief   Defines the @c ZydisFormatterStyle datatype.
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
 * @brief   Defines the @c ZydisFormatterProperty datatype.
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
    ZYDIS_FORMATTER_PROP_FORCE_SEGMENTS,
    /**
     * @brief   Controls the printing of operand-sizes. 
     * 
     * Pass `ZYDIS_TRUE` as value to force the formatter to always print the size of memory-operands 
     * or `ZYDIS_FALSE` to only print it on demand.
     * 
     * The default value is `ZYDIS_FALSE`.
     */
    ZYDIS_FORMATTER_PROP_FORCE_OPERANDSIZE,

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
     * The default value is `0x`.
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
/* Address format constants                                                                       */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent address-formats.
 */
enum ZydisAddressFormat
{   
    /**
     * @brief   Displays absolute addresses instead of relative ones.
     */
    ZYDIS_ADDR_FORMAT_ABSOLUTE,
    /**
     * @brief   Uses signed hexadecimal values to display relative addresses.
     *          
     * Examples:
     * "JMP  0x20"
     * "JMP -0x20"
     */
    ZYDIS_ADDR_FORMAT_RELATIVE_SIGNED,
    /**
     * @brief   Uses unsigned hexadecimal values to display relative addresses.
     *          
     * Examples:
     * "JMP 0x20"
     * "JMP 0xE0"
     */
    ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_ADDR_FORMAT_MAX_VALUE = ZYDIS_ADDR_FORMAT_RELATIVE_UNSIGNED
};

/* ---------------------------------------------------------------------------------------------- */
/* Displacement formats                                                                           */
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
     * "MOV EAX, DWORD PTR SS:[ESP+0x400]"
     * "MOV EAX, DWORD PTR SS:[ESP-0x400]"
     */
    ZYDIS_DISP_FORMAT_HEX_SIGNED,
    /**
     * @brief   Formats displacements as unsigned hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, DWORD PTR SS:[ESP+0x400]"
     * "MOV EAX, DWORD PTR SS:[ESP+0xFFFFFC00]"
     */
    ZYDIS_DISP_FORMAT_HEX_UNSIGNED,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_DISP_FORMAT_MAX_VALUE = ZYDIS_DISP_FORMAT_HEX_UNSIGNED
};

/* ---------------------------------------------------------------------------------------------- */
/* Immediate formats                                                                              */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Values that represent formatter immediate-formats.
 */
enum ZydisImmediateFormat
{
    /**
     * @brief   Automatically chooses the most suitable formatting-mode based on the operands
     *          @c ZydisOperandInfo.imm.isSigned attribute.
     */
    ZYDIS_IMM_FORMAT_HEX_AUTO,
    /**
     * @brief   Formats immediates as signed hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, 0x400"
     * "MOV EAX, -0x400"
     */
    ZYDIS_IMM_FORMAT_HEX_SIGNED,
    /**
     * @brief   Formats immediates as unsigned hexadecimal values.
     *          
     * Examples: 
     * "MOV EAX, 0x400"
     * "MOV EAX, 0xFFFFFC00"
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
 * @brief   Defines the @c ZydisFormatterHookType datatype.
 */
typedef ZydisU8 ZydisFormatterHookType;

/**
 * @brief   Values that represent formatter hook-types.
 */
enum ZydisFormatterHookTypes
{
    /**
     * @brief   This function is called before the formatter starts formatting an instruction.
     */
    ZYDIS_FORMATTER_HOOK_PRE,
    /**
     * @brief   This function is called before the formatter finished formatting an instruction.
     */
    ZYDIS_FORMATTER_HOOK_POST,
    /**
     * @brief   This function refers to the main formatting function, that internally calls all  
     *          other function except the ones that are hooked by @c ZYDIS_FORMATTER_HOOK_PRE and 
     *          @c ZYDIS_FORMATTER_HOOK_POST.
     *          
     * Replacing this function allows for complete custom formatting, but indirectly disables all 
     * other hooks except for @c ZYDIS_FORMATTER_HOOK_PRE and @c ZYDIS_FORMATTER_HOOK_POST. 
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION,
    /**
     * @brief   This function is called to print the instruction prefixes.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES,
    /**
     * @brief   This function is called to print the instruction mnemonic.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC,
    /**
     * @brief   This function is called to format an register operand.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG,
    /**
     * @brief   This function is called to format an memory operand.
     *
     * Replacing this function might indirectly disable some specific calls to the 
     * @c ZYDIS_FORMATTER_PRINT_ADDRESS and @c ZYDIS_FORMATTER_HOOK_PRINT_DISPLACEMENT functions.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM,
    /**
     * @brief   This function is called to format an pointer operand.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR,
    /**
     * @brief   This function is called to format an immediate operand.
     *
     * Replacing this function might indirectly disable some specific calls to the 
     * @c ZYDIS_FORMATTER_PRINT_ADDRESS and @c ZYDIS_FORMATTER_HOOK_PRINT_IMMEDIATE functions.
     */
    ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM,  
    /**
     * @brief   This function is called right before formatting an memory operand to print the 
     *          optional size-specifier.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_OPERANDSIZE,
    /**
     * @brief   This function is called right before formatting an memory operand to print the 
     *          optional segment-register.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_SEGMENT,
    /**
     * @brief   This function is called right after formatting an operand to print the optional 
     *          EVEX/MVEX operand-decorator.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR,
    /**
     * @brief   This function is called to print an absolute address.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS,
    /**
     * @brief   This function is called to print a memory displacement value.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_DISPLACEMENT,
    /**
     * @brief   This function is called to print an immediate value.
     */
    ZYDIS_FORMATTER_HOOK_PRINT_IMMEDIATE,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_FORMATTER_HOOK_MAX_VALUE = ZYDIS_FORMATTER_HOOK_PRINT_IMMEDIATE
};

/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisDecoratorType datatype.
 */
typedef ZydisU8 ZydisDecoratorType;

/**
 * @brief   Values that represent decorator-types.
 */
enum ZydisDecoratorTypes
{
    ZYDIS_DECORATOR_TYPE_INVALID,
    ZYDIS_DECORATOR_TYPE_MASK,
    ZYDIS_DECORATOR_TYPE_BROADCAST,
    ZYDIS_DECORATOR_TYPE_ROUNDING_CONTROL,
    ZYDIS_DECORATOR_TYPE_SAE,
    ZYDIS_DECORATOR_TYPE_SWIZZLE,
    ZYDIS_DECORATOR_TYPE_CONVERSION,
    ZYDIS_DECORATOR_TYPE_EVICTION_HINT,
    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_DECORATOR_TYPE_MAX_VALUE = ZYDIS_DECORATOR_TYPE_EVICTION_HINT
};

/* ---------------------------------------------------------------------------------------------- */

typedef struct ZydisFormatter_ ZydisFormatter;

/**
 * @brief   Defines the @c ZydisFormatterNotifyFunc function pointer.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
 * @param   userData    A pointer to user-defined data.
 * 
 * @return  Returning a status code other than @c ZYDIS_STATUS_SUCCESS will immediately cause the 
 *          formatting process to fail.
 * 
 * This function type is used for the @c ZYDIS_FORMATTER_HOOK_PRE and
 * @c ZYDIS_FORMATTER_HOOK_POST hook-types.
 */
typedef ZydisStatus (*ZydisFormatterNotifyFunc)(const ZydisFormatter* formatter, 
    ZydisString* buffer, const ZydisDecodedInstruction* instruction, void* userData);

/**
 * @brief   Defines the @c ZydisFormatterFormatFunc function pointer.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   str         A pointer to the string buffer.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
 * @param   userData    A pointer to user-defined data.
 * 
 * @return  Returning a status code other than @c ZYDIS_STATUS_SUCCESS will immediately cause the 
 *          formatting process to fail.
 * 
 * After appending text to the @c buffer you MUST increase the buffer-pointer by the size of the
 * number of chars written. Not increasing the buffer-pointer will cause unexpected behavior.
 *
 * This function type is used for the @c ZYDIS_FORMATTER_HOOK_FORMAT_INSTRUCTION, 
 * @c ZYDIS_FORMATTER_HOOK_PRINT_PREFIXES and @c ZYDIS_FORMATTER_HOOK_PRINT_MNEMONIC hook-types.
 */
typedef ZydisStatus (*ZydisFormatterFormatFunc)(const ZydisFormatter* formatter, 
    ZydisString* buffer, const ZydisDecodedInstruction* instruction, void* userData);

/**
 * @brief   Defines the @c ZydisFormatterFormatOperandFunc function pointer.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   str         A pointer to the string buffer.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
 * @param   operand     A pointer to the @c ZydisDecodedOperand struct.
 * @param   userData    A pointer to user-defined data.
 * 
 * @return  Returning a status code other than @c ZYDIS_STATUS_SUCCESS will immediately cause the 
 *          formatting process to fail.
 * 
 * After appending text to the @c buffer you MUST increase the buffer-pointer by the size of the
 * number of chars written.
 * 
 * Returning @c ZYDIS_STATUS_SUCCESS in one of the @c ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_X hooks 
 * without increasing the buffer-pointer is valid and will cause the formatter to omit the current 
 * operand.
 * 
 * Returning @c ZYDIS_STATUS_SUCCESS in @c ZYDIS_FORMATTER_HOOK_PRINT_OPERANDSIZE, 
 * @c ZYDIS_FORMATTER_HOOK_PRINT_SEGMENT or @c ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR without 
 * increasing the buffer-pointer is valid and signals that the corresponding element should not be 
 * printed for the current operand.
 * 
 * Not increasing the buffer-pointer for any other hook-type will cause unexpected behavior.
 *
 * This function type is used for the @c ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_REG,
 * @c ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_MEM, @c ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_PTR, 
 * @c ZYDIS_FORMATTER_HOOK_FORMAT_OPERAND_IMM, @c ZYDIS_FORMATTER_HOOK_PRINT_OPERANDSIZE,
 * @c ZYDIS_FORMATTER_HOOK_PRINT_SEGMENT, @c ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR,
 * @c ZYDIS_FORMATTER_HOOK_PRINT_DISPLACEMENT and @c ZYDIS_FORMATTER_HOOK_PRINT_IMMEDIATE 
 * hook-types.
 */
typedef ZydisStatus (*ZydisFormatterFormatOperandFunc)(const ZydisFormatter* formatter, 
    ZydisString* buffer, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, void* userData);

 /**
 * @brief   Defines the @c ZydisFormatterFormatAddressFunc function pointer.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   str         A pointer to the string buffer.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
 * @param   operand     A pointer to the @c ZydisDecodedOperand struct.
 * @param   userData    A pointer to user-defined data.
 * 
 * @return  Returning a status code other than @c ZYDIS_STATUS_SUCCESS will immediately cause the 
 *          formatting process to fail.
 * 
 * After appending text to the @c buffer you MUST increase the buffer-pointer by the size of the
 * number of chars written.
 * Not increasing the buffer-pointer will cause unexpected behavior.
 *
 * This function type is used for the @c ZYDIS_FORMATTER_HOOK_PRINT_ADDRESS hook-type.
 */
typedef ZydisStatus (*ZydisFormatterFormatAddressFunc)(const ZydisFormatter* formatter, 
    ZydisString* buffer, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, ZydisU64 address, void* userData);

/**
 * @brief   Defines the @c ZydisFormatterFormatDecoratorFunc function pointer.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   str         A pointer to the string buffer.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
 * @param   operand     A pointer to the @c ZydisDecodedOperand struct.
 * @param   type        The decorator type.
 * @param   userData    A pointer to user-defined data.
 * 
 * @return  Returning a status code other than @c ZYDIS_STATUS_SUCCESS will immediately cause the 
 *          formatting process to fail.
 * 
 * After appending text to the @c buffer you MUST increase the buffer-pointer by the size of the
 * number of chars written.
 * 
 * Returning @c ZYDIS_STATUS_SUCCESS without increasing the buffer-pointer is valid and will cause 
 * the formatter to omit the current decorator.
 *
 * This function type is used for the @c ZYDIS_FORMATTER_HOOK_PRINT_DECORATOR hook-type.
 */
typedef ZydisStatus (*ZydisFormatterFormatDecoratorFunc)(const ZydisFormatter* formatter, 
    ZydisString* buffer, const ZydisDecodedInstruction* instruction, 
    const ZydisDecodedOperand* operand, ZydisDecoratorType type, void* userData);

/* ---------------------------------------------------------------------------------------------- */
/* Formatter struct                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisFormatter struct.
 */
struct ZydisFormatter_
{
    ZydisU8 letterCase;
    ZydisBool forceSegments;
    ZydisBool forceOperandSize;
    ZydisU8 addressFormat;
    ZydisU8 displacementFormat;
    ZydisU8 immediateFormat;
    ZydisBool hexUppercase;
    char* hexPrefix;
    char* hexSuffix;
    ZydisU8 hexPaddingAddress;
    ZydisU8 hexPaddingDisplacement;
    ZydisU8 hexPaddingImmediate;
    ZydisFormatterNotifyFunc funcPre;
    ZydisFormatterNotifyFunc funcPost;
    ZydisFormatterFormatFunc funcFormatInstruction;
    ZydisFormatterFormatFunc funcPrintPrefixes;
    ZydisFormatterFormatFunc funcPrintMnemonic;
    ZydisFormatterFormatOperandFunc funcFormatOperandReg;
    ZydisFormatterFormatOperandFunc funcFormatOperandMem;
    ZydisFormatterFormatOperandFunc funcFormatOperandPtr;
    ZydisFormatterFormatOperandFunc funcFormatOperandImm;
    ZydisFormatterFormatOperandFunc funcPrintOperandSize;
    ZydisFormatterFormatOperandFunc funcPrintSegment;
    ZydisFormatterFormatDecoratorFunc funcPrintDecorator;
    ZydisFormatterFormatAddressFunc funcPrintAddress;
    ZydisFormatterFormatOperandFunc funcPrintDisplacement;
    ZydisFormatterFormatOperandFunc funcPrintImmediate; 
};

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Initializes the given @c ZydisFormatter instance.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   style       The formatter style.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterInit(ZydisFormatter* formatter, ZydisFormatterStyle style);

/**
 * @brief   Sets the value of the specified formatter `attribute`.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   property    The id of the formatter-property.
 * @param   value       The new value.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterSetProperty(ZydisFormatter* formatter,
    ZydisFormatterProperty property, ZydisUSize value);

/**
 * @brief   Replaces a formatter function with a custom callback and/or retrieves the currently
 *          used function.
 *
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
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
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
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
 * @param   formatter   A pointer to the @c ZydisFormatter instance.
 * @param   instruction A pointer to the @c ZydisDecodedInstruction struct.
 * @param   buffer      A pointer to the output buffer.
 * @param   bufferLen   The length of the output buffer.
 * @param   userData    A pointer to user-defined data which can be used in custom formatter 
 *                      callbacks.
 *
 * @return  A zydis status code.
 */
ZYDIS_EXPORT ZydisStatus ZydisFormatterFormatInstructionEx(const ZydisFormatter* formatter, 
    const ZydisDecodedInstruction* instruction, char* buffer, ZydisUSize bufferLen, void* userData);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_FORMATTER_H */
