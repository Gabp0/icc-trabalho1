//Gabriel de Oliveira Pontarolo GRR20203895
//Rodrigo Saviam Soffner GRR20205092

#ifndef __NEWTONINEXATO__
#define __NEWTONINEXATO__

#include "functions.h"
#include "gaussSeidel.h"

#define EXPRESSION_MAX_SIZE 1000

typedef struct newton_inexato
{
    void ***hessiana;  // matriz de equacoes da hessiana
    void **gradiente;  // vetor de equacoes do gradiente
    LINEAR_SYST_GS *syst; // sistema linear H(x_i) * delta = - Gf(X_i)
    double *X_i;       // vetor de solucoes do polinomio
    int n;             // numero de variaveis
    double *aprox_newtonI;
    double eps;
} NEWTON_I;

NEWTON_I *initNewtonI(FUNCTION *func);
void NewtonInexato(FUNCTION *func);

#endif