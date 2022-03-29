#ifndef __FUNC__
#define __FUNC__

#define EXPRESSION_MAX_SIZE 256

#include <matheval.h>

typedef struct function
{
    char *expression;  // string com a expressao da funcao
    void *evaluator;   // libmath evaluator
    int variable_num;  // numero de variaveis
    double initial_ap; // aproximacao inicial
    double t_ep;       // tolerancia epsilon
    int it_num;        // numero maximo de iteracoes
} FUNCTION;

char *getArgs(int argc, char **argv);
FUNCTION *readFunction(void);

#endif