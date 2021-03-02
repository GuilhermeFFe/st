#include <labellist.h>

#include <string.h>

#include <stdio.h>

void label_create( Label* l, uint32_t addr, char* name )
{
    l->addr = addr;
    strcpy( l->name, name );
}

void label_list_initialize( LabelList* list, size_t size )
{
    list->labels = (Label*) malloc( sizeof( Label ) * size );
    list->ptr = 0;
    list->size = size;
}

void label_list_add( LabelList* list, Label lab )
{
    if( list->ptr >= list->size )
    {
        list->size *= 2;
        list->labels = (Label*) realloc( list->labels, sizeof( Label ) * list->size );
    }

    Label* l = &list->labels[list->ptr++];
    label_create( l, lab.addr, lab.name );
}

Label* label_list_get( const LabelList* list, const char* name )
{
    for( size_t i = 0; i < list->ptr; i++ )
    {
        if( strcmp( list->labels[i].name, name ) == 0 )
        {
            return &list->labels[i];
        }
    }
    return NULL;
}

void label_list_destroy( LabelList* list )
{
    free( list->labels );
}