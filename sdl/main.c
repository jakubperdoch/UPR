#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void** data;
    int capacity;
    int count;
    int element_size;
} Array;

int array_size(const Array* self);

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

int main(void)
{
    Array inst;
    array_init(&inst, sizeof(int), 2);
    int* i1 = array_push(&inst);
    *i1 = 1;
    int* i2 = array_push(&inst);
    *i2 = 2;
    int* i3 = array_push(&inst);
    *i3 = 3;

    for (int i = 0; i < array_size(&inst); i++)
    {
        printf("%d = %d\n", i, *(int*)array_get(&inst, i));
    }

    array_free(&inst);

    return 0;
}
