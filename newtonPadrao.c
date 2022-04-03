#include "newtonPadrao.h"
#include "utils.h"
#include "functions.h"
#include "gaussianElimination.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

NEWTON_P *initNewtonP(FUNCTION *func)
{
    NEWTON_P *new = malloc(sizeof(NEWTON_P));

    new->gradiente = malloc(sizeof(void *) * func->var_num);

    new->hessiana = malloc(sizeof(void **) * func->var_num);
    for (int i = 0; i < func->var_num; i++)
        new->hessiana[i] = malloc(sizeof(void *) * func->var_num);

    new->syst = initLS(func->var_num);
    new->X_i = copyDoubleArray(func->initial_aps, func->var_num);
    new->n = func->var_num;
    new->aprox_newtonP = calloc(sizeof(double), func->it_num);

    return new;
}

void NewtonPadrao(FUNCTION *func)
{
    double soma = 0;

    NEWTON_P *np = initNewtonP(func);

    func->n_p->timeDer -= timestamp();
    Gradiente(func, np->gradiente);              // gera as funcoes do vetor gradiente
    Hessiana(func, np->gradiente, np->hessiana); // gera as funcoes da matriz hessiana
    func->n_p->timeDer += timestamp();

    for (int k = 0; k < func->it_num; k++) // testa numero de iteracoes // numero de iteracoes utilizadas no metodo
    {
        func->n_p->it_num++;

        np->aprox_newtonP[k] = evaluator_evaluate(func->evaluator, func->var_num, func->names, np->X_i); // f(X_i)

        for (int i = 0; i < func->var_num; i++)                                                              // gradiente f(X_i)
            np->syst->b[i] = evaluator_evaluate(np->gradiente[i], func->var_num, func->names, np->X_i) * -1; // oposto resultado do gradiente para o calculo do sistema linear

        for (int i = 0; i < func->var_num; i++)
            soma += pow(np->syst->b[i], 2);

        if (sqrt(soma) < func->t_ep) // testa || gradiente de f(X_i) || < eps
            break;
        for (int i = 0; i < func->var_num; i++)
            for (int j = 0; j < func->var_num; j++) // calcula a hessiana de X_i
                np->syst->A[i][j] = evaluator_evaluate(np->hessiana[i][j], func->var_num, func->names, np->X_i);

        func->n_p->timeSL -= timestamp();
        gaussianElimination(np->syst); // resolve o sistema linear
        func->n_p->timeSL += timestamp();

        soma = 0;
        for (int i = 0; i < func->var_num; i++)
        {
            np->X_i[i] += np->syst->X[i];   // calcula X_i+1
            soma += pow(np->syst->X[i], 2); // calcula || delta ||
        }

        if (sqrt(soma) < __DBL_EPSILON__) // testa || delta_i || < eps2
            break;
    }

    func->n_p->f_k = copyDoubleArray(np->aprox_newtonP, func->n_p->it_num);
    // deleteNP(np);
}
