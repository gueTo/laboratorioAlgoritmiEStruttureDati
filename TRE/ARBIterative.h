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
#define _FUNPRINT_

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

#ifndef _FUNCTDATA_
#define _FUNCTDATA_


typedef struct func{
	FUNINS fins;
	FUNCPY fcopy;
   	FUNRAND frand;
   	FUNCOM fcomp;
   	FUNODD fodd;
   	FUNPRINT fpri;
   	FUNDEL funfree;
   	int ty;
}FUNCTDATA;

FUNCTDATA *initFUNCTDATA();
void FUNCTDATAtype(FUNCTDATA* , int);
FUNCTDATA* deleteFUNCTDATA(FUNCTDATA*);

#endif // _FUNCTDATA_



#ifndef _ARB_STRUCT_

#define _ARB_STRUCT__
typedef struct ARBType{
    void* element;
    struct ARBType* sx;
    struct ARBType* dx;
}ARB;

ARB* newARBNode(void*, FUNCTDATA*);
ARB* freeARBNode(ARB*, FUNCTDATA*);


#endif // _ARB_STRUCT_

#ifndef _BOUNDARRAY_
#define _BOUNDARRAY_
typedef struct boundArray{
    int i;
    int j;
}boundArray;
#endif // _BOUNDARRAY_

/****/

/****/




ARB* insertARBNodeIterative(ARB*, void*, FUNCTDATA*);
ARB* deleteARBIterative(ARB*, FUNCTDATA*);
void preOrderARBIter(ARB*, FUNCTDATA*);
void inOrderARBIter(ARB*, FUNCTDATA*);
void postOrder(ARB*, FUNCTDATA*);
ARB* searchAndDeleteIterative(ARB*, void*, FUNCTDATA*);

ARB* deleteNodeIter(ARB*, FUNCTDATA*);
ARB* searchConditionAndDeleteIterative(ARB*, char*, char*, int, FUNCTDATA*);
ARB* duplicateARBIterative(ARB*, ARB*, FUNCTDATA*);
int controlSameARB(ARB*, ARB*, FUNCTDATA*);
int controlSameARBIterative(ARB*, ARB*, FUNCTDATA*);
int countARBNodeIterative(ARB*);

void** vectorizeARBIterative(ARB*, FUNCTDATA*);

ARB* balanceARBIterative(ARB*, FUNCTDATA*);

