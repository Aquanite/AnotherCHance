#pragma once


#include <chance/types/generic/NativeStack.h>
#include <chance/types/types.h>
namespace CE::VM
{
    class CVM
    {
    public:
        static void CallMethod(MethodReference method, NativeArray<VMObject> args);
    private:
        NativeStack<MethodCall> CallStack;
    };
}