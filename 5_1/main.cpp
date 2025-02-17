#include <iostream>
#include <cmath>
#include <iomanip>
#include "red_matrix_gen.h"
#include "forcingfunc.h"
#include "conjugate_gradient.h"
#include "cblas.h"

#define F77NAME(x) x##_
extern "C" 
{

    void F77NAME(dgbtrf)(const int& n, const int& m, const int& kl, const int& ku, double* A, const int& lda, int* ipiv, int& info);

    void F77NAME(dgbtrs) (const char& trans, const int& n, const int& kl, const int &ku, const int& nrhs, 
    const double* A, const int& lda, const int* ipiv, 
    double* b, const int& ldb, int& info);
}

void FillHelmholtzMatrix(int nsv, double* H, double lam, double dx, int* ipiv) 
{
    const int ldh = 4;      // Diagonal and upper diagonal
    int info;

    const double oodx2 = 1.0/dx/dx;
    //H[1] = -lam - 2.0*oodx2;
    for (int i = 0; i < nsv; ++i) {
        H[i*ldh    ] = 0.0; // Top row 'padding' could be left unset
        H[i*ldh + 1] = oodx2;
        H[i*ldh + 2] = -lam - 2.0*oodx2;
        H[i*ldh + 3] = oodx2;
    }

    F77NAME(dgbtrf)(nsv, nsv, 1, 1, H, ldh, ipiv, info);

    if (info) {
        std::cout << "Failed to LU factorise matrix" << std::endl;
    }
}

void PrintMatrix(int nsv, double* H) 
{
    std::cout.precision(4);
    for (int i = 0; i < nsv; ++i) {
        for (int j = 0; j < nsv; ++j) {
            std::cout << std::setw(6) << H[j*nsv+i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{   
    const int n = 21;
    int nsv = n-2;
    bool select = false;
    double L;



    if(select)
    {
        L = 2.0;
    }
    else
    {
        L = 3.0;
    }

    double dx = L / (n-1);
    double lambda = 1.0;
    double *A = new double[nsv*nsv];
    double *H = new double[nsv*nsv];
    double *f = new double[n];
    double *u = new double[n];
    double *e = new double[n];

    // Varaibles required to use LAPACK
    const int nrhs = 1;
    double *b = new double[n];
    int *ipiv = new int[n];
    int info = 0;

    // Generate A matrix (reduced symmetric)
    red_matrix_gen(A,nsv,dx,lambda);
    FillHelmholtzMatrix(nsv,H,lambda,dx,ipiv);

    std::cout << "Helmholtz matrix (symmetric): " << std::endl;
    PrintMatrix(nsv, A);

    // Fill out the forcing function
    cblas_dscal(n, 1.0, u, 1);
    forcingfunc(select,f,u,e,n,lambda,dx);
    forcingfunc(select,f,b,e,n,lambda,dx);
    
    std::cout << std::endl;
    for (int k = 0; k < n; ++k)
    {
        std::cout << u[k] << std::endl;
    }

    // Conjugate Gradient
    conjugate_gradient(nsv,A,f+1,u+1);

    // LAPACK
    cblas_dcopy(n, f, 1, b, 1);
    F77NAME(dgbtrs)('N', nsv, 1, 1, nrhs, H, 4, ipiv, b+1, nsv, info);


    std::cout << "Result" << std::setw(60) << "Analytical Solution" << std::endl;

    for (int j = 0; j < n; ++j)
    {
        std::cout << u[j] << std::setw(60) << e[j] << std::setw(60) << b[j] << std::endl;
    }

    delete[] A;
    delete[] f;
    delete[] u;
    delete[] b;
    delete[] ipiv;
    delete[] e;
}