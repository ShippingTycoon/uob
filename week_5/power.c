#include <stdio.h>

unsigned long int power(unsigned long int a, unsigned long int b);

int main(void)
{
    unsigned long int x = 2;
    unsigned long int y = 16;

    printf("%lu^%lu = %ld\n", x, y, power(x, y));
    return 0;
}

unsigned long int power(unsigned long int a, unsigned long int b)
{
    unsigned int i;
    int tot = a;
    for(i=1; i<b; i++){
        tot = tot*a;
    }
    return tot;
}
