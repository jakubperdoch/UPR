#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    char match[60];
    char buffer[60];
    char* input;
    bool matchFound = false;

    match[0] = '\0';

    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    input = strtok(buffer, " ");
    input = strtok(NULL, " ");


    while (fgets(buffer, sizeof(buffer), stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        for (int i = 0; i < strlen(input); i++)
        {
            if (tolower(input[i]) == tolower(buffer[i]) && strlen(match) < strlen(input))
            {
                matchFound = true;
            }
            else
            {
                matchFound = false;
                break;
            }
        }

        if (matchFound)
        {
            strcpy(match, buffer);
        }
    }

    printf("%s\n", match);

    return 0;
}
