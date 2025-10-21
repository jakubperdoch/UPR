#include <stdio.h>
#include <stdlib.h>

void null_array(int array[], const int len)
{
    for (int i = 0; i < len; i++)
    {
        array[i] = 0;
        printf("array[%d] = %d\n", i, array[i]);
    }
}

void array_print_reverse(int* array, const int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%d ", array[i]);
    }
}

void array_average(int* array, const int len)
{
    int sum = 0;
    float result = 0;

    for (int i = 0; i < len; i++)
    {
        sum += array[i];
    }

    result = (float)sum / len;
    printf("%f", result);
}

void array_min_max(int* array, const int len, int* min, int* max)
{
    if (!array)
    {
        return;
    }

    *max = 0;
    *min = 0;

    for (int i = 0; i < len; i++)
    {
        if (array[i] > *max)
        {
            *max = array[i];
        }

        if (array[i] < *min)
        {
            *min = array[i];
        }
    }
}

void array_pos_neg_zero(int* array, const int len, int* pos, int* neg, int* zero)
{
    if (!array)
    {
        return;
    }

    *pos = 0;
    *neg = 0;
    *zero = 0;

    for (int i = 0; i < len; i++)
    {
        if (array[i] > 0)
        {
            *pos += 1;
        }
        else if (array[i] < 0)
        {
            *neg += 1;
        }
        else
        {
            *zero += 1;
        }
    }
}

//Pointer-na-pointer
void array_free(int** array)
{
    if (*array)
    {
        free(*array);
        *array = NULL;
    }
}

int* array_alloc(const int len)
{
    int* array = NULL;
    array = (int*)malloc(len * sizeof(int));
    if (!array)
    {
        exit(-1);
    }
    return array;
}

int dot_product(const int* a, const int* b, const int len)
{
    int sum = 0;

    for (int i = 0; i < len; i++)
    {
        sum += a[i] * b[i];
    }

    return sum;
}

int index_2d_na_1d(int radek, int sloupec, int sirka)
{
    return radek * sirka + sloupec;
}

void matrix_print(const int* m, const int rows, const int cols)
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            int id = index_2d_na_1d(row, col, cols);
            printf("%d ", m[id]);
        }

        printf("\n");
    }
}


int main(void)
{
    // int N = 7;
    // int* array = array_alloc(N);
    //
    // array[0] = -1;
    // array[1] = 2;
    // array[2] = 3;

    // null_array(array, N);

    // array_free(&array);

    // array_print_reverse(array, N);
    // array_average(array, N);

    // array_min_max(array, N, &min, &max);
    // printf("min = %d, max = %d\n", min, max);

    // array_pos_neg_zero(array, N, &pos, &neg, &zero);
    // printf("POS:%d, NEG:%d, ZERO:%d", pos, neg, zero);


    // int N = 4;
    // const int len = 3;
    // int vec2[] = {1, 1, 1};
    //
    // int d = dot_product(vec1, vec2, len);
    // printf("d = %d\n", d);

    const int rows = 3, col = 3;
    int vec1[] = {1, 2, 3};
    int m[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // matrix_print(m, rows, col);

    return 0;
}
