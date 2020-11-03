#include <stdio.h>

int main(void)
{
    int sum = 0, val;
    FILE *ifp, *ofp;

    /* Read a File */
    ifp = fopen("my_file", "r");
    /* Write to a file */
    ofp = fopen("outfile", "w");
    /* If file not readable, returns NULL */
    if (fp == NULL){
        exit(1);
    }
    /*
    .
    .
    .
    .
    */
    fclose(ifp);
    fclose(ofp);
}

/* Files are always read as a string
r = read
w = write
a = append 
rb = read binary file
wb = write binary file
ad = append binary file
*/
