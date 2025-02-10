/* Function to Generate Reduced Symmetic Matrix*/

#include <iostream>
#include <cmath>

void red_matrix_gen(double* A, int n, int N, double dx, double lam)
{
    double alpha = (-2.0/(dx*dx))-lam;
    double beta = 1.0/(dx*dx);
    A[1] = alpha;
    for (int i = 1; i < N; ++i)
    {
        A[i*n] = beta;
        A[i*n+1] = alpha;
    }

}

