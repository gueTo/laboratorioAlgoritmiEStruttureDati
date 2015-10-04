#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "listString.h"

#ifndef _HASH_H_
    #define _HASH_H_
    #include "hash.h"

#endif // _HASH_H_



HASH_TABLE* initHashTable(int dim, OPERAZIONI_LISTA* operazioni){
    HASH_TABLE* ret=NULL;
    ret=(HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    ret->capienza=dim;
    ret->operazioni=operazioni;
    int i=0;
    ret->tabella=(LIST*)malloc(sizeof(LIST)*ret->capienza);
    for(i=0; i<ret->capienza; i++){
        ret->tabella[i]=NULL;
    }
    return ret;
}

HASH_TABLE* inserisciElemento(HASH_TABLE* table, void* elem, void* par){
    int where=table->operazioni->funzioneHash(elem, par)%table->capienza;
    table->tabella[where]=inserisciNuovoNodo(table->tabella[where], table->operazioni, nuovoNodo(elem), par);
    return table;
}

void* cercaElementoHash(HASH_TABLE* table, void* elem, void* par){
    int where=table->operazioni->funzioneHash(elem, par)%table->capienza;
    NODO_LISTA*res=cercaNodo(table->tabella[where], table->operazioni, elem, par);
    if(res!=NULL){
        return res->elem;
    }else return NULL;
}

HASH_TABLE* cancellaDaHash(HASH_TABLE* table, void* elem, void*par){
    int where=table->operazioni->funzioneHash(elem, par)%table->capienza;
    table->tabella[where]=cancellaDallaLista(table->tabella[where], table->operazioni, elem, par);
    return table;
}

void stampaHash(FILE* fp, HASH_TABLE* table, void* par){
    int i=0;
    for(i=0; i<table->capienza; i++){
        fprintf(fp, "%d ", i);
        stampaLista(fp, table->tabella[i], table->operazioni, par);
        fprintf(fp, "\n");
    }
}

HASH_TABLE* deallocaHASH(HASH_TABLE* table, void* par){
    int i=0;
    for(i=0; i<table->capienza; i++){
        table->tabella[i]=deallocaLista(table->tabella[i], table->operazioni, par);
    }
    free(table->tabella);
    table->capienza=0;
    free(table);
    return NULL;
}


HASH_TABLE* ottimizzaHashTable(HASH_TABLE* table, int nDim, void* par){
    HASH_TABLE* ret;
    ret=initHashTable(nDim, table->operazioni);
    int i=0;
//    int where;
    void* toIns;
    for(i=0; i<nDim; i++){
        toIns=PopLista(table->tabella[i]);
        while(toIns!=NULL){
            ret=inserisciElemento(ret, toIns, par);
            toIns=PopLista(table->tabella[i]);
        }
    }
    deallocaHASH(table, par);
    return ret;
}
