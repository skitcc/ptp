#include "input.h"



FILE *validate_file(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return NULL;
    return f;
}

int **input_matrix(char *filename)
{
    FILE *in_file = validate_file(filename);
    if (in_file == NULL)
        return NULL;

    int n = 0, m = 0, nnz = 0;

    if (fscanf(in_file, "%d%d%d", &n, &m, &nnz) != 3)
    {
        fclose(in_file);
        return NULL;
    }

    if (n <= 0 || m <= 0 || nnz < 0)
        return NULL;

    int **a = malloc(n * sizeof(int *) + n * m * sizeof(int));
    if (a == NULL)
    {
        fclose(in_file);
        return NULL;
    }

    int *data = (int *)(a + n); 
    for (int i = 0; i < n; i++)
    {
        a[i] = data + i * m;    
    }

    for (int i = 0; i < n * m; i++)
    {
        data[i] = 0;
    }

    
    for (int i = 0; i < nnz; i++)
    {
        int row, column, value;
        if (fscanf(in_file, "%d%d%d", &row, &column, &value) != 3)
        {
            fclose(in_file);
            return NULL;
        }

        if (row < 0 || column < 0 || value < 0 || row >= n || column >= m)
        {
            fclose(in_file);
            return NULL;
        }
        a[row][column] = value;
    }

    fclose(in_file);
    return a;
}

void print_matrix_to_file(int **matrix, int n, int m, char *file) 
{
    FILE *f = fopen(file, "w");
    if (f == NULL)
        return;
    
    for (int i = 0; i < n; i++)
    { 
        for (int j = 0; j < m; j++) 
            fprintf(f, "%d ", matrix[i][j]);
        
        fprintf(f, "\n");
    }
    fclose(f);
}

void print_matrix(int **matrix, int n, int m) 
{

    for (int i = 0; i < n; i++)
    { 
        for (int j = 0; j < m; j++) 
            fprintf(stdout, "%d ", matrix[i][j]);
        
        fprintf(stdout, "\n");
    }
}



