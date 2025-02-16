#include <iostream>
#include <iomanip>
#include <cmath>
#include <cblas.h>

/* 
This code is written for solving the example test problem
Author: Jeongheon (Edward) Lee
*/

void GenerateBandedSymMatrix(double* D, int ldD, int n, double coeffb)
{
    // Values to be inserted
    double first = 2.0*coeffb;
    double second = -5.0*coeffb;
    double third = 4.0*coeffb;
    double fourth = -1.0*coeffb;

    D[3] = first;
    D[6] = second;
    D[7] = first;
    D[9] = third;
    D[10] = second;
    D[11] = first;

    for (int i = 3; i < n; ++i)
    {
        D[i*ldD] = fourth;
        D[i*ldD + 1] = third;
        D[i*ldD + 2] = second;
        D[i*ldD + 3] = first;
    }
}

void comparevector(double* A, double* B, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << std::setprecision(3) << A[i] << std::setw(40) << B[i] << std::endl;

    }

}

int main()
{
    const int L = 1.0;
    const double h = 0.001;
    const int n = 1 + (L/h);
    double coeffb = 1.0/(h*h);

    double* f = new double[n]; // f vector
    double* fpp = new double[n];
    double* D = new double[4*n]; // D matrix
    double* b = new double[n];
    

    // Generate the vector f
    std::cout << "f(x) = sin(pi*x)" << std::endl;
    for(int i = 0; i < n; ++i)
    {
        f[i] = sin(M_PI*i*h);
        fpp[i] = -1*(M_PI*M_PI)*sin(M_PI*i*h);
        // The temporary code to check the vector f
        std::cout << f[i] << std::endl;
    }

    GenerateBandedSymMatrix(D,4,n,coeffb); // Generate D matrix
    
    // Generate the vector b
    for(int j = 0; j < n; ++j)
    {
        b[j] = 0.0;   
    }
    
    /*
    b[n-3] =     -coeffb*sin(M_PI*(L+h));
    b[n-2] =  4.0*coeffb*sin(M_PI*(L+h)) -     coeffb*sin(M_PI*(L+2.0*h));
    b[n-1] = -5.0*coeffb*sin(M_PI*(L+h)) + 4.0*coeffb*sin(M_PI*(L+2.0*h))
                - coeffb*sin(M_PI*(L+3.0*h));
    */
    
    b[n-3] += coeffb*(-sin(M_PI*(L+h)));
    b[n-2] += coeffb*(4.0*sin(M_PI*(L+h))-sin(M_PI*(L+2*h)));
    b[n-1] += coeffb*((-5.0)*sin(M_PI*(L+h))+4.0*sin(M_PI*(L+2*h))-sin(M_PI*(L+3*h)));
    
    // Calculate g using BLAS routine
    cblas_dgbmv(CblasColMajor,CblasNoTrans,n,n,0,3,1.0,D,4,f,1,1.0,b,1);

    // Display the result and the actual value of f double prime
    std::cout << "Result" << std::setw(40) << "Solution" << std::endl;
    comparevector(b,fpp,n);

    cblas_daxpy(n,-1.0,fpp,1,b,1);
    double mse = cblas_dnrm2(n,b,1);

    std::cout << "MSE: " << mse << std::endl;



    delete[] f;
    delete[] fpp;
    delete[] D;
    delete[] b;
    return 0;
}