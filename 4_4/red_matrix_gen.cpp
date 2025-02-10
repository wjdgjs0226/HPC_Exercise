/* Function to Generate Reduced Symmetic Matrix*/

#include <iostream>
#include <cmath>

void red_matrix_gen(double* A, int N, double dx, double lam)
{
    double alpha = (-2.0/(dx*dx))-lam;
    double beta = 1.0/(dx*dx);
    A[0] = alpha;
    for (int i = 1; i < N; ++i)
    {
        A[i*N+i-1] = beta;
        A[i*N+i] = alpha;
    }
}

