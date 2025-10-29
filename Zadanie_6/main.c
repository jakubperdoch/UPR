#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Sentence_ Sentence;

typedef struct
{
    int lower_case;
    int upper_case;
    int spaces;
} Stats;

struct Sentence_
{
    Stats stats;
    Stats stats_normalized;
    char normalized_sentence[50];
};


void sentence_stats(Sentence* self, const bool is_normalized)
{
    for (int i = 0; self->normalized_sentence[i] != '\0'; i++)
    {
        char c = self->normalized_sentence[i];
        if (islower(c))
        {
            is_normalized ? self->stats_normalized.lower_case++ : self->stats.lower_case++;
        }
        else if (isupper(c))
        {
            is_normalized ? self->stats_normalized.upper_case++ : self->stats.upper_case++;
        }
        else if (isspace(c))
        {
            is_normalized ? self->stats_normalized.spaces++ : self->stats.spaces++;
        }
    }
}

void substring_style(char substring[], Sentence* self)
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

    if (!is_uppercase) substring[0] = toupper(substring[0]);
}

void substring_trim(char substring[])
{
    int w = 0;

    for (int i = 0; substring[i] != '\0'; i++)
    {
        if (i == 0 || substring[i] != substring[i - 1])
        {
            substring[w++] = substring[i];
        }
    }
    substring[w] = '\0';
}

void sentence_normalize(Sentence* self)
{
    char temporary_sentence[50];
    strcpy(temporary_sentence, self->normalized_sentence);

    self->normalized_sentence[0] = '\0';

    char* substr = strtok(temporary_sentence, " ");
    while (substr)
    {
        substring_style(substr, self);
        substring_trim(substr);

        if (strlen(self->normalized_sentence) > 0)
        {
            strcat(self->normalized_sentence, " ");
        }
        strcat(self->normalized_sentence, substr);
        substr = strtok(NULL, " ");
    }
}


int main(void)
{
    int rows = 0;
    Sentence* sentences = NULL;
    char buff[50] = {};

    fgets(buff, sizeof buff, stdin);

    rows = atoi(buff);
    sentences = malloc(sizeof(Sentence) * rows);

    for (int i = 0; i < rows; i++)
    {
        char row[50] = {};
        fgets(row, sizeof row, stdin);
        row[strcspn(row, "\n")] = '\0';
        strcpy(sentences[i].normalized_sentence, row);
    }

    for (int i = 0; i < rows; i++)
    {
        sentence_stats(&sentences[i],false);
        sentence_normalize(&sentences[i]);
        sentence_stats(&sentences[i],true);
        printf("%s\n", sentences[i].normalized_sentence);
        printf("lowercase: %d -> %d\n", sentences[i].stats.lower_case, sentences[i].stats_normalized.lower_case);
        printf("uppercase: %d -> %d\n", sentences[i].stats.upper_case, sentences[i].stats_normalized.upper_case);
        printf("spaces: %d -> %d\n", sentences[i].stats.spaces, sentences[i].stats_normalized.spaces);
        if (i < rows - 1) printf("\n");
    }

    free(sentences);

    return 0;
}
