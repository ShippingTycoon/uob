#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int median = RAND_MAX/2, minus_cnt = 0, plus_cnt = 0, random_number;

    for( int i = 0; i < 500; i++){
        random_number = rand();
        if (random_number < median){
            minus_cnt ++;
        }
        if (random_number >= median){
            plus_cnt ++;
        }
        printf("%d\n", plus_cnt - minus_cnt);
    }
    printf("Numbers Generated:\n<median: %d\n>=median: %d\n", minus_cnt, plus_cnt);
    return 0;
}