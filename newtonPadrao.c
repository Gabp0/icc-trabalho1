#include "functions.h"
#include "derivacao.h"
#include "EliminacaoGauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

NEWTON *NewtonPadrao(FUNCTION *func)
{
    double soma = 0;

    NEWTON *solu = initNewton(func);

    Gradiente(func, solu->gradiente);                // gera as funcoes do vetor gradiente
    Hessiana(func, solu->gradiente, solu->hessiana); // gera as funcoes da matriz hessiana

    for (int h = 0; h < func->it_num; h++) // testa numero de iteracoes
    {
        solu->k++; // numero de iteracoes utilizadas no metodo

        solu->aprox_newtonP[h] = evaluator_evaluate(func->evaluator, func->variable_num, func->names, solu->X_i); // f(X_i)

        for (int i = 0; i < func->variable_num; i++) // gradiente f(X_i)
            solu->G_f[i] = evaluator_evaluate(solu->gradiente[i], func->variable_num, func->names, solu->X_i);

        for (int i = 0; i < func->variable_num; i++)
            soma += pow(solu->G_f[i], 2);
        if (sqrt(soma) < func->t_ep) // testa || gradiente de f(X_i) || < eps
            break;

        for (int i = 0; i < func->variable_num; i++)
        {
            solu->G_f[i] *= -1;                          // oposto resultado do gradiente para o calculo do sistema linear
            for (int j = 0; j < func->variable_num; j++) // calcula a hessiana de X_i
                solu->H_x[i][j] = evaluator_evaluate(solu->hessiana[i][j], func->variable_num, func->names, solu->X_i);
        }

        hessianGaussElimination(solu->H_x, solu->delta, solu->G_f, solu->n); // resolve o sistema linear

        soma = 0;
        for (int i = 0; i < func->variable_num; i++)
        {
            solu->X_i[i] += solu->delta[i]; // calcula X_i+1
            soma += pow(solu->delta[i], 2); // calcula || delta ||
        }
        if (sqrt(soma) < __DBL_EPSILON__) // testa || delta_i || < eps
            break;

        //    for (int i = 0; i < func->variable_num; i++)
        //    {
        //        printf("gradiente: %s\n", evaluator_get_string(solu->gradiente[i]));
        //        for (int j = 0; j < func->variable_num; j++)
        //        {
        //            printf("hessiana: %s\n", evaluator_get_string(solu->hessiana[i][j]));
        //        }
        //    }
    }

    // if (solu->k < func->it_num)
    //     for (int i = solu->k; i < func->it_num; i++)
    //         solu->aprox_newtonP[i] = 0;
    // solu->k = func->it_num;

    return solu;
}
