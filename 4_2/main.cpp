#include "nonblas.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cblas.h>
#include <boost/program_options.hpp>
#define F77NAME(x) x##_

extern "C"
{
    void F77NAME(dgemm)(const char& transA, const char& transB, 
    const int& M, const int& N, const int& K, const double& alpha, 
    double* A, const int& lda, 
    double* B, const int& ldb, 
    const double& beta,
    double* C, const int& ldc);
}

namespace po = boost::program_options;

int main(int argc, char* argv[])
{

    po::options_description opts("Computes the Matrix-Matrix Multiplication using blas library.");
    opts.add_options()
        ("size", po::value<int>()->default_value(2),
                 "Numer of rows/columns (2^n)")
        ("help",       "Print help message.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    const int n = vm["size"].as<int>();

    const int M = pow(2,n);
    const int N = M;
    const int K = M;

    double* A = new double[M*K];
    double* B = new double[N*K];
    double* C = new double[M*N]; 
    double* D = new double[M*N];
    double* E = new double[M*N];

    srand(time(0));

    for(int i = 0; i < M*N; ++i)
    {
        A[i] = double(rand()) / RAND_MAX;
        B[i] = double(rand()) / RAND_MAX;
    }

    F77NAME(dgemm)('N','N',M,N,K,1,A,M,B,K,0,C,M);
    cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,A,M,B,K,0,D,M);
    nonblas(A,B,E,0,0,0,0,0,0,N,N);


    // NOTE: FORTRAN Codes assume column-major
    for(int j = 0; j < M; ++j)
    {
        for (int k = 0; k < M; ++k) 
        {
            std::cout << A[k*M+j] << " "; 
        } 
        std::cout << std::setw(30);
        for (int m = 0; m < M; ++m) 
        {
            std::cout << B[m*M+j] << " "; 
        }

        std::cout << std::setw(30);
        for (int n = 0; n < M; ++n) 
        {
            std::cout << C[n*M+j] << " "; 
        }

        std::cout << std::setw(30);
        for (int p = 0; p < M; ++p) 
        {
            std::cout << D[p*M+j] << " "; 
        }  

        std::cout << std::endl; 
    } 

    std::cout << " " << std::endl; 

    for(int o = 0; o < M; ++o)
    {
        for (int p = 0; p < M; ++p) 
        {
            std::cout << D[p*M+o] << " "; 
        } 
        std::cout << std::endl;
    }

    
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] E;

    return 0;
}