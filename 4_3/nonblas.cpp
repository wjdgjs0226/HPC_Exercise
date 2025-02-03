#include "nonblas.h"
#include <cmath>


//This nonblas function for matrix multiplication is specific for A = (M^T)M
void nonblas(double* A, double* C, int A_i, int A_j, int B_i, int B_j, int C_i, int C_j, const int N, int n)
{                   
    if (n == 1) 
    {
        C[C_j*N+C_i] += A[A_i*N+A_j]*A[B_j*N+B_i];
        return;
    }
    n /= 2;

    //Two By Two Matrix Multiplication
    nonblas(A,C, A_i, A_j, B_i, B_j, C_i, C_j, N, n);
    nonblas(A,C, A_i, A_j+n, B_i+n, B_j, C_i, C_j, N, n);
    nonblas(A,C, A_i, A_j, B_i, B_j+n, C_i, C_j+n, N, n);
    nonblas(A,C, A_i, A_j+n, B_i+n, B_j+n, C_i, C_j+n, N, n);
    nonblas(A,C, A_i+n, A_j, B_i, B_j, C_i+n, C_j, N, n);
    nonblas(A,C, A_i+n, A_j+n, B_i+n, B_j, C_i+n, C_j, N, n);
    nonblas(A,C, A_i+n, A_j, B_i, B_j+n, C_i+n, C_j+n, N, n);
    nonblas(A,C, A_i+n, A_j+n, B_i+n, B_j+n, C_i+n, C_j+n, N, n);
}