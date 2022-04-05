// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#ifndef __FUNC__
#define __FUNC__

#define EXPRESSION_MAX_SIZE 1000
#define FILE_NAME_MAX_SIZE 256

typedef struct newton_result
{
    double *f_k;
    int it_num;
    double timeFull;
    double timeDer;
    double timeSL;
} N_RESULT;

typedef struct function
{
    char *expression;    // string com a expressao da funcao
    char **names;        // vetor com os nomes das variaveis
    void *evaluator;     // libmath evaluator
    int var_num;         // numero de variaveis
    double *initial_aps; // aproximacao inicial
    double t_ep;         // tolerancia epsilon
    int it_num;          // numero maximo de iteracoes
    N_RESULT *n_p;       // resultado do metodo newton padrao
    N_RESULT *n_m;       // resultado do metodo newton modificado
    N_RESULT *n_i;       // resultado do metodo newton inexato
} FUNCTION;

FUNCTION *readFunction(void);
void Gradiente(FUNCTION *func, void **grad);
void Hessiana(FUNCTION *func, void **grad, void ***hessi);
void printMethod(FUNCTION *func, char *output);
void deleteFunction(FUNCTION *func);

#endif