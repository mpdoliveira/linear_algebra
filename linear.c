#include <stdio.h>
#include <stdlib.h>

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
        m->values[i] = calloc(columns, sizeof(float));

        for (int j = 0; j < columns; j++)
        {
            m->values[i][j] = 0;
        }
    }
    m->lines = lines;
    m->columns = columns;
    return m;
}

matrix *sum_matrix(matrix *m0, matrix *m1)
{
    if (m0->lines != m1->lines || m0->columns != m1->columns)
    {
        return NULL;
    }

    matrix *sum = new_matrix(m0->lines, m0->columns);

    for (int i = 0; i < sum->lines; i++)
    {
        for (int j = 0; j < sum->columns; j++)
        {
            sum->values[i][j] = m0->values[i][j] + m1->values[i][j];
        }
    }

    return sum;
}

matrix *factor_mult_matrix(float factor, matrix *m)
{
    matrix *factor_mult = new_matrix(m->lines, m->columns);

    for (int i = 0; i < factor_mult->lines; i++)
    {
        for (int j = 0; j < factor_mult->columns; j++)
        {
            factor_mult->values[i][j] = factor * m->values[i][j];
        }
    }

    return factor_mult;
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

void free_matrix(matrix *m)
{
    for (int i = 0; i < m->lines; i++)
    {
        free(m->values[i]);
    }
    free(m->values);
    free(m);
}

matrix *copy_matrix(matrix *m)
{
    matrix *new = new_matrix(m->lines, m->columns);
    if (new == NULL) {
        return NULL;
    }

    for (int i = 0; i < new->lines; i++)
    {
        for (int j = 0; j < new->columns; j++)
        {
            new->values[i][j] = m->values[i][j];
        }
    }
    return new;
}


// Elementar operations

void line_switch_matrix(matrix *m, unsigned int line1, unsigned int line2)
{
    float* temp_line = malloc(sizeof(float) * m->columns);

    for (int i = 0; i < m->columns; i++) {
        temp_line[i] = m->values[line1][i];
        m->values[line1][i] = m->values[line2][i];
        m->values[line2][i] = temp_line[i];
    }
    free(temp_line);
}

void column_switch_matrix(matrix *m, unsigned int column1, unsigned int column2)
{
    float* temp_column = malloc(sizeof(float) * m->lines);

    for (int i = 0; i < m->lines; i++) {
        temp_column[i] = m->values[i][column1];
        m->values[i][column1] = m->values[i][column2];
        m->values[i][column2] = temp_column[i];
    }
    free(temp_column);
}

void factor_line_add(matrix *m, unsigned int to_line, unsigned int from_line, float factor)
{
    for (int i = 0; i < m->columns; i++) {
        m->values[to_line][i] += factor * m->values[from_line][i];
    }
}

void factor_column_add(matrix *m, unsigned int to_column, unsigned int from_column, float factor)
{
    for (int i = 0; i < m->lines; i++) {
        m->values[i][to_column] += factor * m->values[i][from_column];
    }
}

void line_factor(matrix *m, unsigned int line, float factor)
{
    for (int i = 0; i < m->columns; i++)
    {
        m->values[line][i] = factor * m->values[line][i];
    }
}

void print_matrix(matrix *m) {
    for (int i = 0; i < m->lines; i++) {
        printf("| ");
        for (int j = 0; j < m->columns; j++) {
            printf("%.2f ", m->values[i][j]);
        }
        printf("|\n");
    }
}


int main() {
    matrix *m = new_matrix(3, 3);
    m->values[0][0] = 1;
    m->values[0][1] = 0;
    m->values[0][2] = 0;
    m->values[1][0] = 0;
    m->values[1][1] = 1;
    m->values[1][2] = 0;
    m->values[2][0] = 0;
    m->values[2][1] = 0;
    m->values[2][2] = 1;

    factor_line_add(m, 1, 0, -1);
    factor_line_add(m, 2, 0, -1);
    factor_line_add(m, 2, 1, 2);
    line_switch_matrix(m, 1, 2);
    factor_line_add(m, 2, 1, 2);
    factor_line_add(m, 0, 1, -1);
    line_factor(m, 2, 1.0/9.0);
    factor_line_add(m, 1, 2, -4);
    factor_line_add(m, 0, 2, 3);

    print_matrix(m);
}