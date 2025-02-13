#include <iostream>
#include <cmath>
#include <complex>
#include <iomanip>
#include <cblas.h>
#include "printmatrix.h"

int main()
{
    // Generate the matrix A with random complex number 
    srand(time(0));
    
    const int n = 3;
    std::complex<double>* A = new std::complex<double>[n*n];
    std::complex<double>* B = new std::complex<double>[n*n];
    std::complex<double>* C = new std::complex<double>[n*n];

    for (int j = 0; j < n; ++j)
    {   
        for (int k = 0; k < n; ++k)
        {
            double r = -1.0 + double(rand()) / (RAND_MAX / 2.0);
            double c = -1.0 + double(rand()) / (RAND_MAX / 2.0);
            A[j*n+k] = std::complex<double>(r,c);
            B[k*n+j] = std::complex<double>(r,-c);
        }
    }

    // Display A & B
    printmatrix(n,A);
    std::cout<<std::endl;
    printmatrix(n,B);


    // Copute A*B
    std::complex<double> alpha = 1.0;
    std::complex<double> beta = 0.0;
    cblas_zgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,n,n,n,&alpha,A,n,B,n,&beta,C,n);

    std::cout<<std::endl;
    printmatrix(n,C);

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}