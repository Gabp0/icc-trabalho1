#include "args.h"
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
