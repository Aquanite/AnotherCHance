#include <chance/assert.h>
#include <chance/types/VMObject.h>
#include <vm.h>

using namespace CE;



CENative VM::CVM::Next(StackFrame& frame, Instruction ins, CENative& IP)
{
    switch (ins.Opcode)
    {
        case Opcode::Nop:
            IP++;
            break;
        case Opcode::Const_I:
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewI32(ins.Operand[0].Integer)), 
                "Stack overflow!"
            );

            IP += 5;
            break;
        case Opcode::Const_L:
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewI64(ins.Operand[0].LongInteger)), 
                "Stack overflow!"
            );

            IP += 9;
            break;
        case Opcode::Const_F:
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewSingle(ins.Operand[0].Float)), 
                "Stack overflow!"
            );

            IP += 9;
            break;
        case Opcode::Const_N:
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewNative(ins.Operand[0].NativeInteger)), 
                "Stack overflow!"
            );

            IP += 1 + sizeof(CENative);
            break;
        case Opcode::Cast:
        case Opcode::Ld_l:
            CE_ASSERT(
                frame.Local.Exists(ins.Operand[0].Integer), 
                "Local index does not exist!"
            );

            CE_ASSERT(
                frame.Stack.Push(frame.Local[ins.Operand[0].Integer]), 
                "Stack overflow!"
            );

            IP += 3;
            break;
        case Opcode::Ld_a:
        case Opcode::St_l:
        case Opcode::St_a:
        case Opcode::Add:
        case Opcode::Sub:
        case Opcode::Dup:
        case Opcode::Ret:
        break;
    }
}