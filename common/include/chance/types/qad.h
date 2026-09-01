/*
file: qad.h

Quick and Dirty macros to help across C/C++.
Written by AzureianGH on GitHub.
*/

#ifndef STELLAR_QAD_H
#define STELLAR_QAD_H

#ifndef __cplusplus
    #define struct_t typedef struct
    #define enum_t typedef enum
    #define union_t union
#else 
#define enum_t enum class
#endif // __cplusplus

#define STR(x) #x
#define STR_CONTENTS(x) STR(x)

#endif // STELLAR_QAD_H