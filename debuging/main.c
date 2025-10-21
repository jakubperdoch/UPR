#include <stdio.h>

void null_array(int array[])
{

    for (int i = 0; i < len; i++)
    {
        array[i] = 0;
        printf("%d ", array[i]);
    }
}

int main(void)
{
    int N = 5;
    int array[] = {1, 2, 3, 4, 5,};
    null_array(array, N);

    return 0;
}
