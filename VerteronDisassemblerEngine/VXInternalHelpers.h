/**************************************************************************************************

  Verteron Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : athre0z
  Modifications   : 

  Last change     : 13. March 2015

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

#ifndef _VDE_VXINTERNALHELPERS_H_
#define _VDE_VXINTERNALHELPERS_H_

#include "VXInstructionDecoder.h"
#include "VXInstructionFormatter.h"
#include "VXInternalConfig.h"

#include <assert.h>

/* Types IDs =================================================================================== */

typedef enum _VXTypeId
{
    TYPE_BASEDATASOURCE,
    TYPE_MEMORYDATASOURCE,
    TYPE_INSTRUCTIONDECODER,
    TYPE_BASESYMBOLRESOLVER,
    TYPE_CUSTOMSYMBOLRESOLVER,
    TYPE_BASEINSTRUCTIONFORMATTER,
    TYPE_INTELINSTRUCTIONFORMATTER,
} VXTypeId;

/* Context conversion helpers ================================================================== */

VX_INLINE struct _VXBaseDataSource* VXBaseDataSource_thiz(
    VXBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEDATASOURCE 
        || ctx->d.type == TYPE_MEMORYDATASOURCE);
    return (struct _VXBaseDataSource*)ctx->d.ptr;
}

VX_INLINE const struct _VXBaseDataSource* VXBaseDataSource_cthiz(
    const VXBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEDATASOURCE 
        || ctx->d.type == TYPE_MEMORYDATASOURCE);
    return (const struct _VXBaseDataSource*)ctx->d.ptr;
}

VX_INLINE struct _VXMemoryDataSource* VXMemoryDataSource_thiz(
    VXBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_MEMORYDATASOURCE);
    return (struct _VXMemoryDataSource*)ctx->d.ptr;
}

VX_INLINE const struct _VXMemoryDataSource* VXMemoryDataSource_cthiz(
    const VXBaseDataSourceContext *ctx)
{
    assert(ctx->d.type == TYPE_MEMORYDATASOURCE);
    return (const struct _VXMemoryDataSource*)ctx->d.ptr;
}

VX_INLINE struct _VXInstructionDecoder* VXInstructionDecoder_thiz(
    VXInstructionDecoderContext *ctx)
{
    assert(ctx->d.type == TYPE_INSTRUCTIONDECODER);
    return (struct _VXInstructionDecoder*)ctx->d.ptr;
}

VX_INLINE const struct _VXInstructionDecoder* VXInstructionDecoder_cthiz(
    const VXInstructionDecoderContext *ctx)
{
    assert(ctx->d.type == TYPE_INSTRUCTIONDECODER);
    return (const struct _VXInstructionDecoder*)ctx->d.ptr;
}

VX_INLINE struct _VXBaseSymbolResolver* VXBaseSymbolResolver_thiz(
    VXBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_BASESYMBOLRESOLVER
        || ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (struct _VXBaseSymbolResolver*)ctx->d.ptr;
}

VX_INLINE const struct _VXBaseSymbolResolver* VXBaseSymbolResolver_cthiz(
    const VXBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_BASESYMBOLRESOLVER
        || ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (const struct _VXBaseSymbolResolver*)ctx->d.ptr;
}

VX_INLINE struct _VXCustomSymbolResolver* VXCustomSymbolResolver_thiz(
    VXBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (struct _VXCustomSymbolResolver*)ctx->d.ptr;
}

VX_INLINE const struct _VXCustomSymbolResolver* VXCustomSymbolResolver_cthiz(
    const VXBaseSymbolResolverContext *ctx)
{
    assert(ctx->d.type == TYPE_CUSTOMSYMBOLRESOLVER);
    return (const struct _VXCustomSymbolResolver*)ctx->d.ptr;
}

VX_INLINE struct _VXBaseInstructionFormatter* VXBaseInstructionFormatter_thiz(
    VXBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEINSTRUCTIONFORMATTER 
        || ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER);
    return (struct _VXBaseInstructionFormatter*)ctx->d.ptr;
}

VX_INLINE const struct _VXBaseInstructionFormatter* VXBaseInstructionFormatter_cthiz(
    const VXBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_BASEINSTRUCTIONFORMATTER
        || ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER);
    return (const struct _VXBaseInstructionFormatter*)ctx->d.ptr;
}

VX_INLINE struct _VXIntelInstructionFormatter* VXIntelInstructionFormatter_thiz(
    VXBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER);
    return (struct _VXIntelInstructionFormatter*)ctx->d.ptr;
}

VX_INLINE const struct _VXIntelInstructionFormatter* VXIntelInstructionFormatter_cthiz(
    const VXBaseInstructionFormatterContext *ctx)
{
    assert(ctx->d.type == TYPE_INTELINSTRUCTIONFORMATTER);
    return (const struct _VXIntelInstructionFormatter*)ctx->d.ptr;
}

/* ============================================================================================= */

#endif /* _VDE_VXINTERNALHELPERS_H_ */