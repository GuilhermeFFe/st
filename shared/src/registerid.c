#include <registerid.h>

char* register_id_str( RegisterId id )
{
#define to_str_case( _case, _ret ) case _case: return _ret;

    switch( id )
    {
        to_str_case( REG_A, "a" )
        to_str_case( REG_B, "b" )
        default:
            return "";
    }

#undef to_str_case
}