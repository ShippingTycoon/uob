#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define WIDE 15
#define TALL 9
#define XYSTART 1
#define FLINESIZE 10
#define XY 2
#define LIVE 1
#define DEATH 0
#define LIVEC '@'
#define DEATHC ' '
#define X 0
#define Y 1
#define NUMCOORDINATES 5

int load(const char *infile, 
char buffer[WIDE*TALL][FLINESIZE]);

void to_xy(char buffer[WIDE*TALL][FLINESIZE], 
int xy[WIDE*TALL][XY], int len);

void setup_board(int xy[WIDE*TALL][XY], 
int board[TALL][WIDE], int len);

void life(int board[TALL][WIDE]);

int check_cell(int cnt, int cell);

void zero_tmp(int tmp[TALL][WIDE]);

char tochar(int a);

void test(void);

int main(int argc, char **argv)
{
    char buffer[WIDE*TALL][FLINESIZE] = {0};
    int xy[WIDE*TALL][XY];
    int board[TALL][WIDE] = {0};
    int len, i, j, k;
    if(argc == 3){
        char* infile = argv[1];
        int repeats = atoi(argv[2]);
        test();
        len = load(infile, buffer);
        to_xy(buffer, xy, len);
        setup_board(xy, board, len);
        for(i=0; i<repeats; i++){
            for(j=0; j<TALL; j++){
                for(k=0; k<WIDE; k++){
                    printf("%c", tochar(board[j][k]));
                }
                printf("\n");
            }
            printf("\n");
            life(board);
        }
    }
    else{
        printf("Usage: life file.lif #\n");
    }
    return 0;
}

int load(const char* infile, char buffer[WIDE*TALL][FLINESIZE])
{
    FILE *file;
    int i, j, c, len = 0;
    if((file = fopen(infile, "r")) == NULL){
        exit(EXIT_FAILURE);
    }
    /* Skip first line of file */
    do{
        c = fgetc(file);
    }while(c != EOF && c != '\n');
    i=0;
    do{
        j = 0;
        do{
            c = (buffer[i][j++] = fgetc(file));
        }while(c != EOF && c != '\n');
        len++;
        buffer[i++][j] = '\0';
    }while(c != EOF);
    buffer[i-1][j-1] = '\0';
    fclose(file);
    return len;
}


void to_xy(char buffer[WIDE*TALL][FLINESIZE], 
int xy[WIDE*TALL][XY], int len)
{
    int j;
    int i;
    char* token;
    /*https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c */
    for(i=0; i<len; i++){
        j=0;
        token = strtok(buffer[i], " ");
        while(token != NULL){
            xy[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
    }
}


void setup_board(int xy[WIDE*TALL][XY], 
int board[TALL][WIDE], int len)
{
    int i; 
    int posx, posy;
    for(i=0; i<len; i++){
        posx = (WIDE/2) + xy[i][X];
        posy = (TALL/2) + xy[i][Y];
        board[posy][posx] = LIVE;
    }
}

void life(int board[TALL][WIDE])
{
    /* Clean up this function */
    int i, j, k, l, cnt=0;
    int tmp[TALL][WIDE];
    zero_tmp(tmp);
    /* Iterate through the current board */
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            cnt=0;
            /* Check 8 cells around */
            for(k=i-1; k<=i+1; k++){
                for(l=j-1; l<=j+1; l++){
                    if(k<0 || k>=TALL || l<0 || l>=WIDE ||
                    (k==i && l==j)){
                        /* Skip */
                    }
                    else if(board[k][l] == LIVE){
                        cnt++;
                    }
                }
            }
            tmp[i][j] = check_cell(cnt, board[i][j]);
        }
    }
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            board[i][j] = tmp[i][j];
        }
    }
}

void zero_tmp(int tmp[TALL][WIDE])
{
    int i, j;
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            tmp[i][j]=0;
        }
    }
}

int check_cell(int cnt, int cell)
{
    if((cnt==3 || cnt==2) && cell==LIVE){
        return LIVE;
    }
    else if((cnt<2 || cnt>3) && cell==LIVE){
        return DEATH;
    }
    else if(cnt==3 && cell==DEATH){
        return LIVE;
    }
    else{
        return DEATH;
    }
}

char tochar(int a)
{
    if(a==LIVE){
        return LIVEC;
    }
    else{
        return DEATHC;
    }
}

void test(void)
{
    FILE* file;
    char tbuff[TALL*WIDE][FLINESIZE];
    int xyt[WIDE*TALL][XY];
    int len;
    int tboard[TALL][WIDE] = {0};
    if((file = fopen("file1.lif", "r")) == NULL){
        exit(EXIT_FAILURE);
    }
    assert(load("file1.lif", tbuff) == NUMCOORDINATES);
    len = load("file1.lif", tbuff);
    to_xy(tbuff, xyt, len);
    assert(xyt[0][0] == 0);
    assert(xyt[0][1] == -1);
    assert(xyt[4][0] == 1);
    assert(xyt[4][1] == 1);
    
    setup_board(xyt, tboard, len);
    assert(tboard[(TALL/2)+1][(WIDE/2)+1] == LIVE);
    assert(tboard[TALL/2][(WIDE/2)+1] == LIVE);
    assert(tboard[(TALL/2)+1][(WIDE/2)-1] == LIVE);
    assert(tboard[(TALL/2)+1][WIDE/2] == LIVE);
    assert(tboard[TALL/2-1][WIDE/2] == LIVE);
    /*for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            printf("%d", tboard[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/
}
