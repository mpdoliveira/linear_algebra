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

Fraction frac_div(Fraction frac1, Fraction frac2)
{
    return F(frac1.n * frac2.d, frac1.d * frac2.n);
}

Fraction frac_pow(Fraction frac, int power)
{
    if (power < 0)
    {
        int temp = frac.n;
        frac.n = frac.d;
        frac.d = temp;
    }
    else if (power == 0) {
        return F(1, 1);
    }

    Fraction new_frac = frac;

    while (power > 0)
    {
        new_frac.n *= frac.n;
        new_frac.d *= frac.d;
        power--;   
    }

    return new_frac;
}