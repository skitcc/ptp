#include "matrix_operations.h"


#include "matrix_operations.h"
#include <stdlib.h>

int add(matrix_data_t *matrix_a, matrix_data_t *matrix_b, result_data_t *result)
{
    if (matrix_a->rows != matrix_b->rows || matrix_a->cols != matrix_b->cols)
    {
        free(matrix_a->matrix);
        free(matrix_b->matrix);
        return ERR_ADD_SIZES;
    }

    int rows = matrix_a->rows;
    int cols = matrix_a->cols;

    result->rows = rows;
    result->cols = cols;

    result->matrix = malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (!result->matrix)
        return ERR_ALLOCATION;

    int *data = (int *)(result->matrix + rows);
    for (int i = 0; i < rows; i++)
    {
        result->matrix[i] = data + i * cols;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result->matrix[i][j] = matrix_a->matrix[i][j] + matrix_b->matrix[i][j];
        }
    }

    return 0;
}



int multiply(matrix_data_t *matrix_a, matrix_data_t *matrix_b, result_data_t *result)
{
    if (matrix_a->cols != matrix_b->rows)
    {
  
        return ERR_MUL_SIZES;
    }

    int rows = matrix_a->rows;
    int cols = matrix_b->cols;

    result->rows = rows;
    result->cols = cols;

    result->matrix = malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (!result->matrix)
        return ERR_ALLOCATION;

    
    int *data = (int *)(result->matrix + rows);
    for (int i = 0; i < rows; i++)
    {
        result->matrix[i] = data + i * cols;
    }

    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result->matrix[i][j] = 0; 
            for (int k = 0; k < matrix_a->cols; k++)
            {
                result->matrix[i][j] += matrix_a->matrix[i][k] * matrix_b->matrix[k][j];
            }
        }
    }

    return 0;
}
