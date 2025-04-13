#ifndef CUSTOM_ASSERTS 
#define CUSTOM_ASSERTS

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// release mode 

#ifdef NDEBUG
    #define _ASSERT(condition)                              \
        do {                                                \
            if (!(condition)) {                             \
                printf("assert failed: %s\n", #condition);  \
            }                                               \
        } while (0)

    #define TERMINATING_ASSERT(condition)       \
    do {                                        \
        if (!(condition)) {                     \
            printf("error: %s\n", #condition);  \
            abort();                            \
        }                                       \
    } while (0)

// debug mode 

#else 
    #define _ASSERT(condition)                              \
        assert(condition);

    #define TERMINATING_ASSERT(condition) _ASSERT(condition) 

#endif // NDEBUG

#endif // CUSTOM_ASSERTS
