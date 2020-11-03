#include <stdio.h>

int main(void)
{
    int a, b, i = 1;

    a = ++i;
    b = i++;
    printf("%i %i %i\n", a, b, i);
    return 0;
}