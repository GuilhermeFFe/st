#include <registers.h>

static Register* register_list_get_register( RegisterList* r, RegisterId id )
{
    for( size_t i = 0; i < REGISTER_AMMOUNT; i++ )
    {
        if( r->registers[i].id == id )
        {
            return &r->registers[i];
        }
    }
    return NULL;
}

void register_list_start( RegisterList* r )
{
    for( size_t i = 0; i < REGISTER_AMMOUNT; i++ )
    {
        r->registers[i].data = 0x0000;
        r->registers[i].id = (RegisterId)i;
    }
}

void register_list_push( RegisterList* r, RegisterId id, uint32_t val )
{
    register_list_get_register( r, id )->data = val;
}

uint32_t register_list_get_value( RegisterList* r, RegisterId id )
{
    return register_list_get_register( r, id )->data;
}