#ifndef LBMG
#define LBMG
void LAPACK_bandedsym_matrix_gen(double* A, int ldA, int N, int KL, double dx, double ts);
void LAPACK_banded_matrix_gen(double* A, int ldA, int N, int KL, double dx, double ts);
#endif