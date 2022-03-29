#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *output = getArgs(argc, argv);
<<<<<<< HEAD
    FUNCTION *input_func;

    do
    {
        input_func = readFunction();
        printf("%s\n", input_func->expression);
    } while (getc(stdin) != EOF);
=======
    printf("%s\n", output);

    // cabeçalho
    printf("Iteração \t| Newton Padrão \t| Newton Modificado \t| Newton Inexato\n");

    // para cada iteração
    for (...)
    {
        printf("%d \t\t| ", i); // imprime iteração

        if (...)
        { // se nesta iteração o valor da primeira coluna existe, imprime
            if (isnan(fx) || isinf(fx))
                printf("%1.14e\t\t\t| ", fx);
            else
                printf("%1.14e\t| ", fx);
        }
        else
            printf("\t\t\t| ");

        // repete para as outras duas colunas...
    }

    // imprimir os tempos
    printf("Tempo total \t| %1.14e\t| %1.14e\t| %1.14e\n", TtotalEG, TtotalLU, TtotalGS);
    printf("Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e\n", TderivadasEG, TderivadasLU, TderivadasGS);
    printf("Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e\n", TslEG, TslLU, TslGS);
>>>>>>> refs/remotes/origin/main
}