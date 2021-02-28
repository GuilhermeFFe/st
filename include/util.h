#pragma once

#include <bytebuffer.h>

/**
 * Reads file and returns NULL terminated string.
 * 
 * NOTE: Free the pointer returned by this function! It is heap allocated!
 * 
 * @param path path of file
 */
char* read_ascii_file( const char* path );


/**
 * Writes ByteBuffer's contents to a binary file.
 * 
 * @param path binary file path to be written
 * @param bb ByteBuffer to write to file
 */
void write_binary_file( const char* path, ByteBuffer* bb );