#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cblas.h>
#include <boost/program_options.hpp>
#include "bandedsym_matrix_gen.h"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
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

    const int ldA = 2; // Symmetric Matrix
    const int reduced_gpoints = gpoints - 2; // Reduced Points
    double L = 1.0; // Length of the domain
    double dx = L/(gpoints-1); // Grid size
    double* A = new double[ldA*reduced_gpoints]; // A Matrix for U^(k+1) = A*U^k
    double* u = new double[gpoints]; // U Vector
    double* u1 = new double[gpoints]; // U^(k+1) Vector
    
    

    // Populate the Tridiagonal Matrix A
    bandedsym_matrix_gen(A,ldA,reduced_gpoints,dx,ts_size);

    // Enforce the boundary condition
    u[0] = 0;
    u1[0] = 0;
    for (int i = 1; i < gpoints-1; ++i)
    {
        u[i] = sin(M_PI*i*dx);
    }

    std::ofstream output("result.txt");
    for (int l = 0; l < gpoints; ++l)
    {
        output << u[l] << std::setw(10);
    }
    output << std::endl;

    // Run the integration
    int k = 1; // Variable to count the number of timesteps processed
    do
    {
        cblas_dsbmv(CblasColMajor,CblasUpper,reduced_gpoints,1,1.0,A,ldA,u+1,1,0.0,u1+1,1);
        cblas_dcopy(gpoints,u1,1,u,1);
        for (int m = 0; m < gpoints; ++m)
        {
            output << u[m] << std::setw(10);
        }
        output << std::endl;
        k++;
    } while (k < ts_number);
    
    // Print out the result
    std::cout << "Result:" << std::endl;
    for (int j = 0; j < gpoints; ++j)
    {
        std::setprecision(5);
        std::cout << j*dx << std::setw(30) << u[j] << std::endl;
    }

    // Clear the Memory
    delete[] A;
    delete[] u;
    delete[] u1;
}