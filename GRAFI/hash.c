#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**/
#include "correspondence.h"
/**/
#include "data.h"
#include "list.h"
#include "hash.h"

HASH_OPERATION* initHashOperation(FUNHASH hashing, FUNCOLLISION collision){
    HASH_OPERATION* oper=(HASH_OPERATION*)malloc(sizeof(HASH_OPERATION));
    oper->hashing=hashing;
    oper->gestCollision=collision;
    return oper;
}

HASH_TABLE* initHashTable(long unsigned int dimension, FUNCTDATA* l_operation){//, HASH_OPERATION* l_operation){
    HASH_TABLE* ret=(HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    int i=0;
    ret->dimension=dimension;
    ret->l_operation=l_operation;
//    ret->l_operation=l_operation;
    ret->table=(LIST*)malloc(sizeof(LIST)*dimension);
    for(i=0; i<dimension; i++){
        ret->table[i]=NULL;
    }
    return ret;
}

HASH_TABLE* insertIntoHashTable(HASH_TABLE* table, void* toInsert, void* parameter){
    LIST_NODE* exist;
    long unsigned int index;
    void* temp;
    if(table!=NULL){

        index=table->l_operation->fhas(toInsert, parameter)%(table->dimension);
        /**gestione collisione**/
        /*controllo se esiste già l'elemento*/
        exist=searchNode(table->table[index], toInsert, table->l_operation, parameter);
        /*se esiste, gestisco la collisione*/
        if(exist!=NULL){
                /*come la gestisco, dipende da gestCollision*/
            temp=table->l_operation->fcoll(exist->element);/*se mi risponde NULL, allora non inserisco nulla*/
            if(temp!=NULL){
                /*
                    se invece mi risponde con qualcosa di diverso, inserisco quest'ultima cosa.
                    gestCollision dovrebbe rispondere con cosa devo inserire una volta gestito il problema
                */
                table->table[index]=insertNewNode(table->table[index], temp, table->l_operation, parameter);
            }
        }else{/*se non c'è alcun elemento uguale, allora non c'è problema*/
            table->table[index]=insertNewNode(table->table[index], toInsert, table->l_operation, parameter);
        }
    }return table;
}


HASH_TABLE* deleteFromHashTable(HASH_TABLE* table, void* toDel, void* parameter){
    long unsigned int index;
    if(table!=NULL){
        index=table->l_operation->fhas(toDel, parameter)%(table->dimension);
        table->table[index]=deleteNodeFromList(table->table[index], toDel, table->l_operation, parameter);
    }
    return table;
}

void* searchIntoHashTable(HASH_TABLE* table, void* toSearch, void* parameter){
    long unsigned int index;

    if(table!=NULL){
        index=table->l_operation->fhas(toSearch, parameter)%(table->dimension);
        LIST_NODE* n=searchNode(table->table[index], toSearch, table->l_operation, parameter);
        if(n!=NULL){
            return n->element;
        }
    }
    return NULL;
}

void printHashTable(FILE* fp, HASH_TABLE* table, void* parameter){
    int i=0;
    if(table!=NULL){
        for(i=0; i<table->dimension; i++){
            fprintf(fp, "%d -> ", i);
            printList(fp, table->table[i], table->l_operation, parameter);
            fprintf(fp, "\n");
        }
    }
}

HASH_TABLE* restructHashTable(HASH_TABLE* table, long unsigned int newDim, void* parameter){
    HASH_TABLE* newTable=NULL;
    LIST_NODE* node=NULL;
    int i=0;
    if(table!=NULL){
        newTable=initHashTable(newDim, table->l_operation);//table->l_operation);
            for(i=0; i<table->dimension; i++){
                node=top(table->table[i]);
                while(node!=NULL){
                    table->table[i]=pop(table->table[i]);
                    newTable=insertIntoHashTable(newTable, node->element, parameter);
                    table->l_operation->funfree(node->element, parameter);
                    free(node);
                    node=top(table->table[i]);
                }
            }
        free(table->table);
        free(table);
        table=NULL;
    }
    return newTable;
}

HASH_TABLE* freeHashTable(HASH_TABLE* table, void* parameter){
    int i=0;
    if(table!=NULL){
        for(i=0; i<table->dimension; i++){
            table->table[i]=deleteList(table->table[i], table->l_operation, parameter);
        }
        free(table->table);
        free(table->l_operation);
        free(table->l_operation);
        free(table);
        table=NULL;
    }
    return table;
}

