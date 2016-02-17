
//#include <stdio.h>
//#include <stdlib.h>
#include "CStack.h"
//_____________________________________________________2147483



int CStack::Stack_OK()const
{
    return ((data == NULL) || (len > MAX_LENGTH)) ? 1 : 0;
}


void CStack::Assert_OK()const
{
    if (Stack_OK())
    {
        Stack_Dump();
        assert(!"Bad object CStack");
        exit(-1);
    }
}

CStack::CStack() : data(new T[START_LEN]), pos (0), len(START_LEN)
{}
CStack::~CStack()
{
	delete[] data;
	data = NULL;
	len = 0;
	pos = 0;
}
//________________________________________________________
int CStack::is_empty()const
{
    return (pos == 0) ? 0 : 1;
}

//__________________________________________________________
void CStack::Stack_Dump()const
{
    if (is_empty() == 0)
        cout<<"Stack is Empty!\n";
    else
    {
        for (int i = 0; i < pos; i++)
            cout<<data[i]<<" data["<<i<<"]\n";
        cout<<"Number of elements = "<<pos<<endl;
    }
}
//_____________________________________________________________
void CStack::stack_resize (const int a)
{
    Assert_OK();
    if ((a == 0) && (pos > 3*(len)/8))
        data = (T*)realloc (data, (len*sizeof(T))/2);
    if (a == 1)
    {
        len *= MULTIPLIER;
        data = (T*)realloc (data, len*sizeof(T));
    }
    Assert_OK();
}
//_______________________________________________________________
void CStack::push(T in)
{
    Assert_OK();

    if (pos == len)
        stack_resize(1);
    data[pos++] = in;
    Assert_OK();
}
//_____________________________________________________
void CStack::pop(T& out)
{
    Assert_OK();
    if (pos == 0)
    {
        cout<<"STACK IS UNDERFLOW\n";
        exit(-1);
    }

    out = data[--pos];


    stack_resize(0);
    Assert_OK();
}
//_______________________________________________________
