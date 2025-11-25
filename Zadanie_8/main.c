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

void init_config(SearchConfig* config)
{
    config->import_path = NULL;
    config->export_path = NULL;
    config->needle = NULL;
    config->ignore_case = false;
}

void flush()
{
    fflush(stdout);
}

// function for reseting ansi color
void reset_color()
{
    printf("\x1b[0m");
    flush();
}

// function for applying ansi color
void set_red_color()
{
    printf("\x1b[41;1m");
    flush();
}

// helper function for replacing all capital letters with their lowercase version
void to_lowercase(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void parse_arguments(int argc, char* argv[], SearchConfig* config)
{
    init_config(config);

    for (int i = 1; i < argc; i++)
    {
        // if input contains -i (ignoring capital letters)
        if (strcmp(argv[i], "-i") == 0)
        {
            if (config->ignore_case != false)
            {
                printf("Parameter -i provided multiple times\n");
                exit(1);
            }

            config->ignore_case = true;
        }
        // if input contains -o (export path)
        else if (strcmp(argv[i], "-o") == 0)
        {
            if (config->export_path != NULL)
            {
                printf("Parameter -o provided multiple times\n");
                exit(1);
            }

            if (i + 1 < argc)
            {
                config->export_path = strdup(argv[i + 1]);
                i++;
            }

            if (config->export_path == NULL)
            {
                printf("Missing output path\n");
                exit(1);
            }
        }
        // input must contain import_path & needle
        else
        {
            if (config->import_path == NULL)
            {
                config->import_path = strdup(argv[i]);
            }
            else if (config->needle == NULL)
            {
                config->needle = strdup(argv[i]);
            }
            else
            {
                printf("Too many parameters provided\n");
                exit(1);
            }
        }
    }

    // error messages when required values are not presented
    if (config->import_path == NULL)
    {
        printf("Input path not provided\n");
        exit(1);
    }
    if (config->needle == NULL)
    {
        printf("Needle not provided\n");
        exit(1);
    }
}

// removing \n from the end of line and replacing with \0
void remove_newline(char* line)
{
    const int len = strlen(line);
    if (line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }
}

//BONUS
void highlight_line(const char* line, const char* needle)
{
    bool match = false;
    const int needle_len = strlen(needle);


    for (int i = 0; line[i] != '\0'; i++)
    {
        for (int j = 0; needle[j] != '\0'; j++)
        {
            if (line[i + j] == needle[j])
            {
                match = true;
            }
            else
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            set_red_color();
            for (int k = 0; k < needle_len; k++)
            {
                printf("%c", line[i + k]);
            }
            reset_color();
            i += needle_len - 1;
        }
        else
        {
            reset_color();
            printf("%c", line[i]);
        }
    }

    printf("\n");
}

void output_line(char* line, char** export_path, FILE* export_file, const char* needle)
{
    if (*export_path != NULL)
    {
        fprintf(export_file, "%s\n", line);
    }
    else
    {
        highlight_line(line, needle);
        // printf("%s\n", line);
    }
}

void search_and_output(FILE* output, SearchConfig* config, char* line)
{
    if (config->ignore_case == false)
    {
        if (strstr(line, config->needle) != NULL)
        {
            output_line(line, &config->export_path, output, config->needle);
        }
    }
    else
    {
        char* needle_lower = strdup(config->needle);
        char* line_lower = strdup(line);

        to_lowercase(needle_lower);
        to_lowercase(line_lower);

        if (strstr(line_lower, needle_lower) != NULL)
        {
            output_line(line, &config->export_path, output, needle_lower);
        }
    }
}


int main(const int argc, char* argv[])
{
    SearchConfig config;
    FILE* input_file = NULL;
    FILE* output_file = NULL;
    char buffer[100] = {};

    parse_arguments(argc, argv, &config);

    if (config.import_path != NULL)
    {
        input_file = fopen(config.import_path, "r");
    }
    if (config.export_path != NULL)
    {
        output_file = fopen(config.export_path, "w");
    }

    while (true)
    {
        if (fgets(buffer, sizeof buffer, input_file))
        {
            remove_newline(buffer);
            search_and_output(output_file, &config, buffer);
        }
        else
        {
            if (feof(input_file))
            {
                break;
            }
        }
    }

    // Section for closing all opened files (import/export)
    fclose(input_file);
    if (output_file != NULL)
    {
        fclose(output_file);
    }

    // Section for freeing memory allocated for config
    free(config.import_path);
    free(config.export_path);
    free(config.needle);

    return 0;
}
