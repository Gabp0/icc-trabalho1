// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092
// Implementacao das funcoes da biblioteca newtonInexato.h

#include "newtonInexato.h"
#include "utils.h"
#include "functions.h"
#include "gaussSeidel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

NEWTON_I *_initNewtonI(FUNCTION *func)
// aloca memoria para a struct usada pelo metodo de newton inexato
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
// libera memoria utilizada pela struct do newton inexato
{
    free(ni->aprox_newtonI);

    for (int i = 0; i < ni->n; i++)
        evaluator_destroy(ni->gradiente[i]);

    free(ni->gradiente);

    deleteLSGS(ni->syst);

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
// encontra as raizes da funcao utilizando o metodo de newton inexato
{
    func->n_i->timeFull -= timestamp();

    NEWTON_I *ni = _initNewtonI(func);

    func->n_i->timeDer -= timestamp();
    Gradiente(func, ni->gradiente);              // gera as funcoes do vetor gradiente
    Hessiana(func, ni->gradiente, ni->hessiana); // gera as funcoes da matriz hessiana
    func->n_i->timeDer += timestamp();

    for (int k = 0; k <= func->it_num; k++) // testa numero de iteracoes
    {
        ni->aprox_newtonI[k] = evaluator_evaluate(func->evaluator, func->var_num, func->names, ni->X_i); // f(X_i)

        for (int i = 0; i < func->var_num; i++)                                                              // gradiente f(X_i)
            ni->syst->b[i] = evaluator_evaluate(ni->gradiente[i], func->var_num, func->names, ni->X_i) * -1; // oposto resultado do gradiente para o calculo do sistema linear

        func->n_i->it_num++; // numero de iteracoes utilizadas no metodo

        if (norma(ni->syst->b, func->var_num) < func->t_ep) // testa || gradiente de f(X_i) || < eps
            break;

        for (int i = 0; i < func->var_num; i++) // calcula a hessiana de X_i
            for (int j = 0; j < func->var_num; j++)
                ni->syst->A[i][j] = evaluator_evaluate(ni->hessiana[i][j], func->var_num, func->names, ni->X_i);

        for (int i = 0; i < func->var_num; i++)
            ni->syst->X[i] = 0;

        func->n_i->timeSL -= timestamp();
        gaussSeidel(ni->syst); // resolve o sistema linear utilizando gauss-seidel
        func->n_i->timeSL += timestamp();

        for (int i = 0; i < func->var_num; i++)
            ni->X_i[i] += ni->syst->X[i]; // calcula X_i+1

        if (norma(ni->X_i, func->var_num) < __DBL_EPSILON__) // testa || delta_i || < eps2
        {
            func->n_i->it_num++;
            break;
        }
    }

    func->n_i->f_k = copyDoubleArray(ni->aprox_newtonI, func->n_i->it_num); // resultado do sistema
    _deleteNewtonI(ni);
    func->n_i->timeFull += timestamp();
}
