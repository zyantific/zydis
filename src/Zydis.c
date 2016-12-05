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

#include <Zydis/Zydis.h>

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

uint64_t ZydisGetVersion()
{
    return ZYDIS_VERSION;
}

ZydisBool ZydisIsFeatureEnabled(ZydisFeature feature)
{
    switch (feature)
    {
    case ZYDIS_FEATURE_IMPLICITLY_USED_REGISTERS:
#ifdef ZYDIS_ENABLE_FEATURE_IMPLICITLY_USED_REGISTERS
        return ZYDIS_TRUE;
#else
        return ZYDIS_FALSE;
#endif
    case ZYDIS_FEATURE_AFFECTED_FLAGS:
#ifdef ZYDIS_ENABLE_FEATURE_AFFECTED_FLAGS
        return ZYDIS_TRUE;
#else
        return ZYDIS_FALSE;
#endif
    case ZYDIS_FEATURE_CPUID:
#ifdef ZYDIS_ENABLE_FEATURE_CPUID
        return ZYDIS_TRUE;
#else
        return ZYDIS_FALSE;
#endif
    default:
        break;
    }
    return ZYDIS_FALSE;    
}

/* ============================================================================================== */
