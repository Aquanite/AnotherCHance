#ifndef CHANCE_INSTRUCTION_OPCODE_H
#define CHANCE_INSTRUCTION_OPCODE_H

#include <chance/types/qad.h>
#include <chance/types/vm.h>

namespace CE
{
    enum_t CEILOpcode : uint8_t
    {
        Nop,        // nop;         No operation
        Const_I,    // const.i X32; I32 Constant
        Const_L,    // const.l X64; I64 Constant
        Const_F,    // const.f X?;  Float Constant
        Const_N,    // const.n X?;  Native Constant
        Cast,       // cast T;      Cast to type T
        Ld_l,       // ld.l X16;    Load Local
        Ld_a,       // ld.a X16;    Load Argument
        St_l,       // st.l X16;    Store Local
        St_a,       // st.a X16;    Store Argument
        Add,        // add;         Add two items on the stack
        Sub,        // sub;         Subtract two items on the stack
        Dup,        // dup;         Duplicate the top item
        Ret         // ret;         Return
    };
};

#endif // CHANCE_INSTRUCTION_OPCODE_H