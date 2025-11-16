#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* import_path;
    char* export_path;
    char* needle;
    bool ignore_case;
} SearchConfig;

void input_recognize(const int input_length, char* input[], char** export_path, char** import_path, char** needle_name,
                     bool* ignore_upper_case)
{
    for (int i = 1; i < input_length; i++)
    {
        // if input contains -i (ignoring capital letters)
        if (strcmp(input[i], "-i") == 0)
        {
            if (*ignore_upper_case != false)
            {
                printf("Parameter -i provided multiple times\n");
                exit(1);
            }

            *ignore_upper_case = true;
        }
        // if input contains -o (export path)
        else if (strcmp(input[i], "-o") == 0)
        {
            if (*export_path != NULL)
            {
                printf("Parameter -o provided multiple times\n");
                exit(1);
            }

            if (i + 1 < input_length)
            {
                *export_path = strdup(input[i + 1]);
                i++;
            }

            if (*export_path == NULL)
            {
                printf("Missing output path\n");
                exit(1);
            }
        }
        // input must contains import_path & needle_name
        else
        {
            if (*import_path == NULL)
            {
                *import_path = strdup(input[i]);
            }
            else if (*needle_name == NULL)
            {
                *needle_name = strdup(input[i]);
            }
            else if (*needle_name != NULL)
            {
                printf("Too many parameters provided\n");
                exit(1);
            }
        }
    }

    // error messages when required values are not presented
    if (*import_path == NULL)
    {
        printf("Input path not provided\n");
        exit(1);
    }
    if (*needle_name == NULL)
    {
        printf("Needle not provided\n");
        exit(1);
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

void input_export(char* line, char** export_path, FILE* export_file)
{
    if (*export_path != NULL)
    {
        fprintf(export_file, "%s\n", line);
    }
    else
    {
        printf("%s\n", line);
    }
}

void input_search(char* needle_name, char* line, const bool ignore_upper_case, FILE* export_file,
                  char** export_path)
{
    if (ignore_upper_case == false)
    {
        if (strstr(line, needle_name) != NULL)
        {
            input_export(line, export_path, export_file);
        }
    }
    else
    {
        char* needle_name_lower = strdup(needle_name);
        for (int i = 0; needle_name_lower[i] != '\0'; i++)
        {
            needle_name_lower[i] = tolower(needle_name_lower[i]);
        }

        char* line_lower = strdup(line);
        for (int i = 0; line_lower[i] != '\0'; i++)
        {
            line_lower[i] = tolower(line_lower[i]);
        }

        if (strstr(line_lower, needle_name_lower) != NULL)
        {
            input_export(line, export_path, export_file);
        }
    }
}


int main(const int argc, char* argv[])
{
    char* import_path = NULL;
    char* export_path = NULL;
    char* needle_name = NULL;
    bool ignore_upper_case = false;
    char buffer[100] = {};
    FILE* import_file = NULL;
    FILE* export_file = NULL;


    input_recognize(argc, argv, &export_path, &import_path, &needle_name, &ignore_upper_case);

    if (import_path != NULL)
    {
        import_file = fopen(import_path, "r");
    }
    if (export_path != NULL)
    {
        export_file = fopen(export_path, "w");
    }

    while (true)
    {
        if (fgets(buffer, sizeof buffer, import_file))
        {
            remove_line(buffer);
            input_search(needle_name, buffer, ignore_upper_case, export_file, &export_path);
        }
        else
        {
            if (feof(import_file))
            {
                break;
            }
        }
    }

    // Section for closing all opened files (import/export)
    fclose(import_file);
    fclose(export_file);

    free(needle_name);
    free(export_path);
    free(import_path);


    return 0;
}
