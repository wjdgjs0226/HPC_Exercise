/* Function to Generate Banded Symmetic Matrix for LAPACK Library user*/

#include <iostream>
#include <cmath>


void LAPACK_bandedsym_matrix_gen(double* A, int ldA, int N, int KL, double dx, double ts)
{   
    double beta = ts/dx/dx; 
    double alpha = 1.0 - 2.0*beta;
    
    A[ldA] = alpha;
    for (int i = 1; i < N; ++i)
    {
        A[i*ldA+KL] = beta;
        A[i*ldA+KL+1] = alpha;
    }

}

void LAPACK_banded_matrix_gen(double* A, int ldA, int N, int KL, double dx, double ts)
{   
    double beta = ts/dx/dx; 
    double alpha = 1.0 - 2.0*beta;
    
    for (int i = 0; i < N; ++i)
    {
        A[i*ldA+KL] = beta;
        A[i*ldA+KL+1] = alpha;
        A[i*ldA+KL+2] = beta;
    }

}

