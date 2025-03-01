#include <iostream>
#include <cmath>
#include <mpi.h>
#include <cblas.h>

int main(int argc, char* argv[])
{
    // Initialise MPI.
    int err = MPI_Init(&argc, &argv);
    if (err != MPI_SUCCESS) {
        std::cout << "Failed to initialise MPI" << std::endl;
        return -1;
    }
    
    // Get the world size and the rank
    int world_size;
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Check number of processes is suitable
    if (1024 % world_size) {
        if (world_rank == 0) 
        {
            std::cout << "Error: Number of processes must be 2^n" << std::endl;
        }
        MPI_Finalize();
        return 0;
    }

    // Generate vectors and populate with random numbers
    int n = 1024 / world_size;
    double* x = new double[n];
    double* y = new double[n];
    srand(time(0)+world_rank);

    for (int i = 0; i < n; ++i) 
    {
        x[i] = (double)rand()/RAND_MAX;
        y[i] = (double)rand()/RAND_MAX;
    }

    // Operate dot product at each process
    double dot = cblas_ddot(n,x,1,y,1);
    double normx = cblas_ddot(n,x,1,x,1);
    double normy = cblas_ddot(n,y,1,y,1); // Need to pass norm^2 (Sqrt has to be done after reduction)

    double dot_r;
    double normx_r;
    double normy_r;

    MPI_Reduce(&dot,&dot_r,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&normx,&normx_r,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&normy,&normy_r,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        std::cout << "Dot Product: " << dot_r << std::endl;
        std::cout << "norm x: " << sqrt(normx_r) << std::endl;
        std::cout << "norm y: " << sqrt(normy_r) << std::endl;
    }

    // Deallocate Memory
    delete[] x;
    delete[] y;

    MPI_Finalize();

    return 0;
}