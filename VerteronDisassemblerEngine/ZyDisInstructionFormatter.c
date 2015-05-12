/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : athre0z

  Last change     : 19. March 2014

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

#include "ZyDisInstructionFormatter.h"
#include "ZyDisDisassemblerUtils.h"
#include "ZyDisInternalHelpers.h"
#include "ZyDisOpcodeTableInternal.h"

#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* Interface =================================================================================== */

/* ZyDisBaseSymbolResolver ------------------------------------------------------------------------ */

typedef void (*ZyDisBaseSymbolResolver_DestructionCallback)(
    ZyDisBaseSymbolResolverContext *ctx);
typedef const char* (*ZyDisBaseSymbolResolver_ResolveSymbolCallback)(
    ZyDisBaseSymbolResolverContext *ctx, 
    const ZyDisInstructionInfo *info, 
    uint64_t address, 
    uint64_t *offset);

typedef struct _ZyDisBaseSymbolResolver
{
    ZyDisBaseSymbolResolver_DestructionCallback    destruct; // may be NULL
    ZyDisBaseSymbolResolver_ResolveSymbolCallback  resolveCallback;
} ZyDisBaseSymbolResolver;

/**
 * @brief   Constructor.
 * @param   ctx The context.
 */
static void ZyDisBaseSymbolResolver_Construct(ZyDisBaseSymbolResolverContext *ctx);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisBaseSymbolResolver_Destruct(ZyDisBaseSymbolResolverContext *ctx);

/* ZyDisBaseInstructionFormatter ------------------------------------------------------------------ */

typedef void(*ZyDisBaseInstructionFormatter_DestructionCallback)(
    ZyDisBaseInstructionFormatterContext *ctx);

typedef struct _ZyDisBaseInstructionFormatter
{
    ZyDisBaseInstructionFormatter_DestructionCallback destruct; // may be NULL
    ZyDisBaseInstructionFormatter_InternalFormatInstructionCallback internalFormat;
    ZyDisBaseSymbolResolverContext *symbolResolver;
    char *outputBuffer;
    size_t outputBufferCapacity;
    size_t outputStringLen;
    bool outputUppercase;
} ZyDisBaseInstructionFormatter;

/**
 * @brief   Constructor.
 * @param   ctx             The context.
 * @param   symbolResolver  The symbol resolver to use when formatting addresses.
 */
static void ZyDisBaseInstructionFormatter_Construct(ZyDisBaseInstructionFormatterContext *ctx, 
    ZyDisBaseSymbolResolverContext *symbolResolver);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisBaseInstructionFormatter_Destruct(ZyDisBaseInstructionFormatterContext *ctx);

/*static void ZyDisBaseInstructionFormatter_OutputSetUppercase(
    ZyDisBaseInstructionFormatterContext *ctx, bool uppercase);*/

/**
 * @brief   Returns the string representation of a given register.
 * @param   ctx The context.
 * @param   reg The register.
 * @return  The string representation of the given register.
 */
static char const* ZyDisBaseInstructionFormatter_RegisterToString(
    const ZyDisBaseInstructionFormatterContext *ctx, ZyDisRegister reg);

/**
 * @brief   Resolves a symbol.
 * @param   ctx     The context.
 * @param   info    The instruction info.
 * @param   address The address.
 * @param   offset  Reference to an unsigned 64 bit integer that receives an offset relative 
 *                  to the base address of the symbol.
 * @return  The name of the symbol, if the symbol was found, @c NULL if not.
 */
static char const* ZyDisBaseInstructionFormatter_ResolveSymbol(
    const ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info, uint64_t address, 
    uint64_t *offset);

/**
 * @brief   Clears the output string buffer.
 * @param   ctx The context.
 */
static void ZyDisBaseInstructionFormatter_OutputClear(ZyDisBaseInstructionFormatterContext *ctx);

/**
 * @brief   Returns the content of the output string buffer.
 * @param   ctx The context.
 * @return  Pointer to the content of the ouput string buffer.
 */
static char const* ZyDisBaseInstructionFormatter_OutputString(ZyDisBaseInstructionFormatterContext *ctx);

/**
 * @brief   Appends text to the ouput string buffer.
 * @param   ctx     The context.
 * @param   text    The text.
 */
static void ZyDisBaseInstructionFormatter_OutputAppend(ZyDisBaseInstructionFormatterContext *ctx, 
    char const *text);

/**
 * @brief   Appends formatted text to the output string buffer.
 * @param   ctx     The context.
 * @param   format  The format string.
 */
static void ZyDisBaseInstructionFormatter_OutputAppendFormatted(
    ZyDisBaseInstructionFormatterContext *ctx, char const *format, ...);

/**
 * @brief   Appends a formatted address to the output string buffer.
 * @param   ctx             The context.
 * @param   info            The instruction info.
 * @param   address         The address.
 * @param   resolveSymbols  If this parameter is true, the function will try to display a
 *                          smybol name instead of the numeric value.
 */
static void ZyDisBaseInstructionFormatter_OutputAppendAddress(ZyDisBaseInstructionFormatterContext *ctx, 
    const ZyDisInstructionInfo *info, uint64_t address, bool resolveSymbols);

/**
 * @brief   Appends a formatted immediate value to the output string buffer.
 * @param   ctx             The context.
 * @param   info            The instruction info.
 * @param   operand         The immediate operand.
 * @param   resolveSymbols  If this parameter is true, the function will try to display a
 *                          smybol name instead of the numeric value.
 */
static void ZyDisBaseInstructionFormatter_OutputAppendImmediate(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info, 
    const ZyDisOperandInfo *operand, bool resolveSymbols);

/**
 * @brief   Appends a formatted memory displacement value to the output string buffer.
 * @param   ctx     The context.
 * @param   operand The memory operand.
 */
static void ZyDisBaseInstructionFormatter_OutputAppendDisplacement(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisOperandInfo *operand);

/* ZyDisCustomSymbolResolver ---------------------------------------------------------------------- */

typedef struct _ZyDisCustomSymbolResolver
{
    ZyDisBaseSymbolResolver super;
    ZyDisCustomSymbolResolver_ResolveSymbolCallback resolve;
    void *userData;
} ZyDisCustomSymbolResolver;

/**
 * @brief   Constructor.
 * @param   ctx         The context.
 * @param   resolverCb  The resolver callback.
 * @param   userData    User defined data passed to the resolver callback.
 */
static void ZyDisCustomSymbolResolver_Construct(ZyDisBaseSymbolResolverContext *ctx, 
    ZyDisCustomSymbolResolver_ResolveSymbolCallback resolverCb, void *userData);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisCustomSymbolResolver_Destruct(ZyDisBaseSymbolResolverContext *ctx);

/**
 * @copydoc ZyDisBaseSymbolResolver_Resolve
 */
static const char* ZyDisCustomSymbolResolver_Resolve(ZyDisBaseSymbolResolverContext *ctx, 
    const ZyDisInstructionInfo *info, uint64_t address, uint64_t *offset);

/* ZyDisIntelInstructionFormatter ----------------------------------------------------------------- */

typedef struct _ZyDisIntelInstructionFormatter
{
    ZyDisBaseInstructionFormatter super;
} ZyDisIntelInstructionFormatter;

/**
 * @brief   Constructor.
 * @param   ctx             The context.
 * @param   symbolResolver  The symbol resolver used to resolve addresses.
 * @param   userData        User defined data passed to the resolver callback.
 */
static void ZyDisIntelInstructionFormatter_Construct(ZyDisBaseInstructionFormatterContext *ctx, 
    ZyDisBaseSymbolResolverContext *symbolResolver);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisIntelInstructionFormatter_Destruct(ZyDisBaseInstructionFormatterContext *ctx);

/**
 * @brief   Appends an operand cast to the output string buffer.
 * @param   ctx     The context.
 * @param   operand The operand.
 */
static void ZyDisIntelInstructionFormatter_OutputAppendOperandCast(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisOperandInfo *operand);

/**
 * @brief   Formats the specified operand and appends it to the output buffer.
 * @param   ctx     The context.
 * @param   info    The instruction info.
 * @param   operand The operand.
 */
static void ZyDisIntelInstructionFormatter_FormatOperand(ZyDisBaseInstructionFormatterContext *ctx, 
    const ZyDisInstructionInfo *info, const ZyDisOperandInfo *operand);

/**
 * @coypdoc ZyDisBaseInstructionFormatter_InternalFormatInstruction
 */
static void ZyDisIntelInstructionFormatter_InternalFormatInstruction(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info);

/* ZyDisCustomInstructionFormatter ---------------------------------------------------------------- */

typedef struct _ZyDisCustomInstructionFormatter
{
    ZyDisBaseInstructionFormatter super;
} ZyDisCustomInstructionFormatter;

/**
 * @brief   Contructor.
 * @param   ctx             The context.
 * @param   formatInsnCb    The callback formatting the instruction.
 */
static void ZyDisCustomInstructionFormatter_Construct(ZyDisBaseInstructionFormatterContext *ctx,
    ZyDisBaseInstructionFormatter_InternalFormatInstructionCallback formatInsnCb);

/**
 * @brief   Destructor.
 * @param   ctx The context.
 */
static void ZyDisCustomInstructionFormatter_Destruct(ZyDisBaseInstructionFormatterContext *ctx);

/* Implementation ============================================================================== */

/* ZyDisBaseSymbolResolver ------------------------------------------------------------------------ */

void ZyDisBaseSymbolResolver_Construct(ZyDisBaseSymbolResolverContext *ctx)
{
    memset(ZyDisBaseSymbolResolver_thiz(ctx), 0, sizeof(ZyDisBaseSymbolResolver));
}

void ZyDisBaseSymbolResolver_Destruct(ZyDisBaseSymbolResolverContext *ctx)
{
    ZYDIS_UNUSED(ctx);
}

void ZyDisBaseSymbolResolver_Release(ZyDisBaseSymbolResolverContext *ctx)
{
    ZyDisBaseSymbolResolver *thiz = ZyDisBaseSymbolResolver_thiz(ctx);
    
    if (thiz->destruct)
    {
        thiz->destruct(ctx);
    }

    free(thiz);
    free(ctx);
}

const char* ZyDisBaseSymbolResolver_ResolveSymbol(ZyDisBaseSymbolResolverContext *ctx, 
    const ZyDisInstructionInfo *info, uint64_t address, uint64_t *offset)
{
    assert(ZyDisBaseSymbolResolver_thiz(ctx)->resolveCallback);
    return ZyDisBaseSymbolResolver_thiz(ctx)->resolveCallback(ctx, info, address, offset);
}

/* ZyDisCustomSymbolResolver ---------------------------------------------------------------------- */

static void ZyDisCustomSymbolResolver_Construct(ZyDisBaseSymbolResolverContext *ctx,
    ZyDisCustomSymbolResolver_ResolveSymbolCallback resolverCb, void *userData)
{
    ZyDisBaseSymbolResolver_Construct(ctx);
    ZyDisCustomSymbolResolver *thiz = ZyDisCustomSymbolResolver_thiz(ctx);

    thiz->super.destruct        = &ZyDisCustomSymbolResolver_Destruct;
    thiz->super.resolveCallback = &ZyDisCustomSymbolResolver_Resolve;

    thiz->resolve  = resolverCb;
    thiz->userData = userData;
}

static void ZyDisCustomSymbolResolver_Destruct(ZyDisBaseSymbolResolverContext *ctx)
{
    ZyDisBaseSymbolResolver_Destruct(ctx);
}

ZyDisBaseSymbolResolverContext* ZyDisCustomSymbolResolver_Create(
    ZyDisCustomSymbolResolver_ResolveSymbolCallback resolverCb, void *userData)
{
    ZyDisCustomSymbolResolver      *thiz = malloc(sizeof(ZyDisCustomSymbolResolver));
    ZyDisBaseSymbolResolverContext *ctx  = malloc(sizeof(ZyDisBaseSymbolResolverContext));

    if (!thiz || !ctx)
    {
        if (thiz)
        {
            free(thiz);
        }
        if (ctx)
        {
            free(ctx);
        }

        return NULL;
    }

    ctx->d.type = TYPE_CUSTOMSYMBOLRESOLVER;
    ctx->d.ptr  = thiz;
    
    ZyDisCustomSymbolResolver_Construct(ctx, resolverCb, userData);

    return ctx;
}

static const char* ZyDisCustomSymbolResolver_Resolve(ZyDisBaseSymbolResolverContext *ctx, 
    const ZyDisInstructionInfo *info, uint64_t address, uint64_t *offset)
{
    ZyDisCustomSymbolResolver *thiz = ZyDisCustomSymbolResolver_thiz(ctx);
    return thiz->resolve(info, address, offset, thiz->userData);
}

/* ZyDisBaseInstructionFormatter ------------------------------------------------------------------ */

static const char* ZyDisBaseInstructionFormatter_registerStrings[] =
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

static void ZyDisBaseInstructionFormatter_Construct(ZyDisBaseInstructionFormatterContext *ctx, 
    ZyDisBaseSymbolResolverContext *symbolResolver)
{
    ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_thiz(ctx);

    thiz->destruct              = &ZyDisBaseInstructionFormatter_Destruct;
    thiz->internalFormat        = NULL;
    thiz->symbolResolver        = symbolResolver;
    thiz->outputStringLen       = 0;
    thiz->outputUppercase       = false;
    thiz->outputBufferCapacity  = 256;
    thiz->outputBuffer          = malloc(thiz->outputBufferCapacity);
}

static void ZyDisBaseInstructionFormatter_Destruct(ZyDisBaseInstructionFormatterContext *ctx)
{
    ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_thiz(ctx);

    if (thiz->outputBuffer)
    {
        free(thiz->outputBuffer);
        thiz->outputBuffer = NULL;
    }
}

void ZyDisBaseInstructionFormatter_Release(ZyDisBaseInstructionFormatterContext *ctx)
{
    ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_thiz(ctx);
    
    if (thiz->destruct)
    {
        thiz->destruct(ctx);
    }

    free(thiz);
    free(ctx);
}

/*
static void ZyDisBaseInstructionFormatter_OutputSetUppercase(ZyDisBaseInstructionFormatterContext *ctx,
    bool uppercase)
{
    ZyDisBaseInstructionFormatter_thiz(ctx)->outputUppercase = uppercase;
}
*/

static char const* ZyDisBaseInstructionFormatter_RegisterToString(
    const ZyDisBaseInstructionFormatterContext *ctx, ZyDisRegister reg) 
{
    ZYDIS_UNUSED(ctx);

    if (reg == REG_NONE)
    {
        return "error";   
    }
    return ZyDisBaseInstructionFormatter_registerStrings[reg - 1]; 
}

static char const* ZyDisBaseInstructionFormatter_ResolveSymbol(
    const ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info, 
    uint64_t address, uint64_t *offset)
{
    const ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_cthiz(ctx);

    if (thiz->symbolResolver)
    {
        return ZyDisBaseSymbolResolver_ResolveSymbol(
            thiz->symbolResolver, info, address, offset);
    }

    return NULL;
}

ZyDisBaseSymbolResolverContext* ZyDisBaseInstructionFormatter_GetSymbolResolver(
    const ZyDisBaseInstructionFormatterContext *ctx)
{
    return ZyDisBaseInstructionFormatter_cthiz(ctx)->symbolResolver;
}

void ZyDisBaseInstructionFormatter_SetSymbolResolver(
    ZyDisBaseInstructionFormatterContext *ctx, ZyDisBaseSymbolResolverContext *symbolResolver)
{
    ZyDisBaseInstructionFormatter_thiz(ctx)->symbolResolver = symbolResolver;
}

const char* ZyDisBaseInstructionFormatter_FormatInstruction(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info)
{
    ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_thiz(ctx);

    // Clears the internal string buffer
    ZyDisBaseInstructionFormatter_OutputClear(ctx);

    // Calls the virtual format method that actually formats the instruction
    thiz->internalFormat(ctx, info);

    if (thiz->outputBufferCapacity == 0)
    {
        // The basic instruction formatter only returns the instruction menmonic.
        return ZyDisGetInstructionMnemonicString(info->mnemonic);
    }

    // Return the formatted instruction string
    return ZyDisBaseInstructionFormatter_OutputString(ctx);
}

static void ZyDisBaseInstructionFormatter_OutputClear(ZyDisBaseInstructionFormatterContext *ctx)
{
    ZyDisBaseInstructionFormatter_thiz(ctx)->outputStringLen = 0;
}

static char const* ZyDisBaseInstructionFormatter_OutputString(ZyDisBaseInstructionFormatterContext *ctx)
{
    return &ZyDisBaseInstructionFormatter_thiz(ctx)->outputBuffer[0];
}

static void ZyDisBaseInstructionFormatter_OutputAppend(
    ZyDisBaseInstructionFormatterContext *ctx, char const *text)
{
    ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_thiz(ctx);

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
            thiz->outputBuffer[i] = (char)toupper(thiz->outputBuffer[i]);
        }
    }
}

static void ZyDisBaseInstructionFormatter_OutputAppendFormatted(
    ZyDisBaseInstructionFormatterContext *ctx, char const *format, ...)
{
    ZyDisBaseInstructionFormatter *thiz = ZyDisBaseInstructionFormatter_thiz(ctx);

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
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, format, arguments);
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
            thiz->outputBuffer[i] = (char)toupper(thiz->outputBuffer[i]);
        }
    }

    va_end(arguments);
}

static void ZyDisBaseInstructionFormatter_OutputAppendAddress(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info, uint64_t address, 
    bool resolveSymbols)
{
    uint64_t offset = 0;
    const char* name = NULL;

    if (resolveSymbols)
    {
        name = ZyDisBaseInstructionFormatter_ResolveSymbol(ctx, info, address, &offset);
    }

    if (name)
    {
        if (offset)
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s+%.2llX", name, offset);   
        } 
        else
        {
            ZyDisBaseInstructionFormatter_OutputAppend(ctx, name);     
        }
    } 
    else
    {
        if (info->flags & IF_DISASSEMBLER_MODE_16)
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.4X", address);
        } 
        else if (info->flags & IF_DISASSEMBLER_MODE_32)
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.8lX", address);
        } 
        else if (info->flags & IF_DISASSEMBLER_MODE_64)
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.16llX", address);
        } 
        else
        {
            assert(0);
        }
    }
}

static void ZyDisBaseInstructionFormatter_OutputAppendImmediate(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info, 
    const ZyDisOperandInfo *operand, bool resolveSymbols)
{
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
        name = ZyDisBaseInstructionFormatter_ResolveSymbol(ctx, info, value, &offset);
    }

    if (name)
    {
        if (offset)
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s+%.2llX", name, offset);   
        } 
        else
        {
            ZyDisBaseInstructionFormatter_OutputAppend(ctx, name);     
        }
    } 
    else
    {
        ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.2llX", value);
    }
}

static void ZyDisBaseInstructionFormatter_OutputAppendDisplacement(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisOperandInfo *operand)
{
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
        ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.2llX", value);
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
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "-%.2lX", -value);
        } else
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s%.2lX", 
                (operand->base != REG_NONE || operand->index != REG_NONE) ? "+" : "", value);
        }
    }
}

/* ZyDisIntelInstructionFormatter ----------------------------------------------------------------- */

static void ZyDisIntelInstructionFormatter_Construct(ZyDisBaseInstructionFormatterContext *ctx, 
    ZyDisBaseSymbolResolverContext* symbolResolver)
{
    ZyDisBaseInstructionFormatter_Construct(ctx, symbolResolver);
    ZyDisIntelInstructionFormatter *thiz = ZyDisIntelInstructionFormatter_thiz(ctx);

    thiz->super.destruct       = &ZyDisIntelInstructionFormatter_Destruct;
    thiz->super.internalFormat = &ZyDisIntelInstructionFormatter_InternalFormatInstruction;
}

static void ZyDisIntelInstructionFormatter_Destruct(ZyDisBaseInstructionFormatterContext *ctx)
{
    ZyDisBaseInstructionFormatter_Destruct(ctx);
}

ZyDisBaseInstructionFormatterContext* ZyDisIntelInstructionFormatter_Create(void)
{
    return ZyDisIntelInstructionFormatter_CreateEx(NULL);
}

ZyDisBaseInstructionFormatterContext* ZyDisIntelInstructionFormatter_CreateEx(
    ZyDisBaseSymbolResolverContext *resolver)
{
    ZyDisIntelInstructionFormatter *thiz = malloc(sizeof(ZyDisIntelInstructionFormatter));
    ZyDisBaseInstructionFormatterContext *ctx = malloc(sizeof(ZyDisBaseInstructionFormatterContext));

    if (!thiz || !ctx)
    {
        if (thiz)
        {
            free(thiz);
        }
        if (ctx)
        {
            free(ctx);
        }

        return NULL;
    }

    ctx->d.type = TYPE_INTELINSTRUCTIONFORMATTER;
    ctx->d.ptr  = thiz;

    ZyDisIntelInstructionFormatter_Construct(ctx, resolver);

    return ctx;
}

static void ZyDisIntelInstructionFormatter_OutputAppendOperandCast(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisOperandInfo *operand)
{
    switch(operand->size) 
    {
    case 8:     
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "byte ptr " ); 
        break;
    case 16:    
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "word ptr " ); 
        break;
    case 32:    
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "dword ptr "); 
        break;
    case 64:    
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "qword ptr "); 
        break;
    case 80:    
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "tword ptr "); 
        break;
    case 128:   
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "oword ptr "); 
        break;
    case 256:   
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "yword ptr "); 
        break;
    default: 
        break;
    }
}

static void ZyDisIntelInstructionFormatter_FormatOperand(ZyDisBaseInstructionFormatterContext *ctx, 
    const ZyDisInstructionInfo *info, const ZyDisOperandInfo *operand)
{
    switch (operand->type)
    {
    case OPTYPE_REGISTER: 
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, 
            ZyDisBaseInstructionFormatter_RegisterToString(ctx, operand->base));
        break;
    case OPTYPE_MEMORY: 
        if (info->flags & IF_PREFIX_SEGMENT)
        {
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx,
                "%s:", ZyDisBaseInstructionFormatter_RegisterToString(ctx, info->segment));    
        }
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "[");
        if (operand->base == REG_RIP)
        {
            // TODO: Add option
            ZyDisBaseInstructionFormatter_OutputAppendAddress(
                ctx, info, ZyDisCalcAbsoluteTarget(info, operand), true);   
        } 
        else
        {
            if (operand->base != REG_NONE)
            {
                ZyDisBaseInstructionFormatter_OutputAppend(ctx, 
                    ZyDisBaseInstructionFormatter_RegisterToString(ctx, operand->base)); 
            }

            if (operand->index != REG_NONE) 
            {
                ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%s%s", 
                    operand->base != REG_NONE ? "+" : "", 
                    ZyDisBaseInstructionFormatter_RegisterToString(ctx, operand->index));
                if (operand->scale) 
                {
                    ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "*%d", operand->scale);
                }
            }

            if (operand->offset) 
            {
                ZyDisBaseInstructionFormatter_OutputAppendDisplacement(ctx, operand);
            }
        }
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "]");
        break;
    case OPTYPE_POINTER:
        // TODO: resolve symbols
        switch (operand->size)
        {
        case 32:
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "word %.4X:%.4X", 
                operand->lval.ptr.seg, operand->lval.ptr.off & 0xFFFF);
            break;
        case 48:
            ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "dword %.4X:%.8lX", 
                operand->lval.ptr.seg, operand->lval.ptr.off);
            break;
        default:
            assert(0);
        }
        break;
    case OPTYPE_IMMEDIATE: 
        {
            ZyDisBaseInstructionFormatter_OutputAppendImmediate(ctx, info, operand, true);
        }
        break;
    case OPTYPE_REL_IMMEDIATE: 
        {
            if (operand->size == 8)
            {
                ZyDisBaseInstructionFormatter_OutputAppend(ctx, "short ");
            }
            ZyDisBaseInstructionFormatter_OutputAppendAddress(ctx, info, 
                ZyDisCalcAbsoluteTarget(info, operand), true);
        }
        break;
    case OPTYPE_CONSTANT: 
        ZyDisBaseInstructionFormatter_OutputAppendFormatted(ctx, "%.2X", operand->lval.udword);
        break;
    default: 
        assert(0);
        break;
    }
}

static void ZyDisIntelInstructionFormatter_InternalFormatInstruction(
    ZyDisBaseInstructionFormatterContext *ctx, const ZyDisInstructionInfo *info)
{
    // Append string prefixes
    if (info->flags & IF_PREFIX_LOCK)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "lock ");
    }

    if (info->flags & IF_PREFIX_REP)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "rep ");
    } 
    else if (info->flags & IF_PREFIX_REPNE)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, "repne ");
    }

    // Append the instruction mnemonic
    ZyDisBaseInstructionFormatter_OutputAppend(ctx, ZyDisGetInstructionMnemonicString(info->mnemonic));

    // Append the first operand
    if (info->operand[0].type != OPTYPE_NONE)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, " ");
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
            ZyDisIntelInstructionFormatter_OutputAppendOperandCast(ctx, &info->operand[0]);
        }
        ZyDisIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[0]);
    }

    // Append the second operand
    if (info->operand[1].type != OPTYPE_NONE)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, ", ");
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
            ZyDisIntelInstructionFormatter_OutputAppendOperandCast(ctx, &info->operand[1]);
        }
        ZyDisIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[1]);
    }

    // Append the third operand
    if (info->operand[2].type != OPTYPE_NONE)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, ", ");
        bool cast = false;
        if (info->operand[2].type == OPTYPE_MEMORY && 
            (info->operand[2].size != info->operand[1].size)) 
        {
            cast = true;
        }

        if (cast)
        {
            ZyDisIntelInstructionFormatter_OutputAppendOperandCast(ctx, &info->operand[2]);
        }

        ZyDisIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[2]);
    }

    // Append the fourth operand
    if (info->operand[3].type != OPTYPE_NONE)
    {
        ZyDisBaseInstructionFormatter_OutputAppend(ctx, ", ");
        ZyDisIntelInstructionFormatter_FormatOperand(ctx, info, &info->operand[3]);
    }
}

/* ZyDisCustomInstructionFormatter ---------------------------------------------------------------- */

static void ZyDisCustomInstructionFormatter_Construct(ZyDisBaseInstructionFormatterContext *ctx,
    ZyDisBaseInstructionFormatter_InternalFormatInstructionCallback formatInsnCb)
{
    ZyDisBaseInstructionFormatter_Construct(ctx, NULL);

    ZyDisCustomInstructionFormatter *thiz = ZyDisCustomInstructionFormatter_thiz(ctx);
    thiz->super.internalFormat = formatInsnCb;
}

static void ZyDisCustomInstructionFormatter_Destruct(ZyDisBaseInstructionFormatterContext *ctx)
{
    ZyDisBaseInstructionFormatter_Destruct(ctx);
}

ZYDIS_EXPORT ZyDisBaseInstructionFormatterContext* ZyDisCustomInstructionFormatter_Create(
    ZyDisBaseInstructionFormatter_InternalFormatInstructionCallback formatInsnCb)
{
    ZyDisCustomInstructionFormatter *thiz = malloc(sizeof(ZyDisCustomInstructionFormatter));
    ZyDisBaseInstructionFormatterContext *ctx = malloc(sizeof(ZyDisBaseInstructionFormatterContext));

    if (!thiz || !ctx)
    {
        if (thiz)
        {
            free(thiz);
        }
        if (ctx)
        {
            free(ctx);
        }

        return NULL;
    }

    ctx->d.type = TYPE_CUSTOMINSTRUCTIONFORMATTER;
    ctx->d.ptr  = thiz;

    ZyDisCustomInstructionFormatter_Construct(ctx, formatInsnCb);
    return ctx;
}

/* --------------------------------------------------------------------------------------------- */

/* ============================================================================================= */
