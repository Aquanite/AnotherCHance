#pragma once

#include <chance/instruction/instruction.h>
#include <chance/assert.h>
#include <chance/types/Param.h>
#include <chance/types/types.h>
#include <chance/types/Type.h>

#include <chance/collective/Collective.h>

namespace CE
{
    class Method
    {
        friend Collective::Collective;
    public:
        static Method NullMethod;
    public:
        Method() = default;
        Method(String qualified, Type returnType, NativeArray<Instruction>& body, NativeArray<Param>& params);
        Method(const Method&) = default;
        Method& operator=(const Method&) = default;

        const NativeArray<Instruction>& GetBody() const
        {
            return Body;
        }

        const NativeArray<Param>& GetParameters() const
        {
            return Parameters;
        }

        TypeReference GetReturnTypeReference()
        {
            return ReturnType;
        }

        StringReference GetQualifiedReference()
        {
            return Qualified;
        }

        bool operator==(const Method& other) const
        {
            return Qualified == other.Qualified && ReturnType == other.ReturnType;
        }

        Nullable<Type> ResolveReturnType();
        Nullable<String> ResolveQualified();
    private:
        StringReference Qualified;
        TypeReference ReturnType;
        NativeArray<Instruction> Body;
        NativeArray<Param> Parameters;
    };
}

#include <chance/vm/GlobalVM.h>

namespace CE
{
    inline Method::Method(String qualified, Type returnType, NativeArray<Instruction>& body, NativeArray<Param>& params)
    {
        Qualified = GlobalVM::Get(qualified);
        ReturnType = GlobalVM::Get(returnType);
        Body = body;
        Parameters = params;

        CE_ASSERT(Qualified != StringReference::Fail, "Qualified name does not exist!");
        CE_ASSERT(ReturnType != TypeReference::Fail, "Type does not exist!");
        CE_ASSERT(Body.Length() > 0, "Body of method does not exist!");
    }

    inline Nullable<Type> Method::ResolveReturnType()
    {
        return GlobalVM::Resolve(ReturnType);
    }

    inline Nullable<String> Method::ResolveQualified()
    {
        return GlobalVM::Resolve(Qualified);
    }

    inline Method& GlobalVM::Resolve(MethodReference ref)
    {
        if (!Methods.Exists(ref.ID))
            return Method::NullMethod;

        return Methods[ref.ID];
    }

    inline MethodReference GlobalVM::Add(Method method)
    {
        if (!Methods.Add(method))
            return MethodReference::Fail;

        return MethodReference { Methods.IndexOf(method) };
    }

    inline MethodReference GlobalVM::Get(Method& method)
    {
        return MethodReference { Methods.IndexOf(method) };
    }
}