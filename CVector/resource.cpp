#include "CVector.h"



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
    long double S = 0.0;
    for (unsigned int i = 0; i < N; i++)
        S += (coord[i])*(coord[i]);
    return sqrtl(S);
}

CVector CVector::operator ! ()
{
    long double t_abs = abs();
    for (unsigned int i = 0; i < N; i++)
        coord[i] /= t_abs;
    return *this;
}
void CVector::   operator += (CVector a)
{
    for (unsigned int i = 0; i < N; i++)
        coord[i] += a.coord[i];
}
void CVector::   operator -= (CVector a)
{
    for (unsigned int i = 0; i < N; i++)
        coord[i] -= a.coord[i];
}
CVector CVector::operator + (CVector b)const
{
    CVector temp = *this;
    temp += b;
    return temp;
}
CVector CVector::operator - (CVector b)const
{
    CVector temp = *this;
    temp -= b;
    return temp;

}
CVector CVector::operator * (double h)const
{
    CVector temp;
    temp = *this;
    for (unsigned int i = 0; i < N; i++)
        temp.coord[i] *= h;
    return temp;
}
long double CVector:: operator ^ (CVector b)const
{
    long double res = 0.0;
    for (unsigned int i = 0; i < N; i++)
        res += ((coord[i])*b.coord[i]);
    return res;
}

std::istream& operator >> (std::istream& s, CVector& temp)
{
    for (unsigned int i = 0; i < N; i++)
        s>>temp.coord[i];
    return s;
}
std::ostream& operator << (std::ostream& s, const CVector& temp)
{
    for (unsigned int i = 0; i < N; i++)
        s<<temp.coord[i]<<" ";
    return s;
}
