#ifndef __GAUSS__
#define __GAUSS__

typedef struct linear_syst
// struct para representacao de um sistema linear
{
    double **A; // matriz de coeficientes A
    double *X;  // vetor das variaveis
    double *b;  // vetor do resultado
    int size;   // tamanho
} LINEAR_SYST;

LINEAR_SYST *initLS(int size);
void deleteLS(LINEAR_SYST *syst);
void gaussianElimination(LINEAR_SYST *syst);

#endif
