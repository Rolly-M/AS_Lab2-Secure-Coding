#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_fixed.h"

#define MAP_MAX 256 

int main() {

// corrected the hash function to use a more appropriate algorithm hence reducing risk of  hash collisions
unsigned HashIndex(const char* key) {
    unsigned sum = 0;
    for (const char* c = key; *c; c++){
        sum = sum * 31 + *c; 
    }
    
    return sum % MAP_MAX;
}

// Hashinit function fixed to be  initialized properly 
HashMap* HashInit() {
    HashMap* map = malloc(sizeof(HashMap));
    for (int i = 0; i < MAP_MAX; i++) {
        map->data[i] = NULL;
    }
    return map;
}

// 
void HashAdd(HashMap *map,PairValue *value) {
    unsigned idx = HashIndex(value->KeyName);
    
    if (map->data[idx]) 
        value->Next = map->data[idx]->Next;
    else
        value->Next = NULL;
    map->data[idx] = value;	
}

PairValue* HashFind(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx]; val != NULL; val = val->Next ) { // Fixed the Next pointer declaration 
        if (strcmp(val->KeyName, key) == 0) // fixed the comparison function
            return val;
    }
    
    return NULL; 
}

void HashDelete(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx], *prev = NULL; val != NULL; prev = val, val = val->Next ) {
        if (strcmp(val->KeyName, key) == 0) { // fixed the comparison function by using strcmp to achieve intended behaviour
            if (prev)
                prev->Next = val->Next;
            else
                map->data[idx] = val->Next;
        }
    }
}

void HashDump(HashMap *map) {
    for( unsigned i = 0; i < MAP_MAX; i++ ) {
        for( PairValue* val = map->data[i]; val != NULL; val = val->Next ) {
            printf("%s\n", val->KeyName); // fixed the format string for the printf function by defining the newline character to properly print a string followed by a newline character.
        }
    }
}
    return 0;
}