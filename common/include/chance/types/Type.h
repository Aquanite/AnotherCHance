#pragma once

#include <chance/types/types.h>

namespace CE
{
    struct Type
    {
        StringReference Qualified;
        CENative SizeOf;
        bool IsPrimative;

        bool operator==(const Type& other) const
        {
            return Qualified == other.Qualified && SizeOf == other.SizeOf && IsPrimative == other.IsPrimative;
        }
    };
}