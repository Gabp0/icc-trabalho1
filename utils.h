// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#ifndef __UTILS__
#define __UTILS__

#include <stdlib.h>
#include <sys/time.h>

#define MEM_ALOC 101
#define INV_POINTER 102
#define MATHEVAL_ERR 103
#define ARG_NUM 104
#define ARG_INV 105
#define FOPEN_ERR 106

double timestamp(void);
void prnVetorFloat(float *x, int n);
void prnVetorDouble(double *x, int n);
void prnVetorLongDouble(long double *x, int n);
double *copyDoubleArray(double *a, int size);
int max(int a, int b, int c);
char *getArgs(int argc, char **argv);
double **initDoubleMatrix(int size);
void exitStatus(int code);
double norma(double *array, int size);

#endif
