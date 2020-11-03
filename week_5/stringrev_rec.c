#include <stdio.h>
#include <string.h>

#define SWAP(A,B) {char temp; temp=A;A=B;B=temp;}

void Reverse_String(char* s,int start, int end);

int main()
{
    char str[] = "Hello World!";

    Reverse_String(str, 0, strlen(str)-1);
    printf("%s\n", str);
}

/* RECURSIVE: Inplace String Reverse */
void Reverse_String(char* s,int start, int end)
{
    if(start >= end){
        return;
    }
    SWAP(s[start], s[end]);
    Reverse_String(s, start+1, end-1);
}
