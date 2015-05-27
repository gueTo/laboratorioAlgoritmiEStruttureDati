#include <stdio.h>
#include <stdlib.h>

/*
#ifndef _LIST_H_
#define _LIST_H_

#include "list.h"

#endif // _LIST_H_
*/

#ifndef _FUNINS_
#define _FUNINS_
typedef void*(*FUNINS)();

#endif // _FUNINS_

#ifndef _FUNCOM_
#define _FUNCOM_

typedef int(* FUNCOM)(void*, void*);

#endif // _FUNCOM_

#ifndef _FUNPRINT_
#define _FUNPRINT_

typedef void(* FUNPRINT)(void*);

#endif // _FUNPRINT_

#ifndef _FUNDEL_
#define _FUNDEL_

typedef void(*FUNDEL)(void*);

#endif // _FUNDEL_

#ifndef _FUNCPY_
#define _FUNCPY_

typedef void*(*FUNCPY)(void*, void*);

#endif // _FUNCPY_


typedef struct list{
    void* elem;
    struct list* next;
}list;


list* insertNodeList(list*, void*, FUNCPY);
void printList(list*, FUNPRINT);
list* deleteNodeFromList(list* , void*, FUNCOM, FUNDEL);
void freeList(list*, FUNDEL);


list* insertNodeList(list* HEAD, void* toIns, FUNCPY cpy){
    list* newListNode=(list*)malloc(sizeof(list));
    newListNode->elem=toIns;
    newListNode->next=HEAD;
    HEAD=newListNode;
    return HEAD;
}

void printList(list* HEAD, FUNPRINT pri){
    if(HEAD!=NULL){
        pri(HEAD->elem);
        printList(HEAD->next, pri);
    }
    printf("\n");
}

list* deleteNodeFromList(list* HEAD, void* toDel, FUNCOM compare, FUNDEL del){
    list* delNode;
    if(HEAD!=NULL){
        if(compare(toDel, HEAD->elem)==0){
            delNode=HEAD;
            HEAD=HEAD->next;
            del(delNode);
        }
        else{
            HEAD->next=deleteNodeFromList(HEAD->next, toDel, compare, del);
        }
    }
    return HEAD;
}


void freeList(list* HEAD, FUNDEL del){
    if(HEAD!=NULL){
        freeList(HEAD->next, del);
        del(HEAD->elem);
        free(HEAD);
    }
}
