#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Sentence
{
    int lower_case;
    int upper_case;
    int spaces;
    char normalized_sentence[50];
};

void sentence_stats(struct Sentence* sentence)
{
}

void sentence_style(char substring[])
{
    bool is_uppercase = true;

    for (int i = 0; substring[i] != '\0'; i++)
    {
        if (isupper(substring[i]))
        {
            is_uppercase = false;
            break;
        }
    }

    if (is_uppercase)
    {
        for (int i = 0; substring[i] != '\0'; i++)
        {
            substring[i] = toupper(substring[i]);
        }
    }
    else
    {
        for (int i = 0; substring[i] != '\0'; i++)
        {
            substring[i] = tolower(substring[i]);
        }

        substring[0] = toupper(substring[0]);
    }
}

void sentence_trim(char substring[])
{
    for (int i = 0; substring[i] != '\0'; i++)
    {
        int position = strcspn(substring, &substring[i]);

        printf("%d", position);
    }
}

void sentence_normalize(struct Sentence* sentence)
{
    char* substr = strtok(sentence->normalized_sentence, " ");
    while (substr)
    {
        sentence->spaces++;
        sentence_style(substr);
        printf("%s", substr);
        if (strtok(NULL, " "))
        {
            printf(" ");
        }
        substr = strtok(NULL, " ");
    }
}


int main(void)
{
    int rows = 0;
    struct Sentence* sentences = NULL;
    char buff[50] = {};

    fgets(buff, sizeof buff, stdin);

    rows = atoi(buff);
    sentences = malloc(sizeof(struct Sentence) * rows);

    for (int i = 0; i < rows; i++)
    {
        char row[50] = {};
        fgets(row, sizeof row, stdin);
        row[strcspn(row, "\n")] = '\0';
        strcpy(sentences[i].normalized_sentence, row);
    }

    for (int i = 0; i < rows; i++)
    {
        sentence_normalize(&sentences[i]);
        // printf("Sentence[%d] = %s\n", i, sentences[i].normalized_sentence);
    }

    free(sentences);

    return 0;
}
