#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

enum scale {celsius, farenheit};
typedef enum scale scale;

enum fever {noFever, hasFever};
typedef enum fever fever;

typedef double temperature;

double farenheit2celcius(double temp);

int fvr(double temp, scale s);

#define FEVER_THRESHOLD 37.5

int main(void)
{
   assert(farenheit2celcius(32.0)==0);
   assert(fvr(37.5, celsius)==hasFever);
   assert(fvr(36.5, celsius)==noFever);
   assert(fvr(96.5, farenheit)==noFever);
   assert(fvr(99.5, farenheit)==hasFever);

   return 0;
}

/* wiki definition for farenheit to celcius conversion */
temperature farenheit2celcius(temperature t)
{
    return ((t-32.0)*5.0/9.0);
}


int fvr(temperature t, scale s)
{
   /* In Farenheit, convert to Celcius */
   if(s==farenheit){
       t = farenheit2celcius(t);
   }
   if(t >= FEVER_THRESHOLD){
       return hasFever;
   }
   return noFever;
}