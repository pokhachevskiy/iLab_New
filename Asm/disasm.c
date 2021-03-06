#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void is_ok_string (char* str)
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
*/
#define DEF_CMD(name,num,code) cmd_##name = num,
enum COMMANDS
{
    #include "CMD_LIST.h"
    cmd_LAST
};
#undef DEF_CMD


int main()
{
    FILE* in = NULL;
    FILE* out = NULL;
    in = fopen("output.txt", "rb");
    out = fopen("asm.txt", "wb");
    if (in == NULL || out == NULL)
    {
        printf ("Error reading or writing the file!\n");
        return -1;
    }

    char ch = '0'; // temp char for reading
    char* number = NULL;
    int temp_cmd = -1;
    number = (char*)calloc(100, sizeof(char));
    if (number == NULL)
    {
        printf("Error allocation the memory!\n");
        return -1;
    }

    char buf[10]; // string of Info commands and input numbers
    while (1)
    {

        fscanf(in, "%d", &temp_cmd);
        #define DEF_CMD(name, num, code) \
        if (cmd_##name == temp_cmd) \
            fprintf (out, "%s", #name);
        #include "CMD_LIST.h"
        #undef DEF_CMD

        if (temp_cmd == cmd_PUSH)
        {
            fprintf(out, " ");
            fscanf(in, "%s", number);
            is_ok_string(number);
            fprintf(out, "%s", number);
        }
        fprintf(out,"\n");
        ch = fgetc(in);
        if (ch == EOF)
        {
            printf("break\n");
            break;
        }
        else
            fseek (in, -1, ftell(in));
    }
    fclose(in);
    fclose(out);
    printf("everything is ok\n");
    return 0;
}

