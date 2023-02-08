/**
*
* @Name : hash.h
*
**/
#ifndef __HASH__
#define __HASH__

    typedef struct {
        // The maximum length of the key string is defined as 255, which may not be sufficient in some cases. 
        // This could lead to overflow issues or truncation of the key string. Hence affecting Integrity
        #define KEY_STRING_MAX 255
		char KeyName[KEY_STRING_MAX];
		int  ValueCount;
        struct PairValue* Next;
	} PairValue;

	typedef struct {
        // Fixed maximum size of the hash map at 128, which may not be sufficient in some cases. 
        //This could lead to overflow issues or inefficient memory usage. Hence affecting Integrity, confidentiality and even availaibility
        #define MAP_MAX 128
		PairValue* data[MAP_MAX];
	} HashMap;

    /* The functions defined below do not have an error handling mechanisms defined. 
     For example, if the hash map is full and the HashAdd function is called, 
     there is no way to handle the error or report it to the caller. This may highly affect the apps availaibility
    */

    HashMap* HashInit();
    void HashAdd(HashMap *map, PairValue *value);
    void HashDelete(HashMap *map, const char* key);
    PairValue* HashFind(HashMap *map, const char* key);
    // No input validation Defined for the functions, this way malicious data or very long
    // strings could be entered leading to overflow issues hence Integrity, confidentiality and even availaibility
    void HashDump(HashMap *map);
#endif