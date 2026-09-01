#ifndef CHANCE_TYPES_GENERIC_NATIVEARRAY_H
#define CHANCE_TYPES_GENERIC_NATIVEARRAY_H

#include <chance/imports/imports.h>
#include <chance/target/AARCH64/AARCH64.h>
#include <chance/types/types.h>
#include <chance/target/system.h>
#include <chance/assert.h>
#include <chance/memory/Allocator.h>

namespace CE
{
    template <typename T>
    class NativeArray
    {
    public: // Public Methods
        ~NativeArray()
        {
            Allocator<T>::NativeFree(base);
            top = current = base;
        }

        NativeArray(CENative initialCount = 0)
        {
            if (initialCount == 0)
                return;

            CreateIfNotAlready(initialCount);
        }

        T& operator[](CENative index)
        {
            CE_ASSERT(Exists(index), "Index does not exist in the array"); // If somethings goes wrong, it's best to just end early

            return *(base + index);
        }

        bool Add(T type)
        {
            CreateIfNotAlready(4);

            if (pinned && IsFull())
                return false;

            ExpandIfAtLimits();

            *current++ = type;
            return true;
        }

        bool Remove(CENative index)
        {
            if (!Exists(index))
                return false;

            T* target = base + index + 1;

            if (current - 1 == target)
            {
                current--;
                return true;
            }

            CENative moveCount = static_cast<CENative>(current - target);

            Allocator<T>::Shift(target, moveCount, -1); // Try to not move every FREE element

            current--;

            if (!pinned)
                ShrinkIfAtMinimum();

            return true;
        }

        bool Exists(CENative index)
        {
            CENative currentIndex = static_cast<CENative>(current - base);

            return index < currentIndex;
        }

        T Get(CENative index)
        {
            CE_ASSERT(Exists(index), "Index does not exist in the array"); // If somethings goes wrong, it's best to just end early

            return *(base + index);
        }

        void Set(CENative index, T object)
        {
            CE_ASSERT(Exists(index), "Index does not exist in the array"); // If somethings goes wrong, it's best to just end early

            *(base + index) = object;
        }

        CENative Capacity()
        {
            return static_cast<CENative>(top - base);
        }

        CENative Length()
        {
            return static_cast<CENative>(current - base);
        }

        T* Data()
        {
            return base;
        }

        void Pin()
        {
            pinned = true;
        }

        void Unpin()
        {
            pinned = false;
        }

        bool IsPinned()
        {
            return pinned;
        }

        bool IsFull()
        {
            return current == top;
        }

        bool IsEmpty()
        {
            return current == base;
        }

        bool Grow(CENative to)
        {
            if (base == nullptr)
                CreateIfNotAlready(to);

            if (to <= Capacity() || pinned)
                return false;

            CENative currentIndex = static_cast<CENative>(current - base);

            Allocator<T>::NativeRealloc(base, to);

            top = current = base;

            top += to;
            current += currentIndex;

            return true;
        }

        bool Truncate(CENative to)
        {
            if (base == nullptr || to >= Capacity() || pinned)
                return false;

            if (to == 0)
            {
                CHANCE_FREE(base);
                top = current = base = nullptr;
                return true;
            }

            CENative currentIndex = static_cast<CENative>(current - base);

            bool oversized = currentIndex > to;

            Allocator<T>::NativeRealloc(base, to);

            top = current = base;
            
            top += to;
            if (oversized)
                current = top;
            else
                current = base + currentIndex;

            return true;
        }

        CENative IndexOf(T of)
        {
            if (base == nullptr)
                return CHANCE_NATIVE_MAX;

            for (CENative i = 0; i < Capacity(); i++)
            {
                if (base[i] == of)
                    return i;
            }

            return CHANCE_NATIVE_MAX;
        }

        bool Clear()
        {
            if (pinned)
            {
                current = base;
                return true;
            }

            return Truncate(0);
        }
    private: // Private Methods
        void CreateIfNotAlready(CENative initialCount)
        {
            if (base != nullptr)
                return;

            top = current = base = Allocator<T>::NativeAlloc(initialCount);

            top += initialCount;
        }

        void ShrinkIfAtMinimum()
        {
            CE_ASSERT(base, "Array is null and is attempting to shrink");

            if (Capacity() <= 4 || Length() > (Capacity() / 4))
                return;

            Truncate(Capacity() / 2);
        }

        void ExpandIfAtLimits()
        {
            CE_ASSERT(base, "Array is null and is attempting to expand");

            if (current != top)
                return;

            CENative currentIndex = static_cast<CENative>(current - base);
            
            CENative newSize = static_cast<CENative>(top - base) * 2;

            Allocator<T>::NativeRealloc(base, newSize);

            top = current = base;

            top += newSize;
            current += currentIndex;
        }
    private: // Private Data
        bool pinned = false;
        T* base     = nullptr;
        T* current  = nullptr;
        T* top      = nullptr;
    };
};

#endif // CHANCE_TYPES_GENERIC_NATIVEARRAY_H