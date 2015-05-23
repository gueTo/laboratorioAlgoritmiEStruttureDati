#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifo.h"
#include "data.h"


/***DICHIARAZIONI***/
#ifndef _FUNINS_
#define _FUNINS_
typedef void*(*FUNINS)();

#endif // _FUNINS_

#ifndef _FUNCOM_
#define _FUNCOM_

typedef int(* FUNCOM)(void*, void*);

#endif // _FUNCOM_

#ifndef _FUNPRINT_
#define_FUNPRINT_

typedef void(* FUNPRINT)(void*);

#endif // _FUNPRINT_

#ifndef _FUNDEL_
#define _FUNDEL_

typedef void(*FUNDEL)(void*);

#endif // _FUNDEL_

#ifndef _FUNRAND_
#define _FUNDEL_

typedef void*(*FUNRAND)();

#endif // _FUNRAND_

#ifndef _FUNCPY_
#define _FUNCPY_

typedef void*(*FUNCPY)(void*, void*);

#endif // _FUNCPY_

#ifndef _FUNOOD_
#define _FUNOOD_

typedef int(*FUNODD)(void*, int);

#endif // _FUNOOD_



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
