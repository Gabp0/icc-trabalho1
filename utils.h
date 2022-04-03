#ifndef __UTILS__
#define __UTILS__

#include <stdlib.h>
#include <sys/time.h>

typedef enum
{
    MEM_ALOC,
    INV_POINTER,
    MATHEVAL_ERR
} EXIT_CODE;

double timestamp(void);
void prnVetorFloat(float *x, int n);
void prnVetorDouble(double *x, int n);
void prnVetorLongDouble(long double *x, int n);
double *copyDoubleArray(double *a, int size);
int max(int a, int b);
char *getArgs(int argc, char **argv);
double **initDoubleMatrix(int size);
void exitStatus(EXIT_CODE code);

#endif
