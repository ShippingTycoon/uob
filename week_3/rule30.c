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
int rule30(int a, int b, int c);

int main(void)
{
    int h, i, j, k;
    start_options user_choice = single_on;
    int arr1[ARRAY_SIZE] = {0};
    int arr2[ARRAY_SIZE] = {0};

    test();

    user_choice = get_choice();

    /* Populate initial array */
    switch(user_choice){
        case rand_start:
            for(i=HALF_ARRAY-1; i<HALF_ARRAY+1; i++){
                arr1[i] = random_array_item();
            }
            break;
        case single_on:
            /* Sets array to {0, 1, 0} */
            arr1[HALF_ARRAY] = 1;
            break;
    }

    for(h=0; h<12; h++){
        /* Print arr1 */
        for(j=0; j<ARRAY_SIZE; j++){
            printf("%d", arr1[j]);
        }
        printf("\n");
        /* Populate arr2 */
        for(i=HALF_ARRAY, k = HALF_ARRAY-1; 
        i<(ARRAY_SIZE - 1) && k>0; i++, k--){
            arr2[i] = rule30(arr1[i-1], arr1[i], arr1[i+1]);
            arr2[k] = rule30(arr1[k-1], arr1[k], arr1[k+1]);
        }
        /* Print arr2 */
        for(j=0; j<ARRAY_SIZE; j++){
            printf("%d", arr2[j]);
        }
        printf("\n");
        /* Populate arr1 */
        for(i=HALF_ARRAY, k = HALF_ARRAY-1; 
        i<(ARRAY_SIZE - 1) && k>0; i++, k--){
            arr1[i] = rule30(arr2[i-1], arr2[i], arr2[i+1]);
            arr1[k] = rule30(arr2[k-1], arr2[k], arr2[k+1]);
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
    assert(random_array_item() >= 0 && 
    random_array_item() <= 1);
    assert(rule30(1, 1, 1) == 0);
    assert(rule30(1, 1, 0) == 0);
    assert(rule30(1, 0, 0) == 1);
    assert(rule30(0, 0, 0) == 0);
}

int random_array_item(void)
{
    return rand() % BINARY_BASE;
}



int rule30(int c, int b, int a)
{
    int binary_sum = 0;
    binary_sum += a;
    binary_sum += b*BINARY_BASE;
    binary_sum += c*(pow(BINARY_BASE, 2));
    if(binary_sum == 3 || binary_sum == 4 || 
    binary_sum == 2 || binary_sum == 1){
        /* The next item is 1 */
        return 1;
    }
    else if(binary_sum > 7 || binary_sum < 0){
        printf("Something went wrong.");
        exit(1);
    }
    else{
        /* The next item is 0 */
        return 0;
    }
}