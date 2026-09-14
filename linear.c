#include <stdio.h>
#include <stdlib.h>
#include <linear.h>

typedef struct
{
    float **values;
    int lines;
    int columns;
} matrix;

matrix *new_matrix(int lines, int columns)
{
    matrix *m = malloc(sizeof(matrix));
    m->values = malloc(sizeof(*m->values) * lines);
    for (int i = 0; i < lines; i++)
    {
        m->values[i] = malloc(sizeof(float) * columns);

        for (int j = 0; j < columns; j++)
        {
            m->values[i][j] = 0;
        }
    }
    m->lines = lines;
    m->columns = columns;
    return m;
}

matrix *sum_matrix(matrix *m0, matrix *m1) {
    if (m0->lines != m1->lines || m0->columns != m1->columns) {
        return NULL;
    }

    matrix *sum = new_matrix(m0->lines, m0->columns);

    for (int i = 0; i < sum->lines; i++) {
        for (int j = 0; j < sum->columns; j++) {
            sum->values[i][j] = m0->values[i][j] + m1->values[i][j];
        }
    }

    return sum;
}

matrix *scalar_mult_matrix(float scalar, matrix *m)
{
    matrix *scalar_mult = new_matrix(m->lines, m->columns);

    for (int i = 0; i < scalar_mult->lines; i++) {
        for (int j = 0; j < scalar_mult->columns; j++) {
            scalar_mult->values[i][j] = scalar * m->values[i][j];
        }
    }

    return scalar_mult;
}

matrix *mult_matrix(matrix *m0, matrix *m1)
{
    if (m0->columns != m1->lines)
    {
        return NULL;
    }

    matrix *mult = new_matrix(m0->lines, m1->columns);

    for (int i = 0; i < mult->lines; i++)
    {
        for (int j = 0; j < mult->columns; j++)
        { 
            for (int k = 0; k < m0->columns; k++)
            {
                mult->values[i][j] += m0->values[i][k] * m1->values[k][j];
            }
        }
    }

    return mult;
}