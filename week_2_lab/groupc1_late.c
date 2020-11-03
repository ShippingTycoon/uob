#include <stdio.h>
#include <math.h>
#include <assert.h>

#define ALPHNUM 26

int Isprime(int x);
int Isvowel(char c);
void test(void);

enum check{false, true};
typedef enum check true_false;


int main(void)
{
 int i=0, x, y, sum;
 char c1, c2;

 for (x=0;x<ALPHNUM;x++){
   for (y=0; y<ALPHNUM; y++){
         sum = (x+1)+(y+1)+(x+1);
         if(Isprime(sum)==true){
           c1 = 'a'+x; /*ASCII value*/
           c2 = 'a'+y;
           if(Isvowel(c1)+Isvowel(c2)==true){
             i++;
             printf("%d %c%c%c\n",i, c1, c2, c1);
           }
         }
       }
   }
 return 0;
}




int Isprime(int x)
{
 int i;
 for (i=2; i<=x/2; i++){
   if (x%i==0){
     return false;
   }
 }
return true;
}



int Isvowel(char c)
{
 if (c == 'a' || c =='e' || c=='i' || c=='o' || c=='u') {
   return true;
 }
 return false;
}

void test(void)
{
   assert(Isvowel('a')==1);
}
