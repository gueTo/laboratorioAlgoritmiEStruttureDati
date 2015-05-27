#ifndef _FUNCPY_
#define _FUNCPY_

typedef void*(*FUNCPY)(void*, void*);

#endif // _FUNCPY_

#ifndef _FUNDEL_
#define _FUNDEL_

typedef void(*FUNDEL)(void*);

#endif // _FUNDEL_

#ifndef _HEAPTYPE_

    #define _HEAPTYPE_
    typedef enum heapType {ARRAY_TYPE, TREE_TYPE} heapType;

#endif // _HEAPTYPE_

#ifndef _HEAPNODE_

    #define _HEAPNODE_

    typedef struct heapNode{
        void* data;
        int priority;
    }heapNode;

#endif

#ifndef _HEAPABNODE_

    #define _HEAPABNODE_

    typedef struct heapABNode{
        struct heapABNode* dad;
        struct heapABNode* sx;
        struct heapABNode* dx;
        heapNode* element;
    }heapABNode;

#endif // _HEAPABNODE_

#ifndef _ABNODE_

    #define _ABNODE_

    typedef struct ABHEAP{
        heapABNode* HEAPROOT;
    }ABHEAP;

#endif // _ABNODE_

#ifndef _ARRAYHEAP_

    #define _ARRAYHEAP_

    typedef struct ARRAYHEAP{
        heapNode* HEAP;
        int HEAPDIM;
    }ARRAYHEAP;

#endif // _ARRAYHEAP_

#ifndef _HEAP_

    #define _HEAP_

    typedef struct heap{
        ARRAYHEAP* heapArray;
        ABHEAP* heapTree;
        int HEAPSIZE;
        struct FUNCTHEAP* function;
        heapType type;
    }heap;
#endif // _HEAP_


typedef heap*(*FUNHEAPINS)(heap*, void*, int, FUNCPY);
typedef heap*(*FUNHEAPDEL)(heap*, int);
typedef heapNode*(*FUNHEAPMAX)(heap*);
typedef heapNode*(*FUNHEAPEXTRMAX)(heap*);
typedef void(*FUNHEAPCHANGEPRI)(heap*, int, int);
typedef void(*FUNHEAPIFY)(heap*, int);
typedef heap*(*FUNFREEHEAP)(heap*);
typedef heap*(*FUNFREEHEAPANDELEMENT)(heap*, FUNDEL);

#ifndef _FUNCTHEAP_

    #define _FUNCTHEAP_

    typedef struct FUNCTHEAP{
        FUNHEAPIFY heapify;
        FUNHEAPMAX maxHeap;
        FUNHEAPEXTRMAX extractMaxHeap;
        FUNHEAPCHANGEPRI decreasePriorityHeap;
        FUNHEAPCHANGEPRI increasePriorityHeap;
        FUNHEAPDEL delKeyHeap;
        FUNHEAPINS insKeyHeap;
        FUNFREEHEAP freeOnlyHeap;
        FUNFREEHEAPANDELEMENT freeAll;
    }FUNCTHEAP;

#endif

/***********************************************/
int right(int);
int left(int);
int dad(int);

FUNCTHEAP* initFuncHeap(heapType typeH);
FUNCTHEAP* deleteFuncHeap(FUNCTHEAP*);
/***********************************************/


heap* makeArrayHeap(int n, heapNode*, FUNCPY);
void heapifyArrayHeap(heap* H, int i);
heapNode* maxArrayHeap(heap* extr);
heapNode* extractMaxArrayHeap(heap* extr);
void decreasePriorityArrayHeap(heap* dec, int nEl, int newP);
void increasePriorityArrayHeap(heap* dec, int nEl, int newP);
heap* deleteKeyArrayHeap(heap* A,int i);
heap* insertKeyArrayHeap(heap* A, void*, int key, FUNCPY);
heap* freeArrayHeap(heap*);
heap* freeArrayHeapWithElements(heap*, FUNDEL);


/***********************************************/

heapABNode* makeHeapTreeNode(heapABNode* root, heapABNode* dad, void* toIns, int pri, FUNCPY);
heapABNode* scrollTreeHeap(heap* HEAP, int n);
heapABNode* freeTWE(heapABNode*, FUNDEL);
heapABNode* freeT(heapABNode*);

heap* makeTreeHeap(int n, heapNode*, FUNCPY);
void heapifyTreeHeap(heap* root, int);
heapNode* maxTreeHeap(heap* HEAP);
heapNode* extractMaxTreeHeap(heap* HEAP);
void decreasePriorityTreeHeap(heap* HEAP, int pos, int nPri);
void increasePriorityTreeHeap(heap* HEAP, int pos, int nPri);
heap* deleteKeyTreeHeap(heap* HEAP, int i);
heap* insertKeyTreeHeap(heap* HEAP, void* elem, int key, FUNCPY);
heap* freeTreeHeapWithElements(heap*, FUNDEL);
heap* freeTreeHeap(heap*);

/**************************************************/

heap* makeHeap(heapType TYPE, int n, heapNode*, FUNCPY);
void heapify(heap* toHeapify, int where);
heapNode* maxHeap(heap* see);
heapNode* extractMaxHeap(heap* toExtract);
void increasePriorityHeap(heap* HEAP, int toIncrease, int newPriority);
void decreasePriorityHeap(heap* HEAP, int toDecrease, int newPriority);
heap* deleteKeyHeap(heap* HEAP, int toDelete);
heap* insertKeyHeap(heap* HEAP, void* toInsert, int priority, FUNCPY);
heap* freeHeap(heap* toFree);
heap* freeHeapWithElements(heap*, FUNDEL);

