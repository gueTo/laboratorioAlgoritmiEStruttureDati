#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "listString.h"
#include "data.h"
#include "hash.h"
#include "corrispondence.h"

typedef enum {BLACK, GRAY, WHITE} COLOR;

typedef struct GRAPH_NODE{
    void* elem;
    COLOR color;
    unsigned int predecessor;
    unsigned int discover;
    unsigned int finish;
    unsigned int distance;
}GRAPH_NODE;


typedef struct GRAPH{
    GRAPH_NODE** nodes;
    int array_size;
    int num_vertex;
    LIST nodes_free;
    CORRESPONDANCE_TABLE* corrispondenze;
    //OPERAZIONI_LISTA* funzioniCorrispondenze;
    void* rappresentazione;
}GRAPH;



/*****/

/****/

/*operazioni grafo
inizializzazione
inserimento vertice
inserimento arco
cancellazione vertice
cancellazione arco

*/
GRAPH* initGraph(int array_size, int num_vertex, void* rappr){
    GRAPH* ret=(GRAPH*)malloc(sizeof(GRAPH));
    ret->num_vertex=num_vertex;
    ret->array_size=array_size;
    ret->nodes_free=NULL;
    ret->nodes=(GRAPH_NODE**)malloc(array_size*sizeof(GRAPH_NODE *));
    if(num_vertex<array_size){
        while(num_vertex<array_size){
            ret->nodes_free=PushLista(ret->nodes_free, (void*)num_vertex);
            num_vertex++;
        }
    }
    OPERAZIONI_LISTA* corrOp;
    corrOp= (OPERAZIONI_LISTA*)malloc(sizeof(OPERAZIONI_LISTA));
    *corrOp=InserisciFunzioni(&allocaCorrispondenza, &stampaCorrispondenza, &comparaCorrispondenze, &gestisciCollisioneCorrispondenza, &deallocaCorr, &LeggiCorrispondenzaDaFile, &hashCorrispondenza);
    ret->corrispondenze=initCorrespondanceTable(1037, corrOp);
    ret->rappresentazione=rappr;
    return ret;
}

GRAPH_NODE* inserisciNuovoNodoGrafo(void* info/**funzione copia e allocazione dato*/){
    GRAPH_NODE* nuovo=NULL;
    nuovo=(GRAPH_NODE*)malloc(sizeof(GRAPH_NODE));
    nuovo->elem=info;
    nuovo->color=WHITE;
    nuovo->discover=0;
    nuovo->distance=0;
    nuovo->finish=0;
    nuovo->predecessor=0;
    return nuovo;
}

GRAPH* inserisciVerticeGrafo(GRAPH* g, void* info){
    unsigned int position;
    int k;
    CORRESPONDANCE* ncorr;
//    LIST t;
    if(g!=NULL){
        if(g->nodes_free==NULL){
            g->array_size=g->array_size*1.20;
            g->nodes=(GRAPH_NODE**)realloc(g->nodes, g->array_size*sizeof(GRAPH_NODE*));
            k=g->num_vertex;
            while(k<g->array_size){
                g->nodes_free=PushLista(g->nodes_free, (void*)k);
                k++;
            }
        }
        position=(unsigned int)TopLista(g->nodes_free);
        g->nodes_free=PopLista(g->nodes_free);
        g->nodes[position]=inserisciNuovoNodoGrafo(info);
        g->num_vertex++;
        ncorr=(CORRESPONDANCE*)malloc(sizeof(CORRESPONDANCE));
        ncorr->ID=info;
        ncorr->index=position;
        g->corrispondenze=inserisciCorrispondenza(g->corrispondenze, ncorr, g->corrispondenze->corrId->operazioni);
    }
    return g;
}


GRAPH* inserisciArco(GRAPH* g, void* from, void* to, int peso){
    CORRESPONDANCE search;
    unsigned int nto, nfrom;
    if(g!=NULL){
        search.ID=from;
        nfrom=cercaCorrispondenza(g->corrispondenze, &search, g->corrispondenze->corrId->operazioni)->index;
        search.ID=to;
        nto=cercaCorrispondenza(g->corrispondenze, &search, g->corrispondenze->corrId->operazioni)->index;
    }
    return g;
}

GRAPH* cancellaVertice(GRAPH* g, void* info){
    unsigned int index;
    CORRESPONDANCE search;
    if(g!=NULL){
        search.ID=info;
        index=cercaCorrispondenza(g->corrispondenze, &search, g->corrispondenze->corrId->operazioni)->index;
        if(g->nodes[index]!=NULL){
//            deallocaGraphNode(g->nodes[index]);
            g->nodes[index]=NULL;
            g->num_vertex--;
            g->nodes_free=PushLista(g->nodes_free, (void*)index);
        }
        /**cancella tutti gli archi che partono o arrivano a quel vertice*/
        eliminaCorrispondenza(g->corrispondenze, &search, g->corrispondenze->corrId->operazioni);
    }
    return g;
}

GRAPH_NODE* ricercaVertice(GRAPH* g, void* info){
    CORRESPONDANCE search, *searched;
    search.ID=info;
    int index;
    searched=cercaCorrispondenza(g->corrispondenze, &search, g->corrispondenze->corrId->operazioni);
    if(searched!=NULL){
        return g->nodes[searched->index];
    }else return NULL;
}

GRAPH* cancellaArco(GRAPH* g, void* from, void* to){

}
