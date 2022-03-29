#include "functions.h"
#include <stdio.h>
#include <math.h>

void NewtonPadrao(FUNCTION *func)
{
    for (int i = 0; i < func->it_num; i++)
    {
        if (fabs(evaluator_evaluate(func->evaluator, func->variable_num, func->names, func->initial_aps) < func->t_ep))
        return;



    }
}