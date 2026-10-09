#include "chance/types/stack/i32.h"
#include <chance/assert.h>
#include <chance/types/VMObject.h>
#include <vm.h>

using namespace CE;

enum_t VMArith
{
    ADD,
    PADD,
    SUB,
    PSUB,
};

VMObject Math(VMObject a, VMObject b, VMArith op, VMi32 ptrSizeof = 0)
{
    CE_ASSERT(
        a.Type != VMObject::VMObjectType::VMMObject && b.Type != VMObject::VMObjectType::VMMObject,
        "Managed objects cannot be added!" // TODO, check if theres an operator overload for +, then call it
    );

    VMObject returnObj { .Managed = a.Managed };

    if (op == VMArith::ADD)
    {
        CE_ASSERT(
            a.Type == b.Type,
            "VM Types must be the same or compatible!"
        );

        CE_ASSERT(a.Type != VMObject::VMObjectType::VMVoid, "Cannot add System.Void!");

        switch (a.Type)
        {                
            case VMObject::VMObjectType::VMi32:
                returnObj.Integer = a.Integer + b.Integer;
                break;
            case VMObject::VMObjectType::VMi64:
                returnObj.Integer = a.LongInteger + b.LongInteger;
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.Integer = a.NativeInteger + b.NativeInteger;
                break;
            case VMObject::VMObjectType::VMFloat:
                returnObj.Integer = a.Single + b.Single;
                break;

            default:
                CE_ASSERT(false, "Bad type for ADD!");
        }
    }
    else if (op == VMArith::SUB)
    {
        CE_ASSERT(
            a.Type == b.Type,
            "VM Types must be the same or compatible!"
        );

        CE_ASSERT(a.Type != VMObject::VMObjectType::VMVoid, "Cannot subtract System.Void!");

        switch (a.Type)
        {                
            case VMObject::VMObjectType::VMi32:
                returnObj.Integer = a.Integer - b.Integer;
                break;
            case VMObject::VMObjectType::VMi64:
                returnObj.Integer = a.LongInteger - b.LongInteger;
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.Integer = a.NativeInteger - b.NativeInteger;
                break;
            case VMObject::VMObjectType::VMFloat:
                returnObj.Integer = a.Single - b.Single;
                break;

            default:
                CE_ASSERT(false, "Bad type for SUB!");
        }
    }
    else if (op == VMArith::PADD)
    {
        CE_ASSERT(a.Type == VMObject::VMObjectType::VMPtr, "First PADD arg must be a pointer!");

        returnObj.Type = VMObject::VMObjectType::VMPtr;

        switch (b.Type)
        {
            case VMObject::VMObjectType::VMi32:
                returnObj.Pointer = a.Pointer + b.Integer;
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.Pointer = a.Pointer + b.NativeInteger;
                break;
            case VMObject::VMObjectType::VMPtr:
                returnObj.Pointer = a.Pointer + b.Pointer;
                break;
            
            default:
                CE_ASSERT(false, "Bad type for PADD!");
        }
    }
    else if (op == VMArith::PSUB)
    {
        CE_ASSERT(a.Type == VMObject::VMObjectType::VMPtr, "First PADD arg must be a pointer!");

        returnObj.Type = VMObject::VMObjectType::VMPtr;

        switch (b.Type)
        {
            case VMObject::VMObjectType::VMi32:
                returnObj.Pointer = a.Pointer + b.Integer;
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.Pointer = a.Pointer + b.NativeInteger;
                break;
            case VMObject::VMObjectType::VMPtr:
                returnObj.Pointer = a.Pointer + b.Pointer;
                break;
            
            default:
                CE_ASSERT(false, "Bad type for PADD!");
        }
    }

    return returnObj;
}

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
            CE_ASSERT(
                frame.Param.Exists(ins.Operand[0].Integer), 
                "Param index does not exist!"
            );

            CE_ASSERT(
                frame.Stack.Push(frame.Param[ins.Operand[0].Integer]), 
                "Stack overflow!"
            );

            IP += 3;
            break;
        case Opcode::St_l:
            CE_ASSERT(
                frame.Local.Exists(ins.Operand[0].Integer), 
                "Local index does not exist!"
            );

            CE_ASSERT(
                !frame.Stack.IsEmpty(),
                "Cannot pop from empty stack!"
            );

            frame.Local[ins.Operand[0].Integer] = frame.Stack.Pop();

            IP += 3;
        case Opcode::St_a:
            CE_ASSERT(
                frame.Param.Exists(ins.Operand[0].Integer), 
                "Param index does not exist!"
            );

            CE_ASSERT(
                !frame.Stack.IsEmpty(),
                "Cannot pop from empty stack!"
            );

            frame.Param[ins.Operand[0].Integer] = frame.Stack.Pop();

            IP += 3;
        case Opcode::Add:
            CE_ASSERT(
                frame.Stack.Length() >= 2,
                "Cannot pop from empty stack!"
            );

            VMObject add_b = frame.Stack.Pop();
            VMObject add_a = frame.Stack.Pop();

        case Opcode::Sub:
        case Opcode::Dup:
        case Opcode::Ret:
        break;
    }
}