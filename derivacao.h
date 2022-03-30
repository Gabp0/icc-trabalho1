#ifndef __DERIVACAO__
#define __DERIVACAO__

#include "functions.h"

typedef struct
{
    void **hessiana;
    void **gradiente;
    double *H_x;
    double *G_f;
    double *X_i;
    int n;
    int it_num;
    double *aprox_newtonP;
    double eps;
    double *delta;
} SOLUCAO;

SOLUCAO *initSolucao(FUNCTION *func);
void Gradiente(FUNCTION *func, void **grad);
void Hessiana(FUNCTION *func, void **grad, void **hessi);

#endif