#include <stdio.h>

void zero_array(int b[], int s);
void zero_array2(int *b, int s, int c[]);

int main(void)
{
    int a[5];
    int *p;
    p = a;
    
    /* Passes in the pointer to the start of the array and 
    not the address itself, but to pass in the middle of 
    the array the syntax would be zero_array(&a[1], 3) */
    zero_array2(p, 5, a);
    return 0;
}

void zero_array(int b[], int s)
{
    int i;

    for (i=0; i<s; i++){
        b[i] = 0;
        printf("\n%d\n", b[i]);
    }
}

void zero_array2(int *b, int s, int c[])
{
    int i;

    for (i=0; i<s; i++){
        *b++ = 0;
        printf("\n%d\n", c[i]);
    }
}