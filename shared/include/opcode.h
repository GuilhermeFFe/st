#pragma once

enum _Opcode
{
    OP_NOP              = 0x00,
    OP_PUSH_CONST       = 0x01,
    OP_PUSH_REG_VAL     = 0x02,
    OP_ADD_STACK        = 0x03,
    OP_MULT_STACK       = 0x04,
    OP_DIV_STACK        = 0x05,
    OP_SUB_STACK        = 0x06,
    OP_ADD_REG          = 0x07,
    OP_MULT_REG         = 0x08,
    OP_DIV_REG          = 0x09,
    OP_SUB_REG          = 0x0A,
    OP_JMP              = 0x0B,
    OP_CALL             = 0x0C,
    OP_RET              = 0x0D,
    OP_PUSHR_CONST      = 0x0E,
    OP_PUSHR_REG_VAL    = 0x0F,
    OP_HLT              = 0xFF
};
typedef enum _Opcode Opcode;