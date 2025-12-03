#include <stdio.h>
#include "array.h"

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
