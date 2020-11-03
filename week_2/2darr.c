#include <stdio.h>

/* Number of rows */
#define M 3
/* Number of columns */
#define N 4

int main(void)
{
    int a[M][N], i, j, sum = 0;

    putchar('\n');
    /* Fill array */
    for (i=0; i<M; i++){
        for (j=0; j<N; j++){
            a[i][j] = i+j;
        }
    }
    /* Array values */
    for (i=0; i<M; i++){
        for (j=0; j<N; j++){
            printf("a[%d][%d] = %d\n", i, j, a[i][j]);
        }
        printf("\n");
    }
    /* Sum the array */
    for (i=0; i<M; i++){
        for (j=0; j<N; j++){
            sum += a[i][j];
        }
    }
    printf("\nsum = %d\n\n", sum);
    return 0;
}