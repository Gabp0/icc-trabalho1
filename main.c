#include "functions.h"
#include "newtonPadrao.h"
#include "newtonModificado.h"
#include "derivacao.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // char *output = getArgs(argc, argv);
    FUNCTION *input_func;
    NEWTON *result_func, *result_func2;
    double timeBuffer;
    
    do
    {
        input_func = readFunction();
        printf("%s\n", input_func->expression);

        timeBuffer = timestamp();
        result_func = NewtonPadrao(input_func);
        result_func->timeFull = timestamp() - timeBuffer;
        
        timeBuffer = timestamp();
        result_func2 = NewtonModificado(input_func);
        result_func2->timeFull = timestamp() - timeBuffer;


        printMethod(result_func, result_func2);

        // Free da function
        free(input_func->initial_aps);
        free(input_func);
    } while (getc(stdin) != EOF);
}