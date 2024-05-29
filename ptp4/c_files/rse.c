#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define REPEATS 1000
#define MAX_ITERATIONS_REACHED 1

int main(void)
{
    double time = 0.0;
    double sum_squared = 0.0;
    double s = 0.0;
    double std_err = 0.0;
    size_t iterations = 0;
    double mean = 0.0;
    scanf("%lf", &mean);
    while (scanf("%lf", &time) != EOF) {
        printf("%lf\n", time);
        sum_squared += (time - mean) * (time - mean);
        s = sqrt(sum_squared / iterations);

        std_err = s / sqrt(iterations + 1);

        double rse = (std_err / mean) * 100;
        
        if (rse < 1.0 && iterations > 20) {
            printf("rse = %lf\n", rse);
            printf("iterations = %zu\n", iterations);
            return EXIT_SUCCESS;
        }
        
        iterations++;
        if (iterations >= REPEATS) {
            printf("iterations_reached : %zu", iterations);
            return MAX_ITERATIONS_REACHED;
        }
    } 
    return 2;
}