#include <inttypes.h>
#include <Zycore/Format.h>
#include <Zycore/LibC.h>
#include <Zydis/Zydis.h>
#include <Zydis/Parser.h>

int main()
{
    ZydisParser parser = { 0 };
    ZydisParserInit(&parser,
                    ZYDIS_PARSER_TEXT_STREAM_ENCODING_ASCII,
                    ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_NONE,
                    ZYDIS_PARSER_SYNTAX_INTEL);
    ZyanI8 text[] = { "XACQUIRE LOCK MOV EAX, [EAX + ECX * 8]" };
    ZyanU32 length = sizeof(text);
    ZydisParserParseBuffer(&parser,
                           text,
                           length);

    getchar();
    return 0;
}