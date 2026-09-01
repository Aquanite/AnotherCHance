#ifndef CHANCE_TYPES_GENERIC_NATIVESTACK_H
#define CHANCE_TYPES_GENERIC_NATIVESTACK_H

#include <chance/types/generic/NativeArray.h>
#include <chance/types/types.h>
#include <chance/target/system.h>
#include <chance/assert.h>
#include <chance/memory/Allocator.h>

namespace CE
{
    template <typename T>
    class NativeStack : NativeArray<T>
    {
    private: // Private Using
        using base = NativeArray<T>;

    public: // Public Using
        using base::Capacity;
        using base::Length;
        using base::Data;
        using base::Pin;
        using base::Unpin;
        using base::IsEmpty;
        using base::IsFull;
        using base::IsPinned;
        using base::Grow;
        using base::Truncate;
        using base::Clear;
        using base::operator[];

    public: // Public Methods
        NativeStack(CENative initialCount = 0) : base(initialCount) { }

        bool Push(T object)
        {
            return base::Add(object);
        }

        T Pop()
        {
            CE_ASSERT(base::base, "Cannot pop while stack is NULL");
            CE_ASSERT(base::Length() != 0, "Cannot pop from an empty stack");

            T temp = *(--base::current);

            if (!base::pinned)
                base::ShrinkIfAtMinimum();

            return temp;
        }
    };
};

#endif // CHANCE_TYPES_GENERIC_NATIVESTACK_H