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

#include <Zydis/Internal/String.h>
#include <Zydis/FormatterBuffer.h>

/* ============================================================================================== */
/* Exported functions                                                                             */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Token                                                                                          */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterTokenGetValue(const ZydisFormatterToken* token,
    ZydisTokenType* type, char** value)
{
    if (!token || !type || !value)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    *type = token->type;
    *value = (char*)((ZyanU8*)token + sizeof(ZydisFormatterToken));

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterTokenNext(ZydisFormatterTokenConst** token)
{
    if (!token || !*token)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    const ZyanU16 next = (*token)->next;
    if (!next)
    {
        return ZYAN_STATUS_OUT_OF_RANGE;
    }
    *token = (ZydisFormatterToken*)((ZyanU8*)*token + next);

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */
/* Buffer                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

ZyanStatus ZydisFormatterBufferGetString(ZydisFormatterBuffer* buffer, ZyanString** string)
{
    if (!buffer || !string)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (buffer->tokenized && !buffer->last)
    {
        return ZYAN_STATUS_INVALID_OPERATION;
    }

    ZYAN_ASSERT(buffer->string.vector.data);
    ZYAN_ASSERT(buffer->string.vector.size);

    *string = &buffer->string;

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBufferAppend(ZydisFormatterBuffer* buffer, ZydisTokenType type)
{
    if (!buffer)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (!buffer->tokenized || ((buffer->last) && (buffer->last->type == type)))
    {
        return ZYAN_STATUS_SUCCESS;
    }

    if (buffer->last)
    {
        const ZyanUSize len = buffer->string.vector.size;
        ZYAN_ASSERT(len);

        buffer->data += len;
        buffer->size -= len;
    }

    if (buffer->size <= sizeof(ZydisFormatterToken))
    {
        return ZYAN_STATUS_INSUFFICIENT_BUFFER_SIZE;
    }

    ZydisFormatterToken* const token = (ZydisFormatterToken*)buffer->data;
    buffer->data += sizeof(ZydisFormatterToken);
    buffer->size -= sizeof(ZydisFormatterToken);

    if (buffer->last)
    {
        const ZyanUSize offset = (ZyanU8*)token - (ZyanU8*)buffer->last;
        ZYAN_ASSERT(offset < 65536);
        buffer->last->next = (ZyanU16)(offset);
    }
    buffer->last = token;

    token->type  = type;
    token->next  = 0;

    buffer->string.vector.data = buffer->data;
    buffer->string.vector.size = 1;
    buffer->string.vector.capacity = ZYAN_MIN(buffer->size, 65536);
    *buffer->data = (ZyanU8)'\0';

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBufferRemember(const ZydisFormatterBuffer* buffer, ZyanUPointer* state)
{
    if (!buffer || !state)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (buffer->tokenized)
    {
        *state = (ZyanUPointer)buffer->last;
    } else
    {
        *state = (ZyanUPointer)buffer->string.vector.size;
    }

    return ZYAN_STATUS_SUCCESS;
}

ZyanStatus ZydisFormatterBufferRestore(ZydisFormatterBuffer* buffer, ZyanUPointer state)
{
    if (!buffer)
    {
        return ZYAN_STATUS_INVALID_ARGUMENT;
    }

    if (buffer->tokenized)
    {
        const ZyanUSize delta = state - (ZyanUPointer)buffer->last;
        buffer->last = (ZydisFormatterToken*)state;
        buffer->data -= delta;
        buffer->size += delta;
        buffer->string.vector.data = buffer->data;
        buffer->string.vector.size = 1;
        buffer->string.vector.capacity = buffer->size;
        *buffer->data = (ZyanU8)'\0';
    } else
    {
        buffer->string.vector.size = (ZyanUSize)state;
        ZYDIS_STRING_NULLTERMINATE(&buffer->string);
    }

    return ZYAN_STATUS_SUCCESS;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
