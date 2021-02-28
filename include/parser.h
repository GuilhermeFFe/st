#pragma once

#include <token.h>
#include <stdint.h>

enum _ParserStatus
{
    PARSER_SUCCESS,
    PARSER_SYNTAX_ERROR
};
typedef enum _ParserStatus ParserStatus;

/**
 * Parses source code into a list of tokens
 * 
 * @param list TokenList structure to be filled with Tokens
 * @param source source code as string
 */ 
ParserStatus parser_start( TokenList* list, const char* source );

/**
 * Gets number constant from buf
 * 
 * @param buf buffer to be looked at
 * @returns number constant
 */ 
uint32_t parser_get_number( const char* buf );

/**
 * Gets instruction code from buf
 * 
 * @param buf buffer to be looked at
 * @returns instruction code
 */
TokenInst parser_get_inst( const char* buf );
