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
 * @brief   Utility functions and constants for registers.
 */

#ifndef ZYDIS_REGISTER_H
#define ZYDIS_REGISTER_H

#include <Zydis/Defines.h>
#include <Zydis/CommonTypes.h>
#include <Zydis/String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Registers                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

#include <Zydis/Generated/EnumRegister.h>

/* ---------------------------------------------------------------------------------------------- */
/* Register classes                                                                               */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisRegisterClass datatype.
 */
typedef ZydisU8 ZydisRegisterClass;

/**
 * @brief   Values that represent zydis register-classes.
 */
enum ZydisRegisterClasses
{
    ZYDIS_REGCLASS_INVALID,
    /**
     * @brief   8-bit general-purpose registers.
     */
    ZYDIS_REGCLASS_GPR8,
    /**
     * @brief   16-bit general-purpose registers.
     */
    ZYDIS_REGCLASS_GPR16,
    /**
     * @brief   32-bit general-purpose registers.
     */
    ZYDIS_REGCLASS_GPR32,
    /**
     * @brief   64-bit general-purpose registers.
     */
    ZYDIS_REGCLASS_GPR64,
    /**
     * @brief   Floating point legacy registers.
     */
    ZYDIS_REGCLASS_X87,
    /**
     * @brief   Floating point multimedia registers.
     */
    ZYDIS_REGCLASS_MMX,
    /**
     * @brief   128-bit vector registers.
     */
    ZYDIS_REGCLASS_XMM,
    /**
     * @brief   256-bit vector registers.
     */
    ZYDIS_REGCLASS_YMM,
    /**
     * @brief   512-bit vector registers.
     */
    ZYDIS_REGCLASS_ZMM,
    /**
     * @brief   Flags registers.
     */
    ZYDIS_REGCLASS_FLAGS,
    /**
     * @brief   Instruction-pointer registers.
     */
    ZYDIS_REGCLASS_IP,
    /**
     * @brief   Segment registers.
     */
    ZYDIS_REGCLASS_SEGMENT,
    /**
     * @brief   Test registers.
     */
    ZYDIS_REGCLASS_TEST,
    /**
     * @brief   Control registers.
     */
    ZYDIS_REGCLASS_CONTROL,
    /**
     * @brief   Debug registers.
     */
    ZYDIS_REGCLASS_DEBUG,
    /**
     * @brief   Mask registers.
     */
    ZYDIS_REGCLASS_MASK,
    /**
     * @brief   Bound registers.
     */
    ZYDIS_REGCLASS_BOUND,

    /**
     * @brief   Maximum value of this enum.
     */
    ZYDIS_REGCLASS_MAX_VALUE = ZYDIS_REGCLASS_BOUND
};

/* ---------------------------------------------------------------------------------------------- */
/* Register width                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the @c ZydisRegisterWidth datatype.
 */
typedef ZydisU16 ZydisRegisterWidth;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Returns the register specified by the @c registerClass and the @c id.
 *
 * @param   registerClass   The register class.
 * @param   id              The register id.
 *
 * @return  The register specified by the @c registerClass and the @c id or @c ZYDIS_REGISTER_NONE,
 *          if an invalid parameter was passed.
 */
ZYDIS_EXPORT ZydisRegister ZydisRegisterEncode(ZydisRegisterClass registerClass, ZydisU8 id);

/**
 * @brief   Returns the id of the specified register.
 *
 * @param   reg The register.
 *
 * @return  The id of the specified register, or -1 if an invalid parameter was passed.
 */
ZYDIS_EXPORT ZydisI16 ZydisRegisterGetId(ZydisRegister reg);

/**
 * @brief   Returns the register-class of the specified register.
 *
 * @param   reg The register.
 *
 * @return  The register-class of the specified register.
 */
ZYDIS_EXPORT ZydisRegisterClass ZydisRegisterGetClass(ZydisRegister reg);

/**
 * @brief   Returns the width of the specified register.
 *
 * @param   reg The register.
 *
 * @return  The width of the specified register.
 */
ZYDIS_EXPORT ZydisRegisterWidth ZydisRegisterGetWidth(ZydisRegister reg);

/**
 * @brief   Returns the width of the specified register in 64-bit mode.
 *
 * @param   reg The register.
 *
 * @return  The width of the specified register.
 */
ZYDIS_EXPORT ZydisRegisterWidth ZydisRegisterGetWidth64(ZydisRegister reg);

/**
 * @brief   Returns the specified register string.
 *
 * @param   reg The register.
 *
 * @return  The register string or @c NULL, if an invalid register was passed.
 */
ZYDIS_EXPORT const char* ZydisRegisterGetString(ZydisRegister reg);

/**
 * @brief   Returns the specified register string as `ZydisStaticString`.
 *
 * @param   reg The register.
 *
 * @return  The register string or @c NULL, if an invalid register was passed.
 *
 * The `buffer` of the returned struct is guaranteed to be zero-terminated in this special case.
 */
ZYDIS_EXPORT const ZydisStaticString* ZydisRegisterGetStaticString(ZydisRegister reg);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_REGISTER_H */
