#include <stdio.h>

int main(void)
{
    char c;
    int i;

    while( (c = getchar()) != EOF)
    {
        putchar(c);
        putchar(c);
    }
    return 0;
}