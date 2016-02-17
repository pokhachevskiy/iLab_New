
//#include <stdio.h>
//#include <stdlib.h>
#include "CStack.h"
//_____________________________________________________2147483



int CStack::Stack_OK()const
{
    return ((data == NULL) || (len > MAX_LENGTH)) ? 1 : 0; //there are more options when stack is not ok. E.g., Conditions with pos. 
}//Why length of stack cann't be more then MAX_LENGTH. What for do you limit it?


void CStack::Assert_OK()const
{
    if (Stack_OK())
    {
        Stack_Dump();
        assert(!"Bad object CStack");
        exit(-1);//you don't need this. assert will exit anyway
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
    return (pos == 0) ? 0 : 1;// when pos==0 it should return 1, cause it is empty. It may be clearer to use bool. It exists in c++. 
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
    }//also might help addresses of object and data
}
//_____________________________________________________________
void CStack::stack_resize (const int a)//for future. it's better comment what the parametr stands for.  
{
    Assert_OK();
    if ((a == 0) && (pos > 3*(len)/8))//you need change len too here.
        data = (T*)realloc (data, (len*sizeof(T))/2); //it's better to check != null after allocations. It might help finding errors 
    if (a == 1)
    {
        len *= MULTIPLIER;
        data = (T*)realloc (data, len*sizeof(T));//and not good to use realloc here, cause it won't call contructors for T if it's class
    }// It's better to use new here(but you need copy your data in new array). I hope Ilya Ded will tell you about opertor new.
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
