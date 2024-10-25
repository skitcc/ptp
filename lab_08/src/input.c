#include "input.h"

double **input_matrix(char *filename)
{
    FILE *in_file = fopen(filename, "r");
    if (in_file == NULL)
        return NULL;

    int n = 0, m = 0, nnz = 0;

    if (fscanf(in_file, "%d%d%d", &n, &m, &nnz) != 3)
    {
        fclose(in_file);
        return NULL;
    }

    if (n <= 0 || m <= 0 || nnz < 0)
    {
        fclose(in_file);
        return NULL;
    }
    double **a = malloc(n * sizeof(double *) + n * m * sizeof(double));
    if (a == NULL)
    {
        fclose(in_file);
        return NULL;
    }

    double *data = (double *)(a + n); 
    for (int i = 0; i < n; i++)
    {
        a[i] = data + i * m;    
    }

    for (int i = 0; i < n * m; i++)
    {
        data[i] = 0.0;
    }
    for (int i = 0; i < nnz; i++)
    {
        int row = 0, column = 0;
        double value = 0.0;
        if (fscanf(in_file, "%d%d%lf", &row, &column, &value) != 3)
        {
            free(a);
            fclose(in_file);
            return NULL;
        }
        row--;
        column--;
        if (row < 0 || column < 0 || fabs(value - 0.0) < EPS || row >= n || column >= m)
        {
            free(a);
            fclose(in_file);
            return NULL;
        }
        a[row][column] = value;
    }

    fclose(in_file);
    return a;
}

int print_matrix_to_file(double **matrix, int n, int m, const char *file) 
{
    if (matrix == NULL)
        return 2;
    FILE *f = fopen(file, "w");
    if (f == NULL)
    {
        return 1;
    }
    int nnz = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (fabs(matrix[i][j] - 0.0) > EPS)
                nnz++;
        }
    }

    fprintf(f, "%d %d %d\n", n, m, nnz);
    for (int i = 0; i < n; i++)
    { 
        for (int j = 0; j < m; j++) 
        {
            if (fabs(matrix[i][j] - 0.0) > EPS)
            {
                fprintf(f, "%d %d %lf", i + 1, j + 1, matrix[i][j]);
                fprintf(f, "\n");
            }
        }
    }
    fclose(f);
    return 0;
}

void print_matrix(double **matrix, int n, int m) 
{
    for (int i = 0; i < n; i++)
    { 
        for (int j = 0; j < m; j++) 
            fprintf(stdout, "%lf ", matrix[i][j]);
        
        fprintf(stdout, "\n");
    }
}





