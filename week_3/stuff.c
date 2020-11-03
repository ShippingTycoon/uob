int generate_num(struct node *playlist, int required)
{
 bool unique = false;
 int num = 0;
 struct node *tmp = NULL;
 num = rand() % required;
 while(num == 0){
 num = rand() % required + 1;
 }
 
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
        num = rand() % required;
        while(num == 0){
            num = rand() % required + 1;
        }
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