#ifndef _GRAFI_H_
    #define _GRAFI_H_


#include "correspondence.h"

#ifndef NESSUN_ARCO
#define NESSUN_ARCO 10000000
#endif

typedef enum COLOR {WHITE, GRAY, BLACK} COLOR;

typedef struct GRAPH_NODE{
    void *id;
    COLOR color;
    int pred;
    int dist;
    int scoperta;
    int completamento;
}GRAPH_NODE;

typedef struct GRAPH{
    GRAPH_NODE **vertici;
    LIST_OPERATION* operationInt;
    FUNCTDATA *operationID;//?
    int numVerticiUsati;
    int dimensioneArrayVertici;
    LIST listaNodiLiberi;
    CORRESPONDENCE_TABLE *correspondence;
    void* rapp;
}GRAPH;


//typedef GRAPH*(*INIT_RAPP)(GRAPH*);
#ifndef _FUNINIT_
#define _FUNINIT_

    typedef GRAPH*(*FUNINIT)(GRAPH*);

#endif // _FUNINIT_


typedef GRAPH*(*INS_VER)(GRAPH*);
typedef GRAPH*(*DEL_VER)(GRAPH*, int);
typedef GRAPH*(*INS_ARC)(GRAPH*, int, int, int);
typedef GRAPH*(*DEL_ARC)(GRAPH*, int, int);
typedef int(*EX_ARC)(GRAPH*, int, int);


typedef struct GRAPH_OPERATION{
    FUNINIT inizializza;
    INS_ARC inserisciArco;
    DEL_ARC eliminaArco;
    INS_VER inserisciVertice;
    DEL_VER eliminaVertice;
    EX_ARC esisteArco;
}GRAPH_OPERATION;


GRAPH_NODE* nuovoVertice(GRAPH* grafo, GRAPH_NODE* nodo, void* id);
GRAPH* inserisciVerticeGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* id, void* parameter);
GRAPH_NODE* cercaVerticeGrafo(GRAPH* grafo, void* ID, void* parameter);
GRAPH* cancellaVerticeGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* ID, void* parameter);
GRAPH* aggiungiArcoGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* da, void* a, int peso, void* parameter);
GRAPH* rimuoviArcoGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* da, void* a, void* parameter);
int esisteArcoGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* da, void* a, void* parameter);
void stampaGrafoMatrice(FILE* fp, GRAPH* grafo);
GRAPH* eliminaGrafo(GRAPH* grafo, void* parameter);
CORRESPONDENCE_TABLE* initCorrGraph(GRAPH* grafo, HASH_OPERATION* hash_id, LIST_OPERATION* list_id);
GRAPH* init(GRAPH* graf,int dim, FUNINS ins, FUNCPY cpy, FUNDEL del, FUNCOM comp, FUNPRINT pri, FUNHASH has, FUNCOLLISION coll);
#endif
