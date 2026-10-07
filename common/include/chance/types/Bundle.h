#pragma once

#include <chance/collective/Collective.h>
#include <chance/types/generic/NativeStack.h>
#include <chance/types/Field.h>
#include <chance/types/types.h>

namespace CE
{
    class Bundle
    {
        friend Collective::Collective;

    public:
        
    private:
        NativeStack<Bundle> NestedBundles;
        NativeStack<Field> Fields;
    };
}