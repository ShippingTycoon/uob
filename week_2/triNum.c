#include <stdio.h>

int main(void)
{
    /* Sum on numbers 1 to n */

    /* Print a sequence of triangle numbers using iteration
    based on the previous */

    int i;
    int t[50] = {1};
    for (i=1; i<50; i++){
        t[i] = t[i-1] + i + 1;
        printf("%d\n", t[i]);
    }
    return 0;
}