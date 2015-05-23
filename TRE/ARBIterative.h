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
typedef int(*FUNODD)(void*, int);


typedef struct func{
	FUNINS fins;
	FUNCPY fcopy;
   	FUNRAND frand;
   	FUNCOM fcomp;
   	FUNODD fodd;
   	FUNPRINT fpri;
   	FUNDEL funfree;
   	int ty;
}FUNCT;

typedef struct ARBType{
    void* element;
    struct ARBType* sx;
    struct ARBType* dx;
}ARB;

typedef struct boundArray{
    int i;
    int j;
}boundArray;

/****/

ARB* newARBNode(void*, FUNCT*);
ARB* freeARBNode(ARB*, FUNCT*);
int countARBNode(ARB*);

/****/




ARB* insertARBNodeIterative(ARB*, void*, FUNCT*);
ARB* deleteARBIterative(ARB*, FUNCT*);
void preOrderARBIter(ARB*, FUNCT*);
void inOrderARBIter(ARB*, FUNCT*);
void postOrder(ARB*, FUNCT*);
ARB* searchAndDeleteIterative(ARB*, void*, FUNCT*);

ARB* deleteNodeIter(ARB*, FUNCT*);
ARB* searchConditionAndDeleteIterative(ARB*, char*, char*, int, FUNCT*);
ARB* duplicateARBIterative(ARB*, ARB*, FUNCT*);
int controlSameARB(ARB*, ARB*, FUNCT*);
int controlSameARBIterative(ARB*, ARB*, FUNCT*);
int countARBNodeIterative(ARB*);

void** vectorizeARBIterative(ARB*, FUNCT*);

ARB* balanceARBIterative(ARB*, FUNCT*);

FUNCT *initFUNCT();
void FUNCTtype(FUNCT* , int);
FUNCT* deleteFUNCT(FUNCT*);
