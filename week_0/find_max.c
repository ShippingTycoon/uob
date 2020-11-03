#include <stdio.h>

int main(void)
{
    int num;
    double max;

    printf("How many numbers do you wish to enter? ");
    if (scanf("%d", &num) != 1){
        printf("Usage: Enter integer value and press enter.\n");
        return 0;
    }

    double numbers[num];
    
    printf("Enter %d real numbers:", num);
    for (int i = 0; i < num; i++){
        scanf("%lf", &numbers[i]);
    }

    max = numbers[0];

    for (int i = 1; i < num; i++){
        if (numbers[i] > numbers[i-1]){
            max = numbers[i];
        }
    }

    printf("Maximum value: %lf\n", max);

    return 0;
}