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


FUNCT *initFUNCT();
void FUNCTtype(FUNCT* , int);
FUNCT* deleteFUNCT(FUNCT*);


ARB* newARBNode(void*, FUNCT*);
ARB* freeARBNode(ARB*, FUNCT*);
ARB* detachMin(ARB*, ARB*);
ARB* adjustARB(ARB*, FUNCT*);
int countARBNode(ARB*);

ARB* insertARBNode(ARB*, void*, FUNCT*);
void printARB(ARB*, FUNCT*);
ARB* deleteAllKey(ARB*, FUNCT*);
ARB* searchStringAndDelete(ARB*, void*, FUNCT*);
ARB* searchConditionAndDeleteARB(ARB*, char*, char*, int, FUNCT*);
ARB* casualARB(ARB*, int, FUNCT*);
ARB* duplicateARB(ARB*, FUNCT*);
int controlSameARB(ARB*, ARB*, FUNCT*);
void** vectorizeFunction(ARB*, void**, int*, FUNCT*);
void** vectorizeARB(ARB*, FUNCT*);
ARB* balanceFunction(void**, int, int, ARB*, FUNCT*);
ARB* balanceARB(ARB*, FUNCT*);

