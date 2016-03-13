#include "CVector.h"

bool CVector::Vector_OK()const
{
    return (this) ? true : false;
}
bool CVector::is_empty()const
{
    bool temp = true;
    for (unsigned int i = 0; i < N; i++)
        if (coord[i] != 0.0)
        {
            return false;
        }
    return temp;
}


void CVector::Dump()const
{
    if (is_empty() == true)
        std::cout<<"Vector is Empty!\n";
    else
    {
        for (unsigned int i = 0; i < N; i++)
            std::cout<<coord[i]<<" coord["<<i<<"] "<<std::endl;
        std::cout<<"Addresses: &coord = "<<&coord<<", &this = "<<this<<std::endl;
        std::cout<<"Dim = "<<N<<std::endl;
    }
}
void CVector::Assert_OK()const
{
    if (!Vector_OK())
    {
        Dump();
        assert(!"Bad object CStack");
    }
}


CVector::CVector()
{
    for (unsigned int i = 0; i < N; i++)
        coord[i] = 0.0;
}
CVector::~CVector()
{
    delete[] coord;
}
long double CVector::abs()const
{
    Assert_OK();
    long double S = 0.0;
    for (unsigned int i = 0; i < N; i++)
        S += (coord[i])*(coord[i]);
    return sqrtl(S);
}

CVector CVector::operator ! ()
{
    Assert_OK();
    long double t_abs = abs();
    for (unsigned int i = 0; i < N; i++)
        coord[i] /= t_abs;
    return *this;
}
void CVector::   operator += (CVector a)
{
    Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        coord[i] += a.coord[i];
}
void CVector::   operator -= (CVector a)
{
    Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        coord[i] -= a.coord[i];
}
CVector CVector::operator + (CVector b)const
{
    Assert_OK();
    CVector temp = *this;
    temp += b;
    return temp;
}
CVector CVector::operator - (CVector b)const
{
    Assert_OK();
    CVector temp = *this;
    temp -= b;
    return temp;

}
CVector CVector::operator * (double h)const
{
    Assert_OK();
    CVector temp;
    temp = *this;
    for (unsigned int i = 0; i < N; i++)
        temp.coord[i] *= h;
    return temp;
}
long double CVector:: operator * (CVector b)const
{
    Assert_OK();
    long double res = 0.0;
    for (unsigned int i = 0; i < N; i++)
        res += ((coord[i])*b.coord[i]);
    return res;
}

std::istream& operator >> (std::istream& s, CVector& temp)
{
    temp.Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        s>>temp.coord[i];
    return s;
}
std::ostream& operator << (std::ostream& s, const CVector& temp)
{
    temp.Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        s<<temp.coord[i]<<" ";
    return s;
}
