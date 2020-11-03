#include <stdio.h>

int main(void)
{
    FILE *fp;
    int i;
    char arr[6];

    if ((fp = fopen("doof", "rb")) == NULL){
        printf("Cannot open file\n");
        return 1;
    }
    /* fread(void*ptr, size, num_items, stream); */
    /* fwrite(void*ptr, size, num_items, stream); */
    /* both return an unsigned int, the number of elements
    correctly read or written */
    /* Use of sizeof function! */
    /*    ptr,   size,   num_items, stream */
    fread(arr, sizeof(char), 5, fp);

    for(i=0; i<5; i++){
        printf("Characeter %d was %d\n", i, arr[i]);
    }
    fclose(fp);

    return 0;
}