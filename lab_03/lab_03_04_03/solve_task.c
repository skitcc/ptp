#include "solve_task.h"

// Переформатирование матрицу по условию
void sorting_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns)
{
    size_t c = 0;
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (j >= c && j <= columns - c - 1)
            {
                int temp = matrix[j][c];
                matrix[j][c] = matrix[j][columns - c - 1];
                matrix[j][columns - c - 1] = temp;
            }
        }
        c++;
    }
}
