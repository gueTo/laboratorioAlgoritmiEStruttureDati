#include <stdio.h>
#include <stdlib.h>

#ifndef _FIFO_H_

    #define _FIFO_H_
    #include "fifo.h"

#endif // _FIFO_H_

fifo* enqueue(fifo* tail, void* toIns){
    if(tail!=NULL){
        tail->next=enqueue(tail->next, toIns);
    }else{
        tail=(fifo*)malloc(sizeof(fifo));
        tail->next=NULL;
        tail->el=toIns;
    }
    return tail;
}

fifo* readFifo(fifo* tail){
    return tail;

}

fifo* dequeue(fifo* tail){
    fifo* temp;
    if(tail!=NULL){
        temp=tail;
        tail=tail->next;
        free(temp);
    }
    return tail;
}
