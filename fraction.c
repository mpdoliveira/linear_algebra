#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    int d;
} Fraction;

#define F(n, d) ((Fraction){n, d})

void frac_print(Fraction frac)
{
    printf("%d/%d", frac.n, frac.d);
}

