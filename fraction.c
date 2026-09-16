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

Fraction frac_add(Fraction frac1, Fraction frac2)
{
    return F((frac1.n * frac2.d) + (frac2.n * frac1.d), frac1.d * frac2.d);
}

Fraction frac_mul(Fraction frac1, Fraction frac2)
{
    return F(frac1.n * frac2.n, frac1.d * frac2.d);
}