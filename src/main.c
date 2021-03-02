#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <util.h>
#include <parser.h>
#include <token.h>
#include <compiler.h>
#include <runtime.h>

// staple compile file.stvm

int main( int argc, char** argv )
{
    if( argc < 3 )
    {
        printf( "Too few arguments!\n" );
        return 1;
    }
    
    // Compile
    if( strcmp( argv[1], "compile" ) == 0 )
    {
        char* source = read_ascii_file( argv[2] );
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
    }
    else if( strcmp( argv[1], "run" ) == 0 )
    {
        uint8_t* buffer = read_binary_file( argv[2] );

        Runtime runtime;
        runtime.code = buffer;
        runtime_start( &runtime );

        if( runtime.status == RUNTIME_ERROR )
        {
            return 1;
        }

        free( buffer );

        return runtime.exit;
    }


    return -1;
}