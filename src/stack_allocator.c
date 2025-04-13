#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "defines.h"

// Validator
void validate_stack_allocator_args(int, char**);

void process_args(int argc, char** argv) {
    // validate first
    validate_stack_allocator_args(argc, argv);
}       

struct StackAllocator {
    size_t max_number_of_blocks;
    void* top_ptr;
    size_t used_blocks;
};

void sa_init(struct StackAllocator* allocator) {
     void* bytes = malloc(allocator->max_number_of_blocks * SA_BLOCK_SIZE);
     allocator->top_ptr = bytes;
}

void* sa_get_block(struct StackAllocator* sa) {
    if (sa->used_blocks == sa->max_number_of_blocks) {
        printf("tried to get a new block, but the last one is already taken");
        return NULL; 
    } 
    void* data = sa->top_ptr;
    sa->used_blocks++;
    sa->top_ptr += SA_BLOCK_SIZE;
    return data;
}

// Defines a safe pointer accessor 
//
#define DEFINE_SA_STRUCT_CTR(type)      \
    struct type* ctr_##type(struct StackAllocator* allocator) {  \
        assert(sizeof(struct type) <= SA_BLOCK_SIZE); \
        return (struct type*)sa_get_block(allocator);  \
    }
#define SA_STRUCT_CTR(type, allocator) \
    ctr_##type(allocator)

void sa_remove_block(struct StackAllocator* sa) {
    if (sa->used_blocks == 0) {
        printf("tried to remove the last block, but the memory is totaly unoccupied");
        return;
    }
    sa->top_ptr -= SA_BLOCK_SIZE;
    sa->used_blocks--;
} 

struct StackAllocator get_stack_allocator(size_t allocator_size) {
    struct StackAllocator alloc = {
        .max_number_of_blocks = allocator_size,
        .top_ptr = NULL, 
        .used_blocks = 0 
    };
    return alloc;
}

struct A {
    char data[512];
};
DEFINE_SA_STRUCT_CTR(A) 

struct B {
    char data[64];
};

DEFINE_SA_STRUCT_CTR(B) 

int main(int argc, char** argv) {
    process_args(argc, argv);
    struct StackAllocator allocator = get_stack_allocator(atoi(argv[1]));
    for (int i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }
    struct B* data = SA_STRUCT_CTR(B, &allocator);  // must acquire correctly 
    struct A* data_a = SA_STRUCT_CTR(A, &allocator); // must fail, sizeof A > BATCH_SIZE
    sa_remove_block(&allocator);
    sa_remove_block(&allocator);
}
