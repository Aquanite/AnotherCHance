#pragma once

#include <chance/types/types.h>
#include <chance/types/Type.h>
#include <chance/types/generic/NativeArray.h>

namespace CE
{
    class Method;

    class GlobalVM
    {
    public:
        template<typename T>
        static Nullable<T> Resolve(DataReference ref)
        {
            if (ref == 0)
                return Nullable<T>::Null;

            return Nullable<T>(*reinterpret_cast<T*>(ref));
        }

        static Nullable<Type> Resolve(TypeReference ref)
        {
            if (!Types.Exists(ref.ID))
                return Nullable<Type>::Null;

            return Nullable<Type>(Types[ref.ID]);
        }

        static Nullable<Type> ResolveType(StringReference ref)
        {
            for (CENative i = 0; i < Types.Length(); i++)
                if (Types[i].Qualified == ref)
                    return Types[i];

            return Nullable<Type>::Null;
        }

        static Nullable<String> Resolve(StringReference ref)
        {
            if (!Strings.Exists(ref.ID))
                return Nullable<String>::Null;

            return Nullable<String>(Strings[ref.ID]);
        }

        static Method& Resolve(MethodReference ref);

        static StringReference Add(String str)
        {
            if (str == nullptr)
                return StringReference::Fail;

            CENative index = Strings.IndexOf(str);
            if (index != CHANCE_NATIVE_MAX)
                return StringReference { index };

            if (!Strings.Add(str))
                return StringReference::Fail;

            return StringReference { Strings.IndexOf(str) };
        }

        static TypeReference Add(Type type)
        {
            if (type.SizeOf == 0)
                return TypeReference::Fail;

            CENative index = Types.IndexOf(type);
            if (index != CHANCE_NATIVE_MAX)
                return TypeReference { index };

            if (!Types.Add(type))
                return TypeReference::Fail;

            return TypeReference { Types.IndexOf(type) };
        }

        static MethodReference Add(Method method);

        static StringReference Get(String str)
        {
            return StringReference { Strings.IndexOf(str) };
        }

        static TypeReference Get(Type type)
        {
            return TypeReference { Types.IndexOf(type) };
        }

        static TypeReference Get(StringReference ref)
        {
            for (CENative i = 0; i < Types.Length(); i++)
                if (Types[i].Qualified == ref)
                    return TypeReference { i };
            
            return TypeReference::Fail;
        }

        static MethodReference Get(Method& method);
    private:
        static NativeArray<Type>    Types;
        static NativeArray<String>  Strings;
        static NativeArray<Method>  Methods;
    };
}