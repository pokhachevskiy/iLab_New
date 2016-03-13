#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED
#include <iostream>
#include <cmath>
#include <assert.h>
const unsigned int N = 2; // dim of vector space

//vector can be broken too. Add method ok as private.
//dump too.

class CVector
{
    private:
        long double coord[N];
        bool Vector_OK()const;
    public:
        CVector();
        ~CVector();
        long double abs ()const;
        CVector operator ! ();
        void operator += (CVector a);
        void operator -= (CVector a);
        CVector operator + (CVector b)const;
        CVector operator - (CVector b)const;
        CVector operator * (double h)const;
        long double operator  * (CVector b)const;//you can use * here. the parameter differs from prev one.
        friend std::istream& operator>> (std::istream& s, CVector& temp);
        friend std::ostream& operator<< (std::ostream& s, const CVector& temp);
        bool is_empty()const;
        void Dump()const;
        void Assert_OK()const;
};






#endif // CVECTOR_H_INCLUDED
