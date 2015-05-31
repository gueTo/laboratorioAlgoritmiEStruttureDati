/***DICHIARAZIONE FUNZIONI***/
#ifndef STRING_MAX_SIZE

    #define STRING_MAX_SIZE 10

#endif // STRING_MAX_SIZE


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



void* insertString();
void* insertInteger();
void* insertFloat();
void printInteger(void*);
void printFloat(void*);
void printString(void*);
int compareInteger(void*, void*);
int compareFloat(void*, void*);
int compareString(void*, void*);
void deleteString(void*);
void deleteInteger(void*);
void deleteFloat(void*);
void* casualInteger();
void* casualFloat();
void* casualString();
void* copyString(void*, void*);
void* copyInteger(void*, void*);
void* copyFloat(void*, void*);
int oddInteger(void*, int);
int oddFloat(void*, int);
int oddString(void*, int);


