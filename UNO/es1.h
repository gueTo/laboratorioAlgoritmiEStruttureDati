
#define LENGHT_WORD 5

typedef struct ARBType{
    char* stringElement;
    struct ARBType* sx;
    struct ARBType* dx;
}ARB;


/***DICHIARAZIONI FUNZIONI***/
ARB* newARBNode(char*);
ARB* freeARBNode(ARB*);
ARB* detachMin(ARB*, ARB*);
ARB* adjustARB(ARB*);
char* casualString();
int countARBNode(ARB* );

ARB* insertARBNode(ARB*, char*);
void printARB(ARB*);
ARB* deleteAllKey(ARB*);
ARB* searchStringAndDelete(ARB*, char*);
ARB* searchConditionAndDeleteARB(ARB*, char*, char*, int);
ARB* casualARB(ARB*, int);
ARB* duplicateARB(ARB*);
int controlSameARB(ARB*, ARB*);
char** vectorizeFunction(ARB*, char**, int*);
char** vectorizeARB(ARB*);
ARB* balanceARB(ARB*);
ARB* balanceFunction(char**, int, int, ARB*);
