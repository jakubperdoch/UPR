#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Turtle
{
    int row;
    int column;
    int direction;
};

void array_print(const char* array, const int rows, const int columns)
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            printf("%c", array[row * columns + column]);
        }
        printf("\n");
    }
}


void add_turtle(struct Turtle** current_turtles, int* num_turtles)
{
    *num_turtles += 1;
    struct Turtle* turtles = realloc(*current_turtles, *num_turtles * sizeof(struct Turtle));
    struct Turtle t = {0, 0, 1};
    turtles[*num_turtles - 1] = t;
    *current_turtles = turtles;
}

void move_turtle(struct Turtle** current_turtles, int num_turtles)
{
    for (int i = 0; i < num_turtles; i++)
    {
        struct Turtle* turtle = current_turtles[i];
        if (turtle->direction == 1)
        {
        }
    }
}


int main(void)
{
    int rows = 0, cols = 0;
    struct Turtle* turtles = NULL;
    int num_turtles = 0;
    scanf("%d %d", &rows, &cols);

    char* array = malloc(rows * cols * sizeof(char));
    add_turtle(&turtles, &num_turtles);

    for (int i = 0; i < rows * cols; i++)
    {
        array[i] = '.';
    }

    array_print(array, rows, cols);

    while (true)
    {
        char command;
        scanf("%c", &command);

        if (command == 'f' && num_turtles < 3)
        {
            add_turtle(&turtles, &num_turtles);
            array_print(array, rows, cols);
        }
        else if (command == 'x')
        {
            break;
        }
    }

    array_print(array, rows, cols);


    free(array);
    free(turtles);

    return 0;
}
