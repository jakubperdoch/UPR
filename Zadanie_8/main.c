#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void recognize_input(int input_length, char* input[], char** export_path, char** import_path, char** needle_name,
                     bool* ignores_upper_case)
{
    for (int i = 1; i < input_length; i++)
    {
        if (strcmp(input[i], "-i") == 0)
        {
            if (*ignores_upper_case)
            {
                printf("Parameter -i provided multiple times\n");
                exit(1);
            }

            if (i + 1 < input_length)
            {
                *ignores_upper_case = true;
                *needle_name = strdup(input[i + 1]);
                i++;
            }
        }
        else if (strcmp(input[i], "-o") == 0)
        {
            if (*export_path != NULL)
            {
                printf("Parameter -o provided multiple times\n");
                exit(1);
            }

            *export_path = strdup(input[i + 1]);
            if (*export_path == NULL)
            {
                printf("Missing output path\n");
                exit(1);
            }
            i++;
        }
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
        }
    }

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


int main(const int argc, char* argv[])
{
    char* import_path = NULL;
    char* export_path = NULL;
    char* needle_name = NULL;
    bool ignores_upper_case = false;


    recognize_input(argc, argv, &export_path, &import_path, &needle_name, &ignores_upper_case);

    free(needle_name);
    free(export_path);
    free(import_path);


    return 0;
}
