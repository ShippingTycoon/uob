#include <stdio.h>

int hail(int a);

int main(void)
{
    int h;
    printf("Type a number you would like to run through the hailstone sequence: ");
    if (scanf("%d", &h) == 1)
    {
        int i;
        for (i = 0; i < 15; i++)
        {
            printf("\n%d\n", h);
            h = hail(h);
        }
    }
    return 0;
}

int hail(int a)
{
    if (a%2 == 0)
    {
        return (a/2);
    }
    else if (a%2 == 1)
    {
        return ((a*3) + 1);
    }
    
    return 0;
}