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

static const ZydisStaticString registerStrings[] =
{
    ZYDIS_MAKE_STATIC_STRING("none"),
    // General purpose registers 8-bit
    ZYDIS_MAKE_STATIC_STRING("al"),       ZYDIS_MAKE_STATIC_STRING("cl"),
    ZYDIS_MAKE_STATIC_STRING("dl"),       ZYDIS_MAKE_STATIC_STRING("bl"),
    ZYDIS_MAKE_STATIC_STRING("ah"),       ZYDIS_MAKE_STATIC_STRING("ch"),
    ZYDIS_MAKE_STATIC_STRING("dh"),       ZYDIS_MAKE_STATIC_STRING("bh"),
    ZYDIS_MAKE_STATIC_STRING("spl"),      ZYDIS_MAKE_STATIC_STRING("bpl"),
    ZYDIS_MAKE_STATIC_STRING("sil"),      ZYDIS_MAKE_STATIC_STRING("dil"),
    ZYDIS_MAKE_STATIC_STRING("r8b"),      ZYDIS_MAKE_STATIC_STRING("r9b"),
    ZYDIS_MAKE_STATIC_STRING("r10b"),     ZYDIS_MAKE_STATIC_STRING("r11b"),
    ZYDIS_MAKE_STATIC_STRING("r12b"),     ZYDIS_MAKE_STATIC_STRING("r13b"),
    ZYDIS_MAKE_STATIC_STRING("r14b"),     ZYDIS_MAKE_STATIC_STRING("r15b"),
    // General purpose registers 16-bit
    ZYDIS_MAKE_STATIC_STRING("ax"),       ZYDIS_MAKE_STATIC_STRING("cx"),
    ZYDIS_MAKE_STATIC_STRING("dx"),       ZYDIS_MAKE_STATIC_STRING("bx"),
    ZYDIS_MAKE_STATIC_STRING("sp"),       ZYDIS_MAKE_STATIC_STRING("bp"),
    ZYDIS_MAKE_STATIC_STRING("si"),       ZYDIS_MAKE_STATIC_STRING("di"),
    ZYDIS_MAKE_STATIC_STRING("r8w"),      ZYDIS_MAKE_STATIC_STRING("r9w"),
    ZYDIS_MAKE_STATIC_STRING("r10w"),     ZYDIS_MAKE_STATIC_STRING("r11w"),
    ZYDIS_MAKE_STATIC_STRING("r12w"),     ZYDIS_MAKE_STATIC_STRING("r13w"),
    ZYDIS_MAKE_STATIC_STRING("r14w"),     ZYDIS_MAKE_STATIC_STRING("r15w"),
    // General purpose registers 32-bit
    ZYDIS_MAKE_STATIC_STRING("eax"),      ZYDIS_MAKE_STATIC_STRING("ecx"),
    ZYDIS_MAKE_STATIC_STRING("edx"),      ZYDIS_MAKE_STATIC_STRING("ebx"),
    ZYDIS_MAKE_STATIC_STRING("esp"),      ZYDIS_MAKE_STATIC_STRING("ebp"),
    ZYDIS_MAKE_STATIC_STRING("esi"),      ZYDIS_MAKE_STATIC_STRING("edi"),
    ZYDIS_MAKE_STATIC_STRING("r8d"),      ZYDIS_MAKE_STATIC_STRING("r9d"),
    ZYDIS_MAKE_STATIC_STRING("r10d"),     ZYDIS_MAKE_STATIC_STRING("r11d"),
    ZYDIS_MAKE_STATIC_STRING("r12d"),     ZYDIS_MAKE_STATIC_STRING("r13d"),
    ZYDIS_MAKE_STATIC_STRING("r14d"),     ZYDIS_MAKE_STATIC_STRING("r15d"),
    // General purpose registers 64-bi
    ZYDIS_MAKE_STATIC_STRING("rax"),      ZYDIS_MAKE_STATIC_STRING("rcx"),
    ZYDIS_MAKE_STATIC_STRING("rdx"),      ZYDIS_MAKE_STATIC_STRING("rbx"),
    ZYDIS_MAKE_STATIC_STRING("rsp"),      ZYDIS_MAKE_STATIC_STRING("rbp"),
    ZYDIS_MAKE_STATIC_STRING("rsi"),      ZYDIS_MAKE_STATIC_STRING("rdi"),
    ZYDIS_MAKE_STATIC_STRING("r8"),       ZYDIS_MAKE_STATIC_STRING("r9"),
    ZYDIS_MAKE_STATIC_STRING("r10"),      ZYDIS_MAKE_STATIC_STRING("r11"),
    ZYDIS_MAKE_STATIC_STRING("r12"),      ZYDIS_MAKE_STATIC_STRING("r13"),
    ZYDIS_MAKE_STATIC_STRING("r14"),      ZYDIS_MAKE_STATIC_STRING("r15"),
    // Floating point legacy registers
    ZYDIS_MAKE_STATIC_STRING("st0"),      ZYDIS_MAKE_STATIC_STRING("st1"),
    ZYDIS_MAKE_STATIC_STRING("st2"),      ZYDIS_MAKE_STATIC_STRING("st3"),
    ZYDIS_MAKE_STATIC_STRING("st4"),      ZYDIS_MAKE_STATIC_STRING("st5"),
    ZYDIS_MAKE_STATIC_STRING("st6"),      ZYDIS_MAKE_STATIC_STRING("st7"),
    // Floating point multimedia registers
    ZYDIS_MAKE_STATIC_STRING("mm0"),      ZYDIS_MAKE_STATIC_STRING("mm1"),
    ZYDIS_MAKE_STATIC_STRING("mm2"),      ZYDIS_MAKE_STATIC_STRING("mm3"),
    ZYDIS_MAKE_STATIC_STRING("mm4"),      ZYDIS_MAKE_STATIC_STRING("mm5"),
    ZYDIS_MAKE_STATIC_STRING("mm6"),      ZYDIS_MAKE_STATIC_STRING("mm7"),
    // Floating point vector registers 128-bit
    ZYDIS_MAKE_STATIC_STRING("xmm0"),     ZYDIS_MAKE_STATIC_STRING("xmm1"),
    ZYDIS_MAKE_STATIC_STRING("xmm2"),     ZYDIS_MAKE_STATIC_STRING("xmm3"),
    ZYDIS_MAKE_STATIC_STRING("xmm4"),     ZYDIS_MAKE_STATIC_STRING("xmm5"),
    ZYDIS_MAKE_STATIC_STRING("xmm6"),     ZYDIS_MAKE_STATIC_STRING("xmm7"),
    ZYDIS_MAKE_STATIC_STRING("xmm8"),     ZYDIS_MAKE_STATIC_STRING("xmm9"),
    ZYDIS_MAKE_STATIC_STRING("xmm10"),    ZYDIS_MAKE_STATIC_STRING("xmm11"),
    ZYDIS_MAKE_STATIC_STRING("xmm12"),    ZYDIS_MAKE_STATIC_STRING("xmm13"),
    ZYDIS_MAKE_STATIC_STRING("xmm14"),    ZYDIS_MAKE_STATIC_STRING("xmm15"),
    ZYDIS_MAKE_STATIC_STRING("xmm16"),    ZYDIS_MAKE_STATIC_STRING("xmm17"),
    ZYDIS_MAKE_STATIC_STRING("xmm18"),    ZYDIS_MAKE_STATIC_STRING("xmm19"),
    ZYDIS_MAKE_STATIC_STRING("xmm20"),    ZYDIS_MAKE_STATIC_STRING("xmm21"),
    ZYDIS_MAKE_STATIC_STRING("xmm22"),    ZYDIS_MAKE_STATIC_STRING("xmm23"),
    ZYDIS_MAKE_STATIC_STRING("xmm24"),    ZYDIS_MAKE_STATIC_STRING("xmm25"),
    ZYDIS_MAKE_STATIC_STRING("xmm26"),    ZYDIS_MAKE_STATIC_STRING("xmm27"),
    ZYDIS_MAKE_STATIC_STRING("xmm28"),    ZYDIS_MAKE_STATIC_STRING("xmm29"),
    ZYDIS_MAKE_STATIC_STRING("xmm30"),    ZYDIS_MAKE_STATIC_STRING("xmm31"),
    // Floating point vector registers 256-bit
    ZYDIS_MAKE_STATIC_STRING("ymm0"),     ZYDIS_MAKE_STATIC_STRING("ymm1"),
    ZYDIS_MAKE_STATIC_STRING("ymm2"),     ZYDIS_MAKE_STATIC_STRING("ymm3"),
    ZYDIS_MAKE_STATIC_STRING("ymm4"),     ZYDIS_MAKE_STATIC_STRING("ymm5"),
    ZYDIS_MAKE_STATIC_STRING("ymm6"),     ZYDIS_MAKE_STATIC_STRING("ymm7"),
    ZYDIS_MAKE_STATIC_STRING("ymm8"),     ZYDIS_MAKE_STATIC_STRING("ymm9"),
    ZYDIS_MAKE_STATIC_STRING("ymm10"),    ZYDIS_MAKE_STATIC_STRING("ymm11"),
    ZYDIS_MAKE_STATIC_STRING("ymm12"),    ZYDIS_MAKE_STATIC_STRING("ymm13"),
    ZYDIS_MAKE_STATIC_STRING("ymm14"),    ZYDIS_MAKE_STATIC_STRING("ymm15"),
    ZYDIS_MAKE_STATIC_STRING("ymm16"),    ZYDIS_MAKE_STATIC_STRING("ymm17"),
    ZYDIS_MAKE_STATIC_STRING("ymm18"),    ZYDIS_MAKE_STATIC_STRING("ymm19"),
    ZYDIS_MAKE_STATIC_STRING("ymm20"),    ZYDIS_MAKE_STATIC_STRING("ymm21"),
    ZYDIS_MAKE_STATIC_STRING("ymm22"),    ZYDIS_MAKE_STATIC_STRING("ymm23"),
    ZYDIS_MAKE_STATIC_STRING("ymm24"),    ZYDIS_MAKE_STATIC_STRING("ymm25"),
    ZYDIS_MAKE_STATIC_STRING("ymm26"),    ZYDIS_MAKE_STATIC_STRING("ymm27"),
    ZYDIS_MAKE_STATIC_STRING("ymm28"),    ZYDIS_MAKE_STATIC_STRING("ymm29"),
    ZYDIS_MAKE_STATIC_STRING("ymm30"),    ZYDIS_MAKE_STATIC_STRING("ymm31"),
    // Floating point vector registers 512-bit
    ZYDIS_MAKE_STATIC_STRING("zmm0"),     ZYDIS_MAKE_STATIC_STRING("zmm1"),
    ZYDIS_MAKE_STATIC_STRING("zmm2"),     ZYDIS_MAKE_STATIC_STRING("zmm3"),
    ZYDIS_MAKE_STATIC_STRING("zmm4"),     ZYDIS_MAKE_STATIC_STRING("zmm5"),
    ZYDIS_MAKE_STATIC_STRING("zmm6"),     ZYDIS_MAKE_STATIC_STRING("zmm7"),
    ZYDIS_MAKE_STATIC_STRING("zmm8"),     ZYDIS_MAKE_STATIC_STRING("zmm9"),
    ZYDIS_MAKE_STATIC_STRING("zmm10"),    ZYDIS_MAKE_STATIC_STRING("zmm11"),
    ZYDIS_MAKE_STATIC_STRING("zmm12"),    ZYDIS_MAKE_STATIC_STRING("zmm13"),
    ZYDIS_MAKE_STATIC_STRING("zmm14"),    ZYDIS_MAKE_STATIC_STRING("zmm15"),
    ZYDIS_MAKE_STATIC_STRING("zmm16"),    ZYDIS_MAKE_STATIC_STRING("zmm17"),
    ZYDIS_MAKE_STATIC_STRING("zmm18"),    ZYDIS_MAKE_STATIC_STRING("zmm19"),
    ZYDIS_MAKE_STATIC_STRING("zmm20"),    ZYDIS_MAKE_STATIC_STRING("zmm21"),
    ZYDIS_MAKE_STATIC_STRING("zmm22"),    ZYDIS_MAKE_STATIC_STRING("zmm23"),
    ZYDIS_MAKE_STATIC_STRING("zmm24"),    ZYDIS_MAKE_STATIC_STRING("zmm25"),
    ZYDIS_MAKE_STATIC_STRING("zmm26"),    ZYDIS_MAKE_STATIC_STRING("zmm27"),
    ZYDIS_MAKE_STATIC_STRING("zmm28"),    ZYDIS_MAKE_STATIC_STRING("zmm29"),
    ZYDIS_MAKE_STATIC_STRING("zmm30"),    ZYDIS_MAKE_STATIC_STRING("zmm31"),
    // Flags registers
    ZYDIS_MAKE_STATIC_STRING("flags"),    ZYDIS_MAKE_STATIC_STRING("eflags"),
    ZYDIS_MAKE_STATIC_STRING("rflags"),
    // Instruction-pointer registers
    ZYDIS_MAKE_STATIC_STRING("ip"),       ZYDIS_MAKE_STATIC_STRING("eip"),
    ZYDIS_MAKE_STATIC_STRING("rip"),
    // Segment registers
    ZYDIS_MAKE_STATIC_STRING("es"),       ZYDIS_MAKE_STATIC_STRING("cs"),
    ZYDIS_MAKE_STATIC_STRING("ss"),       ZYDIS_MAKE_STATIC_STRING("ds"),
    ZYDIS_MAKE_STATIC_STRING("fs"),       ZYDIS_MAKE_STATIC_STRING("gs"),
    // Table registers
    ZYDIS_MAKE_STATIC_STRING("gdtr"),     ZYDIS_MAKE_STATIC_STRING("ldtr"),
    ZYDIS_MAKE_STATIC_STRING("idtr"),     ZYDIS_MAKE_STATIC_STRING("tr"),
    // Test registers
    ZYDIS_MAKE_STATIC_STRING("tr0"),      ZYDIS_MAKE_STATIC_STRING("tr1"),
    ZYDIS_MAKE_STATIC_STRING("tr2"),      ZYDIS_MAKE_STATIC_STRING("tr3"),
    ZYDIS_MAKE_STATIC_STRING("tr4"),      ZYDIS_MAKE_STATIC_STRING("tr5"),
    ZYDIS_MAKE_STATIC_STRING("tr6"),      ZYDIS_MAKE_STATIC_STRING("tr7"),
    // Control registers
    ZYDIS_MAKE_STATIC_STRING("cr0"),      ZYDIS_MAKE_STATIC_STRING("cr1"),
    ZYDIS_MAKE_STATIC_STRING("cr2"),      ZYDIS_MAKE_STATIC_STRING("cr3"),
    ZYDIS_MAKE_STATIC_STRING("cr4"),      ZYDIS_MAKE_STATIC_STRING("cr5"),
    ZYDIS_MAKE_STATIC_STRING("cr6"),      ZYDIS_MAKE_STATIC_STRING("cr7"),
    ZYDIS_MAKE_STATIC_STRING("cr8"),      ZYDIS_MAKE_STATIC_STRING("cr9"),
    ZYDIS_MAKE_STATIC_STRING("cr10"),     ZYDIS_MAKE_STATIC_STRING("cr11"),
    ZYDIS_MAKE_STATIC_STRING("cr12"),     ZYDIS_MAKE_STATIC_STRING("cr13"),
    ZYDIS_MAKE_STATIC_STRING("cr14"),     ZYDIS_MAKE_STATIC_STRING("cr15"),
    // Debug registers
    ZYDIS_MAKE_STATIC_STRING("dr0"),      ZYDIS_MAKE_STATIC_STRING("dr1"),
    ZYDIS_MAKE_STATIC_STRING("dr2"),      ZYDIS_MAKE_STATIC_STRING("dr3"),
    ZYDIS_MAKE_STATIC_STRING("dr4"),      ZYDIS_MAKE_STATIC_STRING("dr5"),
    ZYDIS_MAKE_STATIC_STRING("dr6"),      ZYDIS_MAKE_STATIC_STRING("dr7"),
    ZYDIS_MAKE_STATIC_STRING("dr8"),      ZYDIS_MAKE_STATIC_STRING("dr9"),
    ZYDIS_MAKE_STATIC_STRING("dr10"),     ZYDIS_MAKE_STATIC_STRING("dr11"),
    ZYDIS_MAKE_STATIC_STRING("dr12"),     ZYDIS_MAKE_STATIC_STRING("dr13"),
    ZYDIS_MAKE_STATIC_STRING("dr14"),     ZYDIS_MAKE_STATIC_STRING("dr15"),
    // Mask registers
    ZYDIS_MAKE_STATIC_STRING("k0"),       ZYDIS_MAKE_STATIC_STRING("k1"),
    ZYDIS_MAKE_STATIC_STRING("k2"),       ZYDIS_MAKE_STATIC_STRING("k3"),
    ZYDIS_MAKE_STATIC_STRING("k4"),       ZYDIS_MAKE_STATIC_STRING("k5"),
    ZYDIS_MAKE_STATIC_STRING("k6"),       ZYDIS_MAKE_STATIC_STRING("k7"),
    // Bound registers
    ZYDIS_MAKE_STATIC_STRING("bnd0"),     ZYDIS_MAKE_STATIC_STRING("bnd1"),
    ZYDIS_MAKE_STATIC_STRING("bnd2"),     ZYDIS_MAKE_STATIC_STRING("bnd3"),
    ZYDIS_MAKE_STATIC_STRING("bndcfg"),   ZYDIS_MAKE_STATIC_STRING("bndstatus"),
    // Misc registers
    ZYDIS_MAKE_STATIC_STRING("mxcsr"),    ZYDIS_MAKE_STATIC_STRING("pkru"),
    ZYDIS_MAKE_STATIC_STRING("xcr0")
};

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
    { ZYDIS_REGCLASS_FLAGS    , ZYDIS_REGISTER_RFLAGS , ZYDIS_REGISTER_FLAGS  ,   0   ,   0 },
    { ZYDIS_REGCLASS_IP       , ZYDIS_REGISTER_RIP    , ZYDIS_REGISTER_IP     ,   0   ,   0 },
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
    if (reg >= ZYDIS_ARRAY_SIZE(registerStrings))
    {
        return ZYDIS_NULL;
    }
    return registerStrings[reg].buffer;
}

const ZydisStaticString* ZydisRegisterGetStaticString(ZydisRegister reg)
{
    if (reg >= ZYDIS_ARRAY_SIZE(registerStrings))
    {
        return ZYDIS_NULL;
    }
    return &registerStrings[reg];
}

/* ============================================================================================== */
