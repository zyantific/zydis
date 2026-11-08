/***************************************************************************************************

  Zyan Disassembler Library (Zydis)

  Original Author : Koi

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

/**
 * @file
 *
 * Test set for the letter-case formatter properties, in formatting and tokenizing mode.
 */

#include <Zycore/LibC.h>
#include <Zydis/Zydis.h>

/* ============================================================================================== */
/* Enums and Types                                                                                */
/* ============================================================================================== */

typedef struct FormatterProperty_
{
    ZydisFormatterProperty property;
    ZyanBool value;
} FormatterProperty;

typedef struct TestCase_
{
    const char* name;
    const ZyanU8* data;
    ZyanUSize length;
    ZydisFormatterStyle style;
    const FormatterProperty* properties;
    ZyanUSize property_count;
    const char* expected;
} TestCase;

/* ============================================================================================== */
/* Test data                                                                                      */
/* ============================================================================================== */

static const ZyanU8 DATA_LOCK_ADD[] = { 0xF0, 0x83, 0x00, 0x01 };
static const ZyanU8 DATA_REP_MOVSB[] = { 0xF3, 0xA4 };
static const ZyanU8 DATA_VADDPS_BCST[] = { 0x62, 0xF1, 0x74, 0x58, 0x58, 0x00 };
static const ZyanU8 DATA_VADDPS_SAE[] = { 0x62, 0xF1, 0x74, 0x18, 0x58, 0xC2 };
static const ZyanU8 DATA_REX_LOCK_ADD[] = { 0x48, 0xF0, 0x83, 0x00, 0x01 };

static const FormatterProperty PROP_UPPERCASE_PREFIXES[] =
{
    { ZYDIS_FORMATTER_PROP_UPPERCASE_PREFIXES, ZYAN_TRUE }
};

static const FormatterProperty PROP_UPPERCASE_DETAILED_PREFIXES[] =
{
    { ZYDIS_FORMATTER_PROP_DETAILED_PREFIXES, ZYAN_TRUE },
    { ZYDIS_FORMATTER_PROP_UPPERCASE_PREFIXES, ZYAN_TRUE }
};

static const FormatterProperty PROP_UPPERCASE_TYPECASTS[] =
{
    { ZYDIS_FORMATTER_PROP_UPPERCASE_TYPECASTS, ZYAN_TRUE }
};

static const FormatterProperty PROP_UPPERCASE_DECORATORS[] =
{
    { ZYDIS_FORMATTER_PROP_UPPERCASE_DECORATORS, ZYAN_TRUE }
};

static const TestCase TESTS[] =
{
    {
        "lock-prefix-uppercase", DATA_LOCK_ADD, ZYAN_ARRAY_LENGTH(DATA_LOCK_ADD),
        ZYDIS_FORMATTER_STYLE_INTEL, PROP_UPPERCASE_PREFIXES,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_PREFIXES), "LOCK add dword ptr [rax], 0x01"
    },
    {
        "rep-prefix-uppercase", DATA_REP_MOVSB, ZYAN_ARRAY_LENGTH(DATA_REP_MOVSB),
        ZYDIS_FORMATTER_STYLE_INTEL, PROP_UPPERCASE_PREFIXES,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_PREFIXES), "REP movsb"
    },
    {
        "rex-prefix-uppercase", DATA_REX_LOCK_ADD, ZYAN_ARRAY_LENGTH(DATA_REX_LOCK_ADD),
        ZYDIS_FORMATTER_STYLE_INTEL, PROP_UPPERCASE_DETAILED_PREFIXES,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_DETAILED_PREFIXES),
        "REX.W LOCK add dword ptr [rax], 0x01"
    },
    {
        "typecast-uppercase", DATA_LOCK_ADD, ZYAN_ARRAY_LENGTH(DATA_LOCK_ADD),
        ZYDIS_FORMATTER_STYLE_INTEL, PROP_UPPERCASE_TYPECASTS,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_TYPECASTS), "lock add DWORD PTR [rax], 0x01"
    },
    {
        "broadcast-decorator-uppercase", DATA_VADDPS_BCST, ZYAN_ARRAY_LENGTH(DATA_VADDPS_BCST),
        ZYDIS_FORMATTER_STYLE_INTEL, PROP_UPPERCASE_DECORATORS,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_DECORATORS), "vaddps zmm0, zmm1, [rax] {1TO16}"
    },
    {
        "rounding-decorator-uppercase", DATA_VADDPS_SAE, ZYAN_ARRAY_LENGTH(DATA_VADDPS_SAE),
        ZYDIS_FORMATTER_STYLE_INTEL, PROP_UPPERCASE_DECORATORS,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_DECORATORS), "vaddps zmm0, zmm1, zmm2 {RN-SAE}"
    },
    {
        "masm-broadcast-typecast-uppercase", DATA_VADDPS_BCST, ZYAN_ARRAY_LENGTH(DATA_VADDPS_BCST),
        ZYDIS_FORMATTER_STYLE_INTEL_MASM, PROP_UPPERCASE_TYPECASTS,
        ZYAN_ARRAY_LENGTH(PROP_UPPERCASE_TYPECASTS), "vaddps zmm0, zmm1, DWORD BCST [rax]"
    },
    {
        "default-case", DATA_LOCK_ADD, ZYAN_ARRAY_LENGTH(DATA_LOCK_ADD),
        ZYDIS_FORMATTER_STYLE_INTEL, ZYAN_NULL, 0, "lock add dword ptr [rax], 0x01"
    },
};

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

static ZyanBool FormatInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands, char* buffer,
    ZyanUSize length)
{
    return ZYAN_SUCCESS(ZydisFormatterFormatInstruction(formatter, instruction, operands,
        instruction->operand_count_visible, buffer, length, ZYDIS_RUNTIME_ADDRESS_NONE,
        ZYAN_NULL));
}

static ZyanBool TokenizeInstruction(const ZydisFormatter* formatter,
    const ZydisDecodedInstruction* instruction, const ZydisDecodedOperand* operands, char* buffer,
    ZyanUSize length)
{
    ZyanU8 token_buffer[512];
    ZydisFormatterTokenConst* token;
    if (ZYAN_FAILED(ZydisFormatterTokenizeInstruction(formatter, instruction, operands,
        instruction->operand_count_visible, token_buffer, sizeof(token_buffer),
        ZYDIS_RUNTIME_ADDRESS_NONE, &token, ZYAN_NULL)))
    {
        return ZYAN_FALSE;
    }

    buffer[0] = '\0';
    for (;;)
    {
        ZydisTokenType type;
        ZyanConstCharPointer value;
        if (ZYAN_FAILED(ZydisFormatterTokenGetValue(token, &type, &value)))
        {
            return ZYAN_FALSE;
        }
        if (ZYAN_STRLEN(buffer) + ZYAN_STRLEN(value) >= length)
        {
            return ZYAN_FALSE;
        }
        ZYAN_STRCAT(buffer, value);

        const ZyanStatus status = ZydisFormatterTokenNext(&token);
        if (status == ZYAN_STATUS_OUT_OF_RANGE)
        {
            return ZYAN_TRUE;
        }
        if (ZYAN_FAILED(status))
        {
            return ZYAN_FALSE;
        }
    }
}

/* ============================================================================================== */
/* Tests                                                                                          */
/* ============================================================================================== */

static ZyanBool RunTest(const TestCase* test)
{
    ZydisDecoder decoder;
    if (ZYAN_FAILED(ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64,
        ZYDIS_STACK_WIDTH_64)))
    {
        ZYAN_PRINTF("%s: FAILED TO INITIALIZE DECODER\n", test->name);
        return ZYAN_FALSE;
    }

    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
    if (ZYAN_FAILED(ZydisDecoderDecodeFull(&decoder, test->data, test->length, &instruction,
        operands)))
    {
        ZYAN_PRINTF("%s: FAILED TO DECODE INSTRUCTION\n", test->name);
        return ZYAN_FALSE;
    }

    ZydisFormatter formatter;
    if (ZYAN_FAILED(ZydisFormatterInit(&formatter, test->style)))
    {
        ZYAN_PRINTF("%s: FAILED TO INITIALIZE FORMATTER\n", test->name);
        return ZYAN_FALSE;
    }
    for (ZyanUSize i = 0; i < test->property_count; ++i)
    {
        if (ZYAN_FAILED(ZydisFormatterSetProperty(&formatter, test->properties[i].property,
            (ZyanUPointer)test->properties[i].value)))
        {
            ZYAN_PRINTF("%s: FAILED TO SET FORMATTER PROPERTY\n", test->name);
            return ZYAN_FALSE;
        }
    }

    ZyanBool passed = ZYAN_TRUE;

    char formatted[256];
    if (!FormatInstruction(&formatter, &instruction, operands, formatted, sizeof(formatted)))
    {
        ZYAN_PRINTF("%s: FAILED TO FORMAT INSTRUCTION\n", test->name);
        return ZYAN_FALSE;
    }
    if (ZYAN_STRCMP(formatted, test->expected))
    {
        ZYAN_PRINTF("%s: FORMATTED: \"%s\" != \"%s\"\n", test->name, formatted, test->expected);
        passed = ZYAN_FALSE;
    }

    char tokenized[256];
    if (!TokenizeInstruction(&formatter, &instruction, operands, tokenized, sizeof(tokenized)))
    {
        ZYAN_PRINTF("%s: FAILED TO TOKENIZE INSTRUCTION\n", test->name);
        return ZYAN_FALSE;
    }
    if (ZYAN_STRCMP(tokenized, test->expected))
    {
        ZYAN_PRINTF("%s: TOKENIZED: \"%s\" != \"%s\"\n", test->name, tokenized, test->expected);
        passed = ZYAN_FALSE;
    }

    return passed;
}

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(void)
{
    ZyanBool all_passed = ZYAN_TRUE;
    for (ZyanUSize i = 0; i < ZYAN_ARRAY_LENGTH(TESTS); ++i)
    {
        all_passed &= RunTest(&TESTS[i]);
    }
    if (!all_passed)
    {
        ZYAN_PRINTF("SOME TESTS FAILED\n");
        return 1;
    }

    ZYAN_PRINTF("ALL TESTS PASSED\n");
    return 0;
}

/* ============================================================================================== */
