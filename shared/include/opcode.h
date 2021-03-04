#pragma once

enum _Opcode
{
    OP_NOP          = 0x00,
    OP_PUSH_CONST   = 0x01,
    OP_PUSH_REG_VAL = 0x02,
    OP_ADD_STACK    = 0x03,
    OP_MULT_STACK   = 0x04,
    OP_DIV_STACK    = 0x05,
    OP_SUB_STACK    = 0x06,
    OP_JMP          = 0x07,
    OP_CALL         = 0x08,
    OP_RET          = 0x09,
    OP_PUSHR        = 0x10,
    OP_HLT          = 0xFF
};
typedef enum _Opcode Opcode;