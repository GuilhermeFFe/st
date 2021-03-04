#pragma once

enum _RegisterId
{
    REG_A       = 0x00,
    REG_B       = 0x01,
    NO_REG      = 0xFF
};
typedef enum _RegisterId RegisterId;

/**
 * Converts given RegisterId to string
 * 
 * @param id id to convert
 */
char* register_id_str( RegisterId id );