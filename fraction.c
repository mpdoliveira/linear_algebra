#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    int d;
} Fraction;

#define F(n, d) ((Fraction){n, d})

