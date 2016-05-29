#ifndef _CORRESPONDENCE_H_
#define _CORRESPONDENCE_H_



#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct corrSupp{
    void* suppOne;
    void* suppTwo;
}corrSupp;

typedef struct CORRESPONDENCE{
    void* ID;
    unsigned int index;
}CORRESPONDENCE;


typedef struct CORRESPONDENCE_TABLE{
    HASH_TABLE* correspondenceID;
    HASH_TABLE* correspondenceIndex;
}CORRESPONDENCE_TABLE;


CORRESPONDENCE_TABLE* initCorresponcendeTable(unsigned int, FUNCTDATA*, FUNCTDATA*);
CORRESPONDENCE* newCorrespondence(void*, unsigned int, FUNCTDATA*, FUNCTDATA*, void*);
CORRESPONDENCE_TABLE* insertIntoCorrespondenceTable(CORRESPONDENCE_TABLE*, CORRESPONDENCE*, FUNCTDATA*, FUNCTDATA*, void*);
void printCorrespondenceTable(FILE*, CORRESPONDENCE_TABLE*, FUNCTDATA*, FUNCTDATA*,  void*);
CORRESPONDENCE* searchIDIntoCorrespondenceTable(CORRESPONDENCE_TABLE*, void*, FUNCTDATA*, void*);
CORRESPONDENCE* searchIndexIntoCorrespondenceTable(CORRESPONDENCE_TABLE*, unsigned long int, void*);
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByID(CORRESPONDENCE_TABLE*, void*, FUNCTDATA*, FUNCTDATA*, void*);
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByIndex(CORRESPONDENCE_TABLE*, unsigned long int, FUNCTDATA*, void*);
CORRESPONDENCE_TABLE* freeCorrespondenceTable(CORRESPONDENCE_TABLE*, FUNCTDATA*, void*);

/*************FUNZIONI DI SUPPORTO*************/
void* fakeDel(void*, void*);
int compareCorrespondenceByID(void*, void*, void*);
int compareCorrespondenceByIndex(void*, void*, void*);
void* fakeCopy(void*, void*, void*);
unsigned long int hashCorrespondenceID(void*, void*);
unsigned long int hashCorrespondenceIndex(void*, void*);
void printIDCorrespondence(FILE*, void*, void*);
void printIndexCorrespondence(FILE*, void*, void*);
void printCorrespondence(FILE*, void*, void*);
void* deleteCorrespondence(void*, void*);

#endif // _CORRESPONDENCE_H_
