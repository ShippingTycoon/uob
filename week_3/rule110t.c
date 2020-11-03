#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define ARRAY_SIZE 50
#define INITIAL_ARRAY 3
#define BINARY_BASE 2
#define HALF_ARRAY 25

enum start_options {rand_start, single_on};
typedef enum start_options start_options;

void test(void);
start_options get_choice(void);
int random_array_item(void);
int rule110(int a, int b, int c);

int main(void)
{
    int h, i, j, next_item;
    start_options user_choice = single_on;
    int arr1[ARRAY_SIZE] = {0};
    int arr2[ARRAY_SIZE] = {0};

    test();

    /* take input and then make function to return easier to read user choice */
    user_choice = get_choice();

    /* Populate initial array */
    switch(user_choice){
        case rand_start:
            for(i=0; i<INITIAL_ARRAY; i++){
                arr1[i] = random_array_item();
            }
            break;
        case single_on:
            /* Sets array to {0, 1, 0} */
            arr1[1] = 1;
            break;
    }

    for(h=0; h<HALF_ARRAY; h++){
        /* Print arr1 */
        for(j=0; j<ARRAY_SIZE; j++){
            printf("%d", arr1[j]);
        }
        printf("\n");
        /* Populate arr2 */
        for(i=0; i<(ARRAY_SIZE - 2); i++){
            arr2[i+1] = rule110(arr1[i], arr1[i+1], arr1[i+2]);
        }
        /* Print arr2 */
        for(j=0; j<ARRAY_SIZE; j++){
            printf("%d", arr2[j]);
        }
        printf("\n");
        /* Populate arr1 */
        for(i=0; i<(ARRAY_SIZE - 2); i++){
            arr1[i+1] = rule110(arr2[i], arr2[i+1], arr2[i+2]);
        }
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

void test(void)
{
    assert(random_array_item() == 0 || 
    random_array_item() == 1);
    assert(rule110(1, 1, 1) == 0);
    assert(rule110(1, 1, 0) == 1);
    assert(rule110(1, 0, 0) == 0);
    assert(rule110(0, 0, 0) == 0);
}

int random_array_item(void)
{
    return rand() % (INITIAL_ARRAY - 1);
}



int rule110(int a, int b, int c)
{
    int binary_sum = 0;
    binary_sum += a;
    binary_sum += b*BINARY_BASE;
    binary_sum += c*(pow(BINARY_BASE, 2));
    if(binary_sum == 7 || binary_sum == 4 || binary_sum == 0){
        /* The next item is 0 */
        return 0;
    }
    else if(binary_sum > 7 || binary_sum < 0){
        printf("Something went wrong.");
        exit(1);
    }
    else{
        /* The next item is 1 */
        return 1;
    }
}