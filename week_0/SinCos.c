#include <stdio.h>
#include <math.h>

int main(void)
{
    double x, y = 1.0;

    printf("Type a number: ");
    while (scanf("%lf", &x) == 1 && x != EOF)
    {
        y = (pow(sin(x), 2) + (pow(cos(x), 2)));
        printf("%lf\n", y);
        
    }
    return 0;
}