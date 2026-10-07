#pragma once

namespace CE {
    template<typename T>
    class Nullable
    {
    public:
        static inline Nullable<T> Null = Nullable<T>();
    public:
        Nullable() : Value(nullptr) {}

        Nullable(T& value)
        {
            SetValue(value);
        }

        Nullable(const T& value)
        {
            SetValue(value);
        }

        void SetValue(T& value)
        {
            Value = &value;
        }

        void SetValue(const T& value)
        {
            Value = const_cast<T*>(&value);
        }

        T& GetValue()
        {
            return *Value;
        }

        const T& GetValue() const
        {
            return *Value;
        }

        bool IsNull() const
        {
            return Value == nullptr;
        }

        T& operator*()
        {
            return *Value;
        }

    private:
        T* Value;
    };
}
