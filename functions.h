// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092
// Biblioteca functions.h
// Utilizada para a leitura e escrita de funcoes matematicas

#ifndef __FUNC__
#define __FUNC__

#define EXPRESSION_MAX_SIZE 1000 // tamanho maximo da expressao da funcao

typedef struct newton_result
// struct para armazenar o resultado de um metodo de newton
{
    double *f_k;     // vetor f(k)
    int it_num;      // numero de iteracoes necessarias
    double timeFull; // tempo total
    double timeDer;  // tempo para calcular as derivadas
    double timeSL;   // tempo para calcular os sistemas lineares
} N_RESULT;

typedef struct function
// struct para armazenar a funcao matematica e o resultado dos 3 metodos de newton
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

FUNCTION *readFunction(void); // Le a funcao matematica da entrada padrao, armazena em uma struct do tipo FUNCTION e retorna o ponteiro para ela
void Gradiente(FUNCTION *func, void **grad);
void Hessiana(FUNCTION *func, void **grad, void ***hessi);
void printMethod(FUNCTION *func, char *output);
void deleteFunction(FUNCTION *func);

#endif