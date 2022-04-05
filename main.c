//Gabriel de Oliveira Pontarolo GRR20203895
//Rodrigo Saviam Soffner GRR20205092

#include "functions.h"
#include "newtonPadrao.h"
#include "newtonModificado.h"
#include "newtonInexato.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // char *output = getArgs(argc, argv);
    FUNCTION *input_func;
    double timeBuffer;

    do
    {
        input_func = readFunction();
        printf("%s\n", input_func->expression);

        timeBuffer = timestamp();
        NewtonPadrao(input_func);
        input_func->n_p->timeFull = timestamp() - timeBuffer;

        timeBuffer = timestamp();
        NewtonModificado(input_func);
        input_func->n_m->timeFull = timestamp() - timeBuffer;

        printMethod(input_func);

        // Free da function
        free(input_func->initial_aps);
        free(input_func);
    } while (getc(stdin) != EOF);
}