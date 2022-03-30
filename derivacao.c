#include "derivacao.h"
#include <stdlib.h>
#include <matheval.h>

double *_copyDoubleArray(double *a, int size)
{
    double *new = malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++)
        new[i] = a[i];

    return new;
}

SOLUCAO *initSolucao(FUNCTION *func)
{
    SOLUCAO *new = malloc(sizeof(SOLUCAO));

    new->gradiente = malloc(sizeof(void *) * func->variable_num);
    new->hessiana = malloc(sizeof(void *) * func->variable_num * func->variable_num);
    new->delta = malloc(sizeof(double) * func->variable_num);
    new->X_i = _copyDoubleArray(func->initial_aps, func->variable_num);
    new->n = func->variable_num;
    new->it_num = 0;
    new->aprox_newtonP = malloc(sizeof(double) * func->it_num);

    return new;
}

void Gradiente(FUNCTION *func, void **grad)
{
    for (int i = 0; i < func->variable_num; i++)
    {
        grad[i] = evaluator_derivative(func->evaluator, func->names[i]);
    }
}

void Hessiana(FUNCTION *func, void **grad, void **hessi)
{

    for (int i = 0; i < func->variable_num; i++)
    {
        for (int j = 0; j < func->variable_num; j++)
        {
            hessi[i * func->variable_num + j] = evaluator_derivative(grad[i], func->names[j]);
        }
    }
}