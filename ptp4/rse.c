#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define REPEATS 1000

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
        if (iterations > 15)
        {
            sum_squared += (time - mean) * (time - mean);
            s = sqrt(sum_squared / iterations);

            std_err = s / sqrt(iterations + 1);

            double rse = (std_err / mean) * 100;
            
            if (rse < 1.0) {
                return 1;
            }
        }
        iterations++;
        if (iterations >= REPEATS) {
            return 2;
        }
    } 
    return EXIT_SUCCESS;
}