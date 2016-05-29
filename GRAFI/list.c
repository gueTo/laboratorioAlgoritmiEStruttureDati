#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#include "correspondence.h"

LIST_OPERATION* initListOperation(FUNINS insert, FUNCPY copy, FUNDEL dealloc, FUNCOM compare, FUNPRINT print, FUNHASH has, FUNCOLLISION coll){
    LIST_OPERATION* operation=(LIST_OPERATION*)malloc(sizeof(LIST_OPERATION));
    operation->ins=insert;
    operation->cpy=copy;
    operation->del=dealloc;
    operation->compare=compare;
    operation->print=print;
    operation->coll=coll;
    operation->has=has;
    return operation;
}

LIST_NODE* newNode(void* newElement, FUNCTDATA* operation, void* parameter){
    LIST_NODE* ret=(LIST_NODE*)malloc(sizeof(LIST_NODE));

    ret->element=operation->fcopy(ret->element, newElement, parameter);

    ret->next_node=NULL;
    return ret;
}

LIST insertNewNode(LIST list, void* newElement, FUNCTDATA* operation, void* parameter){
    if(list!=NULL){
        if(operation->fcomp(list->element, newElement, parameter)<0){
            list->next_node=insertNewNode(list->next_node, newElement, operation, parameter);
        }else{
            LIST_NODE* nn=newNode(newElement, operation, parameter);
            nn->next_node=list;
            return nn;
        }
    }else{
        LIST_NODE* nn=newNode(newElement, operation, parameter);
        nn->next_node=list;
        return nn;
    }
    return list;
}

LIST_NODE* searchNode(LIST list, void* toSearch, FUNCTDATA* operation, void* parameter){
    LIST_NODE* ret=NULL;
    int cmp=0;
    if(list!=NULL){
        cmp=operation->fcomp(list->element, toSearch, parameter);
       if(cmp==0){
          ret=list;
          return ret;
       }else if(cmp<0){
          return searchNode(list->next_node, toSearch, operation, parameter);
       }else
            return NULL;
    }else return NULL;
}

void printNode(FILE* fp, LIST_NODE* node, FUNCTDATA* operation, void* parameter){
    if(node!=NULL){
        operation->fpri(fp, node->element, parameter);
    }
}

void printList(FILE* fp, LIST list, FUNCTDATA* operation, void* parameter){
    if(list!=NULL){
        printNode(fp, list, operation, parameter);
        fprintf(fp, " ");
        printList(fp, list->next_node, operation, parameter);
    }else fprintf(fp, "\n");
}

LIST_NODE* deleteNode(LIST_NODE*toDel, FUNCTDATA* operation, void* parameter){
    if(toDel!=NULL){
        toDel->element=operation->funfree(toDel->element, parameter);
        free(toDel);
        toDel=NULL;
    }
    return toDel;
}

LIST deleteNodeFromList(LIST list, void* toDel, FUNCTDATA* operation, void* parameter){
    LIST_NODE *temp;
    if(list!=NULL){
        if(operation->fcomp(list->element, toDel, parameter)==0){
            temp=list->next_node;
            list=deleteNode(list, operation, parameter);
            return temp;
        }else if(operation->fcomp(list->element, toDel, parameter)<0){
            list->next_node=deleteNodeFromList(list->next_node, toDel, operation, parameter);
            return list;
        }else return list;
    }else return list;
}

LIST deleteList(LIST list, FUNCTDATA* operation, void* parameter){
    if(list!=NULL){
        list->next_node=deleteList(list->next_node, operation, parameter);
        operation->funfree(list->element, parameter);
        free(list);
        list=NULL;
    }
    return list;
}

LIST push(LIST list, FUNCTDATA* operation, void* elem, void* param){
    LIST_NODE* nodo;

    nodo=newNode(elem, operation, param);

    nodo->next_node=list;
    return nodo;
}

int listIsEmpty(LIST list){
    if(list!=NULL)
        return 0;
    return 1;
}

LIST_NODE* top(LIST list){
    return list;
}

LIST pop(LIST list){
    if(listIsEmpty(list)!=1)
        return list->next_node;
    return list;
}
