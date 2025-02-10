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
#include "conjugate_gradient_solution.h"

// Solve the linear system
void conjugate_gradient_solution(int nsv, double* H, double* f, double* u) {
    double* r = new double[nsv];
    double* p = new double[nsv];
    double* t = new double[nsv]; //temp
    int k;
    double alpha;
    double beta;
    double eps;
    double tol = 1e-08;

    cblas_dcopy(nsv, f, 1, r, 1);     // r_0 = b (i.e. f)
    cblas_dsymv(CblasColMajor, CblasUpper, nsv, -1.0, H, nsv,
                    u, 1, 1.0, r, 1); // r_0 = b - A x_0
    cblas_dcopy(nsv, r, 1, p, 1);     // p_0 = r_0
    k = 0;
    do {
        std::cout << "Iteration " << k << std::endl;
        cblas_dsymv(CblasColMajor, CblasUpper, nsv, 1.0, H, nsv,
                    p, 1, 0.0, t, 1);
        alpha = cblas_ddot(nsv, t, 1, p, 1);
        alpha = cblas_ddot(nsv, r, 1, r, 1) / alpha; // compute alpha_k
        beta  = cblas_ddot(nsv, r, 1, r, 1);

        cblas_daxpy(nsv, alpha, p, 1, u, 1);  // x_{k+1} = x_k + alpha_k p_k
        cblas_daxpy(nsv, -alpha, t, 1, r, 1); // r_{k+1} = r_k - alpha_k A p_k

        eps = cblas_dnrm2(nsv, r, 1);
        std::cout << "eps: " << eps << " tol=" << tol << std::endl;
        if (eps < tol) {
            break;
        }
        beta = cblas_ddot(nsv, r, 1, r, 1) / beta;

        cblas_dcopy(nsv, r, 1, t, 1);
        cblas_daxpy(nsv, beta, p, 1, t, 1);
        cblas_dcopy(nsv, t, 1, p, 1);

        k++;
    } while (k < 500);

    delete[] r;
    delete[] p;
    delete[] t;
}


