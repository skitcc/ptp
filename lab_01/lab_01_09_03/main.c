#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define INPUT_NUMBER 1

double calculate_g(double x);

int main(void)
{
    double x;

    if (scanf("%lf", &x) != INPUT_NUMBER || x < 0)
    {
        printf("Не подходит");
        return EXIT_FAILURE;
    }

    double g = calculate_g(x);
    printf("Result: %lf\n", g);

    return EXIT_SUCCESS;
}

double calculate_g(double x)
{
    int i = 0;
    double mult = 1;

    while (x >= 0)
    {
        i++;
        mult *= (x + i);
        if (scanf("%lf", &x) != INPUT_NUMBER)
        {
            printf("Не подходит");
            exit(1);
        }
    }

    return exp(1 / mult);
}
