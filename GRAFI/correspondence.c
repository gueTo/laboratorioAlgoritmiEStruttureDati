
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "correspondence.h"


/****
CORRESPONDENCE_TABLE* initCorresponcendeTable(unsigned int dimension,
                                              LIST_OPERATION* IDListOperation, LIST_OPERATION* IndexListOperation,
                                              HASH_OPERATION* IDHashOperation, HASH_OPERATION* IndexHashOperation)

INPUT:
-dimension: grandezza della tabella delle corrispondenze
-IDListOperation: operazioni inerenti agli ID
-IndexListOperation: operazioni inerenti agli indici
-IDHashOperation: operazioni per la gestione degll'hashing e delle collisioni degli ID
-IndexHashOperation: operazioni per la gestione degll'hashing e delle collisioni degli indici

OUTPUT:
Alloca, inizializza e restituisce il puntatore di una tabella delle corrispondenze

****/
CORRESPONDENCE_TABLE* initCorresponcendeTable(unsigned int dimension,
                                              LIST_OPERATION* IDListOperation, LIST_OPERATION* IndexListOperation,
                                              HASH_OPERATION* IDHashOperation, HASH_OPERATION* IndexHashOperation){

    CORRESPONDENCE_TABLE* newCorrTable=(CORRESPONDENCE_TABLE*)malloc(sizeof(CORRESPONDENCE_TABLE));
    newCorrTable->correspondenceID=initHashTable(dimension, IDListOperation, IDHashOperation);
    newCorrTable->correspondenceIndex=initHashTable(dimension, IndexListOperation, IndexHashOperation);
    return newCorrTable;
}


/****
CORRESPONDENCE* newCorrespondence(void* ID, unsigned int index, FUNCPY cpy, void* parameter)
INPUT:
-ID: puntatore all'informazione che si vuole inserire
-index: l'indice in cui è conservata l'informazione
-cpy: puntatore alla funzione di copia per l'ID
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di copia

OUTPUT:
Alloca e restituisce il puntatore ad una corrispondenza

****/
CORRESPONDENCE* newCorrespondence(void* ID, unsigned int index, FUNCPY cpy, void* parameter){
    CORRESPONDENCE* ret=(CORRESPONDENCE*)malloc(sizeof(CORRESPONDENCE));
    ret->ID=cpy(ret->ID, ID, parameter);
    ret->index=index;
    return ret;
}

/****
CORRESPONDENCE_TABLE* insertIntoCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, CORRESPONDENCE* toInsert, void* parameter)
INPUT:
-corrTable: il puntatore alla tabella delle corrispondenze nella quale si vuole inserire una corrispondenza
-toInsert: il puntatore alla corrispondenza che si vuole inserire
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di inserimento

OUTPUT:
Inserisce in corrTable una nuova corrispondenza, e restituisce il puntatore alla tabella aggiornata
****/
CORRESPONDENCE_TABLE* insertIntoCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, CORRESPONDENCE* toInsert, void* parameter){
    void* ft;
    if(corrTable!=NULL){
        /****sostituisco funzione copia con una funzione pigra*****/
        ft=corrTable->correspondenceID->l_operation->cpy;
        corrTable->correspondenceID->l_operation->cpy=fakeCopy;
            corrTable->correspondenceID=insertIntoHashTable(corrTable->correspondenceID, toInsert, parameter);
        /****rimetto a posto*****/
        corrTable->correspondenceID->l_operation->cpy=ft;

        /****sostituisco funzione copia con una funzione pigra*****/
        ft=corrTable->correspondenceIndex->l_operation->cpy;
        corrTable->correspondenceIndex->l_operation->cpy=fakeCopy;
            corrTable->correspondenceIndex=insertIntoHashTable(corrTable->correspondenceIndex, toInsert, parameter);
        /****rimetto a posto*****/
        corrTable->correspondenceIndex->l_operation->cpy=ft;
    }
    return corrTable;
}

/****
void printCorrespondenceTable(FILE* fp, CORRESPONDENCE_TABLE* table, void* parameter)

INPUT:
-fp: il puntatore al file su cui si vuole stampare la tavola delle corrispondenze. Anche lo standard output vale come file
-corrTable: il puntatore alla tabella che si vuole stampare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di stampa

OUTPUT:
- NON PREVEDE OUTPUT
****/
void printCorrespondenceTable(FILE* fp, CORRESPONDENCE_TABLE* corrTable, void* parameter){
    void* ft;
    if(corrTable!=NULL){
        ft=corrTable->correspondenceID->l_operation->print;
        corrTable->correspondenceID->l_operation->print=printIDCorrespondence;
            printHashTable(fp, corrTable->correspondenceID, ft);
        corrTable->correspondenceID->l_operation->print=ft;

        ft=corrTable->correspondenceIndex->l_operation->print;
        corrTable->correspondenceIndex->l_operation->print=printIndexCorrespondence;
            printHashTable(fp, corrTable->correspondenceIndex, NULL);
        corrTable->correspondenceID->l_operation->print=ft;
    }
}

/****
CORRESPONDENCE* searchIDIntoCorrespondeceTable(CORRESPONDENCE_TABLE* corrTable, void* toSearch, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella che si vuole stampare
-toSearch: l'informazione, in questo caso l'ID, che si vuole ricercare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di stampa

OUTPUT:
- Restituisce il puntatore alla corrispondenza in cui si trova l'informazione cercata,
  o un puntatore a NULL nel caso non sia stata trovata
****/
CORRESPONDENCE* searchIDIntoCorrespondeceTable(CORRESPONDENCE_TABLE* corrTable, void* toSearch, void* parameter){
    CORRESPONDENCE* ret=NULL;
    CORRESPONDENCE temp;
    void* ft;
    if(corrTable!=NULL){
        temp.ID=toSearch;
        ft=corrTable->correspondenceID->l_operation->compare;
        corrTable->correspondenceID->l_operation->compare=compareCorrespondenceByID;
            ret=searchIntoHashTable(corrTable->correspondenceID, &temp, ft);
        corrTable->correspondenceID->l_operation->compare=ft;
    }
    return ret;
}

/****
CORRESPONDENCE* searchIndexIntoCorrespondeceTable(CORRESPONDENCE_TABLE* corrTable, unsigned int long toSearch, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella che si vuole stampare
-toSearch: l'informazione, in questo caso l'indice, che si vuole ricercare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di ricerca

OUTPUT:
- Restituisce il puntatore alla corrispondenza in cui si trova l'informazione cercata,
  o un puntatore a NULL nel caso non sia stata trovata
****/
CORRESPONDENCE* searchIndexIntoCorrespondeceTable(CORRESPONDENCE_TABLE* corrTable, unsigned long int toSearch, void* parameter){
    CORRESPONDENCE* ret;
    CORRESPONDENCE temp;
    void* ft;
    if(corrTable!=NULL){
        temp.index=toSearch;
        ft=corrTable->correspondenceIndex->l_operation->compare;
        corrTable->correspondenceIndex->l_operation->compare=compareCorrespondenceByIndex;
            ret=searchIntoHashTable(corrTable->correspondenceIndex, &temp, ft);
        corrTable->correspondenceIndex->l_operation->compare=ft;
    }
    return ret;
}

/****
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByID(CORRESPONDENCE_TABLE* corrTable, void* toDelete, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella da cui si vuole rimuovere l'informazione
-toDelete: l'informazione, in questo caso l'ID, tramite la quale eliminare la corrispondenza
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di cancellazione

OUTPUT:
- Restituisce il puntatore alla tabella della corrispondenze aggiornata, se l'elemento esisteva ed è stato eliminato,
  altrimenti restituisce semplicemente il puntatore alla tabella data in ingresso, che non viene modificata
****/
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByID(CORRESPONDENCE_TABLE* corrTable, void* toDelete, void* parameter){
    CORRESPONDENCE* td;
    FUNDEL ft;
    FUNCOM comPar;
    if(corrTable!=NULL){
        td=searchIDIntoCorrespondeceTable(corrTable, toDelete, parameter);

        comPar=corrTable->correspondenceID->l_operation->compare;
        corrTable->correspondenceID->l_operation->compare=compareCorrespondenceByID;
        ft=corrTable->correspondenceID->l_operation->del;
        corrTable->correspondenceID->l_operation->del=fakeDel;

            corrTable->correspondenceID=deleteFromHashTable(corrTable->correspondenceID, td, comPar);

        corrTable->correspondenceID->l_operation->compare=comPar;
        corrTable->correspondenceID->l_operation->del=ft;

        ft=corrTable->correspondenceIndex->l_operation->del;
        comPar=corrTable->correspondenceIndex->l_operation->compare;

        corrTable->correspondenceIndex->l_operation->del=fakeDel;
        corrTable->correspondenceIndex->l_operation->compare=compareCorrespondenceByIndex;

            corrTable->correspondenceIndex=deleteFromHashTable(corrTable->correspondenceIndex, td, comPar);

        corrTable->correspondenceIndex->l_operation->del=ft;
        corrTable->correspondenceID->l_operation->compare=comPar;

        deleteCorrespondence(td, corrTable->correspondenceID->l_operation);
    }
    return corrTable;
}

/****
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByInedx(CORRESPONDENCE_TABLE* corrTable, unsigned long int toDelete, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella da cui si vuole rimuovere l'informazione
-toDelete: l'informazione, in questo caso l'indice, tramite la quale eliminare la corrispondenza
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di cancellazione

OUTPUT:
- Restituisce la tabella della corrispondenze aggiornata, se l'elemento esisteva ed è stato eliminato,
  altrimenti restituisce semplicemente il puntatore alla tabella data in ingresso, che non viene modificata
****/
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByIndex(CORRESPONDENCE_TABLE* corrTable, unsigned long int toDelete, void* parameter){
    CORRESPONDENCE* td;
    FUNDEL ft;
    FUNCOM comPar;
    if(corrTable!=NULL){
        td=searchIndexIntoCorrespondeceTable(corrTable, toDelete, parameter);

        comPar=corrTable->correspondenceID->l_operation->compare;
        corrTable->correspondenceID->l_operation->compare=compareCorrespondenceByID;

        ft=corrTable->correspondenceID->l_operation->del;
        corrTable->correspondenceID->l_operation->del=fakeDel;

            corrTable->correspondenceID=deleteFromHashTable(corrTable->correspondenceID, td, comPar);

        corrTable->correspondenceID->l_operation->compare=comPar;
        corrTable->correspondenceID->l_operation->del=ft;

        ft=corrTable->correspondenceIndex->l_operation->del;
        comPar=corrTable->correspondenceIndex->l_operation->compare;

        corrTable->correspondenceIndex->l_operation->del=fakeDel;
        corrTable->correspondenceIndex->l_operation->compare=compareCorrespondenceByIndex;

            corrTable->correspondenceIndex=deleteFromHashTable(corrTable->correspondenceIndex, td, comPar);

        corrTable->correspondenceIndex->l_operation->del=ft;
        corrTable->correspondenceID->l_operation->compare=comPar;

        deleteCorrespondence(td, corrTable->correspondenceID->l_operation->del);
    }
    return corrTable;
}

/****
CORRESPONDENCE_TABLE* freeCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella che si vuole deallocare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che può servire come parametro ulteriore per la funzione di cancellazione

OUTPUT:
-Dealloca tutta la tabella delle corrispondenze e restituisce un puntatore a NULL;
****/
CORRESPONDENCE_TABLE* freeCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, void* parameter){
    FUNDEL fun;
    if(corrTable!=NULL){
        fun=corrTable->correspondenceIndex->l_operation->del;
        corrTable->correspondenceIndex->l_operation->del=fakeDel;
            freeHashTable(corrTable->correspondenceIndex, NULL);
        corrTable->correspondenceIndex->l_operation->del=fun;

        fun=corrTable->correspondenceID->l_operation->del;
        corrTable->correspondenceID->l_operation->del=deleteCorrespondence;
            freeHashTable(corrTable->correspondenceID, fun);
        corrTable->correspondenceID->l_operation->del=fun;

        free(corrTable);
        corrTable=NULL;
    }
    return corrTable;
}

/*************FUNZIONI DI SUPPORTO*************/

/****
void* fakeDel(void* toDel, void* param)

INFO: questa è una funzione di supporto da passare per evitare di eliminare di un elemento nella tabella hashing degli ID
      prima che venga cercata anche in quella degli indici. Così si riesce ad evitare uno spreco di spazio per la ridondanza dell'informazione.

INPUT: void* fakeDel(void* toDel, void* param)
-toDel: puntatore all'informazione che in teoria si dovrebbe cancellare
-param: parametro inserito in firma, ma non utilizzato. Serve per mantenere lo standard di firma per la funzioni di cancellazione

OUTPUT:
Restituisce il puntatore all'informazione che dovrebbe essere deallocata

****/
void* fakeDel(void* toDel, void* param){
    return toDel;
}

/****
int compareCorrespondenceByID(void* a, void* b, void* parameter)

INPUT:
-a, b: puntatori alle corrispondenze di cui si vuole comparare gli ID
-parameter: in questo caso è il puntatore alla funzione di comparazione
            per gli ID delle corrispondenze.

OUTPUT:
Ritorna 0 se i due ID sono uguali
Ritorna -1 se l'ID di a è minore dell'ID di b
Ritorna 1 se l'ID di a è maggiore dell'ID di b
****/
int compareCorrespondenceByID(void* a, void* b, void* parameter){
    FUNCOM temp=(FUNCOM)parameter;
    return temp(((CORRESPONDENCE*)a)->ID, ((CORRESPONDENCE*)b)->ID, NULL);
}

/****
int compareCorrespondenceByIndex(void* a, void* b, void* parameter)

INPUT:
-a, b: puntatori alle corrispondenze di cui si vuole comparare gli indici
-parameter: in questo caso è il puntatore alla funzione di comparazione
            per gli indici delle corrispondenze.

OUTPUT:
Ritorna 0 se i due indici sono uguali
Ritorna -1 se l'indice di a è minore dell'indice di b
Ritorna 1 se l'indice di a è maggiore dell'indice di b
****/
int compareCorrespondenceByIndex(void* a, void* b, void* parameter){
    return compareInteger(&((CORRESPONDENCE*)a)->index, &((CORRESPONDENCE*)b)->index, parameter);
}

/****
void* fakeCopy(void* toDel, void* param)

INFO: questa è una funzione di supporto da passare per evitare la copia di un elemento, nel caso in cui non si voglia copiarla.

INPUT:
-fake: puntatore dell'indirizzo in cui si vorrebbe copiare l'informazione. Inutilizzato,
       serve a mantenere lo standard di firma per la funzioni di copia
-toCopy: puntatore all'informazione che in teoria si dovrebbe copiare
-param: parametro inserito in firma, ma non utilizzato. Serve per mantenere lo standard di firma per la funzioni di copia

OUTPUT:
Restituisce il puntatore all'informazione che dovrebbe essere copiata

****/
void* fakeCopy(void* fake, void* toCopy, void* parameter){
    return toCopy;
}

/****
unsigned long int hashCorrespondenceID(void* toHash, void* parameter)

INPUT:
-toHash: in questo caso è l'indirizzo della corrispondenza della quala si vuole fare l'hashing dell'ID
-parameter: inutilizato

OUTPUT:
Restituisce l'indice di hashing dell'ID
****/
unsigned long int hashCorrespondenceID(void* toHash, void* parameter){
    return hashingString(((CORRESPONDENCE*)toHash)->ID, parameter);
}

/****
unsigned long int hashCorrespondenceIndex(void* toHash, void* parameter)

INPUT:
-toHash: in questo caso è l'indirizzo della corrispondenza della quala si vuole fare l'hashing dell'indice
-parameter: inutilizato

OUTPUT:
Restituisce l'indice di hashing dell'indice
****/
unsigned long int hashCorrespondenceIndex(void* toHash, void* parameter){
    return ((CORRESPONDENCE*)toHash)->index;
}

/****
void printIDCorrespondence(FILE* fp, void* toPrint, void* parameter)

INPUT:
-fp: il puntatore al file su cui si vuole stampare l'ID della corrispondenza. Anche lo standard output vale come file
-corrTable: il puntatore alla corrispondenza della quale si vuole stampare l'ID
-parameter: il puntatore alla funzione di stampa per gli ID

OUTPUT:
- NON PREVEDE OUTPUT
****/
void printIDCorrespondence(FILE* fp, void* toPrint, void* parameter){
    FUNPRINT temp=(FUNPRINT)parameter;
    temp(fp, ((CORRESPONDENCE*)toPrint)->ID, NULL);
}

/****
void printIndexCorrespondence(FILE* fp, void* toPrint, void* parameter)

INPUT:
-fp: il puntatore al file su cui si vuole stampare l'indice della corrispondenza. Anche lo standard output vale come file
-corrTable: il puntatore alla corrispondenza della quale si vuole stampare l'indice
-parameter: il puntatore alla funzione di stampa per gli indici
OUTPUT:
- NON PREVEDE OUTPUT
****/
void printIndexCorrespondence(FILE* fp, void* toPrint, void* parameter){
    fprintf(fp, "%d", ((CORRESPONDENCE*)toPrint)->index);
}

/****
void printCorrespondence(FILE* fp, void* toPrint, void* parameter)

INPUT:
-fp: il puntatore al file su cui si vuole stampare la corrispondenza. Anche lo standard output vale come file
-corrTable: il puntatore alla corrispondenza che si vuole stampare l'indice
-parameter: --
OUTPUT:
- NON PREVEDE OUTPUT
****/
void printCorrespondence(FILE* fp, void*toPrint, void*paramater){
    printIDCorrespondence(fp, toPrint, printString);
    fprintf(stdout, "\n");
    printIndexCorrespondence(fp, toPrint, NULL);
}

/****
void* deleteCorrespondence(void* toDel, void* parameter)

INPUT:
-toDel: puntatore alla corrispondfenza che si vuole cancellare
-parameter: --
OUTPUT:
Restituisce un puntatore a NULL.
****/
void* deleteCorrespondence(void* toDel, void* parameter){
    FUNDEL fun;
    if(toDel!=NULL){
        fun=(FUNDEL)parameter;
        fun(((CORRESPONDENCE*)(toDel))->ID, parameter);
        free(toDel);
        toDel=NULL;
    }
    return toDel;
}
