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
    new->aprox_newtonP = calloc(sizeof(double), func->it_num);
    new->timeDer = 0;
    new->timeFull = 0;
    new->timeSL = 0;

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

int max(int a, int b)
{
    return a > b ? a : b;
}

void printMethod(NEWTON *newtP, NEWTON *newtM)
{
    // cabeçalho
    printf("Iteração \t| Newton Padrão \t| Newton Modificado \t| Newton Inexato\n");
    int z = max(newtP->k, newtM->k);
    for (int i = 0; i < z; i++)
    {
        printf("%d \t\t| ", i); // imprime iteração

        if (newtP->k > i)
            printf("%1.14e\t| ", newtP->aprox_newtonP[i]);
        else
            printf("\t\t\t| ");
        if (newtM->k > i)
            printf("%1.14e\t| \n", newtM->aprox_newtonP[i]);
        else
            printf("\t\t\t| \n");

        // repete para as outras duas colunas...
    }

    // imprimir os tempos
    printf("Tempo total \t| %1.14e\t| %1.14e\t| %1.14e\n", newtP->timeFull, newtM->timeFull, newtM->timeFull);
    printf("Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e\n", newtP->timeDer, newtM->timeDer, newtM->timeFull);
    printf("Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e\n", newtP->timeSL, newtM->timeSL, newtM->timeFull);
}