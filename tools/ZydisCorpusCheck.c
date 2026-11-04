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

/**
 * @file
 * Decodes every sample of a decoder corpus file and verifies that it reaches the tagged
 * instruction definition through the tagged decoder tree path.
 *
 * A corpus file is tab-separated with one header line and the columns `bytes`, `mode`,
 * `enable`, `disable`, `encoding`, `map`, `opcode`, `osz`, `asz`, `id`, `form`, `mnemonic` and
 * `path`. Every sample that does not decode to the tagged definition, map, opcode and widths,
 * consumes other than exactly its bytes, fails to decode its operands or contradicts a step of
 * its path prints one `FAIL` line.
 */

#include "ZydisToolsShared.h"

#include <stdio.h>

#include <Zycore/LibC.h>
#include <Zydis/Zydis.h>
#include <Zydis/Internal/SharedData.h>

/* ============================================================================================== */
/* Corpus format                                                                                  */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Columns                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

#define CORPUS_LINE_SIZE 4096

static const char CORPUS_HEADER[] =
    "bytes\tmode\tenable\tdisable\tencoding\tmap\topcode\tosz\tasz\tid\tform\tmnemonic\tpath";

typedef enum CorpusColumn_
{
    CORPUS_COLUMN_BYTES,
    CORPUS_COLUMN_MODE,
    CORPUS_COLUMN_ENABLE,
    CORPUS_COLUMN_DISABLE,
    CORPUS_COLUMN_ENCODING,
    CORPUS_COLUMN_MAP,
    CORPUS_COLUMN_OPCODE,
    CORPUS_COLUMN_OSZ,
    CORPUS_COLUMN_ASZ,
    CORPUS_COLUMN_ID,
    CORPUS_COLUMN_FORM,
    CORPUS_COLUMN_MNEMONIC,
    CORPUS_COLUMN_PATH,

    CORPUS_COLUMN_COUNT
} CorpusColumn;

/* ---------------------------------------------------------------------------------------------- */
/* Tag vocabulary                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

typedef struct NamedValue_
{
    const char* name;
    ZyanU32 value;
} NamedValue;

typedef struct MachineModeTag_
{
    const char* name;
    ZydisMachineMode machine_mode;
    ZydisStackWidth stack_width;
} MachineModeTag;

static const MachineModeTag MACHINE_MODE_TAGS[] =
{
    { "16", ZYDIS_MACHINE_MODE_LONG_COMPAT_16, ZYDIS_STACK_WIDTH_16 },
    { "32", ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_STACK_WIDTH_32 },
    { "64", ZYDIS_MACHINE_MODE_LONG_64,        ZYDIS_STACK_WIDTH_64 }
};

static const NamedValue DECODER_MODE_TAGS[] =
{
    { "amd_branches", ZYDIS_DECODER_MODE_AMD_BRANCHES },
    { "apx",          ZYDIS_DECODER_MODE_APX          },
    { "cet",          ZYDIS_DECODER_MODE_CET          },
    { "cldemote",     ZYDIS_DECODER_MODE_CLDEMOTE     },
    { "ibhf",         ZYDIS_DECODER_MODE_IBHF         },
    { "iprefetch",    ZYDIS_DECODER_MODE_IPREFETCH    },
    { "knc",          ZYDIS_DECODER_MODE_KNC          },
    { "lzcnt",        ZYDIS_DECODER_MODE_LZCNT        },
    { "mpx",          ZYDIS_DECODER_MODE_MPX          },
    { "prefetchrst",  ZYDIS_DECODER_MODE_PREFETCHRST  },
    { "tzcnt",        ZYDIS_DECODER_MODE_TZCNT        },
    { "ud0_compat",   ZYDIS_DECODER_MODE_UD0_COMPAT   },
    { "wbnoinvd",     ZYDIS_DECODER_MODE_WBNOINVD     }
};

static const NamedValue ENCODING_TAGS[] =
{
    { "default", ZYDIS_INSTRUCTION_ENCODING_LEGACY },
    { "3dnow",   ZYDIS_INSTRUCTION_ENCODING_3DNOW  },
    { "xop",     ZYDIS_INSTRUCTION_ENCODING_XOP    },
    { "vex",     ZYDIS_INSTRUCTION_ENCODING_VEX    },
    { "evex",    ZYDIS_INSTRUCTION_ENCODING_EVEX   },
    { "mvex",    ZYDIS_INSTRUCTION_ENCODING_MVEX   }
};

static const NamedValue OPCODE_MAP_TAGS[] =
{
    { "map0", ZYDIS_OPCODE_MAP_DEFAULT },
    { "0f",   ZYDIS_OPCODE_MAP_0F      },
    { "0f38", ZYDIS_OPCODE_MAP_0F38    },
    { "0f3a", ZYDIS_OPCODE_MAP_0F3A    },
    { "0f0f", ZYDIS_OPCODE_MAP_0F0F    },
    { "map4", ZYDIS_OPCODE_MAP_MAP4    },
    { "map5", ZYDIS_OPCODE_MAP_MAP5    },
    { "map6", ZYDIS_OPCODE_MAP_MAP6    },
    { "map7", ZYDIS_OPCODE_MAP_MAP7    },
    { "xop8", ZYDIS_OPCODE_MAP_XOP8    },
    { "xop9", ZYDIS_OPCODE_MAP_XOP9    },
    { "xopa", ZYDIS_OPCODE_MAP_XOPA    }
};

static const NamedValue OPERAND_SIZE_TAGS[] =
{
    { "8",  8  },
    { "16", 16 },
    { "32", 32 },
    { "64", 64 }
};

static const NamedValue ADDRESS_SIZE_TAGS[] =
{
    { "16", 16 },
    { "32", 32 },
    { "64", 64 }
};

/* ---------------------------------------------------------------------------------------------- */
/* Sample                                                                                         */
/* ---------------------------------------------------------------------------------------------- */

typedef struct CorpusSample_
{
    ZyanU8 bytes[ZYDIS_MAX_INSTRUCTION_LENGTH];
    ZyanU8 length;
    const MachineModeTag* machine_mode;
    ZyanU32 enabled_modes;
    ZyanU32 disabled_modes;
    ZydisInstructionEncoding encoding;
    ZydisOpcodeMap map;
    ZyanU8 opcode;
    ZyanU8 operand_width;
    ZyanU8 address_width;
    ZyanU16 id;
} CorpusSample;

typedef enum LineResult_
{
    LINE_RESULT_PASSED,
    LINE_RESULT_FAILED,
    LINE_RESULT_SKIPPED
} LineResult;

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Helper functions                                                                               */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* General                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Writes the failure reason and returns `ZYAN_FALSE`, so a check can fail in one statement.
 *
 * @param   reason  A buffer of `CORPUS_LINE_SIZE` bytes that receives the reason.
 * @param   format  The format string.
 *
 * @return  `ZYAN_FALSE`.
 */
static ZyanBool Fail(char* reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    ZYAN_VSNPRINTF(reason, CORPUS_LINE_SIZE, format, args);
    va_end(args);
    return ZYAN_FALSE;
}

static ZyanBool EqualsCounted(const char* text, ZyanUSize length, const char* name)
{
    return (ZYAN_STRLEN(name) == length) && !ZYAN_STRNCMP(text, name, length);
}

static ZyanBool LookupName(const NamedValue* table, ZyanUSize count, const char* text,
    ZyanUSize length, ZyanU32* value)
{
    for (ZyanUSize i = 0; i < count; ++i)
    {
        if (EqualsCounted(text, length, table[i].name))
        {
            *value = table[i].value;
            return ZYAN_TRUE;
        }
    }
    return ZYAN_FALSE;
}

static const char* LookupValue(const NamedValue* table, ZyanUSize count, ZyanU32 value)
{
    for (ZyanUSize i = 0; i < count; ++i)
    {
        if (table[i].value == value)
        {
            return table[i].name;
        }
    }
    return "?";
}

static const char* GetEncodingTag(ZydisInstructionEncoding encoding)
{
    // REX2 instructions share the legacy definition table, so their samples carry its tag.
    if (encoding == ZYDIS_INSTRUCTION_ENCODING_REX2)
    {
        encoding = ZYDIS_INSTRUCTION_ENCODING_LEGACY;
    }
    return LookupValue(ENCODING_TAGS, ZYAN_ARRAY_LENGTH(ENCODING_TAGS), encoding);
}

static const char* GetEncodingName(ZydisInstructionEncoding encoding)
{
    return (encoding == ZYDIS_INSTRUCTION_ENCODING_REX2) ? "rex2" : GetEncodingTag(encoding);
}

/**
 * Recovers the id of a definition by searching the definition table of its encoding.
 *
 * @param   encoding    The instruction encoding.
 * @param   definition  The definition pointer of the decoder context.
 * @param   id          Receives the id.
 *
 * @return  `ZYAN_TRUE` if the table holds the definition.
 */
static ZyanBool FindDefinitionId(ZydisInstructionEncoding encoding, const void* definition,
    ZyanU16* id)
{
    // The decoder tree stores ids as 16-bit values, so this bound covers every id it can reach.
    for (ZyanU32 i = 0; i <= 0xFFFF; ++i)
    {
        const ZydisInstructionDefinition* candidate;
        ZydisGetInstructionDefinition(encoding, (ZyanU16)i, &candidate);
        if ((const void*)candidate == definition)
        {
            *id = (ZyanU16)i;
            return ZYAN_TRUE;
        }
    }
    return ZYAN_FALSE;
}

/* ---------------------------------------------------------------------------------------------- */
/* Parsing                                                                                        */
/* ---------------------------------------------------------------------------------------------- */

static ZyanBool ParseHexDigit(char c, ZyanU8* value)
{
    if ((c >= '0') && (c <= '9'))
    {
        *value = (ZyanU8)(c - '0');
        return ZYAN_TRUE;
    }
    if ((c >= 'A') && (c <= 'F'))
    {
        *value = (ZyanU8)(c - 'A' + 10);
        return ZYAN_TRUE;
    }
    if ((c >= 'a') && (c <= 'f'))
    {
        *value = (ZyanU8)(c - 'a' + 10);
        return ZYAN_TRUE;
    }
    return ZYAN_FALSE;
}

static ZyanBool ParseHexByte(const char* text, ZyanU8* value)
{
    ZyanU8 high;
    ZyanU8 low;
    if (!ParseHexDigit(text[0], &high) || !ParseHexDigit(text[1], &low))
    {
        return ZYAN_FALSE;
    }
    *value = (ZyanU8)((high << 4) | low);
    return ZYAN_TRUE;
}

static ZyanBool ParseBytes(const char* text, CorpusSample* sample)
{
    const ZyanUSize length = ZYAN_STRLEN(text);
    if ((length == 0) || (length % 2) || (length / 2 > ZYDIS_MAX_INSTRUCTION_LENGTH))
    {
        return ZYAN_FALSE;
    }
    for (ZyanUSize i = 0; i < length / 2; ++i)
    {
        if (!ParseHexByte(&text[i * 2], &sample->bytes[i]))
        {
            return ZYAN_FALSE;
        }
    }
    sample->length = (ZyanU8)(length / 2);
    return ZYAN_TRUE;
}

static ZyanBool ParseId(const char* text, ZyanU16* id)
{
    if (*text == '\0')
    {
        return ZYAN_FALSE;
    }
    ZyanU32 value = 0;
    for (const char* c = text; *c != '\0'; ++c)
    {
        if ((*c < '0') || (*c > '9'))
        {
            return ZYAN_FALSE;
        }
        value = value * 10 + (ZyanU32)(*c - '0');
        if (value > 0xFFFF)
        {
            return ZYAN_FALSE;
        }
    }
    *id = (ZyanU16)value;
    return ZYAN_TRUE;
}

static ZyanBool ParseDecoderModes(const char* text, ZyanU32* modes, char* reason)
{
    *modes = 0;
    if (!ZYAN_STRCMP(text, "-"))
    {
        return ZYAN_TRUE;
    }
    const char* entry = text;
    for (;;)
    {
        const ZyanUSize length = ZYAN_STRCSPN(entry, ",");
        ZyanU32 mode;
        if (!LookupName(DECODER_MODE_TAGS, ZYAN_ARRAY_LENGTH(DECODER_MODE_TAGS), entry, length,
            &mode))
        {
            return Fail(reason, "unknown decoder mode %.*s", (int)length, entry);
        }
        *modes |= 1u << mode;
        if (entry[length] == '\0')
        {
            return ZYAN_TRUE;
        }
        entry += length + 1;
    }
}

/**
 * Splits a line at its tabs in place.
 *
 * @param   line    The line.
 * @param   columns Receives the first `CORPUS_COLUMN_COUNT` columns, `ZYAN_NULL` for each one
 *                  the line does not have.
 *
 * @return  The number of columns of the line, including the ones beyond `CORPUS_COLUMN_COUNT`.
 */
static ZyanUSize SplitColumns(char* line, const char* columns[CORPUS_COLUMN_COUNT])
{
    for (ZyanUSize i = 0; i < CORPUS_COLUMN_COUNT; ++i)
    {
        columns[i] = ZYAN_NULL;
    }
    ZyanUSize count = 0;
    char* column = line;
    for (;;)
    {
        if (count < CORPUS_COLUMN_COUNT)
        {
            columns[count] = column;
        }
        ++count;
        char* tab = ZYAN_STRCHR(column, '\t');
        if (!tab)
        {
            return count;
        }
        *tab = '\0';
        column = tab + 1;
    }
}

static ZyanBool ParseSample(const char* const columns[CORPUS_COLUMN_COUNT], CorpusSample* sample,
    char* reason)
{
    const char* text;

    text = columns[CORPUS_COLUMN_BYTES];
    if (!ParseBytes(text, sample))
    {
        return Fail(reason, "malformed bytes %s", text);
    }

    text = columns[CORPUS_COLUMN_MODE];
    sample->machine_mode = ZYAN_NULL;
    for (ZyanUSize i = 0; i < ZYAN_ARRAY_LENGTH(MACHINE_MODE_TAGS); ++i)
    {
        if (!ZYAN_STRCMP(text, MACHINE_MODE_TAGS[i].name))
        {
            sample->machine_mode = &MACHINE_MODE_TAGS[i];
            break;
        }
    }
    if (!sample->machine_mode)
    {
        return Fail(reason, "unknown machine mode %s", text);
    }

    if (!ParseDecoderModes(columns[CORPUS_COLUMN_ENABLE], &sample->enabled_modes, reason) ||
        !ParseDecoderModes(columns[CORPUS_COLUMN_DISABLE], &sample->disabled_modes, reason))
    {
        return ZYAN_FALSE;
    }

    ZyanU32 value;
    text = columns[CORPUS_COLUMN_ENCODING];
    if (!LookupName(ENCODING_TAGS, ZYAN_ARRAY_LENGTH(ENCODING_TAGS), text, ZYAN_STRLEN(text),
        &value))
    {
        return Fail(reason, "unknown encoding %s", text);
    }
    sample->encoding = (ZydisInstructionEncoding)value;

    text = columns[CORPUS_COLUMN_MAP];
    if (!LookupName(OPCODE_MAP_TAGS, ZYAN_ARRAY_LENGTH(OPCODE_MAP_TAGS), text, ZYAN_STRLEN(text),
        &value))
    {
        return Fail(reason, "unknown map %s", text);
    }
    sample->map = (ZydisOpcodeMap)value;

    text = columns[CORPUS_COLUMN_OPCODE];
    if ((ZYAN_STRLEN(text) != 2) || !ParseHexByte(text, &sample->opcode))
    {
        return Fail(reason, "malformed opcode %s", text);
    }

    text = columns[CORPUS_COLUMN_OSZ];
    if (!LookupName(OPERAND_SIZE_TAGS, ZYAN_ARRAY_LENGTH(OPERAND_SIZE_TAGS), text,
        ZYAN_STRLEN(text), &value))
    {
        return Fail(reason, "unknown osz %s", text);
    }
    sample->operand_width = (ZyanU8)value;

    text = columns[CORPUS_COLUMN_ASZ];
    if (!LookupName(ADDRESS_SIZE_TAGS, ZYAN_ARRAY_LENGTH(ADDRESS_SIZE_TAGS), text,
        ZYAN_STRLEN(text), &value))
    {
        return Fail(reason, "unknown asz %s", text);
    }
    sample->address_width = (ZyanU8)value;

    text = columns[CORPUS_COLUMN_ID];
    if (!ParseId(text, &sample->id))
    {
        return Fail(reason, "malformed id %s", text);
    }

    return ZYAN_TRUE;
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Path validation                                                                                */
/* ============================================================================================== */

/* ---------------------------------------------------------------------------------------------- */
/* Decoded slots                                                                                  */
/* ---------------------------------------------------------------------------------------------- */

typedef struct CheckContext_
{
    const ZydisDecoder* decoder;
    const ZydisDecodedInstruction* instruction;
    ZyanU32 enabled_modes;
    ZyanU32 disabled_modes;
} CheckContext;

static const char* const SLOTS_BIT[] = { "0", "1" };
static const char* const SLOTS_EVEX_SCC[] =
{
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
};
static const char* const SLOTS_MANDATORY_PREFIX[] = { "ignore", "none", "66", "f3", "f2" };
static const char* const SLOTS_MODE_COMPACT[] = { "64", "!64" };
static const char* const SLOTS_MODRM_FIELD[] = { "0", "1", "2", "3", "4", "5", "6", "7" };
static const char* const SLOTS_MODRM_MOD[] = { "0", "1", "2", "3" };
static const char* const SLOTS_MODRM_MOD_COMPACT[] = { "reg", "mem" };
static const char* const SLOTS_REX_2[] = { "no_rex2", "rex2" };
static const char* const SLOTS_SWITCH_TABLE[] = { "default" };
static const char* const SLOTS_VECTOR_LENGTH[] = { "128", "256", "512" };
static const char* const SLOTS_WIDTH[] = { "16", "32", "64" };

static ZyanBool HasLegacyPrefix(const ZydisDecodedInstruction* instruction, ZyanU8 value)
{
    for (ZyanU8 i = 0; i < instruction->raw.prefix_count; ++i)
    {
        if (instruction->raw.prefixes[i].value == value)
        {
            return ZYAN_TRUE;
        }
    }
    return ZYAN_FALSE;
}

static ZyanBool GetPrefixW(const ZydisDecodedInstruction* instruction, ZyanU8* w)
{
    switch (instruction->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_LEGACY:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        *w = (instruction->attributes & ZYDIS_ATTRIB_HAS_REX) ? instruction->raw.rex.W : 0;
        return ZYAN_TRUE;
    case ZYDIS_INSTRUCTION_ENCODING_REX2:
        *w = instruction->raw.rex2.W;
        return ZYAN_TRUE;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        *w = instruction->raw.xop.W;
        return ZYAN_TRUE;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        *w = instruction->raw.vex.W;
        return ZYAN_TRUE;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        *w = instruction->raw.evex.W;
        return ZYAN_TRUE;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        *w = instruction->raw.mvex.W;
        return ZYAN_TRUE;
    default:
        return ZYAN_FALSE;
    }
}

static const char* DecodeAddressSize(const CheckContext* context)
{
    // The decoder routes on the 67 prefix, before the definition's address size map applies.
    const ZyanBool has_override =
        (context->instruction->attributes & ZYDIS_ATTRIB_HAS_ADDRESSSIZE) != 0;
    switch (context->instruction->machine_mode)
    {
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
        return SLOTS_WIDTH[has_override ? 1 : 0];
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
        return SLOTS_WIDTH[has_override ? 0 : 1];
    case ZYDIS_MACHINE_MODE_LONG_64:
        return SLOTS_WIDTH[has_override ? 1 : 2];
    default:
        return ZYAN_NULL;
    }
}

static const char* DecodeEvexB(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ?
        SLOTS_BIT[instruction->raw.evex.b] : ZYAN_NULL;
}

static const char* DecodeEvexNd(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ?
        SLOTS_BIT[instruction->raw.evex.ND] : ZYAN_NULL;
}

static const char* DecodeEvexNf(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ?
        SLOTS_BIT[instruction->raw.evex.NF] : ZYAN_NULL;
}

static const char* DecodeEvexScc(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) ?
        SLOTS_EVEX_SCC[instruction->raw.evex.SCC] : ZYAN_NULL;
}

static const char* DecodeEvexU(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    if (instruction->encoding != ZYDIS_INSTRUCTION_ENCODING_EVEX)
    {
        return ZYAN_NULL;
    }
    // With APX the decoder reads U as X4 on memory forms and routes them as U=1.
    if ((context->decoder->decoder_mode & (1u << ZYDIS_DECODER_MODE_APX)) &&
        (instruction->attributes & ZYDIS_ATTRIB_HAS_MODRM) && (instruction->raw.modrm.mod != 3))
    {
        return SLOTS_BIT[1];
    }
    return SLOTS_BIT[instruction->raw.evex.U];
}

static const char* DecodeFeature(const CheckContext* context, ZydisDecoderMode mode)
{
    // The tag must list the mode the slot depends on, so a changed decoder default cannot
    // silently pass the sample.
    const ZyanU32 bit = 1u << mode;
    const ZyanBool is_active = (context->decoder->decoder_mode & bit) != 0;
    if (is_active)
    {
        return (context->enabled_modes & bit) ? SLOTS_BIT[1] : "1, not tagged";
    }
    return (context->disabled_modes & bit) ? SLOTS_BIT[0] : "0, not tagged";
}

#define DEFINE_FEATURE_DECODER(function_name, mode) \
    static const char* function_name(const CheckContext* context) \
    { \
        return DecodeFeature(context, mode); \
    }

DEFINE_FEATURE_DECODER(DecodeFeatureAmd, ZYDIS_DECODER_MODE_AMD_BRANCHES)
DEFINE_FEATURE_DECODER(DecodeFeatureCet, ZYDIS_DECODER_MODE_CET)
DEFINE_FEATURE_DECODER(DecodeFeatureCldemote, ZYDIS_DECODER_MODE_CLDEMOTE)
DEFINE_FEATURE_DECODER(DecodeFeatureIbhf, ZYDIS_DECODER_MODE_IBHF)
DEFINE_FEATURE_DECODER(DecodeFeatureIprefetch, ZYDIS_DECODER_MODE_IPREFETCH)
DEFINE_FEATURE_DECODER(DecodeFeatureKnc, ZYDIS_DECODER_MODE_KNC)
DEFINE_FEATURE_DECODER(DecodeFeatureLzcnt, ZYDIS_DECODER_MODE_LZCNT)
DEFINE_FEATURE_DECODER(DecodeFeatureMpx, ZYDIS_DECODER_MODE_MPX)
DEFINE_FEATURE_DECODER(DecodeFeaturePrefetchrst, ZYDIS_DECODER_MODE_PREFETCHRST)
DEFINE_FEATURE_DECODER(DecodeFeatureTzcnt, ZYDIS_DECODER_MODE_TZCNT)
DEFINE_FEATURE_DECODER(DecodeFeatureUd0Compat, ZYDIS_DECODER_MODE_UD0_COMPAT)
DEFINE_FEATURE_DECODER(DecodeFeatureWbnoinvd, ZYDIS_DECODER_MODE_WBNOINVD)

static const char* DecodeMandatoryPrefix(const CheckContext* context)
{
    // The decoder routes on the prefix candidate before the definition decides whether it
    // consumes it, so the prefix type cannot tell the slot. The last F2 or F3 is the candidate,
    // a 66 only while no candidate is set.
    const ZydisDecodedInstruction* instruction = context->instruction;
    ZyanU8 candidate = 0x00;
    for (ZyanU8 i = 0; i < instruction->raw.prefix_count; ++i)
    {
        const ZyanU8 value = instruction->raw.prefixes[i].value;
        if ((value == 0xF2) || (value == 0xF3) || ((value == 0x66) && (candidate == 0x00)))
        {
            candidate = value;
        }
    }
    switch (candidate)
    {
    case 0x00:
        return SLOTS_MANDATORY_PREFIX[1];
    case 0x66:
        return SLOTS_MANDATORY_PREFIX[2];
    case 0xF3:
        return SLOTS_MANDATORY_PREFIX[3];
    case 0xF2:
        return SLOTS_MANDATORY_PREFIX[4];
    default:
        return ZYAN_NULL;
    }
}

static const char* DecodeMode(const CheckContext* context)
{
    switch (context->instruction->machine_mode)
    {
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
        return SLOTS_WIDTH[0];
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
        return SLOTS_WIDTH[1];
    case ZYDIS_MACHINE_MODE_LONG_64:
        return SLOTS_WIDTH[2];
    default:
        return ZYAN_NULL;
    }
}

static const char* DecodeModeCompact(const CheckContext* context)
{
    return (context->instruction->machine_mode == ZYDIS_MACHINE_MODE_LONG_64) ?
        SLOTS_MODE_COMPACT[0] : SLOTS_MODE_COMPACT[1];
}

static const char* DecodeModrmMod(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->attributes & ZYDIS_ATTRIB_HAS_MODRM) ?
        SLOTS_MODRM_MOD[instruction->raw.modrm.mod] : ZYAN_NULL;
}

static const char* DecodeModrmModCompact(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    if (!(instruction->attributes & ZYDIS_ATTRIB_HAS_MODRM))
    {
        return ZYAN_NULL;
    }
    return (instruction->raw.modrm.mod == 3) ?
        SLOTS_MODRM_MOD_COMPACT[0] : SLOTS_MODRM_MOD_COMPACT[1];
}

static const char* DecodeModrmReg(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->attributes & ZYDIS_ATTRIB_HAS_MODRM) ?
        SLOTS_MODRM_FIELD[instruction->raw.modrm.reg] : ZYAN_NULL;
}

static const char* DecodeModrmRm(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->attributes & ZYDIS_ATTRIB_HAS_MODRM) ?
        SLOTS_MODRM_FIELD[instruction->raw.modrm.rm] : ZYAN_NULL;
}

static const char* DecodeMvexE(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX) ?
        SLOTS_BIT[instruction->raw.mvex.E] : ZYAN_NULL;
}

static const char* DecodeOperandSize(const CheckContext* context)
{
    // The decoder routes on the 66 prefix and W before the definition's operand size map
    // applies, so `operand_width` can differ from the slot (`in` and `out` with REX.W, `pushfq`).
    // The prefix bytes are scanned because the attribute loses a 66 that the definition consumes
    // as its mandatory prefix.
    const ZydisDecodedInstruction* instruction = context->instruction;
    const ZyanBool has_override = HasLegacyPrefix(instruction, 0x66);
    ZyanU8 w;
    if (!GetPrefixW(instruction, &w))
    {
        return ZYAN_NULL;
    }
    switch (instruction->machine_mode)
    {
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_16:
        return SLOTS_WIDTH[has_override ? 1 : 0];
    case ZYDIS_MACHINE_MODE_LONG_COMPAT_32:
        return SLOTS_WIDTH[has_override ? 0 : 1];
    case ZYDIS_MACHINE_MODE_LONG_64:
        return w ? SLOTS_WIDTH[2] : SLOTS_WIDTH[has_override ? 0 : 1];
    default:
        return ZYAN_NULL;
    }
}

static const char* DecodePrefixGroup1(const CheckContext* context)
{
    // The decoder's group 1 filter tests F2 and F3 only, a lock prefix does not route.
    const ZydisDecodedInstruction* instruction = context->instruction;
    return (HasLegacyPrefix(instruction, 0xF2) || HasLegacyPrefix(instruction, 0xF3)) ?
        SLOTS_BIT[1] : SLOTS_BIT[0];
}

static const char* DecodeRex2(const CheckContext* context)
{
    return (context->instruction->encoding == ZYDIS_INSTRUCTION_ENCODING_REX2) ?
        SLOTS_REX_2[1] : SLOTS_REX_2[0];
}

static const char* DecodeRexB(const CheckContext* context)
{
    // The decoder routes on the extension bits the register index receives. The VEX family
    // stores B inverted, while EVEX.B4 and the REX2 bits are stored as is.
    const ZydisDecodedInstruction* instruction = context->instruction;
    ZyanU8 b;
    switch (instruction->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_LEGACY:
    case ZYDIS_INSTRUCTION_ENCODING_3DNOW:
        b = (instruction->attributes & ZYDIS_ATTRIB_HAS_REX) ? instruction->raw.rex.B : 0;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_REX2:
        b = instruction->raw.rex2.B3 | instruction->raw.rex2.B4;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        b = instruction->raw.xop.B ^ 1;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        b = instruction->raw.vex.B ^ 1;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        b = (instruction->raw.evex.B3 ^ 1) | instruction->raw.evex.B4;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        b = instruction->raw.mvex.B ^ 1;
        break;
    default:
        return ZYAN_NULL;
    }
    return SLOTS_BIT[b];
}

static const char* DecodeRexW(const CheckContext* context)
{
    ZyanU8 w;
    return GetPrefixW(context->instruction, &w) ? SLOTS_BIT[w] : ZYAN_NULL;
}

static const char* DecodeSwitchTable(const CheckContext* context)
{
    const ZydisInstructionEncoding encoding = context->instruction->encoding;
    return (encoding == ZYDIS_INSTRUCTION_ENCODING_LEGACY) ?
        SLOTS_SWITCH_TABLE[0] : GetEncodingName(encoding);
}

static const char* DecodeSwitchTableXop(const CheckContext* context)
{
    // REX2 makes 8F a plain opcode, and the decoder routes it to the legacy slot.
    const ZydisInstructionEncoding encoding = context->instruction->encoding;
    return ((encoding == ZYDIS_INSTRUCTION_ENCODING_LEGACY) ||
            (encoding == ZYDIS_INSTRUCTION_ENCODING_REX2)) ?
        SLOTS_SWITCH_TABLE[0] : GetEncodingName(encoding);
}

static const char* DecodeVectorLength(const CheckContext* context)
{
    const ZydisDecodedInstruction* instruction = context->instruction;
    ZyanU8 length;
    switch (instruction->encoding)
    {
    case ZYDIS_INSTRUCTION_ENCODING_XOP:
        length = instruction->raw.xop.L;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_VEX:
        length = instruction->raw.vex.L;
        break;
    case ZYDIS_INSTRUCTION_ENCODING_EVEX:
        length = (ZyanU8)((instruction->raw.evex.L2 << 1) | instruction->raw.evex.L);
        break;
    case ZYDIS_INSTRUCTION_ENCODING_MVEX:
        // MVEX has no length field, the decoder fixes it at 512 bits.
        length = 2;
        break;
    default:
        return ZYAN_NULL;
    }
    return (length < ZYAN_ARRAY_LENGTH(SLOTS_VECTOR_LENGTH)) ?
        SLOTS_VECTOR_LENGTH[length] : ZYAN_NULL;
}

/* ---------------------------------------------------------------------------------------------- */
/* Axes                                                                                           */
/* ---------------------------------------------------------------------------------------------- */

typedef struct AxisDefinition_
{
    const char* name;
    const char* const* slots;
    ZyanUSize slot_count;
    /**
     * Returns the slot the decoder took for the decoded instruction, a description for the
     * failure line if that is no slot of the axis, or `ZYAN_NULL` if the axis does not apply.
     */
    const char* (*decode)(const CheckContext* context);
} AxisDefinition;

#define AXIS_SLOTS(slots) slots, ZYAN_ARRAY_LENGTH(slots)

static const AxisDefinition AXES[] =
{
    { "address_size",        AXIS_SLOTS(SLOTS_WIDTH),              DecodeAddressSize },
    { "evex_b",              AXIS_SLOTS(SLOTS_BIT),                DecodeEvexB },
    { "evex_nd",             AXIS_SLOTS(SLOTS_BIT),                DecodeEvexNd },
    { "evex_nf",             AXIS_SLOTS(SLOTS_BIT),                DecodeEvexNf },
    { "evex_scc",            AXIS_SLOTS(SLOTS_EVEX_SCC),           DecodeEvexScc },
    { "evex_u",              AXIS_SLOTS(SLOTS_BIT),                DecodeEvexU },
    { "feature_amd",         AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureAmd },
    { "feature_cet",         AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureCet },
    { "feature_cldemote",    AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureCldemote },
    { "feature_ibhf",        AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureIbhf },
    { "feature_iprefetch",   AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureIprefetch },
    { "feature_knc",         AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureKnc },
    { "feature_lzcnt",       AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureLzcnt },
    { "feature_mpx",         AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureMpx },
    { "feature_prefetchrst", AXIS_SLOTS(SLOTS_BIT),                DecodeFeaturePrefetchrst },
    { "feature_tzcnt",       AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureTzcnt },
    { "feature_ud0_compat",  AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureUd0Compat },
    { "feature_wbnoinvd",    AXIS_SLOTS(SLOTS_BIT),                DecodeFeatureWbnoinvd },
    { "mandatory_prefix",    AXIS_SLOTS(SLOTS_MANDATORY_PREFIX),   DecodeMandatoryPrefix },
    { "mode",                AXIS_SLOTS(SLOTS_WIDTH),              DecodeMode },
    { "mode_compact",        AXIS_SLOTS(SLOTS_MODE_COMPACT),       DecodeModeCompact },
    { "modrm_mod",           AXIS_SLOTS(SLOTS_MODRM_MOD),          DecodeModrmMod },
    { "modrm_mod_compact",   AXIS_SLOTS(SLOTS_MODRM_MOD_COMPACT),  DecodeModrmModCompact },
    { "modrm_reg",           AXIS_SLOTS(SLOTS_MODRM_FIELD),        DecodeModrmReg },
    { "modrm_rm",            AXIS_SLOTS(SLOTS_MODRM_FIELD),        DecodeModrmRm },
    { "mvex_e",              AXIS_SLOTS(SLOTS_BIT),                DecodeMvexE },
    { "operand_size",        AXIS_SLOTS(SLOTS_WIDTH),              DecodeOperandSize },
    { "prefix_group1",       AXIS_SLOTS(SLOTS_BIT),                DecodePrefixGroup1 },
    { "rex_2",               AXIS_SLOTS(SLOTS_REX_2),              DecodeRex2 },
    { "rex_b",               AXIS_SLOTS(SLOTS_BIT),                DecodeRexB },
    { "rex_w",               AXIS_SLOTS(SLOTS_BIT),                DecodeRexW },
    { "switch_table_emvex",  AXIS_SLOTS(SLOTS_SWITCH_TABLE),       DecodeSwitchTable },
    { "switch_table_rex2",   AXIS_SLOTS(SLOTS_SWITCH_TABLE),       DecodeSwitchTable },
    { "switch_table_vex",    AXIS_SLOTS(SLOTS_SWITCH_TABLE),       DecodeSwitchTable },
    { "switch_table_xop",    AXIS_SLOTS(SLOTS_SWITCH_TABLE),       DecodeSwitchTableXop },
    { "vector_length",       AXIS_SLOTS(SLOTS_VECTOR_LENGTH),      DecodeVectorLength }
};

static const AxisDefinition* FindAxis(const char* name, ZyanUSize length)
{
    for (ZyanUSize i = 0; i < ZYAN_ARRAY_LENGTH(AXES); ++i)
    {
        if (EqualsCounted(name, length, AXES[i].name))
        {
            return &AXES[i];
        }
    }
    return ZYAN_NULL;
}

static ZyanBool IsAxisSlot(const AxisDefinition* axis, const char* slot, ZyanUSize length)
{
    for (ZyanUSize i = 0; i < axis->slot_count; ++i)
    {
        if (EqualsCounted(slot, length, axis->slots[i]))
        {
            return ZYAN_TRUE;
        }
    }
    return ZYAN_FALSE;
}

/* ---------------------------------------------------------------------------------------------- */
/* Steps                                                                                          */
/* ---------------------------------------------------------------------------------------------- */

/**
 * Checks one `name=slot`, `name=slot|slot` or `name=else:slot|slot` step of a path.
 *
 * @param   context The check context.
 * @param   step    The step, not terminated.
 * @param   length  The length of the step.
 * @param   reason  Receives the failure reason.
 *
 * @return  `ZYAN_TRUE` if every slot is known for the axis and one of them is the slot the
 *          decoder took.
 */
static ZyanBool CheckPathStep(const CheckContext* context, const char* step, ZyanUSize length,
    char* reason)
{
    static const char ELSE_PREFIX[] = "else:";
    const ZyanUSize else_length = sizeof(ELSE_PREFIX) - 1;

    if (length == 0)
    {
        return Fail(reason, "empty path step");
    }
    const char* separator = (const char*)ZYAN_MEMCHR(step, '=', length);
    if (!separator || (separator == step))
    {
        return Fail(reason, "malformed path step %.*s", (int)length, step);
    }
    const ZyanUSize name_length = (ZyanUSize)(separator - step);
    const AxisDefinition* axis = FindAxis(step, name_length);
    if (!axis)
    {
        return Fail(reason, "unknown path axis %.*s", (int)name_length, step);
    }

    const char* slots = separator + 1;
    const char* const end = step + length;
    if (((ZyanUSize)(end - slots) >= else_length) &&
        !ZYAN_STRNCMP(slots, ELSE_PREFIX, else_length))
    {
        slots += else_length;
    }

    const char* decoded = axis->decode(context);
    ZyanBool is_match = ZYAN_FALSE;
    const char* slot = slots;
    for (;;)
    {
        const char* slot_end = slot;
        while ((slot_end < end) && (*slot_end != '|'))
        {
            ++slot_end;
        }
        const ZyanUSize slot_length = (ZyanUSize)(slot_end - slot);
        if (!IsAxisSlot(axis, slot, slot_length))
        {
            return Fail(reason, "unknown slot %.*s=%.*s", (int)name_length, step,
                (int)slot_length, slot);
        }
        if (decoded && EqualsCounted(slot, slot_length, decoded))
        {
            is_match = ZYAN_TRUE;
        }
        if (slot_end == end)
        {
            break;
        }
        slot = slot_end + 1;
    }

    if (!is_match)
    {
        return decoded ?
            Fail(reason, "path %.*s (decoded %s)", (int)length, step, decoded) :
            Fail(reason, "path %.*s (axis does not apply to the decoded instruction)",
                (int)length, step);
    }
    return ZYAN_TRUE;
}

static ZyanBool CheckPath(const CheckContext* context, const char* path, char* reason)
{
    if (*path == '\0')
    {
        return ZYAN_TRUE;
    }
    const char* step = path;
    for (;;)
    {
        const ZyanUSize length = ZYAN_STRCSPN(step, ",");
        if (!CheckPathStep(context, step, length, reason))
        {
            return ZYAN_FALSE;
        }
        if (step[length] == '\0')
        {
            return ZYAN_TRUE;
        }
        step += length + 1;
    }
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Sample checks                                                                                  */
/* ============================================================================================== */

static ZyanBool IsUnsupportedByBuild(const CorpusSample* sample)
{
    ZYAN_UNUSED(sample);
#ifdef ZYDIS_DISABLE_KNC
    if ((sample->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX) ||
        (sample->enabled_modes & (1u << ZYDIS_DECODER_MODE_KNC)))
    {
        return ZYAN_TRUE;
    }
#endif
#ifdef ZYDIS_DISABLE_AVX512
    // `ZydisGetInstructionDefinition` has no EVEX table to look the tagged id up in.
    if (sample->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX)
    {
        return ZYAN_TRUE;
    }
#endif
    return ZYAN_FALSE;
}

static ZyanBool InitDecoder(const CorpusSample* sample, ZydisDecoder* decoder, char* reason)
{
    ZyanStatus status = ZydisDecoderInit(decoder, sample->machine_mode->machine_mode,
        sample->machine_mode->stack_width);
    if (!ZYAN_SUCCESS(status))
    {
        return Fail(reason, "decoder init %s", FormatZyanStatus(status));
    }
    for (ZyanUSize i = 0; i < ZYAN_ARRAY_LENGTH(DECODER_MODE_TAGS); ++i)
    {
        const ZyanU32 bit = 1u << DECODER_MODE_TAGS[i].value;
        if (sample->enabled_modes & bit)
        {
            status = ZydisDecoderEnableMode(decoder,
                (ZydisDecoderMode)DECODER_MODE_TAGS[i].value, ZYAN_TRUE);
            if (!ZYAN_SUCCESS(status))
            {
                return Fail(reason, "enable %s %s", DECODER_MODE_TAGS[i].name,
                    FormatZyanStatus(status));
            }
        }
    }
    for (ZyanUSize i = 0; i < ZYAN_ARRAY_LENGTH(DECODER_MODE_TAGS); ++i)
    {
        const ZyanU32 bit = 1u << DECODER_MODE_TAGS[i].value;
        if (sample->disabled_modes & bit)
        {
            status = ZydisDecoderEnableMode(decoder,
                (ZydisDecoderMode)DECODER_MODE_TAGS[i].value, ZYAN_FALSE);
            if (!ZYAN_SUCCESS(status))
            {
                return Fail(reason, "disable %s %s", DECODER_MODE_TAGS[i].name,
                    FormatZyanStatus(status));
            }
        }
    }
    return ZYAN_TRUE;
}

static ZyanBool CheckSample(const CorpusSample* sample, const char* path, char* reason)
{
    ZydisDecoder decoder;
    if (!InitDecoder(sample, &decoder, reason))
    {
        return ZYAN_FALSE;
    }

    ZydisDecoderContext context;
    ZYAN_MEMSET(&context, 0, sizeof(context));
    ZydisDecodedInstruction instruction;
    ZyanStatus status = ZydisDecoderDecodeInstruction(&decoder, &context, sample->bytes,
        sample->length, &instruction);
    if (!ZYAN_SUCCESS(status))
    {
        return Fail(reason, "%s", FormatZyanStatus(status));
    }

    // The registry folds definitions with identical content into one id, so the id alone cannot
    // separate a twin leaf. The map, opcode, widths and path checks below do.
    const ZydisInstructionDefinition* expected;
    ZydisGetInstructionDefinition(sample->encoding, sample->id, &expected);
    if (context.definition != (const void*)expected)
    {
        const char* mnemonic = ZydisMnemonicGetString(instruction.mnemonic);
        ZyanU16 id;
        if (FindDefinitionId(instruction.encoding, context.definition, &id))
        {
            return Fail(reason, "%s:%u %s", GetEncodingTag(instruction.encoding), (unsigned)id,
                mnemonic ? mnemonic : "?");
        }
        return Fail(reason, "%s:? %s", GetEncodingTag(instruction.encoding),
            mnemonic ? mnemonic : "?");
    }
    if (instruction.length != sample->length)
    {
        return Fail(reason, "length %u of %u bytes", (unsigned)instruction.length,
            (unsigned)sample->length);
    }
    if (instruction.opcode_map != sample->map)
    {
        return Fail(reason, "map %s", LookupValue(OPCODE_MAP_TAGS,
            ZYAN_ARRAY_LENGTH(OPCODE_MAP_TAGS), instruction.opcode_map));
    }
    if (instruction.opcode != sample->opcode)
    {
        return Fail(reason, "opcode %02X", (unsigned)instruction.opcode);
    }
    if (instruction.operand_width != sample->operand_width)
    {
        return Fail(reason, "osz %u", (unsigned)instruction.operand_width);
    }
    if (instruction.address_width != sample->address_width)
    {
        return Fail(reason, "asz %u", (unsigned)instruction.address_width);
    }

    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
    status = ZydisDecoderDecodeOperands(&decoder, &context, &instruction, operands,
        instruction.operand_count);
    if (!ZYAN_SUCCESS(status))
    {
        return Fail(reason, "operands %s", FormatZyanStatus(status));
    }

    CheckContext check_context;
    check_context.decoder = &decoder;
    check_context.instruction = &instruction;
    check_context.enabled_modes = sample->enabled_modes;
    check_context.disabled_modes = sample->disabled_modes;
    return CheckPath(&check_context, path, reason);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Files                                                                                          */
/* ============================================================================================== */

static const char* GetColumn(const char* const columns[CORPUS_COLUMN_COUNT], CorpusColumn column)
{
    return columns[column] ? columns[column] : "?";
}

static void PrintFailure(const char* file_name, ZyanUSize line_number,
    const char* const columns[CORPUS_COLUMN_COUNT], const char* reason)
{
    ZYAN_PRINTF("FAIL %s:%u %s mode=%s expect=%s:%s %s got=%s\n", file_name,
        (unsigned)line_number, GetColumn(columns, CORPUS_COLUMN_BYTES),
        GetColumn(columns, CORPUS_COLUMN_MODE), GetColumn(columns, CORPUS_COLUMN_ENCODING),
        GetColumn(columns, CORPUS_COLUMN_ID), GetColumn(columns, CORPUS_COLUMN_MNEMONIC), reason);
}

static void PrintHeaderFailure(const char* file_name)
{
    static const char* const no_columns[CORPUS_COLUMN_COUNT] = { ZYAN_NULL };
    PrintFailure(file_name, 1, no_columns, "malformed header");
}

static LineResult CheckLine(const char* file_name, ZyanUSize line_number, char* line,
    ZyanBool is_too_long)
{
    const char* columns[CORPUS_COLUMN_COUNT];
    const ZyanUSize column_count = SplitColumns(line, columns);

    char reason[CORPUS_LINE_SIZE];
    CorpusSample sample;
    ZyanBool is_valid;
    if (is_too_long)
    {
        is_valid = Fail(reason, "malformed line, longer than %d bytes", CORPUS_LINE_SIZE - 1);
    }
    else if (column_count != CORPUS_COLUMN_COUNT)
    {
        is_valid = Fail(reason, "malformed line, %u columns", (unsigned)column_count);
    }
    else if (!ParseSample(columns, &sample, reason))
    {
        is_valid = ZYAN_FALSE;
    }
    else if (IsUnsupportedByBuild(&sample))
    {
        return LINE_RESULT_SKIPPED;
    }
    else
    {
        is_valid = CheckSample(&sample, columns[CORPUS_COLUMN_PATH], reason);
    }

    if (is_valid)
    {
        return LINE_RESULT_PASSED;
    }
    PrintFailure(file_name, line_number, columns, reason);
    return LINE_RESULT_FAILED;
}

/**
 * Reads one line without its line break.
 *
 * @param   file        The file.
 * @param   line        A buffer of `CORPUS_LINE_SIZE` bytes that receives the line.
 * @param   is_too_long Receives `ZYAN_TRUE` if the line does not fit the buffer. The rest of
 *                      such a line is consumed.
 *
 * @return  `ZYAN_FALSE` at the end of the file.
 */
static ZyanBool ReadLine(FILE* file, char* line, ZyanBool* is_too_long)
{
    *is_too_long = ZYAN_FALSE;
    if (!fgets(line, CORPUS_LINE_SIZE, file))
    {
        return ZYAN_FALSE;
    }
    ZyanUSize length = ZYAN_STRLEN(line);
    if ((length > 0) && (line[length - 1] == '\n'))
    {
        line[--length] = '\0';
    }
    else if (length == CORPUS_LINE_SIZE - 1)
    {
        int c = fgetc(file);
        if ((c != EOF) && (c != '\n'))
        {
            *is_too_long = ZYAN_TRUE;
            while ((c != EOF) && (c != '\n'))
            {
                c = fgetc(file);
            }
        }
    }
    if ((length > 0) && (line[length - 1] == '\r'))
    {
        line[--length] = '\0';
    }
    return ZYAN_TRUE;
}

/**
 * Checks every sample of a corpus file and prints its summary line.
 *
 * @param   file_name   The path of the corpus file.
 *
 * @return  `ZYAN_TRUE` if the file was read completely and no line failed.
 */
static ZyanBool CheckFile(const char* file_name)
{
    FILE* file = fopen(file_name, "r");
    if (!file)
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "%s: cannot open file\n", file_name);
        return ZYAN_FALSE;
    }

    ZyanUSize passed = 0;
    ZyanUSize failed = 0;
    ZyanUSize skipped = 0;
    ZyanUSize line_number = 0;
    char line[CORPUS_LINE_SIZE];
    ZyanBool is_too_long;
    while (ReadLine(file, line, &is_too_long))
    {
        ++line_number;
        if (line_number == 1)
        {
            // A missing header would otherwise drop the first sample unchecked.
            if (is_too_long || ZYAN_STRCMP(line, CORPUS_HEADER))
            {
                PrintHeaderFailure(file_name);
                ++failed;
            }
            continue;
        }
        if ((line[0] == '\0') && !is_too_long)
        {
            continue;
        }
        switch (CheckLine(file_name, line_number, line, is_too_long))
        {
        case LINE_RESULT_PASSED:
            ++passed;
            break;
        case LINE_RESULT_FAILED:
            ++failed;
            break;
        case LINE_RESULT_SKIPPED:
            ++skipped;
            break;
        }
    }

    // An empty file has no header and must not pass with zero samples.
    if (line_number == 0)
    {
        PrintHeaderFailure(file_name);
        ++failed;
    }

    const ZyanBool has_read_error = ferror(file) != 0;
    fclose(file);
    if (has_read_error)
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "%s: read error after line %u\n", file_name,
            (unsigned)line_number);
    }

    ZYAN_PRINTF("%s: %u passed, %u failed, %u skipped\n", file_name, (unsigned)passed,
        (unsigned)failed, (unsigned)skipped);
    return !has_read_error && (failed == 0);
}

/* ---------------------------------------------------------------------------------------------- */

/* ============================================================================================== */
/* Entry point                                                                                    */
/* ============================================================================================== */

int main(int argc, char** argv)
{
    if (ZydisGetVersion() != ZYDIS_VERSION)
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "Invalid zydis version\n");
        return EXIT_FAILURE;
    }

    if (argc < 2)
    {
        ZYAN_FPRINTF(ZYAN_STDERR, "Usage: %s <file.tsv>...\n",
            (argc > 0) ? argv[0] : "ZydisCorpusCheck");
        return EXIT_FAILURE;
    }

    ZyanBool is_success = ZYAN_TRUE;
    for (int i = 1; i < argc; ++i)
    {
        if (!CheckFile(argv[i]))
        {
            is_success = ZYAN_FALSE;
        }
    }
    return is_success ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* ============================================================================================== */
