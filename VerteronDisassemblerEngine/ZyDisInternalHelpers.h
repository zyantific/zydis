/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : athre0z
  Modifications   : 

  Last change     : 19. March 2015

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

#ifndef _VDE_ZyDisINTERNALHELPERS_H_
#define _VDE_ZyDisINTERNALHELPERS_H_

#include "ZyDisInstructionDecoder.h"
#include "ZyDisInstructionFormatter.h"
#include "ZyDisInternalConfig.h"

#include <assert.h>

/* Types IDs =================================================================================== */

typedef enum _ZyDisTypeId
{
    TYPE_BASEDATASOURCE,
    TYPE_MEMORYDATASOURCE,
    TYPE_CUSTOMDATASOURCE,
    TYPE_INSTRUCTIONDECODER,
    TYPE_BASESYMBOLRESOLVER,
    TYPE_CUSTOMSYMBOLRESOLVER,
    TYPE_BASEINSTRUCTIONFORMATTER,
    TYPE_INTELINSTRUCTIONFORMATTER,
    TYPE_CUSTOMINSTRUCTIONFORMATTER,
} ZyDisTypeId;

/* Context conversion helpers ================================================================== */

ZYDIS_INLINE struct _ZyDisBaseDataSource* ZyDisBaseDataSource_thiz(
    ZyDisBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEDATASOURCE 
        || ctx->d.type == TYPE_MEMORYDATASOURCE
        || ctx->d.type == TYPE_CUSTOMDATASOURCE);
    return (struct _ZyDisBaseDataSource*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisBaseDataSource* ZyDisBaseDataSource_cthiz(
    const ZyDisBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEDATASOURCE 
        || ctx->d.type == TYPE_MEMORYDATASOURCE
        || ctx->d.type == TYPE_CUSTOMDATASOURCE);
    return (const struct _ZyDisBaseDataSource*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisMemoryDataSource* ZyDisMemoryDataSource_thiz(
    ZyDisBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_MEMORYDATASOURCE);
    return (struct _ZyDisMemoryDataSource*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisMemoryDataSource* ZyDisMemoryDataSource_cthiz(
    const ZyDisBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_MEMORYDATASOURCE);
    return (const struct _ZyDisMemoryDataSource*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisCustomDataSource* ZyDisCustomDataSource_thiz(
    ZyDisBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMDATASOURCE);
    return (struct _ZyDisCustomDataSource*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisCustomDataSource* ZyDisCustomDataSource_cthiz(
    const ZyDisBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMDATASOURCE);
    return (const struct _ZyDisCustomDataSource*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisInstructionDecoder* ZyDisInstructionDecoder_thiz(
    ZyDisInstructionDecoderContext *ctx)
{
    assert(ctx->d.type == TYPE_INSTRUCTIONDECODER);
    return (struct _ZyDisInstructionDecoder*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisInstructionDecoder* ZyDisInstructionDecoder_cthiz(
    const ZyDisInstructionDecoderContext *ctx)
{
    assert(ctx->d.type == TYPE_INSTRUCTIONDECODER);
    return (const struct _ZyDisInstructionDecoder*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisBaseSymbolResolver* ZyDisBaseSymbolResolver_thiz(
    ZyDisBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_BASESYMBOLRESOLVER
        || ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (struct _ZyDisBaseSymbolResolver*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisBaseSymbolResolver* ZyDisBaseSymbolResolver_cthiz(
    const ZyDisBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_BASESYMBOLRESOLVER
        || ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (const struct _ZyDisBaseSymbolResolver*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisCustomSymbolResolver* ZyDisCustomSymbolResolver_thiz(
    ZyDisBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (struct _ZyDisCustomSymbolResolver*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisCustomSymbolResolver* ZyDisCustomSymbolResolver_cthiz(
    const ZyDisBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (const struct _ZyDisCustomSymbolResolver*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisBaseInstructionFormatter* ZyDisBaseInstructionFormatter_thiz(
    ZyDisBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEINSTRUCTIONFORMATTER 
        || ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER
        || ctx->d.type == TYPE_CUSTOMINSTRUCTIONFORMATTER);
    return (struct _ZyDisBaseInstructionFormatter*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisBaseInstructionFormatter* ZyDisBaseInstructionFormatter_cthiz(
    const ZyDisBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEINSTRUCTIONFORMATTER
        || ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER
        || ctx->d.type == TYPE_CUSTOMINSTRUCTIONFORMATTER);
    return (const struct _ZyDisBaseInstructionFormatter*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisIntelInstructionFormatter* ZyDisIntelInstructionFormatter_thiz(
    ZyDisBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER);
    return (struct _ZyDisIntelInstructionFormatter*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisIntelInstructionFormatter* ZyDisIntelInstructionFormatter_cthiz(
    const ZyDisBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER);
    return (const struct _ZyDisIntelInstructionFormatter*)ctx->d.ptr;
}

ZYDIS_INLINE struct _ZyDisCustomInstructionFormatter* ZyDisCustomInstructionFormatter_thiz(
    ZyDisBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMINSTRUCTIONFORMATTER);
    return (struct _ZyDisCustomInstructionFormatter*)ctx->d.ptr;
}

ZYDIS_INLINE const struct _ZyDisCustomInstructionFormatter* ZyDisCustomInstructionFormatter_cthiz(
    const ZyDisBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMINSTRUCTIONFORMATTER);
    return (struct _ZyDisCustomInstructionFormatter*)ctx->d.ptr;
}

/* ============================================================================================= */

#endif /* _VDE_ZyDisINTERNALHELPERS_H_ */