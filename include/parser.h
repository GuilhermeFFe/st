#pragma once

#include <token.h>
#include <labellist.h>

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
 * Gets label from buf
 * 
 * @param ll labellist of current labels
 * @param buf buffer to be looked at
 * @returns label address
 */
uint32_t parser_get_label( LabelList* ll, char* buf, uint32_t curr_addr );

/**
 * Gets instruction code from buf
 * 
 * @param buf buffer to be looked at
 * @returns instruction code
 */
TokenInst parser_get_inst( const char* buf );

/**
 * Finds all labels defined in given source code and feeds them to list
 * 
 * @param l_list LabelList to feed with labels found on source
 * @param source source code
 */
void parser_find_labels( LabelList* l_list, const char* source );
