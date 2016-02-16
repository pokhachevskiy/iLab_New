#include <stdio.h>
#include "mystring.h"

int main()
{
    char str[10];
    my_itoa(55, str);
    printf ("itoa %s \n", str);
    printf("Hello world!\n");
    return 0;
}
