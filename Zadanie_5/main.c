#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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

void obstacles_generate(char* array, const int rows, const int columns)
{
    int array_size = rows * columns;
    int num_obstacles = array_size / 5;
    for (int i = 0; i < num_obstacles; i++)
    {
        int rand_idx = rand() % array_size;
        if (array[rand_idx] == '#') { i--; }
        else { array[rand_idx] = '#'; }
    }
}

void turtle_add(struct Turtle** turtles, int* num_turtles)
{
    int temporary_count = *num_turtles + 1;
    struct Turtle* temporary_turtles = realloc(*turtles, temporary_count * sizeof(struct Turtle));
    temporary_turtles[temporary_count - 1] = (struct Turtle){0, 0, 1};
    *turtles = temporary_turtles;
    *num_turtles = temporary_count;
}

void turtle_move(struct Turtle* turtles, const int num_turtles, const char* array, const int rows, const int cols)
{
    for (int i = 0; i < num_turtles; i++)
    {
        struct Turtle* turtle = &turtles[i];
        int next_row = turtle->row;
        int next_col = turtle->column;

        if (turtle->direction == 0) next_row -= 1;
        else if (turtle->direction == 1) next_col += 1;
        else if (turtle->direction == 2) next_row += 1;
        else if (turtle->direction == 3) next_col -= 1;

        if (next_col < 0) next_col = cols - 1;
        if (next_col >= cols) next_col = 0;
        if (next_row < 0) next_row = rows - 1;
        if (next_row >= rows) next_row = 0;

        if (array[next_row * cols + next_col] != '#')
        {
            turtle->row = next_row;
            turtle->column = next_col;
        }
    }
}

void turtle_turn(struct Turtle* turtles, const int num_turtles, const char command)
{
    for (int i = 0; i < num_turtles; i++)
    {
        if (command == 'l') turtles[i].direction = (turtles[i].direction + 3) % 4;
        else if (command == 'r') turtles[i].direction = (turtles[i].direction + 1) % 4;
    }
}

void turtle_write(const struct Turtle* turtles, char* array, const int num_turtles, const int cols)
{
    for (int i = 0; i < num_turtles; i++)
    {
        int index = turtles[i].row * cols + turtles[i].column;
        array[index] = (array[index] == 'o') ? '.' : 'o';
    }
}


int main(void)
{
    int rows = 0, cols = 0;
    struct Turtle* turtles = NULL;
    int num_turtles = 0;
    scanf("%d %d", &rows, &cols);

    char* array = malloc(rows * cols * sizeof(char));
    turtle_add(&turtles, &num_turtles);

    for (int i = 0; i < rows * cols; i++)
    {
        array[i] = '.';
    }
    // obstacles_generate(array, rows, cols);
    array[0] = '.';

    char command;


    while (true)
    {
        scanf("%c", &command);

        if (command == 'f' && num_turtles < 3)
        {
            turtle_add(&turtles, &num_turtles);
        }
        else if (command == 'm')
        {
            turtle_move(turtles, num_turtles, array, rows, cols);
        }
        else if (command == 'r' || command == 'l')
        {
            turtle_turn(turtles, num_turtles, command);
        }
        else if (command == 'o')
        {
            turtle_write(turtles, array, num_turtles, cols);
        }
        else if (command == 'x')
        {
            array_print(array, rows, cols);
            break;
        }
    }

    free(array);
    free(turtles);

    return 0;
}
