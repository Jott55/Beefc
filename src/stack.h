#ifndef STACK_HEADER
#define STACK_HEADER
// stack.h
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char* stack_t;

typedef struct Stack {
    stack_t* start; // pointer to const char* [0x007f, ...]
    size_t size;
    size_t capacity;
} Stack;

void stack_printn(Stack *stack, const char *name) {
    printf("Stack: %s\n| size: %lu\n| capacity: %lu\n| contents: ", name, stack->size, stack->capacity);
    for (int i = 0; i < stack->size; i++) {
        printf("%p ", *(stack->start+i));
    }
    putchar('\n');
}

#define stack_print(stack) stack_printn(&stack, "unknown")

Stack stack_new() {
    return (Stack) {
        .start = NULL,
        .size = 0,
        .capacity = 0
    };
}

void stack_resize(Stack *stack, size_t size) {
    if (size > stack->capacity) { 
        stack->capacity = size * 2;
        stack->start = (stack_t*)realloc(stack->start, stack->capacity * sizeof(stack_t));
        assert((size-stack->size >=0)); 
        memset(stack->start+stack->size, 0, sizeof(stack_t)*(size-stack->size));
    } else if (stack->size < size) {
        assert((size-stack->size >=0)); 
        memset(stack->start+stack->size, 0, sizeof(stack_t)*(size-stack->size));
    }
    stack->size = size;
}

void stack_destroy(Stack *stack) {
    free(stack->start);
    stack->capacity = 0;
    stack->size = 0;
}

void stack_add(Stack *stack, stack_t value) {
    stack_resize(stack, stack->size+1);
    stack_t *new_value_loc = stack->start+stack->size-1;
    *new_value_loc = (stack_t)value;
}

stack_t *stack_pointer_at(Stack *stack, size_t i) {
    return stack->start+i;
}

stack_t stack_pop(Stack *stack) {
    if (stack->size == 0) {
        return NULL;
    }

    stack_t *end = stack_pointer_at(stack, stack->size-1);
    stack_t ch = *end;
    end = NULL;
    stack_resize(stack, stack->size-1);
    return ch;
}

stack_t stack_peek(Stack *stack) {
    return *stack_pointer_at(stack, stack->size-1);
}

#endif