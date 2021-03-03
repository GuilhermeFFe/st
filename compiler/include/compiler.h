#pragma once

#include <token.h>
#include <bytebuffer.h>

enum _CompilerStatus
{
    COMPILER_SUCCESS,
    COMPILER_ERROR
};
typedef enum _CompilerStatus CompilerStatus;

struct _Compiler
{
    CompilerStatus status;
    TokenList* tokens;
    ByteBuffer* bytecode;
};
typedef struct _Compiler Compiler;

void compiler_start( Compiler* compiler );
void compiler_destroy( Compiler* compiler );