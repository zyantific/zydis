/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 14. March 2014

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

**************************************************************************************************/

#include "VXInstructionFormatterC.h"
#include "VXDisassemblerUtilsC.h"
#include "VXInternalHelpersC.h"
#include "VXOpcodeTableInternalC.h"

#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* Interface =================================================================================== */

/* VXBaseSymbolResolver ------------------------------------------------------------------------ */

typedef void (*VXBaseSymbolResolver_DestructionCallback)(
    VXBaseSymbolResolverContext *ctx);
typedef const char* (*VXBaseSymbolResolver_ResolveSymbolCallback)(
    VXBaseSymbolResolverContext *ctx, 
    const VXInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset);

typedef struct _VXBaseSymbolResolver
{
    VXBaseSymbolResolver_DestructionCallback    destruct; // may be NULL
    VXBaseSymbolResolver_ResolveSymbolCallback  resolveCallback;
} VXBaseSymbolResolver;

void VXBaseSymbolResolver_Construct(VXBaseSymbolResolverContext *ctx);
void VXBaseSymbolResolver_Destruct(VXBaseSymbolResolverContext *ctx);
void VXBaseSymbolResolver_Release(VXBaseSymbolResolverContext *ctx);
const char* VXBaseSymbolResolver_ResolveSymbol(VXBaseSymbolResolverContext *ctx, const VXInstructionInfo *info, uint64_t address, uint64_t *offset);

/* VXBaseInstructionFormatter ------------------------------------------------------------------ */

typedef void(*VXBaseInstructionFormatter_DestructionCallback)(
    VXBaseInstructionFormatterContext *ctx);
typedef void(*VXBaseInstructionFormatter_InternalFormatInstructionCallback)(
    VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info);

typedef struct _VXBaseInstructionFormatter
{
    VXBaseInstructionFormatter_DestructionCallback destruct; // may be NULL
    VXBaseInstructionFormatter_InternalFormatInstructionCallback internalFormat;
    VXBaseSymbolResolverContext *symbolResolver;
    char *outputBuffer;
    size_t outputBufferCapacity;
    size_t outputStringLen;
    bool outputUppercase;
} VXBaseInstructionFormatter;

void VXBaseInstructionFormatter_Construct(VXBaseInstructionFormatterContext *ctx, VXBaseSymbolResolverContext *symbolResolver);
void VXBaseInstructionFormatter_Destruct(VXBaseInstructionFormatterContext *ctx);
void VXBaseInstructionFormatter_Release(VXBaseInstructionFormatterContext *ctx);
void VXBaseInstructionFormatter_OutputSetUppercase(VXBaseInstructionFormatterContext *ctx, bool uppercase);
char const* VXBaseInstructionFormatter_RegisterToString(const VXBaseInstructionFormatterContext *ctx, VXRegister reg);
char const* VXBaseInstructionFormatter_ResolveSymbol(const VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, uint64_t address, uint64_t *offset);
VXBaseSymbolResolverContext* VXBaseInstructionFormatter_GetSymbolResolver(const VXBaseInstructionFormatterContext *ctx);
void VXBaseInstructionFormatter_SetSymbolResolver(VXBaseInstructionFormatterContext *ctx, VXBaseSymbolResolverContext *symbolResolver);
const char* VXBaseInstructionFormatter_FormatInstruction(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info);
void VXBaseInstructionFormatter_OutputClear(VXBaseInstructionFormatterContext *ctx);
char const* VXBaseInstructionFormatter_OutputString(VXBaseInstructionFormatterContext *ctx);
void VXBaseInstructionFormatter_OutputAppend(VXBaseInstructionFormatterContext *ctx, char const *text);
void VXBaseInstructionFormatter_OutputAppendFormatted(VXBaseInstructionFormatterContext *ctx, char const *format, ...);
void VXBaseInstructionFormatter_OutputAppendAddress(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info,  uint64_t address, bool resolveSymbols);
void VXBaseInstructionFormatter_OutputAppendImmediate(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, const VXOperandInfo *operand, bool resolveSymbols);
void VXBaseInstructionFormatter_OutputAppendDisplacement(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, const VXOperandInfo *operand);

/* VXCustomSymbolResolver ---------------------------------------------------------------------- */

typedef struct _VXCustomSymbolResolver
{
    VXBaseSymbolResolver super;
    VXCustomSymbolResolver_ResolveSymbolCallback resolve;
    void *userData;
} VXCustomSymbolResolver;

void VXCustomSymbolResolver_Construct(VXBaseSymbolResolverContext *ctx, VXCustomSymbolResolver_ResolveSymbolCallback resolverCb, void *userData);
void VXCustomSymbolResolver_Destruct(VXBaseSymbolResolverContext *ctx);
VXBaseSymbolResolverContext* VXCustomSymbolResolver_Create(VXCustomSymbolResolver_ResolveSymbolCallback resolverCb, void *userData);
const char* VXCustomSymbolResolver_Resolve(VXBaseSymbolResolverContext *ctx, const VXInstructionInfo *info, uint64_t address, uint64_t *offset);

/* VXIntelInstructionFormatter ----------------------------------------------------------------- */

typedef struct _VXIntelInstructionFormatter
{
    VXBaseInstructionFormatter super;
} VXIntelInstructionFormatter;

void VXIntelInstructionFormatter_Construct(VXBaseInstructionFormatterContext *ctx, VXBaseSymbolResolverContext *symbolResolver);
void VXIntelInstructionFormatter_Destruct(VXBaseInstructionFormatterContext *ctx);
void VXIntelInstructionFormatter_OutputAppendOperandCast(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, const VXOperandInfo *operand);
void VXIntelInstructionFormatter_FormatOperand(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, const VXOperandInfo *operand);
void VXIntelInstructionFormatter_InternalFormatInstruction(VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info);

/* Implementation ============================================================================== */

/* VXBaseSymbolResolver ------------------------------------------------------------------------ */

void VXBaseSymbolResolver_Construct(VXBaseSymbolResolverContext *ctx)
{
    memset(VXBaseSymbolResolver_thiz(ctx), 0, sizeof(VXBaseSymbolResolver));
}

void VXBaseSymbolResolver_Destruct(VXBaseSymbolResolverContext *ctx)
{
    
}

void VXBaseSymbolResolver_Release(
    VXBaseSymbolResolverContext *ctx)
{
    VXBaseSymbolResolver *thiz = VXBaseSymbolResolver_thiz(ctx);
    
    if (thiz->destruct)
    {
        thiz->destruct(ctx);
    }

    free(thiz);
    free(ctx);
}

const char* VXBaseSymbolResolver_ResolveSymbol(
    VXBaseSymbolResolverContext *ctx,
    const VXInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset)
{
    assert(VXBaseSymbolResolver_thiz(ctx)->resolveCallback);
    return VXBaseSymbolResolver_thiz(ctx)->resolveCallback(ctx, info, address, offset);
}

/* VXCustomSymbolResolver ---------------------------------------------------------------------- */

static void VXCustomSymbolResolver_Construct(
    VXBaseSymbolResolverContext *ctx,
    VXCustomSymbolResolver_ResolveSymbolCallback resolverCb,
    void *userData)
{
    VXBaseSymbolResolver_Construct(ctx);
    VXCustomSymbolResolver *thiz = VXCustomSymbolResolver_thiz(ctx);

    thiz->super.destruct        = &VXCustomSymbolResolver_Destruct;
    thiz->super.resolveCallback = &VXCustomSymbolResolver_Resolve;

    thiz->resolve  = resolverCb;
    thiz->userData = userData;
}

static void VXCustomSymbolResolver_Destruct(VXBaseSymbolResolverContext *ctx)
{
    VXBaseSymbolResolver_Destruct(ctx);
}

VXBaseSymbolResolverContext* VXCustomSymbolResolver_Create(
    VXCustomSymbolResolver_ResolveSymbolCallback resolverCb,
    void *userData)
{
    VXCustomSymbolResolver      *thiz = malloc(sizeof(VXCustomSymbolResolver));
    VXBaseSymbolResolverContext *ctx  = malloc(sizeof(VXBaseSymbolResolverContext));

    ctx->d.type = TYPE_CUSTOMSYMBOLRESOLVER;
    ctx->d.ptr  = thiz;

    return ctx;
}

static const char* VXCustomSymbolResolver_Resolve(
    VXBaseSymbolResolverContext *ctx, 
    const VXInstructionInfo *info, 
    uint64_t address,
    uint64_t *offset)
{
    VXCustomSymbolResolver *thiz = VXCustomSymbolResolver_thiz(ctx);
    return thiz->resolve(info, address, offset, thiz->userData);
}

/* VXBaseInstructionFormatter ------------------------------------------------------------------ */

static const char* VXBaseInstructionFormatter_registerStrings[] =
{
    /* 8 bit general purpose registers */
    "al",       "cl",       "dl",       "bl",
    "ah",       "ch",       "dh",       "bh",
    "spl",      "bpl",      "sil",      "dil",
    "r8b",      "r9b",      "r10b",     "r11b",
    "r12b",     "r13b",     "r14b",     "r15b",
    /* 16 bit general purpose registers */
    "ax",       "cx",       "dx",       "bx",
    "sp",       "bp",       "si",       "di",
    "r8w",      "r9w",      "r10w",     "r11w",
    "r12w",     "r13w",     "r14w",     "r15w",
    /* 32 bit general purpose registers */
    "eax",      "ecx",      "edx",      "ebx",
    "esp",      "ebp",      "esi",      "edi",
    "r8d",      "r9d",      "r10d",     "r11d",
    "r12d",     "r13d",     "r14d",     "r15d",
    /* 64 bit general purpose registers */
    "rax",      "rcx",      "rdx",      "rbx",
    "rsp",      "rbp",      "rsi",      "rdi",
    "r8",       "r9",       "r10",      "r11",
    "r12",      "r13",      "r14",      "r15",
    /* segment registers */
    "es",       "cs",       "ss",       
    "ds",       "fs",       "gs",
    /* control registers */
    "cr0",      "cr1",      "cr2",      "cr3",
    "cr4",      "cr5",      "cr6",      "cr7",
    "cr8",      "cr9",      "cr10",     "cr11",
    "cr12",     "cr13",     "cr14",     "cr15",
    /* debug registers */
    "dr0",      "dr1",      "dr2",      "dr3",
    "dr4",      "dr5",      "dr6",      "dr7",
    "dr8",      "dr9",      "dr10",     "dr11",
    "dr12",     "dr13",     "dr14",     "dr15",
    /* mmx registers */
    "mm0",      "mm1",      "mm2",      "mm3",
    "mm4",      "mm5",      "mm6",      "mm7",
    /* x87 registers */
    "st0",      "st1",      "st2",      "st3",
    "st4",      "st5",      "st6",      "st7",
    /* extended multimedia registers */
    "xmm0",     "xmm1",     "xmm2",     "xmm3",
    "xmm4",     "xmm5",     "xmm6",     "xmm7",
    "xmm8",     "xmm9",     "xmm10",    "xmm11",
    "xmm12",    "xmm13",    "xmm14",    "xmm15",
    /* 256 bit multimedia registers */
    "ymm0",     "ymm1",     "ymm2",     "ymm3",
    "ymm4",     "ymm5",     "ymm6",     "ymm7",
    "ymm8",     "ymm9",     "ymm10",    "ymm11",
    "ymm12",    "ymm13",    "ymm14",    "ymm15",
    /* instruction pointer register */
    "rip"
};

static void VXBaseInstructionFormatter_Construct(
    VXBaseInstructionFormatterContext *ctx, VXBaseSymbolResolverContext *symbolResolver)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    thiz->destruct              = &VXBaseInstructionFormatter_Destruct;
    thiz->internalFormat        = NULL;
    thiz->symbolResolver        = symbolResolver;
    thiz->outputStringLen       = 0;
    thiz->outputUppercase       = false;
    thiz->outputBufferCapacity  = 256;
    thiz->outputBuffer          = malloc(thiz->outputBufferCapacity);
}

static void VXBaseInstructionFormatter_Destruct(VXBaseInstructionFormatterContext *ctx)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    if (thiz->outputBuffer)
    {
        free(thiz->outputBuffer);
        thiz->outputBuffer = NULL;
    }
}

void VXBaseInstructionFormatter_Release(
    VXBaseInstructionFormatterContext *ctx)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);
    
    if (thiz->destruct)
    {
        thiz->destruct(ctx);
    }

    free(thiz);
    free(ctx);
}

static void VXBaseInstructionFormatter_OutputSetUppercase(VXBaseInstructionFormatterContext *ctx,
    bool uppercase)
{
    VXBaseInstructionFormatter_thiz(ctx)->outputUppercase = uppercase;
}

static char const* VXBaseInstructionFormatter_RegisterToString(
    const VXBaseInstructionFormatterContext *ctx, VXRegister reg) 
{
    if (reg == REG_NONE)
    {
        return "error";   
    }
    return VXBaseInstructionFormatter_registerStrings[reg - 1]; 
}

static char const* VXBaseInstructionFormatter_ResolveSymbol(
    const VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, 
    uint64_t address, uint64_t *offset)
{
    const VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_cthiz(ctx);

    if (thiz->symbolResolver)
    {
        return VXBaseSymbolResolver_ResolveSymbol(
            thiz->symbolResolver, info, address, offset);
    }

    return NULL;
}

VXBaseSymbolResolverContext* VXBaseInstructionFormatter_GetSymbolResolver(
    const VXBaseInstructionFormatterContext *ctx)
{
    return VXBaseInstructionFormatter_cthiz(ctx)->symbolResolver;
}

void VXBaseInstructionFormatter_SetSymbolResolver(
    VXBaseInstructionFormatterContext *ctx, VXBaseSymbolResolverContext *symbolResolver)
{
    VXBaseInstructionFormatter_thiz(ctx)->symbolResolver = symbolResolver;
}

const char* VXBaseInstructionFormatter_FormatInstruction(
    VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    // Clears the internal string buffer
    VXBaseInstructionFormatter_OutputClear(ctx);

    // Calls the virtual format method that actually formats the instruction
    thiz->internalFormat(ctx, info);

    if (thiz->outputBufferCapacity == 0)
    {
        // The basic instruction formatter only returns the instruction menmonic.
        return VXGetInstructionMnemonicString(info->mnemonic);
    }

    // Return the formatted instruction string
    return VXBaseInstructionFormatter_OutputString(ctx);
}

static void VXBaseInstructionFormatter_OutputClear(VXBaseInstructionFormatterContext *ctx)
{
    VXBaseInstructionFormatter_thiz(ctx)->outputStringLen = 0;
}

static char const* VXBaseInstructionFormatter_OutputString(VXBaseInstructionFormatterContext *ctx)
{
    return &VXBaseInstructionFormatter_thiz(ctx)->outputBuffer[0];
}

static void VXBaseInstructionFormatter_OutputAppend(
    VXBaseInstructionFormatterContext *ctx, char const *text)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    // Get the string length including the null-terminator char
    size_t strLen = strlen(text) + 1;

    // Get the buffer size
    size_t bufLen = thiz->outputBufferCapacity;

    // Decrease the offset by one, to exclude already existing null-terminator chars in the
    // output buffer
    size_t offset = (thiz->outputStringLen) ? thiz->outputStringLen - 1 : 0;

    // Resize capacity of the output buffer on demand and add some extra space to improve the
    // performance
    if (bufLen <= (thiz->outputStringLen + strLen))
    {
        thiz->outputBufferCapacity = bufLen + strLen + 512;
        thiz->outputBuffer = realloc(thiz->outputBuffer, thiz->outputBufferCapacity);
    }

    // Write the text to the output buffer
    memcpy(&thiz->outputBuffer[offset], text, strLen);

    // Increase the string length
    thiz->outputStringLen = offset + strLen;

    // Convert to uppercase
    if (thiz->outputUppercase)
    {
        for (size_t i = offset; i < thiz->outputStringLen - 1; ++i)
        {
            thiz->outputBuffer[i] = toupper(thiz->outputBuffer[i]);
        }
    }
}

static void VXBaseInstructionFormatter_OutputAppendFormatted(
    VXBaseInstructionFormatterContext *ctx, char const *format, ...)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    va_list arguments;
    va_start(arguments, format);

    // Get the buffer size
    size_t bufLen = thiz->outputBufferCapacity;

    // Decrease the offset by one, to exclude already existing null-terminator chars in the
    // output buffer
    size_t offset = (thiz->outputStringLen) ? thiz->outputStringLen - 1 : 0;

    // Resize the output buffer on demand and add some extra space to improve the performance
    if ((bufLen - thiz->outputStringLen) < 256)
    {
        bufLen = bufLen + 512;
        thiz->outputBuffer = realloc(thiz->outputBuffer, bufLen);
        thiz->outputBufferCapacity = bufLen;
    }

    int strLen = 0;
    do
    {
        // If the formatted text did not fit in the output buffer, resize it, and try again
        if (strLen < 0)
        {
            thiz->outputBufferCapacity = bufLen + 512;
            thiz->outputBuffer = realloc(thiz->outputBuffer, thiz->outputBufferCapacity);
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, format, arguments);
            return;
        }
        // Write the formatted text to the output buffer
        assert((bufLen - offset) > 0);
        strLen = vsnprintf(&thiz->outputBuffer[offset], bufLen - offset, format, arguments);
    } while (strLen < 0);

    // Increase the string length
    thiz->outputStringLen = offset + strLen + 1;

    // Convert to uppercase
    if (thiz->outputUppercase)
    {
        for (size_t i = offset; i < thiz->outputStringLen - 1; ++i)
        {
            thiz->outputBuffer[i] = toupper(thiz->outputBuffer[i]);
        }
    }

    va_end(arguments);
}

static void VXBaseInstructionFormatter_OutputAppendAddress(
    VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, 
    uint64_t address, bool resolveSymbols)
{
    uint64_t offset = 0;
    const char* name = NULL;

    if (resolveSymbols)
    {
        name = VXBaseInstructionFormatter_ResolveSymbol(ctx, info, address, &offset);
    }

    if (name)
    {
        if (offset)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s+%.2llX", name, offset);   
        } 
        else
        {
            VXBaseInstructionFormatter_OutputAppend(ctx, name);     
        }
    } 
    else
    {
        if (info->flags & IF_DISASSEMBLER_MODE_16)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.4X", address);
        } 
        else if (info->flags & IF_DISASSEMBLER_MODE_32)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.8lX", address);
        } 
        else if (info->flags & IF_DISASSEMBLER_MODE_64)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.16llX", address);
        } 
        else
        {
            assert(0);
        }
    }
}

static void VXBaseInstructionFormatter_OutputAppendImmediate(
    VXBaseInstructionFormatterContext *ctx,
    const VXInstructionInfo *info, 
    const VXOperandInfo *operand, 
    bool resolveSymbols)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    assert(operand->type == OPTYPE_IMMEDIATE);
    uint64_t value = 0;
    if (operand->signed_lval && (operand->size != info->operand_mode)) 
    {
        if (operand->size == 8) 
        {
            value = (int64_t)operand->lval.sbyte;
        } 
        else 
        {
            assert(operand->size == 32);
            value = (int64_t)operand->lval.sdword;
        }

        if (info->operand_mode < 64) 
        {
            value = value & ((1ull << info->operand_mode) - 1ull);
        }
    } 
    else 
    {
        switch (operand->size) 
        {
        case 8: 
            value = operand->lval.ubyte; 
            break;
        case 16: 
            value = operand->lval.uword; 
            break;
        case 32: 
            value = operand->lval.udword; 
            break;
        case 64: 
            value = operand->lval.uqword; 
            break;
        default:
            assert(0);
        }
    }

    uint64_t offset = 0;
    const char* name = NULL;
    if (resolveSymbols)
    {
        name = VXBaseInstructionFormatter_ResolveSymbol(ctx, info, value, &offset);
    }

    if (name)
    {
        if (offset)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s+%.2llX", name, offset);   
        } 
        else
        {
            VXBaseInstructionFormatter_OutputAppend(ctx, name);     
        }
    } 
    else
    {
        VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.2llX", value);
    }
}

static void VXBaseInstructionFormatter_OutputAppendDisplacement(
    VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info, 
    const VXOperandInfo *operand)
{
    VXBaseInstructionFormatter *thiz = VXBaseInstructionFormatter_thiz(ctx);

    assert(operand->offset > 0);
    if ((operand->base == REG_NONE) && (operand->index == REG_NONE))
    {
        // Assume the displacement value is unsigned
        assert(operand->scale == 0);
        assert(operand->offset != 8);
        uint64_t value = 0;
        switch (operand->offset)
        {
        case 16:
            value = operand->lval.uword;
            break;
        case 32:
            value = operand->lval.udword;
            break;
        case 64:
            value = operand->lval.uqword;
            break;
        default:
            assert(0);
        }
        VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.2llX", value);
    } 
    else
    {
        // The displacement value might be negative
        assert(operand->offset != 64);  
        int64_t value = 0;
        switch (operand->offset)
        {
        case 8:
            value = operand->lval.sbyte;
            break;
        case 16:
            value = operand->lval.sword;
            break;
        case 32:
            value = operand->lval.sdword;
            break;
        default:
            assert(0);
        }
        if (value < 0)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "-%.2lX", -value);
        } else
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s%.2lX", 
                (operand->base != REG_NONE || operand->index != REG_NONE) ? "+" : "", value);
        }
    }
}

/* VXIntelInstructionFormatter ----------------------------------------------------------------- */

static void VXIntelInstructionFormatter_Construct(VXBaseInstructionFormatterContext *ctx, 
    VXBaseSymbolResolverContext* symbolResolver)
{
    VXBaseInstructionFormatter_Construct(ctx, symbolResolver);
    VXIntelInstructionFormatter *thiz = VXIntelInstructionFormatter_thiz(ctx);

    thiz->super.destruct       = &VXIntelInstructionFormatter_Destruct;
    thiz->super.internalFormat = &VXIntelInstructionFormatter_InternalFormatInstruction;
}

static void VXIntelInstructionFormatter_Destruct(VXBaseInstructionFormatterContext *ctx)
{
    VXBaseInstructionFormatter_Destruct(ctx);
}

VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_Create(void)
{
    return VXIntelInstructionFormatter_CreateEx(NULL);
}

VXBaseInstructionFormatterContext* VXIntelInstructionFormatter_CreateEx(
    VXBaseSymbolResolverContext *resolver)
{
    VXIntelInstructionFormatter *thiz = malloc(sizeof(VXIntelInstructionFormatter));
    VXBaseInstructionFormatterContext *ctx = malloc(sizeof(VXBaseInstructionFormatterContext));

    ctx->d.type = TYPE_INTELINSTRUCTIONFORMATTER;
    ctx->d.ptr  = thiz;

    VXIntelInstructionFormatter_Construct(ctx, resolver);

    return ctx;
}

static void VXIntelInstructionFormatter_OutputAppendOperandCast(
    VXBaseInstructionFormatterContext *ctx, 
    const VXInstructionInfo *info, 
    const VXOperandInfo *operand)
{
    switch(operand->size) 
    {
    case 8:     
        VXBaseInstructionFormatter_OutputAppend(ctx, "byte ptr " ); 
        break;
    case 16:    
        VXBaseInstructionFormatter_OutputAppend(ctx, "word ptr " ); 
        break;
    case 32:    
        VXBaseInstructionFormatter_OutputAppend(ctx, "dword ptr "); 
        break;
    case 64:    
        VXBaseInstructionFormatter_OutputAppend(ctx, "qword ptr "); 
        break;
    case 80:    
        VXBaseInstructionFormatter_OutputAppend(ctx, "tword ptr "); 
        break;
    case 128:   
        VXBaseInstructionFormatter_OutputAppend(ctx, "oword ptr "); 
        break;
    case 256:   
        VXBaseInstructionFormatter_OutputAppend(ctx, "yword ptr "); 
        break;
    default: 
        break;
    }
}

static void VXIntelInstructionFormatter_FormatOperand(
    VXBaseInstructionFormatterContext *ctx, 
    const VXInstructionInfo *info, 
    const VXOperandInfo *operand)
{
    switch (operand->type)
    {
    case OPTYPE_REGISTER: 
        VXBaseInstructionFormatter_OutputAppend(ctx, 
            VXBaseInstructionFormatter_RegisterToString(ctx, operand->base));
        break;
    case OPTYPE_MEMORY: 
        if (info->flags & IF_PREFIX_SEGMENT)
        {
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx,
                "%s:", VXBaseInstructionFormatter_RegisterToString(ctx, info->segment));    
        }
        VXBaseInstructionFormatter_OutputAppend(ctx, "[");
        if (operand->base == REG_RIP)
        {
            // TODO: Add option
            VXBaseInstructionFormatter_OutputAppendAddress(
                ctx, info, VXCalcAbsoluteTarget(info, operand), true);   
        } 
        else
        {
            if (operand->base != REG_NONE)
            {
                VXBaseInstructionFormatter_OutputAppend(ctx, 
                    VXBaseInstructionFormatter_RegisterToString(ctx, operand->base)); 
            }

            if (operand->index != REG_NONE) 
            {
                VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s%s", 
                    operand->base != REG_NONE ? "+" : "", 
                    VXBaseInstructionFormatter_RegisterToString(ctx, operand->index));
                if (operand->scale) 
                {
                    VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "*%d", operand->scale);
                }
            }

            if (operand->offset) 
            {
                VXBaseInstructionFormatter_OutputAppendDisplacement(ctx, info, operand);
            }
        }
        VXBaseInstructionFormatter_OutputAppend(ctx, "]");
        break;
    case OPTYPE_POINTER:
        // TODO: resolve symbols
        switch (operand->size)
        {
        case 32:
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "word %.4X:%.4X", 
                operand->lval.ptr.seg, operand->lval.ptr.off & 0xFFFF);
            break;
        case 48:
            VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "dword %.4X:%.8lX", 
                operand->lval.ptr.seg, operand->lval.ptr.off);
            break;
        default:
            assert(0);
        }
        break;
    case OPTYPE_IMMEDIATE: 
        {
            VXBaseInstructionFormatter_OutputAppendImmediate(ctx, info, operand, true);
        }
        break;
    case OPTYPE_REL_IMMEDIATE: 
        {
            if (operand->size == 8)
            {
                VXBaseInstructionFormatter_OutputAppend(ctx, "short ");
            }
            VXBaseInstructionFormatter_OutputAppendAddress(ctx, info, 
                VXCalcAbsoluteTarget(info, operand), true);
        }
        break;
    case OPTYPE_CONSTANT: 
        VXBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.2X", operand->lval.udword);
        break;
    default: 
        assert(0);
        break;
    }
}

static void VXIntelInstructionFormatter_InternalFormatInstruction(
    VXBaseInstructionFormatterContext *ctx, const VXInstructionInfo *info)
{
    // Append string prefixes
    if (info->flags & IF_PREFIX_LOCK)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, "lock ");
    }

    if (info->flags & IF_PREFIX_REP)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, "rep ");
    } 
    else if (info->flags & IF_PREFIX_REPNE)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, "repne ");
    }

    // Append the instruction mnemonic
    VXBaseInstructionFormatter_OutputAppend(ctx, VXGetInstructionMnemonicString(info->mnemonic));

    // Append the first operand
    if (info->operand[0].type != OPTYPE_NONE)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, " ");
        bool cast = false;
        if (info->operand[0].type == OPTYPE_MEMORY) 
        {
            if (info->operand[1].type == OPTYPE_IMMEDIATE ||
                info->operand[1].type == OPTYPE_CONSTANT ||
                info->operand[1].type == OPTYPE_NONE ||
                (info->operand[0].size != info->operand[1].size)) 
            {
                cast = true;
            } 
            else if (info->operand[1].type == OPTYPE_REGISTER && info->operand[1].base == REG_CL) 
            {
                switch (info->mnemonic) 
                {
                case MNEM_RCL:
                case MNEM_ROL:
                case MNEM_ROR:
                case MNEM_RCR:
                case MNEM_SHL:
                case MNEM_SHR:
                case MNEM_SAR:
                    cast = true;
                    break;
                default: 
                    break;
                }
            }
        }

        if (cast)
        {
            VXIntelInstructionFormatter_OutputAppendOperandCast(ctx, info, &info->operand[0]);
        }
        VXIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[0]);
    }

    // Append the second operand
    if (info->operand[1].type != OPTYPE_NONE)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, ", ");
        bool cast = false;
        if (info->operand[1].type == OPTYPE_MEMORY &&
            info->operand[0].size != info->operand[1].size &&
            ((info->operand[0].type != OPTYPE_REGISTER) ||
             ((info->operand[0].base != REG_ES) && 
             (info->operand[0].base != REG_CS) &&
             (info->operand[0].base != REG_SS) &&
             (info->operand[0].base != REG_DS) &&
             (info->operand[0].base != REG_FS) &&
             (info->operand[0].base != REG_GS)))) 
        {
            cast = true;
        }

        if (cast)
        {
            VXIntelInstructionFormatter_OutputAppendOperandCast(ctx, info, &info->operand[1]);
        }
        VXIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[1]);
    }

    // Append the third operand
    if (info->operand[2].type != OPTYPE_NONE)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, ", ");
        bool cast = false;
        if (info->operand[2].type == OPTYPE_MEMORY && 
            (info->operand[2].size != info->operand[1].size)) 
        {
            cast = true;
        }

        if (cast)
        {
            VXIntelInstructionFormatter_OutputAppendOperandCast(ctx, info, &info->operand[2]);
        }

        VXIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[2]);
    }

    // Append the fourth operand
    if (info->operand[3].type != OPTYPE_NONE)
    {
        VXBaseInstructionFormatter_OutputAppend(ctx, ", ");
        VXIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[3]);
    }
}

/* --------------------------------------------------------------------------------------------- */

/* ============================================================================================= */
