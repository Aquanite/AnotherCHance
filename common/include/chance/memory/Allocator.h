#ifndef CHANCE_MEMORY_ALLOCATOR_H
#define CHANCE_MEMORY_ALLOCATOR_H

#include <chance/types/vm.h>
#include <chance/assert.h>

namespace CE
{
    template <typename T>
    class Allocator
    {
    public:
        static T* NativeAlloc(CENative count)
        {
            CE_ASSERT(count < CHANCE_NATIVE_MAX / sizeof(T), "Allocation will overflow");
    
            void* memory = CHANCE_ALLOC(sizeof(T) * count);
            CE_ASSERT(memory, "Allocation failed");

            return static_cast<T*>(memory);
        }

        static void NativeRealloc(T*& old, CENative count)
        {
            CE_ASSERT(count < CHANCE_NATIVE_MAX / sizeof(T), "Allocation will overflow");

            old = static_cast<T*>(CHANCE_REALLOC(old, sizeof(T) * count)); // If Old is NULL, then it will just behave like malloc

            CE_ASSERT(old, "Allocation failed");
        }

        static void NativeFree(T*& ptr)
        {
            if (!ptr) return;

            CHANCE_FREE(ptr);

            ptr = nullptr;
        }

        static void Shift(T*& ptr, CENative count, int direction)
        {
            CE_ASSERT(count < CHANCE_NATIVE_MAX / sizeof(T), "Shift will overflow");
            CE_ASSERT(ptr, "Pointer is null");

            CHANCE_MEMMOVE(ptr + direction, ptr, count * sizeof(T));

            ptr += direction;
        }

        static void MemCopy(T*& dest, T*& src, CENative count)
        {
            CE_ASSERT(count < CHANCE_NATIVE_MAX / sizeof(T), "Copy will overflow");
            CE_ASSERT(dest, "dest is null");  
            CE_ASSERT(src, "src is null");

            CHANCE_MEMCOPY(dest, src, count * sizeof(T));
        }
    };
};

#endif // CHANCE_MEMORY_ALLOCATOR_H