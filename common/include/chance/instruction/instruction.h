#ifndef CHANCE_INSTRUCTION_INSTRUCTION_H
#define CHANCE_INSTRUCTION_INSTRUCTION_H

#include <chance/instruction/opcode.h>
#include <chance/types/qad.h>
#include <chance/types/vm.h>

namespace CE
{
    struct CEILInstruction
    {
        CEILOpcode Opcode;
        union {
            VMi32       Integer;
            VMi64       LongInteger;
            VMNative    NativeInteger;
            VMPtr       Pointer;
            VMFloat     Float;
        } Operand;
    };
};

#endif // CHANCE_INSTRUCTION_INSTRUCTION_H