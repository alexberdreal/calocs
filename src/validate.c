#include "defines.h"
#include "custom_assert.h"

void validate_number(const char* data) {
    for (const char* ch = data; *ch != '\0'; ch++) {
        TERMINATING_ASSERT(*ch >= '0' && *ch <= '9');
    }
}

// Stack allocator ;

void validate_stack_allocator_args(int argc, char** argv) {
    // 2 arguments must be provided: batch size and allocator size
    TERMINATING_ASSERT(argc == 2);

    char* allocator_size = argv[1];
    
    validate_number(allocator_size);
    
    TERMINATING_ASSERT(atoi(allocator_size) <= SA_MAX_SIZE);
}
