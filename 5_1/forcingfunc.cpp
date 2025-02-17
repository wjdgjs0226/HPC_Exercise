/* Function to Generate the f vector according to the forcing function f, Define the Boundary Conditions, and store the exact solution*/

#include <iostream>
#include <cmath>
#include "forcingfunc.h"

/*
* @param   sel     Indication of which forcing function has to be used
* @param   f       Pointer to forcing term storage of length n
* @param   u       Pointer to solution vector storage of length n
* @param   e       Pointer to solution vector storage of length n
* @param   N       Vector dimension
* @param   lam     Lambda coefficient
* @param   dx      Grid spacing
 */
void forcingfunc(bool sel, double* f, double* u, double*e, int N, double lam, double dx)
{
    if (sel)
    {
        for (int i = 0; i < N; ++i)
        {
            f[i] = -(lam+(M_PI*M_PI))*sin(M_PI*(dx*i));
            e[i] = sin(M_PI*dx*i);
        }
        u[0] = sin(0);
        u[N-1] = sin(M_PI*(N-1)*dx);
        f[1] -= u[0]/(dx*dx);
        f[N-2] -= u[N-1]/(dx*dx);
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            f[i] = -(lam+(M_PI*M_PI))*cos(M_PI*(dx*i));
            e[i] = cos(M_PI*dx*i);
        }
        u[0] = cos(0);
        u[N-1] = cos(M_PI*(N-1)*dx);
        f[1] -= u[0]/(dx*dx);
        f[N-2] -= u[N-1]/(dx*dx);
    }
}