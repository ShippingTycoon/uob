#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

int scode(int a);

int main(void)
{
    char text[250] = {0}, code[250] = {0}, c;
    int i = 0;
    while (scanf("%c", &text[i]) && text[i] != '\n'){
        i++;
    }
    i = 0;
    while (text[i]){
        code[i] = scode(text[i]);
        i++;
    }
    code[i] = '\0';

    i = 0;
    while (code[i] != '\0'){
        printf("%c", code[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int scode(int a)
{
    char code;
    if (isalpha(a) == 0){
        return a;
    }
    else if (isupper(a)){        
        code = 'Z' - (a -='A');
    }
    else{
        code = 'z' - (a -='a');
    }
    return code;
}