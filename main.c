#include "args.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *output = getArgs(argc, argv);
    printf("%s\n", output);
}