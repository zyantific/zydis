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
        buffer->last->next = token;
    }
    buffer->last = token;

    token->type  = type;
    token->next  = ZYAN_NULL;
    token->value = (const char*)buffer->data;

    buffer->string.vector.data = buffer->data;
    buffer->string.vector.size = 1;
    buffer->string.vector.capacity = buffer->size;
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

/* ============================================================================================== */
