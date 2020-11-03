#include <stdio.h>

void change(int *p);

int main(void)
{
    int v = 1;
    int *p;
    *p = v;
    change(*p);
    printf("%d\n", v);
    return 0;
}

void change(int *p)
{
    &p = 2;
}