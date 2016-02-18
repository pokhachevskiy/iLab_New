
#include "CStack.h"

int CStack::number = 0;
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
{
    ++number;
    if (number > 3)
    {
        char* key = new char[100];
        cout<<"You haven't bought this program yet. Enter the license key to open the full functions of program!\n Enter the key>> ";
        cin>>key;
        if (strcmp("Xpe79qa81v\0", key))
        {
            cout<<"The key isn't correct!"<<endl;
            exit(-1);
        }
    }
}//you can add in constructor and destructor some helpful logs in debug mode
// I don't know what to add like logs. May be later...
CStack::~CStack()
{
    number--;
	delete[] data;
	data = NULL;
	len = 0;
	pos = 0;
}
//________________________________________________________
bool CStack::is_empty()const
{
    return ((pos <= 0) || (len <= 0)) ? true : false;
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
        cout<<"Addresses: &data = "<<&data<<", &this = "<<this<<endl; //I meant only the address of data and stack, not all elements' adresses
        cout<<"Number of elements = "<<pos<<endl;
    }//also might help addresses of object and data
}
//_____________________________________________________________
void CStack::stack_resize (const int a)// a shows the type of resize: 0 for contraction and 1 for elongation
{
    Assert_OK();
    int new_len = len;
    if ((a == 0) && (pos > 3*(len)/8))
        new_len /= MULTIPLIER;
    if (a == 1)
        new_len *= MULTIPLIER;
    T* temp = new T[new_len];
        if (temp == NULL)
        {
            cout<<"Can't allocate the memory for temp"<<endl;
            exit(-1);
        }

        for (int i = 0; i < pos; i++)
            temp[i] = data[i];
        delete[] data;
        data = temp;
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
