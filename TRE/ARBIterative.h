#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifo.h"
#include "data.h"


/***DICHIARAZIONI***/
typedef void*(*FUNINS)();
typedef int(* FUNCOM)(void*, void*);
typedef void(* FUNPRINT)(void*);
typedef void(*FUNDEL)(void*);
typedef void*(*FUNRAND)();
typedef void*(*FUNCPY)(void*, void*);
typedef int(FUNODD)(void*, int);


typedef struct ARBType{
    void* element;
    struct ARBType* sx;
    struct ARBType* dx;
}ARB;


/****/

ARB* newARBNode(void*, FUNCPY);
ARB* freeARBNode(ARB*, FUNDEL);
int countARBNode(ARB*);

/****/




ARB* insertARBNodeIterative(ARB*, void*, FUNCOM, FUNCPY);
ARB* deleteARBIterative(ARB*, FUNDEL);
void preOrderARBIter(ARB*, FUNPRINT);
void inOrderARBIter(ARB*, FUNPRINT);
void postOrder(ARB*, FUNPRINT);
ARB* searchAndDeleteIterative(ARB*, void*, FUNCOM, FUNDEL);

ARB* deleteNodeIter(ARB*, FUNDEL);
ARB* searchConditionAndDeleteIterative(ARB*, char*, char*, int, FUNCOM, FUNODD, FUNDEL);
ARB* duplicateARBIterative(ARB*, ARB*, FUNCOM, FUNCPY);
int controlSameARB(ARB*, ARB*, FUNCOM);
int controlSameARBIterative(ARB*, ARB*, FUNCOM);
int countARBNodeIterative(ARB*);

void** vectorizeARBIterative(ARB*, FUNCPY);

ARB* balanceARBIterative(ARB* toBalance, FUNCOM compare, FUNCPY fcopy);
