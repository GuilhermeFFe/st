#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <util.h>
#include <runtime.h>

// staple compile file.stvm

int main( int argc, char** argv )
{
    if( argc < 2 )
    {
        printf( "Too few arguments!\n" );
        return 1;
    }

    uint8_t* buffer = read_binary_file( argv[1] );

    Runtime runtime;
    runtime.code = buffer;
    runtime_start( &runtime );

    if( runtime.status != RUNTIME_SUCCESS )
    {
        printf( runtime.message );
        return runtime.exit;
    }

    free( buffer );

    return runtime.exit;
}
