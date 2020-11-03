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
    int t;
    /* a^1 = a */
    if(b==1){
        return a;
    }
    if(a==0){
        return 0;
    }
    /* a^0 */
    if(b==0){
        return 1;
    }
    /* a*a*a*a*a*a = b*b if b=a*a*a */
    if(b%2==0){
        t = power(a,b/2);
        return t*t;
    }
    /* power(a,4) = a*a*a*a = a*power(a,3) */
    return a*power(a,b-1);
}
