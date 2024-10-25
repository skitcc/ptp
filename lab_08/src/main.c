#include "definitions.h"
#include "input.h"
#include "check_args.h"
#include "structs.h"
#include "matrix_operations.h"
#include "det.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
    matrix_data_t matrix_a, matrix_b;
    result_data_t matrix_res;
    int rc = 0;
    if ((rc = check(argc, argv)))
    {
        return rc;
    }

    char action = argv[1][0];

    if (action == 'a')
    {
        char in_file1[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(in_file1, argv[2], MAX_LEN_FILENAME + 1);
        char in_file2[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(in_file2, argv[3], MAX_LEN_FILENAME + 1);
        char out_file[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(out_file, argv[4], MAX_LEN_FILENAME + 1);


        matrix_a.matrix = input_matrix(in_file1);
        if (matrix_a.matrix == NULL)
            return 1;

        // printf("1\n");
        matrix_b.matrix = input_matrix(in_file2);
        if (matrix_b.matrix == NULL)
        {
            free(matrix_a.matrix); 
            return 2;
        }
        FILE *f_in = fopen(in_file1, "r"); 
        if (!f_in)
            return 2;
        if (fscanf(f_in, "%d%d%d", &matrix_a.rows, &matrix_a.cols, &matrix_a.nnz) != 3)
        {
            fclose(f_in);
            return ERR_INPUT;
        }

        f_in = fopen(in_file2, "r");
        if (!f_in)
            return 2;
        if (fscanf(f_in, "%d%d%d", &matrix_b.rows, &matrix_b.cols, &matrix_b.nnz) != 3)
        {
            fclose(f_in);
            return ERR_INPUT;
        }

        // print_matrix(matrix_a.matrix, matrix_a.rows, matrix_a.cols);
        // print_matrix(matrix_b.matrix, matrix_b.rows, matrix_b.cols);



        if ((rc = add(&matrix_a, &matrix_b, &matrix_res)))
            return rc;

        if (print_matrix_to_file(matrix_res.matrix, matrix_res.rows, matrix_res.cols, out_file))
            return 3;
        free(matrix_a.matrix);
        free(matrix_b.matrix);
        if (matrix_res.matrix)
            free(matrix_res.matrix);
    }    
            
    if (action == 'm')
    {
        char in_file1[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(in_file1, argv[2], MAX_LEN_FILENAME + 1);

        char in_file2[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(in_file2, argv[3], MAX_LEN_FILENAME + 1);
        char out_file[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(out_file, argv[4], MAX_LEN_FILENAME + 1); 
        matrix_a.matrix = input_matrix(in_file1);
        if (matrix_a.matrix == NULL)
            return 1;


        matrix_b.matrix = input_matrix(in_file2);
        if (matrix_b.matrix == NULL)
        {
            free(matrix_a.matrix);
            return 2;
        }
        FILE *f_in = fopen(in_file1, "r"); 
        if (!f_in)
            return 2;
        if (fscanf(f_in, "%d%d%d", &matrix_a.rows, &matrix_a.cols, &matrix_a.nnz) != 3)
        {
            fclose(f_in); 
            return ERR_INPUT;
        }

        f_in = fopen(in_file2, "r");
        if (!f_in)
            return 2;
        if (fscanf(f_in, "%d%d%d", &matrix_b.rows, &matrix_b.cols, &matrix_b.nnz) != 3)
        {
            fclose(f_in);
            return ERR_INPUT;
        }

        // print_matrix(matrix_a.matrix, matrix_a.rows, matrix_a.cols);
        // print_matrix(matrix_b.matrix, matrix_b.rows, matrix_b.cols);

        if ((rc = multiply(&matrix_a, &matrix_b, &matrix_res)))
            return rc;
        
        if (print_matrix_to_file(matrix_res.matrix, matrix_res.rows, matrix_res.cols, out_file))
            return 3;
        free(matrix_a.matrix);
        free(matrix_b.matrix);
        free(matrix_res.matrix);
    }


    int error_code = 0;
    if (action == 'o')
    {
        char in_file1[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(in_file1, argv[2], MAX_LEN_FILENAME + 1);
        char out_file[MAX_LEN_FILENAME + 1] = { 0 };
        strncpy(out_file, argv[3], MAX_LEN_FILENAME + 1);

        matrix_a.matrix = input_matrix(in_file1);
        if (matrix_a.matrix == NULL)
            return 1;
    

        FILE *f_in = fopen(in_file1, "r"); 
        if (!f_in)
            return 2;
        if (fscanf(f_in, "%d%d%d", &matrix_a.rows, &matrix_a.cols, &matrix_a.nnz) != 3)
        {
            fclose(f_in);
            return ERR_INPUT;
        }

        if (matrix_a.rows != matrix_a.cols)
        {
            free(matrix_a.matrix);
            return 4;
        }
        // print_matrix(matrix_a.matrix, matrix_a.rows, matrix_a.cols);


        double det = count_determinant(matrix_a.matrix, matrix_a.rows, &error_code);
        if (error_code)
            return error_code;
        FILE *f = fopen(out_file, "w");
        if (f == NULL)
            return 4;
        fprintf(f, "%lf\n", det);
        fclose(f);
        free(matrix_a.matrix);
    }
    return 0;
}
