#pragma once

#include <chance/assert.h>
#include <chance/vm/GlobalVM.h>
#include <chance/types/types.h>
#include <chance/types/Type.h>

#include <chance/collective/Collective.h>

namespace CE
{
    class Field
    {
        friend Collective::Collective;
    public:
        Field(String qualified, Type type, DataReference data)
        {
            Qualified = GlobalVM::Get(qualified);
            Type = GlobalVM::Get(type);
            Data = data;

            CE_ASSERT(Qualified != StringReference::Fail, "Qualified name does not exist!");
            CE_ASSERT(Type != TypeReference::Fail, "Type does not exist!");
            CE_ASSERT(Data != 0, "Data does not exist!");
        }

        DataReference GetField()
        {
            return Data;
        }

        TypeReference GetTypeReference()
        {
            return Type;
        }

        StringReference GetQualifiedReference()
        {
            return Qualified;
        }

        Nullable<Type> ResolveType()
        {
            return GlobalVM::Resolve(Type);
        }

        Nullable<String> ResolveQualified()
        {
            return GlobalVM::Resolve(Qualified);
        }
    private:
        StringReference Qualified;
        TypeReference Type;
        DataReference Data;
    };
}