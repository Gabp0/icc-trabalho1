// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#include "newtonInexato.h"
#include "utils.h"
#include "functions.h"
#include "gaussSeidel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

NEWTON_I *initNewtonI(FUNCTION *func)
{
    NEWTON_I *new = malloc(sizeof(NEWTON_I));

    new->gradiente = malloc(sizeof(void *) * func->var_num);

    new->hessiana = malloc(sizeof(void **) * func->var_num);
    for (int i = 0; i < func->var_num; i++)
        new->hessiana[i] = malloc(sizeof(void *) * func->var_num);

    new->syst = initLSGS(func->var_num);
    new->X_i = copyDoubleArray(func->initial_aps, func->var_num);
    new->n = func->var_num;
    new->aprox_newtonI = calloc(sizeof(double), func->it_num);

    return new;
}

void _deleteNewtonI(NEWTON_I *ni)
{
    free(ni->aprox_newtonI);

    for (int i = 0; i < ni->n; i++)
        evaluator_destroy(ni->gradiente[i]);

    free(ni->gradiente);

    // deleteLS(ni->syst);

    for (int i = 0; i < ni->n; i++)
    {
        for (int j = 0; j < ni->n; j++)
            evaluator_destroy(ni->hessiana[i][j]);
        free(ni->hessiana[i]);
    }
    free(ni->hessiana);

    free(ni->X_i);
    free(ni);
}

void NewtonInexato(FUNCTION *func)
{
    func->n_i->timeFull -= timestamp();
    double soma = 0;

    NEWTON_I *ni = initNewtonI(func);

    func->n_i->timeDer -= timestamp();
    Gradiente(func, ni->gradiente);              // gera as funcoes do vetor gradiente
    Hessiana(func, ni->gradiente, ni->hessiana); // gera as funcoes da matriz hessiana
    func->n_i->timeDer += timestamp();

    for (int k = 0; k <= func->it_num; k++) // testa numero de iteracoes
    {
        ni->aprox_newtonI[k] = evaluator_evaluate(func->evaluator, func->var_num, func->names, ni->X_i); // f(X_i)

        for (int i = 0; i < func->var_num; i++)                                                              // gradiente f(X_i)
            ni->syst->b[i] = evaluator_evaluate(ni->gradiente[i], func->var_num, func->names, ni->X_i) * -1; // oposto resultado do gradiente para o calculo do sistema linear

        for (int i = 0; i < func->var_num; i++)
            soma += pow(ni->syst->b[i], 2);

        if (sqrt(soma) < func->t_ep) // testa || gradiente de f(X_i) || < eps
            break;

        for (int i = 0; i < func->var_num; i++) // calcula a hessiana de X_i
            for (int j = 0; j < func->var_num; j++)
                ni->syst->A[i][j] = evaluator_evaluate(ni->hessiana[i][j], func->var_num, func->names, ni->X_i);

        for (int i = 0; i < func->var_num; i++)
            ni->syst->X[i] = 0;

        func->n_i->timeSL -= timestamp();
        gaussSeidel(ni->syst); // resolve o sistema linear
        func->n_i->timeSL += timestamp();

        soma = 0;
        for (int i = 0; i < func->var_num; i++)
        {
            ni->X_i[i] += ni->syst->X[i];   // calcula X_i+1
            soma += pow(ni->syst->X[i], 2); // calcula || delta ||
        }

        if (sqrt(soma) < __DBL_EPSILON__) // testa || delta_i || < eps2
            break;

        func->n_i->it_num++; // numero de iteracoes utilizadas no metodo
    }

    func->n_i->f_k = copyDoubleArray(ni->aprox_newtonI, func->n_i->it_num);
    _deleteNewtonI(ni);
    func->n_i->timeFull += timestamp();
}
