#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HT_CAP 128

typedef struct {
    const char* key;
    void* value;
} entry;

typedef struct {
    size_t count;
    entry entries[HT_CAP];
} hash_table;

unsigned long djb2_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + str[c];
    }
    return hash;
}

void* ht_insert(char *str) {
}

void* ht_get(char *str) {
    unsigned long key;
    key = djb2_hash(str);
    return ;
}


int main() {
    char *str = malloc(27);
    for (int j=0; j<26; j++) {
        char c = 'A' + j;
        str[j] = c;
    }
    printf("\nstring: %s", str);
    void* entry = ht_get(str);
    printf("\nptr: %p", entry);
    free(str);
    return 1;
}
