#include <iostream>
#include <cmath>
#include <boost/timer/timer.hpp>


int main() 
{
    boost::timer::auto_cpu_timer t;

    const double a   = round(M_PI * 10000); // 31416
    double estimate1 = 0.0;                 // Computed estimates
    double estimate2 = 1.0;
    int n1           = 0;                   // Iteration counters
    int n2           = 1;

    // Iterate until 10000*estimate is within 0.5 of 31416
    while (fabs(4 * estimate1 * 10000 - a) > 0.5) 
    {
        estimate1 += pow(-1.0,n1)/(2.0*n1 + 1.0);
        n1++;
    }

    while (fabs(2 * estimate2 * 10000 - a) > 0.5) 
    {
        estimate2 *= 4.0*n2*n2 / (4.0*n2*n2 - 1.0);
        n2++;
    }

    // Output result
    std::cout.precision(10);
    std::cout << "PI        : " << M_PI << std::endl;
    std::cout << "PI 5s.f.  : " << a / 10000.0 << std::endl;
    std::cout << "Estimate1 : " << 4.0*estimate1 << std::endl;
    std::cout << "Estimate2 : " << 2.0*estimate2 << std::endl;
    std::cout << "N1        : " << n1 << std::endl;
    std::cout << "N2        : " << n2 << std::endl;

    // Return success
    return 0;
}
