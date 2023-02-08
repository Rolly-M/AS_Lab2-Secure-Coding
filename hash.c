/**
*
* @Name : hash.c
*
**/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* The HashIndex function  is not suitable for generating hash values as it only adds up the values of the characters in the key. 
This can result in many hash collisions and reduce the effectiveness of the hash map thereby affecting programs availaibility
*/
unsigned HashIndex(const char* key) { 
    unsigned sum = 0;
    for (char* c = key; c; c++){
        sum += *c;
    }
    
    return sum;
}

/*
The hash map is not initialized properly in the HashInit function. 
The data array needs to be initialized to NULL so that the HashAdd function can determine if a value is already present at a given index.
*/
HashMap* HashInit() {
	return malloc(sizeof(HashMap));
}

/*
The HashAdd function sets the Next pointer of a PairValue to itself in the case that the hash map index is not empty. 
This creates a circular linked list and can cause unexpected behavior thereby affecting availaibility.
*/
void HashAdd(HashMap *map,PairValue *value) { 
    unsigned idx = HashIndex(value->KeyName);
    
    if (map->data[idx]) 
        value->Next = map->data[idx]; // Next pointer should be updated to map->data[idx], not map->data[idx]->Next.  As the latter is incorrect and may affect the availability of the program.
    map->data[idx] = value;	
}

PairValue* HashFind(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx]; val != NULL; val = val->Next ) {
        /*The strcpy function in the HashFind and HashDelete functions is not correct, as it doesn't compare strings, 
        but instead copies one string over another, which may cause unintended behavior. The correct function to use is strcmp.
        */
        if (strcpy(val->KeyName, key)) // comparison of key values should be done using strcmp instead of strcpy
            return val;
    }
    
    return NULL; 
}

void HashDelete(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx], *prev = NULL; val != NULL; prev = val, val = val->Next ) {
        if (strcpy(val->KeyName, key)) { // comparison of key values should be done using strcmp instead of strcpy
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
            printf(val->KeyName); // Incorrect format string, missing newline character. May result in program not running hence affecting availaibility
        }
    }
}
