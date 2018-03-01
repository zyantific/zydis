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

#include <Zydis/Register.h>

/* ============================================================================================== */
/* Register strings                                                                               */
/* ============================================================================================== */

#include <Generated/EnumRegister.inc>

/* ============================================================================================== */
/* Register-class mapping                                                                         */
/* ============================================================================================== */

struct ZydisRegisterMapItem
{
    ZydisRegisterClass class;
    ZydisRegister lo;
    ZydisRegister hi;
    ZydisRegisterWidth width;
    ZydisRegisterWidth width64;
};

static const struct ZydisRegisterMapItem registerMap[] =
{
    { ZYDIS_REGCLASS_INVALID  , ZYDIS_REGISTER_NONE   , ZYDIS_REGISTER_NONE   ,   0   ,   0 },
    { ZYDIS_REGCLASS_GPR8     , ZYDIS_REGISTER_AL     , ZYDIS_REGISTER_R15B   ,   8   ,   8 },
    { ZYDIS_REGCLASS_GPR16    , ZYDIS_REGISTER_AX     , ZYDIS_REGISTER_R15W   ,  16   ,  16 },
    { ZYDIS_REGCLASS_GPR32    , ZYDIS_REGISTER_EAX    , ZYDIS_REGISTER_R15D   ,  32   ,  32 },
    { ZYDIS_REGCLASS_GPR64    , ZYDIS_REGISTER_RAX    , ZYDIS_REGISTER_R15    ,   0   ,  64 },
    { ZYDIS_REGCLASS_X87      , ZYDIS_REGISTER_ST0    , ZYDIS_REGISTER_ST7    ,  80   ,  80 },
    { ZYDIS_REGCLASS_MMX      , ZYDIS_REGISTER_MM0    , ZYDIS_REGISTER_MM7    ,  64   ,  64 },
    { ZYDIS_REGCLASS_XMM      , ZYDIS_REGISTER_XMM0   , ZYDIS_REGISTER_XMM31  , 128   , 128 },
    { ZYDIS_REGCLASS_YMM      , ZYDIS_REGISTER_YMM0   , ZYDIS_REGISTER_YMM31  , 256   , 256 },
    { ZYDIS_REGCLASS_ZMM      , ZYDIS_REGISTER_ZMM0   , ZYDIS_REGISTER_ZMM31  , 512   , 512 },
    { ZYDIS_REGCLASS_FLAGS    , ZYDIS_REGISTER_FLAGS  , ZYDIS_REGISTER_RFLAGS ,   0   ,   0 },
    { ZYDIS_REGCLASS_IP       , ZYDIS_REGISTER_IP     , ZYDIS_REGISTER_RIP    ,   0   ,   0 },
    { ZYDIS_REGCLASS_SEGMENT  , ZYDIS_REGISTER_ES     , ZYDIS_REGISTER_GS     ,  16   ,  16 },
    { ZYDIS_REGCLASS_TEST     , ZYDIS_REGISTER_TR0    , ZYDIS_REGISTER_TR7    ,  32   ,  32 },
    { ZYDIS_REGCLASS_CONTROL  , ZYDIS_REGISTER_CR0    , ZYDIS_REGISTER_CR15   ,  32   ,  64 },
    { ZYDIS_REGCLASS_DEBUG    , ZYDIS_REGISTER_DR0    , ZYDIS_REGISTER_DR15   ,  32   ,  64 },
    { ZYDIS_REGCLASS_MASK     , ZYDIS_REGISTER_K0     , ZYDIS_REGISTER_K7     ,   0   ,   0 },
    { ZYDIS_REGCLASS_BOUND    , ZYDIS_REGISTER_BND0   , ZYDIS_REGISTER_BND3   , 128   , 128 }
};

static const ZydisU8 registerMapCount = sizeof(registerMap) / sizeof(struct ZydisRegisterMapItem);

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZydisRegister ZydisRegisterEncode(ZydisRegisterClass registerClass, ZydisU8 id)
{
    switch (registerClass)
    {
    case ZYDIS_REGCLASS_INVALID:
    case ZYDIS_REGCLASS_FLAGS:
    case ZYDIS_REGCLASS_IP:
        break;
    default:
        if ((registerClass < registerMapCount) &&
            (id <= (registerMap[registerClass].hi - registerMap[registerClass].lo)))
        {
            return registerMap[registerClass].lo + id;
        }
    }
    return ZYDIS_REGISTER_NONE;
}

ZydisI16 ZydisRegisterGetId(ZydisRegister reg)
{
    for (unsigned i = 0; i < registerMapCount; ++i)
    {
        switch (registerMap[i].class)
        {
        case ZYDIS_REGCLASS_INVALID:
        case ZYDIS_REGCLASS_FLAGS:
        case ZYDIS_REGCLASS_IP:
            break;
        default:
            if ((reg >= registerMap[i].lo) && (reg <= registerMap[i].hi))
            {
                return reg - registerMap[i].lo;
            }
        }
    }
    return -1;
}

ZydisRegisterClass ZydisRegisterGetClass(ZydisRegister reg)
{
    for (unsigned i = 0; i < registerMapCount; ++i)
    {
        if ((reg >= registerMap[i].lo) && (reg <= registerMap[i].hi))
        {
            return registerMap[i].class;
        }
    }
    return ZYDIS_REGCLASS_INVALID;
}

ZydisRegisterWidth ZydisRegisterGetWidth(ZydisRegister reg)
{
    // Special cases
    switch (reg)
    {
    case ZYDIS_REGISTER_IP:
    case ZYDIS_REGISTER_FLAGS:
        return 16;
    case ZYDIS_REGISTER_EIP:
    case ZYDIS_REGISTER_EFLAGS:
        return 32;
    case ZYDIS_REGISTER_RIP:
    case ZYDIS_REGISTER_RFLAGS:
        return 64;
    default:
        break;
    }

    // Register classes
    for (unsigned i = 0; i < registerMapCount; ++i)
    {
        if ((reg >= registerMap[i].lo) && (reg <= registerMap[i].hi))
        {
            return registerMap[i].width;
        }
    }
    return 0;
}

ZydisRegisterWidth ZydisRegisterGetWidth64(ZydisRegister reg)
{
    // Special cases
    switch (reg)
    {
    case ZYDIS_REGISTER_IP:
    case ZYDIS_REGISTER_FLAGS:
        return 16;
    case ZYDIS_REGISTER_EIP:
    case ZYDIS_REGISTER_EFLAGS:
        return 32;
    case ZYDIS_REGISTER_RIP:
    case ZYDIS_REGISTER_RFLAGS:
        return 64;
    default:
        break;
    }

    // Register classes
    for (unsigned i = 0; i < registerMapCount; ++i)
    {
        if ((reg >= registerMap[i].lo) && (reg <= registerMap[i].hi))
        {
            return registerMap[i].width64;
        }
    }
    return 0;
}

const char* ZydisRegisterGetString(ZydisRegister reg)
{
    if (reg >= ZYDIS_ARRAY_SIZE(zydisRegisterStrings))
    {
        return ZYDIS_NULL;
    }
    return zydisRegisterStrings[reg].buffer;
}

const ZydisStaticString* ZydisRegisterGetStaticString(ZydisRegister reg)
{
    if (reg >= ZYDIS_ARRAY_SIZE(zydisRegisterStrings))
    {
        return ZYDIS_NULL;
    }
    return &zydisRegisterStrings[reg];
}

/* ============================================================================================== */
