#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

typedef struct
{
    int id;
    char* login;
    char* name;
    char* surname;
} User;

typedef struct
{
    int id;
    char* name;
    int points;
} Task;

User* user_new(const int id, const char* login, const char* name, const char* surname)
{
    User* user = malloc(sizeof(User));
    if (!user) return NULL;

    user->id = id;
    user->login = strdup(login);
    user->name = strdup(name);
    user->surname = strdup(surname);

    return user;
}

User* parse_user(char* line)
{
    char* id_str = strtok(line, ";");
    int id = atoi(id_str);
    char* login = strtok(NULL, ";");
    char* name = strtok(NULL, ";");
    char* surname = strtok(NULL, ";");

    User* user = user_new(id, login, name, surname);
    return user;
}

void user_free(User** self)
{
    if (*self != NULL)
    {
        free((*self)->login);
        free((*self)->name);
        free((*self)->surname);
        free(*self);

        *self = NULL;
    }
}

Task* task_new(const int id, const char* name, const int points)
{
    Task* task = malloc(sizeof(Task));
    if (!task) return NULL;
    task->id = id;
    task->name = strdup(name);
    task->points = points;

    return task;
}

Task* parse_task(char* line)
{
    char* id_str = strtok(line, ";");
    int id = atoi(id_str);
    char* name = strtok(NULL, ";");
    int points = atoi(strtok(NULL, "\n"));

    Task* task = task_new(id, name, points);
    return task;
}

void task_free(Task** self)
{
    if (*self != NULL)
    {
        free((*self)->name);
        free(*self);

        *self = NULL;
    }
}

void remove_line(char* line)
{
    const int len = strlen(line);
    if (line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }
}

int main(void)
{
    User* users[10] = {};
    Task* tasks[10] = {};
    const char* users_filename = "users.txt";
    const char* points_filename = "points.txt";

    char buffer[80] = {};

    FILE* users_file = fopen(users_filename, "rt");
    assert(users_file != NULL);
    FILE* points_file = fopen(points_filename, "rt");
    assert(points_file != NULL);

    int user_id = 0;
    int task_id = 0;

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), users_file))
        {
            remove_line(buffer);
            printf("|%s|\n", buffer);
            User* user = parse_user(buffer);
            users[user_id++] = user;
        }
        else
        {
            if (feof(users_file))
            {
                break;
            }
        }
    }

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), points_file))
        {
            remove_line(buffer);
            printf("|%s|\n", buffer);
            Task* task = parse_task(buffer);
            tasks[task_id++] = task;
        }
        else
        {
            if (feof(points_file))
            {
                break;
            }
        }
    }

    fclose(users_file);
    fclose(points_file);

    for (int i = 0; i < task_id; i++)
    {
        Task* task = tasks[i];
        const int user_id = task->id;
        char* user_login = users[user_id - 1]->login;

        printf("Completed task %d for user %s. Points: %d\n", task->id, user_login, task->points);
    }

    for (int i = 0; i < user_id; i++)
    {
        user_free(&users[i]);
    }

    for (int i = 0; i < task_id; i++)
    {
        task_free(&tasks[i]);
    }
    return 0;
}
