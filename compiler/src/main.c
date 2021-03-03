#include <stdio.h>

#include <util.h>

#include <parser.h>
#include <token.h>
#include <compiler.h>

int main( int argc, char** argv )
{
    if( argc < 2 )
    {
        printf( "Too few arguments!\n" );
        return 1;
    }

    char* source = read_ascii_file( argv[1] );
    TokenList tokens;
    token_list_initialize( &tokens, 1 );
    ParserStatus ps = parser_start( &tokens, source );

    if( ps != PARSER_SUCCESS )
    {
        return 1;
    }

    Compiler comp;
    comp.tokens = &tokens;
    compiler_start( &comp );
    if( comp.status != COMPILER_SUCCESS )
    {
        return 1;
    }

    write_binary_file( "out.stbc", comp.bytecode );

    compiler_destroy( &comp );
    free( source );

    return 0;
}
