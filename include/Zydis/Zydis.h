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
 * @brief   Master include file, including everything else.
 */

#ifndef ZYDIS_H
#define ZYDIS_H

#include <Zydis/CommonTypes.h>
#include <Zydis/Decoder.h>
#include <Zydis/DecoderTypes.h>
#include <Zydis/Defines.h>
#include <Zydis/Formatter.h>
#include <Zydis/MetaInfo.h>
#include <Zydis/Mnemonic.h>
#include <Zydis/Register.h>   
#include <Zydis/SharedTypes.h>
#include <Zydis/Status.h>
#include <Zydis/String.h>
#include <Zydis/Utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Macros                                                                                         */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Constants                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   A macro that defines the zydis version.
 */
#define ZYDIS_VERSION (ZydisU64)0x0002000000000000

/* ---------------------------------------------------------------------------------------------- */
/* Helper macros                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

/**
 * @brief   Extracts the major-part of the zydis version.
 *
 * @param   version The zydis version value
 */
#define ZYDIS_VERSION_MAJOR(version) (ZydisU16)((version & 0xFFFF000000000000) >> 48)

/**
 * @brief   Extracts the minor-part of the zydis version.
 *
 * @param   version The zydis version value
 */
#define ZYDIS_VERSION_MINOR(version) (ZydisU16)((version & 0x0000FFFF00000000) >> 32)

/**
 * @brief   Extracts the patch-part of the zydis version.
 *
 * @param   version The zydis version value
 */
#define ZYDIS_VERSION_PATCH(version) (ZydisU16)((version & 0x00000000FFFF0000) >> 16)

/**
 * @brief   Extracts the build-part of the zydis version.
 *
 * @param   version The zydis version value
 */
#define ZYDIS_VERSION_BUILD(version) (ZydisU16)(version & 0x000000000000FFFF)

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Enums and types                                                                                */
/* ============================================================================================== */

/**
 * @brief   Defines the @c ZydisFeature datatype.
 */
typedef ZydisU8 ZydisFeature;

/**
 * @brief   Values that represent zydis features.
 */
enum ZydisFeatures
{
    ZYDIS_FEATURE_EVEX,
    ZYDIS_FEATURE_MVEX,
};

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/**
 * @brief   Returns the zydis version.
 *
 * @return  The zydis version.
 *          
 * Use the macros provided in this file to extract the major, minor, patch and build part from the 
 * returned version value.
 */
ZYDIS_EXPORT ZydisU64 ZydisGetVersion(void);

/**
 * @brief   Checks, if the specified feature is enabled in the current zydis library instance.
 *
 * @param   feature The feature.
 *
 * @return  @c True if the feature is enabled, @c false if not.
 */
ZYDIS_EXPORT ZydisBool ZydisIsFeatureEnabled(ZydisFeature feature);

/* ============================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ZYDIS_H */
