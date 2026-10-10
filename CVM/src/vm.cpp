#include <chance/types/Method.h>
#include <chance/types/stack/float.h>
#include <chance/types/stack/i32.h>
#include <chance/types/stack/i64.h>
#include <chance/assert.h>
#include <chance/types/VMObject.h>
#include <vm.h>

using namespace CE;

enum_t VMArith
{
    _start,
    Add,
    Padd,
    Sub,
    Psub,
    _end,
};

VMObject Math(VMObject a, VMObject b, VMArith op)
{
    CE_ASSERT(op > VMArith::_start && op < VMArith::_end, "Invalid Arithmetic option!");

    CE_ASSERT(
        a.Type != VMObject::VMObjectType::VMMObject && b.Type != VMObject::VMObjectType::VMMObject,
        "Managed objects cannot be used during arithmetic!" // TODO, check if theres an operator overload for +, then call it
    );

    VMObject returnObj { .Managed = a.Managed };

    if (op == VMArith::Add)
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
                returnObj.LongInteger = a.LongInteger + b.LongInteger;
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.NativeInteger = a.NativeInteger + b.NativeInteger;
                break;
            case VMObject::VMObjectType::VMFloat:
                returnObj.Single = a.Single + b.Single;
                break;

            default:
                CE_ASSERT(false, "Bad type for ADD!");
        }
    }
    else if (op == VMArith::Sub)
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
                returnObj.LongInteger = a.LongInteger - b.LongInteger;
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.NativeInteger = a.NativeInteger - b.NativeInteger;
                break;
            case VMObject::VMObjectType::VMFloat:
                returnObj.Single = a.Single - b.Single;
                break;

            default:
                CE_ASSERT(false, "Bad type for SUB!");
        }
    }
    else if (op == VMArith::Padd)
    {
        CE_ASSERT(a.Type == VMObject::VMObjectType::VMPtr, "First PADD arg must be a pointer!");

        Nullable<Type> ptr_t = GlobalVM::Resolve(a.TrueType);

        CE_ASSERT(!ptr_t.IsNull(), "Type for PADD does not exist!");

        returnObj.Type = VMObject::VMObjectType::VMPtr;

        switch (b.Type)
        {
            case VMObject::VMObjectType::VMi32:
                returnObj.Pointer = a.Pointer + (b.Integer * ptr_t.GetValue().SizeOf);
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.Pointer = a.Pointer + (b.NativeInteger * ptr_t.GetValue().SizeOf);
                break;
            
            default:
                CE_ASSERT(false, "Bad type for PADD!");
        }
    }
    else if (op == VMArith::Psub)
    {
        CE_ASSERT(a.Type == VMObject::VMObjectType::VMPtr, "First PSUB arg must be a pointer!");

        Nullable<Type> ptr_t = GlobalVM::Resolve(a.TrueType);

        CE_ASSERT(!ptr_t.IsNull(), "Type for PADD does not exist!");

        returnObj.Type = VMObject::VMObjectType::VMPtr;
        
        switch (b.Type)
        {
            case VMObject::VMObjectType::VMi32:
                returnObj.Pointer = a.Pointer - (b.Integer * ptr_t.GetValue().SizeOf);
                break;
            case VMObject::VMObjectType::VMNative:
                returnObj.Pointer = a.Pointer - (b.NativeInteger * ptr_t.GetValue().SizeOf);
                break;
            
            default:
                CE_ASSERT(false, "Bad type for PSUB!");
        }
    }

    return returnObj;
}

VM::NextOptions VM::CVM::Next(StackFrame& frame, Instruction ins, CENative& IP)
{
    switch (ins.Opcode)
    {
        case Opcode::Nop:
        {
            IP++;
            break;
        }
        case Opcode::Const_I:
        {
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewI32(ins.Operand[0].Integer)), 
                "Stack overflow!"
            );

            IP += 1 + sizeof(VMi32);
            break;
        }
        case Opcode::Const_L:
        {
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewI64(ins.Operand[0].LongInteger)), 
                "Stack overflow!"
            );

            IP += 1 + sizeof(VMi64);
            break;
        }
        case Opcode::Const_F:
        {
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewSingle(ins.Operand[0].Float)), 
                "Stack overflow!"
            );

            IP += 1 + sizeof(VMFloat);
            break;
        }
        case Opcode::Const_N:
        {
            CE_ASSERT(
                frame.Stack.Push(VMObject::NewNative(ins.Operand[0].NativeInteger)), 
                "Stack overflow!"
            );

            IP += 1 + sizeof(CENative);
            break;
        }
        case Opcode::Cast:
        {

        }
        case Opcode::Ld_l:
        {
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
        }
        case Opcode::Ld_a:
        {
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
        }
        case Opcode::St_l:
        {
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
            break;
        }
        case Opcode::St_a:
        {
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
            break;
        }
        case Opcode::Add:
        {
            CE_ASSERT(
                frame.Stack.Length() >= 2,
                "Cannot pop from empty stack!"
            );

            VMObject b = frame.Stack.Pop();
            VMObject a = frame.Stack.Pop();

            CE_ASSERT(
                frame.Stack.Push(Math(a, b, VMArith::Add)), 
                "Stack overflow!"
            );

            IP++;
            break;
        }
        case Opcode::Sub:
        {
            CE_ASSERT(
                frame.Stack.Length() >= 2,
                "Cannot pop from empty stack!"
            );

            VMObject b = frame.Stack.Pop();
            VMObject a = frame.Stack.Pop();

            CE_ASSERT(
                frame.Stack.Push(Math(a, b, VMArith::Sub)),
                "Stack overflow!"
            );

            IP++;
            break;
        }
        case Opcode::Padd:
        {
            CE_ASSERT(
                frame.Stack.Length() >= 2,
                "Cannot pop from empty stack!"
            );

            VMObject offset = frame.Stack.Pop();
            VMObject ptr = frame.Stack.Pop();

            CE_ASSERT(
                frame.Stack.Push(Math(ptr, offset, VMArith::Padd)),
                "Stack overflow!"
            );

            IP++;
            break;
        }
        case Opcode::Psub:
        {
            CE_ASSERT(
                frame.Stack.Length() >= 2,
                "Cannot pop from empty stack!"
            );

            VMObject offset = frame.Stack.Pop();
            VMObject ptr = frame.Stack.Pop();

            CE_ASSERT(
                frame.Stack.Push(Math(ptr, offset, VMArith::Psub)),
                "Stack overflow!"
            );

            IP++;
            break;
        }
        case Opcode::Dup:
        {
            CE_ASSERT(
                frame.Stack.Length() > 0,
                "Stack underflow!"
            );

            CE_ASSERT(
                frame.Stack.Push(frame.Stack[frame.Stack.Length() - 1]),
                "Stack overflow!"
            );

            IP++;
            break;
        }
        case Opcode::Drop:
        {
            CE_ASSERT(
                frame.Stack.Length() > 0,
                "Stack underflow!"
            );

            frame.Stack.Pop();

            IP++;
            break;
        }
        case Opcode::Ret:
        {
            return NextOptions::Return;
        }

        default:
            CE_ASSERT(false, "Unknown instruction!");
    }

    return NextOptions::Nothing;
}

bool VM::CVM::CallMethod(StackFrame& frame, MethodReference method)
{
    Method& mthd = GlobalVM::Resolve(method);

    CE_ASSERT(mthd != Method::NullMethod, "Method call failed: Method does not exist!");

    const uint8_t* instructions = mthd.GetBody();
    const CENative insLength = mthd.GetBodyLength();

    NextOptions options = NextOptions::Nothing;

    while (options != NextOptions::Return)
    {
        
    }
}