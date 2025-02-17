#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <cblas.h>

// Function to print out the vector
void printvec(std::complex<double>* A, int N)
{
    for (int i = 0; i < N; ++i)
    {
        std::cout << std::setprecision(3) << std::real(A[i]) << " + " << std::imag(A[i]) << "i" << "   ";
    }
}

int main()
{
    const int N = 16;
    const double dN = 16.0;
    const double dx = 1/16;
    std::complex<double>* x = new std::complex<double>[N];
    std::complex<double>* t = new std::complex<double>[N];
    std::complex<double>* xresult = new std::complex<double>[N];
    std::complex<double>* W = new std::complex<double>[N*N];

    
    //Generate W matrix
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            double r = 0.0;
            double c = -2*M_PI/dN;
            std::complex<double> imterm = std::complex<double>(r,c);
            std::complex<double> omega = std::exp(imterm);
            std::complex<double> term = std::complex<double>((1/sqrt(dN)),0.0);
            W[j*N+i] = term*std::pow(omega,j*i);
        }
    }
    
    // Generate X matrix
    for (int k = 0; k < N; ++k)
    {
        double term = cos(2*M_PI*k*dx)+cos(6*M_PI*k*dx)+1;
        x[k]=std::complex<double>(term,0.0);
    }

    // Use BLAS routine to compute X = Wx for the first time
    std::complex<double> alpha = 1.0;
    std::complex<double> beta = 0.0;
    cblas_zgemv(CblasColMajor,CblasNoTrans,N,N,&alpha,W,N,x,1,&beta,xresult,1);
    printvec(xresult,N/2);

    //Apply X = Wx three more times
    for(int l = 0; l < 3; ++l)
    {
        cblas_zcopy(N,t,1,xresult,1);
        cblas_zgemv(CblasColMajor,CblasNoTrans,N,N,&alpha,W,N,t,1,&beta,xresult,1);
    }
    
    //Calculate the euclidian norm
    std::complex<double> newalpha = -1.0;
    cblas_zaxpy(N,&newalpha,x,1,t,1);
    double euc = cblas_dznrm2(N,t,1);

    std::cout << "Euclidian Norm: " << euc << std::endl;
    

    delete[] W;
    delete[] x;
    delete[] xresult;
    delete[] t;
    return 0;
}