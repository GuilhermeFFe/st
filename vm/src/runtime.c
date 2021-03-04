#include <runtime.h>
#include <opcode.h>

#include <stdio.h>

void runtime_start( Runtime* runtime )
{
    runtime->cp = -1;
    runtime->sp = -1;
    runtime->ip = read32( runtime->code, 0 );
    runtime->exit = 0;
    runtime->running = true;
    register_list_start( &runtime->register_list );

    // TODO: READ VALUE FROM REGISTER

    while( runtime->running )
    {
        switch( (Opcode)runtime->code[runtime->ip++] )
        {
            case OP_PUSH_CONST:
                push32( runtime, read32( runtime->code, runtime->ip ) );
                runtime->ip += 4;
                break;
            case OP_PUSH_REG_VAL: ;
                RegisterId rid = runtime->code[ runtime->ip++ ];
                push32( runtime, register_list_get_value( &runtime->register_list, rid ) );
                break;
            case OP_ADD_STACK:
                push32( runtime, pop32( runtime ) + pop32( runtime ) );
                break;
            case OP_MULT_STACK:
                push32( runtime, pop32( runtime ) * pop32( runtime ) );
                break;
            case OP_CALL:
                push_addr( runtime, runtime->ip+4 );
                // fall through
            case OP_JMP: ;
                uint32_t addr = read32( runtime->code, runtime->ip );
                runtime->ip = addr;
                break;
            case OP_RET: ;
                runtime->ip = pop_addr( runtime );
                break;
            case OP_DIV_STACK: ;
                uint32_t a = pop32( runtime );
                uint32_t b = pop32( runtime );
                if( b == 0 )
                {
                    runtime->message = "Illegal division by zero\n";
                    runtime->status = RUNTIME_ERROR;
                    runtime->running = false;
                    runtime->exit = -1;
                }
                else
                {
                    push32( runtime, a / b );
                }
                break;
            case OP_SUB_STACK:
            // TODO: implement negative numbers
                push32( runtime, pop32( runtime ) - pop32( runtime ) );
                break;
            case OP_PUSHR_CONST: ;
                RegisterId id = runtime->code[runtime->ip++];
                register_list_push( &runtime->register_list, id, read32( runtime->code, runtime->ip ) );
                runtime->ip += 4;
                break;
            case OP_PUSHR_REG_VAL: ;
                RegisterId dest = runtime->code[runtime->ip++];
                RegisterId orig = runtime->code[runtime->ip++];
                uint32_t val = register_list_get_value( &runtime->register_list, orig );
                register_list_push( &runtime->register_list, dest, val );
                break;
            case OP_HLT:
                runtime->exit = pop8( runtime );
                runtime->status = RUNTIME_SUCCESS;
                runtime->running = false;
                break;
            case OP_NOP:
                break;
        }
    }
}

void push_addr( Runtime* r, uint32_t addr )
{
    r->call_stack[++r->cp] = addr;
}

uint32_t pop_addr( Runtime* r )
{
    return r->call_stack[r->cp--];
}

void push8( Runtime* r, uint8_t data )
{
    r->stack[++r->sp] = data;
}

void push16( Runtime* r, uint16_t data )
{
    push8( r, ( data & 0xFF00 ) >> 8 );
    push8( r, ( data & 0x00FF ) );
}

void push32( Runtime* r, uint32_t data )
{
    push8( r, ( data & 0xFF000000 ) >> 24 );
    push8( r, ( data & 0x00FF0000 ) >> 16 );
    push8( r, ( data & 0x0000FF00 ) >> 8 );
    push8( r, ( data & 0x000000FF ) );
}

uint8_t pop8( Runtime* r )
{
    return r->stack[r->sp--];
}

uint16_t pop16( Runtime* r )
{
    uint8_t b = pop8( r );
    uint8_t a = pop8( r );
    return a << 8 | b;
}

uint32_t pop32( Runtime* r )
{
    uint8_t d = pop8( r );
    uint8_t c = pop8( r );
    uint8_t b = pop8( r );
    uint8_t a = pop8( r );
    return a << 24 | b << 16 | c << 8 | d;
}

