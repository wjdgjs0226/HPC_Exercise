/*
 * Solution to Exercise 4.8.
 * Inherited from C++ Exercise 7.6.
 * 
 * Recursive matrix multiplication
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cblas.h>

const int size = 4;
const int RANGE = 5;

// Perform recursive multiplication (requires O(n^2 ln n) operations)

void recursiveMult(double* A, double* B, double* C,
                        int A_i, int A_j, int B_i, int B_j,    
                        int C_i, int C_j, int n) {
    if (n == 1) 
    {
        int index_A = A_j*size+A_i;
        int index_B = B_j*size+B_i;
        int index_C = C_j*size+C_i;
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                    1, 1, 1, 1.0,
                    A+index_A, size, 
                    B+index_B, size, 
                    1.0, C+index_C, size);
        return;
    }
    n /= 2;

    recursiveMult(A,B,C, A_i, A_j, B_i, B_j, C_i, C_j, n);
    recursiveMult(A,B,C, A_i, A_j+n, B_i+n, B_j, C_i, C_j, n);
    recursiveMult(A,B,C, A_i, A_j, B_i, B_j+n, C_i, C_j+n, n);
    recursiveMult(A,B,C, A_i, A_j+n, B_i+n, B_j+n, C_i, C_j+n, n);
    recursiveMult(A,B,C, A_i+n, A_j, B_i, B_j, C_i+n, C_j, n);
    recursiveMult(A,B,C, A_i+n, A_j+n, B_i+n, B_j, C_i+n, C_j, n);
    recursiveMult(A,B,C, A_i+n, A_j,    B_i, B_j+n, C_i+n, C_j+n, n);
    recursiveMult(A,B,C, A_i+n, A_j+n, B_i+n, B_j+n, C_i+n, C_j+n, n);
}


// Perform naive matrix multiplication (requires O(n^3) operations)
void multiply(double* A, double* B, double* C) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[j*size+i] = 0.0;
            for (int k = 0; k < size; k++) {
                C[j*size+i] += A[k*size+i]*B[j*size+k];
            }
        }
    }
}

// Print a matrix
void printMatrix(double* A) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(5) << std::setprecision(2) << A[j*size+i] << "  ";
        }
        std::cout << std::endl;
    }
}

int main() {
    double* A = new double[size*size];
    double* B = new double[size*size];
    double* C = new double[size*size];
    double* D = new double[size*size];

    // Seed random number generator and generate matrices
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i*size+j] = double(rand()) / (RAND_MAX/5.0);
            B[i*size+j] = double(rand()) / (RAND_MAX/5.0);
        }
    }

    // Print matrices
    std::cout << "Matrix A: " << std::endl;
    printMatrix(A);
    std::cout << "Matrix B: " <<std::endl;
    printMatrix(B);

    std::cout << "Matrix C using recursive multiplication: " << std::endl;
    recursiveMult(A,B,C,0,0,0,0,0,0,size);
    printMatrix(C);

    // Perform recursive multiplication and print matrix
    std::cout << "Matrix C: " << std::endl;
    multiply(A,B,D);
    printMatrix(D);



    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;

    return 0;
}
