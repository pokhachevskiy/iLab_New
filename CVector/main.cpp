#include "CVector.h"

int main()
{
    CVector a,b;
    std::cin>>a>>b;
    !a;
    std::cout<<"abs a "<<a.abs()<<std::endl;
    std::cout<<a<<std::endl;
    CVector c = a + b;
    std::cout<<"this is c: "<<c<<std::endl;
    std::cout<<"this is a: "<<a<<std::endl;
    long double m = a*c;
    std::cout<<"scalar proizb a*c "<<m<<std::endl;
    c += b;
    std::cout<<"c after c += b"<<std::endl;
    std::cout<<c<<std::endl;


    return 0;

}
