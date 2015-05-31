#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABR.h"
#include "data.h"
#include "heap.h"

void print(ARB* A){
    if(A!=NULL){
        printf("%d\n", ((heapNode*)(A->element))->priority);
        print(A->sx);
        print(A->dx);
    }
};

int main(){
    HEAP* uno;
    uno=initHEAP(HEAP_TREE, MIN_HEAP);
    int i=0;
    for(i=0;i<10; i++){
        uno=insertHeap(uno, NULL);
    }
    printf("\n");
    print((ARB*)(uno->heap));
    /*for(i=0; i<uno->heapSize; i++){
        printf("%d ", ((arrayHeap*)(uno->heap))->array[i].priority);
    }*/

    freeTree(uno);
    printf("\n");
    print((ARB*)(uno->heap));
    return 0;
}
