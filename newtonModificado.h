#ifndef __NEWTONMODIFICADO__
#define __NEWTONMODIFICADO__

#define EXPRESSION_MAX_SIZE 1000
#define HESS_STEPS 5

#include "derivacao.h"
#include "functions.h"
#include <matheval.h>

NEWTON *NewtonModificado(FUNCTION *func);

#endif