#include "data.h"
/***DICHIARAZIONI***/

#ifndef _ARB_STRUCT_
#define _ARB_STRUCT_
typedef struct ARB{
    void* element;
    struct ARB* sx;
    struct ARB* dx;
}ARB;


ARB* newARBNode(void*, FUNCTDATA*);
ARB* freeARBNode(ARB*, FUNCTDATA*);
#endif // _ARBDATA_



ARB* detachMin(ARB*, ARB*);
ARB* adjustARB(ARB*, FUNCTDATA*);
int countARBNode(ARB*);

ARB* insertARBNode(ARB*, void*, FUNCTDATA*);
void printARB(ARB*, FUNCTDATA*);
ARB* deleteAllKey(ARB*, FUNCTDATA*);
ARB* searchStringAndDelete(ARB*, void*, FUNCTDATA*);
ARB* searchConditionAndDeleteARB(ARB*, char*, char*, int, FUNCTDATA*);
ARB* casualARB(ARB*, int, FUNCTDATA*);
ARB* duplicateARB(ARB*, FUNCTDATA*);
int controlSameARB(ARB*, ARB*, FUNCTDATA*);
void** vectorizeFunction(ARB*, void**, int*, FUNCTDATA*);
void** vectorizeARB(ARB*, FUNCTDATA*);
ARB* balanceFunction(void**, int, int, ARB*, FUNCTDATA*);
ARB* balanceARB(ARB*, FUNCTDATA*);

