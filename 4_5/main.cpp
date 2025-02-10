#include <iostream>
#include <cmath>
#include <iomanip>
#include "red_matrix_gen.h"
#include "forcingfunc.h"
#include "conjugate_gradient.h"
#include "cblas.h"

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
    int n = 21;
    int nsv = n-2;
    int hb = 3;
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
    double *f = new double[n];
    double *u = new double[n];
    double *e = new double[n];

    // Generate A matrix (reduced symmetric)
    red_matrix_gen(A,hb,nsv,dx,lambda);

    std::cout << "Helmholtz matrix (symmetric): " << std::endl;
    PrintMatrix(nsv, A);

    // Fill out the forcing function
    cblas_dscal(n, 1.0, u, 1);
    forcingfunc(select,f,u,e,n,lambda,dx);
    
    std::cout << std::endl;
    for (int k = 0; k < n; ++k)
    {
        std::cout << u[k] << std::endl;
    }

    // Conjugate Gradient
    conjugate_gradient(hb,nsv,A,f+1,u+1);
    //conjugate_gradient_solution(nsv,A,f+1,u+1);

    std::cout << "Result" << std::setw(60) << "Analytical Solution" << std::endl;

    for (int j = 0; j < n; ++j)
    {
        std::cout << u[j] << std::setw(60) << e[j] << std::endl;
    }

    delete[] A;
    delete[] f;
    delete[] u;
    delete[] e;
}