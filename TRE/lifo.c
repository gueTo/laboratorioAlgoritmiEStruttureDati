#include <stdio.h>
#include <stdlib.h>

#ifndef _LIFO_H_

    #define _LIFO_H_

    #include "lifo.h"

#endif // _LIFO_H_



lifo* lifoPush(lifo* stack, void* toPush){
    lifo* nStack=(lifo*)malloc(sizeof(lifo));
    nStack->element=toPush;
    nStack->next=stack;
    return nStack;
}

lifo* lifoTop(lifo* stack){
    return stack;
}

int lifoIsEmpty(lifo* stack){
    if(lifoTop(stack)==NULL)
        return 1;
    else return 0;
}

lifo* lifoPop(lifo* stack){
    lifo* temp;
    if(!lifoIsEmpty(stack)){
        temp=stack;
        stack=stack->next;
        free(temp);
    }
    return stack;
}

lifo* deleteLifo(lifo* stack){
    lifo* tempToFree;
    while(stack!=NULL){
        tempToFree=stack;
        stack=stack->next;
        free(tempToFree);
    }
    return stack;
}
