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
    uint32_t curr_addr = 0;
    LabelList l_list;
    label_list_initialize( &l_list, 1 );

    parser_find_labels( &l_list, source );

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

        switch( lex[0] )
        {
            case '$':;
                uint32_t addr = parser_get_label( &l_list, lex, curr_addr );
                if( addr == 0xFFFF )
                {
                    printf( "Syntax error: undefined label '%s'\n", lex );
                    return PARSER_SYNTAX_ERROR;
                }
                if( addr != curr_addr )
                {
                    token_create( &token, NUMBER, addr, line );
                    token_list_add( list, token );
                    curr_addr += 4;
                }
                break;

            case '#':;
                uint32_t num = parser_get_number( lex );
                token_create( &token, NUMBER, num, line );
                token_list_add( list, token );
                curr_addr += 4;
                break;
            default:;
                int8_t inst = parser_get_inst( lex );
                if( inst >= 0 )
                {
                    token_create( &token, INST, inst, line );
                    token_list_add( list, token );
                    curr_addr++;
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

    label_list_destroy( &l_list );
    return PARSER_SUCCESS;
}

void parser_find_labels( LabelList* l_list, const char* source )
{
    char lex[256];
    int lexi = 0;
    int src_idx = 0;
    uint32_t curr_addr = 0;

    while( 1 )
    {
        while( source[src_idx] != ' ' && source[src_idx] != '\n' && source[src_idx] != '\0' )
        {
            lex[lexi++] = source[src_idx++];
        }
        lex[lexi] = '\0';

        switch( lex[0] )
        {
            case '$':;
                if( lex[1] != '$' )
                {
                    Label l;
                    l.addr = curr_addr;
                    strcpy( l.name, &lex[1] );
                    label_list_add( l_list, l );
                }
                else
                {
                    curr_addr += 4;
                }
                break;
            case '#':
                curr_addr += 4;
                break;
            default:
                curr_addr++;
                break;
        }
        if( source[src_idx] == '\0' )
        {
            break;
        }

        lexi = 0;
        src_idx++;
    }
}

uint32_t parser_get_number( const char* buf )
{
    long num = atoi( &buf[1] );
    return num < UINT32_MAX ? num : 0;
}

uint32_t parser_get_label( LabelList* ll, char* buf, uint32_t curr_addr )
{
    char* name = NULL;
    if( buf[1] == '$' ) // Jump to label
    {
        name = &buf[2];
        Label* l;
        if( ( l = label_list_get( ll, name ) ) != NULL )
        {
            return l->addr;
        }
        return 0xFFFF;
    }
    else
    {
        return curr_addr;
    }
}

TokenInst parser_get_inst( const char* buf )
{
#define CMP( _if, _inst ) _if( strcmp( buf, token_inst_str( _inst ) ) == 0 ) return _inst;

    CMP( if, PUSH )
    CMP( else if, ADD )
    CMP( else if, MULT )
    CMP( else if, HLT )
    CMP( else if, DIV )
    CMP( else if, SUB )
    CMP( else if, JMP )
    else
    {
        return NO_INST;
    }
    

#undef CMP
}
