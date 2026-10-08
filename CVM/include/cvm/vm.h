#pragma once

#include <chance/types/generic/NativeStack.h>
#include <chance/types/types.h>

namespace CE::VM
{
    struct StackFrame
    {
        NativeArray<VMObject> Stack;
        NativeArray<VMObject> Local;
        NativeArray<VMObject> Param;
    };

    class CVM
    {
    public:
        VMObject CallMethod(StackFrame frame, MethodReference method);
    private:
        NativeStack<MethodCall> CallStack;
    };
}