/******STRUTTURE*****/
#ifndef _listType_
#define _listType_

typedef enum {ORDERED, NOT_ORDERED} listType;

#endif // _listType_


#ifndef _LIST_NODE_STRUCT_
#define _LIST_NODE_STRUCT_
/*
definizione del nodo di una lista
*/
typedef struct LIST_NODE{
    void* elem;
    struct LIST_NODE* next;
}LIST_NODE;



#endif // _LIST_NODE_STRUCT_

#ifndef _LIST_STRUCT_
#define _LIST_STRUCT_

/*
definizione della struttura data lista
*/
typedef struct LIST{
    LIST_NODE* list;//la vera e propria lista
    FUNCTDATA* dataf;//per la gestione del tipo di dato inclusi nei nodi della lista
    struct listFunct* listFunction;//gestione della lista di tipo ORDINATA o NON ORDINATA
}LIST;

/**DEFINIZIONI FUNZIONI PER LA GESTIONE DELLA LISTA**/
typedef LIST*(*INS_INTO_LIST)(LIST*, void*);//inserimento di un elemento in lista
typedef LIST_NODE*(*SEARCH_INTO_LIST)(LIST_NODE*, void*, FUNCOM);//ricerca di un elemento nella lista
typedef void (*PRINT_LIST)(LIST_NODE*, FUNPRINT);//stampa degli elementi della lista
typedef LIST_NODE*(*DELETE_FROM_LIST)(LIST_NODE*, void*, FUNCOM, FUNDEL);//cancellazione di un elemento dalla lista
typedef LIST_NODE*(*FREE_LIST)(LIST_NODE*, FUNDEL);//deallocazione di tutta la lista


/********DEFINIZIONE FUNZIONI PER LE LISTE*********/


LIST* newList(listType, int);
LIST_NODE* newNode(void*);

LIST* insertIntoList(LIST*, void*);
LIST* insertNewNodeNotOrdered(LIST*, void*);
LIST* insertNewNodeOrdered(LIST*, void*);

LIST_NODE* searchNode(LIST*, void*);
LIST_NODE* searchNodeNotOrdered(LIST_NODE*, void*, FUNCOM);
LIST_NODE* searchNodeOrdered(LIST_NODE*, void*, FUNCOM);

LIST_NODE* delNode(LIST_NODE*, FUNDEL);
LIST* deleteNodeFromList(LIST*, void*);
LIST_NODE* deleteListNodeNotOrdered(LIST_NODE*, void*, FUNCOM, FUNDEL);
LIST_NODE* deleteListNodeOrdered(LIST_NODE*, void*, FUNCOM, FUNDEL);

void printList(LIST*);
void printListNode(LIST_NODE*, FUNPRINT);

LIST_NODE* freeList(LIST_NODE*, FUNDEL);
LIST_NODE* freeNode(LIST_NODE*, FUNDEL);

LIST* freeAllList(LIST*);



LIST_NODE* ordering(LIST_NODE*, void*, FUNCOM);
#endif // _LIST_STRUCT_

/********STRUTTURA FUNZIONI LISTE*********/
#ifndef _LISTFUNCT_
#define _LISTFUNCT_

/*
definzione della struttura contenente le fuzioni di gestione della lista ordinata o non
*/
typedef struct listFunct{
    INS_INTO_LIST insertNode;
    SEARCH_INTO_LIST searchNode;
    PRINT_LIST printNode;
    DELETE_FROM_LIST deleteNode;
    FREE_LIST freeList;
    listType lType;
}listFunct;

listFunct* initListFunct(listType);
listFunct* freeListFunct();

#endif // _LISTFUNCT_

