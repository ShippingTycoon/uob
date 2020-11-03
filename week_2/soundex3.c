#include <stdio.h>

#define SOUNDEXSIZE 3

int main(int argc, char **argv)
{
    int soundex[SOUNDEXSIZE] = {0};
    if(argc==2){
        /* Turn the array into the codex */
        /* First digit is the upper case first letter */
        printf("%c", toupper(argv[1][0]));
    }
    else{
        printf("ERROR: Incorrect usage.\n");
    }
    return 0;
}