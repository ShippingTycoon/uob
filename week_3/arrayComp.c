#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int getnum(void);
bool check_array(arr[]);

int main(void)
{
    int arr[10] = {0};
    int i, n, j;
    bool noMatch = false;

    while((noMatch = check_array(arr)) == false){

    }
    

    for(i=0; i<10; i++){
        while(noMatch == false){
            n = getnum();
            noMatch = true;
            for(j=0; j<10; j++){
                if(arr[j] == n){
                    noMatch = false;
                }
            }
            printf("%d %d\n", arr[j], n);
        }
        arr[i] = n;
        printf("%d", n);

    }
    printf("\n");
    return 0;
}

int getnum(void)
{
    return rand() % 10;
}

bool check_array(arr[])
{

}