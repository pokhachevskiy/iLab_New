#include "stack.h"
#define PRINT(x) printf("%s\n", x);
int main()
{

    Stack_t *stack = NULL;
    Error temp;
    temp.code = NO_ERROR;
    temp.message = NULL;
    T var1 = 0, var2 = 0, var3, var4, var5, var6;
    scanf("%c %c %c", &var3, &var4, &var5);
    stack = my_stack_ctor(stack);

    if (push(stack, var3).code == temp.code)
    {
        if (push(stack, var4).code == temp.code)
        {
            if (push(stack, var5).code == temp.code)
            {
                if (pop(stack, &var1).code == temp.code)
                {
                    if (pop(stack, &var2).code == temp.code)
                    {
                        if (pop(stack, &var6).code == temp.code)
                        {
                            printf ("%c %c %c\n", (char)var1, (char)var2, (char)var6);
                        }
                        else PRINT(pop(stack, &var6).message)
                    }
                    else PRINT(pop(stack, &var2).message)
                }
                else PRINT(pop(stack, &var1).message)
            }
            else PRINT(push(stack, var5).message)
        }
        else PRINT(push(stack, var4).message)
    }
    else PRINT(push(stack, var3).message)


    temp = dump(stack);
    printf ("\n %s \n", temp.message);

    if (my_stack_dtor(stack).code == temp.code)
        printf("Stack is deleted succesfully\n");
    getchar();
    return 0;




}
