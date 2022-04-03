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

    return new;
}

// void _pivot(LINEAR_SYST_LU *syst)
// {
//     double max = fabs(H_x[i][i]);
//     int max_i = i;
//     for (int j = i + 1; j < n; ++j)
//     {
//         double v = fabs(H_x[j][i]);
//         if (v > max)
//         {
//             max = v;
//             max_i = j;
//         }
//     }
//     if (max_i != i)
//     {
//         double *tmp = H_x[i];
//         H_x[i] = H_x[max_i];
//         H_x[max_i] = tmp;

//         double aux = g_f[i];
//         g_f[i] = g_f[max_i];
//         g_f[max_i] = aux;
//     }
// }

void factorize(LINEAR_SYST_LU *syst)
{
    for (int i = 0; i < syst->size; ++i)
    {
        //_pivot(H_x, g_f, n, i);
        syst->U[i][i] = 1.0;
        for (int k = i + 1; k < syst->size; ++k)
        {
            syst->U[k][i] = syst->L[k][i] / syst->L[i][i];
            if (isnan(syst->U[k][i]))
                printf("ERRO: %g\n", syst->L[i][i]);
            syst->L[k][i] = 0.0;
            for (int j = i + 1; j < syst->size; ++j)
                syst->L[k][j] -= syst->L[i][j] * syst->U[k][i];
        }
    }
}

void _subsLU(LINEAR_SYST_LU *syst)
{
    for (int i = 0; i < syst->size; ++i)
    {
        syst->Y[i] = syst->b[i];
        for (int j = 0; j <= i; j++)
            syst->Y[i] -= syst->L[i][j] * syst->Y[j];
        syst->Y[i] /= syst->L[i][i];
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
