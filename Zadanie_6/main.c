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

void sentence_style(char substring[], struct Sentence* sentence)
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
    for (int i = 0; substring[i] != '\0'; i++)
    {
        if (is_uppercase)
        {
            substring[i] = toupper(substring[i]);
        }
        else
        {
            substring[i] = tolower(substring[i]);
        }
    }

    if (is_uppercase) substring[0] = toupper(substring[0]);
}

void sentence_trim(char substring[])
{
    for (int i = 0; substring[i] != '\0'; i++)
    {
        if (substring[i] == substring[i + 1])
        {
            substring[i] = 8;
        }
    }
}

void sentence_normalize(struct Sentence* sentence)
{
    char temporary_sentence[50];
    strcpy(temporary_sentence, sentence->normalized_sentence);

    sentence->normalized_sentence[0] = '\0';

    char* substr = strtok(temporary_sentence, " ");
    while (substr)
    {
        sentence_trim(substr);
        sentence_style(substr, sentence);

        if (strlen(sentence->normalized_sentence) > 0)
        {
            strcat(sentence->normalized_sentence, " ");
        }
        strcat(sentence->normalized_sentence, substr);
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
        printf("%s\n", sentences[i].normalized_sentence);
    }

    free(sentences);

    return 0;
}
