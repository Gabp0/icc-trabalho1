#include "functions.h"
#include <stdio.h>
#include <math.h>
#include <matheval.h>

void NewtonPadrao(FUNCTION *func)
{
    void **grad = malloc(sizeof(void *) * func->variable_num);
    void ***hessi = malloc(sizeof(void *) * func->variable_num * func->variable_num);

    for (int i = 0; i < func->it_num; i++)
    {
        // if (fabs(evaluator_evaluate(func->evaluator, func->variable_num, func->names, func->initial_aps) < func->t_ep))
        // return;

        Gradiente(func, grad);
        Hessiana(func, grad, hessi);
        for (int i = 0; i < func->variable_num; i++)
        {
            printf("%s\n", evaluator_get_string(grad[i]));
            for (int j = 0; i < func->variable_num; i++)
            {
                printf("%s\n", evaluator_get_string(hessi[i][j]));
            }
        }
    }
}

void Gradiente(FUNCTION *func, void **grad)
{
    for (int i = 0; i < func->variable_num; i++)
    {
        grad[i] = evaluator_derivative(func->evaluator, func->names[i]);
    }
}

void Hessiana(FUNCTION *func, void **grad, void ***hessi)
{
    for (int i = 0; i < func->variable_num; i++)
    {
        for (int j = 0; i < func->variable_num; i++)
        {
            hessi[i][j] = evaluator_derivative(grad[i], func->names[j]);
        }
    }
}