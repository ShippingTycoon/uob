#include <stdio.h>
#include <math.h>

enum calc {plus, minus};
typedef enum calc calc;

int main(void)
{
    /* Compute pi iterating through smaller and smaller loops */

    /* Switching the adding and subtracting - boolean */

    /* Remembering the previous fraction */
    double pi = 4, i=3, count = 0;
    calc sum = minus;

    while (pi>3.141592653 || pi<3.141592653){
        if (sum == minus){
            pi -= (4/i);
            sum = plus;
        }
        else{
            pi += (4/i);
            sum = minus;
        }
        i+=2;
        count++;
    }

    printf("%.9f\n%f", pi, count);
    return 0;
}