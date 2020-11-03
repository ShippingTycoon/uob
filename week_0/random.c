#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, n;

    printf("\n%s\n%s", "Randomly distributed integers are printed.", 
    "How many do you want to see?    ");
    if (scanf("%d", &n) != 1){
        printf("Didn't understand your number?");
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (i % 4 == 0){
            printf("\n");
        }
        printf("%12d", rand());
    }
    printf("\n");
    return 0;
}