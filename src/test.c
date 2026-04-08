#include "vector.h"
#include "stack.h"
#include "brainfuck.h"
#include "file_io.h"


void vector_test() {
    Vector v1 = vector_new();
    vector_resize(&v1, 777);
    vector_add(&v1, 12);
    vector_add(&v1, 34);
    vector_add(&v1, 56);
    vector_resize(&v1, 10);
    Vector v2 = vector_new();
    vector_resize(&v2, 1);
    vector_resize(&v2, 2);
    vector_resize(&v2, 3);
    vector_resize(&v2, 5);
    vector_resize(&v2, 8);
    vector_resize(&v2, 13);
    vector_resize(&v2, 1);
    vector_resize(&v2, 0);
    vector_resize(&v2, 69);
    vector_resize(&v2, 3);

    vector_print(v1, "v1");
    vector_print(v2, "v2");
    
    printf("v1, peek(3): %d\n", *vector_at(&v1, 3));
    
    vector_destroy(&v1);
    vector_destroy(&v2);
}

void stack_test() {
    Stack s = stack_new();
    unsigned char c1 = 'a';
    unsigned char c2 = 'b';
    stack_add(&s, &c1);
    stack_add(&s, &c2);
    stack_add(&s, &c2);
    printf("p: %c\n", **stack_pointer_at(&s, 1));
    printf("pop: %p\n", stack_pop(&s));

    stack_print(s);
    stack_destroy(&s);
 
}

void brainfuck_test() {
    brainfuck_run_from_file("../brainfuck.bf");
}

int main() {
    // vector_test();
    // stack_test();
    brainfuck_test();
    return 0;
}