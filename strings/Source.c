#include <stdio.h>
#include <stdlib.h>
size_t length(const char str[])
{
    size_t i = 0, res = 0;
    while (str[i++] != '\0')
    {
        res++;
    }
    return res;
}
unsigned long long my_atoi (const char str[])
{
    unsigned long long temp = 0;
    for (int i = 0; i < length(str); i++)
        temp = 10*temp + (str[i] - '0');
    return temp;
}

int rank_d (unsigned long long n)
{
    int i = 0;
    if (n == 0)
        return 1;
    while (n > 0)
    {
        i++;
        n /= 10;
    }
    return i;
}


void my_itoa (unsigned long long integer, char res[])
{
    int rank = rank_d(integer);
    for (int i = 0; integer > 0; i++)
    {
        res[rank_d(integer) - 1] = (integer % 10) + '0';
        integer /= 10;
    }
    *(res + rank) = '\0';
}



