// vector.h
#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
// do not forget to initialize it
typedef unsigned char vector_t;

typedef struct Vector {
    vector_t *start;
    size_t size;
    size_t capacity;
} Vector;


void vector_printn(Vector *v, const char *name) {
    printf("Vector: %s\n| size: %lu\n| capacity: %lu\n| contents: ", name, v->size, v->capacity);
    for (int i = 0; i < v->size; i++) {
        printf("%d ", *(v->start+i));
    }
    putchar('\n');
}

#define vector_print(v, name) vector_printn(&v, name)

Vector vector_new() {
    return (Vector) {
        .start = NULL,
        .size = 0,
        .capacity = 0
    };
}

void vector_destroy(Vector *vector) {
    free(vector->start);
    vector->capacity = 0;
    vector->size = 0;
}



void vector_resize(Vector *vector, size_t new_size) {
    if (new_size > vector->capacity) { 
        vector->capacity = new_size * 2;  
        vector->start = (vector_t *)realloc(vector->start, vector->capacity * sizeof(vector->start));
        assert((new_size-vector->size > 0));
        // v {s: 2, c: 2} (4) -> v {s: 2, c: 4}
        // go to end, 0, new capacity
        memset(vector->start+vector->size, 0, sizeof(vector_t)*(vector->capacity));
    }
    for (int i = vector->size; i < vector->capacity; i++) {
        assert(((vector->start+i) == 0) && "Not zero initialized");
    }
    vector->size = new_size;
}

void vector_add(Vector *vector, vector_t value) {
    vector_resize(vector, vector->size+1);
    vector_t *new_value_loc = vector->start+vector->size-1;
    *new_value_loc = value;
}


vector_t *vector_at(Vector *v, size_t i) {
    return (v->start+i);
}


Vector vector_copy(const Vector *v1) {
    Vector v2 = {0};
    v2.size = v1->size;
    v2.capacity = v1->capacity;

    v2.start = (vector_t*)malloc(v2.capacity*sizeof(vector_t));
    memcpy(v2.start, v1->start, sizeof(vector_t)*v1->capacity);
    return v2;
}

#endif