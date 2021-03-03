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


/**
 * Reads a binary file and returns its contents
 * 
 * @param path binary file path to be read
 * @returns heap allocated array with file's contents
 */
uint8_t* read_binary_file( const char* path );

/**
 * Reads 16 bit number from 8 bit buffer
 * 
 * @param buffer 8 bit number buffer
 * @param index index to start reading
 * @returns 16 bit number read from buffer
 */
uint16_t read16( uint8_t* buffer, size_t index );

/**
 * Reads 32 bit number from 8 bit buffer
 * 
 * @param buffer 8 bit number buffer
 * @param index index to start reading
 * @returns 32 bit number read from buffer
 */
uint32_t read32( uint8_t* buffer, size_t index );