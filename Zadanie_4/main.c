#include <stdio.h>

void initialize(int* min, int* max, const int* range, int* invalid, int histogram[], const int* count)
{
    int user_input;

    *min = *range;
    *max = *range + 8;

    for (int i = 0; i < *count; i++)
    {
        scanf("%d", &user_input);
        if (user_input >= *min && user_input <= *max)
        {
            histogram[user_input - *min]++;
        }
        else
        {
            (*invalid)++;
        }
    }
}

void print_histogram(int* min, int* max, int* invalid, int histogram[])
{
    for (int i = 0; i < 9; i++)
    {
        int rowValue = histogram[i];
        int number_of_spaces = 0;

        for (int j = *max; j > 0; j /= 10)
        {
            number_of_spaces++;
        }

        for (int j = *min + i; j > 0; j /= 10)
        {
            number_of_spaces--;
        }

        for (int k = 0; (k < number_of_spaces && *min + i != 0); k++)
        {
            putchar(' ');
        }

        if (rowValue > 0)
        {
            printf("%d ", *min + i);
        }
        else
        {
            printf("%d", *min + i);
        }

        for (int j = 0; j < rowValue; j++)
        {
            putchar('#');
        }
        putchar('\n');
    }

    if (*invalid > 0)
    {
        printf("invalid: ");
        for (int i = 0; i < *invalid; i++)
        {
            putchar('#');
        }
        putchar('\n');
    }
}

void print_histogram_vertical(int* min, int* invalid, int histogram[])
{
    int highest_value = *invalid;

    for (int i = 0; i < 9; i++)
    {
        if (highest_value < histogram[i])
        {
            highest_value = histogram[i];
        }
    }

    for (int i = highest_value; i >= 0; i--)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    printf("i");
                }
                else
                {
                    printf("%d", *min + j - 1);
                }
            }
            else if (i <= histogram[j - 1] || (j == 0 && i <= *invalid))
            {
                putchar('#');
            }
            else
            {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

int main(void)
{
    char selection;
    int histogram[9] = {0};
    int count = 0, range, min, max, invalid = 0;

    scanf("%c", &selection); //selection=vertical/horizontal
    scanf("%d", &count); // n
    scanf("%d", &range); // m

    initialize(&min, &max, &range, &invalid, histogram, &count);

    switch (selection)
    {
    case 'h':
        print_histogram(&min, &max, &invalid, histogram);
        break;
    case 'v':
        print_histogram_vertical(&min, &invalid, histogram);
        break;
    default:
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    return 0;
}
