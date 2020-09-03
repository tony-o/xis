#ifndef __THASH_H__
#define __THASH_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct thash_ll {
    char* key;
    void* val;
    struct thash_ll* next;
} thash_ll;

typedef struct thash_bt {
    struct thash_bt* ab[255];
    void* thash_ll;
} thash_bt;


typedef struct thash {
    struct thash_ll* head;
    struct thash_ll* tail;
    struct thash_bt* trie;
} thash;

thash* thash_new();
thash_bt* thash_tree_walk(thash_bt*,char*,char*);
void thash_put(thash*,char*,void*);
void* thash_get(thash*,char*);
void thash_free(thash*,int);

#endif
