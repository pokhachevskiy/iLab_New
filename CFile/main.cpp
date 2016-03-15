#include "CFile.h"

int main()
{
    CFile myfile, out;
    myfile.cf_open("input.txt", "r");
    out.cf_open("output.txt", "w");
    myfile<<stdout;
    myfile.cf_close();
    out.cf_close();
    return 0;
}
