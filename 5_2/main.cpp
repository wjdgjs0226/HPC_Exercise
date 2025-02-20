#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cblas.h>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include "LAPACK_bandedsym_matrix_gen.h"

#define F77NAME(x) x##_
extern "C" 
{
    void F77NAME(dsbev)(const char& v, const char& ul, const int& N, const int& KD, 
                        double* A, const int& ldA, 
                        double* W, double* Z, const int& ldZ, 
                        double* work, int* info);

    void F77NAME(dgbtrf)(const int& M, const int& N, const int& KL,
                        const int& KU, double* A, const int& lda,
                        int* ipiv, int* info);

    void F77NAME(dgbtrs)(const char& TRANS, const int& N, const int& KL,
                        const int& KU, const int& NRHS,
                        const double* A, const int& lda,
                        int* ipiv, double* B, const int& ldb, int* info);
        
}

namespace po = boost::program_options;

int main(int argc, char* argv[])
{

    boost::timer::auto_cpu_timer t;

    // Get the user input using boost library
    po::options_description opts("Calculate the transient heat equation in one dimension, based on the given number of grid points to use, the time-step size and the number of time steps.");
    opts.add_options()
        ("gpoints", po::value<int>()->default_value(21),"Numer of grid points")
        ("ts_size", po::value<double>()->default_value(0.001), "Timestep size")
        ("ts_number", po::value<int>()->default_value(200), "Number of timesteps")
        ("help",       "Print help message.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << opts << std::endl;
    }

    // Required Variables
    const int gpoints = vm["gpoints"].as<int>(); // number of gridpoints
    const double ts_size = vm["ts_size"].as<double>(); // timestep size
    const int ts_number = vm["ts_number"].as<int>(); // number of timesteps

    const int kl = 1;
    const int ku = 1;
    const int ldA = 1+2*kl+ku; // Symmetric banded matrix (no lower diagonal)
    // const int reduced_gpoints = gpoints - 2; // Reduced Points
    double L = 1.0; // Length of the domain
    double dx = L/(gpoints-1); // Grid size
    double* A = new double[ldA*gpoints]; // A Matrix for U^(k+1) = A*U^k
    double* u = new double[gpoints]; // U Vector

    //Display the parameters
    std::cout << "Number of grindpoints: " << gpoints << std::endl;
    std::cout << "dx: " << dx << std::endl;
    std::cout << "ts: " << ts_size <<std::endl;
    std::cout << "nu: " << ts_size/dx/dx << std::endl;
    
    

    // Populate the Tridiagonal Matrix A
    LAPACK_banded_matrix_gen(A,ldA,gpoints,kl,dx,ts_size);

    //Solve the Eigenvalue problem
    int info;
    double * W = new double[gpoints];
    double * Z = new double[gpoints*gpoints];
    double * work = new double[3*gpoints-2];
    
    // Offset ptr A by 2, as SBEV wants diagonal and lower-diagonal.
    // But we use LDA=4, as this is the memory layout.
    F77NAME(dsbev)('V','L',gpoints,1,A+2,ldA,W,Z,gpoints,work, &info);

    // Print out the eigenvalue
    for (int i = 0; i < gpoints; ++i)
    {
        std::cout << "W"<< i<< ": " << W[i] << std::endl;
    }

    // Re-generate A for implicit time-integration
    LAPACK_banded_matrix_gen(A,ldA,gpoints,kl,dx,-ts_size);

    // To impose Dirichlet boundary conditions, we zero the off-diagonal entries
    // in the first and last rows of the matrix
    A[ldA+1] = 0.0;
    A[(gpoints-2)*ldA+3] = 0.0;

    // Enforce the boundary condition
    u[0] = 0;
    for (int i = 1; i < gpoints-1; ++i)
    {
        u[i] = sin(M_PI*i*dx);
    }

    std::cout << "Initial Condition: " << std::endl;
    for (int i = 0; i < gpoints; ++i)
    {
        std::cout << u[i] << std::endl;
    }

    // Pre-factor the matrix
    int* ipiv = new int[gpoints];
    F77NAME(dgbtrf)(gpoints, gpoints, kl, ku, A, ldA, ipiv, &info);

    // Run the integration
    for (int i = 0; i < ts_number; ++i)
    {
        F77NAME(dgbtrs)('N', gpoints, kl, ku, 1, A, ldA, ipiv, u, gpoints, &info);
    }
    
    std::cout << "Final Solution: " << std::endl;
    for (int i = 0; i < gpoints; ++i)
    {
        std::cout << u[i] << std::endl;
    }

    // Clear the Memory
    delete[] A;
    delete[] u;
    delete[] W;
    delete[] Z;
    delete[] work;
    delete[] ipiv;
    return 0;
}