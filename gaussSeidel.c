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

void gaussSeidel(LINEAR_SYST_GS *syst)
{
    for (int k = 0; k < 50; k++)
    {
        double soma = 0;
        for (int i = 0; i < syst->size; i++)
        {
            for (int j = 0; j < syst->size; j++)
                if (i != j)
                    soma = syst->A[i][j] * syst->X[i];
            syst->X[i] = 1 / syst->A[i][i] * (syst->b[i] - soma);
        }
    }
}
