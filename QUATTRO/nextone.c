#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_TYPE 0
#define TREE_TYPE 1

/**********DEALLOCAZIONE INTERO HEAP************/
typedef struct heapNode{
    void* data;
    int priority;
}heapNode;

typedef struct heapABNode{
    struct heapABNode* dad;
    struct heapABNode* sx;
    struct heapABNode* dx;
    heapNode* element;
}heapABNode;

typedef struct ABHEAP{
    heapABNode* HEAPROOT;
}ABHEAP;

typedef struct ARRAYHEAP{
    heapNode* HEAP;
    int HEAPDIM;
}ARRAYHEAP;

typedef struct heap{
    ARRAYHEAP* heapArray;
    ABHEAP* heapTree;
    int HEAPSIZE;
    struct FUNCT* function;
    int heaptype;
}heap;

typedef heap*(*FUNHEAPINS)(heap*, void*, int);
typedef heap*(*FUNHEAPDEL)(heap*, int);
typedef heapNode*(*FUNHEAPMAX)(heap*);
typedef heapNode*(*FUNHEAPEXTRMAX)(heap*);
typedef void(*FUNHEAPCHANGEPRI)(heap*, int, int);
typedef void(*FUNHEAPIFY)(heap*, int);


typedef struct FUNCT{
    FUNHEAPIFY heapify;
    FUNHEAPMAX maxHeap;
    FUNHEAPEXTRMAX extractMaxHeap;
    FUNHEAPCHANGEPRI decreasePriorityHeap;
    FUNHEAPCHANGEPRI increasePriorityHeap;
    FUNHEAPDEL delKeyHeap;
    FUNHEAPINS insKeyHeap;
}FUNCT;

/***********************************************/

heap* makeArrayHeap(int n, heapNode*);
void heapifyArrayHeap(heap* H, int i);
heapNode* maxArrayHeap(heap* extr);
heapNode* extractMaxArrayHeap(heap* extr);
void decreasePriorityArrayHeap(heap* dec, int nEl, int newP);
void increasePriorityArrayHeap(heap* dec, int nEl, int newP);
heap* deleteKeyArrayHeap(heap* A,int i);
heap* insertKeyArrayHeap(heap* A, void*, int key);

/***********************************************/

heapABNode* makeHeapTreeNode(heapABNode* root, heapABNode* dad, void* toIns, int pri);
heapABNode* scrollTreeHeap(heap* HEAP, int n);

heap* makeTreeHeap(int n, heapNode*);
void heapifyTreeHeap(heap* root, int);
heapNode* maxTreeHeap(heap* HEAP);
heapNode* extractMaxTreeHeap(heap* HEAP);
void decreasePriorityTreeHeap(heap* HEAP, int pos, int nPri);
void increasePriorityTreeHeap(heap* HEAP, int pos, int nPri);
heap* deleteKeyTreeHeap(heap* HEAP, int i);
heap* insertKeyTreeHeap(heap* HEAP, void* elem, int key);
/**************************************************/

heap* makeHeap(int TYPE, int n, heapNode*);
void heapify(heap* toHeapify, int where);
heapNode* maxHeap(heap* see);
heapNode* extractMaxHeap(heap* toExtract);
void increasePriorityHeap(heap* HEAP, int toIncrease, int newPriority);
void decreasePriorityHeap(heap* HEAP, int toDecrease, int newPriority);
heap* deleteKeyHeap(heap* HEAP, int toDelete);
heap* insertKeyHeap(heap* HEAP, void* toInsert, int priority);


void printARB(heapABNode* ROOT){
    if(ROOT!=NULL){
        printf("\n%d", ROOT->element->priority);
        printf("\n%d sx: ");
        printARB(ROOT->sx);//, funList);
        printf("\n%d dx: ");
        printARB(ROOT->dx);//, funList);
    }
}

int main(){
    heap* k;
    heapNode array[7];
int i=0;
    for(i=0; i<7; i++){
        scanf("%d", &(array[i].priority));
        array[i].data=NULL;
    }

printf("\n");
    k=makeHeap(ARRAY_TYPE, 7, array);
    for(i=0; i<k->HEAPSIZE; i++){
        printf("%d\n", k->heapArray->HEAP[i].priority);
    }
    k=insertKeyHeap(k, NULL, 89);
    k=insertKeyHeap(k, NULL, 55);

printf("\n");
//    k=makeHeap(ARRAY_TYPE, 5, array);
    for(i=0; i<k->HEAPSIZE; i++){
        printf("%d\n", k->heapArray->HEAP[i].priority);
    }
    //printARB(k->heapTree->HEAPROOT);
  /*  k=insertKeyTreeHeap(k, NULL, 89);
    printf("\n\n\n\n");
/*/
   // printARB(k->heapTree->HEAPROOT);
/*
heapNode array[5];
int i=0;
    for(i=0; i<5; i++){
        scanf("%d", &(array[i].priority));
        array[i].data=NULL;
    }

k=makeArrayHeap(5, array);
printf("esc");
/*heapNode* p;//=maxArrayHeap(k);
printf("\n%d\n", p->priority);*/
    return 0;
}

FUNCT* initFuncHeap(int typeH){
    FUNCT* ret=(FUNCT*)malloc(sizeof(FUNCT));
    if(typeH==ARRAY_TYPE){
        ret->heapify=&heapifyArrayHeap;
        ret->maxHeap=&maxArrayHeap;
        ret->extractMaxHeap=&extractMaxArrayHeap;
        ret->increasePriorityHeap=&decreasePriorityArrayHeap;
        ret->decreasePriorityHeap=&increasePriorityArrayHeap;
        ret->insKeyHeap=&insertKeyArrayHeap;
        ret->delKeyHeap=&deleteKeyArrayHeap;
    }else if(typeH==TREE_TYPE){
        ret->decreasePriorityHeap=&decreasePriorityTreeHeap;
        ret->delKeyHeap=&deleteKeyTreeHeap;
        ret->extractMaxHeap=&extractMaxTreeHeap;
        ret->heapify=&heapifyTreeHeap;
        ret->increasePriorityHeap=&increasePriorityTreeHeap;
        ret->insKeyHeap=&insertKeyTreeHeap;
        ret->maxHeap=&maxTreeHeap;
    }
    return ret;
}


heap* makeHeap(int TYPE, int n, heapNode* array){
    heap* toMake=NULL;
    if(TYPE==ARRAY_TYPE){
        toMake=makeArrayHeap(n, array);
    }else if(TYPE==TREE_TYPE){
        toMake=makeTreeHeap(n, array);
    }
    return toMake;
}

void heapify(heap* toHeapify, int where){
    if(toHeapify!=NULL){
        if(toHeapify->function!=NULL){
            if(toHeapify->heaptype==ARRAY_TYPE){
                toHeapify->function->heapify(toHeapify, where-1);
            }else{
                toHeapify->function->heapify(toHeapify, where-1);
            }
        }
    }
}

heapNode* maxHeap(heap* see){
    heapNode* toRet=NULL;
    if(see!=NULL){
        if(see->function!=NULL){
            toRet=see->function->maxHeap(see);
        }
    }
    return toRet;
}

heapNode* extractMaxHeap(heap* toExtract){
    heapNode* extracted=NULL;
    if(toExtract!=NULL){
        if(toExtract->function!=NULL){
            extracted=toExtract->function->extractMaxHeap(toExtract);
        }
    }
    return extracted;
}

void increasePriorityHeap(heap* HEAP, int toIncrease, int newPriority){
    if(HEAP!=NULL){
        if(HEAP->function!=NULL){
            HEAP->function->increasePriorityHeap(HEAP, toIncrease, newPriority);
        }
    }
}
void decreasePriorityHeap(heap* HEAP, int toDecrease, int newPriority){
    if(HEAP!=NULL){
        if(HEAP->function!=NULL){
            HEAP->function->decreasePriorityHeap(HEAP, toDecrease, newPriority);
        }
    }
}

heap* deleteKeyHeap(heap* HEAP, int toDelete){
    if(HEAP!=NULL){
        if(HEAP->function!=NULL){
            HEAP=HEAP->function->delKeyHeap(HEAP, toDelete);
        }
    }
    return HEAP;
}

heap* insertKeyHeap(heap* HEAP, void* toInsert, int priority){
    if(HEAP!=NULL){
        if(HEAP->function!=NULL){
            HEAP=HEAP->function->insKeyHeap(HEAP, toInsert, priority);
        }
    }
    return HEAP;
}

heap* makeArrayHeap(int n, heapNode array[]){
    heap* ret;
    int i, p, el=1;
    i=n;
    while(i>0){
        i=i/2;
        el=el*2;
    }
    ret=(heap*)malloc(sizeof(heap));
    ret->heapTree=NULL;
    ret->heapArray=(ARRAYHEAP*)malloc(sizeof(ARRAYHEAP));
    ret->HEAPSIZE=n;
    ret->heapArray->HEAPDIM=el;
    ret->heapArray->HEAP=(heapNode*)malloc(sizeof(heapNode)*el);
    ret->function=initFuncHeap(ARRAY_TYPE);
    ret->heaptype=ARRAY_TYPE;
    for(i=0; i<n; i++){
        ret->heapArray->HEAP[i].priority=array[i].priority;
        ret->heapArray->HEAP[i].data=array[i].data;
    }
    for(i=(n/2); i>=0; i--){
        heapifyArrayHeap(ret,i);
    }
    return ret;
}

void heapifyArrayHeap(heap* H, int i){
    if(i>=0){
        int l, r, max=i;
        l=left(i);
        r=right(i);
        heapNode temp;
        heapNode* work=H->heapArray->HEAP;
        if(l<(H->HEAPSIZE) && (work[l].priority>work[i].priority)){
            max=l;
        }
        if(r<(H->HEAPSIZE) && (work[r].priority>work[max].priority)){
            max=r;
        }
        if(max!=i){
            temp=work[i];
            work[i]=work[max];
            work[max]=temp;
            heapifyArrayHeap(H, max);
        }
    }
}


int right(int i){
    return (2*i);
}

int left(int i){
    return (2*(i+1))-1;
}

int dad(int i){
    return ((i+1)/2)-1;
}


heapNode* maxArrayHeap(heap* extr){
    if(extr->HEAPSIZE<1)
        return NULL;
    else return extr->heapArray->HEAP+(0);
}

heapNode* extractMaxArrayHeap(heap* extr){
    heapNode* ret=NULL;
    heapNode* temp=maxArrayHeap(extr);
    if(temp!=NULL){
        ret=(heapNode*)malloc(sizeof(heapNode));
        ret->data=temp->data;
        ret->priority=temp->priority;
        extr->heapArray->HEAP[0]=extr->heapArray->HEAP[--(extr->HEAPSIZE)];
        heapifyArrayHeap(extr, 0);
    }
    return ret;
}

void decreasePriorityArrayHeap(heap* dec, int nEl, int newP){
    heapNode temp;
    int i=nEl;
    if(dec->heapArray->HEAP[nEl].priority>newP){
        dec->heapArray->HEAP[nEl].priority=newP;
        heapifyArrayHeap(dec, nEl);
    }
}

void increasePriorityArrayHeap(heap* dec, int nEl, int newP){
    heapNode temp;
    int i=nEl;
    if(dec->heapArray->HEAP[nEl].priority<newP){
        dec->heapArray->HEAP[nEl].priority=newP;
        heapifyArrayHeap(dec, nEl);
        while(i>=0 && dec->heapArray->HEAP[dad(i)].priority<dec->heapArray->HEAP[i].priority){
            temp=dec->heapArray->HEAP[dad(i)];
            dec->heapArray->HEAP[dad(i)]=dec->heapArray->HEAP[i];
            dec->heapArray->HEAP[i]=temp;
            i=dad(i);
        }
    }
}

heap* insertKeyArrayHeap(heap* A, void* ele, int key){
    heapNode*t=NULL;
    int i;
    A->HEAPSIZE++;
    if(A->HEAPSIZE>A->heapArray->HEAPDIM){
        A->heapArray->HEAPDIM=A->heapArray->HEAPDIM*2;
        //t=(heapNode*)realloc(sizeof(heapNode)*A->heapArray->HEAPDIM);
        A->heapArray->HEAP=(heapNode*)realloc(A->heapArray->HEAP, sizeof(heapNode)*A->heapArray->HEAPDIM);
        /*for(i=0; i<A->HEAPSIZE; i++){
            t[i]=A->heapArray->HEAP[i];
        }
        A->heapArray->HEAP=t;*/
    }
    A->heapArray->HEAP[A->HEAPSIZE-1].data=ele;
    A->heapArray->HEAP[A->HEAPSIZE-1].priority=-1;
    increasePriorityArrayHeap(A, A->HEAPSIZE-1, key);
    return A;
}

heap* deleteKeyArrayHeap(heap* A,int i){
    heapNode temp;
    if(A->HEAPSIZE>0 && i<=A->HEAPSIZE){
        temp.data=A->heapArray->HEAP[i].data;
        A->heapArray->HEAP[A->HEAPSIZE-1].data=A->heapArray->HEAP[i].data;
        A->heapArray->HEAP[i].data=temp.data;
        if(A->heapArray->HEAP[A->HEAPSIZE-1].priority>A->heapArray->HEAP[i].priority){
            increasePriorityArrayHeap(A, i, A->heapArray->HEAP[A->HEAPSIZE-1].priority);
        }else{
            decreasePriorityArrayHeap(A, i, A->heapArray->HEAP[A->HEAPSIZE-1].priority);
        }
        A->HEAPSIZE--;
    }
    return A;
}





/**********************
***********************
***********************
***********************
***********************
***********************
***********************
***********************
**********************/




heap* makeTreeHeap(int n, heapNode* array){
    heap* ret=(heap*)malloc(sizeof(heap));
    ret->HEAPSIZE=n;
    ret->heapTree=(ABHEAP*)malloc(sizeof(ABHEAP));
    ret->heapArray=NULL;
    ret->heapTree->HEAPROOT=NULL;
    ret->heaptype=TREE_TYPE;
    ret->function=initFuncHeap(TREE_TYPE);
    heapABNode* scroll=ret->heapTree->HEAPROOT;
    heapABNode* dad=NULL;
    int i=0, k, curr, dir;
    char pointer[33];
    curr=1;
    int pri;
    while(n>=curr){
        dad=NULL;
        scroll=ret->heapTree->HEAPROOT;
        itoa(curr, pointer, 2);
        int i=strlen(pointer);
        k=1;
        if(i>1){
            while(i>k){
                if(pointer[k]=='1'){
                    dad=scroll;
                    scroll=scroll->dx;
                }else if(pointer[k]=='0'){
                    dad=scroll;
                    scroll=scroll->sx;
                }
                k++;
            }
            if(pointer[k-1]=='1'){
                /****************array[curr].data vorrei fare la copia più che dare l'indirizzo****/
                dad->dx=makeHeapTreeNode(scroll, dad, array[curr].data, array[curr].priority);
            }else if(pointer[k-1]=='0'){
                dad->sx=makeHeapTreeNode(scroll, dad, array[curr].data, array[curr].priority);
            }
        }else{
            ret->heapTree->HEAPROOT=makeHeapTreeNode(ret->heapTree->HEAPROOT, dad, array[curr].data, array[curr].priority);
        }
        curr++;
    }
    int j=(ret->HEAPSIZE)/2;
    for(j; j>=1; j--){
        heapifyTreeHeap(ret, j);
    }
    return ret;
}

heapABNode* makeHeapTreeNode(heapABNode* root, heapABNode* dad, void* toIns, int pri){
    root=(heapABNode*)malloc(sizeof(heapABNode));
    root->element=(heapNode*)malloc(sizeof(heapNode));
    root->element->data=toIns;
    root->element->priority=pri;
    root->dx=NULL;
    root->sx=NULL;
    root->dad=dad;
    return root;
}

void heapifyTreeHeap(heap* toHeap, int j){
    if(j>=0){
        heapABNode* leftNode=NULL;
        int pifyNum=j;
        heapABNode* rightNode=NULL;
        heapABNode* root=scrollTreeHeap(toHeap, j);
        heapABNode* max=root;
        heapNode* temp;
        if(root!=NULL){
            leftNode=root->sx;
            rightNode=root->dx;
            if(leftNode!=NULL && leftNode->element->priority>max->element->priority){
                max=leftNode;
                pifyNum=j*2;
            }else max=root;
            if(rightNode!=NULL && rightNode->element->priority>max->element->priority){
                max=rightNode;
                pifyNum=(j*2)+1;
            }
            if(max!=root){
                temp=max->element;
                max->element=root->element;
                root->element=temp;
                heapifyTreeHeap(toHeap,pifyNum);
            }
        }
    }
}


heapABNode* scrollTreeHeap(heap* HEAP, int n){
    int k, i;
    heapABNode* scroll=NULL;
    char pointer[33];
    if(n<=HEAP->HEAPSIZE && n>0){
        scroll=HEAP->heapTree->HEAPROOT;
        itoa(n, pointer, 2);
        int i=strlen(pointer);
        k=1;
        if(i>1){
            while(i>k){
                if(pointer[k]=='1'){
                    scroll=scroll->dx;
                }else if(pointer[k]=='0'){
                    scroll=scroll->sx;
                }
                k++;
            }
        }
    }
    return scroll;
}

heapNode* maxTreeHeap(heap* HEAP){
    if(HEAP!=NULL){
        return HEAP->heapTree->HEAPROOT->element;
    }else return NULL;
}

heapNode* extractMaxTreeHeap(heap* HEAP){
    heapABNode* max=NULL;
    heapNode* temp;
    heapABNode* swi;
    int n;
    if(HEAP!=NULL){
        max=scrollTreeHeap(HEAP, HEAP->HEAPSIZE);
        if(swi!=NULL){
            temp=max->element;
            max->element=HEAP->heapTree->HEAPROOT->element;
            HEAP->heapTree->HEAPROOT->element=temp;
            HEAP->HEAPSIZE=HEAP->HEAPSIZE-1;
            if(max==max->dad->dx){
                max->dad->dx=NULL;
            }else{
                max->dad->sx=NULL;
            }
            heapifyTreeHeap(HEAP, 1);
        }
    }
    heapNode* t=max->element;
    free(max);
    return t;
}



void decreasePriorityTreeHeap(heap* HEAP, int pos, int nPri){
    heapABNode* toChange=scrollTreeHeap(HEAP, pos);
    if(toChange!=NULL){
        if(toChange->element->priority>nPri){
            toChange->element->priority=nPri;
            heapifyTreeHeap(HEAP, pos);
        }
    }
}

void increasePriorityTreeHeap(heap* HEAP, int pos, int nPri){
    heapABNode* toChange=scrollTreeHeap(HEAP, pos);
    heapNode* temp;
    if(toChange!=NULL){
        if(toChange->element->priority<nPri){
            toChange->element->priority=nPri;
            while(toChange!=NULL && toChange->dad!=NULL && toChange->dad->element->priority<toChange->element->priority){
                temp=toChange->element;
                toChange->element=toChange->dad->element;
                toChange->dad->element=temp;
                toChange=toChange->dad;
            }
        }
    }
}


heap* deleteKeyTreeHeap(heap* HEAP, int i){
    heapABNode* toDel=NULL;
    heapABNode* toReplace=NULL;
    heapABNode* newLast=NULL;
    heapNode* temp=NULL;
    i++;
    if(HEAP!=NULL && i>0){
        toDel=scrollTreeHeap(HEAP, i);
        if(toDel!=NULL){
            toReplace=scrollTreeHeap(HEAP, HEAP->HEAPSIZE);
            if(toReplace!=NULL){
                temp=toDel->element;
                toDel->element=toReplace->element;
                toReplace->element=temp;
                if(toReplace->dad->dx==toReplace){
                    toReplace->dad->dx=NULL;
                }else{
                    toReplace->dad->sx=NULL;
                }
                HEAP->HEAPSIZE=HEAP->HEAPSIZE-1;
                heapifyTreeHeap(HEAP, i);
                free(toReplace->element);
                free(toReplace);
            }
        }
    }
    return HEAP;
}


heap* insertKeyTreeHeap(heap* HEAP, void* elem, int key){
    int n;
    heapABNode* dad=NULL;
    if(HEAP->HEAPSIZE==0){
        HEAP->heapTree->HEAPROOT=makeHeapTreeNode(HEAP->heapTree->HEAPROOT, NULL, elem, -1);
    }else{
        n=((HEAP->HEAPSIZE)+1)/2;
        dad=scrollTreeHeap(HEAP, n);
        if(dad->sx==NULL){
            dad->sx=makeHeapTreeNode(dad->sx, dad, elem, -1);
        }else if(dad->dx==NULL){
            dad->dx=makeHeapTreeNode(dad->dx, dad, elem, -1);
        }
    }
    HEAP->HEAPSIZE++;
    increasePriorityTreeHeap(HEAP, HEAP->HEAPSIZE, key);
    return HEAP;
}
