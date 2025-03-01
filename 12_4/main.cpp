#include <iostream>
#include <sstream>
#include <cmath>
#include <mpi.h>

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
    int n = 0; // The number of intervals (Defined by the user)

    if(world_rank == 0)
    {
        std::string input;
        std::cout << "Type the number of intervals to use: ";
        std::cin >> input;
        std::stringstream S(input);
        S >> n;

        // Check the number of intervals is divisible by the number of processes
        if (n % world_size) 
        {     
            std::cout << "Error: The number of intervals must be divisible by the number of processes" << std::endl;
            MPI_Finalize();
            return 0;
        }
    }

    // Send the user-defined number of intervals
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    int numel = n/world_size; // The number of intervals to be calculated in each process
    double y_sum = 0; // The array to store each value
    double interval_size = 1.0/double(n); // The size of each interval
    int begin = world_rank*numel;

    for(int i = 0; i < numel; ++i)
    {
        y_sum += (1 / (1 + pow(double(begin+i)*interval_size, 2.0))) + (1 / (1 + pow(double(begin+i+1)*interval_size, 2.0)));
    }

    double y_sum_r = 0;

    MPI_Reduce(&y_sum,&y_sum_r,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    y_sum_r = y_sum_r*interval_size*0.5;

    if (world_rank == 0)
    {
        std::cout << "Interval Size: " << interval_size << std::endl;
        std::cout << "Integration Result: " << y_sum_r << std::endl;
        std::cout << "Pi approximation: " << y_sum_r*4.0 << std::endl;
    }

    MPI_Finalize();

    return 0;
}