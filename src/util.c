#include <util.h>

#include <stdio.h>
#include <stdlib.h>

char* read_ascii_file( const char* path )
{
    // Open file
    FILE* file = fopen( path, "r" );
    if( !file )
    {
        printf( "Could not open file '%s'\n", path );
        return NULL;
    }

    // Get the file size
    fseek( file, 0, SEEK_END );
    int size = ftell( file );
    fseek( file, 0, SEEK_SET );

    // Read file
    char* buf = (char*) malloc( sizeof( char ) * ( size + 1 ) );
    if( !buf )
    {
        printf( "Memory allocation failed!\n" );
        return NULL;
    }
    fread( buf, 1, size, file );
    buf[ size ] = 0;
    fclose( file );

    // Return file's content
    return buf;
}