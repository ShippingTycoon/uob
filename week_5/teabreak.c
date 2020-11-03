#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 2892
#define MAXLEN 15
#define NUMWORDS 2

enum bool {false, true};
typedef enum bool bool;

struct dict{
    char word[MAXLEN];
    int id;
};

void test(void);
void load(struct dict dic[MAXWORDS]);
void check_dic(struct dict dic[MAXWORDS], char* word,
struct dict dic_item1, int used_ids[MAXWORDS][NUMWORDS],
char anagrams[NUMWORDS][MAXLEN]);
bool compare(char* word, char* other_word, int len);
bool comp_id(int id1, int id2, int used_id[MAXWORDS][NUMWORDS]);

int main(int argc, char** argv)
{
    struct dict dic[MAXWORDS];
    int used_ids[MAXWORDS][NUMWORDS];
    char anagrams[NUMWORDS][MAXLEN];
    int i, j;
    test();
    if(argc==2){
        char* word = argv[1];
        load(dic);
        for(i=0; i<MAXWORDS/2; i++){
            check_dic(dic, word, dic[i], used_ids, anagrams);
        }
    }
    else{
        fprintf(stderr, "Usage: ./teabreak word\n");
        exit(EXIT_FAILURE);
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

void reassign_word(char* word_pair, char* new)
{
    int i;
    int len = strlen(word_pair);
    for(i=0; i<len; i++){
        if(word_pair[i] !='\0'){
            word_pair[i] = '\0';
        }
    }
    len = strlen(new);
    for(i=0; i<len; i++){
        word_pair[i] = new[i];
    }
}

bool compare(char* word, char* other_word, int len)
{
    int i, j;
    bool here;
    for(i=0; i<len; i++){
        here = false;
        for(j=0; j<len; j++){
            if(word[i] == other_word[j]){
                here = true;
            }
        }
        if(here == false){
            return false;
        }
    }
    return true;
}

bool comp_id(int id1, int id2, int used_id[MAXWORDS][NUMWORDS])
{
    int i, j;
    for(i=0; i<MAXWORDS; i++){
        if((id1==used_id[i][0]&&id2==used_id[i][1]) ||
        (id2==used_id[i][0]&&id1==used_id[i][1])){
            return true;
        }
    }
    i=0;
    while(used_id[i][0] != 0){
        i++;
    }
    /* If id pair hasn't been used, add to used_id list */
    used_id[i][0] = id1;
    used_id[i][1] = id2;
    return false;
}

void check_dic(struct dict dic[MAXWORDS], char* word,
struct dict dic_item1, int used_ids[MAXWORDS][NUMWORDS],
char anagrams[NUMWORDS][MAXLEN])
{
    int i, apos = 0;
    char word_pair[MAXLEN*2];
    char new_word[MAXLEN];
    bool anagram;
    int len = strlen(word);
    new_word = strcat(word_pair, dic_item1.word);
    for(i=0; i<MAXWORDS-1; i++){
        reassign_word(word_pair, new_word);
        word_pair = strcat(word_pair, dic[i].word);
        anagram = false;
        if(len == (int)strlen(word_pair)){
            /* Do further tests */
            if(compare(word, word_pair, len)==true &&
            compare(word_pair, word, len) ==true){
                anagram = true;
            }
        }
        if(anagram==true && 
        comp_id(dic[i].id, dic_item1.id, used_ids) == false){
            /* Add word to list */
            /* This will result in a write error */
            append_a(anagrams, dic[i].word, apos);
            apos++;
            append_a(anagrams, dic_item1.word, apos);
            printf("%s\n", word_pair);
            apos = 0;
        }
    }
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

void test(void)
{
    struct dict tdic[MAXWORDS];
    int tused_id[MAXWORDS][NUMWORDS];
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
    assert(comp_id(tdic[0].id, tdic[1].id, tused_id) == false);
    assert(comp_id(tdic[0].id, tdic[1].id, tused_id) == true);
}
