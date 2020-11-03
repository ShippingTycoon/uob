#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int getnum(void);
bool checkNum(int *p, int n, int required);

int main(void)
{
    int i, required, n;
    int *p;
    bool checked = false;
    /* Get input from user */
    required = getnum();
    
    p = (int *)malloc(sizeof(int)*required);
    for(i=0; i<required; i++){
        p[i] = 0;
    }

    for(i=0; i<required; i++){
        while(checked == false){
            n = rand() % required;
            
            checked = checkNum(p, n, required);
        }
        checked = false;
        p[i] = n;
    }
    

    for(i=0; i<required; i++){
        printf("%d ", p[i]);
    }
    printf("\n");
    free(p);
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

bool checkNum(int *p, int n, int required)
{
    int i = 0;
    for(i=0; i<required; i++){
        if(p[i] == n){
            printf("%d %d\n", p[i], n);
            return false;
        }
    }

    return true;
    
}