#include <stdio.h>
#include <stdlib.h>
#include "ARBIterative.h"

int main(){
    ARB* prova=NULL;
    void* str=NULL;
    FUNCT* l=initFUNCT();
    l=FUNCTtype(l,1);

    str=insertInteger(str);
    prova=insertARBNodeIterative(prova, str, l);
    str=insertInteger(str);
    prova=insertARBNodeIterative(prova, str, l);
    str=insertInteger(str);
    prova=insertARBNodeIterative(prova, str, l);
/*    int k;
    k=countARBNodeIterative(prova);
    printf("%d\n", k);
    void**a;
    a=vectorizeARB(prova, copyString);
    *//*
    ARB* l=NULL;
    l=balanceARBIterative(prova, compareString, copyString);
    */
    inOrderARBIter(prova, l);
    return 0;
}

