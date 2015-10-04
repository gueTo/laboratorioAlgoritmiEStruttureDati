#include "corrispondence.h"
#include "hash.h"
#include <string.h>

/*typedef struct CORRESPONDANCE{
    void* ID;
    int id;
}CORRESPONDANCE;
*/

CORRESPONDANCE_TABLE* initCorrespondanceTable(int dim, OPERAZIONI_LISTA* operations){
    CORRESPONDANCE_TABLE* ret=(CORRESPONDANCE_TABLE*)malloc(sizeof(CORRESPONDANCE_TABLE));
    ret->corrId=initHashTable(dim, operations);
    return ret;
}

CORRESPONDANCE_TABLE* inserisciCorrispondenza(CORRESPONDANCE_TABLE* tab, CORRESPONDANCE* toIns, OPERAZIONI_LISTA* operations){
    tab->corrId=inserisciElemento(tab->corrId, (void*)toIns, operations);
    return tab;
}

CORRESPONDANCE_TABLE* eliminaCorrispondenza(CORRESPONDANCE_TABLE* tab, CORRESPONDANCE* toDel, OPERAZIONI_LISTA* operations){
    tab->corrId=cancellaDaHash(tab->corrId, (void*)toDel, operations);
    return tab;
}

CORRESPONDANCE* cercaCorrispondenza(CORRESPONDANCE_TABLE* tab, CORRESPONDANCE* toSearch, OPERAZIONI_LISTA* operations){
    return cercaElementoHash(tab->corrId, (void*)toSearch, operations);
}

CORRESPONDANCE_TABLE* deallocaCorrispondenza(CORRESPONDANCE_TABLE* tab, OPERAZIONI_LISTA* operations){
    tab->corrId=deallocaHASH(tab->corrId, operations);
    free(tab);
    tab=NULL;
    return NULL;
}

void* allocaCorrispondenza(void* corrispondenza, void* param){
    CORRESPONDANCE* ret=(CORRESPONDANCE*)malloc(sizeof(CORRESPONDANCE));
    ret->ID=((OPERAZIONI_LISTA*)param)->allocaDato(((CORRESPONDANCE*)corrispondenza)->ID, param + sizeof(OPERAZIONI_LISTA *));
    ret->index=((CORRESPONDANCE*)corrispondenza)->index;
    return ret;
}

void stampaCorrispondenza(FILE* fp, void* corrispondenza, void* param){
    if(corrispondenza!=NULL){
        fprintf(fp, "ID: ");
        ((OPERAZIONI_LISTA*)param)->stampaDato(fp, ((CORRESPONDANCE*)(corrispondenza))->ID, NULL);
        fprintf(fp, "  ->  index: %lu\n", (((CORRESPONDANCE*)(corrispondenza))->index));
    }
}

int comparaCorrispondenze(void* x, void* y, void* param){
    return (strcmp(((char*)(((CORRESPONDANCE*)(x))->ID)),((char*)(((CORRESPONDANCE*)(y))->ID))));
}

void* gestisciCollisioneCorrispondenza(void* corrispondenza, void* param){
    return corrispondenza;
}

void deallocaCorr(void* corrispondenza, void* param){
    ((OPERAZIONI_LISTA*)param)->deallocaDato(((char*)(((CORRESPONDANCE*)(corrispondenza))->ID)),  param+sizeof(OPERAZIONI_LISTA *));
    free(corrispondenza);
    corrispondenza=NULL;
}

unsigned long int hashCorrispondenza(void* corrispondenza, void* param){
    return ((CORRESPONDANCE*)corrispondenza)->index;
}

void *LeggiCorrispondenzaDaFile(void *fp, void *funzioniId){
    CORRESPONDANCE *ret;
    if(fgetc(fp)!=EOF){
        ret = (CORRESPONDANCE*)malloc(sizeof(CORRESPONDANCE));
        fseek(fp, -1, SEEK_CUR);
        fscanf(fp, "%lu", &ret->index);
        if(fgetc(fp)!=EOF){
            fseek(fp, -1, SEEK_CUR);
        ret->ID=((OPERAZIONI_LISTA *)funzioniId)->leggiDaInput(fp, funzioniId + sizeof(OPERAZIONI_LISTA *));
        }else ret=NULL;
    }else ret=NULL;
    return ret;
}
