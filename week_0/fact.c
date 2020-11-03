#include <stdio.h>

int fact(int a);

int main(void)
{
    int a, f;

    printf("Input a number: \n");
    if (scanf("%d", &a) == 1)
    {
        f = fact(a);
        printf("%d!is %d\n", a, f);
    }   
    
    return 0;
}

int fact(int a)
{
    if (a > 0)
    {
        return (a*fact(a-1));
    }
    else
    {
        return 1;
    }

    return a;
    
}

/* int fact(int a)
{
    int i;
    for(i = (a - 1); i > 0; i--)
    {
        a *= i;
    }
    return a;
} */