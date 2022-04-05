//Gabriel de Oliveira Pontarolo GRR20203895
//Rodrigo Saviam Soffner GRR20205092

#include "utils.h"
#include "functions.h"
#include "luDecomposition.h"
#include "newtonModificado.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

NEWTON_M *initNewtonM(FUNCTION *func)
{
    NEWTON_M *new = malloc(sizeof(NEWTON_M));

    new->gradiente = malloc(sizeof(void *) * func->var_num);

    new->hessiana = malloc(sizeof(void **) * func->var_num);
    for (int i = 0; i < func->var_num; i++)
        new->hessiana[i] = malloc(sizeof(void *) * func->var_num);

    new->syst = initLSLU(func->var_num);
    new->X_i = copyDoubleArray(func->initial_aps, func->var_num);
    new->n = func->var_num;
    new->aprox_newtonP = calloc(sizeof(double), func->it_num);

    return new;
}

void NewtonModificado(FUNCTION *func)
{
    double soma = 0;
    NEWTON_M *nm = initNewtonM(func);

    func->n_m->timeDer -= timestamp();
    Gradiente(func, nm->gradiente);              // gera as funcoes do vetor gradiente
    Hessiana(func, nm->gradiente, nm->hessiana); // gera as funcoes da matriz hessiana
    func->n_m->timeDer += timestamp();

    soma += pow(nm->syst->X[0], 2);

    for (int k = 0; k < func->it_num; k++) // testa numero de iteracoes
    {
        func->n_m->it_num++; // numero de iteracoes utilizadas no metodo

        nm->aprox_newtonP[k] = evaluator_evaluate(func->evaluator, func->var_num, func->names, nm->X_i); // f(X_i)

        for (int i = 0; i < func->var_num; i++)                                                              // gradiente f(X_i)
            nm->syst->b[i] = evaluator_evaluate(nm->gradiente[i], func->var_num, func->names, nm->X_i) * -1; // oposto resultado do gradiente para o calculo do sistema linear

        for (int i = 0; i < func->var_num; i++)
            soma += pow(nm->syst->b[i], 2);
        if (sqrt(soma) < func->t_ep) // testa || gradiente de f(X_i) || < eps
            break;

        if ((k % func->var_num) == 0)
        {
            for (int i = 0; i < func->var_num; i++)
                for (int j = 0; j < func->var_num; j++) // calcula a hessiana de X_i apenas a cada HESS_STEPS
                    nm->syst->U[i][j] = evaluator_evaluate(nm->hessiana[i][j], func->var_num, func->names, nm->X_i);

            factorize(nm->syst); // separa a matriz H_x no sistema linear com LU
        }

        func->n_m->timeSL -= timestamp();
        solveLU(nm->syst); // resolve o sistema linear
        func->n_m->timeSL += timestamp();

        soma = 0;
        for (int i = 0; i < func->var_num; i++)
        {
            nm->X_i[i] += nm->syst->X[i];   // calcula X_i+1
            soma += pow(nm->syst->X[i], 2); // calcula || delta ||
        }

        if (sqrt(soma) < __DBL_EPSILON__) // testa || delta_i || < eps
            break;
    }

    func->n_m->f_k = copyDoubleArray(nm->aprox_newtonP, func->n_m->it_num);
}
