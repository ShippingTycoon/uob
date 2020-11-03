#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ARRAY_SIZE 3
#define BINARY_BASE 2.0

enum start_options {rand_start, single_on};
typedef enum start_options start_options;

start_options get_choice(char choice);
int random_array(void);
void rule110(int arr[]);

int main(void)
{
    int i;
    char choice;
    /* Initialise array */
    int arr[ARRAY_SIZE] = {0};
    start_options user_choice;
    srand(time(NULL));

    if(scanf("%c", &choice) != 1){
        exit(1);
    }

    user_choice = get_choice(choice);
    switch(user_choice){
        case rand_start:
            for(i=0; i<ARRAY_SIZE; i++){
                arr[i] = random_array();
            }
            break;
        case single_on:
            arr[0] = 0;
            arr[1] = 1;
            arr[2] = 0;
            break;
        default:
            printf("User choice error.\n");
            exit(1);
    }

    for(i=0; i<10; i++){
        rule110(arr);
    }
    return 0;
}

start_options get_choice(char choice)
{
    switch(choice){
        case'r':
            return rand_start;
            break;
        case'1':
            return single_on;
            break;
        default:
            printf("Incorrect user input.\n");
            exit(1);
    }
}

int random_array(void)
{
    return (rand() % (ARRAY_SIZE - 1));
}

void rule110(int arr[])
{
    int i, sum = 0;
    double bin_base = BINARY_BASE;
    /* Convert array into binary */
    for(i=0; i<ARRAY_SIZE; i++){
        sum += pow(bin_base, (double)i) * arr[i];
        printf("%d", arr[i]);
    }
    printf(" %d \n", sum);
    arr[0] = arr[1];
    arr[1] = arr[2];
    if((int)sum == 7 || (int)sum == 4 || (int)sum == 0){
        /* The next item is 0 */
        arr[2] = 0;
    }
    else{
        /* The next item is 1 */
        arr[2] = 1;
    }
}
/*
        to_decimal = 2;
        for(j=0; j<arr[i]; j++){
            to_decimal *= to_decimal;
        }
        */
