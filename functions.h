#ifndef __FUNC__
#define __FUNC__

#define EXPRESSION_MAX_SIZE 1000
#define FILE_NAME_MAX_SIZE 256

typedef struct function
{
    char *expression;  // string com a expressao da funcao
    char **names;      // vetor com os nomes das variaveis
    void *evaluator;   // libmath evaluator
    int variable_num;  // numero de variaveis
    double *initial_aps; // aproximacao inicial
    double t_ep;         // tolerancia epsilon
    int it_num;          // numero maximo de iteracoes
} FUNCTION;

char *getArgs(int argc, char **argv);
FUNCTION *readFunction(void);

#endif