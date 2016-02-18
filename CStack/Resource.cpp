
#include "CStack.h"

// Add also counting the number of existing stacks.
// You can also make some limit of working stack objects.
// Also you can add methods top and size to make your stack similar to STL one.

bool CStack::Stack_OK()const
{
    return ((data == NULL) || (pos < 0) || (this == NULL) || (len < 0) || (pos > len)); //is that all? Check for len < 0, also it should check limits of pos. Ilya Ded told also about this == NULL.
}					  //think more about ok. It's important part.


void CStack::Assert_OK()const
{
    if (Stack_OK())
    {
        Stack_Dump();
        assert(!"Bad object CStack");
    }
}

CStack::CStack() : data(new T[START_LEN]), pos (0), len(START_LEN)
{}//you can add in constructor and destructor some helpful logs in debug mode
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
    return ((pos <= 0) || (len <= 0) ? true : false;
}//also it is empty when pos of len < 0. And dump doesn't say anything about it.

//__________________________________________________________
void CStack::Stack_Dump()const
{
    if (is_empty() == true)
        cout<<"Stack is Empty!\n";
    else
    {
        for (int i = 0; i < pos; i++)
            cout<<data[i]<<" data["<<i<<"] "<<endl;
        cout<<"Addresses: &data = "<<&data<<", &this = "<<&this<<endl; //I meant only the address of data and stack, not all elements' adresses
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
    //  data = (T*)realloc (data, len*sizeof(T));
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
            temp[i] = data[i]; //doesn't it duplicate code from contraction? You may first determine len of new stack
        delete[] data;	       // then copy data from old to new.
        data = temp;
      //data = (T*)realloc (data, len*sizeof(T));
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
