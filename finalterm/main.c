#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    int year;
    char* subject;
    char* login;
    char* homework;
    int score;
} Record;

typedef struct
{
    int year;
    int count;
    Record* records;
}
Semester;

void addRecord(Semester* semester, char* data)
{
    Record* record = malloc(sizeof(Record));
    record->id = atoi(strtok(data, ";"));
    record->year = atoi(strtok(NULL, ";"));
    record->subject = strtok(NULL, ";");
    record->login = strtok(NULL, ";");
    record->homework = strtok(NULL, ";");
    record->score = atoi(strtok(NULL, ";"));
    semester->records = realloc(semester->records, (semester->count + 1) * sizeof(Record));
    semester->records[semester->count] = *record;
    semester->count++;
    free(record);
}

void printRecord(Record* record)
{
    printf("ID %d: rok %d, predmet %s, login %s, ukol %s, body %d\n", record->id, record->year, record->subject,
           record->login,
           record->homework,
           record->score);
}

void checkSemester(Semester** semesters, int* count, int year, char* data)
{
    for (int i = 0; i < *count; ++i)
    {
        if ((*semesters)[i].year == year)
        {
            addRecord(&(*semesters)[i], data);
            return;
        }
    }

    Semester* tmp = realloc(*semesters, (*count + 1) * sizeof(Semester));
    if (!tmp)
    {
        perror("realloc");
        exit(1);
    }

    *semesters = tmp;

    (*semesters)[*count].year = year;
    (*semesters)[*count].records = NULL;
    (*semesters)[*count].count = 0;
    addRecord(&(*semesters)[*count], data);
    (*count)++;
}


int main(const int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Invalid arguments.");
        return 1;
    }

    Semester* semesters = NULL;
    int semCount = 0;
    char buff[100];
    int rows = atoi(argv[1]);

    for (int i = 0; i < rows; ++i)
    {
        int year;
        char tmp[256];

        fgets(buff, sizeof buff, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        strncpy(tmp, buff, sizeof(tmp));
        tmp[sizeof(tmp) - 1] = '\0';

        char* token = strtok(tmp, ";");
        token = strtok(NULL, ";");
        year = atoi(token);

        checkSemester(&semesters, &semCount, year, buff);
    }

    for (int i = 0; i < semCount; ++i)
    {
        printf("Zaznamy roku %d\n", semesters[i].year);
        for (int j = 0; j < semesters[i].count; ++j)
        {
            printRecord(&semesters[i].records[j]);
        }
    }

    for (int i = 0; i < semCount; ++i)
    {
        for (int j = 0; j < semesters[i].count; ++j)
        {
            free(semesters[i].records[j].subject);
            free(semesters[i].records[j].login);
            free(semesters[i].records[j].homework);
        }
        free(semesters[i].records);
    }
    free(semesters);
    return 0;
}
