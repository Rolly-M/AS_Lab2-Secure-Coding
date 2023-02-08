#ifndef __HASH__
#define __HASH__

#define KEY_STRING_MAX 256  // Increased the maximum length of the key string
#define MAP_INITIAL_SIZE 128  // Initial size of the hash map, can be increased dynamically if needed

typedef struct PairValue {
	char *KeyName;  // Changed the key string from an array to a pointer, allowing for dynamic memory allocation
	int  ValueCount;
	struct PairValue* Next;
} PairValue;

typedef struct {
	int size;  // Added size variable to track the current size of the hash map
	int capacity;  // Added capacity variable to track the maximum capacity of the hash map
	PairValue** data;  // Changed data from an array to a pointer, allowing for dynamic memory allocation
} HashMap;

HashMap* HashInit();  // Added error handling mechanism
void HashAdd(HashMap *map, PairValue *value);  // Added error handling mechanism and return value and changed the  function signature to void to be consistent as used in hash.c
void HashDelete(HashMap *map, const char* key);  // Added error handling mechanism and return value and changed  the  function signature to void to be consistent as used in hash.c
PairValue* HashFind(HashMap *map, const char* key); 
void HashDump(HashMap *map);  
#endif
