#include <stdio.h>

int main(void)
{
    int a = 0, b = 0, c = 0;

    int calc = 0;

    printf("Input three integers: ");
    while(scanf("%i %i %i", &a, &b, &c) == 3){
        calc = (2*(a + b + c)) + 7;
        printf("Twice the sum of the integers plus 7 is %i !\n", calc);
        return 0;
    }
}