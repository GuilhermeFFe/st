#pragma once

/**
 * Reads file and returns NULL terminated string.
 * 
 * NOTE: Free the pointer returned by this function! It is heap allocated!
 * 
 * @param path path of file
 */
char* read_ascii_file( const char* path );