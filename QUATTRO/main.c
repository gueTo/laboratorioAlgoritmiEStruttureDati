#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

void printARB(heapABNode* ROOT){
    if(ROOT!=NULL){
        printf("\n%d", ROOT->element->priority);
        printf("\n%d sx: ",ROOT->element->priority);
        printARB(ROOT->sx);//, funList);
        printf("\n%d dx: ",ROOT->element->priority);
        printARB(ROOT->dx);//, funList);
    }
}

int main(){
    return 0;
}

