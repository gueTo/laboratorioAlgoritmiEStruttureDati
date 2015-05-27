
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

#ifndef _LISTSTRUCT_
#define _LISTSTRUCT_

typedef struct list{
    void* elem;
    struct list* next;
}list;

#endif // _LISTSTRUCT_






list* insertNodeList(list*, void*, FUNCPY);
void printList(list*, FUNPRINT);
list* deleteNodeFromList(list* , void*, FUNCOM, FUNDEL);
void freeList(list*, FUNDEL);
