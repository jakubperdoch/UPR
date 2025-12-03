#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>

typedef struct Array
{
    void** data;
    int capacity;
    int count;
    int element_size;
} Array;


void array_init(Array* self, const int element_size, const int capacity);
void array_free(Array* self);
void* array_push(Array* self);
void* array_get(Array* self, int index);
int array_size(const Array* self);

#endif //AARRAY_H
