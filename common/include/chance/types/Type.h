#pragma once

#include <chance/types/types.h>

namespace CE
{
    struct Type
    {
        StringReference Qualified;
        CENative SizeOf;
        bool IsPrimative;
    };
}