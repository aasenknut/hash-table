#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HT_INIT_CAP 128

typedef struct {
    const char* key;
    void* value;
} entry;

typedef struct {
    size_t count;
    size_t cap;
    entry* entries;
} hash_table;

hash_table HT = {0};

unsigned long djb2_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + str[c];
    }
    return hash;
}

void* ht_insert(hash_table* ht, char *key, void* val) {
    return key;
}

void* ht_set() {
}

void* ht_expand(hash_table* ht) {
    size_t new_cap = (*ht).cap * 2;
    assert(new_cap < (*ht).cap); // overflow

    entry* new_ht = calloc(new_cap, sizeof(entry));
    assert(new_ht!=NULL);

    for(int j = 0; j < (*ht).count; j++) {
        new_ht[j] = ht[j];
    }


    return NULL;
}

void* ht_get(char *str) {
    unsigned long key;
    key = djb2_hash(str);
    return ;
}

hash_table* new_hash_table() {
    hash_table* ht;
    (*ht).count = 0;
    (*ht).cap = HT_INIT_CAP;
    (*ht).entries = malloc(sizeof(entry) * HT_INIT_CAP);
    if ((*ht).entries == NULL) {
        return NULL;
    }
    return ht;
}

int main() {
    char *str = malloc(27);
    for (int j=0; j<26; j++) {
        char c = 'A' + j;
        str[j] = c;
    }
    printf("\nstring: %s", str);
    unsigned long key;
    key = djb2_hash(str);
    void* entry = ht_get(str);
    printf("\nptr: %p", entry);
    free(str);

    hash_table ht;
    ht = new_hash_table();
    return 1;
}
