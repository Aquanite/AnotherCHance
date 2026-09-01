#ifndef CHANCE_TYPES_VMOBJECT
#define CHANCE_TYPES_VMOBJECT

#include <chance/target/system.h>
#include <chance/types/stack/float.h>
#include <chance/types/stack/i32.h>
#include <chance/types/stack/i64.h>
#include <chance/types/stack/native.h>
#include <chance/types/stack/pointer.h>

namespace CE
{
    struct alignas(0x8) VMObject
    {
        bool Managed;

        enum class VMObjectType : uint8_t {
            VMi32,
            VMi64,
            VMNative,
            VMPtr,
            VMFloat,
        } Type;

        union
        {
            VMi32       Integer;
            VMi64       LongInteger;
            VMNative    NativeInteger;
            VMPtr       Pointer;
            VMFloat     Float;
        };
    };
};

#endif // CHANCE_TYPES_VMOBJECT