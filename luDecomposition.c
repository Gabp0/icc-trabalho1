//Gabriel de Oliveira Pontarolo GRR20203895
//Rodrigo Saviam Soffner GRR20205092

#include "luDecomposition.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "utils.h"

LINEAR_SYST_LU *initLSLU(int size)
// Aloca memoria para o sistema linear LU de tamanho size
{
    LINEAR_SYST_LU *new = malloc(sizeof(LINEAR_SYST_LU));
    if (!new)
        exitStatus(MEM_ALOC);

    new->size = size;

    new->L = malloc(sizeof(double *) * size);
    if (!new->L)
        exitStatus(MEM_ALOC);
    for (int i = 0; i < size; i++)
    {
        new->L[i] = calloc(sizeof(double), size);
        if (!new->L[i])
            exitStatus(MEM_ALOC);
    }

    new->U = malloc(sizeof(double *) * size);
    if (!new->U)
        exitStatus(MEM_ALOC);
    for (int i = 0; i < size; i++)
    {
        new->U[i] = calloc(sizeof(double), size);
        if (!new->U[i])
            exitStatus(MEM_ALOC);
    }

    new->b = calloc(sizeof(double), size);
    if (!new->b)
        exitStatus(MEM_ALOC);

    new->X = calloc(sizeof(double), size);
    if (!new->X)
        exitStatus(MEM_ALOC);

    new->Y = calloc(sizeof(double), size);
    if (!new->Y)
        exitStatus(MEM_ALOC);

    new->swaps = 0;

    return new;
}

void _swapBLines(LINEAR_SYST_LU *syst)
{
    double aux;

    for (int i = 0; i < syst->swaps; i++)
    {
        aux = syst->b[syst->swap_index[i].ia];
        syst->b[syst->swap_index[i].ia] = syst->b[syst->swap_index[i].ib];
        syst->b[syst->swap_index[i].ib] = aux;
    }
}

void _pivotLU(LINEAR_SYST_LU *syst, int i)
{
    double max = fabs(syst->U[i][i]);
    int max_i = i;
    for (int j = i + 1; j < syst->size; ++j)
    {
        double v = fabs(syst->U[j][i]);
        if (v > max)
        {
            max = v;
            max_i = j;
        }
    }
    if (max_i != i)
    {
        double *tmp = syst->U[i];
        syst->U[i] = syst->U[max_i];
        syst->U[max_i] = tmp;

        syst->swap_index = realloc(syst->swap_index, sizeof(INDEXES) * syst->swaps + 1);
        syst->swap_index[syst->swaps].ia = i;
        syst->swap_index[syst->swaps].ib = max_i;
        syst->swaps++;
    }
}

void factorize(LINEAR_SYST_LU *syst)
{
    syst->swaps = 0;
    if (syst->swap_index)
        free(syst->swap_index);
    for (int i = 0; i < syst->size; ++i)
    {
        _pivotLU(syst, i);
        syst->L[i][i] = 1.0;
        for (int k = i + 1; k < syst->size; ++k)
        {
            syst->L[k][i] = syst->U[k][i] / syst->U[i][i];
            if (isnan(syst->L[k][i]))
                printf("ERRO: %g\n", syst->U[i][i]);
            syst->U[k][i] = 0.0;
            for (int j = i + 1; j < syst->size; ++j)
                syst->U[k][j] -= syst->U[i][j] * syst->L[k][i];
        }
    }
}

void _subsLU(LINEAR_SYST_LU *syst)
{
    _swapBLines(syst);
    for (int i = 0; i < syst->size; ++i)
    {
        syst->Y[i] = syst->b[i];
        for (int j = 0; j < i; j++)
            syst->Y[i] -= syst->L[i][j] * syst->Y[j];
    }
}

void _retrossubsLU(LINEAR_SYST_LU *syst)
{
    for (int i = syst->size - 1; i >= 0; --i)
    {
        syst->X[i] = syst->Y[i];
        for (int j = i + 1; j < syst->size; j++)
            syst->X[i] -= syst->U[i][j] * syst->X[j];
        syst->X[i] /= syst->U[i][i];
    }
}

void solveLU(LINEAR_SYST_LU *syst)
{
    _subsLU(syst);
    _retrossubsLU(syst);
}

void deleteLSLU(LINEAR_SYST_LU *syst)
// Libera a memoria utilizada pelo sistema LU linear syst
{
    if (!syst)
        exitStatus(INV_POINTER);

    for (int i = 0; i < syst->size; i++)
        free(syst->L[i]);
    for (int i = 0; i < syst->size; i++)
        free(syst->U[i]);
    free(syst->L);
    free(syst->U);
    free(syst->b);
    free(syst->X);
    free(syst);
}
