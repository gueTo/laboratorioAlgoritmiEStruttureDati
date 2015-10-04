#include "list.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct HASH_TABLE{
    unsigned int dimensione; //la dimensione della tabella
    //listFunct *funzioniLista; //le funzioni utilizzate nelle liste
    //FUNCTDATA *funzioniDato;//funzioni utilizzate per i dati
    LIST **tabella; //l'array di liste con i valori
}HASH_TABLE;


HASH_TABLE* init_HashTable(int dim){
    int i=0;
    HASH_TABLE* toRet=(HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    toRet->tabella=(LIST*)malloc(sizeof(LIST)*dim);
    toRet->dimensione=dim;
    toRet->funzioniLista=initListFunct(NOT_ORDERED);
    toRet->funzioniDato=initFUNCTDATA();
    for(i=0; i<dim; i++){
        toRet->tabella[i]=NULL;
    }
    FUNCTDATAtype(toRet->funzioniDato, 1);
    return toRet;
}

HASH_TABLE* insertIntoHashTable(HASH_TABLE* table, void* toIns){
    //int indice=hashFunction(toIns);
    return NULL;
}
