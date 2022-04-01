#include "functions.h"
#include "newtonPadrao.h"
#include "derivacao.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // char *output = getArgs(argc, argv);
    FUNCTION *input_func;
    NEWTON *result_func;

    do
    {
        input_func = readFunction();
        printf("%s\n", input_func->expression);
        result_func = NewtonPadrao(input_func);
        // Free da function
        printMethod(result_func);
        free(input_func->initial_aps);
        free(input_func);
    } while (getc(stdin) != EOF);
}