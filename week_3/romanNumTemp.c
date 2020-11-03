#include <stdio.h>
#include <string.h>

/* enum numeral {I=1, V=5, X=10, L=50, C=100, D=500, M=1000};
typedef enum numeral numeral; */

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

int romanToArabic(char *roman);
int check_previous(char roman[], int i);

int main(int argc, char **argv)
{
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

int romanToArabic(char *roman)
{
    int i, sum = 0;
    int length = strlen(roman);
    printf("\n%d\n", length);
    for(i=0; i<length; i++){
        switch(roman[i]){
            case 'I':
                sum+=I;
                break;
            case 'V':
                sum -= check_previous(roman, i);
                sum+=V;
                break;  
            case 'X':
                sum -= check_previous(roman, i);
                sum+=X;
                break;
            case 'L':
                sum -= check_previous(roman, i);
                sum+=L;
                break;
            case 'C':
                sum -= check_previous(roman, i);
                sum+=C;
                break;
            case 'D':
                sum -= check_previous(roman, i);
                sum+=D;
                break;
            case 'M':
                sum -= check_previous(roman, i);
                sum+=1000;
                break;
            default:
                printf("Something went wrong");
        }
    }
    return sum;
}

int check_previous(char roman[], int i)
{
    int j = i-1;
    if(roman[j] == 'C'){
        return 100;
    }
    switch(roman[j]){
        case 'I':
            return 1;
        case 'X':
            return 10;
        case 'C':
            return 100;
    }
    return 0;
}