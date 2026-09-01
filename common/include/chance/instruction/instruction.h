#ifndef CHANCE_INSTRUCTION_INSTRUCTION_H
#define CHANCE_INSTRUCTION_INSTRUCTION_H

#include <chance/instruction/opcode.h>
#include <chance/types/qad.h>

namespace CE
{
    struct CEILInstruction
    {
        CEILOpcode Opcode;
        union {

        } Operand;
    };
};

#endif // CHANCE_INSTRUCTION_INSTRUCTION_H