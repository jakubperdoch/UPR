#include "array.h"
#include <stdlib.h>
#include <assert.h>

void array_init(Array* self, const int element_size, const int capacity)
{
    self->data = malloc(sizeof(void*) * capacity);
    self->capacity = capacity;
    self->count = 0;
    self->element_size = element_size;
}

void* array_push(Array* self)
{
    void* v = NULL;
    v = malloc(self->element_size);
    if (self->capacity == self->count)
    {
        self->capacity = self->capacity * 2;
        self->data = realloc(self->data, self->capacity * sizeof(void*));
    }
    self->data[self->count] = v;
    self->count++;

    return v;
}

void* array_get(Array* self, int index)
{
    return self->data[index];
}

int array_size(const Array* self)
{
    return self->count;
}

void array_free(Array* self)
{
    for (int i = 0; i < self->count; i++)
    {
        free(self->data[i]);
        self->data[i] = NULL;
    }

    free(self->data);
    self->data = NULL;
}
