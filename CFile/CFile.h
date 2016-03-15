#ifndef CFILE_H_INCLUDED
#define CFILE_H_INCLUDED
#include <stdio.h>
#include <iostream>
#include <stdlib.h>


class CFile
{
    private:
        FILE* cfile;
    public:
        CFile(): cfile(NULL)
        {}
        operator FILE* ()const
        {
            return cfile;
        }
        CFile cf_open (const char* adr, const char* prm)
        {
            this->cfile = fopen(adr, prm);
            if (this->cfile == NULL)
            {
                printf("Error opening the file!\n");
                exit(-1);
            }
            return *this;
        }
        void cf_close ()
        {
            fclose(this->cfile);
        }
        unsigned int number_of_strs ()
        {
            char ch = '\0';
            unsigned int num = 0;
            while ((ch = fgetc(cfile)) != EOF)
                if (ch == '\n')
                    num++;
            fseek(cfile, SEEK_SET, 0);
            return num;
        }
        void operator << (FILE* adr)
        {
            char ch = '\0';
            char* temp = NULL;
            int len = 0;
            unsigned int k = 0;
            while (k != number_of_strs())
            {
                k++;
                ch = fgetc(cfile);
                if (ch != '\n')
                   len++;
                else
                {
                    fseek(cfile, SEEK_CUR, -len - 1);
                    temp = new char[len];
                    fscanf(cfile, "%s", temp);
                    fprintf(adr,"%s", temp);
                    delete[] temp;
                    len = 0;
                }
            }
        }

};


#endif // CFILE_H_INCLUDED
