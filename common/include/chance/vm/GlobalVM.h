#pragma once

#include <chance/types/types.h>
#include <chance/types/Type.h>
#include <chance/types/generic/NativeArray.h>

namespace CE
{
    class GlobalVM
    {
    public:
        
    private:
        static NativeArray<Type> Types;
        static NativeArray<String> Strings;
    };
}