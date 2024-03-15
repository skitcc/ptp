#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    double a, b, phi, square;
    scanf("%lf%lf%lf", &a, &b, &phi);

    square = 0.5 * a * b * sin(phi / 180 * M_PI);

    printf("%lf", square);

    return EXIT_SUCCESS;
}
