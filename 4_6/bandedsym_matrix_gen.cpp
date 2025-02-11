/* Function to Generate Reduced Symmetic Matrix*/

#include <iostream>
#include <cmath>

void bandedsym_matrix_gen(double* A, int ldA, int N, double dx, double ts)
{   
    double beta = ts/dx/dx; 
    double alpha = 1.0 - 2.0*beta;
    
    A[1] = alpha;
    for (int i = 1; i < N; ++i)
    {
        A[i*ldA] = beta;
        A[i*ldA+1] = alpha;
    }

}

