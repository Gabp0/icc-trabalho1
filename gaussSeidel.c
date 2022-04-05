// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>
#include "gaussSeidel.h"

LINEAR_SYST_GS *initLSGS(int size)
// Aloca memoria para o sistema linear de tamanho size
{
    LINEAR_SYST_GS *new = malloc(sizeof(LINEAR_SYST_GS));
    if (!new)
        exitStatus(MEM_ALOC);

    new->size = size;
    new->A = initDoubleMatrix(size);

    new->b = malloc(sizeof(double) * size);
    if (!new->b)
        exitStatus(MEM_ALOC);

    new->X = malloc(sizeof(double) * size);
    if (!new->X)
        exitStatus(MEM_ALOC);

    return new;
}

// escolher uma aproximação inicial xo = (xo1, …, xon)
// faça k = 1.
// enquanto k <= N faça:
//   para i := (1, …, n):
//     σ = 0.
//     para j := (1, …, i-1):
//       σ = σ + aij * xj
//     fim para.
//     para j := (i+1, …, n):
//       σ = σ + aij * xoj
//     fim para.
//     xi = (bi - σ) / aii
//   fim para.
//   se ||x-xo|| <= TOL então:
//     retorna x.
//   fim se
//   xo = x.
//   k = k+1.
// fim enquanto.
// imprime mensagem "Número máximo de iterações excedido."

void gaussSeidel(LINEAR_SYST_GS *syst)
{
    double soma;
    for (int k = 0; k < IT_MAX; k++) // numero de iteracoes
    {

        for (int i = 0; i < syst->size; i++)
        {
            soma = 0;
            for (int j = 0; j < syst->size; j++)
                if (i != j)
                    soma += syst->A[i][j] * syst->X[j];

            syst->X[i] = (syst->b[i] - soma) / syst->A[i][i];
        }
        if (fabs(syst->X[k] - syst->X[k - 1]) < TOL)
            return;
    }
}
