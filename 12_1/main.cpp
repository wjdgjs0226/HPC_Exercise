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

    MPI_Bcast(&userinput,1,MPI_INT,0,MPI_COMM_WORLD);

    std::cout<< "Rank: " << world_rank << "     User Input: " << userinput << std::endl;

    MPI_Finalize();

    return 0;
}