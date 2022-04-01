#include "derivacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <matheval.h>
#include <math.h>

double *_copyDoubleArray(double *a, int size)
{
    double *new = malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++)
        new[i] = a[i];

    return new;
}

NEWTON *initNewton(FUNCTION *func)
{
    NEWTON *new = malloc(sizeof(NEWTON));

    new->gradiente = malloc(sizeof(void *) * func->variable_num);
    new->G_f = malloc(sizeof(double) * func->variable_num);

    new->hessiana = malloc(sizeof(void **) * func->variable_num);
    new->H_x = malloc(sizeof(double *) * func->variable_num);
    for (int i = 0; i < func->variable_num; i++)
    {
        new->hessiana[i] = malloc(sizeof(void **) * func->variable_num);
        new->H_x[i] = malloc(sizeof(double) * func->variable_num);
    }

    new->delta = malloc(sizeof(double) * func->variable_num);
    new->X_i = _copyDoubleArray(func->initial_aps, func->variable_num);
    new->n = func->variable_num;
    new->k = 0;
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

void Hessiana(FUNCTION *func, void **grad, void ***hessi)
{

    for (int i = 0; i < func->variable_num; i++)
    {
        for (int j = 0; j < func->variable_num; j++)
        {
            hessi[i][j] = evaluator_derivative(grad[i], func->names[j]);
        }
    }
}

void printMethod(NEWTON *newt)
{
    // cabeçalho
    printf("Iteração \t\t| Newton Padrão \t\t| Newton Modificado \t\t| Newton Inexato");
    // para cada iteração
    for (int i = 0; i < newt->k; i++)
    {
        printf("\n%d \t\t\t\t| ", i); // imprime iteração

        if (newt->aprox_newtonP[i])
        { // se nesta iteração o valor da primeira coluna existe, imprime
            if (isnan(newt->aprox_newtonP[i]) || isinf(newt->aprox_newtonP[i]))
                printf("%1.14e\t\t\t| ", newt->aprox_newtonP[i]);
            else
                printf("%1.14e\t| ", newt->aprox_newtonP[i]);
        }
        else
            printf("\t\t\t| ");

        // repete para as outras duas colunas...
    }

    // imprimir os tempos
    // printf("Tempo total \t| %1.14e\t| %1.14e\t| %1.14e\n", TtotalEG, TtotalLU, TtotalGS);
    // printf("Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e\n", TderivadasEG, TderivadasLU, TderivadasGS);
    // printf("Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e\n", TslEG, TslLU, TslGS);
}