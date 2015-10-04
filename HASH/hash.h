#include <stdio.h>
#include "list.h"

#ifndef _HASH_TABLE_
    #define _HASH_TABLE_

    typedef struct HASH_TABLE{
        LIST* tabella;
        OPERAZIONI_LISTA* operazioni;
        int capienza;
    }HASH_TABLE;

#endif // _HASH_TABLE_

/**DICHIARAZIONI FUNZIONI GESTIONE TABELLA HASH**/

HASH_TABLE* initHashTable(int dim, OPERAZIONI_LISTA* operazioni);
HASH_TABLE* inserisciElemento(HASH_TABLE* table, void* elem, void* par);
void* cercaElementoHash(HASH_TABLE* table, void* elem, void* par);
HASH_TABLE* cancellaDaHash(HASH_TABLE* table, void* elem, void*par);
void stampaHash(FILE* fp, HASH_TABLE* table, void* par);
HASH_TABLE* deallocaHASH(HASH_TABLE* table, void* par);
HASH_TABLE* ottimizzaHashTable(HASH_TABLE* table, int nDim, void* par);

