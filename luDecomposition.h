//Gabriel de Oliveira Pontarolo GRR20203895
//Rodrigo Saviam Soffner GRR20205092

#ifndef __LU_DEC__
#define __LU_DEC__


typedef struct indexes
{
    int ia;
    int ib;
} INDEXES;

// struct para representacao de um sistema linear
typedef struct linear_syst_lu
{
    double **L; // matriz de coeficientes fatorados L
    double **U; // matriz de coeficientes fatorados U
    double *X;  // vetor das variaveis
    double *Y;  // Ly = b
    double *b;  // vetor do resultado
    INDEXES *swap_index;
    int swaps;
    int size; // tamanho
} LINEAR_SYST_LU;

LINEAR_SYST_LU *initLSLU(int size);
void deleteLSLU(LINEAR_SYST_LU *syst);
void factorize(LINEAR_SYST_LU *syst);
void solveLU(LINEAR_SYST_LU *syst);

#endif