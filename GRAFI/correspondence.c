#include"data.h"
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
CORRESPONDENCE_TABLE* initCorresponcendeTable(unsigned int dimension, FUNCTDATA* IDOperation, FUNCTDATA* IndexOperation){
    CORRESPONDENCE_TABLE* newCorrTable=(CORRESPONDENCE_TABLE*)malloc(sizeof(CORRESPONDENCE_TABLE));
    newCorrTable->correspondenceID=initHashTable(dimension, IDOperation);
    newCorrTable->correspondenceIndex=initHashTable(dimension, IndexOperation);
    return newCorrTable;
}


/****
CORRESPONDENCE* newCorrespondence(void* ID, unsigned int index, FUNCPY fcopy, void* parameter)
INPUT:
-ID: puntatore all'informazione che si vuole inserire
-index: l'indice in cui � conservata l'informazione
-fcopy: puntatore alla funzione di copia per l'ID
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di copia

OUTPUT:
Alloca e restituisce il puntatore ad una corrispondenza

****/
CORRESPONDENCE* newCorrespondence(void* ID, unsigned int index, FUNCTDATA* IDoperation, FUNCTDATA* IndexOperation, void* parameter){
    CORRESPONDENCE* ret=(CORRESPONDENCE*)malloc(sizeof(CORRESPONDENCE));
    ret->ID=IDoperation->fcopy(ret->ID, ID, parameter);
    ret->index=index;
//        ret->index=IndexOperation->fcopy(ret->index, index, parameter);

    return ret;
}

/****
CORRESPONDENCE_TABLE* insertIntoCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, CORRESPONDENCE* toInsert, void* parameter)
INPUT:
-corrTable: il puntatore alla tabella delle corrispondenze nella quale si vuole inserire una corrispondenza
-toInsert: il puntatore alla corrispondenza che si vuole inserire
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di inserimento

OUTPUT:
Inserisce in corrTable una nuova corrispondenza, e restituisce il puntatore alla tabella aggiornata
****/
CORRESPONDENCE_TABLE* insertIntoCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, CORRESPONDENCE* toInsert, FUNCTDATA* IDoperation, FUNCTDATA* indexOperation, void* parameter){
    void* ft;
    void *st;
    void* tt;
    if(corrTable!=NULL){
        /****sostituisco funzione copia con una funzione pigra*****/
        ft=corrTable->correspondenceID->l_operation->fcopy;
        corrTable->correspondenceID->l_operation->fcopy=fakeCopy;
        st=corrTable->correspondenceID->l_operation->fhas;
        corrTable->correspondenceID->l_operation->fhas=hashCorrespondenceID;
        tt=corrTable->correspondenceID->l_operation->fcomp;
        corrTable->correspondenceID->l_operation->fcomp=compareCorrespondenceByID;

            corrTable->correspondenceID=insertIntoHashTable(corrTable->correspondenceID, toInsert, IDoperation);
        /****rimetto a posto*****/

        corrTable->correspondenceID->l_operation->fcopy=ft;
        corrTable->correspondenceID->l_operation->fhas=st;
        corrTable->correspondenceID->l_operation->fcomp=tt;
        /****sostituisco funzione copia con una funzione pigra*****/

        ft=corrTable->correspondenceIndex->l_operation->fcopy;
        corrTable->correspondenceIndex->l_operation->fcopy=fakeCopy;
        st=corrTable->correspondenceID->l_operation->fhas;
        corrTable->correspondenceIndex->l_operation->fhas=hashCorrespondenceIndex;
        tt=corrTable->correspondenceID->l_operation->fcomp;
        corrTable->correspondenceIndex->l_operation->fcomp=compareCorrespondenceByIndex;
            corrTable->correspondenceIndex=insertIntoHashTable(corrTable->correspondenceIndex, toInsert, indexOperation);

        /****rimetto a posto*****/
        corrTable->correspondenceIndex->l_operation->fcopy=ft;
        corrTable->correspondenceIndex->l_operation->fhas=st;
        corrTable->correspondenceIndex->l_operation->fcomp=tt;
    }
    return corrTable;
}

/****
void printCorrespondenceTable(FILE* fp, CORRESPONDENCE_TABLE* table, void* parameter)

INPUT:
-fp: il puntatore al file su cui si vuole stampare la tavola delle corrispondenze. Anche lo standard output vale come file
-corrTable: il puntatore alla tabella che si vuole stampare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di stampa

OUTPUT:
- NON PREVEDE OUTPUT
****/
void printCorrespondenceTable(FILE* fp, CORRESPONDENCE_TABLE* corrTable, FUNCTDATA* IDoperation, FUNCTDATA* indexOperation, void* parameter){
    void* ft;
    if(corrTable!=NULL){
        ft=corrTable->correspondenceID->l_operation->fpri;
        corrTable->correspondenceID->l_operation->fpri=printIDCorrespondence;
            printHashTable(fp, corrTable->correspondenceID, IDoperation);
        corrTable->correspondenceID->l_operation->fpri=ft;

        ft=corrTable->correspondenceIndex->l_operation->fpri;
        corrTable->correspondenceIndex->l_operation->fpri=printIndexCorrespondence;
            printHashTable(fp, corrTable->correspondenceIndex, indexOperation);
        corrTable->correspondenceIndex->l_operation->fpri=ft;
    }
}

/****
CORRESPONDENCE* searchIDIntoCorrespondeceTable(CORRESPONDENCE_TABLE* corrTable, void* toSearch, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella che si vuole stampare
-toSearch: l'informazione, in questo caso l'ID, che si vuole ricercare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di stampa

OUTPUT:
- Restituisce il puntatore alla corrispondenza in cui si trova l'informazione cercata,
  o un puntatore a NULL nel caso non sia stata trovata
****/
CORRESPONDENCE* searchIDIntoCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, void* toSearch, FUNCTDATA* IDoperation, void* parameter){
    CORRESPONDENCE* ret=NULL;
    CORRESPONDENCE temp;
    void *ft, *st;
    if(corrTable!=NULL){
        temp.ID=toSearch;
        ft=corrTable->correspondenceID->l_operation->fcomp;
        corrTable->correspondenceID->l_operation->fcomp=compareCorrespondenceByID;
        st=corrTable->correspondenceID->l_operation->fhas;
        corrTable->correspondenceID->l_operation->fhas=hashCorrespondenceID;

            ret=searchIntoHashTable(corrTable->correspondenceID, &temp, IDoperation);

        corrTable->correspondenceID->l_operation->fcomp=ft;
        corrTable->correspondenceID->l_operation->fhas=st;
    }
    return ret;
}

/****
CORRESPONDENCE* searchIndexIntoCorrespondeceTable(CORRESPONDENCE_TABLE* corrTable, unsigned int long toSearch, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella che si vuole stampare
-toSearch: l'informazione, in questo caso l'indice, che si vuole ricercare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di ricerca

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
        ft=corrTable->correspondenceIndex->l_operation->fcomp;
        corrTable->correspondenceIndex->l_operation->fcomp=compareCorrespondenceByIndex;
            ret=searchIntoHashTable(corrTable->correspondenceIndex, &(temp.index), ft);
        corrTable->correspondenceIndex->l_operation->fcomp=ft;
    }
    return ret;
}

/****
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByID(CORRESPONDENCE_TABLE* corrTable, void* toDelete, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella da cui si vuole rimuovere l'informazione
-toDelete: l'informazione, in questo caso l'ID, tramite la quale eliminare la corrispondenza
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di cancellazione

OUTPUT:
- Restituisce il puntatore alla tabella della corrispondenze aggiornata, se l'elemento esisteva ed � stato eliminato,
  altrimenti restituisce semplicemente il puntatore alla tabella data in ingresso, che non viene modificata
****/
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByID(CORRESPONDENCE_TABLE* corrTable, void* toDelete, FUNCTDATA* IDoperation, FUNCTDATA* indexOperation, void* parameter){
    CORRESPONDENCE* toRemove;
    void *ft;
    void* st;
    void* tt;
    if(corrTable!=NULL){
        toRemove=searchIDIntoCorrespondenceTable(corrTable, toDelete, IDoperation, parameter);
        printString(stdout, toRemove->ID, NULL);
        printf(" %d\n", toRemove->index);
        if(toRemove!=NULL){
            ft=corrTable->correspondenceID->l_operation->fhas;
            st=corrTable->correspondenceID->l_operation->fcomp;
            tt=corrTable->correspondenceID->l_operation->funfree;

            corrTable->correspondenceID->l_operation->fhas=hashCorrespondenceID;
            corrTable->correspondenceID->l_operation->fcomp=compareCorrespondenceByID;
            corrTable->correspondenceID->l_operation->funfree=fakeDel;

                corrTable->correspondenceID=deleteFromHashTable(corrTable->correspondenceID, toRemove, IDoperation);

            corrTable->correspondenceID->l_operation->fhas=ft;
            corrTable->correspondenceID->l_operation->fcomp=st;
            corrTable->correspondenceID->l_operation->funfree=tt;


            ft=corrTable->correspondenceIndex->l_operation->fhas;
            st=corrTable->correspondenceIndex->l_operation->fcomp;
  //          tt=corrTable->correspondenceIndex->l_operation->funfree;

            corrTable->correspondenceIndex->l_operation->fhas=hashCorrespondenceIndex;
            corrTable->correspondenceIndex->l_operation->fcomp=compareCorrespondenceByIndex;
            //corrTable->correspondenceID->l_operation->funfree=fakeDel;

                corrTable->correspondenceIndex=deleteFromHashTable(corrTable->correspondenceIndex, toRemove, indexOperation);

            corrTable->correspondenceIndex->l_operation->fhas=ft;
            corrTable->correspondenceIndex->l_operation->fcomp=st;
//            corrTable->correspondenceIndex->l_operation->funfree=tt;

        }
    }
    return corrTable;
}

/****
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByInedx(CORRESPONDENCE_TABLE* corrTable, unsigned long int toDelete, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella da cui si vuole rimuovere l'informazione
-toDelete: l'informazione, in questo caso l'indice, tramite la quale eliminare la corrispondenza
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di cancellazione

OUTPUT:
- Restituisce la tabella della corrispondenze aggiornata, se l'elemento esisteva ed � stato eliminato,
  altrimenti restituisce semplicemente il puntatore alla tabella data in ingresso, che non viene modificata
****/
CORRESPONDENCE_TABLE* removeFromCorrespondenceTableByIndex(CORRESPONDENCE_TABLE* corrTable, unsigned long int toDelete, FUNCTDATA* IDoperation, void* parameter){
    CORRESPONDENCE* td;
    FUNDEL ft;
    FUNCOM comPar;
    if(corrTable!=NULL){
        td=searchIndexIntoCorrespondeceTable(corrTable, toDelete, parameter);

        comPar=corrTable->correspondenceID->l_operation->fcomp;
//        corrTable->correspondenceID->l_operation->fcomp=compareCorrespondenceByID;

        ft=corrTable->correspondenceID->l_operation->funfree;
        corrTable->correspondenceID->l_operation->funfree=fakeDel;

            corrTable->correspondenceID=deleteFromHashTable(corrTable->correspondenceID, td, comPar);

        corrTable->correspondenceID->l_operation->fcomp=comPar;
        corrTable->correspondenceID->l_operation->funfree=ft;

        ft=corrTable->correspondenceIndex->l_operation->funfree;
        comPar=corrTable->correspondenceIndex->l_operation->fcomp;

        corrTable->correspondenceIndex->l_operation->funfree=fakeDel;
        corrTable->correspondenceIndex->l_operation->fcomp=compareCorrespondenceByIndex;

            corrTable->correspondenceIndex=deleteFromHashTable(corrTable->correspondenceIndex, td, comPar);

        corrTable->correspondenceIndex->l_operation->funfree=ft;
        corrTable->correspondenceID->l_operation->fcomp=comPar;

        deleteCorrespondence(td, corrTable->correspondenceID->l_operation->funfree);
    }
    return corrTable;
}

/****
CORRESPONDENCE_TABLE* freeCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, void* parameter)

INPUT:
-corrTable: il puntatore alla tabella che si vuole deallocare
-parameter: un puntatore ad informazioni di supporto, come una funzione o un ulteriore dato,
            che pu� servire come parametro ulteriore per la funzione di cancellazione

OUTPUT:
-Dealloca tutta la tabella delle corrispondenze e restituisce un puntatore a NULL;
****/
CORRESPONDENCE_TABLE* freeCorrespondenceTable(CORRESPONDENCE_TABLE* corrTable, FUNCTDATA* IDoperation, void* parameter){
    FUNDEL fun;
    if(corrTable!=NULL){
        fun=corrTable->correspondenceIndex->l_operation->funfree;
        corrTable->correspondenceIndex->l_operation->funfree=fakeDel;
            freeHashTable(corrTable->correspondenceIndex, NULL);
        corrTable->correspondenceIndex->l_operation->funfree=fun;

        fun=corrTable->correspondenceID->l_operation->funfree;
        corrTable->correspondenceID->l_operation->funfree=deleteCorrespondence;

            freeHashTable(corrTable->correspondenceID, fun);

        corrTable->correspondenceID->l_operation->funfree=fun;
        free(corrTable->correspondenceID->l_operation);
        free(corrTable->correspondenceIndex->l_operation);
        free(corrTable);
        corrTable=NULL;
    }
    return corrTable;
}

/*************FUNZIONI DI SUPPORTO*************/

/****
void* fakeDel(void* toDel, void* param)

INFO: questa � una funzione di supporto da passare per evitare di eliminare di un elemento nella tabella hashing degli ID
      prima che venga cercata anche in quella degli indici. Cos� si riesce ad evitare uno spreco di spazio per la ridondanza dell'informazione.

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
-parameter: in questo caso � il puntatore alla funzione di comparazione
            per gli ID delle corrispondenze.

OUTPUT:
Ritorna 0 se i due ID sono uguali
Ritorna -1 se l'ID di a � minore dell'ID di b
Ritorna 1 se l'ID di a � maggiore dell'ID di b
****/
int compareCorrespondenceByID(void* a, void* b, void* parameter){
    FUNCOM temp=((FUNCTDATA*)parameter)->fcomp;
    return temp(((CORRESPONDENCE*)a)->ID, ((CORRESPONDENCE*)b)->ID, NULL);
}

/****
int compareCorrespondenceByIndex(void* a, void* b, void* parameter)

INPUT:
-a, b: puntatori alle corrispondenze di cui si vuole comparare gli indici
-parameter: in questo caso � il puntatore alla funzione di comparazione
            per gli indici delle corrispondenze.

OUTPUT:
Ritorna 0 se i due indici sono uguali
Ritorna -1 se l'indice di a � minore dell'indice di b
Ritorna 1 se l'indice di a � maggiore dell'indice di b
****/
int compareCorrespondenceByIndex(void* a, void* b, void* parameter){
    return compareInteger(&((CORRESPONDENCE*)a)->index, &((CORRESPONDENCE*)b)->index, parameter);
}

/****
void* fakeCopy(void* toDel, void* param)

INFO: questa � una funzione di supporto da passare per evitare la copia di un elemento, nel caso in cui non si voglia copiarla.

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
-toHash: in questo caso � l'indirizzo della corrispondenza della quala si vuole fare l'hashing dell'ID
-parameter: inutilizato

OUTPUT:
Restituisce l'indice di hashing dell'ID
****/
unsigned long int hashCorrespondenceID(void* toHash, void* parameter){

    FUNHASH hashing=((FUNCTDATA*)(parameter))->fhas;
    return hashing(((CORRESPONDENCE*)toHash)->ID, parameter);
}

/****
unsigned long int hashCorrespondenceIndex(void* toHash, void* parameter)

INPUT:
-toHash: in questo caso � l'indirizzo della corrispondenza della quala si vuole fare l'hashing dell'indice
-parameter: inutilizato

OUTPUT:
Restituisce l'indice di hashing dell'indice
****/
unsigned long int hashCorrespondenceIndex(void* toHash, void* parameter){
    FUNHASH hashing=((FUNCTDATA*)(parameter))->fhas;
    return hashing(&((CORRESPONDENCE*)toHash)->index, parameter);
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
    FUNPRINT temp=((FUNCTDATA*)(parameter))->fpri;
    temp(fp, ((CORRESPONDENCE*)toPrint)->ID, NULL);
  // printString(fp, ((CORRESPONDENCE*)toPrint)->ID, NULL);
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
void printCorrespondence(FILE* fp, void*toPrint, void* parameter){
    if(toPrint!=NULL){
        printIDCorrespondence(fp, toPrint, parameter);
        fprintf(fp, " ");
        printIndexCorrespondence(fp, toPrint, NULL);
        fprintf(fp, "\n");
    }
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
