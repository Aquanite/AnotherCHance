#pragma once

#include <chance/types/Nullable.h>
#include <chance/types/vm.h>

#define IDTYPE(type) \
    struct type { \
        static type Fail; \
        CENative ID = CHANCE_NATIVE_MAX; \
        bool operator==(const type& other) const = default; \
    }

namespace CE
{
    typedef const char* String;
    typedef VMPtr DataReference;
    IDTYPE(TypeReference);
    IDTYPE(StringReference);
    IDTYPE(MethodReference);
    typedef struct {MethodReference Ref; CENative ReturningInstruction;} MethodCall;
}