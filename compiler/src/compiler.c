#include <compiler.h>
#include <opcode.h>

#include <stdio.h>

void compiler_start( Compiler* compiler )
{
    compiler->bytecode = byte_buffer_create( 1 );
    {
        Token* t = token_list_get( compiler->tokens, 0 );
        if( t->type == NUMBER )
        {
            byte_buffer_write32( compiler->bytecode, t->data );
        }
        else
        {
            printf( "Starting address not set!\n" );
            compiler->status = COMPILER_ERROR;
            return;
        }
    }

    for( size_t i = 1; i < compiler->tokens->ptr; i++ )
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
                        byte_buffer_write32( compiler->bytecode, token_list_get( compiler->tokens, ++i )->data );
                    }
                    else if( token_list_get( compiler->tokens, i+1 )->type == REGISTER )
                    {
                        byte_buffer_write8( compiler->bytecode, OP_PUSH_REG_VAL );
                        byte_buffer_write8( compiler->bytecode, token_list_get( compiler->tokens, ++i )->data );
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
                case JMP:
                    if( token_list_get( compiler->tokens, i+1 )->type == NUMBER )
                    {
                        byte_buffer_write8( compiler->bytecode, OP_JMP );
                        byte_buffer_write32( compiler->bytecode, token_list_get( compiler->tokens, i+1 )->data );
                        i++;
                    }
                    else
                    {
                        printf( "Bad JMP inst\n" );
                        compiler->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                case CALL:
                    if( token_list_get( compiler->tokens, i+1 )->type == NUMBER )
                    {
                        byte_buffer_write8( compiler->bytecode, OP_CALL );
                        byte_buffer_write32( compiler->bytecode, token_list_get( compiler->tokens, i+1 )->data );
                        i++;
                    }
                    else
                    {
                        printf( "Bad CALL inst\n" );
                        compiler->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                case RET:
                    byte_buffer_write8( compiler->bytecode, OP_RET );
                    break;
                case HLT:
                    byte_buffer_write8( compiler->bytecode, OP_HLT );
                    break;
                case PUSHR:
                    byte_buffer_write8( compiler->bytecode, OP_PUSHR );
                    if( token_list_get( compiler->tokens, ++i )->type == REGISTER )
                    {
                        byte_buffer_write8( compiler->bytecode, token_list_get( compiler->tokens, i )->data );
                        if( token_list_get( compiler->tokens, ++i )->type == NUMBER )
                        {
                            byte_buffer_write32( compiler->bytecode, token_list_get( compiler->tokens, i )->data );
                        }
                        else
                        {
                            printf( "Bad PUSHR inst - No number constant given\n" );
                            compiler->status = COMPILER_ERROR;
                            return;
                        }
                    }
                    else
                    {
                        printf( "Bad PUSHR inst - No register given\n" );
                        compiler->status = COMPILER_ERROR;
                        return;
                    }
                    break;
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