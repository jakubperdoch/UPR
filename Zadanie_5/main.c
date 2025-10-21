#include <stdio.h>
#include <stdlib.h>

struct Turtle
{
    const int id;
    int row;
    int column;
    int angle;
};

void print_array(const char* array, const int* rows, const int* columns)
{
    for (int i = 0; i < *rows; i++)
    {
        for (int j = 0; j < *columns; j++)
        {
            printf("%c", array[i * (*columns) + j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int rows = 0, cols = 0;
    scanf("%d %d", &rows, &cols);

    char* array = malloc(rows * cols * sizeof(char));

    for (int i = 0; i < rows * cols; i++)
    {
        array[i] = '.';
    }

    print_array(array, &rows, &cols);

    free(array);

    return 0;
}
