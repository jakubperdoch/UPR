#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int rows = 0, word_length = 0;
    char previous_word[50] = "none";
    char buffer[50];

    fgets(buffer, sizeof buffer, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    word_length = atoi(&buffer[strlen(buffer) - 1]);

    fgets(buffer, sizeof buffer, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    rows = atoi(buffer);


    for (int i = 0; i < rows; i++)
    {
        fgets(buffer, sizeof buffer, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) >= word_length)
        {
            printf("%s (%s)\n", buffer, previous_word);
        }
        else
        {
            printf("%s (none)\n", buffer);
        }
        strcpy(previous_word, buffer);
    }
    return 0;
}
