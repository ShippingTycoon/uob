#include <stdio.h>
#include <assert.h>

int mul(int a, int b);

int x, y, m;

int main(void)
{
    printf("Type two numbers you would like to multiply: ");
    if (scanf("%d%d", &x, &y) == 2)
    {
        assert(x > 0 && y > 0);
        m = mul(x, y);
        printf("%d multiplied by %d is %d\n", x, y, m);
    }
    return 0;
}

int mul(int a, int b)
{
    int c = 0, i = 0;

    for(i = 0; i < a; i++)
    {
        c += b;
    }
    return c;
}