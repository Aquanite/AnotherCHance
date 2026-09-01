#ifndef CHANCE_ASSERT_H
#define CHANCE_ASSERT_H

#include <chance/imports/imports.h>
#include <chance/types/qad.h>

#define CE_ERROR(x) CHANCE_FAIL(x)

#define CE_ASSERT(cond, reason)                                                                                                      \
    if (!(cond))                                                                                                                     \
    {                                                                                                                                \
        CE_ERROR("Assertion Failed! \"" STR_CONTENTS(cond) "\": At " __FILE__ ":" STR_CONTENTS(__LINE__) "\nReason: " reason "\n");  \
    }

#define CE_NOTIMPL() CE_ASSERT(false, "Not implemented!")

#define CE_FAIL(x) CE_ERROR("At " __FILE__ ":" STR_CONTENTS(__LINE__) "\nReason: " x "\n")

#endif // CHANCE_ASSERT_H