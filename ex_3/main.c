#include <stdio.h>


int sqr(const int x)
{
    return x * x;
}

int pow(const int x, const int y)
{
    int result = 1;
    for (int i = 1; i <= y; i++)
    {
        result *= x;
    }

    return result;
}


void rectangle()
{
    for (int i = 1; i <= 9; i++)
    {
        putchar('x');

        if (i % 3 == 0)
        {
            printf("\n");
        }
    }
}

int main(void)
{
    int a = 5;

    int* ptr = &a;

    printf("%d\n", *ptr);
    *ptr += 1;

    printf("%d\n", *ptr);
    *ptr += 1;

    printf("%d\n", *ptr);


    // int n = 3;
    //
    // for (int i = 1; i <= 3; i++)
    // {
    //     rectangle();
    //     printf("\n");
    // }

    // for (int i = 0; i < n; ++i)
    // {
    //     int sqrResult = sqr(i);
    //     int pwrResult = pow(i, 3);
    //
    //     printf("sqr(%d) = %d\n", i, sqrResult);
    //     printf("pow(%d, %d) = %d\n", i, 3, pwrResult);
    // }
}
