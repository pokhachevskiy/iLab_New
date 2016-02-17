
#include "CStack.h"




bool CStack::Stack_OK()const
{
    return ((data == NULL) || (pos < 0)); //there are more options when stack is not ok. E.g., Conditions with pos.
}//Why length of stack cann't be more then MAX_LENGTH. What for do you limit it?


void CStack::Assert_OK()const
{
    if (Stack_OK())
    {
        Stack_Dump();
        assert(!"Bad object CStack");
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
bool CStack::is_empty()const
{
    return (pos == 0) ? true : false;// when pos==0 it should return 1, cause it is empty. It may be clearer to use bool. It exists in c++.
}

//__________________________________________________________
void CStack::Stack_Dump()const
{
    if (is_empty() == true)
        cout<<"Stack is Empty!\n";
    else
    {
        for (int i = 0; i < pos; i++)
            cout<<data[i]<<" data["<<i<<"] address "<<&data + i<<endl;
        cout<<"Number of elements = "<<pos<<endl;
    }//also might help addresses of object and data
}
//_____________________________________________________________
void CStack::stack_resize (const int a)// a shows the type of resize: contraction or elongation
{
    Assert_OK();
    if ((a == 0) && (pos > 3*(len)/8))
    {
        len /= MULTIPLIER;
        T* temp = new T[len];
        if (temp == NULL)
        {
            cout<<"Can't allocate the memory for temp"<<endl;
            exit(-1);
        }

        for (int i = 0; i < len; i++)
            temp[i] = data[i];
        delete[] data;
        data = temp;
    //  data = (T*)realloc (data, len*sizeof(T)); //it's better to check != null after allocations. It might help finding error
    }

    if (a == 1)
    {
        len *= MULTIPLIER;
        T* temp = new T[len];
        if (temp == NULL)
        {
            cout<<"Can't allocate the memory for temp"<<endl;
            exit(-1);
        }
        for (int i = 0; i < len/MULTIPLIER; i++)
            temp[i] = data[i];
        delete[] data;
        data = temp;
      //data = (T*)realloc (data, len*sizeof(T));//and not good to use realloc here, cause it won't call contructors for T if it's class
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
