#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Turtle
{
    int row;
    int column;
    int direction;
};

void array_print(char* array, int num_turtles, struct Turtle* turtles, const int rows, const int columns)
{
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            char symbol = array[row * columns + column];
            for (int index = 0; index < num_turtles; index++)
            {
                if (turtles[index].row == row && turtles[index].column == column)
                {
                    symbol = 'z';
                    break;
                }
            }
            printf("%c", symbol);
        }
        printf("\n");
    }
}

void add_turtle(struct Turtle** current_turtles, int* num_turtles)
{
    int temporary_count = *num_turtles + 1;
    struct Turtle* temporary_turtles = realloc(*current_turtles, temporary_count * sizeof(struct Turtle));
    temporary_turtles[temporary_count - 1] = (struct Turtle){0, 0, 1};
    *current_turtles = temporary_turtles;
    *num_turtles = temporary_count;
}

void move_turtle(struct Turtle* turtles, int num_turtles, int rows, int cols)
{
    for (int i = 0; i < num_turtles; i++)
    {
        struct Turtle* turtle = &turtles[i];
        if (turtle->direction == 0) turtle->row -= 1;
        else if (turtle->direction == 1) turtle->column += 1;
        else if (turtle->direction == 2) turtle->row += 1;
        else if (turtle->direction == 3) turtle->column -= 1;

        if (turtle->column < 0) turtle->column = cols - 1;
        if (turtle->column >= cols) turtle->column = 0;
        if (turtle->row < 0) turtle->row = rows - 1;
        if (turtle->row >= rows) turtle->row = 0;
    }
}

void turn_turtle(struct Turtle* turtles, int num_turtles, char command)
{
    for (int i = 0; i < num_turtles; i++)
    {
        if (command == 'l') turtles[i].direction = (turtles[i].direction + 3) % 4;
        else if (command == 'r') turtles[i].direction = (turtles[i].direction + 1) % 4;
    }
}

void draw_turtle(const struct Turtle* turtles, char* array, int num_turtles, int cols)
{
    for (int i = 0; i < num_turtles; i++)
    {
        int index = turtles[i].row * cols + turtles[i].column;
        array[index] = (array[index] == '0') ? '.' : '0';
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

    array_print(array, num_turtles, turtles, rows, cols);

    char command;

    //TODO:
    while (true)
    {
        scanf("%c", &command);

        if (command == 'f' && num_turtles < 3)
        {
            add_turtle(&turtles, &num_turtles);
            array_print(array, num_turtles, turtles, rows, cols);
        }
        else if (command == 'm')
        {
            move_turtle(turtles, num_turtles, rows, cols);
            array_print(array, num_turtles, turtles, rows, cols);
        }
        else if (command == 'r' || command == 'l')
        {
            turn_turtle(turtles, num_turtles, command);
            array_print(array, num_turtles, turtles, rows, cols);
        }
        else if (command == 'o')
        {
            draw_turtle(turtles, array, num_turtles, cols);
            array_print(array, num_turtles, turtles, rows, cols);
        }
        else if (command == 'x')
        {
            break;
        }
    }

    array_print(array, num_turtles, turtles, rows, cols);

    free(array);
    free(turtles);

    return 0;
}
