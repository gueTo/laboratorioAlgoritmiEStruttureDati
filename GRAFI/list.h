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
        FUNHASH has;
        FUNCOLLISION coll;
    }LIST_OPERATION;

    typedef LIST_NODE* LIST;

    LIST_OPERATION* initListOperation(FUNINS, FUNCPY, FUNDEL, FUNCOM, FUNPRINT, FUNHASH, FUNCOLLISION);

    LIST_NODE* newNode(void*, FUNCTDATA*, void*);

    LIST insertNewNode(LIST, void*, FUNCTDATA*, void*);

    LIST_NODE* searchNode(LIST, void*, FUNCTDATA*, void*);

    void printNode(FILE*, LIST_NODE*, FUNCTDATA*, void*);

    void printList(FILE*, LIST, FUNCTDATA*, void*);

    LIST deleteNodeFromList(LIST, void*, FUNCTDATA*, void*);

    LIST_NODE* deleteNode(LIST_NODE*, FUNCTDATA*, void*);

    LIST deleteList(LIST, FUNCTDATA*, void*);

    LIST push(LIST, FUNCTDATA*, void*, void*);

    int listIsEmpty(LIST);

    LIST_NODE* top(LIST);

    LIST pop(LIST);
#endif // _LIST_H_
