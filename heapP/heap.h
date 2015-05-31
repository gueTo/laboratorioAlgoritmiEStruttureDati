#include "ABR.h"
#include "data.h"

#ifndef _HEAP_TYPE_

    #define _HEAP_TYPE_

    typedef enum heapType {HEAP_ARRAY, HEAP_TREE} heapType;
    typedef enum orderHeapType {MIN_HEAP, MAX_HEAP} orderHeapType;

#endif // _HEAP_TYPE_

#ifndef _HEAPNODE_STRUCT_
#define _HEAPNODE_STRUCT_

typedef struct heapNode{
    void* info;
    int priority;
}heapNode;

#endif // _HEAPNODE_STRUCT_


#ifndef _ARB_STRUCT_
#define _ARB_STRUCT_
typedef struct ARB{
    void* element;
    struct ARB* sx;
    struct ARB* dx;
}ARB;

#endif // _ARB_STRUCT_

#ifndef _ARRAYHEAP_STRUCT_
#define _ARRAYHEAP_STRUCT_

typedef struct arrayHeap{
    heapNode* array;
    int arraySize;
}arrayHeap;

#endif // _ARRAYHEAP_STRUCT_


#ifndef _HEAP_STRUCT_
#define _HEAP_STRUCT_
typedef struct HEAP{
    void* heap;//albero o array;
    int heapSize;
    struct functHeap* functions;
    FUNCTDATA* infoFunctions;
}HEAP;
#endif // _HEAP_STRUCT_


#ifndef _GEST_HEAP_
#define _GEST_HEAP_

typedef void (*CHANGEHEAPSIZE)(HEAP*);
typedef heapNode* (*GETNODEFROMHEAP)(HEAP*, int);
typedef void (*INSERTINTOHEAP)(HEAP*, void*, int);
typedef int(*COMPAREHEAPNODE)(heapNode*, heapNode*);
typedef int(*FUNCPRIORITY)(void*);
typedef void*(*DELHEAP)(HEAP*);

typedef struct functHeap{
    CHANGEHEAPSIZE decreaseHeapSize;
    GETNODEFROMHEAP nodeFromHeap;
    INSERTINTOHEAP insertElement;
    COMPAREHEAPNODE compare;
    FUNCPRIORITY getPriority;
    DELHEAP deleteHeap;
}functHeap;

#endif // _GEST_HEAP_

HEAP* initHEAP(heapType , orderHeapType);
functHeap* initFuncHeap(heapType, orderHeapType);
FUNCTDATA* myFunctInfo();
void heapify(HEAP*, int);
HEAP* insertHeap(HEAP*, void*);
void decreaseKeyHeap(HEAP*, int, int);
void increaseKeyHeap(HEAP*, int, int);
heapNode* getHeapNode(HEAP*, int);
void swapHeapNode(heapNode*, heapNode*);
heapNode* firstHeap(HEAP*);
heapNode* extractFirstHeap(HEAP* );
void increaseHeapSizeArray(HEAP* );
void increaseHeapSizeTree(HEAP* );
void decreaseHeapSizeTree(HEAP*);
void decreaseHeapSizeArray(HEAP*);
void deleteKeyHeap(HEAP* , int);
ARB* makeHeapTreeNode(ARB*, ARB*, void*);
ARB* scrollHeapTree(ARB* , int );
heapNode* fromTreeHeap(HEAP*, int );
heapNode* fromArrayHeap(HEAP* , int );
void insertElementArray(HEAP*, void*, int);
void insertElementTree(HEAP* , void*, int);
int comparaMax(heapNode*, heapNode*);
int comparaMin(heapNode*, heapNode*);
void* insertInfo();
void* copyInfo(void*, void*);
void freeInfo(void*);
int randomPriority(void*);
void* freeTree(HEAP*);
void* freeArray(HEAP*);
void* freeHeapNode(void*, FUNDEL );
void* freeARB(HEAP* , ARB* );
void* freeHeap(HEAP*);
heapNode* insertHeapNode(void*, int);

