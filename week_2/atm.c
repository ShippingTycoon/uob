#include <stdio.h>
#include <stdbool.h>

bool checkAmount(int amount);
void offerAlternate( int amount);

int main(void)
{
    int amount;
    bool isTwenty;
    /* Prompt user for amount */
    printf("How much money would you like? ");
    if (scanf("%d", &amount) == 1){
        assert(amount > 0);
        /* Check it's a multiple of 20 */
        isTwenty = checkAmount(amount);
    }
    /* Offer alternatives */
    if (isTwenty == false){
        offerAlternate(amount);
    }
    else if (isTwenty == true){
        /* Dispense */
        printf("OK, dispensing...\n");
    }
    return 0;
}

bool checkAmount(int amount)
{
    if (amount%20 == 0){
        return true;
    }
    return false;
}

void offerAlternate( int amount)
{
    int distDown = amount %20;
    int distUp = 20 - distDown;
    int offer1 = amount - distDown;
    int offer2 = amount + distUp;
    printf("\nI can give you %d or %d, try again. \n", 
            offer1, offer2);
    main();
}