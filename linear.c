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
