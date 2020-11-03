#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDS 2892
#define MAXLEN 15

enum bool {false, true};
typedef enum bool bool;

struct dict{
    char word[MAXLEN];
    int id;
};

void test(void);
void init_used_id(int used_id[MAXWORDS]);
void init_anagrams(char anagrams[MAXLEN][MAXLEN]);
void load(struct dict dic[MAXWORDS]);
int check_dic(struct dict dic[MAXWORDS], struct dict item, 
int used_id[MAXWORDS], char anagrams[MAXLEN][MAXLEN]);
void append_a(char anagrams[MAXLEN][MAXLEN], char* word, 
int apos);
bool compare(char* word, char* dic_item, int len);
bool comp_id(int id, int used_id[MAXWORDS]);
void reset_ids(int used_id[MAXWORDS]);

int main(void)
{
    struct dict dic[MAXWORDS];
    int used_id[MAXWORDS] = {0};
    char anagrams[MAXLEN][MAXLEN];
    int i, j, num;
    test();
    load(dic);
    for(i=0; i<MAXWORDS-1; i++){
        init_anagrams(anagrams);
        num = check_dic(dic, dic[i], used_id, anagrams);
        if(num != 0){
            printf("%d ", num);
            for(j=0; j<num; j++){
                printf("%s ", anagrams[j]);
            }
            printf("\n");
        }
    }
    return 0;
}

void init_used_id(int used_id[MAXWORDS])
{
    int i;
    for(i=0; i<MAXWORDS; i++){
        used_id[i] = 0;
    }
}

void init_anagrams(char anagrams[MAXLEN][MAXLEN])
{
    int i, j;
    for(i=0; i<MAXLEN; i++){
        for(j=0; j<MAXLEN; j++){
            anagrams[i][j] = '\0';
        }
    }
}

void load(struct dict dic[MAXWORDS])
{
    FILE *file;
    int i, j, c;
    /*printf("load\n"); */
    if((file = fopen("34words.txt", "r")) == NULL){
        fprintf(stderr, "Couldn't load file\n");
        exit(EXIT_FAILURE);
    }
    i=0;
    do{
        j = 0;
        do{
            c = (dic[i].word[j++] = fgetc(file));
        }while(c != EOF && c != '\n' );
        dic[i].id = i+1;
        dic[i++].word[j-1] = '\0';
    }while(c != EOF);
    fclose(file);
}

int check_dic(struct dict dic[MAXWORDS], struct dict item, 
int used_id[MAXWORDS], char anagrams[MAXLEN][MAXLEN])
{
    int i, apos = 0;
    bool anagram;
    int len = strlen(item.word);
    for(i=0; i<MAXWORDS-1; i++){
        anagram = false;
        if(len == (int)strlen(dic[i].word)){
            /* Do further tests */
            if(compare(item.word, dic[i].word, len)==true &&
            compare(dic[i].word, item.word, len) ==true){
                anagram = true;
            }
        }
        if(anagram==true && 
        comp_id(dic[i].id, used_id) == false){
            /* Add word to list */
            append_a(anagrams, dic[i].word, apos);
            apos++;
        }
    }
    return apos;
}

void append_a(char anagrams[MAXLEN][MAXLEN], char* word, 
int apos)
{
    int i;
    int len = strlen(word);
    for(i=0; i<len; i++){
        anagrams[apos][i] = word[i];
    }
}

bool comp_id(int id, int used_id[MAXWORDS])
{
    int i;
    for(i=0; i<MAXWORDS; i++){
        if(id == used_id[i]){
            return true;
        }
    }
    i=0;
    while(used_id[i] != 0){
        i++;
    }
    /* If id hasn't been used, add it to the used_id list */
    used_id[i] = id;
    return false;
}

void reset_ids(int used_id[MAXWORDS])
{
    int i;
    for(i=0; i<MAXWORDS; i++){
        used_id[i] = 0;
    }
}

bool compare(char* word, char* dic_item, int len)
{
    int i, j;
    bool here;
    for(i=0; i<len; i++){
        here = false;
        for(j=0; j<len; j++){
            if(word[i] == dic_item[j]){
                here = true;
            }
        }
        if(here == false){
            return false;
        }
    }
    return true;
}

void test(void)
{
    struct dict tdic[MAXWORDS];
    int tused_id[MAXWORDS];
    char tanagrams[MAXLEN][MAXLEN];
    int len, i;
    char* tword;
    int tpos;
    load(tdic);
    assert(tdic[0].word[0] == 'w');
    assert(tdic[0].id == 1);
    assert(tdic[1].id == 2);
    assert(tdic[MAXWORDS-2].id == MAXWORDS-1);
    assert(tdic[MAXWORDS-2].word[0] == 't');
    assert(tdic[MAXWORDS-2].word[3] == 's');
    assert(tdic[MAXWORDS-2].word[4] == '\0');
    assert(tdic[0].word[4] == '\0');
    len = strlen(tdic[MAXWORDS-2].word);
    assert(len == 4);
    assert(compare("vidad", "david", 5) == true);
    assert(compare("meoinher", "hermione", 8) == true);
    assert(comp_id(tdic[0].id, tused_id) == false);
    assert(comp_id(tdic[0].id, tused_id) == true);
    reset_ids(tused_id);
    assert(comp_id(tdic[0].id, tused_id) == false);
    /*check_dic(tdic, tdic[0], tused_id, MAXLEN);*/
    tword = "work";
    tpos = 0;
    append_a(tanagrams, tword, tpos);
    len = strlen(tword);
    for(i=0; i<len; i++){
        assert(tanagrams[tpos][i] == tword[i]);
    }
    tword = "hard";
    tpos = 1;
    append_a(tanagrams, tword, tpos);
    len = strlen(tword);
    for(i=0; i<len; i++){
        assert(tanagrams[tpos][i] == tword[i]);
    }
}
