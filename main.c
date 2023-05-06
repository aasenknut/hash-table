#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_INIT_CAP 1024
#define KEY_CAP 512 
#define ENTRY_CAP 1024
#define IDX_ENTRY_CAP 128

typedef struct {
    char key[KEY_CAP];
    void *value;
} entry_record;

typedef struct {
    entry_record records[IDX_ENTRY_CAP];
    int taken;
} table_entry;

typedef struct {
    size_t count;
    size_t cap;
    table_entry *entries;
} hash_table;

unsigned long djb2_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + str[c];
    }
    return hash;
}

size_t table_index(char *key, size_t cap) {
    return (size_t)(djb2_hash(key) % cap);
}

void* table_insert_entry(hash_table* table, char* key, void* val) {
    size_t idx = table_index(key, table->cap);
    entry_record *rec = malloc(sizeof(entry_record));
    strcpy(rec->key, key);
    rec->value = val;
    table->entries[idx].records[table->entries[idx].taken++] = *rec;
    table->count++;
    return table;
}


hash_table* table_expand(hash_table* table) {
    size_t new_cap = table->cap * 2;
    assert(new_cap > table->cap); // overflow check

    table_entry* new_table_entries = calloc(new_cap, sizeof(table_entry));
    assert(new_table_entries != NULL);
    hash_table* new_table = {0};
    new_table->count = table->count; 
    new_table->cap =new_cap; 
    new_table->entries =new_table_entries;

    for(size_t j = 0; j < table->count; j++) {
        table_insert_entry(new_table, table->entries->records->key, table->entries->records->value);
    }

    return new_table;
}

void* table_insert(hash_table *table, char *key, void *val) {
    if (table->count > (table->cap)/2) {
        table_expand(table);
    }
    table_insert_entry(table, key, val);
    return table;
}


table_entry* table_get(hash_table *table, char *key) {
    size_t idx = table_index(key, table->cap);
    return &(table->entries[idx]);
}


hash_table* new_hash_table() {
    hash_table* table = malloc(sizeof(hash_table));
    table->count = 0;
    table->cap = TABLE_INIT_CAP;
    table->entries = malloc(sizeof(table_entry) * TABLE_INIT_CAP);

    assert(table->entries != NULL);

    for (size_t j = 0; j < TABLE_INIT_CAP; j++) {
        table->entries[j].taken = 0;
        for (size_t k = 0; k < IDX_ENTRY_CAP; k++) {
            table->entries[j].records[k].key[0] = '\0';
            table->entries[j].records[k].value = NULL;
        }
    }
    return table;
}

void dump_table(hash_table *table) {
    printf("\nDumping table...");
    for (size_t j = 0; j < table->cap; j++) {
        for (size_t i = 0; i < IDX_ENTRY_CAP; i++) {
            if (table->entries[j].records[i].value != NULL) {
                char* str = (char*)table->entries[j].records[i].value;
                printf("\n%s", str);
            }
        }
    }
    printf("\nDumped table.");
}

int main() {
    hash_table* table = new_hash_table();
    size_t n_records = 26;
    size_t value_len = 26;
    char *str = malloc(value_len * sizeof(char));
    char **vals = malloc(n_records * sizeof(char *));
    int *keys = malloc(n_records * sizeof(int));
    for (size_t j=0; j<n_records; j++) {
        vals[j] = malloc((j+1) * sizeof(char));
        keys[j] = j;
        str[j] = 'A' + j;
        strcpy(vals[j], str);
    }

    for (size_t j=0; j<n_records; j++) {
        char k[KEY_CAP];
        sprintf(k, "%d", keys[j]);
        table_insert(table, k, vals[j]);
    }

    dump_table(table);
    printf("\n\n[END]\n\n");
    return 1;
}



