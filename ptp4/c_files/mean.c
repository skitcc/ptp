#include <stdio.h>
#include <stddef.h>

// Функция для расчета среднего значения для внешних измерений
int main(void)
{
    size_t c = 0;
    double mean = 0.0;
    double time = 0.0;
    while (scanf("%lf", &time) != EOF)
    {
        mean += time;
        c++;
    }
    mean /= c;
    printf("%lf\n", mean);
    return 0;
}