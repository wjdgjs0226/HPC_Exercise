/*
 * High-performance Computing
 *
 * Solution to Exercise 4.3
 *
 * Conjugate Gradient algorithm for a symmetric matrix.
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include "cblas.h"
#include "conjugate_gradient.h"

// Solve the linear system
void conjugate_gradient(int n, double* A, double* b, double* x) {
    double* r = new double[n];
    double* p = new double[n];
    double* t = new double[n]; //temporary
    int k;
    double alpha;
    double beta;
    double eps;
    double tol = 0.00001;

    cblas_dcopy(n, b, 1, r, 1);        // r_0 = b (i.e. b)
    cblas_dsymv(CblasRowMajor, CblasUpper, n, -1.0, A, n, x, 1, 1.0, r, 1);  // r_0 = b - A x_0
    cblas_dcopy(n, r, 1, p, 1);        // p_0 = r_0
    k = 0;
    do 
    {
        cblas_dsymv(CblasRowMajor, CblasUpper, n, 1.0, A, n,
                    p, 1, 0.0, t, 1);       // t = A p_k
        alpha = cblas_ddot(n, t, 1, p, 1);  // alpha = p_k^T A p_k
        alpha = cblas_ddot(n, r, 1, r, 1) / alpha; // compute alpha_k
        beta  = cblas_ddot(n, r, 1, r, 1);  // r_k^T r_k

        cblas_daxpy(n, alpha, p, 1, x, 1);  // x_{k+1} = x_k + alpha_k p_k
        cblas_daxpy(n, -alpha, t, 1, r, 1); // r_{k+1} = r_k - alpha_k A p_k

        eps = cblas_dnrm2(n, r, 1);
        std::cout << "Iteration " << k << ": eps=" << eps << std::endl;
        if (eps < tol*tol) 
        {
            break;
        }
        beta = cblas_ddot(n, r, 1, r, 1) / beta;

        cblas_dcopy(n, r, 1, t, 1);
        cblas_daxpy(n, beta, p, 1, t, 1);
        cblas_dcopy(n, t, 1, p, 1);

        k++;
    } while (k < 5000); // Set a maximum number of iterations

    delete[] r;
    delete[] p;
    delete[] t;
}


