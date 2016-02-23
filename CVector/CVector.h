#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cmath>
//using namespace std;
const unsigned int N = 2; // dim of vector space


class CVector
{
    private:
        long double coord[N];
    public:
        CVector();
        ~CVector();
        long double abs ()const;
        CVector operator ! ();
        void operator += (CVector a);
        void operator -= (CVector a);
        CVector operator + (CVector b)const;
        CVector operator - (CVector b)const;
        CVector operator * (double h);
        long double operator  ^ (CVector b)const;
        friend std::istream& operator>> (std::istream& s, CVector& temp);
        friend std::ostream& operator<< (std::ostream& s, const CVector& temp);
};






#endif // CVECTOR_H_INCLUDED
