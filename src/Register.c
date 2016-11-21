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

#include <stddef.h>
#include <stdbool.h>
#include <Zydis/Register.h>

/* ============================================================================================== */
/* Register strings                                                                               */
/* ============================================================================================== */

const char* registerStrings[] =
{
    "none",
    // General purpose registers 64-bit
    "rax",    "rcx",    "rdx",   "rbx",    
    "rsp",    "rbp",    "rsi",   "rdi",
    "r8",     "r9",     "r10",   "r11",    
    "r12",    "r13",    "r14",   "r15",
    // General purpose registers 32-bit
    "eax",    "ecx",    "edx",   "ebx",    
    "esp",    "ebp",    "esi",   "edi",
    "r8d",    "r9d",    "r10d",  "r11d",   
    "r12d",   "r13d",   "r14d",  "r15d",
    // General purpose registers 16-bit
    "ax",     "cx",     "dx",    "bx",     
    "sp",     "bp",     "si",    "di",
    "r8w",    "r9w",    "r10w",  "r11w",   
    "r12w",   "r13w",   "r14w",  "r15w",
    // General purpose registers  8-bit
    "al",     "cl",     "dl",    "bl",     
    "ah",     "ch",     "dh",    "bh",
    "spl",    "bpl",    "sil",   "dil",
    "r8b",    "r9b",    "r10b",  "r11b",   
    "r12b",   "r13b",   "r14b",  "r15b",
    // Floating point legacy registers
    "st0",    "st1",    "st2",   "st3",    
    "st4",    "st5",    "st6",   "st7",
    // Floating point multimedia registers
    "mm0",    "mm1",    "mm2",   "mm3",    
    "mm4",    "mm5",    "mm6",   "mm7",
    // Floating point vector registers 512-bit
    "zmm0",   "zmm1",   "zmm2",  "zmm3",   
    "zmm4",   "zmm5",   "zmm6",  "zmm7",
    "zmm8",   "zmm9",   "zmm10", "zmm11",  
    "zmm12",  "zmm13",  "zmm14", "zmm15",
    "zmm16",  "zmm17",  "zmm18", "zmm19",  
    "zmm20",  "zmm21",  "zmm22", "zmm23",
    "zmm24",  "zmm25",  "zmm26", "zmm27",  
    "zmm28",  "zmm29",  "zmm30", "zmm31",
    // Floating point vector registers 256-bit
    "ymm0",   "ymm1",   "ymm2",  "ymm3",   
    "ymm4",   "ymm5",   "ymm6",  "ymm7",
    "ymm8",   "ymm9",   "ymm10", "ymm11",  
    "ymm12",  "ymm13",  "ymm14", "ymm15",
    "ymm16",  "ymm17",  "ymm18", "ymm19",  
    "ymm20",  "ymm21",  "ymm22", "ymm23",
    "ymm24",  "ymm25",  "ymm26", "ymm27",  
    "ymm28",  "ymm29",  "ymm30", "ymm31",
    // Floating point vector registers 128-bit
    "xmm0",   "xmm1",   "xmm2",  "xmm3",   
    "xmm4",   "xmm5",   "xmm6",  "xmm7",
    "xmm8",   "xmm9",   "xmm10", "xmm11",  
    "xmm12",  "xmm13",  "xmm14", "xmm15",
    "xmm16",  "xmm17",  "xmm18", "xmm19",  
    "xmm20",  "xmm21",  "xmm22", "xmm23",
    "xmm24",  "xmm25",  "xmm26", "xmm27",  
    "xmm28",  "xmm29",  "xmm30", "xmm31",
    // Special registers
    "rflags", "eflags", "flags", "rip",   
    "eip",    "ip",     "mxcsr",
    // Segment registers
    "es",     "ss",     "cs",    "ds",     
    "fs",     "gs",
    // Table registers
    "gdtr",   "ldtr",   "idtr",  "tr",
    // Test registers
    "tr0",    "tr1",    "tr2",   "tr3",
    "tr4",    "tr5",    "tr6",   "tr7",
    // Control registers
    "cr0",    "cr1",    "cr2",   "cr3",    
    "cr4",    "cr5",    "cr6",   "cr7",
    "cr8",    "cr9",    "cr10",  "cr11",   
    "cr12",   "cr13",   "cr14",  "cr15",
    // Debug registers
    "dr0",    "dr1",    "dr2",   "dr3",    
    "dr4",    "dr5",    "dr6",   "dr7",
    "dr8",    "dr9",    "dr10",  "dr11",   
    "dr12",   "dr13",   "dr14",  "dr15",
    // Mask registers
    "k0",     "k1",     "k2",    "k3",     
    "k4",     "k5",     "k6",   "k7",
    // Bounds registers
    "bnd0",   "bnd1",   "bnd2",  "bnd3",
    "bndcfg", "bndstatus"
};

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

ZydisRegister ZydisRegisterGetById(ZydisRegisterClass registerClass, uint8_t id)
{
    switch (registerClass)
    {
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE8:
        if (id <= 19)
        {
            return ZYDIS_REGISTER_AL + id;
        }
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE16:
        if (id <= 15)
        {
            return ZYDIS_REGISTER_AX + id;
        }    
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE32:
        if (id <= 15)
        {
            return ZYDIS_REGISTER_EAX + id;
        }      
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE64:
        if (id <= 15)
        {
            return ZYDIS_REGISTER_RAX + id;
        }     
    case ZYDIS_REGISTERCLASS_FLOATING_POINT:
        if (id <= 7)
        {
            return ZYDIS_REGISTER_ST0 + id;
        }    
    case ZYDIS_REGISTERCLASS_MULTIMEDIA:
        if (id <= 7)
        {
            return ZYDIS_REGISTER_MM0 + id;
        }     
    case ZYDIS_REGISTERCLASS_VECTOR128:
        if (id <= 31)
        {
            return ZYDIS_REGISTER_XMM0 + id;
        }    
    case ZYDIS_REGISTERCLASS_VECTOR256:
        if (id <= 31)
        {
            return ZYDIS_REGISTER_YMM0 + id;
        }
    case ZYDIS_REGISTERCLASS_VECTOR512:
        if (id <= 31)
        {
            return ZYDIS_REGISTER_ZMM0 + id;
        }    
    case ZYDIS_REGISTERCLASS_SEGMENT:
        if (id <= 5)
        {
            return ZYDIS_REGISTER_ES + id;
        }   
    case ZYDIS_REGISTERCLASS_TEST:
        if (id <= 7)
        {
            return ZYDIS_REGISTER_TR0 + id;
        } 
    case ZYDIS_REGISTERCLASS_CONTROL:
        if (id <= 15)
        {
            return ZYDIS_REGISTER_CR0 + id;
        }   
    case ZYDIS_REGISTERCLASS_DEBUG:
        if (id <= 15)
        {
            return ZYDIS_REGISTER_DR0 + id;
        }       
    case ZYDIS_REGISTERCLASS_MASK:
        if (id <= 7)
        {
            return ZYDIS_REGISTER_K0 + id;
        }    
    case ZYDIS_REGISTERCLASS_BOUNDS:
        if (id <= 3)
        {
            return ZYDIS_REGISTER_BND0 + id;
        }      
    default:
        // The registers of the missing register-classes can not be encoded by the register-id.
        break;
    }
    return ZYDIS_REGISTER_NONE;
}

const char* ZydisRegisterGetString(ZydisRegister reg)
{
    if ((reg == 0) || (reg > (sizeof(registerStrings) / sizeof(registerStrings[0])) - 1))
    {
        return NULL;
    }
    return registerStrings[reg];    
}

ZydisRegisterClass ZydisRegisterGetClass(ZydisRegister reg)
{
    if ((reg >= ZYDIS_REGISTER_RAX) && (reg <= ZYDIS_REGISTER_R15))
    {
        return ZYDIS_REGISTERCLASS_GENERAL_PURPOSE64;
    } 
    if ((reg >= ZYDIS_REGISTER_EAX) && (reg <= ZYDIS_REGISTER_R15D))
    {
        return ZYDIS_REGISTERCLASS_GENERAL_PURPOSE32;
    } 
    if ((reg >= ZYDIS_REGISTER_AX) && (reg <= ZYDIS_REGISTER_R15W))
    {
        return ZYDIS_REGISTERCLASS_GENERAL_PURPOSE16;
    }
    if ((reg >= ZYDIS_REGISTER_AL) && (reg <= ZYDIS_REGISTER_R15B))
    {
        return ZYDIS_REGISTERCLASS_GENERAL_PURPOSE8;
    }
    if ((reg >= ZYDIS_REGISTER_ST0) && (reg <= ZYDIS_REGISTER_ST7))
    {
        return ZYDIS_REGISTERCLASS_FLOATING_POINT;
    }
    if ((reg >= ZYDIS_REGISTER_ZMM0) && (reg <= ZYDIS_REGISTER_ZMM31))
    {
        return ZYDIS_REGISTERCLASS_VECTOR512;
    }
    if ((reg >= ZYDIS_REGISTER_YMM0) && (reg <= ZYDIS_REGISTER_YMM31))
    {
        return ZYDIS_REGISTERCLASS_VECTOR256;
    }
    if ((reg >= ZYDIS_REGISTER_XMM0) && (reg <= ZYDIS_REGISTER_XMM31))
    {
        return ZYDIS_REGISTERCLASS_VECTOR128;
    }
    if ((reg >= ZYDIS_REGISTER_RFLAGS) && (reg <= ZYDIS_REGISTER_FLAGS))
    {
        return ZYDIS_REGISTERCLASS_FLAGS;
    }
    if ((reg >= ZYDIS_REGISTER_RIP) && (reg <= ZYDIS_REGISTER_IP))
    {
        return ZYDIS_REGISTERCLASS_IP;
    }
    if ((reg >= ZYDIS_REGISTER_ES) && (reg <= ZYDIS_REGISTER_GS))
    {
        return ZYDIS_REGISTERCLASS_SEGMENT;
    }
    if ((reg >= ZYDIS_REGISTER_GDTR) && (reg <= ZYDIS_REGISTER_TR))
    {
        return ZYDIS_REGISTERCLASS_TABLE;
    }
    if ((reg >= ZYDIS_REGISTER_TR0) && (reg <= ZYDIS_REGISTER_TR7))
    {
        return ZYDIS_REGISTERCLASS_TEST;
    }
    if ((reg >= ZYDIS_REGISTER_CR0) && (reg <= ZYDIS_REGISTER_CR15))
    {
        return ZYDIS_REGISTERCLASS_CONTROL;
    }
    if ((reg >= ZYDIS_REGISTER_DR0) && (reg <= ZYDIS_REGISTER_DR15))
    {
        return ZYDIS_REGISTERCLASS_DEBUG;
    }
    if ((reg >= ZYDIS_REGISTER_K0) && (reg <= ZYDIS_REGISTER_K7))
    {
        return ZYDIS_REGISTERCLASS_MASK;
    }
    if ((reg >= ZYDIS_REGISTER_BND0) && (reg <= ZYDIS_REGISTER_BNDSTATUS))
    {
        return ZYDIS_REGISTERCLASS_BOUNDS;
    }
    return ZYDIS_REGISTERCLASS_NONE;
}

ZydisRegisterSize ZydisRegisterGetSize(ZydisRegister reg)
{
    ZydisRegisterClass registerClass = ZydisRegisterGetClass(reg);
    switch (registerClass)
    {
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE8:
        return ZYDIS_REGISTERSIZE_8;
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE16:
        return ZYDIS_REGISTERSIZE_16;
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE32:
        return ZYDIS_REGISTERSIZE_32;
    case ZYDIS_REGISTERCLASS_GENERAL_PURPOSE64:
        return ZYDIS_REGISTERSIZE_64;
    case ZYDIS_REGISTERCLASS_FLOATING_POINT:
        return ZYDIS_REGISTERSIZE_80;
    case ZYDIS_REGISTERCLASS_MULTIMEDIA:
        return ZYDIS_REGISTERSIZE_64;
    case ZYDIS_REGISTERCLASS_VECTOR128:
        return ZYDIS_REGISTERSIZE_128;
    case ZYDIS_REGISTERCLASS_VECTOR256:
        return ZYDIS_REGISTERSIZE_256;
    case ZYDIS_REGISTERCLASS_VECTOR512:
        return ZYDIS_REGISTERSIZE_512;
    case ZYDIS_REGISTERCLASS_FLAGS:
        return ZYDIS_REGISTERSIZE_DYNAMIC;
    case ZYDIS_REGISTERCLASS_IP:
        return ZYDIS_REGISTERSIZE_DYNAMIC;
    case ZYDIS_REGISTERCLASS_SEGMENT:
        return ZYDIS_REGISTERSIZE_16;
    case ZYDIS_REGISTERCLASS_TABLE:
        return ZYDIS_REGISTERSIZE_DYNAMIC;
    case ZYDIS_REGISTERCLASS_TEST:
        return ZYDIS_REGISTERSIZE_32;
    case ZYDIS_REGISTERCLASS_CONTROL:
        return ZYDIS_REGISTERSIZE_DYNAMIC;
    case ZYDIS_REGISTERCLASS_DEBUG:
        return ZYDIS_REGISTERSIZE_DYNAMIC;
    case ZYDIS_REGISTERCLASS_MASK:
        return ZYDIS_REGISTERSIZE_64;
    case ZYDIS_REGISTERCLASS_BOUNDS:
        return ZYDIS_REGISTERSIZE_128;
    default:
        break;
    }
    return ZYDIS_REGISTERSIZE_INVALID;
}

/* ============================================================================================== */
