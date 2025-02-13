#include <iostream>
#include <cmath>
#include <complex>
#include <iomanip>

void printmatrix(int n, std::complex<double>* A)
{
    for (int k = 0; k < n; ++k)
    {
        for (int l = 0; l < n; ++l)
        {
            
            std::cout << std::setprecision(3) << std::real(A[l*n+k]) << " + " << std::imag(A[l*n+k]) << "i" << "   ";
        }
        std::cout<<std::endl;
    }
}