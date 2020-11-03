#include <stdio.h>
#include <string.h>
#include <assert.h>

/* enum numeral {I=1, V=5, X=10, L=50, C=100, D=500, M=1000};
typedef enum numeral numeral; */

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

void test(void);
int romanToArabic(char *roman);
int check_previous(char roman[], int i);

int main(int argc, char **argv)
{
    test();

    if(argc==2){
        printf("The roman numberal %s is equal to %d\n",
        argv[1], romanToArabic(argv[1]));
    }
    else{
        printf("ERROR: Incorrect usage, try e.g. %sXXI\n",
        argv[0]);
    }
    return 0;
}

void test(void)
{
    char tstring[256] = {'V', '\0'};
    assert(romanToArabic(tstring) == 5);
}

int romanToArabic(char *roman)
{
    
}