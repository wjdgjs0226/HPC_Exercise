#include <cmath>

void populateMatrix(double* M, const int N) {
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) { //fix: j to i
            double alpha = pow(exp(double(i)/N), 2.0); //int to double
            double beta  = pow(exp(double(i)/N), 2.0);
            M[i*N+j] = alpha / beta;
        }
    }
}

void setup(const int N) {
    double* M = new double[N*N];
    populateMatrix(M, N);
    delete[] M;
}