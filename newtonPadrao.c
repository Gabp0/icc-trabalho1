#include "functions.h"
#include "derivacao.h"
#include "EliminacaoGauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

void NewtonPadrao(FUNCTION *func, SOLUCAO *solu)
{
    double soma;

    for (int k = 0; k < func->it_num; k++)
    {
        solu->it_num++;
        solu->aprox_newtonP[k] = evaluator_evaluate(func->evaluator, func->variable_num, func->names, solu->X_i);
        for (int i = 0; i < func->variable_num; i++)
            soma += pow(evaluator_evaluate(solu->gradiente[i], func->variable_num, func->names, solu->X_i), 2);

        if (sqrt(soma) < func->t_ep)
            return;

        Gradiente(func, solu->gradiente);
        Hessiana(func, solu->gradiente, solu->hessiana);

        for (int i = 0; i < func->variable_num; i++)
        {
            solu->G_f[i] = -1 * evaluator_evaluate(solu->gradiente[i], func->variable_num, func->names, solu->X_i);
            for (int j = 0; j < func->variable_num; j++)
            {

                solu->H_x[i * func->variable_num + j] = evaluator_evaluate(solu->hessiana[i * func->variable_num + j], func->variable_num, func->names, solu->X_i);
            }
        }

        hessianGaussElimination(solu->H_x, solu->delta, solu->G_f, solu->n);

        for (int i = 0; i < func->variable_num; i++)
        {
            solu->X_i[i] += solu->delta[i];
        }

        //    for (int i = 0; i < func->variable_num; i++)
        //    {
        //        printf("gradiente: %s\n", evaluator_get_string(solu->gradiente[i]));
        //        for (int j = 0; j < func->variable_num; j++)
        //        {
        //            printf("hessiana: %s\n", evaluator_get_string(solu->hessiana[i * func->variable_num + j]));
        //        }
        //    }
    }
}
