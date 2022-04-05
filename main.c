// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#include "functions.h"
#include "newtonPadrao.h"
#include "newtonModificado.h"
#include "newtonInexato.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *output = NULL;//getArgs(argc, argv);
    FUNCTION *input_func;

    do
    {
        input_func = readFunction();

        NewtonPadrao(input_func);
        NewtonModificado(input_func);
        NewtonInexato(input_func);

        printMethod(input_func, output);
        deleteFunction(input_func);
    } while (getc(stdin) != EOF);

    return EXIT_SUCCESS;
}