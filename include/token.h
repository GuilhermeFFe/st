#pragma once

#include <stdlib.h>

enum _TokenType
{
    INST,
    NUMBER
};
typedef enum _TokenType TokenType;

enum _TokenInst
{
    NO_INST = -1, // No instruction found (error state)
    PUSH,
    ADD,
    HLT
};
typedef enum _TokenInst TokenInst;

char* token_inst_str( const TokenInst tinst );

struct _Token
{
    TokenType type;
    int data;
    int line;
};

typedef struct _Token Token;

Token* token_create( TokenType type, int data, int line );
void token_destroy( Token* tok );

struct _TokenList
{
    Token** data;
    size_t ptr; // Points to the current selected pointer in data
    size_t size;
};

typedef struct _TokenList TokenList;

TokenList* token_list_create( TokenList* list, size_t size );
void token_list_add( TokenList* list, Token* tok );
Token* token_list_get( const TokenList* list, int index );
void token_list_destroy( TokenList* list );
