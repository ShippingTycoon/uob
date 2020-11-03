#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEQOFALPHA (96*3)

enum bool {true, false};
typedef enum bool bool;

bool isvowel(char c);
bool isprime(int number);

int main(void)
{
    int cnt;
    int n1='a', n2, n3;

    for(cnt=0;n1<='z';n1++){
        for(n2='a';n2<='z';n2++){
	    if (isvowel(n1) == true && isvowel(n2) == false){
		n3 = n1;
	        if (isprime(n1+n2+n3) == true){
		    cnt++;
		    printf("%3d %c%c%c %3d\n",cnt, n1,n2, n3);
		}
	    }
	    if (isvowel(n1) == false && isvowel(n2) == true){
                n3 = n1;
                if (isprime(n1+n2+n3) == true){
                    cnt++;
                    printf("%3d %c%c%c %3d\n",cnt, n1,n2, n3);
                }
            }
	}
    }
    return 0;	    
}

bool isvowel(char c)
{
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
	return true;
    }
    else{
	return false;
    }
}

bool isprime(int number)
{
    int i;
    
    number = number - SEQOFALPHA;
    for (i=2;i<=sqrt(number);i++){
	 if (number % i == 0){
             return false;
	 }
    }
    return true;
}
