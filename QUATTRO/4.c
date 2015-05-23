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



heap* deleteKeyArray(heap*, int);
heap* insertKey(heap*, int);
heap* makeHeapArray(int);
heapNode* maxHeap(heap*);
void Heapify(heap*, int);
heapNode* extractMaxHeap(heap*);
void decreasePriorityHeap(heap*, int, int);
void increasePriorityHeap(heap*, int, int);
heapABNode* makeHeapABNode(heapABNode*, heapABNode*, void*, int);
int right(int);
int left(int);
int dad(int);


int main(){
    heap* p;
    p=makeHeapArray(5);
    int i=0;
    printf("\n");
    for(i=0; i<p->HEAPSIZE; i++){
        printf("%d: %d\n", i, p->HEAP[i].priority);
    }
    getchar();
    /*printf("\nins\n");
    scanf("%d", &i);*/
    p=deleteKeyArray(p, 0);
    for(i=0; i<p->HEAPSIZE; i++){
        printf("\n%d: %d", i, p->HEAP[i].priority);
    }
    return 0;
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
    ret->HEAPDIM=el;
    ret->HEAP=(heapNode*)malloc(sizeof(heapNode)*el);
    for(i=0; i<n; i++){
        scanf("%d", &ret->HEAP[i].priority);
    }
    ret->HEAPSIZE=n;
    for(i=(n/2); i>=0; i--){
        Heapify(ret,i);
    }
    printf("\nk\n");
    return ret;
}

void Heapify(heap* H, int i){
    int l, r, max=i;
    l=left(i);
    r=right(i);
    heapNode temp;
    if(l<(H->HEAPSIZE) && (H->HEAP[l].priority>H->HEAP[i].priority)){
        max=l;
    }
    if(r<(H->HEAPSIZE) && (H->HEAP[r].priority>H->HEAP[max].priority)){
        max=r;
    }
    if(max!=i){
        temp=H->HEAP[i];
        H->HEAP[i]=H->HEAP[max];
        H->HEAP[max]=temp;
        Heapify(H, max);
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

heapNode* maxHeap(heap* extr){
    if(extr->HEAPSIZE<1)
        return NULL;
    else return extr->HEAP+(0);
}

heapNode* extractMaxHeap(heap* extr){
    heapNode* ret=NULL;
    heapNode* temp=maxHeap(extr);
    if(temp!=NULL){
        ret=(heapNode*)malloc(sizeof(heapNode));
        ret->data=temp->data;
        ret->priority=temp->priority;
        extr->HEAP[0]=extr->HEAP[--(extr->HEAPSIZE)];
        Heapify(extr, 0);
    }
    return ret;
}

void decreasePriorityHeap(heap* dec, int nEl, int newP){
    heapNode temp;
    int i=nEl;
    if(dec->HEAP[nEl].priority>newP){
        dec->HEAP[nEl].priority=newP;
        Heapify(dec, nEl);
    }
}

void increasePriorityHeap(heap* dec, int nEl, int newP){
    heapNode temp;
    int i=nEl;
    if(dec->HEAP[nEl].priority<newP){
        dec->HEAP[nEl].priority=newP;
        Heapify(dec, nEl);
        while(i>=0 && dec->HEAP[dad(i)].priority<dec->HEAP[i].priority){
            temp=dec->HEAP[dad(i)];
            dec->HEAP[dad(i)]=dec->HEAP[i];
            dec->HEAP[i]=temp;
            i=dad(i);
        }
    }
}

heap* insertKeyArray(heap* A, int key){
    heapNode*t=NULL;
    int i;
    A->HEAPSIZE++;
    if(A->HEAPSIZE>A->HEAPDIM){
        A->HEAPDIM=A->HEAPDIM*2;
        t=(heapNode*)malloc(sizeof(heapNode)*A->HEAPDIM);
        for(i=0; i<A->HEAPSIZE; i++){
            t[i]=A->HEAP[i];
        }
        free(A->HEAP);
        A->HEAP=t;
    }
    A->HEAP[A->HEAPSIZE].priority=-1;
    increasePriorityHeap(A, A->HEAPSIZE-1, key);
    return A;
}

heap* deleteKeyArray(heap* A,int i){
    heapNode temp;
    if(A->HEAPSIZE>0 && i<=A->HEAPSIZE){
        temp.data=A->HEAP[i].data;
        A->HEAP[A->HEAPSIZE-1].data=A->HEAP[i].data;
        A->HEAP[i].data=temp.data;
        if(A->HEAP[A->HEAPSIZE-1].priority>A->HEAP[i].priority){
            increasePriorityHeap(A, i, A->HEAP[A->HEAPSIZE-1].priority);
        }else{
            decreasePriorityHeap(A, i, A->HEAP[A->HEAPSIZE-1].priority);
        }
        A->HEAPSIZE--;
    }
    return A;
}

heap* makeHeapTree(int n){
    heap* HEAP=(heap*)malloc(sizeof(heap));
    HEAP->HEAPDIM=n;
    HEAP->HEAPSIZE=0;
    HEAP->HEAP=NULL;
    HEAP->HEAPROOT=NULL;
    heapABNode* scroll=HEAP->HEAPROOT;
    int i=0, k, curr, dir;
    char pointer[33];
    curr=1;
    int pri;
    while(n>=curr){
        scanf("%d", &pri);
        scroll=HEAP->HEAPROOT;
        itoa(curr, pointer, 2);
        int i=strlen(pointer);
        k=1;
        if(i>1){
            while(i>k){
                printf("%d %c: ",k, pointer[k]);
                if(pointer[k]=='1'){
                    scroll=scroll->dx;
                }else if(pointer[k]=='0'){
                    scroll=scroll->sx;
                }
                k++;
            }
        }else{
            HEAP->HEAPROOT=makeHeapABNode(HEAP->HEAPROOT,NULL, NULL, pri);
        }
        curr++;
    }

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
