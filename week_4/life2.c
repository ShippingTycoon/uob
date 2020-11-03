#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define WIDE 15
#define TALL 9
#define XYSTART 1
#define RNUMSTART 1
#define FLINESIZE 10
#define XY 2
#define LIVE 1
#define DEATH 0
#define LIVEC '@'
#define DEATHC ' '
#define X 0
#define Y 1
#define NUMCOORDINATES 5
#define MAXRULES 3
#define MAXNUMS 10
#define NORULE 12
#define RBIRTH 9
#define RSURVIVAL 10
#define RDEATH 11

/* Open file and take info into string array */
int load(const char *infile, 
char buffer[WIDE*TALL][FLINESIZE]);

/* Parse strings into int coordinates */
void to_xy(char buffer[WIDE*TALL][FLINESIZE], 
int xy[WIDE*TALL][XY], int len);

/* Fills in board with start coordinates from file */
void setup_board(int xy[WIDE*TALL][XY], 
int board[TALL][WIDE], int len);

/* Assigns all vlas in array to special value NORULE */
void setup_rule(int rule[MAXRULES][MAXNUMS]);

/* Assigns all vals in array to special valie '\0' */
void setup_rulesp(char rulesp[MAXRULES][MAXNUMS]);

/* Parse string of rules into individual rules array */
void parse_rules(char* rules, char rulesp[MAXRULES][MAXNUMS]);

/* Parse stirngs into int array of rules */
void format_rules(char rulesp[MAXRULES][MAXNUMS], 
int rule[MAXRULES][MAXNUMS]);

/* Iterate through array and change values accordingly */
void life(int board[TALL][WIDE], int rule[MAXRULES][MAXNUMS]);

/* Check individual cells agains rules */
int check_cell(int cnt, int cell, int rule[MAXRULES][MAXNUMS]);

/* Assign all vals in tmp array to 0 */
void zero_tmp(int tmp[TALL][WIDE]);

/* Convert int value of cell into printable char */
char tochar(int a);

void test(void);

int main(int argc, char **argv)
{
    char buffer[WIDE*TALL][FLINESIZE] = {0};
    int xy[WIDE*TALL][XY];
    int board[TALL][WIDE] = {0};
    int rule[MAXRULES][MAXNUMS];
    char rulesp[MAXRULES][MAXNUMS];
    int len, i, j, k;
    setup_rule(rule);
    setup_rulesp(rulesp);
    if(argc == 3){
        char* rules = argv[1];
        char* infile = argv[2];
        test();
        parse_rules(rules, rulesp);
        format_rules(rulesp, rule);
        len = load(infile, buffer);
        to_xy(buffer, xy, len);
        setup_board(xy, board, len);
        for(i=0; i<10; i++){
            for(j=0; j<TALL; j++){
                for(k=0; k<WIDE; k++){
                    printf("%c", tochar(board[j][k]));
                }
                printf("\n");
            }
            printf("\n");
            life(board, rule);
        }
    }
    else{
        printf("Usage: life file.lif #\n");
    }
    neillclrscrn();
    return 0;
}

void setup_rule(int rule[MAXRULES][MAXNUMS])
{
    int i, j;
    for(i=0; i<MAXRULES; i++){
        for(j=0; j<MAXNUMS; j++){
            rule[i][j] = NORULE;
        }
    }
}

void setup_rulesp(char rulesp[MAXRULES][MAXNUMS])
{
    int i, j;
    for(i=0; i<MAXRULES; i++){
        for(j=0; j<MAXNUMS; j++){
            rulesp[i][j] = '\0';
        }
    }
}

void parse_rules(char* rules, char rulesp[MAXRULES][MAXNUMS])
{
    int k;
    int i=0;
    int j=0;
    int cnt;
    do{
        k=0;
        do{
            rulesp[i][k++] = rules[j++];
        }while(rules[j] != '/' && rules[j] != '\0');
        i++;
        if(rules[j] == '/'){
            j++;
        }
    }while(i<MAXRULES && rules[j] !='\0');
    cnt = i+1;
}

void format_rules(char rulesp[MAXRULES][MAXNUMS], 
int rule[MAXRULES][MAXNUMS])
{
    int i, j;
    for(i=0; i<MAXRULES; i++){
        switch(rulesp[i][0]){
            case 'B':
                rule[i][0] = RBIRTH;
                break;
            case 'S':
                rule[i][0] = RSURVIVAL;
                break;
            case 'D':
                rule[i][0] = RDEATH;
                break;
        }
        for(j=RNUMSTART; j<MAXNUMS && rulesp[i][j] != '\0'; 
        j++){
            sscanf(&rulesp[i][j], "%1d", &rule[i][j]);
        }
    }

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

void life(int board[TALL][WIDE], int rule[MAXRULES][MAXNUMS])
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
            tmp[i][j] = check_cell(cnt, board[i][j], rule);
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

int check_cell(int cnt, int cell, int rule[MAXRULES][MAXNUMS])
{
    int i, j;
    for(i=0; i<MAXRULES; i++){
        switch(rule[i][0]){
            case RBIRTH:
                for(j=RNUMSTART; j<MAXNUMS; j++){
                    if(cnt == rule[i][j] && cell == DEATH){
                        return LIVE;
                    }
                }
                if(cell==DEATH){
                    return DEATH;
                }
                break;
            case RSURVIVAL:
                for(j=RNUMSTART; j<MAXNUMS; j++){
                    if(cnt == rule[i][j] && cell == LIVE){
                        return LIVE;
                    }
                }
                if(cell == LIVE){
                    return DEATH;
                }
                break;
            case RDEATH:
                for(j=RNUMSTART; j<MAXNUMS; j++){
                    if(cnt == rule[i][j] && cell == LIVE){
                        return DEATH;
                    }
                }
                if(cell == LIVE){
                    return DEATH;
                }
                break;
            default:
                return DEATH;
        }
    }
    return DEATH;
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
    int trule[MAXRULES][MAXNUMS];
    char trulesp[MAXRULES][MAXNUMS];
    char* trules = "B32/S45/D16";
    char* trules2 = "B012345678/S012345678/D012345678";
    char* trules3 = "B32";
    int i, j;

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
    setup_rule(trule);
    for(i=0; i<MAXRULES; i++){
        for(j=0; j<MAXNUMS; j++){
            assert(trule[i][j] == NORULE);
        }
    }
    setup_rulesp(trulesp);
    for(i=0; i<MAXRULES; i++){
        for(j=0; j<MAXNUMS; j++){
            assert(trulesp[i][j] == '\0');
        }
    }
    parse_rules(trules, trulesp);
    /*for(i=0; i<MAXRULES; i++){
        for(j=0; j<MAXNUMS; j++){
            printf("%c", trulesp[i][j]);
        }
        printf("\n");
    }*/
    assert(trulesp[0][0] == 'B');
    assert(trulesp[0][1] == '3');
    assert(trulesp[0][3] == '\0');
    assert(trulesp[2][0] == 'D');
    parse_rules(trules2, trulesp);
    assert(trulesp[0][9] == '8');
    assert(trulesp[2][9] == '8');
    assert(trulesp[2][0] == 'D');
    format_rules(trulesp, trule);
    /*for(i=0; i<MAXRULES; i++){
        for(j=1; j<MAXNUMS; j++){
            printf("%d ", trule[i][j]);
        }
        printf("\n");
    }*/
    assert(trule[0][0] == RBIRTH);
    assert(trule[0][9] == 8);
    assert(trule[2][9] == 8);
    assert(trule[1][0] == RSURVIVAL);
    assert(trule[1][1] == 0);
    setup_rulesp(trulesp);
    parse_rules(trules, trulesp);
    setup_rule(trule);
    format_rules(trulesp, trule);
    assert(check_cell(3, DEATH, trule) == LIVE);
    assert(check_cell(1, LIVE, trule) == DEATH);
    setup_rulesp(trulesp);
    parse_rules(trules3, trulesp);
    setup_rule(trule);
    format_rules(trulesp, trule);
    life(tboard, trule);
    assert(tboard[(TALL/2)+1][(WIDE/2)+2] == LIVE);
}
