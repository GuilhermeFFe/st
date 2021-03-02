#include <compiler.h>
#include <opcode.h>

#include <stdio.h>

void compiler_start( Compiler* compiler )
{
    compiler->bytecode = byte_buffer_create( 1 );

    for( size_t i = 0; i < compiler->tokens->ptr; i++ )
    {
        Token* t = token_list_get( compiler->tokens, i );

        if( t->type == INST )
        {
            switch( (TokenInst)t->data )
            {
                case PUSH:
                    if( token_list_get( compiler->tokens, i+1 )->type == NUMBER )
                    {
                        byte_buffer_write8( compiler->bytecode, OP_PUSH_CONST );
                        byte_buffer_write32( compiler->bytecode, token_list_get( compiler->tokens, i+1 )->data );
                        i++;
                    }
                    else
                    {
                        printf( "Bad PUSH inst\n" );
                        compiler->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                case ADD:
                    byte_buffer_write8( compiler->bytecode, OP_ADD_STACK );
                    break;
                case MULT:
                    byte_buffer_write8( compiler->bytecode, OP_MULT_STACK );
                    break;
                case DIV:
                    byte_buffer_write8( compiler->bytecode, OP_DIV_STACK );
                    break;
                case SUB:
                    byte_buffer_write8( compiler->bytecode, OP_SUB_STACK );
                    break;
                case HLT:
                    byte_buffer_write8( compiler->bytecode, OP_HLT );
                    break;
                case NO_INST:
                default:
                    printf( "Unknown instruction token\n" );
                    compiler->status = COMPILER_ERROR;
                    return;
            }
        }
    }
    compiler->status = COMPILER_SUCCESS;
}

void compiler_destroy( Compiler* compiler )
{
    token_list_destroy( compiler->tokens );
    byte_buffer_destroy( compiler->bytecode );
}