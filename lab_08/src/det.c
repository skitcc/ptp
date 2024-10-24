#include "det.h"

int **allocate_minor(int size)
{
    // Выделяем память для указателей на строки и самих данных
    int **minor = malloc(size * sizeof(int *) + size * size * sizeof(int));

    if (minor == NULL)
        return NULL;

    // Указатель на начало данных
    int *data = (int *)(minor + size); 

    for (int i = 0; i < size; i++)
    {
        minor[i] = data + i * size;    
    }

    return minor;
}

void fill_minor(int **matrix, int **minor, int n, int current_col)
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

int count_determinant(int **matrix, int n, int *error_code)
{
    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    int det = 0;
    int sign = 1;

    int **minor = allocate_minor(n - 1);

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
