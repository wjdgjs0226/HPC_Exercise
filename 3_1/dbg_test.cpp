#include "dbg.h"
#include <iostream>

#define BOOST_TEST_MODULE PopulateTestSuite

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( Populate1 )
{
    const int N = 1;
    double* M = new double[N*N];
    populateMatrix(M,N);

    BOOST_CHECK(M[0] == 1.0);

    delete[] M;
}

BOOST_AUTO_TEST_CASE( Populate2 )
{
    const int N = 2;
    double* M = new double[N*N];
    populateMatrix(M,N);

    const double f = pow(exp(1.0/N), 2.0);
    BOOST_CHECK_CLOSE( M[0], 1.0,     1e-08 );
    BOOST_CHECK_CLOSE( M[1], 1.0 / f, 1e-08 );
    BOOST_CHECK_CLOSE( M[2], f,       1e-08 );
    BOOST_CHECK_CLOSE( M[3], 1.0,     1e-08 );
}