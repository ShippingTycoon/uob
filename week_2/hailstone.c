#include <stdio.h>
#include <ctype.h>

struct record {
    int seed;
    int result;
};

int hailstone(int num);
struct record findLongest(void);
struct record findLargest(void);

int main(void)
{
    /* Find longest hailstone number with seed < 50,000 */
    struct record longest = findLongest();
    printf("The seed to find the longest sequence is %d.\n",
    longest.seed);
    printf("Which had a total of %d numbers in it.\n\n", 
    longest.result);

    /* Find sequence with largest number with seed < 50,000 */
    struct record largest = findLargest();
    printf("The seed to find the sequence with the largest"
           "number is: %d\n", largest.seed);
    printf("Which had a largest number of: %d\n", largest.result);
    return 0;
}

/* Number is halved if even 
and if odd the next becomes 3*n+1 */
int hailstone(int num)
{
    if (num%2 == 0){
        return num/2;
    }
    else{
        return 3*num+1;
    }
}

struct record findLongest(void)
{
    struct record longest = {0, 0};
    int i, tmp;
    i = 1;
    while (i<50000){
        int counter = 1;
        tmp = i;
        do{
            tmp = hailstone(tmp);
            counter++;
        }while (tmp != 1);
        if (counter > longest.result){
            longest.result = counter;
            longest.seed = i;
        }
        i++;
    }
    return longest;
}

struct record findLargest(void)
{
    struct record largest = {0, 0};
    int i = 1;
    while (i<50000){
        int tmp = i;
        do{
            tmp = hailstone(tmp);
            if (tmp > largest.result){
                largest.result = tmp;
                largest.seed = i;
            }
        }while (tmp != 1);
        i++;
    }
    return largest;
}