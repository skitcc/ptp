#include "process.h"

int process(FILE *f)
{   
    int number = 1;
    if (fscanf(f, "%d", &number) != 1)
    {
        printf("В файле нет чисел\n");
        return ERROR_NO_NUMBERS;
    }
    int next_number = 0, mx = number, index = 1, min_index = 1;
    while (fscanf(f, "%d", &next_number) == 1)
    {
        index++;
        if (next_number > mx)
        {
            min_index = index;
            mx = next_number;
        }
        
        number = next_number;
    }
    printf("Индекс максимального элемента последовательности : %d\n", min_index);
    return 0;
}
