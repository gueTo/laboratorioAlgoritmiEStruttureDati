#ifndef _DATA_H_
#include <stdio.h>
    #define _DATA_H_

/***DICHIARAZIONE FUNZIONI***/


#ifndef STRING_MAX_SIZE

    #define STRING_MAX_SIZE 10

#endif // STRING_MAX_SIZE


#ifndef _FUNINS_
#define _FUNINS_
typedef void*(*FUNINS)(void*);

#endif // _FUNINS_

#ifndef _FUNCOM_
#define _FUNCOM_

typedef int(* FUNCOM)(void*, void*, void*);

#endif // _FUNCOM_

#ifndef _FUNPRINT_
#define _FUNPRINT_

typedef void(*FUNPRINT)(FILE*, void*, void*);

#endif // _FUNPRINT_

#ifndef _FUNDEL_
#define _FUNDEL_

typedef void*(*FUNDEL)(void*, void*);

#endif // _FUNDEL_

#ifndef _FUNRAND_
#define _FUNDEL_

typedef void*(*FUNRAND)(void*);

#endif // _FUNRAND_

#ifndef _FUNCPY_
#define _FUNCPY_

typedef void*(*FUNCPY)(void*, void*, void*);

#endif // _FUNCPY_

#ifndef _FUNOOD_
#define _FUNOOD_

typedef int(*FUNODD)(void*, int, void*);

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
FUNCTDATA *initFUNCTDATA_2(FUNINS, FUNCPY, FUNRAND, FUNCOM, FUNODD, FUNPRINT, FUNDEL);
void FUNCTDATAtype(FUNCTDATA* , int);
FUNCTDATA* deleteFUNCTDATA(FUNCTDATA*);

#endif // _FUNCTDATA_



void* insertString(void*);
void* insertInteger(void*);
void* insertFloat(void*);
void printInteger(FILE*, void*, void*);
void printFloat(FILE*, void*, void*);
void printString(FILE*, void*, void*);
int compareInteger(void*, void*, void*);
int compareFloat(void*, void*, void*);
int compareString(void*, void*, void*);
void* deleteString(void*, void*);
void* deleteInteger(void*, void*);
void* deleteFloat(void*, void*);
void* casualInteger(void*);
void* casualFloat(void*);
void* casualString(void*);
void* copyString(void*, void*, void*);
void* copyInteger(void*, void*, void*);
void* copyFloat(void*, void*, void*);
int oddInteger(void*, int, void*);
int oddFloat(void*, int, void*);
int oddString(void*, int, void*);



#endif // _DATA_H_
