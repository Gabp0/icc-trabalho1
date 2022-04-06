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
    double soma;
    double *xk_m1 = malloc(sizeof(double) * syst->size);
    if (!xk_m1)
        exitStatus(MEM_ALOC);

    for (int k = 0; k < IT_MAX; k++) // numero de iteracoes
    {

        for (int i = 0; i < syst->size; i++)
        {
            soma = 0;
            for (int j = 0; j < syst->size; j++)
            {
                if (i != j)
                    soma += syst->A[i][j] * syst->X[j];
            }
            xk_m1[i] = syst->X[i];
            syst->X[i] = (syst->b[i] - soma) / syst->A[i][i];
        }
        if (k > 0)
            if (fabs(norma(syst->X, syst->size) - norma(xk_m1, syst->size)) < TOL)
                break;
    }
    free(xk_m1);
    return;
}

void deleteLSGS(LINEAR_SYST_GS *syst)
{
    if (!syst)
        exitStatus(INV_POINTER);

    for (int i = 0; i < syst->size; i++)
        free(syst->A[i]);
    free(syst->A);
    free(syst->b);
    free(syst->X);
    free(syst);
}
