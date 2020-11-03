#include <stdio.h>
#include <assert.h>
#include <math.h>

#define ARRAY_SIZE 50
#define INITIAL_ARRAY 3
#define BINARY_BASE 2

enum start_options {rand_start, single_on};
typedef enum start_options start_options;

void test(void);
int random_array_item(void);
int gen_arr_item(int a, int b, int c);

int main(void)
{
    int i, next_item;
    start_options user_choice = rand_start;
    int arr[ARRAY_SIZE] = {0};

    test();

    /* Populate initial array */
    switch(user_choice){
        case rand_start:
            for(i=0; i<INITIAL_ARRAY; i++){
                arr[i] = random_array_item();
            }
        case single_on:
            arr[1] = 1;
    }


    for(i=0; i<(ARRAY_SIZE - INITIAL_ARRAY); i++){
        for(j=0; j<ARRAY_SIZE; j++){
            printf("%d", arr[j]);
        }
        printf("\n");
        next_item = gen_arr_item(arr[i], arr[i+1], arr[i+2]);
        arr[i+3] = next_item;
    }
    return 0;
}

void test(void)
{
    assert(random_array_item() >= 0 && 
    random_array_item() <= 1);
}

int random_array_item(void)
{
    return rand() % (INITIAL_ARRAY - 1);
}

int gen_arr_item(int a, int b, int c)
{
    int sum = 0;
    sum += a;
    sum += b*BINARY_BASE;
    sum += c*(pow(BINARY_BASE, 2));
    return sum;
}