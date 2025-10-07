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

void gun_frame_1()
{
    set_black_color();

    //SIGHT
    move_right();
    move_right();
    draw_pixel();

    for (int j = 0; j < 18; j++)
    {
        move_right();
    }

    draw_pixel();
    move_down();
    return_to_position(20,true);

    //BODY
    for (int i = 0; i < 2; i++)
    {
        draw_horizontal_line(23,false);
        return_to_position(22,true);
        move_down();
    }

    move_right();
    move_right();
    draw_horizontal_line(19,false);
    return_to_position(16,true);


    //HANDLE
    move_down();
    for (int k = 0; k < 7; k++)
    {
        move_right();
    }
    draw_pixel();

    for (int j = 0; j < 2; j++)
    {
        move_down();
        move_left();
        draw_pixel();
    }

    move_left();
    draw_pixel();
    return_to_position(3,true);

    for (int j = 0; j < 3; ++j)
    {
        move_up();
    }

    for (int j = 0; j < 4; j++)
    {
        move_down();
        draw_pixel();
        move_right();
        draw_pixel();
        move_right();
        draw_pixel();
        return_to_position(2,true);
    }

    move_up();
    move_left();
    draw_pixel();
    move_down();
    draw_pixel();
}


void gun_frame_2()
{
    reset_color();
    draw_horizontal_line(22,false);

    return_to_position(20,true);
    set_black_color();
    draw_pixel();

    for (int j = 0; j < 14; j++)
    {
        move_right();
    }

    draw_pixel();
}

void gun_frame_3()
{
    set_red_color();

    move_to(4, 35);
    draw_horizontal_line(1,false);
    move_to(5, 33);
    draw_horizontal_line(4,false);
    move_to(6, 33);
    draw_horizontal_line(7,false);
    move_to(7, 33);
    draw_horizontal_line(3,false);

    set_yellow_color();
    move_to(4, 33);
    draw_horizontal_line(2,false);
    move_to(3, 35);
    draw_horizontal_line(1,false);

    move_to(4, 36);
    draw_horizontal_line(1,false);
    move_to(5, 37);
    draw_horizontal_line(3,false);

    move_to(8, 33);
    draw_horizontal_line(3,false);
    move_to(7, 36);
    draw_horizontal_line(4,false);

    move_to(6, 39);
    draw_horizontal_line(2,false);
}

void draw_bullet(int x, int y)
{
    move_to(y, x);

    set_white_color();
    draw_vertical_line(2,false);
    move_right();
    move_up();
    set_yellow_color();
    draw_vertical_line(2,false);
}


void draw_gun()
{
    move_to(4, 10);
    gun_frame_1();
    animate();
    move_to(4, 10);
    gun_frame_2();
    animate();
    gun_frame_3();

    for (int i = 0; i < 15; ++i)
    {
        draw_bullet(34 + i * 3, 5);
        animate_ms(200);
        clear_screen();
        move_to(4, 10);
        gun_frame_1();
    }
}


int main()
{
    clear_screen();
    move_to(0, 0);
    unsigned int interval = (unsigned int)time(NULL);
    srand(interval);

    int userInput = 0;
    scanf("%d", &userInput);

    switch (userInput)
    {
    case 0:
        set_random_color();
        draw_horizontal_line(5,true);
        move_to(5, 1);

        set_random_color();
        draw_horizontal_line(3,true);
        move_to(4, 10);

        set_random_color();
        draw_horizontal_line(10,true);
        break;
    case 1:
        draw_stairs(5);
        move_to(1, 15);
        draw_stairs(7);
        move_to(1, 32);
        draw_stairs(2);
        break;
    case 2:
        draw_flower(9, 12);
        move_to(1, 12);
        draw_flower(3, 4);
        move_to(4, 20);
        draw_flower(5, 7);
        break;
    case 3:
        draw_garden(5, 2);
        break;
    case 4:
        draw_gun();
        break;

    default:
        break;
    }

    end_drawing();
    return 0;
}
