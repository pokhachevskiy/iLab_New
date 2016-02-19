
#include "CStack.h"


int main()
{
    int ch = 0, out = 0;
    CStack temp, temp1, temp2;
    cin>>ch;
    temp.push(ch);
    cin>>ch;
    temp.push(ch);
    cin>>ch;
    temp.push(ch);
    temp.Stack_Dump();
    cout<<"This is top = "<<temp.top()<<endl;
    cout<<"This is temp[1] = "<<temp[1]<<endl;
    temp.top() -= 10;
    temp[0] += 12;
    cout<<"This is top after -= 10;= "<<temp.top()<<endl<<endl;
    cout<<"current size of stack = "<<temp.size()<<endl;
    cout<<"Now all pop, including temp[0] += 12;"<<endl;
    temp.pop(out);
    cout<<out<<endl;
    temp.pop(out);
    cout<<out<<endl;
    temp.pop(out);
    cout<<out<<endl;

    cout<<"Trying to out temp[0] after pops everything:= \n";
    cout<<temp[0]<<endl;
    return 0;
}
