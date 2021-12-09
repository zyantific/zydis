#include "Parser.h"

/*
    Text Stream
*/

ZydisParserStatus ZydisParserTextStreamPrepareASCII(struct _ZydisParserTextStream * text_stream)
{
    // To prepare the buffer, all spaces are removed and all
    // letters are converted to lower-case to ease parsing.
    //
    // There is a read index that goes through each character
    // in the original buffer, and when a non-space is encountered,
    // it is written to a separate write index, and at the end a
    // NULL terminator is appended and the length of the text
    // is updated.
    ZyanU8 * pointer = (ZyanU8 *)text_stream->buffer;
    ZyanU32 read_index = (ZyanU32)ZYAN_NULL,
        write_index = (ZyanU32)ZYAN_NULL;

    // Go through each letter in the text
    for (ZyanU32 i = 0; i < text_stream->length; ++i)
    {
        ZyanU8 current_character = pointer[read_index];
        // Check if the current character is invalid ASCII
        if (0x80 & current_character)
        {
            return ZYDIS_PARSER_STATUS_UNKNOWN_CHARACTER_ENCOUNTERED;
        }

        // If the current leter is not a space
        if (' ' != current_character)
        {
            // Check if it is upper-case, and if so, make it lower-case
            if ('A' <= current_character && 'Z' >= current_character)
            {
                current_character |= ' ';
            }
            // Store the current character
            pointer[write_index++] = current_character;
        }
        ++read_index;
    }

    // Append NULL terminator at the last position
    pointer[write_index] = '\0';
    // Update length, not including NULL terminator
    text_stream->length = write_index - 1;
    return ZYDIS_PARSER_STATUS_SUCCESS;
}

ZyanU32 ZydisParserTextStreamCompareASCII(struct _ZydisParserTextStream * text_stream,
                                          const ZyanU32 text_stream_start_index,
                                          const ZyanVoidPointer ascii_buffer)
{
    return ZYAN_STRCMP((const char *)text_stream->buffer + text_stream_start_index,
                       (const char *)ascii_buffer);
}

ZyanU32 ZydisParserTextStreamReadASCII(struct _ZydisParserTextStream * text_stream,
                                       ZyanU32 index)
{
    if (index > text_stream->length)
    {
        return (ZyanU32)ZYAN_NULL;
    }

    return ((ZyanU8 *)text_stream->buffer)[index];
}

ZyanBool ZydisParserTextStreamWriteASCII(struct _ZydisParserTextStream * text_stream,
                                         ZyanU32 index,
                                         ZyanU32 value)
{
    if (text_stream->length < index)
    {
        return ZYAN_FALSE;
    }

    ((ZyanU8 *)text_stream->buffer)[index] = (ZyanU8)value;

    return ZYAN_TRUE;
}

ZyanBool ZydisParserTextStreamAdvanceASCII(struct _ZydisParserTextStream * text_stream,
                                           ZyanU32 count)
{
    if (text_stream->length < count)
    {
        return ZYAN_FALSE;
    }

    text_stream->buffer += count;
    text_stream->length -= count;

    return ZYAN_TRUE;
}

/*
    Parser
*/

ZydisParserStatus ZydisParserInit(ZydisParser * parser,
                                  ZydisParserTextStreamEncoding text_stream_encoding,
                                  ZydisParserTextStreamEndianess text_stream_endianess,
                                  ZydisParserSyntax syntax)
{
    if (!parser
        || !text_stream_encoding
        || ZYDIS_PARSER_TEXT_STREAM_ENCODING_MAXIMUM < text_stream_encoding
        || ZYDIS_PARSER_TEXT_STREAM_ENDIANESS_MAXIMUM < text_stream_endianess)
    {
        return ZYDIS_PARSER_STATUS_INVALID_PARAMETER;
    }
    parser->text_stream.encoding = text_stream_encoding;
    parser->text_stream.endianess = text_stream_endianess;
    if (ZYDIS_PARSER_SYNTAX_INTEL != syntax)
    {
        return ZYDIS_PARSER_STATUS_UNSUPPORTED_SYNTAX;
    }
    parser->syntax = syntax;
    switch (parser->text_stream.encoding)
    {
        case ZYDIS_PARSER_TEXT_STREAM_ENCODING_ASCII:
            parser->text_stream.prepare = ZydisParserTextStreamPrepareASCII;
            parser->text_stream.compare = ZydisParserTextStreamCompareASCII;
            parser->text_stream.read = ZydisParserTextStreamReadASCII;
            parser->text_stream.write = ZydisParserTextStreamWriteASCII;
            parser->text_stream.advance = ZydisParserTextStreamAdvanceASCII;
            break;
        default:
            return ZYDIS_PARSER_STATUS_UNSUPPORTED_TEXT_STREAM_ENCODING;
    }
    return ZYDIS_PARSER_STATUS_SUCCESS;
}


ZydisParserStatus ZydisParserParseOptionalPrefix(ZydisParser * parser)
{
    for (ZyanU32 i = 0; i < parser->text_stream.length;)
    {
        ZydisParserOptionalPrefixInformation * current = ZYAN_NULL;
        ZyanBool found_optional_prefix = ZYAN_FALSE;

        for (ZyanU8 j = 0; j <= ZYDIS_PARSER_OPTIONAL_PREFIX_MAXIMUM; ++j)
        {
            current = &ZydisParserOptionalPrefixInformationTable[j];

            // Temporarily place a NULL terminator where it should end
            ZyanU8 character_save = parser->text_stream.read(&parser->text_stream,
                                                             i + current->text.size);
            parser->text_stream.write(&parser->text_stream,
                                      i + current->text.size,
                                      (ZyanU32)ZYAN_NULL);

            // Check if the current optional prefix is a match
            if (!parser->text_stream.compare(&parser->text_stream,
                                             i,
                                             (ZyanVoidPointer)current->text.data))
            {
                found_optional_prefix = ZYAN_TRUE;
            }

            // Restore previous character
            parser->text_stream.write(&parser->text_stream,
                                      i + current->text.size,
                                      character_save);

            // If an optional prefix was found, exit
            if (found_optional_prefix)
            {
                break;
            }
        }
        // If no optional prefix was found, there are no valid optional
        // prefixes to parse, so exit
        if (!found_optional_prefix)
        {
            return ZYDIS_PARSER_STATUS_SUCCESS;
        }
        // If a segment override was found, it is an error
        if (current->is_segment_override)
        {
            return ZYDIS_PARSER_STATUS_SEGMENT_OVERRIDE_TOO_EARLY;
        }

        // Patch the attribute of the current optional prefix
        parser->encoder_request.prefixes |= (ZyanU64)0x1 << current->index;
        // Reset index
        i = 0;
        // Update string to skip current optional prefix
        parser->text_stream.advance(&parser->text_stream,
                                    current->text.size);
    }

    return ZYDIS_PARSER_STATUS_SUCCESS;
}

ZydisParserStatus ZydisParserParseMnemonic(ZydisParser * parser)
{
    ZyanBool found_mnemonic = ZYAN_FALSE;
    ZyanU32 mnemonic_index = ZYAN_NULL;
    // Try to find a valid mnemonic
    for (ZyanU32 i = 0; i < ZYDIS_PARSER_MNEMONIC_MAXIMUM; ++i)
    {
        ZydisShortString * current = &STR_MNEMONIC[i];
        
        // Temporarily place a NULL terminator where it should end
        ZyanU8 character_save = parser->text_stream.read(&parser->text_stream,
                                                         current->size);

        parser->text_stream.write(&parser->text_stream,
                                  current->size,
                                  (ZyanU32)ZYAN_NULL);

        // Check if the current optional prefix is a match
        if (!parser->text_stream.compare(&parser->text_stream,
                                         (ZyanU32)ZYAN_NULL,
                                         (ZyanVoidPointer)current->data))
        {
            found_mnemonic = ZYAN_TRUE;
            mnemonic_index = i;
            break;
        }

        // Restore previous character
        parser->text_stream.write(&parser->text_stream,
                                  current->size,
                                  character_save);
    }
    
    // If a mnemonic was not found
    if (!found_mnemonic)
    {
        return ZYDIS_PARSER_STATUS_UNKNOWN_MNEMONIC;
    }
    
    // Store mnemonic
    parser->encoder_request.mnemonic = mnemonic_index;

    return ZYDIS_PARSER_STATUS_SUCCESS;
}

ZydisParserStatus ZydisParserParseBuffer(ZydisParser * parser,
                                         ZyanVoidPointer buffer,
                                         ZyanU32 length)
{
    ZydisParserStatus last_status = ZYDIS_PARSER_STATUS_SUCCESS;

    parser->text_stream.buffer = buffer;
    parser->text_stream.length = length;
    
    last_status = parser->text_stream.prepare(&parser->text_stream);
    if (ZYDIS_PARSER_STATUS_SUCCESS != last_status)
    {
        return last_status;
    }

    last_status = ZydisParserParseOptionalPrefix(parser);
    if (ZYDIS_PARSER_STATUS_SUCCESS != last_status)
    {
        return last_status;
    }

    last_status = ZydisParserParseMnemonic(parser);
    if (ZYDIS_PARSER_STATUS_SUCCESS != last_status)
    {
        return last_status;
    }

    return ZYDIS_PARSER_STATUS_SUCCESS;
}