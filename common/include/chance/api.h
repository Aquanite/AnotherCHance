#ifndef CHANCE_API_H
#define CHANCE_API_H

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef LIBBUILD
        #define CHANCEAPI __declspec(dllexport)
    #else
        #define CHANCEAPI __declspec(dllimport)
    #endif
#else
    #if __GNUC__ >= 4
        #define CHANCEAPI __attribute__((visibility("default")))
    #else
        #define CHANCEAPI
    #endif
#endif

#endif // CHANCE_API_H