#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

float calculate_vector_product(float x1, float y1, float x2, float y2) 
{
    return x1 * y2 - x2 * y1;
}

bool segments_intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
{
    if (fabs(calculate_vector_product(x2 - x1, y2 - y1, x4 - x3, y4 - y3)) < 0.0001) 
        return false;   

    float t1 = calculate_vector_product(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
    float t2 = calculate_vector_product(x2 - x1, y2 - y1, x4 - x1, y4 - y1);
    float t3 = calculate_vector_product(x4 - x3, y4 - y3, x1 - x3, y1 - y3);
    float t4 = calculate_vector_product(x4 - x3, y4 - y3, x2 - x3, y2 - y3);
    
    return (t1 * t2 < 0) && (t3 * t4 < 0);
}

int main(void) 
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    printf("Введите координаты отрезка PQ ((xP, yP), (xQ, yQ)), RS ((xR, yR), (xS, yS)):\n"); 
    if (scanf("%f%f%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4) != 8)
    {
        printf("Ошибка ввода\n");
        return EXIT_FAILURE;
    }
    if (!((fabs(x1 - x2) < 0.0001 && fabs(y1 - y2) < 0.0001) || 
        (fabs(x3 - x4) < 0.0001 && fabs(y3 - y4) < 0.0001)))
    {
        if (segments_intersect(x1, y1, x2, y2, x3, y3, x4, y4))
            printf("1\n");
        else
            printf("0\n");
    }
    else
    {
        printf("Концы отрезков должны иметь разные координаты\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
