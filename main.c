#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *output = getArgs(argc, argv);
    FUNCTION *input_func;

    do
    {
        input_func = readFunction();
        printf("%s\n", input_func->expression);
    } while (getc(stdin) != EOF);
}