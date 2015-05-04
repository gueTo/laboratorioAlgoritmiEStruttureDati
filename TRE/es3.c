#include <stdio.h>
#include <stdlib.h>
#include "ARBIterative.h"

int main(){
    ARB* prova=NULL;
    void* str;

    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);
    str=insertString(str);
    prova=insertARBNodeIterative(prova, str, compareString, copyString);

/*    int k;
    k=countARBNodeIterative(prova);
    printf("%d\n", k);
    void**a;
    a=vectorizeARB(prova, copyString);
    */
    ARB* l=NULL;
    l=balanceARBIterative(prova, compareString, copyString);
    return 0;
}

