#ifndef __NEWTONPADRAO__
#define __NEWTONPADRAO__

#include "functions.h"
#include "gaussianElimination.h"

#define EXPRESSION_MAX_SIZE 1000

typedef struct newton_padrao
{
    void ***hessiana;  // matriz de equacoes da hessiana
    void **gradiente;  // vetor de equacoes do gradiente
    LINEAR_SYST *syst; // sistema linear H(x_i) * delta = - Gf(X_i)
    double *X_i;       // vetor de solucoes do polinomio
    int n;             // numero de variaveis
    double *aprox_newtonP;
    double eps;
} NEWTON_P;

NEWTON_P *initNewtonP(FUNCTION *func);
void NewtonPadrao(FUNCTION *func);

#endif