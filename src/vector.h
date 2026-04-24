// vector.h
#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// typedef struct Vector {
//     vector_t *start;
//     size_t size;
//     size_t capacity;
// } Vector;

#define vector_create(name, type) typedef struct {\
    type *start;\
    size_t size;\
    size_t capacity;\
} name

#define vr(v,s)do{size_t c=v->capacity;if(s>c){size_t n;if(c==0)n=2;else n=c*2;while(n<s)n*=2;v->start=realloc(v->start,n*sizeof(*v->start));memset(v->start+c,0,sizeof(*v->start)*(n-c));v->capacity=n;}else if(s<v->size){memset(v->start+s,0,sizeof(*v->start)*(v->size-s));}v->size=s;}while(0)

#define vadd(v, i)do{vr(v,v->size+1);(*(v->start+v->size-1))=i;}while(0)


#define vector_add(vector, value) vadd(vector, value)
#define vector_resize(vector,value) vr(vector, value)



#define vector_printn(v,name) {\
    printf("Vector: %s\n| size: %lu\n| capacity: %lu\n| contents: ", name, v->size, v->capacity);\
    for (int i = 0; i < v->size; i++) {\
        printf("%d ", *(v->start+i));\
    }\
    putchar('\n');\
}
#define vector_print(v, name) vector_printn(&v, name)

#define vector_printAlln(v,  name) \
    printf("Vector: %s\n| size: %lu\n| capacity: %lu\n| contents: ", name, v->size, v->capacity);\
    for (int i = 0; i < v->capacity; i++) {\
        printf("%d ", *(v->start+i));\
    }\
    putchar('\n');\
    
#define vector_printAll(v, name) vector_printAlln((&v), name)

#define vector_new() {0}

#define vector_destroy(vector) do{\
    free(vector->start);\
    vector->capacity = 0;\
    vector->size = 0;\
}while(0)

#define vector_at(v, i) ((v)->start+i)
#define pointer(v) (&v)
#define vector_peek(s) *vector_at(s, s->size-1)
#define vector_remove_last(s) do{vector_peek(s) = 0;s->size-=1;}while(0)


#endif
// stack_t stack_pop(Stack *stack) {
    //     if (stack->size == 0) {
        //         return NULL;
//     }

//     stack_t *end = stack_pointer_at(stack, stack->size-1);
//     stack_t ch = *end;
//     end = NULL;
//     stack_resize(stack, stack->size-1);
//     return ch;
// }

// stack_t stack_peek(Stack *stack) {
//     return *stack_pointer_at(stack, stack->size-1);
// }
