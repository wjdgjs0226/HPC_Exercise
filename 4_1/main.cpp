#include <iostream>
#include <iomanip>
#include <cblas.h>
#define F77NAME(x) x##_

extern "C"
{
    double F77NAME(dnrm2)(const int& n, const double* x, const int& incx);
    double F77NAME(dasum)(const int& n, const double* x, const int& incx);
    int F77NAME(idamax)(const int& n, const double* x, const int& incx);
}

int main()
{
    // Define the required variables
    const int N = 20; // vector size
    double* x = new double[N];

    srand(time(0));
    
    for(int i = 0; i < N; ++i)
    {
        x[i] = (double(rand())) / double(RAND_MAX/10);
    }
    

    
    // Compute the Euclidian Norm, the Sum of the abs, and the maximum abs
    double norm2 = F77NAME(dnrm2)(N,x,1);
    double norm2_c = cblas_dnrm2(N,x,1);

    double abssum = F77NAME(dasum)(N,x,1);
    double abssum_c = cblas_dasum(N,x,1);

    int maxabs = F77NAME(idamax)(N,x,1);
    int maxabs_c = cblas_idamax(N,x,1);

    // Print out
    for(int j = 0; j < N; ++j)
    {
        std::cout << x[j] << std::endl;
    }
    std::cout << " " << std::endl;
    std::cout << "Euclidian Norm: " << norm2 << std::setw(40) << "Cblas: " << norm2_c << std::endl;
    std::cout << "Sum of the abs: " << abssum << std::setw(40) << "Cblas: " << abssum_c << std::endl;
    std::cout << "Maximum abs index: " << maxabs << std::setw(40) << "Cblas: " << maxabs_c << std::endl; //Fortran Array indexing uses one-based indexing

    delete[] x; //Deallocate the Memory

    return 0;
}