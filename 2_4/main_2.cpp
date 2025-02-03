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
    

    std::vector <double> filtered(n);
    fftw_plan q;
    q = fftw_plan_dft_c2r_1d(n, out, &filtered[0], FFTW_ESTIMATE);

    fftw_execute(q); /* repeat as needed */
    fftw_destroy_plan(q);

    double freq_bsize = samplerate/n;


    
    std::ofstream output("filtered_output.txt");

    for (int i = 0; i < n; ++i)
    {
        std::cout << filtered[i] << std::endl;
        output << filtered[i] << std::endl;
    }

    fftw_free(out);
    return 0;
}