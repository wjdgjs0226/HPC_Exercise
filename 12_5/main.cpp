#include <iostream>
#include <sstream>
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

    // Initialize the required parameters
    int mvsize = 0; // The number of intervals (Defined by the user)

    if(world_rank == 0)
    {
        std::string input;
        std::cout << "Type the size to use. Please type n (2^n): ";
        std::cin >> input;
        std::stringstream S(input);
        S >> mvsize;
        
        mvsize = int(pow(2.0,double(mvsize)));
        // Check the number of intervals is divisible by the number of processes
        if (mvsize % world_size) 
        {     
            std::cout << "Error: The number of intervals must be divisible by the number of processes" << std::endl;
            MPI_Finalize();
            return 0;
        }

    }

    // Send the user-defined size
    MPI_Bcast(&mvsize,1,MPI_INT,0,MPI_COMM_WORLD);

    // Define the vector
    double* x = new double[mvsize];

    srand(time(0)+world_rank);
    // Fill out the vector and broadcast
    if(world_rank == 0)
    {
        for (int i = 0; i < mvsize; ++i) 
        {
            x[i] = (double)rand()/RAND_MAX;
        }
    }

    MPI_Bcast(&x,mvsize,MPI_DOUBLE,0,MPI_COMM_WORLD);

    // Perform sub Matrix-Vector multiplication at each process
    int numel = mvsize/world_size; // Number of vector elements to be derived at each process
    double* A_sub = new double[mvsize*numel];
    double* y_sub = new double[numel]; // An array to store the results from each process

    // Fill out A_sub at each process
    for (int i = 0; i < mvsize*numel; ++i)
    {
        A_sub[i] = (double)rand()/RAND_MAX;
    }

    for (int i = 0; i < numel; ++i)
    {
        y_sub[i] = cblas_ddot(mvsize,A_sub+(i*mvsize),1,x,1);
    }

    delete[] x;
    delete[] A_sub;
    delete[] y_sub;

    MPI_Finalize();

    return 0;
}