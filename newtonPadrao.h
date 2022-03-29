#ifndef __NEWTONPADRAO__
#define __NEWTONPADRAO__

#define EXPRESSION_MAX_SIZE 1000

#include "functions.h"
#include <matheval.h>

void NewtonPadrao(FUNCTION *func);
void Gradiente(FUNCTION *func, void **grad);
void Hessiana(FUNCTION *func, void **grad, void ***hessi);

#endif