#include "solve_task.h"
bool summ_digits(int digit)
{
    int summ = 0;
    while (abs(digit) > 0)
    {
        summ += digit % 10;
        digit /= 10;
    }

    return summ > 10 || summ < -10;
}

void shift_array(int array[], int lenght)
{
    int start = array[0];

    for (int i = 0; i < lenght - 1; i++)
        array[i] = array[i + 1];

    array[lenght - 1] = start;
}


int fill_array(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[])
{
    size_t ind = 0;
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (summ_digits(matrix[i][j]))
                array[ind++] = matrix[i][j];
        }
    }
    return ind;
}

void refill_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[])
{
    size_t ind = 0;
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (summ_digits(matrix[i][j]))
                matrix[i][j] = array[ind++];
        }
    }
}
