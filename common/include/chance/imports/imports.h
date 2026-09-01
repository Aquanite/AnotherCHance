#ifndef CHANCE_IMPORTS_IMPORTS_H
#define CHANCE_IMPORTS_IMPORTS_H

#ifndef CHANCE_USE_CUSTOM_IMPORTS
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define CHANCE_ALLOC(x) malloc(x)
    #define CHANCE_REALLOC(x, y) realloc(x, y)
    #define CHANCE_FREE(x) free(x)
    #define CHANCE_EXIT(x) exit(x)
    #define CHANCE_MEMMOVE(dest, src, len) memmove(dest, src, len)
    #define CHANCE_FAIL(x) fprintf(stderr, x); CHANCE_EXIT(-1)
    #define CHANCE_PRINT(x, ...) fprintf(stdout, "%s: " x, __FILE__ __VA_OPT__(,) __VA_ARGS__)
#endif // CHANCE_USE_CUSTOM_IMPORTS

#endif // CHANCE_IMPORTS_IMPORTS_H