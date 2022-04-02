#include "utils.h"
#include "functions.h"
#include "derivacao.h"
#include "EliminacaoGauss.h"
#include "newtonModificado.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

NEWTON *NewtonModificado(FUNCTION *func)
{
    double soma = 0, timeBuffer;

    NEWTON *solu = initNewton(func);

    solu->timeDer -= timestamp();
    Gradiente(func, solu->gradiente);                // gera as funcoes do vetor gradiente
    Hessiana(func, solu->gradiente, solu->hessiana); // gera as funcoes da matriz hessiana
    solu->timeDer += timestamp();


    for (int k = 0; k < func->it_num; k++) // testa numero de iteracoes // numero de iteracoes utilizadas no metodo
    {
        solu->aprox_newtonP[k] = evaluator_evaluate(func->evaluator, func->variable_num, func->names, solu->X_i); // f(X_i)

        for (int i = 0; i < func->variable_num; i++) // gradiente f(X_i)
            solu->G_f[i] = evaluator_evaluate(solu->gradiente[i], func->variable_num, func->names, solu->X_i) * -1; // oposto resultado do gradiente para o calculo do sistema linear

        for (int i = 0; i < func->variable_num; i++)
            soma += pow(solu->G_f[i], 2);

        if (sqrt(soma) < func->t_ep) // testa || gradiente de f(X_i) || < eps
            break;

        for (int i = 0; i < func->variable_num; i++)
            if (k % HESS_STEPS == 0)
                for (int j = 0; j < func->variable_num; j++) // calcula a hessiana de X_i
                    solu->H_x[i][j] = evaluator_evaluate(solu->hessiana[i][j], func->variable_num, func->names, solu->X_i);
        
        solu->timeSL -= timestamp();
        hessianGaussEliminationLU(solu->H_x, solu->delta, solu->G_f, solu->n); // resolve o sistema linear
        solu->timeSL += timestamp();

        soma = 0;
        for (int i = 0; i < func->variable_num; i++)
        {
            solu->X_i[i] += solu->delta[i]; // calcula X_i+1
            soma += pow(solu->delta[i], 2); // calcula || delta ||
        }
        solu->k++;
        if (sqrt(soma) < __DBL_EPSILON__) // testa || delta_i || < eps
            break;
    }
    return solu;
}
