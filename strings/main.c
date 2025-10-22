#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int my_strlen(const char* s)
{
    int i = 0;
    while (s[i] != 0)
    {
        i++;
    }

    return i;
};

void my_strcat(char* dest, const char* src)
{
    const int size_dest = my_strlen(dest);
    const int size_src = my_strlen(src);

    for (int i = 0; i <= size_src; i++)
    {
        dest[size_dest + i] = src[i];
    }
}

int main(void)
{
    char re[] = {'j', 'a', 'k', '\n', 0};
    const char* s1 = "UPR";
    const char* s2 = "UPR";

    char buff[80] = {};

    while (fgets(buff, 80, stdin))
    {
        if (buff[strlen(buff) - 1] == '\n')
        {
            buff[strlen(buff) - 1] = 0;
        }

        char* substr = strtok(buff, ";");
        printf("substr = %s\n", substr);
        printf("|%s| \n", buff);
    }

    // printf("strcmp= %d", strcmp(buff, s2));
    // printf("\n");
    //
    // if (!strcmp(buff, s2))
    // {
    //     printf("Rovnaké");
    // }
    // else
    // {
    //     printf("Rozdielne");
    // }

    // printf("|%s| ", re);
    //
    // printf("Len(re)= %d", my_strlen(re));

    // my_strcat(buff, s1);

    return 0;
}
