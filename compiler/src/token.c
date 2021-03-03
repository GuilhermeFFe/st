#include <token.h>

void token_create( Token* tok, TokenType type, int data, int line )
{
    tok->type = type;
    tok->data = data;
    tok->line = line;
}

// void token_destroy( Token* tok )
// {
//     // free( tok );
// }

void token_list_initialize( TokenList* list, size_t size )
{
    list->data = (Token*) malloc( sizeof( Token ) * size );
    list->ptr = 0;
    list->size = size;
}

void token_list_add( TokenList* list, Token tok )
{
    if( list->ptr >= list->size )
    {
        list->size *= 2;
        list->data = (Token*) realloc( list->data, sizeof(Token) * list->size );
    }

    Token* t = &list->data[list->ptr++];
    token_create( t, tok.type, tok.data, tok.line );
}

Token* token_list_get( const TokenList* list, size_t index )
{
    return &list->data[index];
}

void token_list_destroy( TokenList* list )
{
    // for( size_t i = 0; i < list->ptr; i++ )
    // {
    //     token_destroy( &list->data[i] );
    // }
    free( list->data );
}

char* token_inst_str( const TokenInst tinst )
{
#define to_str_case( _case, _ret ) case _case: return _ret;

    switch( tinst )
    {
        to_str_case( PUSH, "push" )
        to_str_case( ADD, "add" )
        to_str_case( MULT, "mult" )
        to_str_case( HLT, "hlt" )
        to_str_case( DIV, "div" )
        to_str_case( SUB, "sub" )
        to_str_case( JMP, "jmp" )
        to_str_case( CALL, "call" )
        to_str_case( RET, "ret" )
        case NO_INST:
        default:
            return "";
    }

#undef to_str_case
}