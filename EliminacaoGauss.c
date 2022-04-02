#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <matheval.h>

#include "EliminacaoGauss.h"

void _pivot(double **H_x, double *g_f, int n, int i)
{
  double max = fabs(H_x[i][i]);
  int max_i = i;
  for (int j = i + 1; j < n; ++j)
  {
    double v = fabs(H_x[j][i]);
    if (v > max)
    {
      max = v;
      max_i = j;
    }
  }
  if (max_i != i)
  {
    double *tmp = H_x[i];
    H_x[i] = H_x[max_i];
    H_x[max_i] = tmp;

    double aux = g_f[i];
    g_f[i] = g_f[max_i];
    g_f[max_i] = aux;
  }
}

void _retrossubs(double **H_x, double *X, double *g_f, int n)
{
  for (int i = n - 1; i >= 0; --i)
  {
    X[i] = g_f[i];
    for (int j = i + 1; j < n; j++)
      X[i] -= H_x[i][j] * X[j];
    X[i] /= H_x[i][i];
  }
}

void _triang(double **H_x, double *X, double *g_f, int n)
{
  for (int i = 0; i < n; ++i)
  {
    _pivot(H_x, g_f, n, i);
    for (int k = i + 1; k < n; ++k)
    {
      double m = H_x[k][i] / H_x[i][i];
      if (isnan(m))
        printf("ERRO: %g\n", H_x[i][i]);
      H_x[k][i] = 0.0;
      for (int j = i + 1; j < n; ++j)
        H_x[k][j] -= H_x[i][j] * m;
      g_f[k] -= g_f[i] * m;
    }
  }
}

void hessianGaussElimination(double **H_x, double *X, double *g_f, int n)
{
  _triang(H_x, X, g_f, n);
  _retrossubs(H_x, X, g_f, n);
}

void hessianGaussEliminationLU(double **H_x, double *X, double *g_f, int n)
{
  _triang(H_x, X, g_f, n);
  _retrossubs(H_x, X, g_f, n);
}

// double **solveHessian(void ***H, double *X, int n)
// {
//   double **H_x = malloc(sizeof(double *));
//   for (int i = 0; i < n; i++)
//   {
//     H_x[i] = malloc(sizeof(double));
//   }

//   for (int i = 0; i < n; i++)
//   {
//     for (int j = 0; j < n; j++)
//     {
//       evaluator_evaluate(H[i][j], 1, "x", )
//     }
//   }
// }
