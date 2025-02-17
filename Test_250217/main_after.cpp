#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <cblas.h>

// Function to print out the vector
void printvec(std::complex<double>* A, int N)
{
    for (int i = 0; i < N; ++i)
    {
        std::cout << std::setprecision(3) << std::real(A[i]) << " + " << std::imag(A[i]) << "i" << std::endl;
    }
}

// Function to print out the matrix
void printmatrix(std::complex<double>* A, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << std::setprecision(3) << std::setw(10) << std::real(A[j*N+i]) << " + " << std::imag(A[j*N+i]) << "i";
        }
        std::cout << std::endl;
    }
}

void comparevector(std::complex<double>* A, std::complex<double>* B, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << std::setprecision(3) << std::real(A[i]) << " + " << std::imag(A[i]) << "i" << 
        std::setw(40) << std::real(B[i]) << " + " << std::imag(B[i]) << "i" << std::endl;

    }
}

int main()
{
    const int N = 16;
    const double dN = 16.0; // Add double type for N
    const double dx = 1.0/(dN-1.0);
    //const std::complex<double> N_complex = 16.0;
    std::complex<double>* x = new std::complex<double>[N];
    std::complex<double>* t = new std::complex<double>[N];
    std::complex<double>* xresult = new std::complex<double>[N];
    std::complex<double>* W = new std::complex<double>[N*N];
    //return 0;
    
    //Generate W matrix
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            double r = 0.0;
            //double c = -2*M_PI/double(N);
            double c = -2*M_PI/dN;
            std::complex<double> imterm = std::complex<double>(r,c);
            std::complex<double> omega = std::exp(imterm);
            std::complex<double> term = std::complex<double>(1.0/sqrt(dN),0.0); //Make the term with complex data type
            W[j*N+i] = term*std::pow(omega,j*i);
        }
    }
    
    // Generate X matrix
    for (int k = 0; k < N; ++k)
    {
        //double term = cos(2*M_PI*k*dx)+cos(6*M_PI*k*dx)+1;
        double term = cos(2.0*M_PI*k*dx)+cos(6.0*M_PI*k*dx)+1;
        x[k]=std::complex<double>(term,0.0);
    }

    // Use BLAS routine
    std::complex<double> alpha = 1.0;
    std::complex<double> beta = 0.0;
    cblas_zgemv(CblasColMajor,CblasNoTrans,N,N,&alpha,W,N,x,1,&beta,xresult,1);

    // Print x
    std::cout<<std::endl;
    std::cout << "x: " << std::endl;
    printvec(x,N);

    // Print the result of first iteration
    std::cout<<std::endl;
    std::cout << "Iteration 1: " << std::endl;
    printvec(xresult,N);

    cblas_zgemv(CblasColMajor,CblasNoTrans,N,N,&alpha,W,N,xresult,1,&beta,t,1);


    
    //Apply X = Wx three more times
    for(int l = 0; l < 3; ++l)
    {
        std::cout << std::endl;
        cblas_zgemv(CblasColMajor,CblasNoTrans,N,N,&alpha,W,N,xresult,1,&beta,t,1); // X = Wx
        std::cout << "Iteration " << l+2 << ": " << std::endl; 
        cblas_zcopy(N,t,1,xresult,1); // Move the result to xresult
        printvec(xresult,N); // Print out xresult at each iteration
    }


    //Compare the result of fourth iteration and the original x
    std::cout<<std::endl;
    std::cout << "x" << std::setw(50) << "X_4" << std::endl;
    comparevector(x,xresult,N);

    //Calculate the euclidian norm
    std::complex<double> newalpha = -1.0;
    cblas_zaxpy(N,&newalpha,x,1,t,1);
    double euc = cblas_dznrm2(N,t,1);

    // Print the Euclidian Norm
    std::cout<<std::endl;
    std::cout << "Euclidian Norm: " << euc << std::endl;
    

    delete[] W;
    delete[] x;
    delete[] t;
    return 0;
}