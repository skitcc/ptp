#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define INPUT_NUMBER 2
#define WRONG_INPUT_NUMBER 2

double find_sum(double x, double eps)
{
    int free_multiplier = 1;
    double sum = 0, member_row = 1;

    while (member_row >= eps)
    {
        sum += member_row;
        member_row *= x * x * free_multiplier / (free_multiplier + 1);
        free_multiplier += 2;
    }

    return sum;
}

double given_function(double x)
{
    return 1 / sqrt(1 - x * x);
}

int main(void)
{	
    double x, eps;

    if (scanf("%lf%lf", &x, &eps) != INPUT_NUMBER)
        return WRONG_INPUT_NUMBER;

    if ((eps <= 0 || eps > 1) || (x <= -1 || x >= 1))
    {
        printf("eps должен быть в рамках от (0, 1), |x| <= 1");
        return EXIT_FAILURE;
    }
    double sum = find_sum(x, eps);
    double absolute_exact = fabs(given_function(x) - sum);
    double relative_exact = absolute_exact / given_function(x);

    printf("%lf %lf %lf% lf", sum, given_function(x), absolute_exact, relative_exact);

    return EXIT_SUCCESS;
}
