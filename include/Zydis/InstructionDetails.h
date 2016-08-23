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

#ifndef ZYDIS_INSTRUCTIONDETAILS_H
#define ZYDIS_INSTRUCTIONDETAILS_H

#include <stdint.h>
#include <stdbool.h>
#include <Zydis/Defines.h>
#include <Zydis/InstructionInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* CPUID                                                                                          */  
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Enums and types                                                                                */  
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Defines the zydis cpuid-feature-flag datatype.
 */
typedef uint8_t ZydisCPUIDFeatureFlag;

/**
 * @brief   Values that represent zydis cpuid feature flags.
 */
enum ZydisCPUIDFeatureFlags
{
    ZYDIS_CPUID_FEATURE_NONE
};

/* ---------------------------------------------------------------------------------------------- */
/* Exported functions                                                                             */  
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Retrieves the first CPUID feature-flag of the given instruction.
 *
 * @param   info        A pointer to the instruction-info struct.
 * @param   featureFlag A pointer to the memory that receives the first CPUID feature-flag.
 *
 * @return  @c True if the function succeeds, @c false if the instruction does not have any CPUID
 *          feature-flags assigned.
 */
ZYDIS_EXPORT bool ZydisGetFirstCPUIDFeatureFlag(const ZydisInstructionInfo* info,
    ZydisCPUIDFeatureFlag* featureFlag);

/**
 * @brief   Retrieves the next CPUID feature-flag of the given instruction.
 *
 * @param   info        A pointer to the instruction-info struct.
 * @param   featureFlag A pointer to the memory that contains the last CPUID feature-flag and 
 *                      receives the next one.
 *
 * @return  @c True if the function succeeds, @c false if the instruction does not have another 
 *          CPUID feature-flag assigned.
 */
ZYDIS_EXPORT bool ZydisGetNextCPUIDFeatureFlag(const ZydisInstructionInfo* info,
    ZydisCPUIDFeatureFlag* featureFlag);

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_INSTRUCTIONDETAILS_H */
