#include "hash.h"

typedef struct CORRESPONDANCE{
    void* ID;
    unsigned long int index;
}CORRESPONDANCE;


typedef struct CORRESPONDANCE_TABLE{
    HASH_TABLE* corrId;
}CORRESPONDANCE_TABLE;




CORRESPONDANCE_TABLE* initCorrespondanceTable(int, OPERAZIONI_LISTA*);
CORRESPONDANCE_TABLE* inserisciCorrispondenza(CORRESPONDANCE_TABLE*, CORRESPONDANCE*, OPERAZIONI_LISTA*);
CORRESPONDANCE_TABLE* eliminaCorrispondenza(CORRESPONDANCE_TABLE*, CORRESPONDANCE*, OPERAZIONI_LISTA*);
CORRESPONDANCE* cercaCorrispondenza(CORRESPONDANCE_TABLE*, CORRESPONDANCE*, OPERAZIONI_LISTA*);
CORRESPONDANCE_TABLE* deallocaCorrispondenza(CORRESPONDANCE_TABLE*, OPERAZIONI_LISTA*);

void* allocaCorrispondenza(void*, void*);
void stampaCorrispondenza(FILE*, void*, void*);
int comparaCorrispondenze(void*, void*, void*);
void* gestisciCollisioneCorrispondenza(void*, void*);
void deallocaCorr(void*, void*);
unsigned long int hashCorrispondenza(void*, void*);
void *LeggiCorrispondenzaDaFile(void*, void*);
