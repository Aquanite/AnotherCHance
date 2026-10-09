#pragma once

#include <chance/types/VMObject.h>
#include <chance/types/generic/NativeStack.h>
#include <chance/types/types.h>
#include <chance/instruction/Instruction.h>

namespace CE::VM
{
    struct StackFrame
    {
        NativeStack<VMObject> Stack;
        NativeArray<VMObject> Local;
        NativeArray<VMObject> Param;
    };

    struct CatchFrame
    {
        CENative Start;
        StringReference Catches;
    };

    struct ExceptionFrame
    {
        MethodReference Method;
        CENative TryStart;
        
    };

    class CVM
    {
    public:
        VMObject CallMethod(StackFrame& frame, MethodReference method);
    private:
        CENative Next(StackFrame& frame, Instruction ins, CENative& IP);
    private:
        NativeStack<MethodCall> CallStack;
        NativeStack<MethodCall> ExceptionStack;
    };
}