#pragma once

enum _Opcode
{
    OP_NOP          = 0x00,
    OP_PUSH_CONST   = 0x01,
    OP_ADD_STACK    = 0x02,
    OP_HLT          = 0xFF
};
typedef enum _Opcode Opcode;