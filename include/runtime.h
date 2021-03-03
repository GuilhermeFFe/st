#pragma once

#include <stdbool.h>

#include <util.h>

#define STACK_SIZE 1024
#define CALL_STACK_SIZE (STACK_SIZE/4)

enum _RuntimeStatus
{
    RUNTIME_SUCCESS,
    RUNTIME_ERROR
};
typedef enum _RuntimeStatus RuntimeStatus;

struct _Runtime
{
    uint8_t* code;
    RuntimeStatus status;
    uint8_t stack[STACK_SIZE];
    uint32_t call_stack[CALL_STACK_SIZE];
    uint32_t cp;      // Call pointer
    uint32_t sp;      // Stack pointer
    uint32_t ip;      // Instruction pointer
    uint8_t exit;
    char* message;
    bool running;
};
typedef struct _Runtime Runtime;

/**
 * Initializes runtime
 * 
 * @param runtime runtime object to fill in
 */
void runtime_start( Runtime* runtime );

/**
 * Pushes 32bit address into call stack
 * 
 * @param r runtime object in which to fill call stack
 * @param addr address to push
 */
void push_addr( Runtime* r, uint32_t addr );

/**
 * Pops address from call stack
 * 
 * @param r runtime object to pop call stack
 * @returns address from call stack
 */
uint32_t pop_addr( Runtime* r );

/**
 * Pushes 8 bit number into stack
 * 
 * @param r runtime object in which to fill stack
 * @param data 8 bit number to push
 */
void push8( Runtime* r, uint8_t data );

/**
 * Pushes 16 bit number into stack
 * 
 * @param r runtime object in which to fill stack
 * @param data 16 bit number to push
 */
void push16( Runtime* r, uint16_t data );

/**
 * Pushes 32 bit number into stack
 * 
 * @param r runtime object in which to fill stack
 * @param data 32 bit number to push
 */
void push32( Runtime* r, uint32_t data );

/**
 * Pops 8 bit number from stack
 * 
 * @param r runtime object in which to pop stack
 * @returns 8 bit number from stack
 */
uint8_t pop8( Runtime* r );

/**
 * Pops 16 bit number from stack
 * 
 * @param r runtime object in which to pop stack
 * @returns 16 bit number from stack
 */
uint16_t pop16( Runtime* r );

/**
 * Pops 32 bit number from stack
 * 
 * @param r runtime object in which to pop stack
 * @returns 32 bit number from stack
 */
uint32_t pop32( Runtime* r );