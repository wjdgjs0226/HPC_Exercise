#include <iostream>
#include <cmath>
#include <iomanip>
#include "nonblas.h"
#include "conjugate_gradient.h"

int main()
{
    int n = 2;
    srand(time(0));
    double *M = new double[n * n];
    double *A = new double[n * n];
    double *x = new double[n];
    double *x_cg = new double[n];
    double *b = new double[n];
    double *y = new double[n];

    // Insert the values
    for (int i = 0; i < n; ++i)
    {
        x[i] = -1. + double(rand()) / (RAND_MAX / 2.);
        for (int j = 0; j < n; ++j)
        {
            M[i * n + j] = -1. + double(rand()) / (RAND_MAX / 2.);
            //std::cout << M[j] << std::endl;
	}
        //std::cout << x[i] << std::endl;
    }

    // Operate Matrix Multiplication to calculate A
    int start = 0;
    nonblas(M, A, start, start, start, start, start, start, n, n);

/*
    for (int k = 0; k < n; ++k)
    {
        for (int l = 0; l < n; ++l)
        {
            std::cout << A[l * n + k] << " ";
        }
        std::cout << std::setw(30);
        for (int m = 0; m < n; ++m)
        {
            std::cout << M[m * n + k] << " ";
        }
        std::cout << std::endl;
    }
*/

    // Compute Ax = b
    for (int o = 0; o < n; ++o)
    {
        for (int p = 0; p < n; ++p)
        {
            b[o] += A[p*n+o]*x[p];
        }
        //std::cout << b[o] << std::endl;
    }

    conjugate_gradient(n,A,b,x_cg);

    for (int q = 0; q < n; ++q)
    {
        std::cout << x[q] << std::setw(30) << x_cg[q] <<std::endl;
    }

    delete[] M;
    delete[] A;
    delete[] x;
    delete[] x_cg;
    delete[] b;
    delete[] y;

    return 0;
}
