#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include <iostream>
#include <cmath>
#include <cstdlib>

int sgn (double t)
{
    return (t > 0)? 1 : -1;
}
class Complex
{
	private:
        double re;
        double im;
	public:
        Complex(double a, double b): re(a), im(b)
        {}
        Complex(double a): re(a), im(0)
        {}
        Complex()
        {
            re = 0;
            im = 0;
        }
        ~Complex()
        {}
        bool isNULL ()const;
        void operator += (Complex a);
        void operator -= (Complex a);
        void operator *= (Complex a);
        void operator /= (Complex a);
        Complex operator + (Complex b)const;
        Complex operator - (Complex b)const;
        Complex operator  * (Complex b)const;
        Complex operator  / (Complex b)const;
        bool operator == (const Complex& b)const;
        Complex operator ^ (unsigned int h)const;
        Complex csqrt ()const;
        void operator = (const Complex& b);
        friend std::istream& operator>> (std::istream& s, Complex& temp);
        friend std::ostream& operator<< (std::ostream& s, const Complex& temp);
        bool isReal()const;
};


class square_equation //az^2 + bz + c = 0
{
    private:
        Complex a;
        Complex b;
        Complex c;
        Complex discriminant()const;
    public:
        square_equation(Complex a0, Complex b0, Complex c0): a(a0), b(b0), c(c0)
        {}
        square_equation(): a(0), b(0), c(0)
        {}
        void solve()const;
};
void square_equation::solve()const
{
    if (a.isNULL())
    {
        if (b.isNULL())
        {
            std::cout << "There is no solution" << std::endl;
            return;
        }
        else
        {
            Complex z = ((Complex)0 - c)/b;
            std::cout << "z = " << z;
            return;
        }
    }
    Complex z_1, z_2;
    Complex sqDisc = discriminant().csqrt();
    z_1 = ((Complex)0 - b + sqDisc)/((Complex)2*a);
    z_2 = ((Complex)0 - b - sqDisc)/((Complex)2*a);
    (sqDisc == (Complex)0)? std::cout << z_1:
    std::cout << "z1 = " << z_1 << "z2 = " << z_2;
}
Complex square_equation::discriminant()const
{
    return ((b^2) - a*c*(Complex)4);
}
Complex Complex::csqrt()const
{
    Complex res(0, 0);
    res.re = sqrt((sqrt(re*re + im*im) + re)/2);
    res.im = sgn(im)*sqrt((sqrt(re*re + im*im) - re)/2);
    return res;
}
bool Complex::isNULL ()const
{
    return (!re && !im);
}
bool Complex::operator == (const Complex& b)const
{
    return ((re == b.re) && (im == b.im));
}
void Complex::operator += (Complex a)
{
    re += a.re;
    im += a.im;
}
void Complex::operator -= (Complex a)
{
    re -= a.re;
    im -= a.im;
}
void Complex::operator *= (Complex a)
{
    *this = *this * a;
}
void Complex::operator /= (Complex a)
{
    *this = *this / a;
}
Complex Complex::operator + (Complex b)const
{
    Complex res(re, im);
    res += b;
    return res;
}
Complex Complex::operator - (Complex b)const
{
    Complex res(re, im);
    res -= b;
    return res;
}
Complex Complex::operator * (Complex b)const
{
    Complex res(re, im);
      //a·a′−b·b′)+(a·b′+b·a′)i
    res.re = b.re*re - b.im*im;
    res.im = re*b.im + b.re*im;
    return res;
}

Complex Complex::operator / (Complex b)const
{

    Complex res(re, im);
      //a·a′−b·b′)+(a·b′+b·a′)i
    try
    {
        if (!(b.re*b.re + b.im*b.im))
            throw -1;
        res.re = (re*b.re + im*b.im)/(b.re*b.re + b.im*b.im);
        res.im = (b.re*im - b.im*re)/(b.re*b.re + b.im*b.im);
    }
    catch(int i)
    {
        if (!(i + 1))
            std::cout<<"Division by zero!"<<std::endl;
        exit(-1);
    }
    return res;
}
Complex Complex::operator ^ (unsigned int h)const
{
    Complex res(re, im);
    h--;
    while(h--)
        res *= res;
    return res;
}
void Complex::operator = (const Complex& b)
{
    re = b.re;
    im = b.im;
}
std::istream& operator >> (std::istream& s, Complex& temp)
{
    std::cout<<"Re = ";
    s>>temp.re;
    std::cout<<"Im = ";
    s>>temp.im;
    return s;
}
std::ostream& operator << (std::ostream& s, const Complex& temp)
{
    if (temp.isReal())
    {
            s<<temp.re<<std::endl;
    }
    else if (temp.re)
        (temp.im > 0)? s<<temp.re<<" + "<<fabs(temp.im)<<"i"<<std::endl : s<<temp.re<<" - "<<fabs(temp.im)<<"i"<<std::endl;
    else
        (temp.im > 0)? s<<fabs(temp.im)<<"i"<<std::endl : s<<" - "<<fabs(temp.im)<<"i"<<std::endl;
    return s;
}
bool Complex::isReal()const
{
    return (!im);
}



#endif // COMPLEX_H_INCLUDED
