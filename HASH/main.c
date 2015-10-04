#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "listString.h"
#include "data.h"
#include "hash.h"


int main(){
    OPERAZIONI_LISTA* lll;
    lll = (OPERAZIONI_LISTA*)malloc(sizeof(OPERAZIONI_LISTA));
    *lll= InserisciFunzioni(&AllocaStringa, &StampaStringa, &ComparaStringhe, &GestisciCollisioneStringa,
                                    &DeallocaStringa, &LeggiStringaDaTastiera, &HashStringhe);
//    FILE* k=fopen("prova.txt", "rw");
    HASH_TABLE* prova=initHashTable(5, lll);
    prova=inserisciElemento(prova, prova->operazioni->leggiDaInput(stdin, NULL), NULL);
    prova=inserisciElemento(prova, prova->operazioni->leggiDaInput(stdin, NULL), NULL);
    prova=inserisciElemento(prova, prova->operazioni->leggiDaInput(stdin, NULL), NULL);
    prova=inserisciElemento(prova, prova->operazioni->leggiDaInput(stdin, NULL), NULL);
    prova=inserisciElemento(prova, prova->operazioni->leggiDaInput(stdin, NULL), NULL);
    stampaHash(stdout, prova, NULL);
return 0;
}
