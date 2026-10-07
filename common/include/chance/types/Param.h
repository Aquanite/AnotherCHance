#pragma once

#include <chance/assert.h>
#include <chance/types/types.h>
#include <chance/types/Type.h>

#include <chance/collective/Collective.h>

namespace CE
{
    class Param
    {
        friend Collective::Collective;
    public:
        Param(String qualified, Type type);
        Param(String qualified, TypeReference type);

        TypeReference GetTypeReference()
        {
            return Type;
        }

        StringReference GetQualifiedReference()
        {
            return Qualified;
        }

        Nullable<Type> ResolveType();
        Nullable<String> ResolveQualified();
    private:
        StringReference Qualified;
        TypeReference Type;
    };
}

#include <chance/vm/GlobalVM.h>

namespace CE
{
    inline Param::Param(String qualified, CE::Type type)
    {
        Qualified = GlobalVM::Get(qualified);
        Type = GlobalVM::Get(type);

        CE_ASSERT(Qualified != StringReference::Fail, "Qualified name does not exist!");
        CE_ASSERT(Type != TypeReference::Fail, "Type does not exist!");
    }

    inline Param::Param(String qualified, TypeReference type)
    {
        Qualified = GlobalVM::Get(qualified);
        Type = type;

        CE_ASSERT(Qualified != StringReference::Fail, "Qualified name does not exist!");
        CE_ASSERT(Type != TypeReference::Fail, "Type does not exist!");
    }

    inline Nullable<Type> Param::ResolveType()
    {
        return GlobalVM::Resolve(Type);
    }

    inline Nullable<String> Param::ResolveQualified()
    {
        return GlobalVM::Resolve(Qualified);
    }
}