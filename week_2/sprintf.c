#include <stdio.h>
#include <string.h>

int main(void)
{
    int i = 7;
    float f = 17.041;
    char str[100];
    sprintf(str, "%d %f", i, f);
    printf("%s\n", str);
    return 0;
}
/* Outputs : 7 17.041000 
Uselful if you need to create a string for passing to 
another function for further processing*/