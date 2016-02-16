#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void is_ok_string (char* str)
{
    int i = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            printf("input arguments is not correct!\n");
            exit(1);
        }
    }

}

#define DEF_CMD(name,num,code) cmd_##name = num,
enum COMMANDS
{
    #include "CMD_LIST.h"
    cmd_LAST
};
#undef DEF_CMD
const int MUL = 2, START_L = 30;



typedef struct cmd_INFO
{
    int num;
    const char* name;
}cmd_INFO;

/*
const cmd_INFO Info[] =
{
    {cmd_PUSH,  "PUSH"},
    {cmd_POP,   "POP"},
    {cmd_ADD,   "ADD"},
    {cmd_SUB,   "SUB"},
    {cmd_MULTI, "MULTI"},
    {cmd_DIV,   "DIV"},
    {cmd_MOD,   "MOD"},
};
*/

int main()
{
    FILE* in = NULL;
    FILE* out = NULL;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    if (in == NULL || out == NULL)
    {
        printf ("Error reading or writing the file!\n");
        return -1;
    }
    char* str_source; //string with input file
    str_source = (char*)calloc(START_L, sizeof(char));
    if (str_source == NULL)
    {
        printf ("Error creating memory!\n");
        return -1;
    }
    char ch; // temp chat for reading
    int i = 0;
    while ((ch = fgetc(in)) != EOF)
    {
        str_source[i++] = ch;
        if (i == START_L - 1)
        {
            str_source = (char*)realloc(str_source, START_L*MUL);
            if (str_source == NULL)
            {
                printf ("Error creating memory!\n");
                return -1;
            }
        }
    }
    str_source[i] = ' ';
    str_source[i + 1] = '\0';
    i = 0;
    int k = 0;
    int j = 0;
    char* number;
    number = (char*)calloc(100, sizeof(char));
    if (number == NULL)
    {
        printf("Error allocation the memory!\n");
        return -1;
    }

    char buf[10]; // string of Info commands and input numbers
    while (1)
    {

        fscanf(in, "%s", buf);
        #define DEF_CMD(name, num, code) \
        if (!strcmp(buf, #name)) \
            fprintf (out, "%d", cmd_##name);
        #include "CMD_LIST.h"
        #undef DEF_CMD

        if (!strcmp(buf, "PUSH"))
        {
            fscanf(in, "%s", number);
            is_ok_string(number);
            fprintf(out, "%s", number);
        }
        fprintf(out,"\n");

    }
    return 0;
}
