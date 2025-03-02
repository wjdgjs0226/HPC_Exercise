/**
 * High-performance Computing
 *
 * Example code demonstrating the use of the JPEG library to read and write
 * image files to/from arrays.
 */
#include <iostream>
#include <cblas.h>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/program_options.hpp>
using namespace boost::gil;
namespace po = boost::program_options;

#define F77NAME(x) x##_
extern "C" 
{
    void F77NAME(dgesvd)(
        const char& u,
		const char& v,
		const int& M,
		const int& N,
		double* A,
		const int& lda,
		double* S,
		double* U,
		const int& ldu,
		double* VT,
		const int& ldvt,
		double* work,
		int& lwork,
		int* info);
}

void Perform_SVD(char Name,double* A, double* M, int m, int n, int k)
{
    // Perform SVD on each matrix
    double* u = new double[m*m]; // U matrix
    double* vt = new double[n*n]; // V^T matrix
    double* v = new double[n*n]; // V matrix
    int mind = std::min(m,n);

    double* s = new double[mind]; // Storage for singular values
    
    double work_output;
    int info;
    int lwork = -1; // For querying

    F77NAME(dgesvd)('A','A',m,n,M,m,s,u,m,vt,n,&work_output,lwork,&info);
    lwork = (int)work_output;
    double* workr = new double[lwork];
    F77NAME(dgesvd)('A','A',m,n,M,m,s,u,m,vt,n,workr,lwork,&info); // Perform the actual SVD

    // Print out the singular values
    std::cout << Name << " Singular Values: " << std::endl;
    for (int i = 0; i < mind; ++i)
    {
        std::cout << s[i] << "  ";
    }
    std::cout << std::endl;

    // Transpose the matrix
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            v[i*n+j] = vt[j*n+i];
        }
    }
    
    // Get the approximation of matrix
    for (int i = 0; i < k; ++i)
    {
        cblas_dger(CblasColMajor,m,n,s[i],u+(i*m),1,v+(i*n),1,A,m);
    }

    // Clear the memory
    delete[] u;
    delete[] v;
    delete[] vt;
    delete[] s;
    delete[] workr;
    
}

int main(int argc, char* argv[]) 
{
    // Read the image
    rgb8_image_t img;
    read_image("plane.jpg", img, jpeg_tag());

    const int n = img.width();
    const int m = img.height();

    std::cout << "Image dimensions: " << n << " x " << m << std::endl;

    // Extract the pixel data to three matrices
    double* r = new double[n*m];        // Red
    double* ar = new double[n*m];       // Red_Simplified
    double* g = new double[n*m];        // Green
    double* ag = new double[n*m];       // Red_Simplified
    double* b = new double[n*m];        // Blue
    double* ab = new double[n*m];       // Blue_Simplified

    auto imgv = const_view(img);

    for (int x = 0; x < n; ++x) 
    {
        for (int y = 0; y < m; ++y) 
        {
            r[x*m+y] = (int)at_c<0>(imgv(x,y));
            g[x*m+y] = (int)at_c<1>(imgv(x,y));
            b[x*m+y] = (int)at_c<2>(imgv(x,y));
        }
    }

    // Get the user input using boost library
    po::options_description opts("Extract the simplified image using the first k singular values of the three image matrices (r,g,b)");
    opts.add_options()
        ("k", po::value<int>()->default_value(std::min(m,n)),"The value of k")
        ("help",       "Print help message.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << opts << std::endl;
    }

    // Required Variables
    const int k = vm["k"].as<int>(); // number of gridpoints
    
    if(k > std::min(m,n))
    {
        std::cout << "k should be smaller than the value of min(number of rows, number of columns)" << std::endl;
        return 0;
    }

    Perform_SVD('R',ar,r,m,n,k);
    Perform_SVD('G',ag,g,m,n,k);
    Perform_SVD('B',ab,b,m,n,k);
    
    
    
    // Generate a new image to write out
    rgb8_image_t out(n, m);
    auto outv = view(out);
    for (int x = 0; x < n; ++x) 
    {
        for (int y = 0; y < m; ++y) 
        {
            outv(x,y) = rgb8_pixel_t(ar[x*m+y], ag[x*m+y], ab[x*m+y]);
        }
    }
    

    write_view("output.jpg", outv, jpeg_tag());
    

    delete[] r;
    delete[] ar;
    delete[] g;
    delete[] ag;
    delete[] b;
    delete[] ab;
}
