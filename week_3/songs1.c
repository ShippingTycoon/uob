#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int song;
    struct node *next;
};

int getnum(void);
int generate_num(struct node *playlist, int required);

int main(void)
{
    int i, required;
    struct node playlist = {0, NULL}, *songs, *tmp;
    srand(time(NULL));
    /* Get input from user */
    required = getnum();
    songs = &playlist;
    for(i=0; i<required; i++){
        songs->song = generate_num(&playlist, required);
        songs->next = malloc(sizeof(struct node));
        songs = songs->next;
        songs->next = NULL;
        songs->song = 0;
    }
    printf("\n");
    songs = &playlist;
    for(i=0; i<required; i++){
        printf("%d ", songs->song);
        songs = songs->next;
    }
    printf("\n");
    songs = &playlist;
    songs = songs->next;
    for(i=0; i<required; i++){
        tmp = songs;
        songs = songs->next;
        free(tmp);
    }
    return 0;
}

int getnum(void)
{
    int num;
    printf("How many songs required? ");
    if(scanf("%d", &num) == 1){
        return num;
    }
    else{
        return 0;
    } 
}

int generate_num(struct node *playlist, int required)
{
    bool unique = false;
    int num = 0;
    struct node *tmp = NULL;
    num = (rand() % required + 1) + 1;

    while(unique == false){
        
        /* Go to the start of the playlist */
        tmp = playlist;

        /* Check its not already in list */
        unique = true;

        /* While the current list item is not the final one */
        while(tmp->next != NULL){
            if(tmp->song == num){
                /* The number generated is not unique */
                unique = false;
                num = (rand() % required + 1);
            }
            else{
                /* Go to next item */
                tmp = tmp->next;
            }
        }
    }
    /* Return random number */
    return num;
}

