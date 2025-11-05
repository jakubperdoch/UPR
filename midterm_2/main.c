#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int rows = 0;
    char buffer[50];
    char symbol;

    fgets(buffer, sizeof buffer, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    symbol = buffer[strlen(buffer) - 1];

    fgets(buffer, sizeof buffer, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    rows = atoi(buffer);

    for (int i = 0; i < rows; i++)
    {
        char out[300];
        int out_i = 0;

        fgets(buffer, sizeof buffer, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        for (int j = 0; j < buffer[j] != '\0'; j++)
        {
            if (tolower(buffer[j]) == tolower(symbol))
            {
                out[out_i++] = 'x';
                out[out_i++] = 'x';
                out[out_i++] = 'x';
            }
            else
            {
                out[out_i++] = buffer[j];
            }
        }

        out[out_i] = '\0';
        printf("%s\n", out);
    }
    return 0;
}
