#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED
#include <iostream>
#include <cmath>
#include <assert.h>
#define TPL template<typename T>

//---------COMMENTS-------------
//Add operator[], addressing to components 
//Add core functions, like on lecture was said. And functions such as operator*(Vector, Vector) will be outside or operator+()

#define Assert_OK()\
if (!Vector_OK())\
{\
    Dump();\
    assert(!"Bad object CVector");\
}


const unsigned int N = 2; // dim of vector space

//vector can be broken too. Add method ok as private.
//dump too.
template <typename T>
class CVector
{
    private:
        T coord[N];
        bool Vector_OK()const;
    public:
        CVector<T>();
        explicit CVector<T>(T elem);
        ~CVector<T>();
        long double abs ()const;
        CVector<T> operator ! ();
        void operator += (CVector<T> a);
        void operator -= (CVector<T> a);
        CVector<T> operator + (CVector<T> b)const;
        CVector<T> operator - (CVector<T> b)const;
        CVector<T> operator * (double h)const;
        void operator = (const CVector<T>& b);
        T operator  * (CVector b)const;//you can use * here. the parameter differs from prev one.
        template <typename T_>//why do you need another type? It should work with main template.
        friend std::istream& operator>> (std::istream& s, CVector<T_>& temp);
        template <typename T_>
        friend std::ostream& operator<< (std::ostream& s, const CVector<T_>& temp);
        bool is_empty()const;
        void Dump()const;
        void foo(); //strange function
      //  void Assert_OK()const;
};

TPL
bool CVector<T>::Vector_OK()const
{
    return (coord && this);
}
TPL
bool CVector<T>::is_empty()const//what does the empty vector mean?
{
    bool temp = true;
    for (unsigned int i = 0; i < N; i++)
        if (coord[i] != 0.0)
        {
            return false;
        }
    return temp;//you don't change temp, anywhere.
}

TPL
void CVector<T>::Dump()const
{
    std::cout<<"----------------------------DUMP-----------------\n";
    if (!coord)
        assert("Very bad object CVector");
    if (is_empty() == true)
        std::cout<<"Vector is Empty!\n";
    else
    {
        for (unsigned int i = 0; i < N; i++)
            std::cout<<coord[i]<<" coord["<<i<<"] "<<std::endl;
        std::cout<<"Addresses: &coord = "<<&coord<<", &this = "<<this<<std::endl;
        std::cout<<"Dim = "<<N<<std::endl;
        std::cout<<"-------------------------END_OF_DUMP-------------\n";
    }
}
/*void CVector::Assert_OK()const
{
    if (!Vector_OK())
    {
        Dump();
        assert(!"Bad object CVector");
    }
} */

TPL
CVector<T>::CVector()
{
    for (unsigned int i = 0; i < N; i++)
        coord[i] = 0.0;
}

TPL
CVector<T>::CVector(T elem)
{
    coord[0] = elem;
}
TPL
CVector<T>::~CVector()
{
    //delete[] coord;
}

TPL
long double CVector<T>::abs()const
{
    Assert_OK();
    long double S = 0.0;
    for (unsigned int i = 0; i < N; i++)
        S += (coord[i])*(coord[i]);
    return sqrtl(S);
}

TPL
CVector<T> CVector<T>::operator ! ()
{
    Assert_OK();
    long double t_abs = abs();
    for (unsigned int i = 0; i < N; i++)
        coord[i] /= t_abs;
    return *this;
}

TPL
void CVector<T>::   operator += (CVector<T> a)
{
    Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        coord[i] += a.coord[i];
}

TPL
void CVector<T>::   operator -= (CVector<T> a)
{
    Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        coord[i] -= a.coord[i];
}

TPL
CVector<T> CVector<T>::operator + (CVector<T> b)const
{
    Assert_OK();
    CVector<T> temp = *this;
    temp += b;
    return temp;
}

TPL
CVector<T> CVector<T>::operator - (CVector<T> b)const
{
    Assert_OK();
    CVector<T> temp = *this;
    temp -= b;
    return temp;

}

TPL
CVector<T> CVector<T>::operator * (double h)const
{
    Assert_OK();
    CVector<T> temp;
    temp = *this;
    for (unsigned int i = 0; i < N; i++)
        temp.coord[i] *= h;
    return temp;
}

TPL
T CVector<T>:: operator * (CVector<T> b)const
{
    Assert_OK();
    long double res = 0.0;
    for (unsigned int i = 0; i < N; i++)
        res += ((coord[i])*b.coord[i]);
    return res;
}

TPL
void CVector<T>::operator = (const CVector<T>& b)
{
    Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        coord[i] = b.coord[i];
    Assert_OK();
}


TPL
std::istream& operator >> (std::istream& s, CVector<T>& temp)
{
    //temp.Assert_OK();
//    Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        s>>temp.coord[i];
    return s;
}

TPL
std::ostream& operator << (std::ostream& s, const CVector<T>& temp)
{
 //   temp.Assert_OK();
    for (unsigned int i = 0; i < N; i++)
        s<<temp.coord[i]<<" ";
    return s;
}
TPL
void CVector<T>::foo ()
{
 //   delete[] coord;
    Assert_OK();
    Dump();
}






#endif // CVECTOR_H_INCLUDED
