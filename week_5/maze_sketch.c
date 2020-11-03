bool explore(int x, int y, char mz[YS][XS])
{
    /* If it's marked with a cross we have escaped*/
    if mz[y][x] is exit return true;

    Mark mz[y][x] so we dont return here

    /* If we can move in this direction it means we can escape from here */
    if we can go up:
        if(explore(x, y=1, mz)) return 1
    
    if we can go right:
        if(explore(x+1, y, mz)) return 1
    
    Do left & down in a similar manner

    return 0; /* Failed to find route */
}