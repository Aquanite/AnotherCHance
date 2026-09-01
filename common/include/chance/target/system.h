#ifndef CHANCE_TARGET_SYSTEM_H
#define CHANCE_TARGET_SYSTEM_H

#include <chance/types/qad.h>
#ifdef T_AARCH64
    #include <chance/target/AARCH64/AARCH64.h>
#else
    #error "No target is defined"
#endif // Arch lists


#ifndef CHANCE_FLOAT
    #error "CHANCE_FLOAT is NOT defined."
#endif // CHANCE_FLOAT

#ifndef CHANCE_NATIVE
    #error "CHANCE_NATIVE is NOT defined."
#endif // CHANCE_NATIVE

#ifndef CHANCE_POINTER
    #error "CHANCE_POINTER is NOT defined."
#endif // CHANCE_POINTER

#ifndef CHANCE_NATIVE_MAX
    #error "CHANCE_NATIVE_MAX is NOT defined."
#endif // CHANCE_NATIVE_MAX

namespace CE
{
    typedef CHANCE_FLOAT CEFloat;
    typedef CHANCE_NATIVE CENative;
    typedef CHANCE_POINTER CEPtr;

    enum_t CETargets : uint32_t
    {
        X86_32 = 0x80386,
        X86_64 = 0x808664,
        
        AARCH32 = 0xAA6C532,
        AARCH64 = 0xAA6C564
    };
};

#endif // CHANCE_TARGET_SYSTEM_H