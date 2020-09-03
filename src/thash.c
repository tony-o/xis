#include "thash.h"

thash* thash_new() {
    thash* t = malloc(sizeof(thash));

    t->head = malloc(sizeof(thash_ll));
    t->head->next = 0;
    t->tail = t->head;

    t->trie = malloc(sizeof(thash_bt));
    t->trie->ab[0] = t->trie->ab[1] = 0;
    t->trie->thash_ll = 0;

    return t;
}

thash_bt* thash_tree_walk(thash_bt* t, char* key, char* o_key) {
    if(t == 0 || strlen(key) == 0){
        return t;
    }
    int ab = key[0];
    if(t->ab[ab] == 0){
        t->ab[ab] = malloc(sizeof(thash_bt));
        return t->ab[ab];
    }
    if(strcmp(((thash_ll*)t->ab[ab]->thash_ll)->key, o_key) == 0){
        return t->ab[ab];
    }
    return thash_tree_walk(t->ab[ab], key+1, o_key);
}

void* thash_get(thash* t, char* key) {
    // walk the trie
    thash_bt* n = thash_tree_walk(t->trie, key, key);
    return ((thash_ll*)n->thash_ll)->val;
}

void thash_put(thash* t, char* key, void* val) {
    thash_bt* n = thash_tree_walk(t->trie, key, key);
    if(n->thash_ll == 0) {
        t->tail->key = key;
        t->tail->val = val;
        t->tail->next = malloc(sizeof(thash_ll));
        n->thash_ll = t->tail;
        t->tail = t->tail->next;
        t->tail->next = 0;
    } else {
        ((thash_ll*)n->thash_ll)->val = val;
        ((thash_ll*)n->thash_ll)->key = key;
    }
}

void thash_free(thash* t, int free_val){
    if(free_val > 0){
        thash_ll* h = t->head;
        thash_ll* c;
        while(h->next != 0) {
            if(h->key != 0){
                free(h->key);
            }
            if(h->val != 0){
                free(h->val);
            }
            c = h;
            h = h->next;
            if(c != 0){
                free(c);
            }
        }
        if(h->key != 0){
            free(h->key);
        }
        if(h->val != 0){
            free(h->val);
        }
    }
    free(t->head);
    free(t->tail);
    free(t->trie);
}
