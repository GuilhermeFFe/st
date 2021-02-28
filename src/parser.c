#include <parser.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

ParserStatus parser_start( TokenList* list, const char* source )
{
    char lex[256];
    int lexi = 0;
    int src_idx = 0;
    int line = 1;

    while( 1 )
    {
        // memset( lex, '\0', 256 );

        while( source[src_idx] != ' ' && source[src_idx] != '\n' && source[src_idx] != '\0' )
        {
            lex[lexi++] = source[src_idx++];
        }
        lex[lexi] = '\0';

        // TODO: linhas vazias
        // TODO: tabs

        Token token;

        // Numerical constant
        if( lex[0] == '#' )
        {
            int num = parser_get_number( lex );
            token_create( &token, NUMBER, num, line );
            token_list_add( list, token );
        }
        else // Must be an instruction
        {
            int inst = parser_get_inst( lex );
            if( inst >= 0 )
            {
                token_create( &token, INST, inst, line );
                token_list_add( list, token );
            }
            else
            {
                printf( "Syntax error: no such instruction '%s'\n", lex );
                return PARSER_SYNTAX_ERROR;
            }
        }

        if( source[src_idx] == '\n' )
        {
            line++;
        }
        else if( source[src_idx] == '\0' )
        {
            break;
        }

        lexi = 0;
        src_idx++;
    }
    return PARSER_SUCCESS;
}

uint32_t parser_get_number( const char* buf )
{
    long num = atoi( &buf[1] );
    return num < UINT32_MAX ? num : 0;
}

TokenInst parser_get_inst( const char* buf )
{
#define CMP( _if, _inst ) _if( strcmp( buf, token_inst_str( _inst ) ) == 0 ) return _inst;

    CMP( if, PUSH )
    CMP( else if, ADD )
    CMP( else if, HLT )
    else
    {
        return NO_INST;
    }
    

#undef CMP
}
