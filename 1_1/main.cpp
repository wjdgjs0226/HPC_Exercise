#include <cmath>
#include <iostream>
#include <iomanip>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

void fibonacci(int* A)
{
    int result = A[0] + A[1];

    A[0] = A[1];
    A[1] = result;

}

int main(int argc, char* argv[])
{   
    // Specify the options we want to make available to the user
    po::options_description opts("Calculate the first n Fibonacci numbers, in which n can be defined by the user ");
    opts.add_options()
        ("n", po::value<int>()->default_value(15),
                 "Size of vector to sort.")
        ("help",       "Print help message.");

    // Tell Boost to parse the command-line arguments using the list of
    // possible options and generate a map (vm) containing the options and
    // values actually specified by the user.
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    if (vm.count("help")) 
    {
        std::cout << opts << std::endl;
        return 0;
    }

    const int n = vm["n"].as<int>();
    
    int* A = new int[2];
    A[0] = 1;
    A[1] = 1;

    int i = 2;
    std::cout << "Result: " << A[0] << std::setw(5) << A[1] << std::setw(5);
   do
    {
        fibonacci(A);
        std::cout << A[1] << std::setw(5);
        ++i;
    } while (i < n);
    
    std::cout << std::endl;

    delete[] A;
    return 0;
}