#include <iostream>
#include <sstream>
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

    // Initialize the constant to send
    int userinput = 0;

    /*
    std::cout<< "Rank: " << world_rank << "     User Input: " << userinput << std::endl;
    std::cout << std::endl;
    */

    if(world_rank == 0)
    {
        std::string input;
        std::cout << "Type the integer to use: ";
        std::cin >> input;
        std::stringstream S(input);
        S >> userinput;

    }
    else
    {
        // Other processes rank > 0 wait for a number to be received first.
        MPI_Recv(&userinput,1,MPI_INT,world_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        std::cout << "Process " << world_rank << "        received " << userinput << "      from rank " << world_rank - 1 << std::endl;
    }


    MPI_Send(&userinput,1,MPI_INT,(world_rank+1) % world_size,0,MPI_COMM_WORLD); // Make sure the last process sends the data to the first process

    // Only rank 0 now needs to receive the number from the last process.
    if (world_rank == 0) 
    {
        MPI_Recv(&userinput, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        std::cout << "Process " << world_rank << "        received " << userinput << "       from rank " << world_size - 1 << std::endl;
    }

    MPI_Finalize();

    return 0;
}