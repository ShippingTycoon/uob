#include <stdio.h>

int main(void)
{
    /* Pointers can only be assigned when both sides have
    the same type */
    int i , *p;
    i = 5;
    p = &i; /* Has to be assigned to the variable, not the
            value of the variable (5) */
    printf("%d\n", *p); /* Dereference p */

    i = 17;
    printf("%d\n", *p);

    *p = 10;
    printf("%d\n", i);
}