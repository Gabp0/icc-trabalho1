#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

/*  Retorna tempo em milisegundos

	Forma de uso:

	double tempo;
	tempo = timestamp();
	<trecho de programa do qual se deseja medir tempo>
	tempo = timestamp() - tempo;
*/

double timestamp(void)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}

void prnVetorFloat(float *v, int n)
{
	for (int i = 0; i < n; ++i)
		printf("%g ", v[i]);
	printf("\n");
}

void prnVetorDouble(double *v, int n)
{
	for (int i = 0; i < n; ++i)
		fprintf(stderr, "%lg ", v[i]);
	fprintf(stderr, "\n");
}

void prnVetorLongDouble(long double *v, int n)
{
	for (int i = 0; i < n; ++i)
		printf("%Lg ", v[i]);
	printf("\n");
}

double *copyDoubleArray(double *a, int size)
{
	double *new = malloc(sizeof(double) * size);
	for (int i = 0; i < size; i++)
		new[i] = a[i];

	return new;
}

double **initDoubleMatrix(int size)
{
	double **A = malloc(sizeof(double *) * size);
	if (!A)
		exitStatus(MEM_ALOC);

	for (int i = 0; i < size; i++)
	{
		A[i] = malloc(sizeof(double) * size);
		if (!A[i])
			exitStatus(MEM_ALOC);
	}

	return A;
}

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

int max(int a, int b)
{
	return a > b ? a : b;
}

void exitStatus(EXIT_CODE code)
{
	switch (code)
	{
	case MEM_ALOC:
		perror("Falha na alocação de memória");
		exit(code);

	case INV_POINTER:
		perror("Ponteiro inválido");
		exit(code);

	default:
		break;
	}
}