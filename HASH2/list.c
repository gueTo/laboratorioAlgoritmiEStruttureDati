#include <stdlib.h>
#include <stdio.h>

#ifndef _DATA_H_
    #define _DATA_H_

    #include "data.h"

#endif


#ifndef _LIST_H_
    #define _LIST_H_

    #include "list.h"

#endif

#ifndef _GEST_FUNCT_LIST_
#define _GEST_FUNCT_LIST_
/***********INIZIALIZZAZIONE*************************/
/*
Inizializza la struttura di funzioni di gestione della lista

INPUT: listType(ORDERED, NOT_ORDERED)
OUTPUT: listFunction inizializzata con le funzioni adatte
*/

listFunct* initListFunct(listType lt){
    listFunct* toInit=(listFunct*)malloc(sizeof(listFunct));
    if(lt==ORDERED){
        toInit->insertNode=&insertNewNodeOrdered;
        toInit->searchNode=&searchNodeOrdered;
        toInit->deleteNode=&deleteListNodeOrdered;
    }
    if(lt==NOT_ORDERED){
        toInit->insertNode=&insertNewNodeNotOrdered;
        toInit->searchNode=&searchNodeNotOrdered;
        toInit->deleteNode=&deleteListNodeNotOrdered;
    }
    toInit->printNode=&printListNode;
    toInit->freeList=&freeList;
    toInit->lType=lt;
    return toInit;
}

/*
funzione di deallocazione struttura gestione lista

INPUT:
    - listFunct*, la struttura da deallocare
OUTPUT:
    - listFunct*, un puntatore a NULL dopo aver deallocato la struttura
*/
listFunct* freeListFunct(listFunct* toDel){
    free(toDel);
    return NULL;
}
#endif // _GEST_FUNCT_LIST_


/*********CREA NUOVA LISTA*********/

/*
inizializza la struttura contenente la lista e le funzioni di gestione
INPUT:
    - listType, per definire se la lista è ordinata o meno
    - int, per definire il tipo di dato che si trova nella lista
OUTPUT:
    - LIST*, in puntatore alla nuova struttura dati LIST* inizializzata
*/

LIST* newList(listType lt, int dt){
    LIST* toRet=NULL;
    toRet=(LIST*)malloc(sizeof(LIST));
    toRet->list=NULL;
    toRet->listFunction=initListFunct(lt);
    toRet->dataf=initFUNCTDATA();
    FUNCTDATAtype(toRet->dataf, dt);
    return toRet;
}


/*****CREA NUOVO NODO*****/
/*
crea un nodo per la lista
INPUT:
    - void* toIns, il puntatore all'elemento da inserire nella lista
OUTPUT:
    - LIST_NODE*, il puntatore al nodo con l'elemento inserito
*/

LIST_NODE* newNode(void* toIns){
    LIST_NODE* toRet=NULL;
    toRet=(LIST_NODE*)malloc(sizeof(LIST_NODE));
    toRet->elem=toIns;
    toRet->next=NULL;
    return toRet;
}

/*******INSERISCI NUOVO NODO*******/
/*
Crea e inserisce un nodo nella lista
INPUT:
    - LIST* HEAD, la lista nella quale si vuole inserire l'elemento
    - void* toIns, l'elemento da inserire nella lista
OUTPUT:
    -LIST*, la lista modificata col nuovo elemento
*/
LIST* insertIntoList(LIST* HEAD, void* toIns){
    if(HEAD!=NULL){
        HEAD=HEAD->listFunction->insertNode(HEAD, toIns);
    }
    return HEAD;
}

/*******STAMPA NUOVO NODO*******/
/*
procedura per la stampa degli elementi della lista
INPUT:
    - LIST* HEAD, la lista che si vuole stampare
*/
void printList(LIST* HEAD){
    if(HEAD!=NULL){
        HEAD->listFunction->printNode(HEAD->list, HEAD->dataf->fpri);
    }
}

/*******CERCA NODO*********/
/*
cerca e restituisce, se presente, un elemento nella lista
INPUT:
    - LIST* HEAD, la lista nel quale si vuole cercare l'elemento
    - void* toSearch, l'elemento che si vuole ricercare
OUTPUT:
    - LIST_NODE*, il nodo contenente l'elemento ricercato, o un puntatore a NULL
        se l'elemento non esiste
*/
LIST_NODE* searchNode(LIST* HEAD, void* toSearch){
    if(HEAD!=NULL){
        return HEAD->listFunction->searchNode(HEAD->list, toSearch, HEAD->dataf->fcomp);
    }else {
        return NULL;
    }
}

/***********CANCELLAZIONE NODO**********/
/*
cerca e cancella, se presente, un elemento nella lista
INPUT:
    - LIST* HEAD, la lista in cui si vuole cercare l'elemento
    - void* toDel, l'elemento che si vuole cercare
OUTPUT:
    - LIST*, la lista modificata dalla cancellazione
*/
LIST* deleteNodeFromList(LIST* HEAD, void* toDel){
    if(HEAD!=NULL){
        HEAD->list=HEAD->listFunction->deleteNode(HEAD->list, toDel, HEAD->dataf->fcomp, HEAD->dataf->funfree);
    }
    return HEAD;
}

/*
dealloca il nodo
INPUT:
    - LIST_NODE* HEAD, il nodo da cancellare
    - FUNDEL del, la procedura per la deallocazione dell'elemento inserito nel nodo
OUTPUT
    - LIST_NODE*, un puntatore a NULL
*/

LIST_NODE* freeNode(LIST_NODE* HEAD, FUNDEL del){
    if(HEAD!=NULL){
        del(HEAD->elem);
        free(HEAD);
        return NULL;
    }
    return HEAD;
}

/*********DEALLOCA LISTA************/

LIST_NODE* freeList(LIST_NODE* HEAD, FUNDEL del){
    if(HEAD!=NULL){
        HEAD->next=freeList(HEAD->next, del);
        HEAD=freeNode(HEAD, del);
        return NULL;
    }
    return HEAD;
}

/******FUNZIONI SPECIFICHE LISTA*******/
LIST_NODE* searchNodeNotOrdered(LIST_NODE* list, void* toSearch, FUNCOM compare){
    if(list!=NULL){
        if(compare(toSearch, list->elem)==0)
            return list;
        else return searchNodeNotOrdered(list->next, toSearch, compare);
    }else return NULL;
}

LIST_NODE* searchNodeOrdered(LIST_NODE* list, void* toSearch, FUNCOM compare){
    if(list!=NULL){
        int res=compare(list->elem,toSearch);
        if(res==0)
            return list;
        else if(res>0)
            return searchNodeNotOrdered(list->next, toSearch, compare);
        else return NULL;
    }else return NULL;
}

LIST* insertNewNodeNotOrdered(LIST* HEAD, void* toIns){
    LIST_NODE* node=NULL;
    node=newNode(toIns);
    node->next=HEAD->list;
    HEAD->list=node;
    return HEAD;
}

LIST_NODE* ordering(LIST_NODE* HEAD, void* toIns, FUNCOM compare){
    if(HEAD!=NULL){
        if(compare(toIns, HEAD->elem)<0){
            HEAD->next=ordering(HEAD->next, toIns, compare);
        }else{
            LIST_NODE* n=newNode(toIns);
            n->next=HEAD;
            return n;
        }
    }else HEAD=newNode(toIns);
    return HEAD;
}

LIST* insertNewNodeOrdered(LIST* HEAD, void* toIns){
    if(HEAD!=NULL){
        HEAD->list=ordering(HEAD->list, toIns, HEAD->dataf->fcomp);
    }return HEAD;
}

void printListNode(LIST_NODE* HEAD, FUNPRINT print){
    if(HEAD!=NULL){
        print(HEAD->elem);
        printf("\n");
        printListNode(HEAD->next, print);
    }
}

LIST_NODE* delNode(LIST_NODE* nodeToDel, FUNDEL del){
    LIST_NODE* temp;
    temp=nodeToDel;
    nodeToDel=nodeToDel->next;
    del(temp->elem);
    free(temp);
    return nodeToDel;
}

LIST_NODE* deleteListNodeNotOrdered(LIST_NODE* HEAD, void* toDel, FUNCOM compare, FUNDEL del){
    if(HEAD!=NULL){
        if(compare(HEAD->elem, toDel)==0){
            HEAD=delNode(HEAD, del);
            return HEAD;
        }else{
            HEAD->next=deleteListNodeNotOrdered(HEAD->next, toDel, compare, del);
        }
    }
    return HEAD;
}

LIST_NODE* deleteListNodeOrdered(LIST_NODE* HEAD, void* toDel, FUNCOM compare, FUNDEL del){
    if(HEAD!=NULL){
        int res=compare(HEAD->elem, toDel);
        if(res==0){
            HEAD=delNode(HEAD, del);
            return HEAD;
        }else if(res>0){
            HEAD->next=deleteListNodeOrdered(HEAD->next, toDel, compare, del);
        }else return HEAD;
    }
    return HEAD;
}


LIST* freeAllList(LIST* HEAD){
    if(HEAD!=NULL){
        HEAD->list=HEAD->listFunction->freeList(HEAD->list, HEAD->dataf->funfree);
        HEAD->listFunction=freeListFunct(HEAD->listFunction);
        HEAD->dataf=deleteFUNCTDATA(HEAD->dataf);
        return NULL;
    }
    return HEAD;
}
