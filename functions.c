#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getArgs(int argc, char **argv)
{
    if (argc > 3)
    {
        fprintf(stderr, "Número de argumentos inválidos.\n");
        exit(EXIT_FAILURE);
    }

    if (!strcmp(argv[1], "-o"))
    {
        if (!access(argv[2], F_OK))
            return argv[2];
        else
        {
            fprintf(stderr, "Arquivo %s não encontrado.\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    }
    return "stdout";
}

FUNCTION *readFunction(void)
{
    FUNCTION *new = malloc(sizeof(FUNCTION));
    if (!new)
    {
        perror("Falha ao alocar memória para as funções.");
        exit(EXIT_FAILURE);
    }
    new->expression = malloc(sizeof(char) * EXPRESSION_MAX_SIZE);
    if (!new->expression)
    {
        perror("Falha ao alocar memória para as funções.");
        exit(EXIT_FAILURE);
    }

    fscanf(stdin, "%d\n%s\n%lf\n%lf\n%d", &new->variable_num,
           new->expression, &new->initial_ap, &new->t_ep, &new->it_num);

    new->evaluator = evaluator_create(new->expression);
    if (!new->evaluator)
    {
        perror("Falha ao criar o avalidor para o libmatheval");
        exit(EXIT_FAILURE);
    }

    return new;
}
