#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct 
{
    int **matrix;
    int rows;
    int cols;
    int nnz;
} matrix_data_t;

typedef struct
{
    int **matrix;
    int rows;
    int cols;
} result_data_t;


#endif
