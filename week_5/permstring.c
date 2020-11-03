#include <stdio.h>
#include <string.h>

void swap(char* x, char*y);
void permute(char* a, int f, int rt);

int main(void)
{
    char str[] = "ABCD";
    int n = strlen(str);
    permute(str, 0, n-1);
    return 0;
}

void permute(char* s, int f, int rt)
{
    int i;
    if(f==rt){
        printf("%s\n", s);
    }
    else{
        for(i=f; i<=rt; i++){
            swap(&s[f], &s[i]);
            permute(s, f+1, rt);
            swap(&s[f], &s[i]); /* Backtrack */
        }
    }
}

void swap(char* x, char*y)
{
    char tmp;
    tmp = *x;
    *x=*y;
    *y=tmp;
}
