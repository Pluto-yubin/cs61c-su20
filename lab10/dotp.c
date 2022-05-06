#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int array_size = 100000;

#include "omp_apps.h"

int main()
{
    char* report = compute_dotp(array_size);
    printf("%s\n", report);
    return 0;
}
