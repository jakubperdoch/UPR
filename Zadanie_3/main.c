#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "drawing.h"

void set_random_color()
{
    int r = rand() % 6;

    if (r == 0)
        set_black_color();
    else if (r == 1)
        set_blue_color();
    else if (r == 2)
        set_red_color();
    else if (r == 3)
        set_green_color();
    else if (r == 4)
        set_yellow_color();
    else
        set_white_color();
}

void return_to_position(int steps,bool left)
{
    for (int i = 0; i < steps; i++)
    {
        if (left)
        {
            move_left();
        }
        else
        {
            move_right();
        }
    }
}

void draw_horizontal_line(int length,bool dashed)
{
    for (int i = 0; i < length; i++)
    {
        draw_pixel();
        if (i + 1 < length)
        {
            move_right();
            if (dashed)
                move_right();
        }
    }
}

void draw_vertical_line(int length,bool dashed)
{
    for (int i = 0; i < length; i++)
    {
        draw_pixel();
        if (i + 1 < length)
        {
            move_down();
            if (dashed)
                move_down();
        }
    }
}

void draw_stairs(int count)
{
    set_random_color();

    for (int i = 0; i < count; i++)
    {
        draw_horizontal_line(6,false);

        if (i + 1 < count)
        {
            draw_vertical_line(2,false);
        }
    }
}

void draw_flower(int width, int height)
{
    int middle = width / 2;
    int fill = width - 2;
    int stem = height - width;

    //FLOWER
    for (int i = 0; i < width; ++i)
    {
        set_blue_color();
        if (i == 0 || i == width - 1)
        {
            //TOP & BOTTOM
            move_right();
            draw_horizontal_line(width - 2,false);
            return_to_position(width - 2,true);
        }
        else
        {
            //BLUE BORDERS
            draw_horizontal_line(width,false);
            return_to_position(width - 1,true);

            // WHITE FILL
            move_right();
            set_white_color();
            draw_horizontal_line(fill,false);
            return_to_position(fill,true);
        }

        move_down();
    }

    //STEM
    for (int j = 0; j < width / 2; j++)
    {
        move_right();
    }

    set_green_color();

    for (int j = 0; j < stem; j++)
    {
        draw_pixel();
        move_down();
    }
}

void draw_garden(int columns, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int column = 1;
        int line = (i * 8) + 2;

        for (int j = 0; j < columns; j++)
        {
            move_to(line, column);
            draw_flower(3, 5);
            column += 8;
        }
    }
}

int main()
{
    clear_screen();
    move_to(0, 0);
    srand((int)time(NULL));

    int userInput = 0;
    scanf("%d", &userInput);

    switch (userInput)
    {
    case 1:
        set_random_color();
        draw_horizontal_line(5,true);
        break;
    case 2:
        draw_stairs(5);
        break;
    case 3:
        draw_flower(9, 12);
        break;
    case 4:
        draw_garden(5, 2);
        break;
    default:
        break;
    }

    end_drawing();

    return 0;
}
