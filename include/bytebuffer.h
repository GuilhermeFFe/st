#pragma once

#include <stdlib.h>
#include <stdint.h>

struct _ByteBuffer
{
    uint8_t* buffer;
    size_t size;
    size_t ptr;
};
typedef struct _ByteBuffer ByteBuffer;

/**
 * Create ByteBuffer from given initial size
 * 
 * NOTE: Remember to destroy, using byte_buffer_destroy
 * 
 * @param size initial size to allocate memory to buffer
 * @returns allocated ByteBuffer pointer
 */
ByteBuffer* byte_buffer_create( size_t size );

/**
 * Writes 8 bit number to given ByteBuffer
 * 
 * @param bb ByteBuffer to write to
 * @param data 8bit number to write
 */
void byte_buffer_write8( ByteBuffer* bb, uint8_t data );

/**
 * Writes 16 bit number to given ByteBuffer
 * 
 * @param bb ByteBuffer to write to
 * @param data 16bit number to write
 */
void byte_buffer_write16( ByteBuffer* bb, uint16_t data );

/**
 * Writes 32 bit number to given ByteBuffer
 * 
 * @param bb ByteBuffer to write to
 * @param data 32bit number to write
 */
void byte_buffer_write32( ByteBuffer* bb, uint32_t data );

/**
 * Destroys given ByteBuffer
 * 
 * @param bb ByteBuffer to destroy and free
 */
void byte_buffer_destroy( ByteBuffer* bb );