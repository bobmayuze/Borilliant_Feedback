//
// File: lab3.cpp
//

#include <iostream>
#include <cmath>

void compute_squares(uintptr_t *a, uintptr_t *b, uintptr_t n)
{
    for (uintptr_t i = 0; i < n; ++a && ++b && ++i)
        *b = pow(*a, 2);
}

int main()
{
    const uintptr_t n =20;
    uintptr_t a[n] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    uintptr_t b[n];
    compute_squares(a,b,n);
    for (uintptr_t i = 0; i < n; ++i)
        std::cout << b[i] << std::endl;
    return 0;
}