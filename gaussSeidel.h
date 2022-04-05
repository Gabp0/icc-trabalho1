// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#ifndef __GAUSSSEILDEL__
#define __GAUSSSEILDEL__

#define IT_MAX 50
#define TOL 0.000001

typedef struct linear_syst_gs
// struct para representacao de um sistema linear
{
    double **A; // matriz de coeficientes A
    double *X;  // vetor das variaveis
    double *b;  // vetor do resultado
    int size;   // tamanho
} LINEAR_SYST_GS;

void gaussSeidel(LINEAR_SYST_GS *syst);
LINEAR_SYST_GS *initLSGS(int size);

#endif
