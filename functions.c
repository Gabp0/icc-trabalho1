#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getArgs(int argc, char **argv)
{
    char *output = malloc(sizeof(char) * FILE_NAME_MAX_SIZE);
    if (!output)
    {
        perror("Falha ao alocar memória para string");
        exit(EXIT_FAILURE);
    }

    if (argc > 3)
    {
        fprintf(stderr, "Número de argumentos inválidos.\n");
        exit(EXIT_FAILURE);
    }

    if (!strcmp(argv[1], "-o"))
    {
        if (!access(argv[2], F_OK))
            strncpy(output, argv[2], FILE_NAME_MAX_SIZE);
        else
        {
            fprintf(stderr, "Arquivo %s não encontrado.\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    }
    else
        strncpy(output, argv[2], FILE_NAME_MAX_SIZE);

    return output;
}

FUNCTION *readFunction(void)
{
    FUNCTION *function = malloc(sizeof(FUNCTION));
    if (!function)
    {
        perror("Falha ao alocar memória para as funções.");
        exit(EXIT_FAILURE);
    }
    function->expression = malloc(sizeof(char) * EXPRESSION_MAX_SIZE);
    if (!function->expression)
    {
        perror("Falha ao alocar memória para as funções.");
        exit(EXIT_FAILURE);
    }

    fscanf(stdin, "%d\n%s\n", &function->variable_num, function->expression);

    function->initial_aps = malloc(sizeof(double)*function->variable_num);

    for(int i = 0;i < function->variable_num; i++)
        fscanf(stdin, "%lf", &function->initial_aps[i]);

    fscanf(stdin, "%lf\n%d", &function->t_ep, &function->it_num);

    function->evaluator = evaluator_create(function->expression);
    if (!function->evaluator)
    {
        perror("Falha ao criar o avalidor para o libmatheval");
        exit(EXIT_FAILURE);
    }

    return function;
}
