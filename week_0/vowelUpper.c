#include <stdio.h>
#include <ctype.h>

int isvowel(char c);

int main(void)
{
    char c;

    while ((c = getchar()) != EOF)
    {
        if (isvowel(c) == 1)
        {
            putchar(toupper(c));
        }
        else
        {
            putchar(c);
        }
        
    }
}

int isvowel(char c)
{
    c = toupper(c);
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
    {
        return 1;
    }
    return 0;
}