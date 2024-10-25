#include "det.h"

double **allocate_minor(int size)
{
    double **minor = malloc(size * sizeof(double *) + size * size * sizeof(double));

    if (minor == NULL)
        return NULL;

    double *data = (double *)(minor + size); 

    for (int i = 0; i < size; i++)
    {
        minor[i] = data + i * size;    
    }

    return minor;
}

void fill_minor(double **matrix, double **minor, int n, int current_col)
{
    for (int i = 1; i < n; i++)
    {
        int minor_col = 0;
        for (int j = 0; j < n; j++)
        {
            if (j == current_col)
                continue;
            minor[i - 1][minor_col] = matrix[i][j];
            minor_col++;
        }
    }
}

double count_determinant(double **matrix, int n, int *error_code)
{
    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0;
    int sign = 1;

    double **minor = allocate_minor(n - 1);

    if (minor == NULL)
    {
        *error_code = 1;
        return ERR_ALLOCATION;
    }

    for (int col = 0; col < n; col++) 
    {
        fill_minor(matrix, minor, n, col);
        det += sign * matrix[0][col] * count_determinant(minor, n - 1, error_code);
        sign = -sign; 
    }

    free(minor);
    return det;
}
