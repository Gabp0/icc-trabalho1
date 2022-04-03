#ifndef __LU_DEC__
#define __LU_DEC__

typedef struct linear_syst_lu
// struct para representacao de um sistema linear
{
    double **L; // matriz de coeficientes fatorados L
    double **U; // matriz de coeficientes fatorados U
    double *X;  // vetor das variaveis
    double *Y;  // Ly = b
    double *b;  // vetor do resultado
    int size;   // tamanho
} LINEAR_SYST_LU;

LINEAR_SYST_LU *initLSLU(int size);
void deleteLSLU(LINEAR_SYST_LU *syst);
void factorize(LINEAR_SYST_LU *syst);
void solveLU(LINEAR_SYST_LU *syst);

#endif