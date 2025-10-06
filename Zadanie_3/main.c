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

void draw_horizontal_line(int length,bool dashed)
{
    for (int i = 0; i < length; i++)
    {
        draw_pixel();
        if (i + 1 < length)
        {
            move_right();
            if (dashed)
            {
                move_right();
            }
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
        draw_vertical_line(3,false);
    }
}

void draw_flower(int width, int height)
{
    set_blue_color();
    const int middle = width / 2;
    const int stem = height - width;

    //KVET
    for (int i = 0; i < width; i++)
    {
        if (i == 0 || i == width - 1)
        {
            draw_horizontal_line(width,false);
        }
        else
        {
            draw_horizontal_line(width,false);
            set_yellow_color();
            draw_horizontal_line(width,false);
        }

        set_blue_color();
        move_down();
    }

    //STONKA
    for (int j = 0; j < middle; j++)
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
    move_to(2, 0);
    draw_flower(5, 6);

    move_to(2, 30);
    draw_flower(5, 6);
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
        draw_flower(5, 6);
        break;
    case 4:
        draw_garden(5, 6);
        break;
    default:
        break;
    }

    end_drawing();

    return 0;
}
