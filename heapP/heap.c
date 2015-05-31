#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABR.h"
#include "data.h"


#ifndef _HEAP_H_
    #define _HEAP_H_

    #include "heap.h"

#endif // _HEAP_H_



FUNCTDATA* initFunctInfo(){
    FUNCTDATA* ret=initFUNCTDATA();
    ret->funfree=&freeInfo;
    ret->fins=&insertInfo;
    ret->fcopy=&copyInfo;
    return ret;
}

functHeap* initFunctHeap(heapType type, orderHeapType order){
    functHeap* toInit=(functHeap*)malloc(sizeof(functHeap));
    if(type==HEAP_TREE){
        toInit->decreaseHeapSize=&decreaseHeapSizeTree;
        toInit->insertElement=&insertElementTree;
        toInit->nodeFromHeap=&fromTreeHeap;
        toInit->deleteHeap=&freeTree;
    }
    if(type==HEAP_ARRAY){
        toInit->decreaseHeapSize=&decreaseHeapSizeArray;
        toInit->insertElement=&insertElementArray;
        toInit->nodeFromHeap=&fromArrayHeap;
        toInit->deleteHeap=&freeArray;
    }
    if(order==MIN_HEAP){
        toInit->compare=&comparaMin;
    }
    if(order==MAX_HEAP){
        toInit->compare=&comparaMax;
    }
    toInit->getPriority=&randomPriority;
    return toInit;
}



HEAP* initHEAP(heapType type, orderHeapType order){
    HEAP* toInit=(HEAP*)malloc(sizeof(HEAP));
    toInit->functions=initFunctHeap(type, order);
    toInit->heap=NULL;
    toInit->heapSize=0;
    toInit->infoFunctions=initFunctInfo();
    return toInit;
}

void heapify(HEAP* theHeap, int where){
    int sx=where*2;
    int dx=where*2+1;
    int max;
    if(theHeap!=NULL){
        if(theHeap->heap!=NULL && where>0){
            if(sx<=theHeap->heapSize && theHeap->functions->compare(getHeapNode(theHeap, sx), getHeapNode(theHeap, where))){
                max=sx;
            }else max=where;
            if(dx<=theHeap->heapSize && theHeap->functions->compare(getHeapNode(theHeap, dx), getHeapNode(theHeap, max))){
                max=dx;
            }
            if(max!=where){
                swapHeapNode(getHeapNode(theHeap, where), getHeapNode(theHeap, max));
                heapify(theHeap, max);
            }
        }
    }
}


HEAP* insertHeap(HEAP* theHeap, void* elem){
    if(theHeap!=NULL){
        void* toIns;
        int i=0;
        theHeap->heapSize++;
        theHeap->functions->insertElement(theHeap, theHeap->infoFunctions->fcopy(elem, toIns), theHeap->functions->getPriority(elem));
        for(i=theHeap->heapSize/2; i>0; i=i/2){
            heapify(theHeap, i);
        }
    }
    return theHeap;
}


void decreaseKeyHeap(HEAP* theHeap, int pos, int nkey){
    heapNode* toDec=getHeapNode(theHeap, pos);
    if(theHeap!=NULL){
        if(theHeap->heap!=NULL){
            if(toDec!=NULL){
                if(nkey<toDec->priority){
                    toDec->priority=nkey;
                    heapify(theHeap, pos);
                }
            }
        }
    }
}

void increaseKeyHeap(HEAP* theHeap, int pos, int nkey){
    heapNode* toInc=getHeapNode(theHeap, pos);
    if(toInc!=NULL){
        if(nkey>toInc->priority){
            toInc->priority=nkey;
        }
        pos=(pos)/2;
        heapNode* dad=getHeapNode(theHeap, pos);
        while(dad!=NULL && dad->priority<toInc->priority){
            swapHeapNode(dad, toInc);
            toInc=dad;
            pos=(pos)/2;
            dad=getHeapNode(theHeap, pos);
        }
    }
}

heapNode* getHeapNode(HEAP* theHeap, int pos){
    if(theHeap!=NULL){
        if(theHeap->heap!=NULL){
            if(theHeap->heapSize>=pos && pos>0){
                return theHeap->functions->nodeFromHeap(theHeap, pos);
            }
        }return NULL;
    }return NULL;
}

void swapHeapNode(heapNode* a, heapNode* b){
    void* infot;
    int priot;
    if(a!=NULL && b!=NULL){
        infot=a->info;
        a->info=b->info;
        b->info=infot;
        priot=a->priority;
        a->priority=b->priority;
        b->priority=priot;
    }
}

heapNode* firstHeap(HEAP* theHeap){
    if(theHeap!=NULL){
        if(theHeap->heapSize>0){
            return getHeapNode(theHeap, 1);
        }
    }return NULL;
}

heapNode* extractFirstHeap(HEAP* theHeap){
    heapNode* firstNode;
    heapNode* ret;
    if(theHeap!=NULL){
        if(theHeap->heapSize<1){
            return NULL;
        }else{
            ret=(heapNode*)malloc(sizeof(heapNode));
            firstNode=firstHeap(theHeap);
            /**remove last**/
            ret->info=firstNode->info;
            ret->priority=firstNode->priority;
            firstNode->info=getHeapNode(theHeap, theHeap->heapSize)->info;
            firstNode->priority=getHeapNode(theHeap, theHeap->heapSize)->priority;
            /****/
            theHeap->functions->decreaseHeapSize(theHeap);
            /****/
            heapify(theHeap, 1);
            return ret;
        }
    }return NULL;
}

void decreaseHeapSizeTree(HEAP* theHeap){
    ARB* dad=scrollHeapTree((ARB*)(theHeap->heap), theHeap->heapSize/2);
    ARB* toF;
    heapNode* htf;
    if(theHeap!=NULL){
        if(dad==NULL){
            toF=((ARB*)(theHeap->heap));
            htf=((heapNode*)(toF->element));
            theHeap->heap=NULL;
        }else if(dad->dx!=NULL){
            toF=dad->dx;
            htf=((heapNode*)(dad->dx->element));
            dad->dx=NULL;
        }else{
            toF=dad->sx;
            htf=((heapNode*)(dad->sx->element));
            dad->sx=NULL;
        }

        theHeap->infoFunctions->funfree(htf->info);
        free(htf);
        free(dad->dx);

        theHeap->heapSize--;
    }
}



void decreaseHeapSizeArray(HEAP* theHeap){
    theHeap->heapSize--;
    arrayHeap* temp=(arrayHeap*)(theHeap->heap);
    free((temp->array+(theHeap->heapSize))->info);
}

void deleteKeyHeap(HEAP* theHeap, int i){
    if(theHeap!=NULL){
        if(theHeap->heap!=NULL){
            if(theHeap->heapSize>0){
                if(getHeapNode(theHeap, theHeap->heapSize)->priority>getHeapNode(theHeap, i)->priority){
                    increaseKeyHeap(theHeap, i, getHeapNode(theHeap, theHeap->heapSize)->priority);
                }else{
                    decreaseKeyHeap(theHeap, i, getHeapNode(theHeap, theHeap->heapSize)->priority);
                }
                theHeap->functions->decreaseHeapSize(theHeap);
            }
        }
    }
}

ARB* makeHeapTreeNode(ARB* toCreate, ARB* dad, void* toAttach){
    toCreate=(ARB*)malloc(sizeof(ARB));
    toCreate->dx=NULL;
    toCreate->sx=NULL;
    toCreate->element=(toAttach);
    return toCreate;
}


ARB* scrollHeapTree(ARB* ROOT, int n){
    ARB* ret=NULL;
    int k;
    int i;
    char pointer[33];
    if(ROOT!=NULL){
        if(n>0){
            ret=ROOT;
            itoa(n, pointer, 2);
            i=strlen(pointer);
            k=1;
            if(i>1){
                while(i>k && ret!=NULL){
                    if(pointer[k]=='1'){
                        ret=ret->dx;
                    }else if(pointer[k]=='0'){
                        ret=ret->sx;
                    }
                    k++;
                }
            }
        }
    }
    return ret;
}


heapNode* fromTreeHeap(HEAP* theHeap, int pos){
    ARB*ret=scrollHeapTree((ARB*)(theHeap->heap), pos);
    if(ret!=NULL){
        return ret->element;
    }else {
        return NULL;
    }
}

heapNode* fromArrayHeap(HEAP* theHeap, int pos){
    if(pos>0 && pos<=theHeap->heapSize){
        return(((arrayHeap*)(theHeap->heap))->array)+(pos-1);
    }else return NULL;
}


void increaseHeapSizeArray(HEAP* theHeap){
    if(theHeap!=NULL){
        if(theHeap->heap==NULL){
            theHeap->heapSize++;
        }
    }
}

void increaseHeapSizeTree(HEAP* theHeap){
    if(theHeap!=NULL){
        theHeap->heapSize=theHeap->heapSize+1;
    }
}

void insertElementArray(HEAP* theHeap, void* elem, int priority){
    if(theHeap!=NULL){
        if(theHeap->heap==NULL){
            theHeap->heap=(arrayHeap*)malloc(sizeof(arrayHeap)*theHeap->heapSize);
            ((arrayHeap*)(theHeap->heap))->arraySize=0;
            ((arrayHeap*)(theHeap->heap))->array=NULL;
        }
        if(((arrayHeap*)(theHeap->heap))->array==NULL){
            ((arrayHeap*)(theHeap->heap))->array=(heapNode*)malloc(sizeof(heapNode)*1);
            ((arrayHeap*)(theHeap->heap))->arraySize=1;
            theHeap->heapSize=1;
        }
        if(((arrayHeap*)(theHeap->heap))->arraySize<=theHeap->heapSize){
            ((arrayHeap*)(theHeap->heap))->arraySize=((((arrayHeap*)(theHeap->heap))->arraySize)*2)+1;
            ((arrayHeap*)(theHeap->heap))->array=(heapNode*)realloc(((arrayHeap*)(theHeap->heap))->array, sizeof(heapNode)*(((arrayHeap*)(theHeap->heap))->arraySize));
        }
        ((arrayHeap*)(theHeap->heap))->array[theHeap->heapSize-1].info=elem;
        ((arrayHeap*)(theHeap->heap))->array[theHeap->heapSize-1].priority=priority;
    }
}


void insertElementTree(HEAP* theHeap, void* elem, int priority){
    ARB* t;
    ARB* dad=NULL;
    void* toAttach;
    int s;
    if(theHeap!=NULL){
        t=(ARB*)(theHeap->heap);
        /*toAttach=(heapNode*)malloc(sizeof(heapNode));
        ((heapNode*)(toAttach))->info=elem;
        ((heapNode*)(toAttach))->priority=priority;*/
        toAttach=(void*)(insertHeapNode(elem, priority));
        s=theHeap->heapSize;
        if(theHeap->heap==NULL){
            t=makeHeapTreeNode(t,dad, toAttach);
            (theHeap->heap)=(void*)t;
        }else{
            dad=scrollHeapTree(t, s/2);
            if(dad->sx==NULL){
                dad->sx=makeHeapTreeNode(dad->sx,dad, toAttach);
            }else if(dad->dx==NULL){
                dad->dx=makeHeapTreeNode(dad->dx,dad, toAttach);
            }
        }
    }
}


int comparaMax(heapNode* a, heapNode* b){
    if(a!=NULL && b!=NULL){
        if(a->priority>b->priority){
            return 1;
        }
    }return 0;
}

int comparaMin(heapNode* a, heapNode* b){
    if(a!=NULL && b!=NULL){
        if(a->priority<b->priority){
            return 1;
        }
    }return 0;
}

int randomPriority(void* ret){
    int i=rand()%25;
//    printf("%d ", i);
    return i;
}
/***data functions***/
void* insertInfo(){
    return NULL;
}

void* copyInfo(void* original, void* copy){
    return NULL;
}

void freeInfo(void* toFree){
    free(toFree);
}


/*************MANCA LA DEALLOCAZIONE*****************/
/*********PROBABILMENTE INSERISCO UN ALTRO FUNCTDATA*************/

void* freeHeapNode(void* toFree, FUNDEL funfree){
    if(toFree!=NULL){
        funfree(((heapNode*)toFree)->info);
        free((heapNode*)toFree);
    }
    return NULL;
}

void* freeARB(HEAP* theHeap, ARB* toDel){
    if(toDel!=NULL){
        toDel->dx=freeARB(theHeap, toDel->dx);
        toDel->sx=freeARB(theHeap, toDel->sx);
        toDel->element=freeHeapNode(toDel->element, theHeap->infoFunctions->funfree);
        free(toDel);
        toDel=NULL;
    }
    return toDel;
}

void* freeTree(HEAP* theHeap){
    if(theHeap!=NULL){
        if(theHeap->heap!=NULL){
            theHeap->heap=freeARB(theHeap, (ARB*)(theHeap->heap));
        }
    }
    return NULL;
}

void* freeArray(HEAP* theHeap){
    int i;
    arrayHeap* toDel=NULL;
    if(theHeap!=NULL){
        if(theHeap->heap!=NULL){
            toDel=(arrayHeap*)(theHeap->heap);
            for(i=0; i<theHeap->heapSize; i++){
                theHeap->infoFunctions->funfree((toDel->array+i)->info);
            }
            free((arrayHeap*)(theHeap->heap));
        }
    }
    return NULL;
}

void* freeHeap(HEAP* theHeap){
    if(theHeap!=NULL){
        theHeap->heap=theHeap->functions->deleteHeap(theHeap);
        deleteFUNCTDATA(theHeap->infoFunctions);
        free(theHeap);
    }
    return NULL;
}


heapNode* insertHeapNode(void* info, int priority){
    heapNode* ret=(heapNode*)malloc(sizeof(heapNode));
    ret->info=info;
    ret->priority=priority;
    return ret;
}
