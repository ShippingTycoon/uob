#include <stdio.h>
#include <stdlib.h>

int getnum(void);
void pop_arr(int arr[], int required);
void shuffle(int arr[], int size);

int main(void)
{
    int arr[50] = {0};
    int required, i;

    required = getnum();

    pop_arr(arr, required);

    shuffle(arr, required);

    for(i=0; i<required; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int getnum(void)
{
    int num;
    printf("How many songs required? ");
    if(scanf("%d", &num) == 1){
        return num;
    }
    else{
        return 0;
    } 
}

void pop_arr(int arr[], int required)
{
    int i;
    for(i=0; i<required; i++){
        arr[i] = (i+1);
    }
}

void shuffle(int arr[], int size)
{
    int i, j, tmp;
    if(size>1){
        for(i=0; i<size-1; i++){
            j = i + rand() % (size - i);
            tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
        }
    }
}