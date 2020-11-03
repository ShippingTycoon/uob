#include <stdio.h>
#include <ctype.h>

/* toupper will leave chars already upper case*/
/* ctype.h has loads of useful checking and assigning functions */
int main(void)
{
    char c; 

    while ((c = getchar()) != EOF)
    {
        putchar(toupper(c));
    }
    return 0;
}