/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : astunm

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

#include <Zycore/Format.h>
#include <Zycore/LibC.h>
#include <Zydis/Zydis.h>

static ZyanStatus SkipOperand(const ZydisFormatter* formatter,
    ZydisFormatterBuffer* buffer, ZydisFormatterContext* context)
{
    ZYAN_UNUSED(formatter);
    ZYAN_UNUSED(buffer);
    return context->operand->id == 1 ? ZYDIS_STATUS_SKIP_TOKEN : ZYAN_STATUS_SUCCESS;
}

int main(void)
{
    const ZyanU8 data[] = { 0x89, 0xD8 };
    ZydisDecoder decoder;
    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
    ZYAN_CHECK(ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64));
    ZYAN_CHECK(ZydisDecoderDecodeFull(&decoder, data, sizeof(data), &instruction, operands));

    ZyanBool passed = ZYAN_TRUE;
    for (ZydisFormatterStyle style = ZYDIS_FORMATTER_STYLE_ATT;
        style <= ZYDIS_FORMATTER_STYLE_INTEL; ++style)
    {
        const ZydisFormatterFunction hooks[] =
        {
            ZYDIS_FORMATTER_FUNC_PRE_OPERAND,
            ZYDIS_FORMATTER_FUNC_POST_OPERAND
        };
        for (ZyanUSize i = 0; i < ZYAN_ARRAY_LENGTH(hooks); ++i)
        {
            ZydisFormatter formatter;
            ZYAN_CHECK(ZydisFormatterInit(&formatter, style));
            const void* callback = (const void*)SkipOperand;
            ZYAN_CHECK(ZydisFormatterSetHook(&formatter, hooks[i], &callback));

            char formatted[128];
            ZYAN_CHECK(ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
                instruction.operand_count_visible, formatted, sizeof(formatted), 0, ZYAN_NULL));

            ZyanU8 buffer[256];
            const ZydisFormatterToken* token;
            ZYAN_CHECK(ZydisFormatterTokenizeInstruction(&formatter, &instruction, operands,
                instruction.operand_count_visible, buffer, sizeof(buffer), 0, &token, ZYAN_NULL));

            char tokenized[128];
            ZyanString string;
            ZYAN_CHECK(ZyanStringInitCustomBuffer(&string, tokenized, sizeof(tokenized)));
            do
            {
                ZydisTokenType type;
                const char* value;
                ZYAN_CHECK(ZydisFormatterTokenGetValue(token, &type, &value));
                ZYAN_CHECK(ZyanStringAppendFormat(&string, "%s", value));
            } while (ZYAN_SUCCESS(ZydisFormatterTokenNext(&token)));

            const char* expected = style == ZYDIS_FORMATTER_STYLE_ATT ? "mov %eax" : "mov eax";
            if (ZYAN_STRCMP(formatted, expected) || ZYAN_STRCMP(tokenized, expected))
            {
                ZYAN_PRINTF("Style %u, hook %u: expected '%s', formatted '%s', tokenized '%s'\n",
                    style, hooks[i], expected, formatted, tokenized);
                passed = ZYAN_FALSE;
            }
        }
    }
    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
