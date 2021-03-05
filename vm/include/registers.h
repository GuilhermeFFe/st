#pragma once

#include <registerid.h>

#include <stdint.h>
#include <stdlib.h>

struct _Register
{
    RegisterId id;
    uint32_t data;
};
typedef struct _Register Register;

struct _RegisterList
{
    Register registers[REGISTER_AMMOUNT];
};
typedef struct _RegisterList RegisterList;

/**
 * Starts a given RegisterList with the default values and registers
 * 
 * @param r RegisterList to initialize
 */
void register_list_start( RegisterList* r );

/**
 * Pushes value into a register in given RegisterList
 * 
 * @param r pointer to the RegisterList in which to push value
 * @param id register id to push
 * @param val value to push
 */
void register_list_push( RegisterList* r, RegisterId id, uint32_t val );

/**
 * Gets value from a register in given RegisterList
 * 
 * @param r pointer to the RegisterList in which to get value
 * @param id register id to get
 */
uint32_t register_list_get_value( RegisterList* r, RegisterId id );
