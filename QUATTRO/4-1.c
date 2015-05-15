#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

typedef struct heapType{
    heapNode* HEAP;
    heapABNode* HEAPROOT;
    int HEAPSIZE;
    int HEAPDIM;
    int heaptype;
}heap;



heapABNode* makeHeapABNode(heapABNode*, heapABNode*, void*, int);
heap* makeHeapTree(int );
void heapifyAB(heapABNode*);
void  heapifyABHeap(heapABNode*);


/*****/

heapABNode* maxABHeap(heap* HEAP);
heapABNode* extractMaxABHeap(heap* HEAP);
heapABNode* scrollAB(heap* HEAP, int n);
void decreasePriorityABHeap(heap* HEAP, int pos, int nPri);
void increasePriorityABHeap(heap* HEAP, int pos, int nPri);
heap* deleteKeyABHeap(heap* HEAP, int i);
heap* insertKeyABHeap(heap* HEAP, void* elem, int key);
/*****/
void printARB(heapABNode* ROOT){//, FUNCT* funList){
    if(ROOT!=NULL){
        printf("\n%d", ROOT->element->priority);
        printf("\n%d sx: ");
        printARB(ROOT->sx);//, funList);
        printf("\n%d dx: ");
        printARB(ROOT->dx);//, funList);
    }
}


int main(){
    heap* p;
    p=makeHeapTree(8);
    printARB(p->HEAPROOT);
    printf("\nhere\n\n\n\n\n");

    //heapABNode*s=extractMaxABHeap(p);
    insertKeyABHeap(p, NULL, 10);
    printARB(p->HEAPROOT);/*
    heapABNode* s=scrollAB(p, 3);*/
    return 0;
}


heap* makeHeapTree(int n){
    heap* HEAP=(heap*)malloc(sizeof(heap));
    HEAP->HEAPSIZE=n;
    HEAP->HEAPDIM=0;
    HEAP->HEAP=NULL;
    HEAP->HEAPROOT=NULL;
    heapABNode* scroll=HEAP->HEAPROOT;
    heapABNode* dad=NULL;
    int i=0, k, curr, dir;
    char pointer[33];
    curr=1;
    int pri;
    while(n>=curr){
        scanf("%d", &pri);
        dad=NULL;
        scroll=HEAP->HEAPROOT;
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
            HEAP->HEAPROOT=makeHeapABNode(HEAP->HEAPROOT, dad, NULL, pri);
        }
        curr++;
    }
    int j=(HEAP->HEAPSIZE)/2;
    heapABNode* temp;
    for(j; j>=0; j--){
        temp=scrollAB(HEAP, j);
        heapifyAB(temp);
    }
    return HEAP;
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

void heapifyAB(heapABNode* root){
    heapABNode* left=NULL;
    heapABNode* right=NULL;
    heapABNode* max=root;
    heapNode* temp;
    if(root!=NULL){
        left=root->sx;
        right=root->dx;
        if(left!=NULL && left->element->priority>max->element->priority){
            max=left;
        }else max=root;
        if(right!=NULL && right->element->priority>max->element->priority){
            max=right;
        }
        if(max!=root){
            temp=max->element;
            max->element=root->element;
            root->element=temp;
            heapifyAB(max);
        }
    }
}

heapABNode* maxABHeap(heap* HEAP){
    if(HEAP!=NULL){
        return HEAP->HEAPROOT;
    }else return NULL;
}

heapABNode* extractMaxABHeap(heap* HEAP){
    heapABNode* max=NULL;
    heapNode* temp;
    heapABNode* swi;
    int n;
    if(HEAP!=NULL){

        max=scrollAB(HEAP, HEAP->HEAPSIZE);
        if(swi!=NULL){
            temp=max->element;
            max->element=HEAP->HEAPROOT->element;
            HEAP->HEAPROOT->element=temp;

            HEAP->HEAPSIZE=HEAP->HEAPSIZE-1;

            /******/
            if(max==max->dad->dx){
                max->dad->dx=NULL;
            }else{
                max->dad->sx=NULL;
            }

            /******/

            heapifyAB(HEAP->HEAPROOT);
        }

    }
    return max;
}




heapABNode* scrollAB(heap* HEAP, int n){
    int k, i;
    heapABNode* scroll=NULL;
    char pointer[33];
    if(n<=HEAP->HEAPSIZE){
        scroll=HEAP->HEAPROOT;
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

void decreasePriorityABHeap(heap* HEAP, int pos, int nPri){
    heapABNode* toChange=scrollAB(HEAP, pos);
    if(toChange!=NULL){
        if(toChange->element->priority>nPri){
            toChange->element->priority=nPri;
            heapifyAB(toChange);
        }
    }
}

void increasePriorityABHeap(heap* HEAP, int pos, int nPri){
    heapABNode* toChange=scrollAB(HEAP, pos);
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

heap* deleteKeyABHeap(heap* HEAP, int i){
    heapABNode* toDel=NULL;
    heapABNode* toReplace=NULL;
    heapABNode* newLast=NULL;
    heapNode* temp=NULL;
    if(HEAP!=NULL){
        toDel=scrollAB(HEAP, i);
        if(toDel!=NULL){
            toReplace=scrollAB(HEAP, HEAP->HEAPSIZE);
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
                newLast=scrollAB(HEAP, HEAP->HEAPSIZE);
                if(toReplace->element->priority>toDel->element->priority){
                    increasePriorityABHeap(HEAP, i, newLast->element->priority);
                }else{
                    decreasePriorityABHeap(HEAP, i, newLast->element->priority);
                }
                free(toReplace->element);
                free(toReplace);
            }
        }
    }
    return HEAP;
}



heap* insertKeyABHeap(heap* HEAP, void* elem, int key){
    int n;
    heapABNode* dad=NULL;
    heapABNode* ins=NULL;
    ins=(heapABNode*)malloc(sizeof(heapABNode));
    ins->element=(heapNode*)malloc(sizeof(heapNode));
    ins->element->data=elem;
    ins->element->priority=-1;
    ins->dx=NULL;
    ins->sx=NULL;
    if(HEAP->HEAPSIZE==0){
        HEAP->HEAPROOT=ins;

    ins->dad=dad;
        HEAP->HEAPSIZE++;
    }else{
        n=((HEAP->HEAPSIZE)+1)/2;
        dad=scrollAB(HEAP, n);
        if(dad->sx==NULL){
            dad->sx=ins;
        }else if(dad->dx==NULL){
            dad->dx=ins;
        }

        ins->dad=dad;
        HEAP->HEAPSIZE++;
        increasePriorityABHeap(HEAP, HEAP->HEAPSIZE, key);
    }
    return HEAP;
}
