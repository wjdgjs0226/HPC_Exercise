#include <iostream>
#include <iomanip>
#include <cmath>
#include "cblas.h"
#include "conjugate_gradient.h"

void conjugate_gradient(int ldA, int N, double* A, double* b, double* x)
{
    double* r = new double[N];
    double* p = new double[N];
    double* t = new double[N]; //temporary
    int k;
    double alpha;
    double beta;
    double eps;
    double tol = 1e-08;

    cblas_dcopy(N, b, 1, r, 1);
    cblas_dsbmv(CblasColMajor,CblasUpper,N,1,-1.0,A,ldA,p,1,0.0,t,1);
    cblas_dcopy(N, r, 1, p, 1);

    // Start Loop
    k = 0; // index starts from zero
    do
    {   
        std::cout << "Iteration " << k << std::endl;
        cblas_dsbmv(CblasColMajor,CblasUpper, N, 1, 1.0, A, ldA, p, 1, 0.0, t, 1); // t = A*p_k
        alpha = cblas_ddot(N, p, 1, t, 1); // alpha = p_k^T A p_k
        alpha = cblas_ddot(N, r, 1, r, 1) / alpha; // Alpha_k
        beta = cblas_ddot(N, r, 1, r, 1); // beta = r^T r 
        
        cblas_daxpy(N, alpha, p, 1, x, 1);
        cblas_daxpy(N, -alpha, t, 1, r, 1);

        eps = cblas_dnrm2(N, r, 1);

        std::cout << "eps: " << eps << std::endl;

        if (eps < tol)
        {
            break;
        }

        beta = cblas_ddot(N,r,1,r,1) / beta;

        cblas_dcopy(N, r, 1, t, 1);
        cblas_daxpy(N, beta, p, 1, t, 1);
        cblas_dcopy(N, t, 1, p, 1);

        k++;
    } while (k < 500);
    
    delete[] r;
    delete[] p;
    delete[] t;
}
