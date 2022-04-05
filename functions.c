// Gabriel de Oliveira Pontarolo GRR20203895
// Rodrigo Saviam Soffner GRR20205092

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <matheval.h>

N_RESULT *_initNR(void)
{
    N_RESULT *new = malloc(sizeof(N_RESULT));
    if (!new)
        exitStatus(MEM_ALOC);

    new->it_num = 0;
    new->timeDer = 0.0;
    new->timeSL = 0.0;
    new->timeFull = 0.0;

    return new;
}

void _deleteResult(N_RESULT *result)
{
    free(result->f_k);
    free(result);
}

FUNCTION *readFunction(void)
{
    FUNCTION *function = malloc(sizeof(FUNCTION));
    char *namePointer;

    if (!function)
        exitStatus(MEM_ALOC);
    function->expression = malloc(sizeof(char) * EXPRESSION_MAX_SIZE);
    if (!function->expression)
        exitStatus(MEM_ALOC);

    fscanf(stdin, "%d\n%s\n", &function->var_num, function->expression);

    function->initial_aps = malloc(sizeof(double) * function->var_num);
    function->names = malloc(sizeof(char **) * function->var_num);
    if ((!function->initial_aps) || (!function->names))
        exitStatus(MEM_ALOC);

    for (int i = 0; i < function->var_num; i++)
    {
        namePointer = malloc(sizeof(char) * 5);
        if (!namePointer)
            exitStatus(MEM_ALOC);
        snprintf(namePointer, sizeof(char) * 5, "x%d", i + 1);
        function->names[i] = namePointer;
        fscanf(stdin, "%lf", &function->initial_aps[i]);
        // free(namePointer);
    }

    fscanf(stdin, "%lf\n%d", &function->t_ep, &function->it_num);

    function->evaluator = evaluator_create(function->expression);
    if (!function->evaluator)
        exitStatus(MATHEVAL_ERR);

    function->n_p = _initNR();
    function->n_m = _initNR();
    // function->n_i = _initNR();

    return function;
}

void Hessiana(FUNCTION *func, void **grad, void ***hessi)
{
    for (int i = 0; i < func->var_num; i++)
        for (int j = 0; j < func->var_num; j++)
            hessi[i][j] = evaluator_derivative(grad[i], func->names[j]);
}

void Gradiente(FUNCTION *func, void **grad)
{
    for (int i = 0; i < func->var_num; i++)
        grad[i] = evaluator_derivative(func->evaluator, func->names[i]);
}

void printMethod(FUNCTION *func, char *output)
{
    FILE *output_file;
    if (!output)
        output_file = stdout;
    else
        output_file = fopen(output, "a");

    if (!output_file)
        exitStatus(FOPEN_ERR);

    // cabeçalho
    fprintf(output_file, "%d\n%s\n#\n", func->var_num, func->expression);
    fprintf(output_file, "Iteração \t| Newton Padrão \t| Newton Modificado \t| Newton Inexato\n");
    int z = max(func->n_p->it_num, func->n_m->it_num);
    // int z = func->n_p->it_num;
    for (int i = 0; i < z; i++)
    {
        fprintf(output_file, "%d \t\t| ", i); // imprime iteração

        if (func->n_p->it_num > i)
            fprintf(output_file, "%1.14e\t| ", func->n_p->f_k[i]);
        else
            fprintf(output_file, "\t\t\t| ");

        if (func->n_m->it_num > i)
            fprintf(output_file, "%1.14e\t| \n", func->n_m->f_k[i]);
        else
            fprintf(output_file, "\t\t\t| \n");

        // repete para as outras duas colunas...
    }

    // imprimir os tempos
    fprintf(output_file, "Tempo total \t| %1.14e\t| %1.14e\t| %1.14e\n", func->n_p->timeFull, func->n_m->timeFull, func->n_p->timeFull);
    fprintf(output_file, "Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e\n", func->n_p->timeDer, func->n_m->timeDer, func->n_p->timeFull);
    fprintf(output_file, "Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e\n#\n\n", func->n_p->timeSL, func->n_m->timeSL, func->n_p->timeFull);

    if (output)
        fclose(output_file);
}

void deleteFunction(FUNCTION *func)
{
    free(func->initial_aps);
    for (int i = 0; i < func->var_num; i++)
        free(func->names[i]);
    free(func->names);

    evaluator_destroy(func->evaluator);
    free(func->expression);
    //_deleteResult(func->n_i);
    _deleteResult(func->n_m);
    _deleteResult(func->n_p);
    free(func);
}