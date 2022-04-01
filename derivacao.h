#ifndef __DERIVACAO__
#define __DERIVACAO__

#include "functions.h"

typedef struct newton
{
    void ***hessiana; // matriz de equacoes da hessiana
    double **H_x;     // matriz de resultados da hessiana
    void **gradiente; // vetor de equacoes do gradiente
    double *G_f;      // vetor de resultados do gradiente
    double *X_i;      // vetor de solucoes do polinomio
    int n;            // numero de variaveis
    int k;            // numero de iteracoes utilizadas pelo metodo
    double *aprox_newtonP;
    double eps;
    double *delta;
} NEWTON;

NEWTON *initNewton(FUNCTION *func);
void Gradiente(FUNCTION *func, void **grad);
void Hessiana(FUNCTION *func, void **grad, void ***hessi);
void printMethod(NEWTON *newt);

#endif