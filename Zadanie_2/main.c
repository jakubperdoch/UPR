#include <stdio.h>
#include <stdbool.h>

// helper function

void print_loop(int a, char c)
{
    for (int j = 0; j < a; j++)
    {
        printf("%c", c);
    }
}

// Rectangles

void rectangle(int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        print_loop(width, 'x');
        printf("\n");
    }
}

void filled_rectangle(int width, int height,bool fillNumbers)
{
    int counter = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1))
            {
                putchar('x');
            }
            else
            {
                if (fillNumbers)
                {
                    printf("%d", counter % 10);
                    counter++;
                }
                else
                {
                    putchar(' ');
                }
            }
        }
        printf("\n");
    }
}

// Diagonals

void diagonal(int size)
{
    for (int i = 0; i < size; i++)
    {
        print_loop(i, ' ');

        putchar('x');
        printf("\n");
    }
}

void reversed_diagonal(int size)
{
    for (int i = 0; i < size; i++)
    {
        print_loop(size - i - 1, ' ');
        putchar('x');

        print_loop(i, ' ');
        printf("\n");
    }
}

// Triangle

void triangle(int size)
{
    for (int i = 0; i < size; i++)
    {
        print_loop(size - i - 1, ' ');

        if (i == 0)
        {
            putchar('x');
        }
        else if (i == size - 1)
        {
            print_loop(2 * size - 1, 'x');
        }
        else
        {
            putchar('x');
            print_loop(2 * i - 1, ' ');
            putchar('x');
        }

        print_loop(size - i - 1, ' ');
        printf("\n");
    }
}

// Letters

void letter_t(int width, int height)
{
    print_loop(width, 'x');
    printf("\n");

    for (int j = 0; j < height - 1; j++)
    {
        print_loop((width - 1) / 2, ' ');
        printf("x\n");
    }
}

void letter_p(int width, int height)
{
    int length = height / 2;

    for (int i = 0; i < height - length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bool top_or_mid = (i == 0 || i == length);
            bool left_or_right = (j == 0 || j == width - 1);

            if (top_or_mid || left_or_right)
            {
                putchar('x');
            }
            else
            {
                putchar(' ');
            }
        }
        printf("\n");
    }

    for (int i = 0; i < length; i++)
    {
        putchar('x');
        print_loop(width - 1, ' ');
        printf("\n");
    }
}

// Bonus *

void bonus_quest(int width, int height)
{
    int innerHeight = height - 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1))
            {
                putchar('x');
            }
            else
            {
                printf("%d", (i - 1 + innerHeight * (j - 1)) % 10);
            }
        }
        printf("\n");
    }
}

int main()
{
    int obrazec = 0;
    int a = 0;
    int b = 0;

    scanf("%d%d%d", &obrazec, &a, &b);

    switch (obrazec)
    {
    case 0:
        rectangle(a, b);
        break;
    case 1:
        filled_rectangle(a, b, false);
        break;
    case 2:
        filled_rectangle(a, b,true);
        break;
    case 3:
        diagonal(a);
        break;
    case 4:
        reversed_diagonal(a);
        break;
    case 5:
        triangle(a);
        break;
    case 6:
        letter_t(a, b);
        break;
    case 7:
        letter_p(a, b);
        break;
    case 9:
        bonus_quest(a, b);
        break;
    default:
        printf("Neznamy obrazec\n");
    }

    return 0;
}
