#ifndef _HASH_H_
#include "list.h"
    #define _HASH_H_


    typedef struct HASH_OPERATION{
        FUNHASH hashing;
        FUNCOLLISION gestCollision;
    }HASH_OPERATION;

    typedef struct HASH_TABLE{
        long unsigned int dimension;
        LIST* table;
        FUNCTDATA* l_operation;
    }HASH_TABLE;

    HASH_OPERATION* initHashOperation(FUNHASH, FUNCOLLISION);
    HASH_TABLE* initHashTable(long unsigned int, FUNCTDATA*);//, HASH_OPERATION*);
    HASH_TABLE* insertIntoHashTable(HASH_TABLE*, void*, void*);
    HASH_TABLE* deleteFromHashTable(HASH_TABLE*, void*, void*);
    void* searchIntoHashTable(HASH_TABLE*, void*, void*);
    void printHashTable(FILE*, HASH_TABLE*, void*);
    HASH_TABLE* restructHashTable(HASH_TABLE*, long unsigned int, void*);
    HASH_TABLE* freeHashTable(HASH_TABLE*, void*);

    void* collisionString(void*);
    unsigned long hashingString(void*, void*);
    void* collisionInteger(void*);
    unsigned long hashingInteger(void*, void*);

#endif // _HASH_H_
