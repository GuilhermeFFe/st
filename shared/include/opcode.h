#pragma once

enum _Opcode
{
    OP_NOP          = 0x00,
    OP_PUSH_CONST   = 0x01,
    OP_ADD_STACK    = 0x02,
    OP_MULT_STACK   = 0x03,
    OP_DIV_STACK    = 0x04,
    OP_SUB_STACK    = 0x05,
    OP_JMP          = 0x06,
    OP_CALL         = 0x07,
    OP_RET          = 0x08,
    OP_HLT          = 0xFF
};
typedef enum _Opcode Opcode;