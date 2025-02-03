#include <iostream>
#include <boost/program_options.hpp>
#include "insert.h"
#include "insertionsort.h"
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    // Specify the options we want to make available to the user
    po::options_description opts("Sorts a list of random numbers using the insertion sort algorithm.");
    opts.add_options()
        ("size", po::value<int>()->default_value(10),
                 "Size of vector to sort.")
        ("min",  po::value<int>()->default_value(0),
                 "Minimum value of numbers to generate.")
        ("max",  po::value<int>()->default_value(10),
                 "Maximum value of numbers to generate.")
        ("descending", "Indicate the array should be reversed.")
        ("help",       "Print help message.");

    // Tell Boost to parse the command-line arguments using the list of
    // possible options and generate a map (vm) containing the options and
    // values actually specified by the user.
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    // Check if the user gave the "--help" option and print the usage.
    if (vm.count("help")) {
        std::cout << "Performs an insertion sort algorithm on an array of "
             << "random numbers." << std::endl;
        std::cout << opts << std::endl;
        return 0;
    }

// Extract the values given to other parameters using the appropriate
    // data type.
    const int n = vm["size"].as<int>();
    const int range = vm["max"].as<int>() - vm["min"].as<int>();
    const int offset = vm["min"].as<int>();
    const bool desc = vm.count("descending");

    float *randarray = new float[n];
    for (int i=0; i<n; ++i)
    {
        randarray[i] = float(rand()) / RAND_MAX * range + offset;
        std::cout << randarray[i] << std::endl;
    }
    std::cout << "" << std::endl;

    // Sort array
    insertionsort(randarray,n,desc);

    // Print sorted array
    std::cout << "Sorted random numbers: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << randarray[i] << std::endl;
    }

    delete[] randarray;

    return 0;
}