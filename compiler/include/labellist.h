#pragma once

#include <stdlib.h>
#include <stdint.h>

struct _Label
{
    char name[128];
    uint32_t addr;
};
typedef struct _Label Label;

/**
 * Initializes given label with data
 * 
 * @param l label to initialize
 * @param addr label's address
 * @param name label's name
 */
void label_create( Label* l, uint32_t addr, char* name );

struct _LabelList
{
    Label* labels;
    size_t size;
    size_t ptr;
};
typedef struct _LabelList LabelList;

/**
 * Creates a label list
 * 
 * NOTE: the list inside is heap allocated, remember to destroy it later
 * 
 * @param size initial size
 * @param list list to initialize
 */
void label_list_initialize( LabelList* list, size_t size );

/**
 * Adds Label to given LabelList
 * 
 * NOTE: this will copy the label
 * 
 * @param list LabelList in which the label will be added
 * @param lab Label to add
 */
void label_list_add( LabelList* list, Label lab );

/**
 * Gets a label in list from given name
 * 
 * NOTE: may return null
 * 
 * @param list LabelList in which to search for name
 * @param name Label name to search for
 */
Label* label_list_get( const LabelList* list, const char* name );

/**
 * Destroys given LabelList
 * 
 * @param list LabelList to destroy
 */
void label_list_destroy( LabelList* list );