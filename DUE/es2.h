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


ARB* newARBNode(void*, FUNCPY);
ARB* freeARBNode(ARB*, FUNDEL);
ARB* detachMin(ARB*, ARB*);
ARB* adjustARB(ARB*, FUNDEL);
int countARBNode(ARB*);

ARB* insertARBNode(ARB*, void*, FUNCOM, FUNCPY);
void printARB(ARB*, FUNPRINT);
ARB* deleteAllKey(ARB*, FUNDEL);
ARB* searchStringAndDelete(ARB*, void*, FUNCOM, FUNDEL);
ARB* searchConditionAndDeleteARB(ARB*, char*, char*, int, FUNCOM, FUNODD, FUNDEL);
ARB* casualARB(ARB*, int, FUNRAND, FUNCOM, FUNCPY);
ARB* duplicateARB(ARB*, FUNCPY);
int controlSameARB(ARB*, ARB*, FUNCOM);
void** vectorizeFunction(ARB*, void**, int*, FUNCPY);
void** vectorizeARB(ARB*, FUNCPY);
ARB* balanceFunction(void**, int, int, ARB*, FUNCOM, FUNCPY);
ARB* balanceARB(ARB*, FUNCOM, FUNCPY);
int oddInteger(void*, int);
int oddString(void*, int);

