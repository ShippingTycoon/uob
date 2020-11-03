#include <stdio.h>
#include <stdlib.h>

#define MAXFILENAME 128

int main(void)
{
    FILE *ifp, *ofp;
    char inpname[MAXFILENAME];
    char oupname[MAXFILENAME];
    int i;

    printf("Enter two filenames: ");
    if (scanf("%s %s", inpname, oupname) != 2){
        printf("Failed to scan two filenames.");
        exit(1);
    }
    ifp = fopen(inpname, "rb");
    ofp = fopen(oupname, "wb");
    if (ifp == NULL || ofp == NULL){
        printf("Failed to open two filenames.");
        exit(1);
    }
    while ((i = getc(ifp)) != EOF){
        /* Check putc documentation 
        Checked - putc writes to variable and does not
        print to terminal */
        putc(i, ofp);
    };

    fclose(ifp);
    fclose(ofp);

    return 0;
}