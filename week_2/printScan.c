#include <stdio.h>

int main(void)
{
    FILE *fp;

    if ((fp = fopen("file.txt", "w")) == NULL){
        printf("Cannot open file\n");
        return 1;
    }
    /* Creates a file called file.txt with the string
    "Hello World" in it */
    fprintf(fp, "Hello World\n");
    fclose(fp);

    return 0;
}

/* Function definitions:
int fprintf(FILE*stream, format, other args);
int fscanf(FILE*stream, format, other args);
*/