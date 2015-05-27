#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

#ifndef _HEAP_H_

    #define _HEAP_H_

    #include "heap.h"

#endif // _HEAP_H_

/***********************************/

/*************************************/

#ifndef _GEST_FUNCTHEAP_

#define _GEST_FUNCTHEAP_

FUNCTHEAP* initFuncHeap(heapType typeH){
    FUNCTHEAP* ret=(FUNCTHEAP*)malloc(sizeof(FUNCTHEAP));
    if(typeH==ARRAY_TYPE){
        ret->heapify=&heapifyArrayHeap;
        ret->maxHeap=&maxArrayHeap;
        ret->extractMaxHeap=&extractMaxArrayHeap;
        ret->increasePriorityHeap=&decreasePriorityArrayHeap;
        ret->decreasePriorityHeap=&increasePriorityArrayHeap;
        ret->insKeyHeap=&insertKeyArrayHeap;
        ret->delKeyHeap=&deleteKeyArrayHeap;
        ret->freeOnlyHeap=&freeArrayHeap;
        ret->freeAll=&freeArrayHeapWithElements;
    }else if(typeH==TREE_TYPE){
        ret->decreasePriorityHeap=&decreasePriorityTreeHeap;
        ret->delKeyHeap=&deleteKeyTreeHeap;
        ret->extractMaxHeap=&extractMaxTreeHeap;
        ret->heapify=&heapifyTreeHeap;
        ret->increasePriorityHeap=&increasePriorityTreeHeap;
        ret->insKeyHeap=&insertKeyTreeHeap;
        ret->maxHeap=&maxTreeHeap;
        ret->freeOnlyHeap=&freeTreeHeap;
        ret->freeAll=&freeTreeHeapWithElements;
    }
    return ret;
}

FUNCTHEAP* deleteFuncHeap(FUNCTHEAP* toDel){
    free(toDel);
    return NULL;
}

#endif // _GEST_FUNCTHEAP_


heap* makeHeap(heapType TYPE, int n, heapNode* array, FUNCPY fcopy){
    heap* toMake=NULL;
    if(TYPE==ARRAY_TYPE){
        toMake=makeArrayHeap(n, array, fcopy);
    }else if(TYPE==TREE_TYPE){
        toMake=makeTreeHeap(n, array, fcopy);
    }
    return toMake;
}

void heapify(heap* toHeapify, int where){
    if(toHeapify!=NULL){
        if(toHeapify->function!=NULL){
            if(toHeapify->type==ARRAY_TYPE){
                toHeapify->function->heapify(toHeapify, where-1);
            }else if(toHeapify->type==TREE_TYPE){
                toHeapify->function->heapify(toHeapify, where);
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

heap* insertKeyHeap(heap* HEAP, void* toInsert, int priority, FUNCPY fcopy){
    if(HEAP!=NULL){
        if(HEAP->function!=NULL){
            HEAP=HEAP->function->insKeyHeap(HEAP, toInsert, priority, fcopy);
        }
    }
    return HEAP;
}

heap* freeHeap(heap* toFree){
    if(toFree!=NULL){
        if(toFree->function!=NULL){
            toFree=toFree->function->freeOnlyHeap(toFree);
        }
    }
    return toFree;
}

heap* freeHeapWithElements(heap* toFree, FUNDEL FDEL){
    if(toFree!=NULL){
        if(toFree->function!=NULL){
            toFree=toFree->function->freeAll(toFree, FDEL);
        }
    }
    return toFree;
}

/*****/

heap* makeArrayHeap(int n, heapNode array[], FUNCPY fcopy){
    heap* ret;
    int i, el=1;
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
    ret->type=ARRAY_TYPE;
    for(i=0; i<n; i++){
        ret->heapArray->HEAP[i].priority=array[i].priority;
        ret->heapArray->HEAP[i].data=fcopy(ret->heapArray->HEAP[i].data, array[i].data);
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

heap* insertKeyArrayHeap(heap* A, void* ele, int key, FUNCPY fcopy){
    A->HEAPSIZE++;
    if(A->HEAPSIZE>A->heapArray->HEAPDIM){
        A->heapArray->HEAPDIM=A->heapArray->HEAPDIM*2;
        A->heapArray->HEAP=(heapNode*)realloc(A->heapArray->HEAP, sizeof(heapNode)*A->heapArray->HEAPDIM);
    }
    A->heapArray->HEAP[A->HEAPSIZE-1].data=fcopy(A->heapArray->HEAP[A->HEAPSIZE-1].data, ele);
    A->heapArray->HEAP[A->HEAPSIZE-1].priority=-1;
    increasePriorityArrayHeap(A, A->HEAPSIZE-1, key);
    return A;
}

/**cancella il nodo, ma non dealloca l'elemento alocato nell'HEAP**/
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

heap* freeArrayHeap(heap* toFree){
    int i=0;
    if(toFree!=NULL){
        for(i=0; i<toFree->HEAPSIZE; i++){
            free((toFree->heapArray->HEAP)+i);
        }
        free(toFree->heapArray);
        deleteFuncHeap(toFree->function);
        free(toFree);
        toFree=NULL;
    }
    return toFree;
}

heap* freeArrayHeapWithElements(heap* toFree, FUNDEL FDEL){
    int i=0;
    if(toFree!=NULL){
        for(i=0; i<toFree->HEAPSIZE; i++){
            FDEL(toFree->heapArray->HEAP[i].data);
            free((toFree->heapArray->HEAP)+i);
        }
        free(toFree->heapArray);
        free(toFree->function);
        free(toFree);
        toFree=NULL;
    }
    return toFree;
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




heap* makeTreeHeap(int n, heapNode* array, FUNCPY fcopy){
    heap* ret=(heap*)malloc(sizeof(heap));
    ret->HEAPSIZE=n;
    ret->heapTree=(ABHEAP*)malloc(sizeof(ABHEAP));
    ret->heapArray=NULL;
    ret->heapTree->HEAPROOT=NULL;
    ret->type=TREE_TYPE;
    ret->function=initFuncHeap(TREE_TYPE);
    heapABNode* scroll=ret->heapTree->HEAPROOT;
    heapABNode* dad=NULL;
    int j, k, curr;
    char pointer[33];
    curr=1;
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
                dad->dx=makeHeapTreeNode(scroll, dad, array[curr].data, array[curr].priority, fcopy);
            }else if(pointer[k-1]=='0'){
                dad->sx=makeHeapTreeNode(scroll, dad, array[curr].data, array[curr].priority, fcopy);
            }
        }else{
            ret->heapTree->HEAPROOT=makeHeapTreeNode(ret->heapTree->HEAPROOT, dad, array[curr].data, array[curr].priority, fcopy);
        }
        curr++;
    }

    for(j=(ret->HEAPSIZE)/2; j>0; j--){
        heapifyTreeHeap(ret, j);
    }
    return ret;
}

heapABNode* makeHeapTreeNode(heapABNode* root, heapABNode* dad, void* toIns, int pri, FUNCPY fcopy){
    root=(heapABNode*)malloc(sizeof(heapABNode));
    root->element=(heapNode*)malloc(sizeof(heapNode));
    root->element->data=fcopy(root->element->data, toIns);
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
    int k;
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
    if(HEAP!=NULL){
        swi=HEAP->heapTree->HEAPROOT;
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
                free(toReplace);
            }
        }
    }
    return HEAP;
}


heap* insertKeyTreeHeap(heap* HEAP, void* elem, int key, FUNCPY fcopy){
    int n;
    heapABNode* dad=NULL;
    if(HEAP->HEAPSIZE==0){
        HEAP->heapTree->HEAPROOT=makeHeapTreeNode(HEAP->heapTree->HEAPROOT, NULL, elem, -1, fcopy);
    }else{
        n=((HEAP->HEAPSIZE)+1)/2;
        dad=scrollTreeHeap(HEAP, n);
        if(dad->sx==NULL){
            dad->sx=makeHeapTreeNode(dad->sx, dad, elem, -1, fcopy);
        }else if(dad->dx==NULL){
            dad->dx=makeHeapTreeNode(dad->dx, dad, elem, -1, fcopy);
        }
    }
    HEAP->HEAPSIZE++;
    increasePriorityTreeHeap(HEAP, HEAP->HEAPSIZE, key);
    return HEAP;
}

heapABNode* freeTWE(heapABNode* nodeToFree, FUNDEL FDEL){
    if(nodeToFree!=NULL){
        nodeToFree->dx=freeTWE(nodeToFree->dx, FDEL);
        nodeToFree->sx=freeTWE(nodeToFree->sx, FDEL);
        FDEL(nodeToFree->element->data);
        free(nodeToFree->element);
        free(nodeToFree);
        nodeToFree=NULL;
    }
    return nodeToFree;
}

heap* freeTreeHeapWithElements(heap* toFree, FUNDEL FDEL){
    if(toFree!=NULL){
        freeTWE(toFree->heapTree->HEAPROOT, FDEL);
        free(toFree->heapTree);
        deleteFuncHeap(toFree->function);
        free(toFree);
        toFree=NULL;
    }
    return toFree;
}

heapABNode* freeT(heapABNode* nodeToFree){
    if(nodeToFree!=NULL){
        freeT(nodeToFree->dx);
        freeT(nodeToFree->sx);
        free(nodeToFree);
        nodeToFree=NULL;
    }
    return nodeToFree;
}

heap* freeTreeHeap(heap* toFree){
    if(toFree!=NULL){
        freeT(toFree->heapTree->HEAPROOT);
        free(toFree->heapTree);
        deleteFuncHeap(toFree->function);
        free(toFree);
        toFree=NULL;
    }
    return toFree;
}

