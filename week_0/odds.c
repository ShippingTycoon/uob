#include <stdio.h>

int main(void)
{
    int num, max;
    
    printf("This program will only process odd integers.\n"
    "How many numbers do you wish to enter? ");
    if (scanf("%d", &num) != 1){
        printf("Usage: Enter integer value and press enter.\n");
        return 0;
    }

    int numbers[num], num_check;
    
    printf("Enter %d integers:", num);
    for (int i = 0; i < num; i++){
        scanf("%d", &numbers[i]);
    }

    if (numbers[0] % 2 == 0){
        numbers[0] = 0;
    }
    else{
        max = numbers[0];
    }

    for (int i = 1; i < num; i++){
        if (numbers[i] > numbers[i-1] && numbers[i] % 2 != 0){
            max = numbers[i];
        }
    }

    printf("Maximum value: %d\n", max);

    return 0;
}