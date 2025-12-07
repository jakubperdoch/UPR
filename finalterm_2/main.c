#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *slovo;
    int skore;
    int count;
}Token;



Token* token_new(char *slovo,int skore)
{
    Token *token=malloc(sizeof(Token));
    if(!token) return NULL;

    token->slovo=strdup(slovo);
    token->skore=skore;
    token->count=0;

    return token;
}

Token* token_parse(char*line)
{
    char *slovo=strtok(line,",");
    int skore=atoi(strtok(NULL, ","));

    Token* token=token_new(slovo,skore);
    return token;
}

void empty_count(Token *tokens,int rows)
{
    for (int row = 0;row<rows;row++)
    {
        tokens[row].count=0;
    }

}


int main(const int argc, char* argv[])
{
    Token *tokens=NULL;
    char buffer[100]={};
    int rows=0;
    int list_count=0;
    bool new_list=false;

    if(argc<2)
    {
        printf("Parameters");
        exit(1);
    }

    rows=atoi(argv[1]);
    tokens= malloc(rows*sizeof(Token));


    for (int i = 0; i < rows; i++)
    {

        fgets(buffer, sizeof buffer, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        Token* token=token_parse(buffer);
        tokens[i]=*token;

        free(token);

    }

    while(fgets(buffer, sizeof buffer, stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        if(strcmp(buffer, "---") == 0)
        {
            bool has_content = false;
            for(int token = 0; token < rows; token++) {
                if(tokens[token].count > 0) {
                    has_content = true;
                    break;
                }
            }

            if(has_content) {
                list_count++;
                int count = 0;
                printf("Letter #%d\n", list_count);
                for(int token = 0; token < rows; token++)
                {
                    if(tokens[token].count > 0)
                    {
                        printf("Token '%s': %d occurrence, AI score: %d\n",
                               tokens[token].slovo, tokens[token].count, tokens[token].skore);
                    }
                    count += tokens[token].count * tokens[token].skore;
                }
                printf("Total AI score: %d\n", count);
            }

            empty_count(tokens, rows);
            continue;
        }

        for(int letter = 0; buffer[letter] != '\0'; letter++)
        {
            for(int token = 0; token < rows; token++)
            {
                for(int j = 0; tokens[token].slovo[j] != '\0'; j++)
                {
                    if(tolower(buffer[letter]) == tokens[token].slovo[j])
                    {
                        tokens[token].count++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < rows; i++)

    {

        free(tokens[i].slovo);

    }
    free(tokens);

    return 0;
}
