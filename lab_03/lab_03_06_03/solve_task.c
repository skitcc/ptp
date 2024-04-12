#include "solve_task.h"

void spiral_fill(int (*matrix)[COLUMNS], int n) 
{
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int direction = 0;
    int value = 1;

    while (top <= bottom && left <= right) 
    {
        if (direction == 0) 
        {
            for (int i = top; i <= bottom; i++) 
            {
                matrix[i][left] = value++;
            }
            left++;
        }
        else if (direction == 1) 
        {
            for (int i = left; i <= right; i++) 
            {
                matrix[bottom][i] = value++;
            }
            bottom--;
        }
        else if (direction == 2) 
        {
            for (int i = bottom; i >= top; i--) 
            {
                matrix[i][right] = value++;
            }
            right--;
        }
        else if (direction == 3) 
        {
            for (int i = right; i >= left; i--) 
            {
                matrix[top][i] = value++;
            }
            top++;
        }
        direction = (direction + 1) % 4;
    }
}