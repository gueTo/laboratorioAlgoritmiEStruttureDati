#ifndef _LIST_H_
    #define _LIST_H_
    #include "data.h"

    typedef struct LIST_NODE{
        void* element;
        struct LIST_NODE* next_node;
    }LIST_NODE;

    typedef struct LIST_OPERATION{
        FUNCOM compare;
        FUNCPY cpy;
        FUNDEL del;
        FUNPRINT print;
        FUNINS ins;
    }LIST_OPERATION;

    typedef LIST_NODE* LIST;

    LIST_OPERATION* initListOperation(FUNINS, FUNCPY, FUNDEL, FUNCOM, FUNPRINT);

    LIST_NODE* newNode(void*, LIST_OPERATION*, void*);

    LIST insertNewNode(LIST, void*, LIST_OPERATION*, void*);

    LIST_NODE* searchNode(LIST, void*, LIST_OPERATION*, void*);

    void printNode(FILE*, LIST_NODE*, LIST_OPERATION*, void*);

    void printList(FILE*, LIST, LIST_OPERATION*, void*);

    LIST deleteNodeFromList(LIST, void*, LIST_OPERATION*, void*);

    LIST_NODE* deleteNode(LIST_NODE*, LIST_OPERATION*, void*);

    LIST deleteList(LIST, LIST_OPERATION*, void*);

    LIST_NODE* top(LIST );

    LIST pop(LIST);
#endif // _LIST_H_
