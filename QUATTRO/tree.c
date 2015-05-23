
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARRAY_TYPE 0
#define TREE_TYPE 1

typedef struct heapNode{
    void* data;
    int priority;
}heapNode;

typedef struct heapArray{
    heapNode* array;
    struct FUNCT* function;
    int HEAPDIM;
}heapArray;

typedef struct heapABNode{
    struct heapABNode* dad;
    struct heapABNode* sx;
    struct heapABNode* dx;
    heapNode* element;
}heapABNode;

typedef struct heapABTree{
    heapABNode* tree;
    struct FUNCT* function;
}heapABTree;

typedef struct heapType{
    heapArray* HEAPARRAY;
    heapABTree* HEAPROOT;
    int heaptype;
}heapType;

typedef struct heap{
    heapType* HEAP;
    int HEAPSIZE;
}heap;

typedef heap*(*FUNHEAPINS)(heap*, void*, int);
typedef heap*(*FUNHEAPDEL)(heap*, int);
typedef heapNode*(*FUNHEAPMAX)(heap*);
typedef heapNode*(*FUNHEAPEXTRMAX)(heap*);
typedef void(*FUNHEAPCHANGEPRI)(heap*, int, int);
typedef void(*FUNHEAPIFY)(heap*, int);



typedef struct FUNCT{
    FUNHEAPINS insHeap;
    FUNHEAPDEL delHeap;
    FUNHEAPMAX maxHeap;
    FUNHEAPEXTRMAX extractMaxHeap;
    FUNHEAPCHANGEPRI decreasePriorityHeap;
    FUNHEAPCHANGEPRI increasePriorityHeap;
    FUNHEAPIFY heapify;
}FUNCT;

/***VETTORE***/
heap* makeHeapArray(int n);
void arrayHeapify(heap* H, int i);
int right(int i);
int left(int i);
int dad(int i);
heapNode* maxArrayHeap(heap* extr);
heapNode* extractMaxArrayHeap(heap* extr);
void decreasePriorityArrayHeap(heap* dec, int nEl, int newP);
void increasePriorityArrayHeap(heap* inc, int nEl, int newP);
heap* insertKeyArrayHeap(heap* A, void* elem, int key);
heap* deleteKeyArrayHeap(heap* A,int i);

/***ALBERO***/
heap* makeHeapTree(int n);
heapABNode* makeHeapABNode(heapABNode* root, heapABNode* dad, void* toIns, int pri);
void ABTreeHeapify(heap* toHeap, int j);
heapNode* maxABTreeHeap(heap* toMax);
heapNode* extractMaxABTreeHeap(heap* toMax);
heapABNode* scrollAB(heap* HEAP, int n);
void decreasePriorityABTreeHeap(heap* dec, int pos, int nPri);
void increasePriorityABTreeHeap(heap* inc, int pos, int nPri);
heap* deleteKeyABTreeHeap(heap* del, int i);
heap* insertKeyABTreeHeap(heap* toIns, void* elem, int key);

FUNCT* initFuncHeap(int);
/*****************************************************************************************/
int main(){
    heap* prova;
    prova=makeHeapArray(5);
    int i=0;
/*    for(i=0; i<5; i++){
        printf("%d\n", prova->HEAP->HEAPARRAY->array[i].priority);
    }
    heapNode* gne=maxArrayHeap(prova);
    printf("\n\n%d\n", gne->priority);
    */
    free(prova->HEAP->HEAPARRAY->function);
    free(prova->HEAP->HEAPARRAY->array);

    free(prova->HEAP->HEAPARRAY);

    free(prova->HEAP);
    free(prova);
exit(0);
    return 0;
}
/**************************************************************************************/


FUNCT* initFuncHeap(int typeH){
    FUNCT* ret=(FUNCT*)malloc(sizeof(FUNCT));
    if(typeH==ARRAY_TYPE){
        ret->decreasePriorityHeap=&decreasePriorityArrayHeap;
        ret->delHeap=&deleteKeyArrayHeap;
        ret->extractMaxHeap=&extractMaxArrayHeap;
        ret->heapify=&arrayHeapify;
        ret->increasePriorityHeap=&increasePriorityArrayHeap;
        ret->insHeap=&insertKeyArrayHeap;
        ret->maxHeap=&maxArrayHeap;
    }else if(typeH==TREE_TYPE){
        ret->decreasePriorityHeap=&decreasePriorityABTreeHeap;
        ret->delHeap=&deleteKeyABTreeHeap;
        ret->extractMaxHeap=&extractMaxABTreeHeap;
        ret->heapify=&ABTreeHeapify;
        ret->increasePriorityHeap=&increasePriorityABTreeHeap;
        ret->insHeap=&insertKeyABTreeHeap;
        ret->maxHeap=&maxABTreeHeap;
    }
    return ret;
}




heap* makeHeapArray(int n){
    heap* ret;
    int i, p, el=1;
    i=n;
    while(i>0){
        i=i/2;
        el=el*2;
    }
    ret=(heap*)malloc(sizeof(heap));
    ret->HEAP->HEAPARRAY->HEAPDIM=el;
//    ret->HEAP->HEAPARRAY->array=(heapNode*)malloc(sizeof(heapNode)*el);
    heapNode* k=(heapNode*)malloc(sizeof(heapNode)*el);
    for(i=0; i<n; i++){
//        scanf("%d", &(k[i].priority));
//        printf("    %d\n", ret->HEAP->HEAPARRAY->array[i].priority);
k[i].priority=i;
    }
    ret->HEAPSIZE=n;
    ret->HEAP->HEAPARRAY->function=initFuncHeap(ARRAY_TYPE);
    for(i=0; i<n; i++){
        printf("    %d\n", k[i].priority);
    }
    ret->HEAP->HEAPARRAY->array=k;
    for(i=(n/2); i>=0; i--){
            printf("\nyo\n");
        ret->HEAP->HEAPARRAY->function->heapify(ret, i);
//        Heapify(ret,i);
    }

    printf("heapized:\n");
    for(i=0; i<n; i++){
        printf("    %d\n", ret->HEAP->HEAPARRAY->array[i].priority);
    }
    printf("\nk\n");
    return ret;


}

void arrayHeapify(heap* H, int i){
    int l, r, max=i;
    heapNode temp;
    if(i>=0){
        l=left(i);
        r=right(i);
        if(l<(H->HEAPSIZE) && (H->HEAP->HEAPARRAY->array[l].priority>H->HEAP->HEAPARRAY->array[i].priority)){
            max=l;
        }else max=i;
        if(r<(H->HEAPSIZE) && (H->HEAP->HEAPARRAY->array[r].priority>H->HEAP->HEAPARRAY->array[max].priority)){
            max=r;
        }
        if(max!=i){
            temp.priority=H->HEAP->HEAPARRAY->array[i].priority;
            H->HEAP->HEAPARRAY->array[i].priority=H->HEAP->HEAPARRAY->array[max].priority;
            H->HEAP->HEAPARRAY->array[max].priority=temp.priority;
/*
            temp.data=H->HEAP->HEAPARRAY->array[i].data;
            H->HEAP->HEAPARRAY->array[i].data=H->HEAP->HEAPARRAY->array[max].data;
            H->HEAP->HEAPARRAY->array[max].data=temp.data;
*/

            H->HEAP->HEAPARRAY->function->heapify(H, max);
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
    else return extr->HEAP->HEAPARRAY->array+(0);
}

heapNode* extractMaxArrayHeap(heap* extr){
    heapNode* ret=NULL;
    heapNode* temp=extr->HEAP->HEAPARRAY->function->maxHeap(extr);
    if(temp!=NULL){
        ret=(heapNode*)malloc(sizeof(heapNode));
        ret->data=temp->data;
        ret->priority=temp->priority;
        extr->HEAP->HEAPARRAY->array[0]=extr->HEAP->HEAPARRAY->array[--(extr->HEAPSIZE)];
        extr->HEAP->HEAPARRAY->function->heapify(extr, 0);
    }
    return ret;
}

void decreasePriorityArrayHeap(heap* dec, int nEl, int newP){
    heapNode temp;
    int i=nEl;

    if(dec->HEAP->HEAPARRAY->array[nEl].priority>newP){
        dec->HEAP->HEAPARRAY->array[nEl].priority=newP;
        dec->HEAP->HEAPARRAY->function->heapify(dec, nEl);
    }
}

void increasePriorityArrayHeap(heap* inc, int nEl, int newP){
    heapNode temp;
    int i=nEl;

    if(inc->HEAP->HEAPARRAY->array[nEl].priority<newP){
        inc->HEAP->HEAPARRAY->array[nEl].priority=newP;
        inc->HEAP->HEAPARRAY->function->heapify(inc, nEl);
        while(i>=0 && inc->HEAP->HEAPARRAY->array[dad(i)].priority<inc->HEAP->HEAPARRAY->array[i].priority){
            temp=inc->HEAP->HEAPARRAY->array[dad(i)];
            inc->HEAP->HEAPARRAY->array[dad(i)]=inc->HEAP->HEAPARRAY->array[i];
            inc->HEAP->HEAPARRAY->array[i]=temp;
            i=dad(i);
        }
    }
}

heap* insertKeyArrayHeap(heap* A, void* iii, int key){
    heapNode*t=NULL;
    int i;
    A->HEAPSIZE++;
    if(A->HEAPSIZE>A->HEAP->HEAPARRAY->HEAPDIM){
        A->HEAP->HEAPARRAY->HEAPDIM=(A->HEAP->HEAPARRAY->HEAPDIM)*2;
        t=(heapNode*)malloc(sizeof(heapNode)*(A->HEAP->HEAPARRAY->HEAPDIM));
        for(i=0; i<A->HEAPSIZE; i++){
            t[i]=A->HEAP->HEAPARRAY->array[i];
        }
        free(A->HEAP->HEAPARRAY->array);
        A->HEAP->HEAPARRAY->array=t;
    }
    A->HEAP->HEAPARRAY->array[A->HEAPSIZE].priority=-1;
    A->HEAP->HEAPARRAY->function->increasePriorityHeap(A, A->HEAPSIZE-1, key);
    return A;
}

heap* deleteKeyArrayHeap(heap* A,int i){
    heapNode temp;
    if(A->HEAPSIZE>0){
        temp.data=A->HEAP->HEAPARRAY->array[i].data;
        A->HEAP->HEAPARRAY->array[A->HEAPSIZE-1].data=A->HEAP->HEAPARRAY->array[i].data;
        A->HEAP->HEAPARRAY->array[i].data=temp.data;
        if(A->HEAP->HEAPARRAY->array[A->HEAPSIZE-1].priority>A->HEAP->HEAPARRAY->array[i].priority){
            A->HEAP->HEAPARRAY->function->increasePriorityHeap(A, i, A->HEAP->HEAPARRAY->array[A->HEAPSIZE-1].priority);
        }else{
            A->HEAP->HEAPARRAY->function->decreasePriorityHeap(A, i, A->HEAP->HEAPARRAY->array[A->HEAPSIZE-1].priority);
        }
        A->HEAPSIZE--;
    }
    return A;
}





heap* makeHeapTree(int n){
    heap* ret=(heap*)malloc(sizeof(heap));
    ret->HEAPSIZE=n;
//    ret->HEAPDIM=0;
    ret->HEAP=(heapType*)malloc(sizeof(heapType));
    ret->HEAP->HEAPROOT=(heapABTree*)malloc(sizeof(heapABTree));
    ret->HEAP->HEAPROOT->tree=NULL;
    ret->HEAP->HEAPROOT->function=initFuncHeap(TREE_TYPE);
    heapABNode* scroll=ret->HEAP->HEAPROOT->tree;
    heapABNode* dad=NULL;
    int i=0, k, curr, dir;
    char pointer[33];
    curr=1;
    int pri;
    while(n>=curr){
        scanf("%d", &pri);
        dad=NULL;
        scroll=ret->HEAP->HEAPROOT->tree;
        itoa(curr, pointer, 2);
        int i=strlen(pointer);
        k=1;
        if(i>1){
            while(i>k){
//                printf("%d %c: ",k, pointer[k]);
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
                dad->dx=makeHeapABNode(scroll, dad, NULL, pri);
            }else if(pointer[k-1]=='0'){
                dad->sx=makeHeapABNode(scroll, dad, NULL, pri);
            }
        }else{
            ret->HEAP->HEAPROOT->tree=makeHeapABNode(ret->HEAP->HEAPROOT->tree, dad, NULL, pri);
        }
        curr++;
    }
    int j=(ret->HEAPSIZE)/2;
    heapABNode* temp;
    for(j; j>=0; j--){
        //temp=scrollAB(ret->HEAP->HEAPROOT->tree, j);
        //ret->HEAP->HEAPROOT->function->
        ret->HEAP->HEAPROOT->function->heapify(ret, j);
    }
    return ret;
}

heapABNode* makeHeapABNode(heapABNode* root, heapABNode* dad, void* toIns, int pri){
    root=(heapABNode*)malloc(sizeof(heapABNode));
    root->element=(heapNode*)malloc(sizeof(heapNode));
    root->element->data=toIns;
    root->element->priority=pri;
    root->dx=NULL;
    root->sx=NULL;
    root->dad=dad;
    return root;
}

void ABTreeHeapify(heap* toHeap, int j){
    heapABNode* left=NULL;
    heapABNode* right=NULL;
    heapABNode* root=NULL;
    heapABNode* max=NULL;
    heapNode* temp=NULL;
    if(toHeap->HEAP->HEAPROOT->tree!=NULL){
        root=scrollAB(toHeap, j);
        left=root->sx;
        right=root->dx;

        if(left!=NULL && left->element->priority>max->element->priority){
            max=left;
        }else {
            max=root;
        }

        if(right!=NULL && right->element->priority>max->element->priority){
            max=right;
        }

        if(max!=root){
            temp=max->element;
            max->element=root->element;
            root->element=temp;
            /***/
            toHeap->HEAP->HEAPROOT->function->heapify(toHeap, j/2);
        }
    }
}

heapNode* maxABTreeHeap(heap* toMax){
    if(toMax!=NULL){
        return toMax->HEAP->HEAPROOT->tree->element;
    }else return NULL;
}

heapNode* extractMaxABTreeHeap(heap* toMax){
    heapABNode* max=NULL;
    heapNode* temp;
    heapABNode* swi;
    int n;
    if(toMax->HEAP->HEAPROOT->tree!=NULL){
        max=scrollAB(toMax, toMax->HEAPSIZE);
        if(swi!=NULL){
            temp=max->element;
            max->element=toMax->HEAP->HEAPROOT->tree->element;
            toMax->HEAP->HEAPROOT->tree->element=temp;

            toMax->HEAPSIZE=toMax->HEAPSIZE-1;

            /******/
            if(max==max->dad->dx){
                max->dad->dx=NULL;
            }else{
                max->dad->sx=NULL;
            }

            /******/

            toMax->HEAP->HEAPROOT->function->heapify(toMax, 1);
        }

    }
    return max->element;
}




heapABNode* scrollAB(heap* toS, int n){
    int k, i;
    heapABNode* scroll=NULL;
    char pointer[33];
    if(n<=toS->HEAPSIZE){
        scroll=toS->HEAP->HEAPROOT->tree;
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

void decreasePriorityABTreeHeap(heap* dec, int pos, int nPri){
    heapABNode* toChange=scrollAB(dec, pos);
    if(toChange!=NULL){
        if(toChange->element->priority>nPri){
            toChange->element->priority=nPri;
            dec->HEAP->HEAPROOT->function->heapify(dec, pos);
        }
    }
}

void increasePriorityABTreeHeap(heap* inc, int pos, int nPri){
    heapABNode* toChange=scrollAB(inc, pos);
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

heap* deleteKeyABTreeHeap(heap* del, int i){
    heapABNode* toDel=NULL;
    heapABNode* toReplace=NULL;
    heapABNode* newLast=NULL;
    heapNode* temp=NULL;
    if(del->HEAP->HEAPROOT->tree!=NULL){
        toDel=scrollAB(del, i);
        if(toDel!=NULL){
            toReplace=scrollAB(del, del->HEAPSIZE);
            if(toReplace!=NULL){
                temp=toDel->element;
                toDel->element=toReplace->element;
                toReplace->element=temp;
                if(toReplace->dad->dx==toReplace){
                    toReplace->dad->dx=NULL;
                }else{
                    toReplace->dad->sx=NULL;
                }
                del->HEAPSIZE=del->HEAPSIZE-1;
                newLast=scrollAB(del, del->HEAPSIZE);
                if(toReplace->element->priority>toDel->element->priority){
                    del->HEAP->HEAPROOT->function->increasePriorityHeap(del, i, newLast->element->priority);
                }else{
                    del->HEAP->HEAPROOT->function->decreasePriorityHeap(del, i, newLast->element->priority);
                }
                free(toReplace->element);
                free(toReplace);
            }
        }
    }
    return del;
}



heap* insertKeyABTreeHeap(heap* toIns, void* elem, int key){
    int n;
    heapABNode* dad=NULL;
    heapABNode* ins=NULL;
    ins=(heapABNode*)malloc(sizeof(heapABNode));
    ins->element=(heapNode*)malloc(sizeof(heapNode));
    ins->element->data=elem;
    ins->element->priority=-1;
    ins->dx=NULL;
    ins->sx=NULL;
    if(toIns->HEAPSIZE==0){
        toIns->HEAP->HEAPROOT->tree=ins;
        ins->dad=dad;
        toIns->HEAPSIZE++;
    }else{
        n=((toIns->HEAPSIZE)+1)/2;
        dad=scrollAB(toIns, n);
        if(dad->sx==NULL){
            dad->sx=ins;
        }else if(dad->dx==NULL){
            dad->dx=ins;
        }

        ins->dad=dad;
        toIns->HEAPSIZE++;
        toIns->HEAP->HEAPROOT->function->increasePriorityHeap(toIns, toIns->HEAPSIZE, key);
    }
    return toIns;
}
