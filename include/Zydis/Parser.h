#ifndef ZYDIS_PARSER_H
#define ZYDIS_PARSER_H

#include "Zydis/Zydis.h"
#include "Zycore/Zycore.h"
#include "Zycore/LibC.h"

#include "../src/Generated/EnumMnemonic.inc"

typedef enum _ZydisParserStatus
{
    ZYDIS_PARSER_STATUS_SUCCESS,
    ZYDIS_PARSER_STATUS_INVALID_PARAMETER,
    ZYDIS_PARSER_STATUS_UNSUPPORTED_TEXT_STREAM_ENCODING,
    ZYDIS_PARSER_STATUS_UNSUPPORTED_TEXT_STREAM_ENDIANESS,
    ZYDIS_PARSER_STATUS_UNSUPPORTED_SYNTAX,
    ZYDIS_PARSER_STATUS_UNKNOWN_CHARACTER_ENCOUNTERED,
    ZYDIS_PARSER_STATUS_SEGMENT_OVERRIDE_TOO_EARLY,
    ZYDIS_PARSER_STATUS_UNKNOWN_MNEMONIC
} ZydisParserStatus;

/*
    Text Stream
*/

typedef enum _ZydisParserTextStreamEncoding
{
    ZYDIS_PARSER_TEXT_STREAM_ENCODING_NONE,
    ZYDIS_PARSER_TEXT_STREAM_ENCODING_ASCII,
    // Unsupported
    ZYDIS_PARSER_TEXT_STREAM_ENCODING_UTF8,
    ZYDIS_PARSER_TEXT_STREAM_ENCODING_UTF16,
    ZYDIS_PARSER_TEXT_STREAM_ENCODING_UTF32,
    // Maximum
    ZYDIS_PARSER_TEXT_STREAM_ENCODING_MAXIMUM = ZYDIS_PARSER_TEXT_STREAM_ENCODING_UTF32
} ZydisParserTextStreamEncoding;

typedef enum _ZydisParserTextStreamEndianess
{
    ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_NONE,
    // Unsupported
    ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_LITTLE,
    ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_BIG,
    // Maximum
    ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_MAXIMUM = ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_BIG
} ZydisParserTextStreamEndianess;

typedef ZydisParserStatus(* f_ZydisParserTextStreamPrepare)(struct _ZydisParserTextStream *);

typedef ZyanU32(* f_ZydisParserTextStreamCompare)(struct _ZydisParserTextStream *,
                                                  ZyanU32,
                                                  ZyanVoidPointer);

typedef ZyanU32(* f_ZydisParserTextStreamRead)(struct _ZydisParserTextStream *,
                                               ZyanU32);

typedef ZyanU32(* f_ZydisParserTextStreamWrite)(struct _ZydisParserTextStream *,
                                                ZyanU32,
                                                ZyanU32);

typedef ZyanU32(* f_ZydisParserTextStreamAdvance)(struct _ZydisParserTextStream *,
                                                  ZyanU32);

ZydisParserStatus ZydisParserTextStreamPrepareASCII(struct _ZydisParserTextStream * text_stream);

ZyanU32 ZydisParserTextStreamCompareASCII(struct _ZydisParserTextStream * text_stream,
                                          ZyanU32 text_stream_start_index,
                                          ZyanVoidPointer ascii_buffer);

ZyanU32 ZydisParserTextStreamReadASCII(struct _ZydisParserTextStream * text_stream,
                                       ZyanU32 index);

ZyanBool ZydisParserTextStreamWriteASCII(struct _ZydisParserTextStream * text_stream,
                                         ZyanU32 index,
                                         ZyanU32 value);

ZyanBool ZydisParserTextStreamAdvanceASCII(struct _ZydisParserTextStream * text_stream,
                                           ZyanU32 count);

typedef struct _ZydisParserTextStream
{
    ZyanVoidPointer buffer;
    ZyanU32 length;
    ZydisParserTextStreamEncoding encoding;
    ZydisParserTextStreamEndianess endianess;
    f_ZydisParserTextStreamPrepare prepare;
    f_ZydisParserTextStreamCompare compare;
    f_ZydisParserTextStreamRead read;
    f_ZydisParserTextStreamWrite write;
    f_ZydisParserTextStreamAdvance advance;
} ZydisParserTextStream;

/*
    Parser
*/

typedef enum _ZydisParserSyntax
{
    ZYDIS_PARSER_SYNTAX_INTEL,
    // Unsupported
    ZYDIS_PARSER_SYNTAX_ATT
} ZydisParserSyntax;

typedef struct _ZydisParser
{
    ZydisParserTextStream text_stream;
    ZydisParserSyntax syntax;
    ZydisEncoderRequest encoder_request;
} ZydisParser;

ZydisParserStatus ZydisParserInit(ZydisParser * parser,
                                  ZydisParserTextStreamEncoding text_stream_encoding,
                                  ZydisParserTextStreamEndianess text_stream_endianess,
                                  ZydisParserSyntax syntax);


typedef struct _ZydisParserOptionalPrefixInformation
{
    ZydisShortString text;
    ZyanU8 index;
    ZyanBool is_segment_override;
} ZydisParserOptionalPrefixInformation;

static ZydisParserOptionalPrefixInformation ZydisParserOptionalPrefixInformationTable[] =
{
    { ZYDIS_MAKE_SHORTSTRING("branch taken"), 35, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("branchtaken"), 35, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("bt"), 35, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("branch not taken"), 34, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("branchnottaken"), 34, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("bnt"), 34, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("bnd"), 31, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("cs"), 37, ZYAN_TRUE },
    { ZYDIS_MAKE_SHORTSTRING("ds"), 39, ZYAN_TRUE },
    { ZYDIS_MAKE_SHORTSTRING("es"), 40, ZYAN_TRUE },
    { ZYDIS_MAKE_SHORTSTRING("fs"), 41, ZYAN_TRUE },
    { ZYDIS_MAKE_SHORTSTRING("gs"), 42, ZYAN_TRUE },
    { ZYDIS_MAKE_SHORTSTRING("lock"), 27, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("not taken"), 34, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("nottaken"), 34, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("no track"), 36, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("notrack"), 36, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("nt"), 36, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("rep"), 28, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("repe"), 29, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("repz"), 29, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("repne"), 30, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("repnz"), 30, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("ss"), 38, ZYAN_TRUE },
    { ZYDIS_MAKE_SHORTSTRING("taken"), 35, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("xacquire"), 32, ZYAN_FALSE },
    { ZYDIS_MAKE_SHORTSTRING("xrelease"), 33, ZYAN_FALSE }
};

#define ZYDIS_PARSER_OPTIONAL_PREFIX_MAXIMUM 26

ZydisParserStatus ZydisParserParseOptionalPrefix(ZydisParser * parser);

#define ZYDIS_PARSER_MNEMONIC_MAXIMUM ZYAN_ARRAY_LENGTH(STR_MNEMONIC)

ZydisParserStatus ZydisParserParseMnemonic(ZydisParser * parser);

ZydisParserStatus ZydisParserParseBuffer(ZydisParser * parser,
                                         ZyanVoidPointer buffer,
                                         ZyanU32 length);

#endif