/*
 * Solution to Exercise 7.6. Equivalent to the solution of Exercise 1.4 in HPC
 *
 * Recursive matrix multiplication
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int SIZE = 8;
const int RANGE = 5;

// Perform recursive multiplication (requires O(n^2 ln n) operations)
void recursiveMult(int A[][SIZE], int B[][SIZE], int C[][SIZE],
                        int A_i, int A_j, int B_i, int B_j,    
                        int C_i, int C_j, int n) {
    if (n == 1) {
        C[C_i][C_j] += A[A_i][A_j] * B[B_i][B_j];
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
void multiply(int A[][SIZE], int B[][SIZE], int C[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Print a matrix
void printMatrix(int A[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << setw(5) << A[i][j] << "  ";
        }
        cout << endl;
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

    // Seed random number generator and generate matrices
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand()%RANGE;
            B[i][j] = rand()%RANGE;
            C[i][j] = 0;
        }
    }

    // Print matrices
    cout << "Matrix A: " << endl;
    printMatrix(A);
    cout << "Matrix B: " <<endl;
    printMatrix(B);

    // Perform recursive multiplication and print matrix
    cout << "Matrix C: " << endl;
    recursiveMult(A,B,C,0,0,0,0,0,0,SIZE);
    printMatrix(C);

    return 0;
}
