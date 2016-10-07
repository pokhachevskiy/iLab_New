#include "Complex.h"

int main()
{
    std::cout<<"Input a, b, c in order:\nRe(z)\nIm(z)"<<std::endl;
    Complex a, b, c;
    std::cin >> a >> b >> c;
    square_equation first(a, b, c);
    first.solve();
    return 0;
}

