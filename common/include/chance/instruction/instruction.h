#pragma once

#include <chance/instruction/opcode.h>
#include <chance/types/qad.h>
#include <chance/types/vm.h>

namespace CE
{
    struct Instruction
    {
        Opcode Opcode;
        union {
            VMi32       Integer;
            VMi64       LongInteger;
            VMNative    NativeInteger;
            VMPtr       Pointer;
            VMFloat     Float;
        } Operand[3];
    };
};