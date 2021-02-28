#include <token.h>

Token* token_create( TokenType type, int data, int line )
{
    Token* tok = (Token*) malloc( sizeof( Token ) ); // TODO: remove
    tok->type = type;
    tok->data = data;
    tok->line = line;

    return tok;
}

void token_destroy( Token* tok )
{
    free( tok );
}

TokenList* token_list_create( TokenList* list, size_t size )
{
    list->data = (Token**) malloc( sizeof( Token* ) * size );
    list->ptr = 0;
    list->size = size;
}

void token_list_add( TokenList* list, Token* tok )
{
    if( list->ptr >= list->size )
    {
        list->size *= 2;
        list->data = (Token**) realloc( list->data, sizeof(Token*) * list->size );
    }

    list->data[list->ptr++] = tok;
}

Token* token_list_get( const TokenList* list, int index )
{
    return list->data[index];
}

void token_list_destroy( TokenList* list )
{
    for( int i = 0; i < list->ptr; i++ )
    {
        free( list->data[i] );
    }
    free( list->data );
}

char* token_inst_str( const TokenInst tinst )
{
#define to_str_case( _case, _ret ) case _case: return _ret;

    switch( tinst )
    {
        to_str_case( PUSH, "push" )
        to_str_case( ADD, "add" )
        to_str_case( HLT, "hlt" )
    }

#undef to_str_case
}