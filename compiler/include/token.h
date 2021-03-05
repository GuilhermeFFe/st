#pragma once

#include <stdlib.h>
#include <stdint.h>

enum _TokenType
{
    INST,
    NUMBER,
    REGISTER
};
typedef enum _TokenType TokenType;

enum _TokenInst
{
    NO_INST = -1, // No instruction found (error state)
    PUSH,
    ADD,
    MULT,
    DIV,
    SUB,
    JMP,
    CALL,
    RET,
    PUSHR,
    PRNT,
    HLT
};
typedef enum _TokenInst TokenInst;

/**
 * Converts TokenInst to a string
 * 
 * @param tinst TokenInst to be converted as string
 * @returns string from TokenInst (I.E. PUSH becomes "push")
 */
char* token_inst_str( const TokenInst tinst );

struct _Token
{
    TokenType type;
    uint32_t data;
    uint32_t line;
};

typedef struct _Token Token;

/**
 * Creates token from given type, data and line number
 * 
 * @param tok token to fill
 * @param type token type to be created
 * @param data data to insert into token
 * @param line source code's line
 * @returns token from given type, data and line
 */
void token_create( Token* tok, TokenType type, int data, int line );

// /**
//  * Frees memory allocated to given token
//  * 
//  * @param tok token to be free'd
//  */
// void token_destroy( Token* tok );

struct _TokenList
{
    Token* data;
    size_t ptr; // Points to the current selected pointer in data
    size_t size;
};

typedef struct _TokenList TokenList;

/**
 * Initializes given TokenList with size
 * 
 * NOTE: remember to free the list, using token_list_free
 * 
 * @param list TokenList to initialize
 * @param size initial size to initialize TokenList
 */
void token_list_initialize( TokenList* list, size_t size );

/**
 * Adds given Token to given TokenList
 * 
 * @param list TokenList to append Token
 * @param tok Token to apppend
 */
void token_list_add( TokenList* list, Token tok );

/**
 * Gets token from list at given index
 * 
 * @param list TokenList to find Token
 * @param index index to find token
 * @returns Token that is at list's index
 */
Token* token_list_get( const TokenList* list, size_t index );

/**
 * Destroy given token list, freeing it's memory. Also destroys all tokens inside it
 * 
 * @param list TokenList to be destroyed
 */
void token_list_destroy( TokenList* list );
