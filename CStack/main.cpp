
#include "CStack.h"


int main()
{
    char ch = '\0', out = '\0';
    CStack temp;
    cin>>ch;
    temp.push(ch);
    cin>>ch;
    temp.push(ch);
    cin>>ch;
    temp.push(ch);
    temp.Stack_Dump();
    temp.pop(out);
    cout<<out<<endl;
    temp.pop(out);
    cout<<out<<endl;
    temp.pop(out);
    cout<<out<<endl;
    return 0;
}
