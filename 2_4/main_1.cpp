#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fftw3.h>

int main()
{   
    std::vector <double> s;
    double val;
    std::ifstream input("signal.txt");
    
    while (!input.eof()) 
    {
    input >> val;
    s.push_back(val);
    }
    input.close();

    const int n = s.size();
    const int n_out = n/2 + 1;
    const double samplerate = 1000.0;
    fftw_complex *out;
    fftw_plan p; 
     
    out = new fftw_complex[n_out];
    p = fftw_plan_dft_r2c_1d(n, &s[0], out,
                               FFTW_ESTIMATE);

    fftw_execute(p); /* repeat as needed */
    fftw_destroy_plan(p);
    

    double freq_bsize = samplerate/n;

    std::vector <double> result(n_out, 0.0);

    std::cout << "The sample size: " << n << std::endl;
    std::cout << "output size: " << n_out << std::endl;
    std::cout << "The frequency bin size: " << freq_bsize << std::endl;
    std::ofstream output("output.txt");

    for (int i = 0; i < n_out; ++i)
    {
        result[i] = sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1])/(n);
        if (i > 0)
        {
            result[i] *= 2.0;
        }

        
        std::cout << i*freq_bsize << " " << result[i] << std::endl;
        output << i*freq_bsize << std::setw(15) << result[i] << std::endl;
    }

    fftw_free(out);
    return 0;
}