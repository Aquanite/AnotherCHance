#pragma once

#include <chance/types/types.h>
#include <chance/types/Type.h>

#include <chance/collective/Collective.h>

namespace CE
{
    class Field
    {
        friend Collective::Collective;
    public:
        static DataReference    GetFieldReference();
        static TypeReference    GetTypeReference();
        static Type&            ResolveType();
    private:
        TypeReference Type;
        DataReference Data;
    };
}