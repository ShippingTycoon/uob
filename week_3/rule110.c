#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ARRAY_SIZE 50
#define INITIAL_ARRAY 3
#define BINARY_BASE 2.0
#define EMPTY -1

enum start_options {rand_start, single_on};
typedef enum start_options start_options;

start_options get_choice(void);
void random_array(int arr[]);
void single_on_array(int arr[]);
void rule110(int arr[]);

int main(void)
{
    /* Give the user the option to start with either
    a randomised first line, or a line with a single
    'on' int he central location */
    int i;
    /* Initialise array */
    int arr[ARRAY_SIZE] = {-1};
    start_options user_choice;
    srand(time(NULL));

    user_choice = get_choice();
    switch(user_choice){
        case rand_start:
            random_array(arr);
            break;
        case single_on:
            single_on_array(arr);
            break;
        default:
            printf("User choice error.\n");
            exit(1);
    }

    for(i=0; i<10; i++){
        rule110(arr);
        printf("\n");
    }
    return 0;
}

start_options get_choice(void)
{
    char choice;
    printf("Type \"r\" for random first line, or \"1\"\n"
    "to start with a single 'on' in the middle.\n");
    if(scanf("%c", &choice) != 1){
        exit(1);
    }
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

void random_array(int arr[])
{
    int i;
    for(i=0; i<INITIAL_ARRAY; i++){
        arr[i] = (rand() % (INITIAL_ARRAY - 1));
    }
}

void single_on_array(int arr[])
{
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 0;
}

void rule110(int arr[])
{
    int i, j, sum = 0;
    /* Convert array into binary */
    for(i=0; i<ARRAY_SIZE; i++){
        sum += pow(BINARY_BASE, (double)i) * arr[i];
        printf("%d", arr[i]);
    }
    printf("\n");
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
