#ifndef BRAINFUCK_HEADER
#define BRAINFUCK_HEADER

#include "vector.h"
#include "file_io.h"
#include "unistd.h"

#ifndef MEMORY_MAX_SIZE 
#define MEMORY_MAX_SIZE 24
#endif

#ifndef FIND_ERRORS_BEFORE_EXECUTING
#define FIND_ERRORS_BEFORE_EXECUTING 1
#endif

// brainfuck.h
typedef unsigned char vector_t;
typedef unsigned char* stack_t;


vector_create(
    Vector,
    vector_t
); 

vector_create (
    Stack,
    stack_t
);



void brainfuck_right(Vector *mem, int *mp) {
    (*mp)++;
    if (*mp+1 > mem->size) {
        vector_resize(mem, mem->size*2);
    }
    assert(*mp+1 <= mem->size);
}

void brainfuck_left(Vector *mem, int *mp) {
    (*mp)--;
    if (*mp < 0) {
        // undefined behavior
        *mp = MEMORY_MAX_SIZE-1;
        if (mem->size != MEMORY_MAX_SIZE) {
            vector_resize(mem, MEMORY_MAX_SIZE);
        }
    }
}

void brainfuck_left_bracket(Vector *mem, int *mp, Stack *stack, stack_t *ch) {
    if (*vector_at(mem, *mp) == 0) {
        while (**ch != '\0' && **ch != ']') {
            (*ch)++;
        }
        return;
    }

    vector_add(stack, *ch);
}

void brainfuck_right_bracket(Vector *mem, int *mp, Stack *stack, stack_t *ch) { 
    assert(stack->size > 0);
    if (*vector_at(mem, *mp) == 0) {
        vector_remove_last(stack);
        return;
    }
    *ch = vector_peek(stack); 
}

void brainfuck_input(Vector *mem, int *mp) {
    (*vector_at(mem, *mp)) = getchar();
}

void brainfuck_output(Vector *mem, int *mp) {
    putchar(*vector_at(mem, *mp));
}

void brainfuck_add(Vector *mem, int *mp) {
    (*vector_at(mem, *mp))++;
}

void brainfuck_sub(Vector *mem, int *mp) {
    (*vector_at(mem, *mp))--;
}

void interpret_brainfuck(unsigned char *content) {
    stack_t ch = content;
    Vector memory = vector_new();
    int mp = 0;
    Stack stack = vector_new();
    
    vector_resize(pointer(memory), 2);
    
    while (*ch != '\0') {
        switch (*ch)
        {
        case '+':
            brainfuck_add(&memory, &mp);
            break;
        case '-':
            brainfuck_sub(&memory, &mp);
            break;
        case '>':
            brainfuck_right(&memory, &mp);
            break;
        case '<':
            brainfuck_left(&memory, &mp);
            break;
        case '.':
            brainfuck_output(&memory, &mp);
            break;
        case ',':
            brainfuck_input(&memory, &mp);
            break;
        case '[':
            brainfuck_left_bracket(&memory, &mp, &stack, &ch);
            break;    
        case ']':
            brainfuck_right_bracket(&memory, &mp, &stack, &ch);
            break;
        default:
            break;
        }
        ch++;
    }
    vector_destroy(pointer(stack));
    vector_destroy(pointer(memory));
}

int brainfuck_find_errors(stack_t content) {
    stack_t ch = content;
    int mp = 0;
    Stack stack = vector_new();
    int lines = 1;
    stack_t line_start = ch;
    int error_quantity = 0;

    while (*ch != '\0') {
        switch (*ch)
        {
        case '>':
            mp++;
            break;
        case '<':
            mp--;
            if (mp < 0) {
                fprintf(stderr,"Undefined behaviour, at line: %d pos: %d by '%c'\n", lines, (int)(ch-line_start+1), *ch);
                error_quantity++;
                break;
            }
            break;
        case '[':
            vector_add(pointer(stack), ch);
            break;
        case ']':
            if (stack.size <= 0) {
                fprintf(stderr, "Missing '[' for closing, at line: %d col: %d by '%c'\n", lines, (int)(ch-line_start+1), *ch);
                error_quantity++;
                break;
            }
            vector_remove_last(pointer(stack));
            break;
        case '\n':
            lines++;
            line_start = ch+1;
            break;
        default:
            break;
        }
        ch++;
    }
    while (stack.size > 0) {
        ch = vector_peek(pointer(stack));
        vector_remove_last(pointer(stack));
        fprintf(stderr, "Missing ']' for closing, at pos: %d by '%c'\n",  (int)(ch-content+1), *ch);
        error_quantity++;
    }
    vector_destroy(pointer(stack));
    return error_quantity;
}


void brainfuck_run(unsigned char *string) {
    if (FIND_ERRORS_BEFORE_EXECUTING) {
        if (!brainfuck_find_errors(string)) {
            interpret_brainfuck(string);
        };
    } else {
        interpret_brainfuck(string);
    }
}

void brainfuck_run_from_file(const char *filepath) {
    stack_t file = read_file(filepath);
    brainfuck_run(file);
}
#endif