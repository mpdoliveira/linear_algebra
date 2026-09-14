#include <stdio.h>
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
    m->values = malloc(sizeof(float) * lines);
    for (int i = 0; i < lines; i++)
    {
        m->values[i] = malloc(sizeof(float) * columns);

        for (int j = 0; j < columns; j++)
        {
            m->values[i][j] = 0;
        }
    }
    return m;
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
                mult->values[i][j] += m0->values[i][k] * m1->values[k][1];
            }
        }
    }

    return mult;
}